#ifndef CREATEUSER_CPP
#define CREATEUSER_CPP

#include "createUser.h"

#include <string>
#include <iostream>
#include <exception>

using namespace std;

//[WORKING] Constructor
createUser::createUser(Netflix * netflix, QWidget * parent) : QDialog(parent)
{

	//MY VARIABLES
	this->netflix = netflix;
	//**********
	
	
	//QVARIABLES
	windowLayout = new QHBoxLayout;
	
	labelsLayout = new QVBoxLayout;
	fieldsLayout = new QVBoxLayout;
	buttonsLayout = new QHBoxLayout;
	
	idLabel = new QLabel("User ID:");
	nameLabel = new QLabel("Name:");
	passwordLabel = new QLabel("Password:");
	addressLabel = new QLabel("Address:");
	ccLabel = new QLabel("Credit Card Number:");

	
	idField = new QLineEdit;
	nameField = new QLineEdit;
	passwordField = new QLineEdit;
	addressField = new QLineEdit;
	ccField = new QLineEdit;
	
	submitButton = new QPushButton("&Submit");
	returnButton = new QPushButton("&Return");
	//**********
	
	
	//DECORATIONS
	QVBoxLayout *mainLayout = new QVBoxLayout;
	
	mainLayout->addLayout(windowLayout);
	mainLayout->addLayout(buttonsLayout);
	
	windowLayout->addLayout(labelsLayout);
	windowLayout->addLayout(fieldsLayout);
	
	labelsLayout->addWidget(idLabel);
	labelsLayout->addWidget(nameLabel);
	labelsLayout->addWidget(passwordLabel);
	labelsLayout->addWidget(addressLabel);
	labelsLayout->addWidget(ccLabel);
	
	fieldsLayout->addWidget(idField);
	fieldsLayout->addWidget(nameField);
	fieldsLayout->addWidget(passwordField);
	fieldsLayout->addWidget(addressField);
	fieldsLayout->addWidget(ccField);
	
	buttonsLayout->addWidget(submitButton);
	buttonsLayout->addWidget(returnButton);
	
	
	setLayout(mainLayout);
	//**********
	
	
	//CONNECTIONS
	connect(submitButton, SIGNAL(clicked()), this, SLOT(submitClicked()));
	connect(returnButton, SIGNAL(clicked()), this, SLOT(returnClicked()));
	//**********
	
	
}


createUser::~createUser()
{
	qDeleteAll(this->children());
}


void createUser::submitClicked()
{
	string user_id = idField->displayText().toUtf8().constData();
	string user_name = nameField->displayText().toUtf8().constData();	
	string user_address = addressField->displayText().toUtf8().constData();
	string user_cc = ccField->displayText().toUtf8().constData();	
	string user_password = md5(passwordField->displayText().toUtf8().constData());	

	
	try {	//checks if user_id already exists
	
		if(user_name == "" || user_address == "" || user_cc == "" || user_password == "") {
			popw = new PopUp("All fields must be filled.", 0);
			popw->setWindowTitle("Notice");
			popw->show();
			popw->exec();
		}
		else if(user_id == "" 
				|| (netflix->map_of_users.size() != 0 && netflix->map_of_users.at(user_id)->getID() == user_id)
			)
		{
			popw = new PopUp("Please choose another ID.", 0);
			popw->setWindowTitle("Notice");
			popw->show();
			popw->exec();
		}
	}	
	catch (exception & e) { 
		//if caught, new_user_id is unique
		
		User* user_build = new User(user_id, user_name);
		netflix->map_of_users.insert(std::pair<string, User*>(user_id, user_build));
		
		user_build->address = user_address;
		user_build->cc_number = user_cc;
		user_build->charges = 0;
		user_build->password = user_password;
		
		popw = new PopUp("Account creation successful! BUG: see README", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		*(netflix->user_append_data) << "BEGIN " << user_id << endl;
		*(netflix->user_append_data) << "NAME: " << user_name << endl;
		*(netflix->user_append_data) << "BEGIN INFO" << endl;
		*(netflix->user_append_data) << user_address << endl;
		*(netflix->user_append_data) << user_cc << endl;
		*(netflix->user_append_data) << 0 << endl;
		*(netflix->user_append_data) << user_password << endl;
		*(netflix->user_append_data) << "END INFO" << endl;
		*(netflix->user_append_data) << "END" << endl;
		
		this->accept();
	}
}


void createUser::returnClicked()
{
	this->reject();
}

#endif