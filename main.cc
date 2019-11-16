#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <utility> // std::pair
#include <list>

using namespace std;

class data_set{
private:
  string int8 = "int8";
  string int16 = "int16";
  string int32 = "int32";
  string int64 = "int64";
  string str = "string";

  // Access specifier
public:

  // Data members
  string set_loc;
  string set_name;
  string set_type;

  std::vector<int8_t> data_int8;
  std::vector<int16_t> data_int16;
  std::vector<int32_t> data_int32;
  std::vector<int64_t> data_int64;
  std::vector<string> data_string;

 // Reads int data from files

  void int8_reader(string name){
    cout << "Dtype: int8 \n";
    string line;
    int8_t number;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        istringstream buffer(line);
        buffer >> number;
        data_int8.push_back(number);
      }
      cout << "Size of data-set: " << data_int8.size()
    }
  }

  void read_data(){
    cout << "Reading data from: " << set_loc+set_name << "\n";
    if (set_type.compare(int8)==0){
      int8_reader(set_loc+set_name);
    }//if
  }// void read_data_int
  /*
  void read_data_sting(){
    std::vector<string> data;
    cout << "Reading data from: " << set_loc+set_name << "\n";
    cout << "Data type: " << set_type << "\n";

    // Preparing variables
    string line;
    // Reading file
    ifstream myFile(set_loc+set_name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        data.push_back(line);
      }// while
    }// if
  }// vector read_data_string

  // Prints data set
  void print(){
    cout << "Printing first 10 rows from data set: " << set_name << "\n";
    for (int i = 0; i < 10; i++){
      cout << data.at(i) << "\n";
    } //for
    cout << "Total size of data_set = " << data.size() << "\n";
  } // void print
  */
};// class data_set

// Function that returns a list of all the file names
std::vector<string> getFileNames(string filename){
  cout << "Reading file names from: \n";
  cout << filename << "\n";

  // Preparing variables
  string line;
  std::vector<string> file_name_list;

  // Reading file
  ifstream myFile(filename);
  if (myFile.is_open()){
    while(!myFile.eof()){ // while the end of the file not reached
      getline(myFile,line);
      cout << line << "\n";
      file_name_list.push_back(line);
    } // while
  } // if

  // Returning list
  return file_name_list;
}

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
    string working_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM_asg1/";
    string data_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM-2019-Assignment-1-data-T-SF-1/";


    // Reading file names
    string string_file = "string_list.csv";
    vector<string> string_files = getFileNames(working_directory+string_file);
    string int_file = "int_list.csv";
    vector<string> int_files = getFileNames(working_directory+int_file);

    string dtype = "int8";

    data_set set_one;
    set_one.set_loc = data_directory;
    set_one.set_name = int_files.at(0);
    set_one.set_type = dtype;
    set_one.read_data();

    return 0;
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
