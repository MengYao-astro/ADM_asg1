#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <utility> // std::pair

using namespace std;

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset){
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create and output filestream object
    cout << "Saving output to: \n";
    cout << filename+"\n";
    std::ofstream myFile(filename);

    // Send the column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    } // for
    myFile << "\n";

    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        } // for
        myFile << "\n";
    } // for

    // Close the file
    myFile.close();

} // void

std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){

  // Reads a CSV file into a vector of <string, vector<int> pairs where each pair represents <column name, column values>

  // Create a vector of <string, int vector> pairs to store the result
  std::vector<std::pair<std::string, std::vector<int>>> result;

  // Create an input filestream
  std::ifstream myFile(filename);

  // Make sure that the file is open
  if(!myFile.is_open()) throw std::runtime_error("Could not open file");

  // Helper variables
  std::string line, colname;
  int val;

  // Read the column names
  if(myFile.good())
  {
    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stingstream from line
    std::stringstream ss(line);

    // Extract each column name
    while(std::getline(ss, colname, ',')){

      // Initialize and add <colname, int vector> pairs to result
      result.push_back({colname,std::vector<int> {}});
    }// while
  }// if

   // Read data, line by line
   while(std::getline(myFile, line))
   {
      // Create a stringstream of the current line
      std::stringstream ss(line);

      // Keep track of the current column index
      int colIdx = 0;

      // Extract each integer
      while(ss >> val){

        // Add the current integer to the 'colIdx' column's values vector
        result.at(colIdx).second.push_back(val);

        // If the next token is a comma, ignore it and move on
        if(ss.peek() == ',') ss.ignore();

        // Increment the column index
        colIdx++;
      }// while
    }// while

    // Close file
    myFile.close();

    return result;

}//vector

int main() {

    // Setting name and directory of output
    //string file_directory = "/home/vbuchem/Documents/ADM_asg1/";
    string file_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM_asg1/";
    string file_name = "foo.csv";
    string file_loc = file_directory + file_name;

    // Make test output vector
    std::vector<int> test_data0(100,1);
    std::vector<int> test_data1(100,2);
    std::vector<int> test_data2(100,3);
    std::vector<std::pair<std::string, std::vector<int>>> test_data = {{"One",test_data0},{"Two",test_data1},{"Three",test_data2}};

    // Write the vector to CSV
    write_csv(file_loc, test_data);

    // Read the file that we have just written
    std::vector<std::pair<std::string, std::vector<int>>> data = read_csv(file_loc);
    cout << "Printing the name of the first column and first value in that column: \n";
    std::cout << data.at(0).first << "\n";
    std::cout << data.at(0).second.at(0);

    return 0;
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
