#ifndef MOVIE_IMPL_INCLUDED
#define MOVIE_IMPL_INCLUDED

#include "Movie.h"



//Constructor (w/ movie title)
Movie::Movie (string title)
{
	this->title = title;
	//cerr << "+ " << title << " added." << endl;
}

//Deep Copy Constructor
Movie::Movie (const Movie & other)
{
	this->title = other.title;
	this->keywords = other.keywords;
}

//Destructor
Movie::~Movie ()
{
	//delete keywords;
}

//GET TITLE
string Movie::getTitle() const
{
	return this->title;
}

//ADD KEYWORD
void Movie::addKeyword (string keyword)
{			
	this->keywords.insert(keyword);
	//cerr << "+ Added '" << keyword << "' to " << this->title << "." << endl;
	
	//Note: Duplicates are accounted for in Map.add
}

//GET ALL KEYWORDS
set<string> Movie::getAllKeywords () const
{
	//cerr << "(Got keywords for " << this->title << ")" << endl; 
	
//	Set<string> dummy = new Set<string>(keywords);
//	keywords.first();
//	cout << keywords.getCurrent();
	
	try{
		return this->keywords;
	}
	catch(NoSuchElementException & e) {
		return keywords;
	}
	

}


void Movie::addActor(string actor)
{
	this->actors.insert(actor);
}

set<string> Movie::getAllActors() const 
{
	return keywords;
}




#endif