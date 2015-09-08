#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

class BitInputStream 
{
  private:
    char buffer;
    int nbits;
    istream& in;

  public:
    
    //Initializes the input stream
    BitInputStream(istream& in) : in(in) 
    {
      buffer = 0;
      nbits = 8;
    }

    //Fills in buffer if all bits have been read
    void fill() 
    {
      buffer = in.get();
      nbits = 0;
    }

    //Function that reads bits from the file
    int readBit();

};
#endif
