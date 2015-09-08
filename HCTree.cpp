#include <algorithm>
#include <bitset>
#include "HCTree.hpp"

//Default destructor for the tree
HCTree::~HCTree()
{
  delete root;
}

//Method that gets the value or code and puts it into a sequence of type string
std::string HCTree::getValue(byte bits) const
{
  //Checks and returns a valid sequence of bits
  if(value[bits].size())
  {
    return value[bits];
  }

  HCNode* node = leaves[bits];
  std::string seq;

  //This will traverse the tree up to the root while setting the seqence
  while( node->p )
  {
    if (node->p->c0 && node == node->p->c0)
    {
       seq = "0" + seq;
    }
    else
    {
       seq = "1" + seq;
    }
    node = node->p;
  }
  return seq;
}

//Method to build the Huffman Code Tree
void HCTree::build(const std::vector<int> &freqs)
{
  //Starts by adding the correct leaves into the given priority queue
  for(size_t index = 0; index < freqs.size(); index++)
  {
    //Checks to make sure there is a current freq at this point
    if(freqs[index])
    {
      //Creates the node and pushes it to the queue.
      HCNode *node = new HCNode(freqs[index], index);
      leaves[index] = node;
      queue.push(node);
    }
  }

  if(queue.size() == 0)
  {
    HCNode *rootNode = new HCNode(0,0);
    root = rootNode;
    return;
  }

  //Adds a new node if the queue is only of size 1
  if(queue.size() == 1)
  {
    queue.push(new HCNode(0, 0));
  }

  //Constructs the internal nodes of the Huffman tree.
  HCNode *node;
  while (queue.size() > 1)
  {
    node = new HCNode(0, 0);

    node->c0 = queue.top();
    node->c0->p = node;
    queue.pop();

    node->c1 = queue.top();
    node->c1->p = node;
    queue.pop();

    node->count = node->count + node->c0->count;
    node->count = node->count + node->c1->count;

    queue.push(node);
  }

  //Changes the root of the tree when it is full constructed.
  root = queue.top();
}

//Method that encodes the tree into an out file to be decoded later on
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  //Gets the certain code sequence of the current symbol
  std::string seq = getValue(symbol);

  //Writes the bits to the correct sequences
  for(size_t index = 0; index < seq.size(); index++)
  {
    if(seq[index] == '1')
    {
      out.writeBit(true);
    }
    else
    {
      out.writeBit(false);
    }
  }
}

//Method that reads in a compress file and decodes it to it's original form
int HCTree::decode(BitInputStream& in) const
{
  HCNode *currNode = root;
  int bit;

  //Traverses the tree to each node and returns the respective symbol
  while(currNode->c0 || currNode->c1)
  {
    bit = in.readBit();
    if(bit == 1)
    {
      currNode = currNode->c1;
    }
    else
    {
      currNode = currNode->c0;
    }
  }
  return currNode->symbol;
}
