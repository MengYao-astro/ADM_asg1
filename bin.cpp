//
//  bin.cpp
//  bit_vector
//
//  Created by Meng Yao on 17/11/2019.
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
#include <algorithm>

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

void bin_encoding(std::vector<int> file)
{
    vector<int> IDs;
    vector<long> indice;
    ofstream file_com;
    file_com.open("/Users/mengyao/work/ADM/bit_vector/bin_en.txt", ofstream::app);
    file_com<<file.size()<<endl;
    IDs = file;
    vector<int>::iterator ip;
    std::sort(IDs.begin(),IDs.end());
    ip = std::unique(IDs.begin(), IDs.end());
    IDs.resize(std::distance(IDs.begin(), ip));
    for (ip = IDs.begin(); ip != IDs.end(); ++ip)
    {
          file_com<<*ip<<";";
    }
    file_com<<endl;
    for (int i=0; i< IDs.size();i++)
    {
        for(int j=0; j<file.size(); j++)
        {
            if( file[j] == IDs[i])
            {
                file_com<<j<<";" ;// save the bit vector as a sparse matrix.
                //Only save the position of zeros
            }
            else{}
        }
        file_com<<endl;
    }

    
    cout<<"Compressed"<<endl;
};

void bin_decoding(string filecom_name, string filedecom_name)
{
    ifstream file_com;
    ofstream file_decom;
    file_com.open(filecom_name);
    file_decom.open(filedecom_name, ofstream::app);
    string l1_length, l2_IDs;
    vector<int> IDs;
    vector<int> sparse;
    std::string delimiter = ";";
    size_t pos = 0;
    getline(file_com,l1_length);
    int file_length;
    istringstream buffer(l1_length);
    buffer >> file_length;
    vector<int> file_recover(file_length, 0);
    getline(file_com,l2_IDs);
    std::string element;
    while ((pos = l2_IDs.find(delimiter)) != std::string::npos)
    {
        element = l2_IDs.substr(0,pos);
        l2_IDs.erase(0,pos+delimiter.length());
        IDs.push_back(stoi(element));
    }
    for(int i=0;i<IDs.size();i++)
    {
        string sparse_line;
        getline(file_com, sparse_line);
        while ((pos = sparse_line.find(delimiter)) != std::string::npos)
        {
            element = sparse_line.substr(0,pos);
            sparse_line.erase(0,pos+delimiter.length());
            file_recover[stoi(element)] = IDs[i];
        }
    }
    for(int i =0; i<file_length; i++)
    {
        file_decom<<file_recover[i]<<endl;
    }
}


int main()
{
    remove("/Users/mengyao/work/ADM/bit_vector/bin_en.txt");
    remove("/Users/mengyao/work/ADM/bit_vector/bin_de.txt");
    std::vector<int> test_data{1,2,1,2,1};
    bin_encoding(test_data);
    bin_decoding("/Users/mengyao/work/ADM/bit_vector/bin_en.txt","/Users/mengyao/work/ADM/bit_vector/bin_de.txt");
    return 0;

};
