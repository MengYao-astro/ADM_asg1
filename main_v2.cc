#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <utility> // std::pair
using namespace std;

string str = "string";

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
      string_reader(set_loc+set_name+".csv");
    }//if
    else{
      int_reader(set_loc+set_name+".csv");
    } //else
  }// void read_data_int

};// class data_set

// Frame of reference encoding
void for_encoding(data_set dset){
  cout << "Applying frame of reference encoding. \n";
  // Calculate reference number
  int sum = 0;
	int boundary = 50;
	for (int i = 0; i < boundary; i++ ) {
		sum += dset.data_int.at(i);
	}
	int ref_number = sum / boundary;

	// Initialise encoded array.
	std::vector<int> encoded_data;
	int length = dset.data_int.size();

	// Compute encoded values.
	for (int i = 0; i < length; i++) {
		encoded_data.push_back(dset.data_int.at(i) - ref_number);
	}

  // Write encoded data to csv
  string file_name_for = dset.set_name+".for";
	cout << "Saving output to: \n";
  cout << file_name_for << "\n";
  std::ofstream myFile(dset.set_loc+file_name_for);
  for(int i = 0; i < dset.data_int.size(); ++i)
  {
    int8_t number = dset.data_int.at(i);
    myFile << number;
    myFile << "\n";
  } // for

  // Close the file
    myFile.close();
} // void for encoding

int main(){

  string working_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM_asg1/";
  string data_directory = "C:/Users/Christiaan/Documents/Studie/ADM/ADM-2019-Assignment-1-data-T-SF-1/";

  cout << "Please enter the name of the file: \n";
  //cin << fname;
  string fname = "l_tax-int64.for";
  cout << "Would you like to decode (\"de\") or encode (\"en\") the file? \n";
  //cin << en_de;
  string en_de = "de";
  cout << "What is the data type of the file? \n";
  //cin << dtype;
  string dtype = "int64";
  string en = "en";

  if (en_de.compare(en)==0){ // The encoding algorithm

    data_set dset;
    dset.set_loc = data_directory;
    dset.set_name = fname.substr(0,fname.size()-4);
    dset.set_type = dtype;
    dset.read_data();

    //Frame of reference encoding
    for_encoding(dset);
  }

  else { // The decoding algorithm

    string ct_for = ".for";
    string ct = fname.substr(fname.size()-4,4);

    if (ct.compare(ct_for) == 0){


    }


  }
}
