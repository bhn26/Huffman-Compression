#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "HCTree.hpp"

using namespace std;

int main( int argc, char** argv )
{
  //Creates a vector to store values in
  vector<int> freqs(256,0);
  char symbol;
  int num = 0;
  int uSym = 0;

  //Creates a new input stream to read from file
  ifstream input;
  
  //Opens the compressed file
  input.open(argv[1], ios::binary);
  cout << "Reading header from file \"" << argv[1] << "... done." << endl;

  //Gets the amount of unique symbols
  input.read((char*)&uSym, sizeof(int));

  cout << "Uncompressed file will have " << uSym << " unique symbols ";

  //Reads the file to get the necessary info and fills up the freqs
  for(int index = 0; index < uSym; index++)
  {
    input.read((char*)&symbol, sizeof(char));
    input.read((char*)&num, sizeof(int));
    freqs[(unsigned char)symbol] = num;
  }

  //Builds a new Huffman tree with restored freqs
  HCTree huffTree;
  huffTree.build(freqs);

  //Creates an output stream using the second argument
  ofstream output;
  output.open(argv[2], ios::binary);
  
  //Creates a new input stream using the input fill
  BitInputStream inStream = BitInputStream(input);

  //Gets the size of the file
  int fSize = 0;
  for(size_t index = 0; index < freqs.size(); index++ )
  {
    fSize += freqs[index];
  }

  cout << "and size " << fSize << " bytes." << endl;
  cout << "Building Huffman code tree... done." << endl;
  cout << "Writing to file \"" << argv[2] << "\"... done." << endl;

  //Decodes the tree to it's original form
  while( fSize > 0 )
  {
    output.put((unsigned char)huffTree.decode(inStream));
    fSize--;
  }

  //Closes the files
  input.close();
  output.close();

  return 0;
}
