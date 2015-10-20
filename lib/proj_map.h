#ifndef PROJ_MAP_HEADER_INCLUDED
#define PROJ_MAP_HEADER_INCLUDED

#include "proj_required.h"

//template <class T>
//class set;


template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev, *next;
};


template <class FirstType, class SecondType>
struct Pair {
   FirstType first;
   SecondType second;

   Pair (FirstType first, SecondType second)
      { this->first = first; this->second = second; }
};


template <class keyType, class valueType>
class Map {
   
public:
	//[DONE] map constructor
	Map ();
	
	//[DONE] map deep-copy constructor
	Map (const Map<keyType, valueType> & other);
	
	//[DONE] map destructor
    ~Map ();
 
    //[DONE] returns size
    int size () const;
   
    //[DONE] adds given key/value pair
    void add (const keyType & key, valueType & value);
    
    //[DONE] removes key/value pair given key
    void remove (const keyType & key);

    //[DONE] returns value given key
    valueType & get (const keyType & key) const;

    //[DONE] adds all values of other into this
    void merge (const Map<keyType, valueType> & other);
    
    //[DONE] makes this equal to the other
    Map<keyType, valueType> & operator= (const Map<keyType, valueType> & other);

    //friend class set<keyType>;
    
	class Iterator {
	  public:
    	   friend class Map<keyType, valueType>;
    	
    	   //[WORKING] map's iterator 'dereference' *
    	   Pair<keyType, valueType> operator* () const;
		   
		   //[WORKING] map's iterator 'pre-increment' ++
		   Map<keyType,valueType>::Iterator operator++ ();
		
		   //[WORKING] make this equal to other iterator
		   Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other);
		   
		   //[WORKING] returns whether this and other are the same
		   bool operator== (const Map<keyType,valueType>::Iterator & other) const;
		
		   //[WORKING] returns whether this and other are NOT the same
		   bool operator!= (const Map<keyType,valueType>::Iterator & other) const;

		   MapItem<keyType, valueType>* current;
		   
	  private:
	    	
		   //[WORKING] iterator constructor (call using Map<keyType, valueType>::Iterator)
		   Iterator(const Map<keyType, valueType>* m, MapItem<keyType, valueType> *p);
		   
		   const Map<keyType, valueType> *whoIBelongTo;
		  
		
	};
	
	//[todo] returns iterator set to first element
    typename Map<keyType,valueType>::Iterator begin () const;
       
    //[todo] returns iterator set to last element +1
    typename Map<keyType, valueType>::Iterator end () const;

     
     
  private:
     
	MapItem <keyType, valueType> *head, *tail;
};




#include "proj_map_impl.cpp"
#endif