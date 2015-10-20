//version final(2)

#include "User.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>


//returns all-lowercased string
string makeLowercase(string str) {
	
	//int length = str.length();
	char c;
	
	for(unsigned int i = 0; i < str.length(); i++)
	{
		c = str[i];
		c = tolower(c);
		str[i] = c;
	}
	
	return str;
}

//searches for the movie given a title
Movie* searchTitle (string title, Map<string, Movie*> & list)
{
	title = makeLowercase(title);
	string prev = "";	
	
	for(Map<string, Movie*>::Iterator mi = list.begin(); mi != list.end(); ++mi)
	{
		if(makeLowercase((*mi).first) == title) {
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

//searches for the movie set given a key
Set<Movie*>* searchKeyword (string keyword, Map<string, Set<Movie*>*> & list)
{
	keyword = makeLowercase(keyword);
	string prev = "";	
	
	for(Map<string, Set<Movie*>*>::Iterator mi = list.begin(); mi != list.end(); ++mi)
	{
		if(makeLowercase((*mi).first) == keyword) {
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


//Gets data_keyword from the given (data-scraped) line
string getKeyword (string line) 
{
	//unsigned int lineLength = line.length();
	
	if(line.length() >= 11 && line.substr(0,11) == "BEGIN QUEUE") return "BEGIN QUEUE";
	if(line.length() >= 9 && line.substr(0,9) == "END QUEUE") return "END QUEUE";
	if(line.length() >= 3 && line.substr(0,3) == "END") return "END";
	if(line.length() >= 5 && line.substr(0,5) == "BEGIN") return "BEGIN";

	int end = line.find(":");
	
	string s = line.substr(0, end);

	return s;
}


//Gets data_value from the given (data-scraped) line
string getValue (string line)
{
	unsigned int lineLength = line.length();
	int start = 0;
	
	if(line.substr(0,5) == "BEGIN") return line.substr(line.find("BEGIN") + 6);
	
	else start = line.find(":") + 1;

	int strLength = 0;

	while((unsigned)(strLength) < lineLength)
		strLength++;

	string s = line.substr(start, strLength);

    return s;
}


//Finds and opens the data files.
void openFiles(		ifstream & data_file_B,
					ifstream & user_data_file_B,
					ifstream & movie_data_file_B,
					ofstream & user_append_data_B,
					ofstream & movie_append_data_B,
					const char * data_file_name		) 
{

	//Find and open the data file.
	string data_file_directory = "data/";

	data_file_directory.append(data_file_name);

	//cout << "Opening '" << data_file_directory << "'... ";
	data_file_B.open(data_file_directory.c_str());	
	//cout << "[success]" << endl;

	
	//Find and open the user file.
	string user_file_name;
	string user_file_directory = "data/";
	
	getline(data_file_B, user_file_name);
	
	user_file_directory.append(user_file_name);
	
	//cout << "Opening '" << user_file_directory << "'... ";
	user_data_file_B.open(user_file_directory.c_str());
	user_append_data_B.open(user_file_directory.c_str(), std::ios::app);
	//cout << "[success]" << endl;
	
	
	//Find and open the user file.
	string movie_file_name;
	string movie_file_directory = "data/";
	
	getline(data_file_B, movie_file_name);
	
	movie_file_directory.append(movie_file_name);
	
	//cout << "Opening '" << movie_file_directory << "'... ";
	movie_data_file_B.open(movie_file_directory.c_str());
	movie_append_data_B.open(movie_file_directory.c_str(), std::ios::app);
	//cout << "[success]" << endl;	
}

	
void processUsers(	ifstream & user_data_file, 
					Map<string, User*> & map_of_users_B, 
					Map<string, Movie*> map_of_movies) 
{ 
	
	string userScrape;
	string userID, userName;
	User* buildUser;
	
	bool initialization = true;
	
	while(!user_data_file.eof()) { //todo: this doesnt detect endOfFile. Workaround: breaking when != BEGIN
		string data_keyword = "", data_value = "";
		
		getline(user_data_file, userScrape);
		
		if(initialization) {	//run once for BEGIN
			initialization = false;
			
			stringstream ss;
			ss << userScrape;
			ss >> data_keyword >> userID;
			
			//first line should always get 'BEGIN userid'
			if(data_keyword != "BEGIN") break; //{cout << "user data might not be formatted correctly." << endl; break; }
		}
		else {
			data_keyword = getKeyword(userScrape); 	
			
			if(data_keyword == "NAME") {
				userName = getValue(userScrape).substr(1);	//workaround: substr removes a leading space
				buildUser = new User(userID, userName);
			}
			else if(data_keyword == "BEGIN QUEUE") {
				string addToQueue;
				getline(user_data_file, addToQueue);
				while(addToQueue != "END QUEUE")
				{
					buildUser->userQueue.enqueue(searchTitle(addToQueue, map_of_movies));
					getline(user_data_file, addToQueue);
				}
			}
			else if(data_keyword == "END") {
				initialization = true;
				map_of_users_B.add(userID, buildUser);
				//cout << "+ Added: '" << userID << "' '" << userName << "'" << endl;
			}
			else {
				cout << "user data might not be formatted correctly." << endl; 
				break;
			}	
		}		
	}
}


void processMovies (	ifstream & movie_data_file_B, 
						Map<string, Movie*> & map_of_movies_B, 
						Map<string, Set<Movie*>*> & map_of_keywords_B	)
{
	string movieScrape;
	string movieName, movieKeyword;
	Movie* buildMovie;
	Set<string> movieKeywords;
	Set<Movie*>* buildSet;
	
	bool initialization = true;
	
	while(!movie_data_file_B.eof()) { //todo: this doesnt detect endOfFile. Workaround: breaking when != BEGIN
		string data_keyword = "", data_value = "";
				
		getline(movie_data_file_B, movieScrape);
		
		if(initialization) {	//run once for BEGIN
			initialization = false;
			
			stringstream ss;
			ss << movieScrape;
			ss >> data_keyword;
			movieName = getValue(movieScrape);
			
			//first line should always get 'BEGIN: movieName'
			if(data_keyword != "BEGIN") break; //{cout << "movie data might not be formatted correctly." << endl; break; }
		
			buildMovie = new Movie(movieName);
			//cout << "+ Created new movie: '" << movieName << "'" << endl;
		}
		else {
			data_keyword = getKeyword(movieScrape); 	
			
			if(data_keyword == "KEYWORD") {
				movieKeyword = getValue(movieScrape).substr(1);	//workaround: substr removes a leading space
				buildMovie->addKeyword(movieKeyword);
				//cout << "\t Added keyword: '" << movieKeyword << "'" << endl;
			}
			else if(data_keyword == "END") {
				initialization = true;
				
				//add to map_of_movies
				map_of_movies_B.add(movieName, buildMovie);
				
				//add to map_of_keywords
				movieKeywords = buildMovie->getAllKeywords();
				
				for(Set<string>::Iterator si = movieKeywords.begin(); si != movieKeywords.end(); ++si)
				{
					buildSet = new Set<Movie*>();
					movieKeyword = si.current->key;
					
					map_of_keywords_B.add(movieKeyword, buildSet);	//if already exists, does nothing
					buildSet = map_of_keywords_B.get(movieKeyword);
					buildSet->add(buildMovie);
				}
			}
			else {
				cout << "user data might not be formatted correctly." << endl; 
				break;
			}
	
		}	
		
	}	
}


void displayRented (User* currentUserB)
{
	if(currentUserB->checkedOut) cout << "<Rented: " << currentUserB->checkedOut->getTitle() << ">" << endl;
	else cout << "<No movie checked out>" << endl;
}

void userLogOut(Map<string, User*> & map_of_users) 
{
	string userFilename = "data/users.txt";
	ofstream current_user_file(userFilename.c_str());
	
	//for each user
	for(Map<string, User*>::Iterator mI = map_of_users.begin(); mI != map_of_users.end(); ++mI)
	{
		//id
		current_user_file << "BEGIN " << mI.current->value->getID() << endl;
		
		//name
		current_user_file << "NAME: " << mI.current->value->getName() << endl;
		
		//movie rented
		if(mI.current->value->checkedOut) current_user_file << "MOVIE: " << mI.current->value->checkedOut->getTitle() << endl;
	
		//queue
		current_user_file << "BEGIN QUEUE" << endl;
		
		while(true) {
			try {
				current_user_file << mI.current->value->movieQueue()->peekFront()->getTitle() << endl;
			}
			catch(EmptyQueueException & e) {
				break;
			}
			mI.current->value->movieQueue()->dequeue();
		}
		
		current_user_file << "END QUEUE" << endl;
		
		//end
		current_user_file << "END" << endl;
	
	}
}	cout << "Size of map_of_users: " << map_of_users.size() << endl;



int main (int argc, char * argv[]) {
	
	//data types to keep track of users, movies, movie keywords
	Map<string, User*> map_of_users = Map<string, User*>();
	Map<string, Movie*> map_of_movies = Map<string, Movie*>();
	Map<string, Set<Movie*>*> map_of_keywords = Map<string, Set<Movie*>*>();
	
	//variables for data files
	ifstream data_file, user_data_file, movie_data_file;
	ofstream user_append_data, movie_append_data;
	
	//function finds and opens data.txt users.txt movies.txt
	openFiles(data_file, user_data_file, movie_data_file, user_append_data, movie_append_data, argv[1]);
	
	//error checks to see if file was properly opened
	if (!data_file.is_open()) {
		cout << "Could not open data file; command should be something like: './bin/movie_app filename.txt'" << endl;
		exit(30);
	}
	
	if (!(user_data_file).is_open()) {
		cout << "Could not open user data file; make sure line 1 of data file only contains something like 'userdata.txt'" << endl;
		exit(40);
	}
	
	if (!(movie_data_file).is_open()) {
		cout << "Could not open movie data file; make sure line 2 of data file only contains something like 'moviedata.txt'" << endl;
		exit(50);
	}
	
	//this creates the movie objects and then stores all of them in a map<moviename, movie obj*>
	//this also takes keywords from the movie and stores them in a map<keyword, set<movie*>*>
	processMovies(movie_data_file, map_of_movies, map_of_keywords);
	
	//this creates the user objects and then stores all of them in a map<userid, user obj*>
	processUsers(user_data_file, map_of_users, map_of_movies);

	//sanity check
	//cout << "Size of map_of_users: " << map_of_users.size() << endl;
	//cout << "Size of map_of_movies: " << map_of_movies.size() << endl;
	//cout << "Size of map_of_keywords: " << map_of_keywords.size() << endl;
	
	//start menu (not logged in)
	int user_menu_input;
	
	while(true) //program loop
	{
		while(true) //menu loop
		{
			cout << "\n===== Movie App =====" << endl;
			cout << "1. Log in" << endl;
			cout << "2. Create a new user" << endl;
			cout << "3. Quit" << endl;
			cout << "Enter a number: ";
			cin >> user_menu_input;
			cout << endl;
			
			if(cin.good() && user_menu_input < 4) break; //breaks from menu once input is validated
			
			else {
				cout << "Try again. Acceptable inputs are: 1, 2, 3." << endl;
				cin.clear();
				cin.ignore();
			}
		}
		
		//cleans cin
		cin.clear();
		cin.ignore();
		
		if(user_menu_input == 1) //log in
		{
			//Display the logged-in menu
			#include "snippets/logged_in_menu.cpp"
		}
		else if(user_menu_input == 2) //create a new user
		{
			//Code to create new user
			#include "snippets/create_new_user.cpp"
		}
		else {	//quit program
			//todo: make an exit_program function
			cout << "Quitting..." << endl;
			exit(300);
		}
	}
	
	
	
	//closing files
	data_file.close();
	user_data_file.close();
	movie_data_file.close();
	user_append_data.close();
	movie_append_data.close();
	
	cout << "End of movie_app_tester" << endl;
}