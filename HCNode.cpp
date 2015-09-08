#include "HCNode.hpp"

//The default destructor method
HCNode::~HCNode()
{
  if(c0)
  {
    delete c0;
  }
  if(c1)
  {
    delete c1;
  }
}

//Operator method
bool HCNode::operator<(const HCNode& other)
{
  return other.count <= this->count;
}
