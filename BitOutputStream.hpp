#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <string>
#include <bitset>

class BitOutputStream
{
  public:
    //Constructor method
    BitOutputStream(std::ostream &out) : out(out)
    {
      count = 0;
    }

    //Default destructor
    ~BitOutputStream();

    /**
     * Takes in an int and runs through the check to sets the necessary
     * bits into byte. Also checks and flushes the count.
     */
    void writeBit(int bit);

    //Flushes out any bits and sets it to zero
    void flush();

    //Reference of the output stream
    std::ostream &out;

  private:
    //Used to check if the code has 8 bits or not
    int count;
    //Used to set the bits
    char byte;
};
#endif
