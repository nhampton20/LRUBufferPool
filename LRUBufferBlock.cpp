#define _CRT_SECURE_NO_WARNINGS
#include "LRUBufferBlock.h"


LRUBufferBlock::LRUBufferBlock(char* data, int sz, int ID)
{
    size = sz;
    block = new char[size];
    setBlock(data);
    
    blockID = ID;

}
LRUBufferBlock::~LRUBufferBlock()
{
    delete block;
}

void LRUBufferBlock::getData(int pos, int sz, char* data)
{
    try {
        int count = 0;
        for (int i = pos; i < pos+sz; i++) {
           data[count] = block[i];
           count++;
        }
        //strncat_s(data, sizeof(data), block + pos, sz);
    }
    catch (out_of_range) {
    }
}

void LRUBufferBlock::setID(int id)
{
    blockID = id;
}

int LRUBufferBlock::getID() const
{
    return blockID;
}

int LRUBufferBlock::getBlocksize() const
{
    return size;
}

char* LRUBufferBlock::getBlock() const
{
    return block;
}

void LRUBufferBlock::setBlock(char* blk)
{
    for (int i = 0; i < size; i++) {
        block[i] = blk[i];
    }
}

