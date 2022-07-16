/*#####################################################################################################################
Note: Please don’t upload the assignments, template file/solution and lab. manual on GitHub or others public repository.
Kindly remove them, if you have uploaded the previous assignments. 
It violates the BITS’s Intellectual Property Rights (IPR).
***********************************************************************************************************************/

#include <queue>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

class FIFO {

	/*
	* @param
	* size = size of the queue
	* q = vector of queues, (for fully associative cache vector size = 1 otherwise vector size = number of sets)
	* lastEntry = represents last index where data was inserted (only used for fully associative cache)
	* hit = represents number of hits in cache
	* miss = represents number of miss in cache
	*/
	int size;
	vector<queue<int>> q;
	int lastEntry;
public:
	int hit;
	int miss;

	/*
	* @constructor
	* @method
	* size = represents size of queue
	* sets = represents number of sets in cache (1 = fully associative cache, otherwise set associvative)
	*/
	FIFO(){}
	FIFO(int size, int sets) {
		this->size = size; //WRITE YOUR CODE HERE
		this->lastEntry = -1; //WRITE YOUR CODE HERE
		this->hit = 0;//WRITE YOUR CODE HERE
		this->miss = 0;//WRITE YOUR CODE HERE
		for(int i = 0; i < sets; i++) { // Maintain a queue for each set.
			queue<int> temp_q;
			q.push_back(temp_q);
		}

	}

	/*
	* @method
	* method to get the index of data array based on tag and handeling of miss and hit scenarios for fully associative cache
	*
	* @param
	* tag = represents tag bits from mem address
	* data = represents tag table
	*/
	int getIndex(unsigned int tag, vector<unsigned int> &tags, vector<bool> &valid) {
        int i;
		//WRITE YOUR CODE HERE

		for(i=0; i < size; i++)
			if(valid[i] && tags[i]==tag)
			{
				this->hit++;
				break;
			}

		if (i==size)
		{
			this->miss++;
			if (q[0].size() < size)
				i = q[0].size();
			else
			{
				i = q[0].front();
				q[0].pop();	
			}

			q[0].push(i);
			valid[i] = true;
			tags[i] = tag;
		}


		return i;
	}

	/*
	* @method
	* method to get the index of data array based on tag and handeling of miss and hit scenarios for set associative cache
	*
	* @param
	* tag = represents tag bits from address
	* set = represents set bits from address
	* ways = represents number of ways for cache
	* data = represents tag table
	* valid = represents valid bit table
	*/
	int getIndex(unsigned int tag, int set, int ways, vector<unsigned int> &tags, vector<bool> &valid) {
		int base, temp, i;
		//WRITE YOUR CODE HERE
		
		base = set*ways;
		temp = -1;
		for(i=base; i < base + size; i++)
			if(valid[i] && tags[i]==tag)
			{
				this->hit++;
				temp = i;
				break;
			}

		if (temp==-1)
		{
			this->miss++;
			if (q[set].size() < ways)
				i = base + q[set].size();
			else
			{
				i = q[set].front();
				q[set].pop();	
			}

			q[set].push(i);
			valid[i] = true;
			tags[i] = tag;
		}

		return i;
	}
};