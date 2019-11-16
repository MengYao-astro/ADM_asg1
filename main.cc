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
	// Compute average of first 50 elements and take that as reference number.
	int sum = 0;
	int boundary = 50;
	for (int i = 0; i < boundary; i++ ) {
		sum += array.at(i);
	}
	int ref_number = sum / boundary;

	return ref_number;
}

// Frame of reference encoding
std::vector<int> for_encoding(std::vector<int> array) {
  cout << "Applying frame of reference encoding.\n ";
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

  std::vector<int> data_int;
  std::vector<string> data_string;

 // Reads int data from files
  std::vector<int> int_reader(string name){
    string line;
    int number;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        istringstream buffer(line);
        buffer >> number;
        data_int.push_back(number);
      } // while
      cout << "Size of data-set: " << data_int.size() << "\n";
    } // if
    return data_int;
  } // vector int_reader

  std::vector<string> string_reader(string name){
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
    return data_string;
  } // vector string_reader

  void read_data(){
    cout << "Reading data from: " << set_loc+set_name << "\n";
    if (set_type.compare(str)==0){
      string_reader(set_loc+set_name);
    }//if
    else{
      int_reader(set_loc+set_name);
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


void write_csv(std::string filename, std::vector<int> dataset,string dtype){
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // colname - the name of the one and only column
    // vals - an integer vector of values

    // Create and output filestream object
    cout << "Saving output to: \n";
    cout << filename+"\n";
    std::ofstream myFile(filename);
    int force_int8 = 0;
    if (force_int8 == 0){
//    if (dtype.compare(int8)==0){
      // Send data to the stream
      for(int i = 0; i < dataset.size(); ++i)
      {
        int8_t number = dataset.at(i);
        myFile << number;
        myFile << "\n";
      } // for
    } // if

    else if (dtype.compare(int16)==0){
      // Send data to the stream
      for(int i = 0; i < dataset.size(); ++i)
      {
        int16_t number = dataset.at(i);
        myFile << number;
        myFile << "\n";
      } // for
    } // else if

    else if (dtype.compare(int32)==0){
      // Send data to the stream
      for(int i = 0; i < dataset.size(); ++i)
      {
        int32_t number = dataset.at(i);
        myFile << number;
        myFile << "\n";
      } // for
    } // else if

    else if (dtype.compare(int64)==0){
      // Send data to the stream
      for(int i = 0; i < dataset.size(); ++i)
      {
        int64_t number = dataset.at(i);
        myFile << number;
        myFile << "\n";
      } // for
    } // else if

    else if (dtype.compare(str)==0){
      // Send data to the stream
      for(int i = 0; i < dataset.size(); ++i)
      {
        myFile << dataset.at(i);
        myFile << "\n";
      } // for
    } // else if


    // Close the file
    myFile.close();

} // void

int main() {
  string dtype;
  //cout << "Please give dtype: ";
  //cin >> dtype;
  // Setting name and directory of output
  //string file_directory = "/home/vbuchem/Documents/ADM_asg1/";
  string working_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM_asg1/";
  string data_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM-2019-Assignment-1-data-T-SF-1/";
  dtype = "int64";
  string data_file_list;

  if (dtype.compare(int8)==0){
      data_file_list = "data_list_int8.csv";
      std::vector<int> data;
    }//if
  else if (dtype.compare(int16)==0){
      data_file_list = "data_list_int16.csv";
      std::vector<int> data;
    } //else if
  else if (dtype.compare(int32)==0){
      data_file_list = "data_list_int32.csv";
      std::vector<int> data;
    } //else if
  else if (dtype.compare(int64)==0){
      data_file_list = "data_list_int64.csv";
      std::vector<int> data;
    } //else if
  else if(dtype.compare(str)==0){
      data_file_list = "data_list_string.csv";
      std::vector<string> data;
    } //else

  // Reading file names
  std::vector<string> files = getFileNames(working_directory+data_file_list);

  //string dtype = "string";
  for (int i = 0; i < files.size()-1; i++){
  //for (int i = 0; i < 1; i++){
    data_set dset;
    dset.set_loc = data_directory;
    dset.set_name = files.at(i);
    dset.set_type = dtype;
    dset.read_data();

    // Frame of reference encoding
    string file_name_for = files.at(i).erase(files.at(i).size()-3,3)+"for";
	  std::vector<int> data_en_for = for_encoding(dset.data_int);
    write_csv(data_directory+file_name_for,data_en_for,dtype);
  }




    return 0;
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
