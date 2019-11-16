#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <utility> // std::pair
#include <list>
#include <typeinfo>

using namespace std;
string int8 = "int8";
string int16 = "int16";
string int32 = "int32";
string int64 = "int64";
string str = "string";

/*

#### En- and Decoding functions #####

*/

int reference_number(std::vector<int> array) {
	int length = array.size();

	// Compute average of first 50 elements and take that as reference number.
	int sum = 0;
	int boundary = 50;

	for (int i = 0; i < boundary; i++ ) {
		sum += array[i];
	}

	int ref_number = sum / boundary;

	return ref_number;
}

// Frame of reference encoding
std::vector<int> for_encoding(std::vector<int> array) {

  // Calculate reference number
  int ref_number = reference_number(array);
	// Initialise encoded array.
	std::vector<int> encoded_data;
	int length = array.size();

	// Compute encoded values.
	for (int i = 0; i < length; i++) {
		encoded_data.push_back(array[i] - ref_number);
	}

	// Return encoded_data.
	return encoded_data;
	}

/*

#### Data importing functions #####

*/


class data_set{
  public:
  // Data members
  string set_loc;
  string set_name;
  string set_type;

  std::vector<int> data_int8;
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
      } // while
      cout << "Size of data-set: " << data_int8.size() << "\n";
    } // if
  } // void int8_reader

  void int16_reader(string name){
    cout << "Dtype: int16 \n";
    string line;
    int16_t number;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        istringstream buffer(line);
        buffer >> number;
        data_int16.push_back(number);
      } // while
      cout << "Size of data-set: " << data_int16.size() << "\n";
    } // if
  } // void int16_reader

  void int32_reader(string name){
    cout << "Dtype: int32 \n";
    string line;
    int32_t number;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        istringstream buffer(line);
        buffer >> number;
        data_int32.push_back(number);
      } // while
      cout << "Size of data-set: " << data_int32.size() << "\n";
    } // if
  } // void int32_reader

  void int64_reader(string name){
    cout << "Dtype: int64 \n";
    string line;
    int64_t number;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        istringstream buffer(line);
        buffer >> number;
        data_int64.push_back(number);
      } // while
      cout << "Size of data-set: " << data_int64.size() << "\n";
    } // if
  } // void int8_reader

  void string_reader(string name){
    cout << "Dtype: string \n";
    string line;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        data_string.push_back(line);
      } // while
      cout << "Size of data-set: " << data_string.size() << "\n";
    } // if
  } // void string_reader

  void read_data(){
    cout << "Reading data from: " << set_loc+set_name << "\n";
    if (set_type.compare(int8)==0){
      int8_reader(set_loc+set_name);
    }//if
    else if (set_type.compare(int16)==0){
      int16_reader(set_loc+set_name);
    } //else if
    else if (set_type.compare(int32)==0){
      int32_reader(set_loc+set_name);
    } //else if
    else if (set_type.compare(int64)==0){
      int64_reader(set_loc+set_name);
    } //else if
    else if(set_type.compare(str)==0){
      string_reader(set_loc+set_name);
    } //else
  }// void read_data_int

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

/*

#### Data exporting functions #####

*/


void write_csv(std::string filename, std::vector<int> dataset){
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create and output filestream object
    cout << "Saving output to: \n";
    cout << filename+"\n";
    std::ofstream myFile(filename);

    // Send data to the stream
    for(int i = 0; i < dataset.size(); ++i)
    {
      myFile << dataset.at(i);
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
  string dtype;
  //cout << "Please give dtype: ";
  //cin >> dtype;
  // Setting name and directory of output
  //string file_directory = "/home/vbuchem/Documents/ADM_asg1/";
  string working_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM_asg1/";
  string data_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM-2019-Assignment-1-data-T-SF-1/";
  dtype = "int8";
  string data_file_list;

  if (dtype.compare(int8)==0){
      data_file_list = "data_list_int8.csv";
    }//if
  else if (dtype.compare(int16)==0){
      data_file_list = "data_list_int16.csv";
    } //else if
  else if (dtype.compare(int32)==0){
      data_file_list = "data_list_int32.csv";
    } //else if
  else if (dtype.compare(int64)==0){
      data_file_list = "data_list_int64.csv";
    } //else if
  else if(dtype.compare(str)==0){
      data_file_list = "data_list_string.csv";
    } //else

  // Reading file names
  std::vector<string> files = getFileNames(working_directory+data_file_list);

  //string dtype = "string";
  //for (int i = 0; i < files.size(); i++){
  for (int i = 0; i < 1; i++){
    data_set dset;
    dset.set_loc = data_directory;
    dset.set_name = files.at(i);
    dset.set_type = dtype;
    dset.read_data();
    // Frame of reference encoding
    string file_name_for = files.at(i).erase(files.at(i).size()-3,3)+"for";
	  std::vector<int> data_en_for = for_encoding(dset.data_int8);
    write_csv(working_directory+file_name_for,data_en_for);
  }




    return 0;
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
