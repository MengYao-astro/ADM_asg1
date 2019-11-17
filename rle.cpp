//
//  main.cpp
//  compression
//
//  Created by Meng Yao on 16/11/2019.
//  Copyright © 2019 Meng Yao. All rights reserved.
//


#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <list>
using namespace std;

void write_csv(std::string filename, std::string colname, std::vector<int> vals){
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create and output filestream object
    cout << "File saved as: ";
    cout << filename+"\n";
    std::ofstream myFile(filename);

    // Send the column name to the stream
    myFile << colname << "\n";

    // Send data to the stream
    for(int i = 0; i < vals.size(); ++i)
    {
        myFile << vals.at(i) << "\n";
    }

    // Close the file
    myFile.close();
}

void rl_encoding(std::vector<string> file)
{
    struct RL_chunk {
    string value ;
    int start_pos = 0, run_length = 1;
    } rl_chunk;
    ofstream file_com;
    file_com.open("/Users/mengyao/work/ADM/compression/rl_en.txt", ofstream::app);
    for(int i=0; i < file.size();i++)
    {
        if(file[i] == file[i+1])
        {
            rl_chunk.run_length++ ;
        }
        else
        {
            rl_chunk.value = file[i];
            rl_chunk.start_pos = i+1-rl_chunk.run_length;
            file_com<<rl_chunk.value<<";"<<rl_chunk.start_pos<<";"<<rl_chunk.run_length<<endl;
            rl_chunk.run_length = 1;
        }
    }
    file_com.close();
    cout<<"Compressed"<<endl;
};

void rl_decoding(string filecom_name, string filedecom_name)
{
    string line;
    ifstream file_com;
    ofstream file_decom;
    file_com.open(filecom_name);
    file_decom.open(filedecom_name, ofstream::app);
    while ( getline(file_com,line))
    {
        string line_copy = line;
        std::string delimiter = ";";
        size_t pos = 0;
        std::string peice;
        while ((pos = line_copy.find(delimiter)) != std::string::npos)
        {
            peice = line_copy.substr(0,pos);
            line_copy.erase(0,pos+delimiter.length());
        }
        int run_length = std::stoi(line_copy);
        size_t pos_value = line.find(delimiter);
        string value = line.substr(0,pos_value);
        for(int i=0; i < run_length;i++)
        {
            file_decom<<value<<endl;
        }
    }
}


int main()
{
    remove("/Users/mengyao/work/ADM/compression/rl_en.txt");
    remove("/Users/mengyao/work/ADM/compression/rl_de.txt");
    std::vector<string> test_data{"a","a","a","b","b","c"};
    rl_encoding(test_data);
    rl_decoding("/Users/mengyao/work/ADM/compression/rl_en.txt","/Users/mengyao/work/ADM/compression/rl_de.txt");
    return 0;

};
