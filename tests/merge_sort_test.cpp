#include "../lib/proj_mergeSort.h"
#include <gtest/gtest.h>


class merge_sort_test: public ::testing::Test
{

	
};


//BasicCase tests whether a 'normal' vector is successfully sorted and returned.
TEST (MergeSortTest, BasicCase) {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	std::vector<int> v_sorted = MergeSort::sort(v);
	for(unsigned int i = 0; i < v.size(); i++) {
		std::cout << i+1 << " == " << v_sorted.at(i) << std::endl;
		EXPECT_EQ(v_sorted.at(i), i+1);
	}
}


//MinCase tests whether a vector of length 1 is successfully 'sorted' and returned as expected.
TEST (MergeSortTest, MinCase) {
	std::vector<int> v;
	v.push_back(1);
	std::vector<int> v_sorted = MergeSort::sort(v);
	EXPECT_EQ(v_sorted.at(0), 1);
}



//OddCase tests whether a vector with odd-number of elements will be split and sorted successfully.
TEST (MergeSortTest, OddCase) {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	std::vector<int> v_sorted = MergeSort::sort(v);
	for(unsigned int i = 0; i < v.size(); i++) {
		EXPECT_EQ(v_sorted.at(i), i+1);
	}

}