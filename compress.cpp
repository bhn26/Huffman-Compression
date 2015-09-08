#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "HCTree.hpp"

int constructHeader(std::ostream &out, std::vector<int> freqs)
{
  int uSym = 0;
  for(size_t index = 0; index < freqs.size(); index++) 
  {
    if (freqs[index]) 
    {
      uSym++;
    }
  }
  
  out.write((char*)&uSym, sizeof(int));

  // Write the count of each uSym and symbols
  for(size_t index2 = 0; index2 < freqs.size(); index2++ )
  {
    if(freqs[index2])
    {
      out.write((char*)&index2, sizeof(char));
      out.write((char*)&freqs[index2], sizeof(int));
    }
  }
  return uSym;
}

int main(int argc, char* argv[])
{
  //Checks if the amount of arguments are correct, if not, prints error message
  if(argc != 3)
  {
    std::cout <<"./compress called with incorrect arguments." << std::endl;
    std::cout << "Usage: ./refcompress infile outfile" << std::endl;
  }

  vector<int> freqs(256,0);

  //Checks and initializes input file, then opens it
  std::ifstream input(argv[1], std::ios::binary);
 
  std::string buffer((std::istreambuf_iterator<char>(input)),
  		     (std::istreambuf_iterator<char>()));
  
  int uSym = 0;

  //Creates a file if one isn't present
  if (!buffer.size()) 
  {
    std::ofstream ofs(argv[2], std::ios::binary);
    std::cout << "Found " << uSym << " unique symbols in input file of size ";
    std::cout << buffer.size() << " bytes." << std::endl;
    std::cout << "Building Huffman code tree... done." << std::endl;
    std::cout << "Writing to file \"" << argv[2] << "\"... done." << std::endl;
    ofs.close();
    input.close();
    freqs.clear();
    freqs.shrink_to_fit();
    exit(0);
  }

  //Succesful reading
  std::cout << "Reading from file \"" << argv[1] << "\"... done." << std::endl;

  for (size_t i = 0; i < buffer.size(); ++i) 
  {
    byte b = buffer[i];
    ++freqs[b];
  }

  //Consrtucts the Huffman tree with the given freqs
  HCTree huffTree;
  huffTree.build(freqs);

  //Creates an output file and opens it
  std::ofstream output(argv[2], std::ios::binary);

  //Creates new output stream
  BitOutputStream stream(output);

  //Gets the amount of unique characters
  uSym = constructHeader(output, freqs);

  //Encodes the tree
  for (size_t index = 0; index < buffer.size(); index++) 
  {
    huffTree.encode(buffer[index], stream);
  }
  
  int iSize = buffer.size();

  //Calculates the size of the output file
  int oSize = output.tellp();
  oSize++;

  long ratio = oSize/iSize;

  std::cout << "Found " << uSym << " unique symbols in input file of size ";
  std::cout << iSize << " bytes." << std::endl;
  std::cout << "Building Huffman code tree... done." << std::endl;
  std::cout << "Writing to file \"" << argv[2] << "\"... done." << std::endl;
  std::cout << "Output file has size " << oSize << " bytes." << std::endl;
  std::cout << "Compression ratio: " << ratio << std::endl;

  return 0;
}
