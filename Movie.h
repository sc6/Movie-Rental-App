#ifndef MOVIE_CLASS_INCLUDED
#define MOVIE_CLASS_INCLUDED

#include "lib/proj_required.h"

class User;


class Movie {
  public: 
    Movie (string title);       // constructor for a movie with the given title

    Movie (const Movie & other);  // copy constructor

    ~Movie ();                  // destructor

    string getTitle () const;   // returns the title of the movie

    void addKeyword (string keyword); 
      /* Adds the (free-form) keyword to this movie.
         If the exact same keyword (up to capitalization) was already
         associated with the movie, then the keyword is not added again. */

    std::set<string> getAllKeywords () const;
      /* Returns a set of all keywords associated with the movie. */
    
    void addActor (string actor);
    
    std::set<string> getAllActors() const;

    set<User*> usersRated;	//set of users who have rated this movie.
    int price;	//price of the movie
    
  private:
    
    string title;
    set<string> keywords;
    set<string> actors;

};

#endif
