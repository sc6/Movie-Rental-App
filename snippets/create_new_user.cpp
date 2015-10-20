			string new_user_id, new_user_name;
			User* new_user_build;
			
			//prompts for new_user_id
			while (true) {
				cout << "\nEnter a user id: ";
				cin >> new_user_id;
				cout << endl;
				
				try{
					if(map_of_users.size() != 0) {
						if(new_user_id == map_of_users.get(new_user_id)->getID())
						{
							cout << "That name already exists in the database." << endl;
						}
					}
				}
				catch (NoSuchElementException & e) { //if caught, new_user_id is unique
					 break;							 //breaks prompt
				}
			}
			
			//gets user's name
			cout << "\nEnter your name: ";
			cin.ignore();
			std::getline(cin, new_user_name);
			cout << endl;
			new_user_build = new User(new_user_id, new_user_name);
			
			map_of_users.add(new_user_id, new_user_build);
			cout << "+ User " << new_user_id << " has been successfully created and saved." << endl;
			
			//[todo] rework // Saving user to file
			user_append_data << "BEGIN " << new_user_id << endl;
			user_append_data << "NAME: " << new_user_name << endl;
			user_append_data << "END" << endl;
			//cout << "'" << new_user_id << "' was successfully saved to file." << endl;