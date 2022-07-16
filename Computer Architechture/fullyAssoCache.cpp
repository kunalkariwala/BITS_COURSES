/*#####################################################################################################################
Note: Please don’t upload the assignments, template file/solution and lab. manual on GitHub or others public repository.
Kindly remove them, if you have uploaded the previous assignments. It violates the BITS’s Intellectual Property Rights (IPR).
***********************************************************************************************************************/

#include <bits/stdc++.h>
using namespace std;
//extern LW_OFFSET_BITS;
class FullyAssociativeCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* offSetBits = number of offset bits in address
	* tagBits = number of tag bits in address
	* FIFO replacement policy
	* tags = data structure to store tag bits
	* data = data structure to store data
	* fifo = instance of FIFO replacement policy
	* lru = instance of LRU replacement policy
	*/
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int tagBits;
	
	//unsigned int LW_OFFSET_BITS 16;
	vector<unsigned int> tags;
	vector<bool> valid;
	vector<int> data;
	FIFO fifo;
	

	/*
	* @constructor
	* @param
	* blockSize = represents block size for cache (in word units)
	* cacheSize = represents cache size for cache (in word units)
	* replacement = represnt replacement policy for cache (1 = FIFO, 2 = LRU)
	*/
	FullyAssociativeCache(int blockSize, int cacheSize) {
		this->cacheSize = cacheSize;//WRITE YOUR CODE HERE
		this->blockSize = blockSize;//WRITE YOUR CODE HERE
		this->numOfBlock = cacheSize/blockSize;//WRITE YOUR CODE HERE
		this->offsetBits = log2(blockSize*4);//WRITE YOUR CODE HERE
		this->tagBits = 16 - this->offsetBits;//WRITE YOUR CODE HERE
		this->tags.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
        this->valid.reserve(numOfBlock);
		for(int i = 0; i < numOfBlock; i++) {
			valid[i] = false; 
		}
		this->fifo = FIFO(this->numOfBlock, 1);
		
	}


	/*
	* @method
	* method to get data from cache given address
	*
	* @param
	* addr = represent memory address
	*/
	int get(int addr) {
		int offSet, tag, index;
		//WRITE YOUR CODE HERE
		
     	offSet = ((1<<(offsetBits))-1) & addr; 

		tag = addr >> (offsetBits);

		index = fifo.getIndex(tag, tags, valid) ;
		
		return data[index];
	}

	/*
	* @method
	* method to display tag, valid and data tables
	*/
	void display() {
		
		cout << "TAG tabel" << endl;

		stringstream ss;
		for(int i = 0; i < numOfBlock; i++) {
			ss.str("");
			ss << hex << tags[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}

		cout << "DATA tabel" << endl;

		for(int i = 0; i < numOfBlock; i++) {
			ss.str("");
			ss << hex << data[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}
	}
};