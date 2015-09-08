#include <sstream>
#include <iostream>
#include <bitset>
#include "BitInputStream.hpp"

int BitInputStream::readBit() 
{
  //Fills the buffer if all bits have been read
  if( nbits == 8 )
  {
    fill();
  }

  //Gets the location of correct bits
  int number = buffer & (1 << ( 7 - nbits ));
  
  nbits++;

  if (number != 0)
    return 1;
  else
    return 0;
}
