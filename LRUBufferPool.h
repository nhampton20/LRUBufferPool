#pragma once
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include "BufferPoolADT.h"
#include "LRUBufferBlock.h"
class LRUBufferPool :
    public BufferPoolADT
{
private:

	//unique_ptr<shared_ptr<LRUBufferBlock>[]> pool;
	vector<shared_ptr<LRUBufferBlock>> pool1;
	unsigned short pSize;
	unsigned int bSize;
	fstream in;

	//char* readHelp( string filename, int blocksize);
public:

	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096);
    ~LRUBufferPool();

	virtual void getBytes(char* space, int sz, int pos) ;

	// Print the order of the buffer blocks using the block id
	//numbers.
	virtual void printBufferBlockOrder();

	// Get the block id number of the least recently used 
	//	 buffer block.
	virtual int getLRUBlockID();
};

