/*#####################################################################################################################
Note: Please don’t upload the assignments, template file/solution and lab. manual on GitHub or others public repository.
Kindly remove them, if you have uploaded the previous assignments. 
It violates the BITS’s Intellectual Property Rights (IPR).
***********************************************************************************************************************/

#include <fstream>
#include <bits/stdc++.h>
//extern LW_OFFSET_BITS;
using namespace std;


class SetAssociativeCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* numOfSets = number of sets for cache
	* offSetBits = number of offset bits in address
	* setBits = number of set bits in address
	* tagBits = number of tag bits in address
	* FIFO replacement policy
	* tags = data structure to store tag bits
	* valid = data structure to store valid bits
	* data = data structure to store data
		*/
	int cacheSize;
	int blockSize;
	int ways;
	int numOfBlock;
	int numOfSets;
	int offsetBits;
	int setBits;
	int tagBits;
	//unsigned int LW_OFFSET_BITS 16;
	vector<unsigned int> tags;
	vector<bool> valid;
	vector<int> data;
	FIFO fifo;
	

	/*
	* @constructor
	* 
	* @param
	* blockSize = represents block size for cache (in word units)
	* cacheSize = represents cache size for cache (in word units)
	* ways = represents number of ways
	* FIFO replacement policy 
	*/
	SetAssociativeCache(int blockSize, int cacheSize, int ways) {
		this->cacheSize = //WRITE YOUR CODE HERE
		this->blockSize = //WRITE YOUR CODE HERE
		this->ways = //WRITE YOUR CODE HERE
		this->numOfBlock = //WRITE YOUR CODE HERE
		this->offsetBits = //WRITE YOUR CODE HERE
		this->numOfSets = //WRITE YOUR CODE HERE
		this->setBits = //WRITE YOUR CODE HERE
		this->tagBits = //WRITE YOUR CODE HERE
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		
		for(int i = 0; i < numOfBlock; i++) {
			valid[i] = //WRITE YOUR CODE HERE
		}
		this->data.reserve(numOfBlock);
		this->fifo = FIFO(this->ways, this->numOfSets);
		
	}

	/*
	* @method
	* method to get data from cache given mem address
	* 
	* @param
	* addr = represnets memory address to access data
	*/
	int get(int addr) {
		int offSet, set, tag, index;
		//WRITE YOUR CODE HERE

		offSet = ((1<<(this->offsetBits))-1) & addr; 
        set = ((addr >> this->offsetBits) & ((1 << (this->setBits))-1));
		tag = addr >> (this->setBits + this->offsetBits);
		
		
		
		// fetching index from replacement policy instance
		index = fifo.getIndex(tag, set, this->ways, tags, valid);
		return data[index];
	}

	/*
	* @method
	* method to print valid, tag and data tables
	*/
	void display() {
		cout << "VALID tabel" << endl;

		for(int i = 0; i < numOfBlock; i++) {
			cout << i << " : " << (valid[i] ? "1" : "0") << endl;
		}
		
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