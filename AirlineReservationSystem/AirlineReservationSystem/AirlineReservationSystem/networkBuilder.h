/**
 *  networkBuilder.h 
 *
 *  Function declaration for networkBuilder.c 
 *  Reads a file that defines a network, and builds that network
 *  by calling functions in the abstractNetwork ADT.
 *
 *  Created by Sally Goldin, 3 February 2012 for CPE 113
 */
#ifndef NETWORKBUILDER_H
#define NETWORKBUILDER_H
/*********************************************************************
 The network definition file is a text file. Its format is as follows.

  Line 1              NumVertices  bDirected     e.g.    "100  1"

  Following lines are either VERTEX lines or EDGE lines
  A VERTEX line must have the form

      VERTEX keyvalue              e.g. "VERTEX A"

  An EDGE line must have the form 

      EDGE key1 key2 weight        e.g. "EDGE A C 13"

  VERTEX and EDGE lines can be in any order, but both keys referenced
  in an EDGE line must have been mentioned in VERTEX lines earlier in
  the file. That is, both vertices must exist before they can be linked
  with an edge.

  (There should not be any quotation marks around the commands.)

  If the format of the file is bad, the readNetworkDefinition function returns
  an error status value. However, if the format is okay but there are semantic
  errors (e.g. trying to define a vertex or edge more than once, trying to
  create an edge before its vertices are defined, trying to define an edge
  more than once), the function simply prints an error message but then
  ignores the bad line.

 **************************************************************************
 */

/* Opens and reads a network definition file that is supposed to follow
 * the structure explained above. If 'bVerbose' is true, displays messages
 * as it processes the file, explaining what it is doing.
 * Arguments
 *    filename    -   filename to read, with path
 *    bVerbose    -   if non-zero, print messages as processing goes on
 *                    if zero, prints only error messages
 * Returns 1 if successful, -1 if any error occurs.
 */  
int readNetworkDefinition(char* filename, int bVerbose);

#endif
