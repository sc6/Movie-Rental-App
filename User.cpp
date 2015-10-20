#ifndef USER_IMPL_INCLUDED
#define USER_IMPL_INCLUDED

#include "User.h"


//[DONE] constructor
User::User (string ID, string name)
{
	this->ID = ID;
	this->name = name;
	this->checkedOut = NULL;
	//&(this->userQueue) = NULL;
}

//[DONE] deep copy constructor
User::User (const User & other)
{
	this->ID = other.ID;
	this->name = other.name;
	this->checkedOut = other.checkedOut;
	this->userQueue = other.userQueue;		//make a deep copy of userQueue
}

//[DONE] destructor
User::~User ()
{ }

//[DONE] gets the user's login id
string User::getID () const
{
	return this->ID;
}

//[DONE] gets the user's name
string User::getName ()
{
	return this->name;
}

//[WORKING] returns a pointer to user's movie queue
queue<Movie*>* User::movieQueue()
{
	return &userQueue;
}

//[WORKING] sets the user's rented movie to m
//Note: if there's already a rented movie, do nothing
void User::rentMovie (Movie *m)
{
	if(checkedOut == NULL) checkedOut = m;
}


//[WORKING] returns the user's rented movie
//Note: if there's no rented movie, do nothing
void User::returnMovie ()
{
	if(checkedOut != NULL) checkedOut = NULL;
}

//[WORKING] returns user's checked out movie.
//Note: returns NULL if no movie is checked out
Movie* User::currentMovie()
{
	if(checkedOut != NULL) return checkedOut;
	else return NULL;
}

#endif