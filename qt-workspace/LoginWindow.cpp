#ifndef LOGINWINDOW_CPP
#define LOGINWINDOW_CPP

#include "LoginWindow.h"

#include <string>
#include <iostream>
#include <exception>

using namespace std;

//[WORKING] Constructor
LoginWindow::LoginWindow(Netflix * netflix, QWidget * parent) : QDialog(parent)
{
	
	//MY VARIABLES
	this->netflix = netflix;
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	loginLayout = new QHBoxLayout;
	buttonsLayout = new QHBoxLayout;
	
	loginLabel = new QLabel("Login");
	passwordLabel = new QLabel("Password");
	loginField = new QLineEdit;
	passwordField = new QLineEdit;
	
	loginButton = new QPushButton("&Login");
	quitButton = new QPushButton("&Return");
	//**********
	
	
	//DECORATIONS
	QVBoxLayout *mainLayout = new QVBoxLayout;
	
	mainLayout->addLayout(loginLayout);
	loginLayout->addWidget(loginLabel);
	loginLayout->addWidget(loginField);
	loginLayout->addWidget(passwordLabel);
	loginLayout->addWidget(passwordField);
	
	mainLayout->addLayout(buttonsLayout);
	buttonsLayout->addWidget(loginButton);
	buttonsLayout->addWidget(quitButton);
	
	setLayout(mainLayout);
	//**********
	
	
	//CONNECTIONS
	connect(loginButton, SIGNAL(clicked()), this, SLOT(loginClicked()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitClicked()));
	//**********
	
}


LoginWindow::~LoginWindow()
{
	qDeleteAll(this->children());
}


void LoginWindow::loginClicked()
{	
	string user_id = loginField->displayText().toUtf8().constData();
	string user_password = passwordField->displayText().toUtf8().constData();
	if(netflix->loginUser(user_id, user_password)) {
		this->accept();
	}
	else {		
		popw = new PopUp("Invalid username or password.", 0);
		popw->setWindowTitle("Error");
		popw->show();
		popw->exec();
	}
}

void LoginWindow::quitClicked()
{
	this->reject();
}


void LoginWindow::getUserID(string & user_id)
{
	user_id = loginField->displayText().toUtf8().constData();
}

#endif