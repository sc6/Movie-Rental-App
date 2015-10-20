#ifndef NETFLIX_H
#define NETFLIX_H

#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../User.h"


using namespace std;

class Netflix
{
	
public:
	
	Netflix();
	bool loginUser(string user, string password);
	
	void importUsers(map<string, User*> & m);
	void importMovies(map<string, Movie*> & m);
	void importKeywords(map<string, set<Movie*>*> & m);
	void importUserFileOutput(ofstream * user_append_data);
	
	void setCurrentUser(string user);
	
	void userLogOut();
	
	Movie* searchTitle(string movieTitle);
	set<Movie*>* searchKeyword(string movieKeyword);

	string showCurrentUser();
	User* showCurrentUserObj();
	string showCurrentMovie();
	
	//Compares ratings of the two given users. Returns the similarity factor.
	double compareUsers(User* a, User* b);
	
	//Sets a recommended movie for the given user.
	Movie* calculateRecommendation(User* a);
	
	//[todo] make private via. setter functions
	ofstream * user_append_data;
	map<string, User*> map_of_users;
	map<string, Movie*> map_of_movies;
	map<string, set<Movie*>*> map_of_keywords;

private:
	//information tables

	string currentUser;
	User * currentUserObj;
	
	string makeLowercase(string s);
};


#include "Netflix.cpp"

#endif