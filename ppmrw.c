// Libraries to Include
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h" // contains 'isspace method'

// Function Declarations
void readInputFile(int ppm_format, char* input_file_name, char* output_file_name);
void convertToP3(char* buffer, char* p3_r, char* p3_g, char* p3_b, char* p3_a);
void writeHeaderToOutputFile(char* output_file_name,  char ppm_format, int width, int height, int max_color);
void writeDataToOutputFile(char* output_file_name, char* p3);

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
  int ppm_format = atoi(argv[1]); // the ppm format given in the arguments

  //
  /* End of Necessary Variable Declartions */
  //

  //
  /* Start of call to functions to read and write data */
  //
  // Call to method to read in data from input file
  printf("\nReading from the input file, %s, specified in the arguments.\n", argv[2]);

  readInputFile(ppm_format, argv[2], argv[3]);
  // Call to appropriate converter

  // Call to method to write data into output file
  printf("\nNow writing the data to the specified output file, %s.\n", argv[3]);
  //
  /* End of functions to read and write data */
  //

  // End procedures for program
  printf("\nThe conversion has finished.\n");
}

/*
Reads the file given in the arguments as the input.
All file handling occurs in the function in order to keep everything cohesive.
*/
void readInputFile(int ppm_format, char* input_file_name, char* output_file_name){
  FILE* input_file = fopen(input_file_name, "r");

  // get length of input file
  fseek(input_file, 0, SEEK_END);
  long file_length = ftell(input_file);

  ///
  // Reading header information
  ///

  // find the magic number first, should be the first thing in file
  int magic_num;
  fseek(input_file, 0, SEEK_SET); // set pointer to beginning of file
  char f_result[250];
  fscanf(input_file, "%s", f_result);
  magic_num = f_result[1];

  printf("%d", ppm_format);

  // find the width, height, and max color value, in the order stated
  int input_width = -1;
  int input_height = -1;
  int input_max_color = -1;
  char pending_input[15]; // where info sits while sifting through header, character by character
  pending_input[0] = 'N'; // sign that no input is being gathered at the moment
  int pending_index = 0;

  int loop_var = 80;
  while (loop_var >= 0) {
    f_result[0] = fgetc(input_file); // grabs the first

    if (f_result[0] == '#') {
      fgets(f_result, 250, input_file); // check if comment longer
    }
    else if (isspace(f_result[0])) {
      if (pending_input[0] != 'N') {
        if (input_width == -1) {
          input_width = atoi(pending_input);
        }
        else if (input_height == -1) {
          input_height = atoi(pending_input);
        }
        else if (input_max_color == -1) {
          input_max_color = atoi(pending_input);
          break; // break out of loop
        }
        // reset pending input array
        for (int i = 0; i < pending_index; i = i + 1) {
          pending_input[i] = ' ';
        }
        pending_index = 0; // reset value to ready for next input with new index
        pending_input[0] = 'N'; // reset value to signify that no input being gathered at moment
      }
    }
    else {
      pending_input[pending_index] = f_result[0];
      pending_index = pending_index + 1;
    }
    loop_var = loop_var - 1;
  }

  writeHeaderToOutputFile(output_file_name, ppm_format, input_width, input_height, input_max_color);

  ///
  // Reading data if the magic number is P3
  ///
  if (magic_num == '3') {
    fclose(input_file); // close the input file
    FILE *p3_input = fopen(input_file_name, "r"); // reopen file

    fclose(p3_input); // close the input file after reading it
  }

  ///
  // Reading data if the magic number is P6
  ///
  if (ppm_format == 6 || ppm_format == '6') {
    fclose(input_file); // close file so you can read it in binary

    FILE* p6_input = fopen(input_file_name, "rb"); // open t

    unsigned char buffer[8];
    unsigned char p3[3*input_width*input_height];

    // read one line of info
    for(int i = 0; i < ((input_width * input_height)); i++) {
      fread(buffer, 3, 1, p6_input);
      printf("\n%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);

      // convert to p3

      // write to file
      writeDataToOutputFile(output_file_name, buffer);

      // skip a character
      fgetc(p6_input);
    }
    fclose(p6_input);
  }

  // if magic num not equal to 3 or 6, return null to signify error
}

/*
Is only called if the data given is in P3 format. If the input file is already in P6 format then it wil be directly written to
the output file via the 'writeOutputFile' method.
*/
void convertToP6(int ppm_format){

}

/*
Writes header data into output file.
*/
void writeHeaderToOutputFile(char* output_file_name, char ppm_format, int width, int height, int max_color) {
  FILE* output_file = fopen(output_file_name, "w");

  fputs("P", output_file);
  fprintf(output_file, "%d", ppm_format);
  fputs(" ", output_file);
  fprintf(output_file, "%d", width);
  fputs(" ", output_file);
  fprintf(output_file, "%d", height);
  fputs(" ", output_file);
  fprintf(output_file, "%d", max_color);
  fputs("\n", output_file);

  fclose(output_file);
}

/*
This function is used to write the data to the output file and is passed the output file name from the arguments.
All file handling occurs in the function in order to keep things cohesive.
*/
void writeDataToOutputFile(char* output_file_name, char* p3){
  FILE* output_file = fopen(output_file_name, "a"); // should erase the contents of the output file or make new one if doesn't exist

  fprintf(output_file, "%d %d %d", p3[0], p3[1], p3[2]);

  fputs(" ", output_file);

  fclose(output_file); // close the file
}
