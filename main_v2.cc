#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <utility> // std::pair
#include <algorithm>
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

  void read_data(string filetype){
    cout << "Reading data from: " << set_loc+set_name << "\n";
    if (set_type.compare(str)==0){
      string_reader(set_loc+set_name+filetype);
    }//if
    else{
      int_reader(set_loc+set_name+filetype);
    } //else
  }// void read_data_int

};// class data_set

/*
------------- ENCODING AND DECODING ALGORITHMS -------------
In the lines below each encoding/decoding method as an associated function.
Each encoding function accepts a class object called 'data_set' and then encodes it and saves it.
Every decoding function reads the given file itself, decodes it and writes a new unencoded file.
*/

// --- Run-length encoding ---
void rl_encoding(data_set dset){
    cout << "Applying run-length encoding. \n";
    // Passing data to new vector
    std::vector<int> file = dset.data_int;
  
    // Creating chunk object
    struct RL_chunk {
      int value ;
      int start_pos = 0, run_length = 1;
    } rl_chunk;
    
    // Preparing output file
    string file_name_rle = dset.set_loc+dset.set_name+".rle"; 
    std::ofstream myFile(file_name_rle);
    // Running through data
    for(int i=0; i < file.size();i++){
        if(file[i] == file[i+1]){
            rl_chunk.run_length++ ;
        }//if 
        else{
            rl_chunk.value = file.at(i);
            rl_chunk.start_pos = i+1-rl_chunk.run_length;
            myFile << rl_chunk.value<<";"<<rl_chunk.start_pos<<";"<<rl_chunk.run_length<<endl;
            rl_chunk.run_length = 1;
        }//else
    }//for
    myFile.close();   
}//void rl encoding 

// --- Run-length decoding ---
void rl_decoding(string filecom_name){
    cout << "Decoding run-length encoded file. \n";
    string line;
    ifstream file_com;
    file_com.open(filecom_name);
    for(int i=0; i < 10; i++){
      getline(file_com,line);
      string line_copy = line;
      std::string delimiter = ";";
      size_t pos = 0;
      std::string peice;
      while ((pos = line_copy.find(delimiter)) != std::string::npos){
          peice = line_copy.substr(0,pos);
          line_copy.erase(0,pos+delimiter.length());
      }
      int run_length = std::stoi(line_copy);
      size_t pos_value = line.find(delimiter);
      string value = line.substr(0,pos_value);
      cout << "\nDecoded data: \n";
      for(int i=0; i < run_length; i++){
        cout << value << endl;  
      }//while
    }//for
    file_com.close();
}//void rl_decoding

// --- Dictionary encoding ---
void dic_encoding(data_set dset){
    cout << "Applying dictionary encoding. \n";
    // Passing data to new vector
    std::vector<string> file = dset.data_string;
    // Preparing variables    
    std::vector<string> dictionary;
    vector<long> indice;
    std::vector<string>::iterator it;
    
    // Preparing output file 
    string file_name_dic = dset.set_loc+dset.set_name+".dic"; 
    std::ofstream myFile(file_name_dic);  
    // Running through data  
    for(int i=0; i < file.size();i++){
        it = std::find (dictionary.begin(), dictionary.end(), file[i]);
        if (it != dictionary.end()){
            indice.push_back(it - dictionary.begin());
        }//if
        else{
            indice.push_back(dictionary.size());
            dictionary.push_back(file[i]);
        }//else
    }//for
    for (int i=0; i<dictionary.size(); i++){
        myFile << dictionary[i] << ";";
    }//for
    myFile <<endl;
    for (int i=0; i<indice.size(); i++){
        myFile << indice[i] << ";";
    }//for
    myFile.close();
}//void dic_encoding_string

// --- Dictionary decoding --- 
void dic_decoding_string(string filecom_name){
    cout << "Decoding dictionary encoded file. \n";
    ifstream file_com;
    file_com.open(filecom_name);
    string line1,line2;
    vector<string> dictionary;
    vector<int> indice;
    std::string delimiter = ";";
    size_t pos = 0;
    getline(file_com,line1);
    std::string element;
    while ((pos = line1.find(delimiter)) != std::string::npos){
        element = line1.substr(0,pos);
        line1.erase(0,pos+delimiter.length());
        dictionary.push_back(element);
    }//while
    getline(file_com, line2);
    int count = 0;    
    while (((pos = line2.find(delimiter)) != std::string::npos) && (count<10)){
        count++;        
        int index = std::stoi(line2.substr(0,pos));
        line2.erase(0,pos+delimiter.length());
        indice.push_back(index);
    }//while
    file_com.close();
    cout << "\nDecoded data: \n";
    for(int i=0; i < 10;i++){
        cout << dictionary[indice[i]] << endl;
    }
    cout << endl;
}//void dic_decoding

// --- Frame of reference encoding --- 
void for_encoding(data_set dset){
  cout << "Applying frame of reference encoding. \n";
  // Calculate reference number
  int sum = 0;
	int boundary = 50;
	for (int i = 0; i < boundary; i++ ) {
		sum += dset.data_int.at(i);
	}
	int ref_number = sum / boundary;

	cout << ref_number << "\n";

	// Initialise encoded array.
	std::vector<int> encoded_data;
	int length = dset.data_int.size();

	encoded_data.push_back(ref_number); // Added this line so the first element of the array is the ref_number

	// Compute encoded values.
	for (int i = 0; i < length; i++) { // Start at i = 1 because first element is ref_number
		encoded_data.push_back(dset.data_int.at(i) - ref_number);
		if (i < 10) {
			cout << dset.data_int.at(i) << " " << encoded_data[i+1] << "\n";
		}
	}

  // Write encoded data to csv
  string file_name_for = dset.set_name+".for";
	cout << "Saving output to: \n";
  cout << file_name_for << "\n";
  std::ofstream myFile(dset.set_loc+file_name_for);
  for(int i = 0; i < encoded_data.size(); ++i)
  {
    int number = encoded_data[i];
		//cout << number << "\n";
    myFile << number;
    myFile << "\n";
  } // for

  // Close the file
    myFile.close();
} // void for_encoding

