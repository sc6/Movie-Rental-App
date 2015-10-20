#ifndef PROJ_SET_HEADER_INCLUDED
#define PROJ_SET_HEADER_INCLUDED

#include <set>
#include <vector>
#include "proj_mergeSort.h"



template <class T>
class Set: public std::set<T>
{
  public:
	
    //[todo] returns the union of this and other
    Set<T> setUnion (Set<T> & other);
    
    //[todo] returns the intersection of this and other
    Set<T> setIntersection (Set<T> & other); //changed signature

};


#include "proj_set_impl.cpp"


#endif