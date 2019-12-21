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
      //cout << "Size of data-set: " << data_int.size() << "\n";
    } // if
    return data_int;
  } // vector int_reader

  std::vector<string> string_reader(string name){
    string line;
    ifstream myFile(name);
    if (myFile.is_open()){
      while(!myFile.eof()){
        getline(myFile,line);
        data_string.push_back(line);
      } // while
      //cout << "Size of data-set: " << data_string.size() << "\n";
    } // if
    return data_string;
  } // vector string_reader

  void read_data(string filetype){
    cout << "Reading data from: " << set_loc+set_name+".csv" << "\n";
    //if (set_type.compare(str)==0){
    string_reader(set_loc+set_name+filetype);
    //}//if
    //else{
    int_reader(set_loc+set_name+filetype);
    //} //else
  }// void read_data_int

};// class data_set

/*
------------- ENCODING AND DECODING ALGORITHMS -------------
In the lines below each encoding/decoding method as an associated function.
Each encoding function accepts a class object called 'data_set' and then encodes it and saves it.
Every decoding function reads the given file itself, decodes it and writes a new unencoded file.
*/

// --- Bit vector encoding --- 
void bve_encoding(data_set dset){
    cout << "\nApplying bit vector encoding. \n";
    // Passing data to new vector
    std::vector<int> file = dset.data_int;
    vector<int> IDs;
    vector<long> indice;

    // Preparing output file
    string file_name_rle = dset.set_loc+dset.set_name+".bin";
    cout << "Saving output to: ";
    cout << dset.set_name+".bin" << "\n"; 
    std::ofstream myFile(file_name_rle);
    myFile << file.size() << endl;
  
    IDs = file;
    vector<int>::iterator ip;
    std::sort(IDs.begin(),IDs.end());
    ip = std::unique(IDs.begin(), IDs.end());
    IDs.resize(std::distance(IDs.begin(), ip));
    for (ip = IDs.begin(); ip != IDs.end(); ++ip){
          myFile << *ip << ";";
    }//for
    myFile << endl;
    for (int i=0; i< IDs.size();i++){
        for(int j=0; j<file.size(); j++){
            if( file[j] == IDs[i]){
                myFile << j << ";";// save the bit vector as a sparse matrix.
                //Only save the position of zeros
            }//if
        }//for
        myFile << endl;
    }//for    
    //cout << "Compressed" << endl;
}//void bve_encoding

// --- Bit vector decoding --- 
void bin_decoding(string filecom_name){
    cout << "\nDecoding bit-vector encoded file. \n";
    ifstream file_com;
    file_com.open(filecom_name);
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

    while ((pos = l2_IDs.find(delimiter)) != std::string::npos){
        element = l2_IDs.substr(0,pos);
        l2_IDs.erase(0,pos+delimiter.length());
        IDs.push_back(stoi(element));
    }//while

    for(int i=0;i<IDs.size();i++){
        string sparse_line;
        getline(file_com, sparse_line);
        while ((pos = sparse_line.find(delimiter)) != std::string::npos){
            element = sparse_line.substr(0,pos);
            sparse_line.erase(0,pos+delimiter.length());
            file_recover[stoi(element)] = IDs[i];
        }//while
    }//for

    cout << "\nDecoded data: \n";
    for(int i =0; i<10; i++){
        cout << file_recover[i] << endl;
    }//for
    cout << endl;
}//void bve_decoding

// --- Run-length encoding ---
void rl_encoding(data_set dset){
    cout << "\nApplying run-length encoding. \n";
    // Passing data to new vector
    std::vector<string> file = dset.data_string;
    // Creating chunk object
    struct RL_chunk {
      string value ;
      int start_pos = 0, run_length = 1;
    } rl_chunk;
    // Preparing output file
    string file_name_rle = dset.set_loc+dset.set_name+".rle";
    cout << "Saving output to: ";
    cout << dset.set_name+".rle" << "\n"; 
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
    cout << "\nDecoding run-length encoded file. \n";
    string line;
    ifstream file_com;
    file_com.open(filecom_name);
    cout << "\nDecoded data: \n";
    for(int i=0; i < 10; i){
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
      for(int j=0; j < run_length; j++){
        cout << value << endl;
        i++;  
      }//while
    }//for
    cout << endl;
    file_com.close();
}//void rl_decoding

// --- Dictionary encoding ---
void dic_encoding(data_set dset){
    cout << "\nApplying dictionary encoding. \n";
    // Passing data to new vector
    std::vector<string> file = dset.data_string;
    // Preparing variables    
    std::vector<string> dictionary;
    vector<long> indice;
    std::vector<string>::iterator it;
    
    // Preparing output file 
    string file_name_dic = dset.set_loc+dset.set_name+".dic"; 
    cout << "Saving output to: ";
    cout << dset.set_name+".dic" << "\n";
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
        //cout << dictionary[i] << endl;
    }//for
    myFile <<endl;
    for (int i=0; i<indice.size(); i++){
        myFile << indice[i] << ";";
        //cout << indice[i] << endl;
    }//for
    myFile.close();
}//void dic_encoding_string

