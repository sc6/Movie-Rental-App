#ifndef NETFLIX_CPP
#define NETFLIX_CPP

using namespace std;
	
//[todo] Netflix constructor
inline Netflix::Netflix()
{
	map_of_users = map<string, User*>();
	map_of_movies = map<string, Movie*>();
	map_of_keywords = map<string, set<Movie*>*>();
	
	currentUser = "Not Logged In";
	currentUserObj = new User("Not Logged In", "Not Logged In");
}

//[todo] Logs the user into Netflix if userid is valid
inline bool Netflix::loginUser(string user, string password)
{	
	try {
		//cerr << map_of_users.at(user)->password << " == " << md5(password) << " == " << md5("test") << endl;
		if(map_of_users.at(user) != NULL && map_of_users.at(user)->password == md5(password)) { 
			//cerr << map_of_users.at(user)->password << " == " << md5(password) << endl;
			return true;
		}
	}
	catch (exception &e){
		return false;
		
	}
	
	return false;
}

//[WORKING] Populates map_of_users
inline void Netflix::importUsers(map<string, User*> & m) 
{ map_of_users = m; }

inline void Netflix::importMovies(map<string, Movie*> & m)
{ map_of_movies = m; }

inline void Netflix::importKeywords(map<string, set<Movie*>*> & m)
{ map_of_keywords = m; }

inline void Netflix::importUserFileOutput(ofstream * user_append_data)
{ this->user_append_data = user_append_data; }

inline void Netflix::setCurrentUser(string user) 
{ this->currentUser = user; }

inline string Netflix::showCurrentUser()
{ return this->currentUser; }

inline string Netflix::showCurrentMovie()
{	
	if(currentUserObj->getID() == "Not Logged In") {
		currentUserObj = map_of_users.at(currentUser);
	}
	
	if(currentUserObj->currentMovie())
		return currentUserObj->currentMovie()->getTitle();
	else return "nothing";
}

inline User* Netflix::showCurrentUserObj()
{ return currentUserObj; }

inline Movie* Netflix::searchTitle(string movieTitle) 
{
	movieTitle = makeLowercase(movieTitle);
	string prev = "";
	
	for(map<string, Movie*>::iterator mi = this->map_of_movies.begin(); mi != this->map_of_movies.end(); ++mi)
	{
		if(makeLowercase((*mi).first) == movieTitle) {
			return (*mi).second;
		}
		else if(makeLowercase((*mi).first) == prev) {
			return NULL; //detects cycle
		}
		else {
			prev = makeLowercase((*mi).first);
		}
	}
	
	return NULL;
}

inline set<Movie*>* Netflix::searchKeyword(string movieKeyword) 
{
	movieKeyword = makeLowercase(movieKeyword);
	string prev = "";	
	
	for(map<string, set<Movie*>*>::iterator mi = map_of_keywords.begin(); mi != map_of_keywords.end(); ++mi)
	{
		if(makeLowercase((*mi).first) == movieKeyword) {
			return (*mi).second;
		}
		else if(makeLowercase((*mi).first) == prev) {
			return NULL; //detects cycle
		}
		else {
			prev = makeLowercase((*mi).first);
		}
	}
	
	return NULL;
}

inline string Netflix::makeLowercase(string s) {

	char c;
	
	for(unsigned int i = 0; i < s.length(); i++)
	{
		c = s[i];
		c = tolower(c);
		s[i] = c;
	}
	
	return s;
}

