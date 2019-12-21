//
//  dic.cpp
//  dic_compress
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


void dic_encoding(std::vector<string> file)
{
    std::vector<string> dictionary;
    std::vector<int> indice;
    std::vector<string>::iterator it;
       
    ofstream file_com;
    file_com.open("/home/vbuchem/Documents/ADM_asg1/dic_en.txt", ofstream::app);
         
    for(int i=0; i < file.size();i++)
    {   
        it = std::find(dictionary.begin(),dictionary.end(),file[i]);
                
        if (it != dictionary.end())
        {
            int index = it - dictionary.begin() ;
            indice.push_back(index);
        }
        else
        {
            indice.push_back(dictionary.size());
            dictionary.push_back(file[i]);
        }
    for (int i=0; i<dictionary.size(); i++)
        file_com << dictionary[i] << ";";
    file_com<<endl;
    for (int i=0; i<dictionary.size(); i++)
        file_com << indice[i] << ";";  
    }
    
    cout<<"Compressed"<<endl;
    
};

/*
void dic_decoding(string filecom_name, string filedecom_name)
{
    ifstream file_com;
    ofstream file_decom;
    file_com.open(filecom_name);
    file_decom.open(filedecom_name, ofstream::app);
    string line1,line2;
    vector<string> dictionary;
    vector<int> indice;
    std::string delimiter = ";";
    size_t pos = 0;
    getline(file_com,line1);
    std::string element;
    while ((pos = line1.find(delimiter)) != std::string::npos)
    {
        element = line1.substr(0,pos);
        line1.erase(0,pos+delimiter.length());
        dictionary.push_back(element);
    }
    getline(file_com, line2);
    while ((pos = line2.find(delimiter)) != std::string::npos)
    {
        int index = std::stoi(line2.substr(0,pos));
        line2.erase(0,pos+delimiter.length());
        indice.push_back(index);
    }
    

    for(int i=0; i < indice.size();i++)
    {
        file_decom<<dictionary[indice[i]]<<endl;
    }
}
*/

int main()
{
    //remove("/Users/mengyao/work/ADM/dic_compress/dic_en.txt");
    //remove("/Users/mengyao/work/ADM/dic_compress/dic_de.txt");
    std::vector<string> test_data{"a","a","a","b","b","c"};
    //std::vector<string> test_data{"a","a","a","b","b","c"};
    
    dic_encoding(test_data);
    //dic_decoding("/Users/mengyao/work/ADM/dic_compress/dic_en.txt","/Users/mengyao/work/ADM/dic_compress/dic_de.txt");
    return 0;

};