// --- Frame of reference decoding --- 
void for_decoding(data_set dset) {
	// Don't print all values but only the first 50 values.
	int boundary = 10;
	
	cout << "\nDecoded data: \n";

	int ref_number = dset.data_int.at(0);
	//cout << ref_number << "\n";

	for(int i = 1; i < boundary; i++) {
		cout << dset.data_int.at(i) + ref_number << endl;
		//cout << dset.data_int.at(i) << " ";	
	}//for
	cout << "\n";
}//void for_decoding

// --- Differential encoding --- 
void dif_encoding(data_set dset){
  cout << "Applying differential encoding. \n";

	// Initialise encoded array.
	std::vector<int> encoded_data;
	int length = dset.data_int.size();

	encoded_data.push_back(dset.data_int.at(0)); // First element is the same is normal array.

	// Compute encoded values.
	for (int i = 1; i < length; i++) { 
		encoded_data.push_back(dset.data_int.at(i) - dset.data_int.at(i-1)); // Compute difference.
		if (i < 10) {
      // Print values to see if it works as intended.
			//cout << dset.data_int.at(i) << " " << encoded_data[i] << "\n"; 
		}//if
	}//for 

  // Write encoded data to csv
  string file_name_for = dset.set_name+".dif";
	cout << "Saving output to: \n";
  cout << file_name_for << "\n";
  std::ofstream myFile(dset.set_loc+file_name_for);
  for(int i = 0; i < encoded_data.size(); ++i)
  {
    int number = encoded_data[i];
    myFile << number;
    myFile << "\n";
  } // for
    myFile.close();
} // void dif_encoding

// --- Differential decoding --- 
void dif_decoding(data_set dset) {
	int boundary = 10;
	cout << "\nDecoded data: \n";
	cout << dset.data_int.at(0) << endl;
	int sum = dset.data_int.at(0);

	for(int i = 1; i < boundary; i++) {
		sum += dset.data_int.at(i);
		cout << sum << endl;
	}//for
	cout << "\n";
}//void dif_decoding

/*
void bve_encoding(data_set dset){
  cout << "Applying bit-vector encoding. \n";
  int length = dset.data_int.size();  

  std:vector<std::pair<std:string, bitset<length>>> result;
  
  cout << result;

  //for (int i = 0; i < length; i++){
  //
      
  //}   

}
*/

int main(){

  string working_directory = "/home/vbuchem/Documents/ADM_asg1/";
  string data_directory = "/data1/vbuchem/ADM-2019-Assignment-1-data-T-SF-1/";
  string en = "en";


  cout << "Please enter the name of the file: \n";
  //cin << fname;
  cout << "Would you like to decode (\"de\") or encode (\"en\") the file? \n";
  //cin << en_de;
  cout << "What is the data type of the file? \n";
  //cin << dtype;
  
  //string fname = "l_shipmode-string.dic";  
  string fname = "l_tax-int64.csv"; 
  string en_de = "en";
  string dtype = "int";
  



  if (en_de.compare(en)==0){ // The encoding algorithm
    string csv = ".csv";
    data_set dset;
    dset.set_loc = data_directory;
    dset.set_name = fname.substr(0,fname.size()-4);
    dset.set_type = dtype;
    dset.read_data(csv);
    
    //Dictionary encoding
    dic_encoding(dset);

    //Run-length encoding
    rl_encoding(dset);

    // Exception for string data
    if (dtype.compare(str)!=0){

      //Bit vector encoding 
      //bve_encoding(dset);
      
      //Frame of reference encoding
      //for_encoding(dset);
      
      //Differential encoding
      //dif_encoding(dset);

    }//if 
  }//if 

  else { // The decoding algorithm

    // Defining the different encoding types
    string ct_bin = ".bin";
    string ct_rle = ".rle";
    string ct_dic = ".dic";
    string ct_for = ".for";
    string ct_dif = ".dif";
    
    string ct = fname.substr(fname.size()-4,4);

    if (ct.compare(ct_bin) == 0){
      cout << "Detected .bin format." << endl;
    }

    else if (ct.compare(ct_rle) == 0){
      cout << "Detected .rle format." << endl;
      rl_decoding(data_directory+fname);
    }
    
    else if (ct.compare(ct_dic) == 0){
      cout << "Detected .dic format." << endl;
      if (dtype.compare(str)==0){dic_decoding_string(data_directory+fname);}
      //else {dic_decoding_string(data_directory+fname)}    
    }
    
    else if (ct.compare(ct_for) == 0){
      cout << "Detected .for format." << endl;
      data_set dset;
		  dset.set_loc = data_directory;
		  dset.set_name = fname.substr(0,fname.size()-4);
		  dset.set_type = dtype;
		  dset.read_data(".for");
			for_decoding(dset);
    }

    else if (ct.compare(ct_dif) == 0){
      cout << "Detected .dif format." << endl;
      data_set dset;
      dset.set_loc = data_directory;
		  dset.set_name = fname.substr(0,fname.size()-4);
		  dset.set_type = dtype;
		  dset.read_data(".dif");
			dif_decoding(dset);
    }
  }
}
