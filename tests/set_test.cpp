#include "../lib/proj_set.h"
#include <gtest/gtest.h>


class set_test: public ::testing::Test
{

	
};


TEST (SetTest, unionTestA) {	//checks set size
	Set<int> *a = new Set<int>;
	Set<int> *b = new Set<int>;
	
	for(int i = 0; i < 5; i++) a->add(i);
	for(int i = 5; i < 10; i++) b->add(i);
	
	Set<int> unionSet = a->setUnion(*b);
	
	EXPECT_EQ(10, unionSet.size());
}


TEST (SetTest, unionTestB) {	//checks content
	Set<int> *a = new Set<int>;
	Set<int> *b = new Set<int>;

	for(int i = 0; i < 5; i++) a->add(i);
	for(int i = 5; i < 10; i++) b->add(i);
	
	Set<int> unionSet = a->setUnion(*b);
		
	for(int i = 0; i < 10; i++) ASSERT_TRUE(unionSet.contains(i));
}


TEST (SetTest, unionTestC) {	//checks repeats
	Set<int> *a = new Set<int>;
	Set<int> *b = new Set<int>;

	int i;
	i = 1; a->add(i);
	i = 1; a->add(i);
	i = 1; a->add(i);
	
	i = 1; b->add(i);
	i = 1; b->add(i);
	i = 1; b->add(i);
	
	Set<int> unionSet = a->setUnion(*b);
		
	EXPECT_EQ(1, unionSet.size());
	ASSERT_TRUE(unionSet.contains(1));
}



TEST (SetTest, intersectionTestA) {	//checks set size (no intersections, 0)
	Set<double> *a = new Set<double>;
	Set<double> *b = new Set<double>;
	
	for(double d = 0; d < 5.0; d=d+1) a->add(d);
	for(double d = 5.0; d < 10.0; d=d+1) b->add(d);
	
	Set<double> intersectionSet = a->setIntersection(*b);
	
	EXPECT_EQ(0, intersectionSet.size());
}

TEST (SetTest, intersectionTestB) {	//checks set size (all elements same, 1)
	Set<double> *a = new Set<double>;
	Set<double> *b = new Set<double>;
	
	double insert = 10.0;
	for(double d = 0; d < 5.0; d=d+1) a->add(insert);
	for(double d = 5.0; d < 10.0; d=d+1) b->add(insert);

	Set<double> intersectionSet = a->setIntersection(*b);
	
	ASSERT_TRUE(intersectionSet.contains(10.0));
	EXPECT_EQ(1, intersectionSet.size());
}


TEST (SetTest, intersectionTestC) {	//checks set size (repeats in one set, 0)
	Set<double> *a = new Set<double>;
	Set<double> *b = new Set<double>;
	
	double d;
	d = 1.0; a->add(d);
	d = 2.0; a->add(d);
	d = 3.0; a->add(d);
	
	d = 4.0; b->add(d);
	d = 4.0; b->add(d);
	d = 5.0; b->add(d);
	
	Set<double> intersectionSet = a->setIntersection(*b);
	
	EXPECT_EQ(0, intersectionSet.size());
}

