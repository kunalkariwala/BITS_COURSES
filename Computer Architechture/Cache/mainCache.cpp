/*#####################################################################################################################
Note: Please don’t upload the assignments, template file/solution and lab. manual on GitHub or others public repository.
Kindly remove them, if you have uploaded the previous assignments. 
It violates the BITS’s Intellectual Property Rights (IPR).
***********************************************************************************************************************/

#include <bits/stdc++.h>
#include <stdio.h>
#include <fstream>


/*******************************************CONFIGURATION***********************/

#define DIRECT_CACHE 1
#define FULLY_ASSO_CACHE 2
#define SET_ASSO_CACHE 3
#define ITERATION 10000
#define LW_OFFSET_BITS 16
/******************************************************************************/
#include "fifoReplacePolicy.cpp"
#include "dirCache.cpp"
#include "fullyAssoCache.cpp"
#include "setAssoCache.cpp"
using namespace std;


/*
* @method
* method to read file into vector seperated by coma ","
*
* @param
* filename = filename to be read
*/
vector<string> readDataIntoVector(string filename) {
	ifstream f(filename);
	stringstream strStream;
	strStream << f.rdbuf();
	string str = strStream.str();
	f.close();

	vector<string> truth;
	stringstream ss(str);
	while(ss.good()) {
		string substr;
		getline(ss, substr, ',');
		truth.push_back(substr);
	}
	
	return truth;
}

/*
* @method
* main function - starting point of application
*/

int main(int argc, char **traceFile) {

	/*
	* @params
	* cache_type = user input for cache type (1 : direct mapping, 2 : fully associative, 3 : set associative)
	* cache_size = user input for cache size (in words unit, 1 word = 4 bytes)
	* block_size = user input for block size (in words unit)
	* ways = user input for number of ways for set associative
	*/
	int cache_type;
	int cache_size;
	int block_size;
	int ways;

	// reading input file
	vector<string> data = readDataIntoVector(traceFile[1]);

	cout << "Cache Memory" << endl;
	cout << "----------------------------------------------------------------\n" << endl;

	// infinite loop to run program
	while(true) {

		// taking user input for cache type
		cout << "Select Cache Type" << endl;
		cout << "1. Direct mapping cache\n2. Fully Associative Cache\n3. Set Associative Cache" << endl;
		cin >> cache_type;
        
		// DIRECT MAPPING CACHE
		if(cache_type == DIRECT_CACHE) {

			// taking user input for cache parameters
			cout << "you selected direct mapping cache\n" << endl;
			cout << "Enter cache size (unit words): ";
			cin >> cache_size;
			cout << "\nSelect cache block size" << endl;
			cout << "1. 1-word\n2. 2-word" << endl; 
			cin >> block_size;
			cout << endl;

			// initiating direct map cache
			DirectMapCache cache = DirectMapCache(block_size, cache_size);
		
			// looping through given instruction addresses 10000 time
			int indx = 0, total = data.size();
			while(indx < ITERATION) {
				string addr = data[indx % total];
				indx++;
				int data = cache.get(stoi(addr, 0, 16));////Converting string hex
			}

			cout << "hits : " << cache.hit << " out of " << ITERATION << " hit ratio: " << (float) cache.hit/ITERATION << endl;
			cout << "miss : " << cache.miss << " out of " << ITERATION << " miss ratio: " << (float) cache.miss/ITERATION << endl;

			//cache.display();

		} else {

			// FULLY ASSOCIATIVE CACHE
			if(cache_type == FULLY_ASSO_CACHE) {

				// taking user input for cache parameters
				cout << "you selected fully associative cache\n" << endl;
				cout << "Enter cache size (unit words): ";
				cin >> cache_size;
				cout << "\nSelect cache block size" << endl;
				cout << "1. 1-word\n2. 2-word" << endl; 
				cin >> block_size;
				cout << endl;

				// initiating fully  associative cache
				FullyAssociativeCache cache = FullyAssociativeCache(block_size, cache_size);
				
				// looping through given instruction addresses 10000 times
				int indx = 0, total = data.size();
				while(indx < ITERATION) { //50
					string addr = data[indx % total];
					indx++;
					int data = cache.get(stoi(addr, 0, 16));////Converting string hex
				}

				//cout << "hits : " << cache.fifo.hit  << endl;
				//cout << "miss : " << cache.fifo.miss  << endl;
				
				cout << "hits : " << cache.fifo.hit << " out of " << ITERATION << " hit ratio: " << (float) cache.fifo.hit/ITERATION << endl;
			    cout << "miss : " << cache.fifo.miss << " out of " << ITERATION << " miss ratio: " << (float) cache.fifo.miss/ITERATION << endl;

				// cache.display();

			} 

			// SET ASSOCIATIVE CACHE
			else if(cache_type == SET_ASSO_CACHE) {

				// taking user input for cache parameters
				cout << "\nyou selected set associative cache\n" << endl;
				cout << "Enter cache size (unit words): ";
				cin >> cache_size;
				cout << "\nSelect cache block size" << endl;
				cout << "1. 1-word\n2. 2-word" << endl;
				cin >> block_size;
				cout << "\nSelect ways" << endl;
				cout << "1. 2-way\n2. 4-way" << endl;
				cin >> ways;
				cout << endl;

				// initiating set associative cache
				SetAssociativeCache cache = SetAssociativeCache(block_size, cache_size, ways);
				
				// looping through given instruction addresses 10000 times
				int indx = 0, total = data.size();
				while(indx < ITERATION) { // 50
					string addr = data[indx % total];
					indx++;
					int data = cache.get(stoi(addr, 0, 16)); //Converting string hex
				}
				
				cout << "hits : " << cache.fifo.hit << " out of " << ITERATION << " hit ratio: " << (float) cache.fifo.hit/ITERATION << endl;
			    cout << "miss : " << cache.fifo.miss << " out of " << ITERATION << " miss ratio: " << (float) cache.fifo.miss/ITERATION << endl;

				// cache.display();
			} else {
				cout << "\nwrong choice" << endl;
			}
		}

		string reply;
		cout << "\nDo you want to continue (Y/N)?" << endl;
		cin >> reply;
		if(reply == "N" || reply == "n") break;
	}
	return 0;
}