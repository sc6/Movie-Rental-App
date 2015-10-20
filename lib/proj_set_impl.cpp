#ifndef PROJ_SET_IMPL_INCLUDED
#define PROJ_SET_IMPL_INCLUDED


//[WORKING] returns the union of this and other
template <class T>
Set<T> Set<T>::setUnion (Set<T> & other)
{
	//translating set to vector
	vector<T> *v_this = new vector<T>();
	vector<T> *v_other = new vector<T>();
	
	for(Set<T>::Iterator si_this = this->begin(); si_this != this->end(); ++si_this)
	{
		v_this->push_back(si_this.current->key);
	}
	
	for(Set<T>::Iterator si_other = other.begin(); si_other != other.end(); ++si_other)
	{
		v_other->push_back(si_other.current->key);
	}
	
	//sorting the vectors
	MergeSort::sort(*v_this);
	MergeSort::sort(*v_other);
	
	//finding union of the vectors
	typename vector<T>::iterator vI_other = v_other->begin();
	Set<T>* toReturn = new Set<T>();
	
	for(typename vector<T>::iterator vI_this = v_this->begin(); vI_this != v_this->end(); ++vI_this) {
		toReturn->add(*vI_this);
	}
	
	for(typename vector<T>::iterator vI_other = v_other->begin(); vI_other != v_other->end(); ++vI_other) {
		toReturn->add(*vI_other);
	}
	
	return *toReturn;
}

//[WORKING] returns the intersection of this and other
template <class T>
Set<T> Set<T>::setIntersection (Set<T> & other)
{
	//translating set to vector
	vector<T> *v_this = new vector<T>();
	vector<T> *v_other = new vector<T>();
	
	for(Set<T>::Iterator si_this = this->begin(); si_this != this->end(); ++si_this)
	{
		v_this->push_back(si_this.current->key);
	}
	
	for(Set<T>::Iterator si_other = other.begin(); si_other != other.end(); ++si_other)
	{
		v_other->push_back(si_other.current->key);
	}
	
	//sorting the vectors
	MergeSort::sort(*v_this);
	MergeSort::sort(*v_other);
	
	//finding intersection of the vectors
	typename vector<T>::iterator vI_other = v_other->begin();
	Set<T>* toReturn = new Set<T>();
	
	for(typename vector<T>::iterator vI_this = v_this->begin(); vI_this != v_this->end(); ++vI_this) {
		
		while(vI_other != v_other->end()) {
			if(*vI_this == *vI_other) { 
				toReturn->add(*vI_this); 
				++vI_other; 
				break; 
			}
			else if(*vI_this > *vI_other) ++vI_other;
			else break;
		}
	}
	
	return *toReturn;
}


#endif