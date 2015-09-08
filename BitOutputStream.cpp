#include <iostream>
#include <bitset>
#include "BitOutputStream.hpp"

//Default destructor that flushes everything
BitOutputStream::~BitOutputStream()
{
  if(count != 0)
  {
    flush();
  }
}

//Method to write the bits into the buffer
void BitOutputStream::writeBit(int bit)
{
  //Increments the counter
  count++;

  //Checks if the bit is non zero and writes it
  if (bit) 
  {
    byte = (byte << 1) | 1;
  }
  else 
  {
    byte = (byte << 1);
  }

  //Flushes the byte if it is full
  if (count == 8) 
  {
    flush();
  }
}

//Used to clear out all the buffers and sets them to zero
void BitOutputStream::flush()
{
  byte = byte << (8 - count);
  count = 0;
  out << byte;
  byte ^= byte;
}
