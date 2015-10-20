#include "../User.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

int main () {
	
	vector<int>* a = new vector<int>;
	Set<int>* b = new Set<int>;
	
	for(int i = 0; i < 10; i++) a->push_back(i);
	
	for(int i = 100; i > 90; i--) a->push_back(i);
	
	MergeSort::sort(*a);
	
	for(vector<int>::iterator vI = a->begin(); vI != a->end(); ++vI)
		cout << *vI << endl;
	
	
	return 0;
}