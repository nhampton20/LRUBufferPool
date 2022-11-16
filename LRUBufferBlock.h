#pragma once
#include "BufferBlockADT.h"
class LRUBufferBlock :
    public BufferblockADT
{
private:
    char* block;
    int blockID;
    unsigned short size;


public:

    LRUBufferBlock(char* data, int sz = 4096, int ID=0);
    ~LRUBufferBlock();
    //read the block from pos to pos + sz-1 (or to the end of the block)
    virtual void getData(int pos, int sz, char* data);

    //setID
    virtual void setID(int id);

    //getID
    virtual int getID() const ;

    //getBlocksize
    virtual int getBlocksize() const;

    //return the block
    virtual char* getBlock() const;

    //set the block
    virtual void setBlock(char* blk);

};

