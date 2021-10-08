#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <cstdlib>
#include <bitset>

//define memory size
#define ADDRESS_BIT 32

using namespace std;

int main(int argc, const char *argv[])
{
    //This part reads all the data from the file ,line by line
    vector<string> input;
    ifstream filein;
    map<int, int> Hit;
    map<int, int> Miss;

    filein.open(argv[2], ios::in);

    ofstream fileout;
    fileout.open(argv[4], ios::out);

    int i = 0;
    string input_i;
    while (getline(filein, input_i))
    {
        input.push_back(input_i);
        i++;
    }
    filein.close();

    //Separate the input by its ow meaning

    int cache_size = atoi(input[0].c_str());
    cache_size = cache_size * 1024;
    int block_size = atoi(input[1].c_str());
    int input3 = atoi(input[2].c_str());
    ;
    int algorithm = atoi(input[3].c_str());
    ;

    // cout<<cache_size<<endl;
    // cout<<block_size<<endl;
    // cout<<input3<<endl;
    // cout<<algorithm<<endl;

    int associative = 0;
    if (input3 == 0)
    {
        associative = 1;
    }
    else if (input3 == 1)
    {
        associative = 4;
    }
    else if (input3 == 2)
    {
        associative = cache_size / block_size;
    }

    //get things
    int index = cache_size / block_size;
    int num_of_address = i - 4;
    int offset = log2(block_size);
    int setbit = log2(index / associative);
    int sets = index / associative;
    int tagbit = ADDRESS_BIT - setbit - offset;

    //The memory from the input file
    //By tag value,index value,and offset value

    std::vector<int> address_data;
    std::vector<int> tag;
    std::vector<int> indexval;
    std::vector<int> offsetval;

    //real cache spaces
    int cache_valid[sets][associative];
    memset(cache_valid, 0, sets * associative * sizeof(int));
    int cache_tag[sets][associative];
    memset(cache_tag, 0, sets * associative * sizeof(int));
    int cache_LRU[sets][associative];
    memset(cache_LRU, 0, sets * associative * sizeof(int));
    int cache_FIFO[sets];
    memset(cache_FIFO, 0, sets * sizeof(int));

    //Here is the part I analyze address

    int val;
    //stringstream ss;

    //string address[num_of_address];
    vector<string> address;

    //here move the memory address to normal range
    for (int i = 0; i < num_of_address; i++)
    {
        address.push_back(input[i + 4]);
    }

    int tag_tag;
    int index_index;
    int offset_offset;
    //process of cutting tag index and offset
    //bitwise operation
    for (int i = 0; i < num_of_address; i++)
    {
        tag_tag = 0;
        index_index = 0;
        offset_offset = 0;

        //special implementation transfer hex string to integer value
        stringstream ss;
        unsigned int binval;
        ss << hex << address[i];
        ss >> binval;
        bitset<32> b(binval);

        val = binval;
        //fileout<<val<<endl;
        address_data.push_back(val);

        //tag
        int i_tagbit = tagbit - 1;
        for (int k = ADDRESS_BIT - 1; k >= ADDRESS_BIT - tagbit; k--)
        {
            if (val & 1 << k)
            {
                tag_tag |= 1 << i_tagbit;
            }
            i_tagbit--;
        }
        tag.push_back(tag_tag);

        //index or sets
        int i_indexbit = setbit - 1;
        for (int k = offset + setbit - 1; k >= offset; k--)
        {
            if (val & 1 << k)
            {
                index_index |= 1 << i_indexbit;
            }
            i_indexbit--;
        }
        indexval.push_back(index_index);

        //offset value
        for (int k = offset - 1; k >= 0; k--)
        {
            if (val & 1 << k)
            {
                offset_offset |= 1 << k;
            }
            offsetval.push_back(offset_offset);
        }
    }

    //for output purpose

    int hit_counter = 0;
    int miss_counter = 0;

    //Initaillize good value for LRU
    for (int i = 0; i < sets; i++)
    {
        for (int j = 0; j < associative; j++)
        {
            cache_LRU[i][j] = j;
        }
    }

    //variables declarations
    //int cache_FIFO[indexval[i]]=0;
    bool hit = false;
    int hit_LRU = 0;
    int hit_block = 0;
    //main loop for memory addresses
    for (int i = 0; i < num_of_address; i++)
    {
        //initially no hit happened

        hit = false;
        hit_block = 0;
        hit_LRU = 0;

        //check hit
        for (int j = 0; j < associative; j++)
        {
            if (cache_tag[indexval[i]][j] == tag[i] && cache_valid[indexval[i]][j] == 1)
            {
                hit = true;
                hit_LRU = cache_LRU[indexval[i]][j];
                hit_block = j;
            }
        }

        //algorithm LRU
        if (algorithm == 1)
        {
            if (hit == true)
            {
                for (int k = 0; k < associative; k++)
                {
                    if (cache_LRU[indexval[i]][k] > hit_LRU)
                    {
                        cache_LRU[indexval[i]][k]--;
                    }
                }
                cache_LRU[indexval[i]][hit_block] = associative - 1;
                Hit[hit_counter] = i + 1;
                hit_counter++;
            }
            else if (hit == false)
            {
                for (int k = 0; k < associative; k++)
                {
                    if (cache_LRU[indexval[i]][k] == 0)
                    {
                        cache_LRU[indexval[i]][k] = associative - 1;
                        cache_tag[indexval[i]][k] = tag[i];
                        cache_valid[indexval[i]][k] = 1;
                    }
                    else
                        cache_LRU[indexval[i]][k]--;
                }
                Miss[miss_counter] = i + 1;
                miss_counter++;
            }
        }

        //Algorithm FIFO
        if (algorithm == 0)
        {
            if (cache_FIFO[indexval[i]] >= associative)
            {
                cache_FIFO[indexval[i]] = 0;
            }
            if (hit == true)
            {
                Hit[hit_counter] = i + 1;
                hit_counter++;
            }
            else if (hit == false)
            {
                cache_tag[indexval[i]][cache_FIFO[indexval[i]]] = tag[i];
                cache_valid[indexval[i]][cache_FIFO[indexval[i]]] = 1;
                Miss[miss_counter] = i + 1;
                cache_FIFO[indexval[i]]++;
                miss_counter++;
            }
        }
    }

    map<int, int>::iterator it;
    fileout << "Hits instructions: ";
    for (it = Hit.begin(); it != Hit.end(); it++)
    {
        fileout << it->second;
        if (it->first != hit_counter - 1)
        {
            fileout << ",";
        }
    }
    fileout << endl;

    fileout << "Misses instructions: ";
    for (it = Miss.begin(); it != Miss.end(); it++)
    {
        fileout << it->second;
        if (it->first != miss_counter - 1)
        {
            fileout << ",";
        }
    }
    fileout << endl;

    fileout << "Miss rate: " << (float)miss_counter / num_of_address << endl;

    fileout.close();
    return 0;
}
