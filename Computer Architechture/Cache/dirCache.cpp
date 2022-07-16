/*#####################################################################################################################
Note: Please don’t upload the assignments, template file/solution and lab. manual on GitHub or others public repository.
Kindly remove them, if you have uploaded the previous assignments. 
It violates the BITS’s Intellectual Property Rights (IPR).
***********************************************************************************************************************/

#include <bits/stdc++.h>
//extern LW_OFFSET_BITS;
using namespace std;

class DirectMapCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* offSetBits = number of offset bits in address
	* indexBits = number of index bits in address
	* tagBits = number of tag bits in address
	* tags = data structure to store tag bits
	* valid = data structure to store valid bits
	* data = data structure to store data
	* hit = represents number of hits
	* miss = represents number of miss
	*/
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int indexBits;
	int tagBits;
	
	vector<unsigned int> tags;
	vector<bool> valid;
	vector<int> data; 

	int hit;
	int miss;

	/*
	* @construnctor
	* @param
	* blockSize = represents number of blocksize for cache (in word units)
	* cacheSize = represnts number of cache size for cache (in word units)
	*/
	DirectMapCache(int blockSize, int cacheSize) {
		this->cacheSize =            //WRITE YOUR CODE HERE
		this->blockSize =              //WRITE YOUR CODE HERE
		this->numOfBlock =  //WRITE YOUR CODE HERE
		this->offsetBits =  //WRITE YOUR CODE HERE
		this->indexBits =   //WRITE YOUR CODE HERE
		this->tagBits =  //WRITE YOUR CODE HERE
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		for(int i = 0; i < numOfBlock; i++) {
			valid[i] = //WRITE YOUR CODE HERE
		}
		this->hit =  //WRITE YOUR CODE HERE
		this->miss =  //WRITE YOUR CODE HERE
	}


	/*
	* @method
	* method to get data from cache and calculate hit and miss
	*
	* @param
	* addr = represents memory address
	*/
	int get(int addr) {
		int offSet, index, tag;
		//WRITE YOUR CODE HERE

		offSet = (1<<(this->offsetBits-1)) & addr; 
        index = ((addr >> this->offsetBits) & ((1 << (this->indexBits))-1));
		tag = addr >> (this->indexBits + this->offsetBits);

        if(this->tags[index]==tag && valid[index]==1) hit++;
        else {
            
            tags[index] = tag;
            valid[index] = 1;            
            miss++;}
		
		return data[index];
	}

	/*
	* @method
	* method to display valid, tag and data table
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