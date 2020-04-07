/**
 *  networkWriter.h 
 *
 *  Writes a file that defines a network, by calling functions
 *  in the abstractNetwork ADT. The file it writes can be read
 *  by networkBuilder.c
 *
 *  Created by Sally Goldin, 15 March 2016 for CPE 113 (Lab 9-2)
 */

/* Main function to open and write the file.
 *    outputfile    Name of file to create.
 * Returns 1 if everything is fine, 0 if there is 
 * either a file error or an error accessing the network information.
 */
int writeNetwork(char* outputfile);