//saves files
inline void Netflix::userLogOut() 
{
	string userFilename = "data/users.txt";
	ofstream current_user_file(userFilename.c_str());
	
	//for each user
	for(map<string, User*>::iterator mI = map_of_users.begin(); mI != map_of_users.end(); ++mI)
	{
		//id
		current_user_file << "BEGIN " << (*mI).second->getID() << endl;
		
		//name
		current_user_file << "NAME: " << (*mI).second->getName() << endl;
		
		//movie rented
		if((*mI).second->checkedOut) current_user_file << "MOVIE: " << (*mI).second->checkedOut->getTitle() << endl;
	
		//queue
		current_user_file << "BEGIN QUEUE" << endl;
		
		while(true) {
			if((*mI).second->movieQueue()->empty()) break;
			current_user_file << (*mI).second->movieQueue()->front()->getTitle() << endl;
			(*mI).second->movieQueue()->pop();
		}
		
		current_user_file << "END QUEUE" << endl;
		
		//ratings
		current_user_file << "BEGIN RATINGS" << endl;
		
		for(map<Movie*, int>::iterator mI2 = (*mI).second->myRatings.begin(); mI2 != (*mI).second->myRatings.end(); ++mI2)
		{
			current_user_file << (*mI2).second << " ";
			current_user_file << (*mI2).first->getTitle() << endl;
		}
		
		current_user_file << "END RATINGS" << endl;
		
		//info
		current_user_file << "BEGIN INFO" << endl;
		
		current_user_file << mI->second->address << endl;
		current_user_file << mI->second->cc_number << endl;
		current_user_file << mI->second->charges << endl;
		current_user_file << mI->second->password << endl;
		
		current_user_file << "END INFO" << endl;
		
		//end
		current_user_file << "END" << endl;
	
	}
}


inline double Netflix::compareUsers(User* a, User* b)
{
	set<Movie*> movieMatches = set<Movie*>();
	
	//movieMatches = (a->ratedMovies).set_intersection(b->ratedMovies);
	
	set_intersection(a->ratedMovies.begin(), a->ratedMovies.end(), b->ratedMovies.begin(), b->ratedMovies.end(), inserter(movieMatches, movieMatches.begin()));
	
	double similarityFactor = 0;
	
	for(set<Movie*>::iterator sI = movieMatches.begin(); sI != movieMatches.end(); ++sI)
	{
		double rating_a = a->myRatings.at(*sI);
		double rating_b = b->myRatings.at(*sI);
		
		similarityFactor += abs(rating_a - rating_b)/4;
	}
			
	if (movieMatches.size() > 0) return similarityFactor/movieMatches.size();
	return 0;
}


//calculates and sets the best match movie to the input user.
inline Movie* Netflix::calculateRecommendation(User* a)
{
	Movie* recommended_movie = new Movie("No recommendations available");
	
	//sets user's not rated list
	for(map<string, Movie*>::iterator mI = map_of_movies.begin(); mI != map_of_movies.end(); ++mI)
	{
		Movie* ptr_input = (*mI).second;
		a->notRatedMovies.insert(ptr_input);
		
		for(set<Movie*>::iterator sI = a->ratedMovies.begin(); sI != a->ratedMovies.end(); ++sI)
		{
			if((*mI).first == (*sI)->getTitle()) {
				a->notRatedMovies.erase((*mI).second);
				break;
			}
		}
	}
	
	double max_interest_factor = 0;
	
	//calculates recommendation factor for each movie in user's not rated set
	for(set<Movie*>::iterator sI = a->notRatedMovies.begin(); sI != a->notRatedMovies.end(); ++sI)
	{ //cycles each movie in user's 'not rated' set
		Movie* currentMovie = *sI;
		double r_function = 0;
		double w_function = 0;
		for(set<User*>::iterator sIB = currentMovie->usersRated.begin(); sIB != currentMovie->usersRated.end(); ++sIB)
		{ //cycles each user who've rated this movie
			if((*sIB)->getID() == a->getID()) break;
			
			double similarity_factor = a->similarities.at(*sIB);
			double rating_factor = (*sIB)->myRatings.at(currentMovie);
			
			w_function += (1-similarity_factor);
			r_function += w_function * rating_factor;
		}
		
		if((w_function == 0) && (max_interest_factor == 0)) recommended_movie = currentMovie;
		else if((r_function/w_function) > max_interest_factor) {
			recommended_movie = currentMovie;
			max_interest_factor = (r_function/w_function);
		}
	}
	return recommended_movie;
}




#endif