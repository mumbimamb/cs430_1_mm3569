// libraries to include for program
#include "stdio.h"
#include "stdlib.h"

// the main function of the program which runs when the program is called
int main (int argc, char* argv[]) {
  //
  /* Start of Error Handling */
  //
  // Check if right number of arguments
  if (argc != 4) {
    printf("\nYou have entered the wrong number of arguments.\nPlease refer to the README file for proper usage of the program.\n");
    return 1; // the program returns a nonzero number to indicate an error has occurred
  }
  // Check if the second argument is "3" or "6" to indicate the requested PPM format
  if ( atoi(argv[1]) != 3 && atoi(argv[1]) != 6)
  {
    printf("\nThe second argument you have given is not '3' or '6'.\nPlease refer to the README file for the proper usage of the program.\n");
    return 2; // the program returns a nonzero number to indicate an error has occurred
  }
  // Check if the input file can be read with a dummy FILE pointer
  FILE* dummy_file = fopen(argv[2], "r");
  if (dummy_file == NULL) {
    printf("\nThe third argument you have given for input is not a readable or existing file.\nPlease try again with an appropriate file.\n");
    return 3; // the program returns a nonzero number to indicate an error has occurred
  }
  else {
    fclose(dummy_file); // close the dummy file
  }
  //
  /* End of Error Handling */
  //

  //
  /* Start of Necessary Variable Declarations */
  //
  // Variables for errors
  int error_int = 0; // specifices if an error occured while running read and wrtie functions; if no errors it should be equal to 0
  char* error_message = "Blank"; // specifies an erorr message if an error reached during read and write functions
  // Variables for read and write functions
  int ppm_format = atoi(argv[1]);

  //
  /* End of Necessary Variable Declartions */
  //

  //
  /* Start of call to functions to read and write data */
  //
  // Call to method to read in data from input file
  printf("\nReading from the input file specified in the arguments.\n");

  // Call to method to write data into output file
  printf("\nNow writing the data to the specified output file.\n");
  //
  /* End of functions to read and write data */
  //

  // End procedures for program
  printf("\nThe conversion has finished.\n");
}

/*
The file handling occurs in the function
*/
void readInputFile(int ppm_format, char* input_file_name){

}

/*

*/
void convertToP3(int ppm_format){

}

/*
*/
void convertToP6(int ppm_format){

}

/*
This function is used to write the data to the output file.
Is passed the output file name from the arguments.
The file hadnling occurs in the function.
*/
void writeOutputFile(char* output_file_name){
FILE* output_file = fopen(output_file_name, "w"); // should erase the contents of the output file or make new one if doesn't exist

fclose(output_file);// close the file
}
