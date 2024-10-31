#include <fstream>
#include <iostream>
#include <cstdlib> //for exit()
using namespace std;
const int MAX_SIZE = 100;


//Input: (1) Array storing data retrieved from the file (i.e., 
//instream)
// (2) input file stream object
//Output: Size of array. Note: you need to use this parameter to 
//control the array size.
int readfile(int inputArray[], ifstream& instream);

//sorts the values from the two arrays and writes them to outputArray[]; returns the size of outputArray[]
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]);

//writes the outputArray[] to a new file
void writefile(int outputArray[], int outputArray_size); //void


//main method
int main()
{   
    //declare variables for I/O, arrays, and file names
    ifstream inStream1;
    ifstream inStream2;
    int iArray1[MAX_SIZE];
    int iArray1_size;
    int iArray2[MAX_SIZE];
    int iArray2_size;
    int outputArray[2*MAX_SIZE];
    int outputArray_size;
    string filename;

    cout << "*** Welcome to Brandon's sorting program ***" << endl;
    //For the first input file
    cout << "Enter the first input file name: ";
    cin >> filename;
    

    // Pass the file name as an array of chars to open()
    // inStream1.open(filename);
    inStream1.open((char*)filename.c_str());

    // make sure file can be opened
    if (inStream1.fail()) {
        cout << "Input file opening failed." << endl;
        exit(1);
        //leave the program if file can't be opened
    }
    
    //read the file and store the values in iArray1[]
    iArray1_size = readfile(iArray1, inStream1);
    inStream1.close( );
    cout << "The list of " << iArray1_size << " numbers in file " << filename << " is:" << endl;

    //print the values in iArray1[]
    for (int i = 0; i < iArray1_size; i++) {
        cout << iArray1[i] << endl;
    }


    //For the second input file
    cout << "\n";
    cout << "Enter the second input file name: ";
    cin >> filename;


    inStream2.open((char*)filename.c_str());
    // make sure file can be opened
    if (inStream2.fail()) {
        cout << "Input file opening failed." << endl;
        exit(2);
        //leave the program if file can't be opened
    }

    //read the file and store the values in iArray2[]
    iArray2_size = readfile(iArray2, inStream2);
    inStream2.close( );
    cout << "The list of " << iArray2_size << " numbers in file " << filename << " is:" << endl;
    
    //print the values in iArray2[]
    for (int i = 0; i < iArray2_size; i++) {
        cout << iArray2[i] << endl;
    }
    
    cout << endl;

    //sort the values from iArray1[] and iArray2[] and add them to outputArray[]
    //also, print the values in outputArray[]
    outputArray_size = sort(iArray1, iArray1_size, iArray2, iArray2_size, outputArray);
    
    //write the outputArray[] to a new file
    writefile(outputArray, outputArray_size);
    cout << "*** Goodbye. ***" << endl;
    return 0;


}



//helper methods

//reads the file, adds the values to the array, and returns the size of the array
int readfile(int inputArray[], ifstream& inStream){
    int index;
    index = 0;
    inStream >> inputArray[index];
    while (! inStream.eof()) {
        index++;
        inStream >> inputArray[index];
    } 
 
    return index;
}

//sorts the values from the two arrays and adds them in order to the output array
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]){
    int p1 = 0; //for inputArray1[]
    int p2 = 0; //for inputArray2[]
    //Two pointer approach works because both arrays are sorted; O(N) time complexity

    cout << "The sorted list of " << inputArray1_size + inputArray2_size << " numbers is:";

    for (int i = 0; i < inputArray1_size + inputArray2_size; i++) {
        //add the smaller value to the outputArray[]; if one is empty, add the other
        if (inputArray1[p1] < inputArray2[p2] || p2 == inputArray2_size) {
            outputArray[i] = inputArray1[p1];
            p1++;
        } else {
            outputArray[i] = inputArray2[p2];
            p2++;
        }

        //print the new value in outputArray[]
        cout << " " << outputArray[i];
    }
    cout << endl;

    //size of outputArray[]
    return inputArray1_size + inputArray2_size;
}


//writes the outputArray[] to a new file
void writefile(int outputArray[], int outputArray_size){
    ofstream outStream;
    string filename;

    //user inputs file name
    cout << "Enter the output file name: ";
    cin >> filename;

    //open the file and write the values to outputArray[]
    outStream.open((char*)filename.c_str());
    
    // make sure file can be opened
    if (!outStream) {
        cout << "Output file opening failed." << endl;
        exit(3);
    }

    for (int i = 0; i < outputArray_size; i++) {
        outStream << outputArray[i] << endl;
    }
    outStream.close();
    cout << "*** Please check the new file - " << filename << " ***" << endl;

}
