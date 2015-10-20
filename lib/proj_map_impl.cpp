#ifndef PROJ_MAP_IMPL_INCLUDED
#define PROJ_MAP_IMPL_INCLUDED

//Implementations of proj_map.


//CONSTRUCTOR.
template <class keyType, class valueType>
Map<keyType, valueType>::Map() {
	this->head = NULL;
	this->tail = NULL;
}


//CONSTRUCTOR, DEEP COPY. Copies 'other' to make a new map.
template <class keyType, class valueType>
Map<keyType, valueType>::Map (const Map<keyType, valueType> & other) 
{	
	this->head = NULL;
	this->tail = NULL;
	
	MapItem<keyType, valueType> *p = other.head;
	while(p != NULL)
	{
		this->add(p->key, p->value);
		
		if(p->next != NULL) p = p->next;
		else break;
	}
}


//DESTRUCTOR deletes everything created
template <class keyType, class valueType>
Map<keyType, valueType>::~Map() 
{	
	
	if(this->size() == 0) return;
	
	MapItem<keyType, valueType> *p = this->head;
	MapItem<keyType, valueType> *temp;
	while(p->next != NULL)
	{
		temp = p->next;
		delete p;
		p = temp;
	}	
	
	delete p;
}


//SIZE. Returns the number of elements in this map.
template <class keyType, class valueType>
int Map<keyType, valueType>::size() const
{
	int count = 0;
	for(MapItem<keyType, valueType> *p = this->head; p != NULL; p = p->next) 
		++count;
	
	return count;
}


//ADD an element onto the end of the map
template <class keyType, class valueType>
void Map<keyType, valueType>::add (const keyType & key, valueType & value)
{
	//special case: checks for duplicate key
	if(this->head != NULL) 
	{	
		MapItem<keyType,valueType> *p = this->head;
		while(p->next != NULL) {
			if(p->key == key) return;
			p = p->next;
		}
	}

	MapItem<keyType, valueType> *newItem = new MapItem<keyType, valueType>;
	newItem->key = key;
	newItem->value = value;
	this->tail = newItem;
	
	//special case: when newItem is the first item in the map.
	if(this->head == NULL) 
	{
		this->head = newItem;
		newItem->prev = NULL;
		newItem->next = NULL;
	}
	else {
		//setting next of previous element
		MapItem<keyType, valueType> *p = this->head;
		while(p->next != NULL) p = p->next;	//goes to end
		p->next = newItem;
		
		//setting prev of new element
		MapItem<keyType, valueType> *q = this->head;
		while(q->next != newItem) q = q->next;
		newItem->prev = q;
		
		//setting next of new element
		newItem->next = NULL;
		
	}
	
	//delete p;
	//delete q;
}


//REMOVE a specific key/value pair from the map.
template <class keyType, class valueType>
void Map<keyType, valueType>::remove (const keyType & k) 
{	
	//special case: checks if key does not exist OR map is empty
	MapItem<keyType, valueType> *p = this->head;

	if(p == NULL) return;
	
	while(p->key != k) {
		if(p->next == NULL) return;
		p = p->next;
	}
	
	
	//have the previous element's next pointer redirected
	if(p != this->head)
		(p->prev)->next = p->next;
	else 
		this->head = p->next;
	
	//have the next element's prev pointer redirected
	if(p->next != NULL && p->next != this->head)
		(p->next)->prev = p->prev;
	
	//resets the tail
	if(p == this->tail) {
		this->tail = p->prev;
	}
	
	delete p; //<-- problem. seg faults?
}


//GET Given a key, returns the value.
template <class keyType, class valueType>
valueType & Map<keyType, valueType>::get (const keyType & k) const 
{
	MapItem<keyType, valueType> *p = this->head;
	
	while(p != NULL && p->key != k) {
		p = p->next;
	}
	
	if(p == NULL) throw NoSuchElementException();
		
	return p->value; //key found
	
	//catch (NoSuchElementException &e)
}


//MERGE
template <class keyType, class valueType>
void Map<keyType, valueType>::merge (const Map<keyType, valueType> & other) {
	
	MapItem<keyType, valueType> *p = other.head;
	while(p != NULL) {
		try {
			this->get(p->key);
		}
		catch (NoSuchElementException & e){
			this->add(p->key, p->value);
		}
		
		p = p->next;
	}
}


//OPERATOR=. Makes this map equal to the other map. 
//(note: reverse copy is not needed because theyre a map too)
template <class keyType, class valueType>
Map<keyType, valueType> & Map<keyType, valueType>::operator= (const Map<keyType, valueType> & other)
{
	//special case: maps are already equivalent
	if(this==&other)
	{
		return *this;
	}
	
	//removing the old elements (note: garbage is handled in remove())
	MapItem<keyType, valueType> *p = this->head;

	while(p != NULL)
	{
		this->remove(p->key);
		if(p->next != NULL) p = p->next;
		else break;
	}
	
	this->head = NULL;
	this->tail = NULL;

	
	//setting the new elements
	MapItem<keyType, valueType> *q = other.head;

	while(q != NULL)
	{
		this->add(q->key, q->value);		
		if(q->next != NULL) q = q->next;
		else break;
	}
	
	delete p;
	delete q;
	
	return *this;
}


//[WORKING] map's iterator constructor
template <class keyType, class valueType>
Map<keyType, valueType>::Iterator::Iterator(const Map<keyType, valueType>* m, MapItem<keyType, valueType>* p)
{  
	whoIBelongTo = m; current = p;
}

//[WORKING] map's iterator 'dereference' *
template <class keyType, class valueType>
Pair<keyType, valueType> Map<keyType, valueType>::Iterator::operator* () const 
{
	Pair<keyType, valueType> toReturn = Pair<keyType, valueType>(current->key, current->value);
	return toReturn;
}

//[WORKING] map's iterator 'pre-increment' ++
template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType,valueType>::Iterator::operator++ ()
{
	current = current->next;
	return *this;
}

//[WORKING] make this equal to other iterator
template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType,valueType>::Iterator::operator= (const Map<keyType,valueType>::Iterator & other)
{
	if(this.operator==(other)) return;
		
	this.whoIBelongTo = other.whoIBelongTo;
	this.current = other.current;
	
	return this;
}

//[WORKING] returns whether this and other are the same
template <class keyType, class valueType>
bool Map<keyType, valueType>::Iterator::operator== (const Map<keyType,valueType>::Iterator & other) const
{
	return (current == other.current && whoIBelongTo == other.whoIBelongTo);
}

//[WORKING] returns whether this and other are NOT the same
template <class keyType, class valueType>
bool Map<keyType, valueType>::Iterator::operator!= (const Map<keyType, valueType>::Iterator & other) const
{
	return (!this->operator==(other));
}

//[WORKING] returns iterator set to first element
template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType, valueType>::begin() const
{
	return Map<keyType,valueType>::Iterator(this, head);
}

//[WORKING] returns iterator set to last element +1
template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType, valueType>::end() const
{
	return Map<keyType,valueType>::Iterator(this, NULL);
}


#endif