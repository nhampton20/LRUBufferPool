#include "LRUBufferPool.h"

//char* LRUBufferPool::readHelp(string filename, int blocksize)
//{
//	
//	
//	in.close();
//	return end;
//}

LRUBufferPool::LRUBufferPool(string filename, int poolSize, int blockSize)
{
	
	/*LRUBufferBlock pool = shared_ptr<LRUBufferBlock[]>(poolSize);*/
	char* end= new char[blockSize];
	//pool= unique_ptr<shared_ptr<LRUBufferBlock>[]> (new shared_ptr<LRUBufferBlock>[blockSize]);
	//pool1 = vector<shared_ptr<LRUBufferBlock>>(new shared_ptr<LRUBufferBlock>[blockSize]);
	bSize = blockSize;
	pSize = poolSize;

	in.open(filename.c_str(), fstream::in, fstream::binary);
	if (!in.is_open()) exit(-1);
	in.seekg(0);

	for (short i = 0; i < pSize; i++) {
		in.read(end, blockSize);
		shared_ptr<LRUBufferBlock> block = make_shared<LRUBufferBlock>(end, blockSize, i);
		//LRUBufferBlock* block = new LRUBufferBlock(readHelp(data, filename, blockSize), blockSize);
		//pool[i] = block;
		pool1.push_back(block);
	}
}

LRUBufferPool::~LRUBufferPool()
{
}

void LRUBufferPool::getBytes(char* space, int sz, int pos)
{
	int block = pos / bSize;
	int start = pos % bSize;
	int flag = 0;
	for (int i = 0; i < pSize; i++)
		if (pool1.at(i)->getID() == block) {
			flag = i; break;
		}
	if (flag==0) {
		char* end = new char[bSize];
		this->in.seekg((block-1)*bSize);
		this->in.read(end, bSize);

		//for (short i = pSize - 2; i >= 0; i--) {
		//	//pool[i + 1] = pool[i];
		//}
		//shared_ptr<LRUBufferBlock> block = make_shared<LRUBufferBlock>(end, bSize, block);

		shared_ptr<LRUBufferBlock> block1 = make_shared<LRUBufferBlock>(end, bSize, block);
		pool1.erase(pool1.end()-1);
		pool1.insert(pool1.begin(), block1);
		//pool[0] = block;
	}
	//for (int i = 0; i < pSize; i++)
	//	//if (pool[i]->getID() == block) pool[i]->getData(start, sz - 1, space);
	//	if (pool1.at(i)->getID() == block) {
	//		pool1.at(i)->getData(start, sz - 1, space); break;
	//	}
	pool1.at(flag)->getData(start, sz , space);

	//shared_ptr<LRUBufferBlock> temp = pool[block];
	shared_ptr<LRUBufferBlock> temp1 = pool1.at(flag);
	for (short i = flag-1; i >= 0; i--) {
		//pool[i + 1] = pool[i];
		iter_swap(pool1.begin() + i + 1, pool1.begin() + i);
	}
	//pool[0] = temp;
	pool1.erase(pool1.begin());
	pool1.insert(pool1.begin(), temp1);
}

void LRUBufferPool::printBufferBlockOrder()
{
	cout << "Buffer Block Order by ID is: ";
	for (short i = 0; i < pSize; i++) {
		//cout << pool[i]->getID() << " ";
		cout << pool1.at(i)->getID() << " ";
	}
	cout << "\n";
}

int LRUBufferPool::getLRUBlockID()
{
	//return pool[0]->getID();
	return pool1.at(0)->getID();
}