// --- Dictionary decoding --- 
void dic_decoding_string(string filecom_name){
    cout << "\nDecoding dictionary encoded file. \n";
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
  cout << "\nApplying frame of reference encoding. \n";
  // Calculate reference number
  int sum = 0;
  int boundary = 50;
  for (int i = 0; i < boundary; i++ ) {
          sum += dset.data_int.at(i);
  }
  int ref_number = sum / boundary;

  //cout << ref_number << "\n";
  // Threshold for number of bits.
  int max_bits = 4;
  int escape_value = max_bits+1;

  // Initialise encoded array.
  std::vector<int> encoded_data;
  int length = dset.data_int.size();

  encoded_data.push_back(ref_number); // Added this line so the first element of the array is the ref_number
  encoded_data.push_back(max_bits);

  // Compute encoded values.
  for (int i = 0; i < length; i++) { // Start at i = 1 because first element is ref_number
    int dif = dset.data_int.at(i) - ref_number;
    if (dif <= max_bits ) {
      encoded_data.push_back(dif);
    }
    else {
      encoded_data.push_back(escape_value);
      encoded_data.push_back(dset.data_int.at(i));
    }
    if (i < 20) {
      //cout << dset.data_int.at(i) << " " << encoded_data[i+2] << "\n";
    }
  }

  // Write encoded data to csv
  string file_name_for = dset.set_name+".for";
	cout << "Saving output to: ";
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
  cout << "\nDecoding frame of reference encoded file. \n";
	// Don't print all values but only the first 50 values.
	int boundary = 10;
	
	cout << "\nDecoded data: \n";

	int ref_number = dset.data_int.at(0);
  int max_bits = dset.data_int.at(1);
  int escape_value = max_bits+1;

	for(int i = 2; i < boundary+2; i++) {
    int cur_val = dset.data_int.at(i);
    if (cur_val == escape_value) {
      cout << dset.data_int.at(i+1) << endl;
      i++;
    }//if 
    else {
		  cout << dset.data_int.at(i) + ref_number << endl;
		//cout << dset.data_int.at(i) << " ";	
	  }//else
  }//for
	cout << "\n";
}//void for_decoding

// --- Differential encoding --- 
void dif_encoding(data_set dset){
  cout << "\nApplying differential encoding. \n";

	// Initialise encoded array.
	std::vector<int> encoded_data;
	int length = dset.data_int.size();

	 // Setting a maximum bit size.
  int max_bits = 6;
  int escape_value = max_bits + 1;

  encoded_data.push_back(max_bits);
  encoded_data.push_back(dset.data_int.at(0)); // First element is the same is normal array.
  //cout << dset.data_int.at(0) << " " << encoded_data[0] << "\n";
	// Compute encoded values.
	for (int i = 1; i < length; i++) { 
    int dif = dset.data_int.at(i) - dset.data_int.at(i-1);
    if (dif > max_bits || dif < max_bits*-1) {
      encoded_data.push_back(escape_value);
      encoded_data.push_back(dset.data_int.at(i));
    }//if 

    else {
      encoded_data.push_back(dif); // Compute difference.
    }//else
		
    if (i < 10) {
      //cout << dset.data_int.at(i) << " " << encoded_data[i] << "\n"; //Print values to see if it works as intended.
		}//if
	}//for 

  // Write encoded data to csv
  string file_name_for = dset.set_name+".dif";
	cout << "Saving output to: ";
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
  cout << "\nDecoding differential encoded file. \n";
	int boundary = 10;
	cout << "\nDecoded data: \n";

  int max_bits = dset.data_int.at(0);
  int escape_value = max_bits + 1;

	cout << dset.data_int.at(1) << "\n";
	int sum = dset.data_int.at(1);
  for(int i = 2; i < boundary+1; i++) {
    int cur_val = dset.data_int.at(i);
		//cout << cur_val << endl;
    if (cur_val == 7) {
      i++;
      sum = dset.data_int.at(i);
    }//if 
    else {
      sum += dset.data_int.at(i);
    }//else
    cout << sum << "\n";
	}//for
	cout << "\n";
}//void dif_decoding

/*
------------- MAIN FUNCTION -------------
Only varibale that has to be altered for a different computer is the data_directory. 
*/

int main(){

  string data_directory = "/data1/vbuchem/ADM-2019-Assignment-1-data-T-SF-1/";
  string en = "en";
  
  string fname;
  string en_de; 
  string dtype;

  cout << "Please enter the name of the file: ";
  cin >> fname;
  cout << "\nEncode (\"en\") or decode (\"de\"): ";
  cin >> en_de;
  cout << "\nData type: ";
  cin >> dtype;
  cout << endl;

  //string fname = "l_shipmode-string.csv";  
  //string fname = "l_tax-int64.dif"; 
  //string en_de = "de";
  //string dtype = "int64";
  

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
      bve_encoding(dset);
      
      //Frame of reference encoding
      for_encoding(dset);
      
      //Differential encoding
      dif_encoding(dset);

    }//if 
  
  cout << "\nDone encoding for all (relevant) methods.\n";

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
      bin_decoding(data_directory+fname);
    }//if

    else if (ct.compare(ct_rle) == 0){
      cout << "Detected .rle format." << endl;
      rl_decoding(data_directory+fname);
    }//else if
    
    else if (ct.compare(ct_dic) == 0){
      cout << "Detected .dic format." << endl;
      dic_decoding_string(data_directory+fname);
    }//else if
    
    else if (ct.compare(ct_for) == 0){
      cout << "Detected .for format." << endl;
      data_set dset;
		  dset.set_loc = data_directory;
		  dset.set_name = fname.substr(0,fname.size()-4);
		  dset.set_type = dtype;
		  dset.read_data(".for");
			for_decoding(dset);
    }//else if

    else if (ct.compare(ct_dif) == 0){
      cout << "Detected .dif format." << endl;
      data_set dset;
      dset.set_loc = data_directory;
		  dset.set_name = fname.substr(0,fname.size()-4);
		  dset.set_type = dtype;
		  dset.read_data(".dif");
			dif_decoding(dset);
    }//else if
  }//else
}//int main()
