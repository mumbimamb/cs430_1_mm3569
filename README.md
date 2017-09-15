Overview
====================
A converter for PPM files in P3 or P6 format. It prints an error message if an error occurs, such as in user input or in the program itself.

Usage
====================
### In order to use the program and convert a P3 or P6 image to a P3 image, you must input:

"ppmrw 3 input.ppm output.ppm"

where "input.ppm" is the input file and "output.ppm" is the output file; "ppmrw" refers to the program and "3" establishes which format you would like the image to be converted to, P3.

### In order to convert a P3 or P6 to a P6 image, you must input:

"ppmrw 6 input.ppm output.ppm"

The terms have the same meaning as the p3 format conversion, however, this time "6" designates a conversion to the P6 format.

Purpose
====================
The purpose of the ppmrw converter is to convert PPM images from P3 or P6 to P3 or P6 format. If the file is already in P3 format and is prompted to be converted to P3 format, the output file will be a copy of the input file with the original file's comments removed if present. The same action will occur if a P6 image is asked to be converted to a P6 image.

Known Issues
====================
Does not read PPM P3 images. Does not write to the output files, but does read P6 files. As of now, it does read the headers of PPM files.

Authors
====================
Mumbi Macheho-Mbuthia <mm3569@nau.edu OR mumbimamb@gmail.com>
