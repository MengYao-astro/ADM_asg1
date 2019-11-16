#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
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

std::vector<int> for_encoding(std::vector<int> array,int ref_number) {
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

void output_decoded_values(std::vector<int> array,int ref_number) {
	// Don't print all values but only the first 50 values.
	int boundary = 50;
	
	cout << "\nDecoded array: \n";

	for(int i = 0; i < boundary; i++) {
		cout << array[i] + ref_number << " ";
	}

	cout << "\n\n";
}

int main() {
	// Input settings.
	string input_dir = "/home/auke/Desktop/ADM/assignments/ass_1/data/ADM-2019-Assignment-1-data-T-SF-1/int/";
	string txt_file_path = input_dir + "int_list.txt";
	int num_files = 14; // Number of files in the /int folder.
	string input_fname[num_files]; // Stores the filenames in a string array.
	string input_path = input_dir + input_fname[0];

	ifstream file(txt_file_path);

	if (file.is_open()) {
		for(int i = 0; i < num_files; ++i) {
			file >> input_fname[i];
		}
	}

	// Output settings.
	string output_dir = "/home/auke/Desktop/ADM/assignments/ass_1/data/output/";
	string output_path = output_dir + "test_data.csv";
	string output_encoded_path = output_dir + "encoded_data.csv";
	   
	// Make test vector.
	std::vector<int> test_data{4,9,10,9,10,7,0,6,10,6,1,4,10,3,2,7,8,8,7,8,10,3,8,6,4,5,2,9,9,5,4,9,2,5,9,0,8,2,2,6,6,6,8,3,9,9,5,5,4,9,8,6,7,1,6,5,3,0,9,0,4,9,9,3,8,5,2,5,2,4,7,3,5,9,1,8,9,9,7,5,3,6,3,1,9,6,9,9,0,0,8,4,10,1,0,2,6,6,0,5};
	string Col1_name = "Column 1";

	// Optional linear shift.
	for(int i = 0; i < test_data.size(); i++) {
		test_data[i] += 10;
	}

	// Write the test vector to CSV
	write_csv(output_path, Col1_name, test_data);

	// Compute a reference number.
	int ref_number = reference_number(test_data);

	// Encode the test vector.
	std::vector<int> encoded_data = for_encoding(test_data,ref_number);

	// Write the encoded vector to CSV
	write_csv(output_encoded_path, Col1_name, encoded_data);

	// Output decoded values in terminal.
	output_decoded_values(encoded_data,ref_number);
	
	return 0;
}

// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
