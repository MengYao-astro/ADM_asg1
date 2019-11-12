#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

void write_csv(std::string filename, std::string colname, std::vector<int> vals){
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create and output filestream object
    cout << "Saving output to: \n";
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

int main() {

    // Setting name and directory of output
    string file_directory = "/home/vbuchem/Documents/ADM_asg1/";
    string file_name = "foo.csv";
    string file_loc = file_directory + file_name;
        
    // Make test output vector
    std::vector<int> test_data(100,1);
    string Col1_name = "Column 1";
    
    // Write the vector to CSV
    write_csv(file_loc, Col1_name, test_data);
    
    return 0;
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
