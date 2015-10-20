#include <QApplication>

#include "LoginWindow.h"	//netflix included in this
#include "MainWindow.h"
#include "UIWindow.h"



#include <iostream>
using namespace std;


#include "nec-functions.cpp"


int main (int argc, char * argv[])
{
	//Data
	map<string, User*> map_of_users = map<string, User*>();
	map<string, Movie*> map_of_movies = map<string, Movie*>();
	map<string, set<Movie*>*> map_of_keywords = map<string, set<Movie*>*>();
	map<string, set<Movie*>*> map_of_actors = map<string, set<Movie*>*>();
	
	ifstream data_file, user_data_file, movie_data_file;
	ofstream user_append_data, movie_append_data;
	
	//function finds and opens data.txt users.txt movies.txt
	openFiles(data_file, user_data_file, movie_data_file, user_append_data, movie_append_data, argv[1]);
	
	//this creates the movie objects and then stores all of them in a map<moviename, movie obj*>
	//this also takes keywords from the movie and stores them in a map<keyword, set<movie*>*>
	processMovies(movie_data_file, map_of_movies, map_of_keywords, map_of_actors);
	
	//this creates the user objects and then stores all of them in a map<userid, user obj*>
	processUsers(user_data_file, map_of_users, map_of_movies);
	
	//sanity check
//	cerr << "Size of map_of_users: " << map_of_users.size() << endl;
//	cerr << "Size of map_of_movies: " << map_of_movies.size() << endl;
//	cerr << "Size of map_of_keywords: " << map_of_keywords.size() << endl;
	

	//creating netflix and passing the data above
	Netflix netflix = Netflix();
	netflix.importUsers(map_of_users);
	netflix.importMovies(map_of_movies);
	netflix.importKeywords(map_of_keywords);
	netflix.importUserFileOutput(&user_append_data);
	

	//set similaries for all users <could be made more efficient>
	for(map<string, User*>::iterator mIA = netflix.map_of_users.begin(); mIA != netflix.map_of_users.end(); ++mIA)
	{
		for(map<string, User*>::iterator mIB = netflix.map_of_users.begin(); mIB != netflix.map_of_users.end(); ++mIB)
		{
			if((*mIA).second->getID() == (*mIB).second->getID()) continue;
			
			User* ptr_input = (*mIB).second;
			double factor_input = netflix.compareUsers((*mIA).second, (*mIB).second);
			(*mIA).second->similarities.insert(std::pair<User*, double>(ptr_input, factor_input));
		}
	}
	
	//creates a set of people who've rated the movie for all movies
	for(map<string, User*>::iterator mI = netflix.map_of_users.begin(); mI != netflix.map_of_users.end(); ++mI)
	{
		for(map<Movie*, int>::iterator mIB = (*mI).second->myRatings.begin(); mIB != (*mI).second->myRatings.end(); ++mIB)
		{
			User* ptr_input = (*mI).second;
			(*mIB).first->usersRated.insert(ptr_input);
			//cerr << "User " << (*mI).second->getID() << " added to " << (*mIB).first->getTitle() << endl;
		}
	}		
	
	QApplication app(argc, argv);
	
	MainWindow * startw = new MainWindow(&netflix, 0);
		
	startw->setWindowTitle("Movie App (Not logged in)");
	startw->show();
	
	//done above when login check is successful
	//UIWindow * mainw = new UIWindow(&netflix, 0);
	//mainw->setWindowTitle("Movie App (Logged in)");
	
	
	
	return app.exec();
}