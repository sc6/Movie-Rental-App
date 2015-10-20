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
Movie* searchTitle (string title, map<string, Movie*> & list)
{
	title = makeLowercase(title);
	string prev = "";	
	
	for(map<string, Movie*>::iterator mi = list.begin(); mi != list.end(); ++mi)
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
set<Movie*>* searchKeyword (string keyword, map<string, set<Movie*>*> & list)
{
	keyword = makeLowercase(keyword);
	string prev = "";	
	
	for(map<string, set<Movie*>*>::iterator mi = list.begin(); mi != list.end(); ++mi)
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
	if(line.length() >= 10 && line.substr(0,10) == "BEGIN INFO") return "BEGIN INFO";
	if(line.length() >= 8 && line.substr(0,8) == "END INFO") return "END INFO";
	if(line.length() >= 13 && line.substr(0,13) == "BEGIN RATINGS") return "BEGIN RATINGS";
	if(line.length() >= 11 && line.substr(0,11) == "END RATINGS") return "END RATINGS";
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
					map<string, User*> & map_of_users_B, 
					map<string, Movie*> map_of_movies) 
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
				continue;
			}
			else if(data_keyword == "MOVIE") {
				buildUser->checkedOut = searchTitle(getValue(userScrape).substr(1), map_of_movies);
			}
			else if(data_keyword == "BEGIN QUEUE") {
				string addToQueue;
				getline(user_data_file, addToQueue);
				while(addToQueue != "END QUEUE")
				{
					buildUser->userQueue.push(searchTitle(addToQueue, map_of_movies));
					getline(user_data_file, addToQueue);
				}
			}
			else if(data_keyword == "BEGIN RATINGS") {
				int movieRating;
				string addToRatings;
				getline(user_data_file, addToRatings);
				while(addToRatings != "END RATINGS") 
				{
					int slength = addToRatings.length();
					movieRating = atoi(addToRatings.substr(0,1).c_str());
					addToRatings = addToRatings.substr(2,slength-2);
					
					//cerr << movieRating << ", " << addToRatings << endl;
					
					Movie* ptr_input = searchTitle(addToRatings, map_of_movies);
					buildUser->myRatings.insert(std::pair<Movie*, int>(ptr_input, movieRating));	
					buildUser->ratedMovies.insert(ptr_input);
					
					getline(user_data_file, addToRatings);
				}
			}
			else if (data_keyword == "BEGIN INFO") {
				string current_info;
				
				int counter = 0;
				
				//getline(user_data_file, current_info);
				getline(user_data_file, current_info);
				
				while(current_info != "END INFO") 
				{
					if(counter == 0) {
						//cerr << "Address: " << current_info << endl;
						buildUser->address = current_info;
					}
					else if(counter == 1) {
						//cerr << "CC: " << current_info << endl;
						buildUser->cc_number = current_info;
					}
					else if(counter == 2) {
						//cerr << "charge: " << current_info << endl;
						buildUser->charges = atoi(current_info.c_str());
					}
					else {
						//cerr << "password: " << current_info << endl;
						buildUser->password = current_info;
					}
					
					getline(user_data_file, current_info);
					counter++;
				}
			}
			else if(data_keyword == "END") {
				initialization = true;
				map_of_users_B.insert(std::pair<string, User*>(userID, buildUser));
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
						map<string, Movie*> & map_of_movies_B, 
						map<string, set<Movie*>*> & map_of_keywords_B,
						map<string, set<Movie*>*> & map_of_actors)
{
	string movieScrape;
	string movieName, movieKeyword, movieActor;
	Movie* buildMovie;
	set<string> movieKeywords;
	set<string> movieActors;
	set<Movie*>* buildSet;
	
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
			else if(data_keyword == "ACTOR") {
				movieActor = getValue(movieScrape).substr(1);
				buildMovie->addActor(movieKeyword);
				//cerr << "added actor: " << movieActor << endl;
			}
			else if(data_keyword == "PRICE") {
				buildMovie->price = atoi((getValue(movieScrape).substr(1)).c_str());
				//cerr << "Added price: $" << buildMovie->price << ".00" << endl;
			}
			else if(data_keyword == "END") {
				initialization = true;
				
				//add to map_of_movies
				map_of_movies_B.insert(std::pair<string,Movie*>(movieName, buildMovie));
				
				//add to map_of_keywords
				movieKeywords = buildMovie->getAllKeywords();
				
				for(set<string>::iterator si = movieKeywords.begin(); si != movieKeywords.end(); ++si)
				{
					buildSet = new set<Movie*>();
					movieKeyword = *si;
					
					map_of_keywords_B.insert(std::pair<string, set<Movie*>*>(movieKeyword, buildSet));	//if already exists, does nothing
					buildSet = map_of_keywords_B.at(movieKeyword);
					buildSet->insert(buildMovie);
				}
				
				//add to map_of_actors
				movieActors = buildMovie->getAllActors();
				
				for(set<string>::iterator si = movieActors.begin(); si != movieActors.end(); ++si)
				{
					buildSet = new set<Movie*>();
					movieKeyword = *si;
					
					map_of_actors.insert(std::pair<string, set<Movie*>*>(movieActor, buildSet));	//if already exists, does nothing
					buildSet = map_of_actors.at(movieActor);
					buildSet->insert(buildMovie);
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
