


//*** SET UP ***

//variables for log in
string user_menu_input_id;
string logged_user_id;
User *current_user = NULL;
bool logged_in = false;

cout << "\nEnter your user id: ";
cin >> user_menu_input_id;
cout << endl;

//logs the user in if id exists
if(map_of_users.size() != 0) {
	try 
	{
		if(user_menu_input_id == map_of_users.get(user_menu_input_id)->getID())
		{
			cout << "You've successfully logged in as " << user_menu_input_id << "." << endl;
			logged_user_id = user_menu_input_id;
			current_user = map_of_users.get(user_menu_input_id);
			logged_in = true;
		}
	}
	catch (NoSuchElementException & e) 
	{
		cout << "User doesn't exist." << endl;
	}
}
else cout << "User doesn't exist." << endl;


//*** MENU ***

while(logged_in) //logged in menu
{
	while(true) //menu prompt
	{
		cout << "\n===== " << current_user->getID() << " =====" << endl;
		displayRented(current_user);
		cout << "1. Search for a movie by title" << endl;
		cout << "2. Search for a movie by keyword" << endl;
		cout << "3. Return the current movie" << endl;
		cout << "4. View Queue" << endl;
		cout << "5. Logout" << endl;
		cout << "Enter a number: ";
		cin >> user_menu_input;
		cout << endl;
		
		if(cin.good() && user_menu_input <= 5) break;
					
		else {
			cout << "Try again. Acceptable inputs are: 1, 2, 3, 4, 5." << endl;
			cin.clear();
			cin.ignore();
		}
	}
	
	//cleans cin
	cin.clear();
	cin.ignore();
	
	
	if(user_menu_input == 1)	//find movie by title
	{	
		Movie* found_movie;
		string search_this_title;
		
		cout << "\nEnter a title: ";
		std::getline(cin, search_this_title);
		cout << endl;
		
		//cout << "Entered: '" << search_this_title << "'" << endl;
		cout << "\nResults:" << endl;
		
		//Search algorithm
		Map<string, Movie*> *workaround_temp = new Map<string,Movie*>(map_of_movies);
		found_movie = searchTitle(search_this_title, *workaround_temp);
		
		//Prints result
		if(found_movie == NULL) {
			cout << "No movie found." << endl;
		}
		else {
			//title
			cout << found_movie->getTitle() << endl;
			
			//keywords
			Set<string> temp_set_3;
			temp_set_3 = found_movie->getAllKeywords();
			
			for(Set<string>::Iterator si = temp_set_3.begin(); si != temp_set_3.end(); ++si)
			{
				cout << si.current->key << endl;
			}		
			
		}
	}
	
	else if(user_menu_input == 2)	//find movie by keyword
	{
		
		string search_this_keyword;
		Set<Movie*>* found_set;
			
		cout << "\nEnter a keyword: ";
		std::getline(cin, search_this_keyword);
		cout << endl;
			
		
		//cout << "Entered: '" << search_this_keyword << "'" << endl;
		//cout << "\nResults:" << endl;
		
		//Search algorithm
		Map<string, Set<Movie*>*> *workaround_temp_B = new Map<string, Set<Movie*>*>(map_of_keywords);
		found_set = searchKeyword(search_this_keyword, *workaround_temp_B);
		
		//Prints result
		if(found_set == NULL) { //no movie found, attempts to find keyword == title
				
			Map<string, Movie*> *workaround_temp_C = new Map<string,Movie*>(map_of_movies);
			Movie* found_movie_B = searchTitle(search_this_keyword, *workaround_temp_C);
								
			if(found_movie_B == NULL) { 
				cout << "No match" << endl;
			}
			else {
				//title
				cout << found_movie_B->getTitle() << endl;
				
				//keywords
				Set<string> temp_set_4;
				temp_set_4 = found_movie_B->getAllKeywords();
				
				for(Set<string>::Iterator si = temp_set_4.begin(); si != temp_set_4.end(); ++si)
				{
					cout << si.current->key << endl;
				}
				
				//break;
			}
		}
				
		else {
			cout << "Matches: " << endl;
			for(Set<Movie*>::Iterator si = (*found_set).begin(); si != (*found_set).end(); ++si)
			{
				cout << si.current->key->getTitle() << endl;
			}
		
		
			cout << endl;
			int tempCounter = 0;
			for(Set<Movie*>::Iterator si = (*found_set).begin(); si != (*found_set).end(); ++si)
			{
				tempCounter++;
				Movie* tempMoviePtr = si.current->key;
				cout << tempMoviePtr->getTitle() << endl;	//title
				Set<string> keyword_set_C = tempMoviePtr->getAllKeywords();	//keywords
				
				//keywords print loop
				for(Set<string>::Iterator si2 = keyword_set_C.begin(); si2 != keyword_set_C.end(); ++si2) {
					cout << si2.current->key << endl;
				}
				
				//menu
				if(found_set->size() > 1 && tempCounter < found_set->size()) { 
					int user_menu_input_C;
					while(true) {
						cout << endl;
						cout << "== " << found_set->size() << " matches, current: " << tempMoviePtr->getTitle() << "  ==" << endl;
						cout << "1. Next movie" << endl;
						cout << "2. Add movie to queue" << endl;
						cout << "3. Return to menu" << endl;
						cout << "Enter a number: ";
						cin >> user_menu_input_C;
						cout << endl;
						
						if(cin.good() && user_menu_input_C <= 3) {
							if(user_menu_input_C == 1) {	//lookup next movie
								cout << "Next movie:" << endl;
								break;
							}
							else if (user_menu_input_C == 2) {
								current_user->userQueue.enqueue(tempMoviePtr); //add movie ptr to queue
								cout << "Movie added to queue!\n" << endl;
							}
							else {	//return to menu
								break;
							}
							
						}
						
						else {
							cout << "Try again. Acceptable inputs are: 1, 2, 3." << endl;
							cin.clear();
							cin.ignore();
						}
					}
					if(user_menu_input_C == 3) break;
				}
				
				else {	//no next movie
					int user_menu_input_C;
					while(true) {
						cout << endl;
						cout << "== " << found_set->size() << " match(es), current: " << tempMoviePtr->getTitle() << "  ==" << endl;
						cout << "1. Add movie to queue" << endl;
						cout << "2. Return to menu" << endl;
						cout << "Enter a number: ";
						cin >> user_menu_input_C;
						cout << endl;
						
						if(cin.good() && user_menu_input_C <= 2) {
							if(user_menu_input_C == 1) {	//lookup next movie
								current_user->userQueue.enqueue(tempMoviePtr); //add movie ptr to queue
								cout << "Movie added to queue!\n" << endl;
							}
							else {	//return to menu
								break;
							}
						}
											
						else {
							cout << "Try again. Acceptable inputs are: 1, 2." << endl;
							cin.clear();
							cin.ignore();
						}
					}
					if (user_menu_input_C == 2) break;
				}
			}
		}
		
		
	}
	
	else if(user_menu_input == 3) {	//return the current movie
		
		current_user->returnMovie();
		cout << "You now have no rented movies!" << endl;
	}
	
	else if(user_menu_input == 4) { 	//view queue
		bool movieQueueEmpty = false;
		Queue<Movie*>* current_user_queue_ptr;
		int queue_menu_input;
		while(true) { //view queue 
			while(true) //queue menu prompt
			{
				try { 	current_user_queue_ptr = current_user->movieQueue();
						cout << "\n==< Action: " << current_user_queue_ptr->peekFront()->getTitle() << " >==" << endl;
				}
				catch (EmptyQueueException & e) {
					cout << "\n-- Movie queue empty --" << endl;
					movieQueueEmpty = true;
				}
				
				cout << "1. Order movie" << endl;
				cout << "2. Remove movie from queue" << endl;
				cout << "3. Move movie to back of queue" << endl;
				cout << "4. Return to user menu" << endl;
				cout << "Enter a number: ";
				cin >> queue_menu_input;
				cout << endl;
				
				if(cin.good() && queue_menu_input <= 4) break;
							
				else {
					cout << "Try again. Acceptable inputs are: 1, 2, 3, 4." << endl;
					cin.clear();
					cin.ignore();
				}
			}
	
	
			//cleans cin
			cin.clear();
			cin.ignore();
			
			
			if(queue_menu_input == 1)	//Order movie
			{
				if(!(current_user->checkedOut) && !(movieQueueEmpty)) 
				{
					current_user->checkedOut = current_user->movieQueue()->peekFront();
					current_user->movieQueue()->dequeue();
					cout << "Movie ordered" << endl;
				}
				else cout << "You already have a movie rented out or there is no movie selected." << endl;
				
				break;
			}
			
			else if(queue_menu_input == 2)	//Remove movie from queue
			{
				if(!(movieQueueEmpty)) {
					current_user->movieQueue()->dequeue();
					cout << "Removed movie from queue." << endl;
				}
				else cout << "Your queue is empty; nothing to remove." << endl;
			}
			
			else if(queue_menu_input == 3)	//Move movie to back of queue
			{
				if(!(movieQueueEmpty)) {
					Movie* tempMovieToQueue = current_user->movieQueue()->peekFront();
					current_user->movieQueue()->dequeue();
					current_user->movieQueue()->enqueue(tempMovieToQueue);
					cout << "Moved movie to back of queue" << endl;
				}
				else cout << "Your queue is empty; nothing to postpone." << endl;
			}
			
			else	//Return to user menu
			{
				break;
			}
			
		}	
	}//view queue ends
	
	else	//log out
	{
		cout << "You have successfully logged out." << endl;
		userLogOut(map_of_users);
		cout << "Your queue has been saved in data/users.txt" << endl;
		break;
	}
}