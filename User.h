#ifndef PROJ_USER_HEADER_INCLUDED
#define PROJ_USER_HEADER_INCLUDED

#include "Movie.h"



class User {
  public:
	//[DONE] constructor
    User (string ID, string name);  

    //[DONE] deep copy constructor
    User (const User & other);

    //[DONE] destructor
    ~User ();

    //[DONE] gets the users login id
    string getID () const;

    //[DONE] gets the users name
    //Note: removed const (member class const)
    string getName ();
    
    //[WORKING] returns a pointer to user's movie queue
    queue<Movie*>* movieQueue (); 
    
    //[WORKING] sets the user's rented movie to m
    //Note: if there's already a rented movie, do nothing
    void rentMovie (Movie *m);
    
    //[WORKING] returns the user's rented movie
    //Note: if there's no rented movie, do nothing
    void returnMovie();
    
    //[WORKING] returns user's checked out movie.
    //Note: returns NULL if no movie is checked out
    Movie* currentMovie();
    
    queue<Movie*> userQueue;			//
    Movie* checkedOut;					//
    set<Movie*> ratedMovies;			//A set of movies rated by this user
    set<Movie*> notRatedMovies;			//A set of movies not rated by this user
    map<Movie*, int> myRatings;			//Relates the movie ptr and this user's ratings
    map<User*, double> similarities; 	//Relates the other user's ptr and the similarity value
    
    Movie* recommended;
    
    string address;
    string cc_number;
    int charges;
    string password;

  private:
    string ID;
    string name;
   

};

#endif