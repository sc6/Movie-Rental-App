#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "MainWindow.h"

#include <string>
#include <iostream>
#include <exception>

using namespace std;

//[WORKING] Constructor
MainWindow::MainWindow(Netflix * netflix, QWidget * parent) : QMainWindow(parent)
{

	
	//MY VARIABLES
	this->netflix = netflix;
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	userOptionsLayout = new QHBoxLayout;
	buttonsLayout = new QVBoxLayout;
	labelLayout = new QVBoxLayout;

	preloginLabel = new QLabel("Sign in required: ");	
	preloginButton = new QPushButton("&Login");
	//loginButton->setDefault();
	
	signupLabel = new QLabel("Create a new account: ");
	signupButton = new QPushButton("&Sign up");

	//**********
	
	
	//DECORATIONS
	centerWidget  = new QWidget(this);
	centerWidget->setLayout(winLayout);
	this->setCentralWidget(centerWidget);
	
	winLayout->addLayout(userOptionsLayout);
	
	userOptionsLayout->addLayout(labelLayout);
	labelLayout->addWidget(preloginLabel);
	labelLayout->addWidget(signupLabel);

	userOptionsLayout->addLayout(buttonsLayout);
	buttonsLayout->addWidget(preloginButton);
	buttonsLayout->addWidget(signupButton);
	//**********
	
	
	//CONNECTIONS
	connect(preloginButton, SIGNAL(clicked()), this, SLOT(showLogin()));
	connect(signupButton, SIGNAL(clicked()), this, SLOT(showCreateUser()));
	//**********


}


MainWindow::~MainWindow()
{
	qDeleteAll(this->children());
}


void MainWindow::showLogin()
{
	loginw = new LoginWindow(netflix, 0);
	
	connect(loginw, SIGNAL(accepted()), this, SLOT(saveLoginID()));
		
	loginw->setWindowTitle("Login");
	loginw->show();
	loginw->exec();
}


void MainWindow::showCreateUser()
{
	createuserw = new createUser(netflix, 0);
	
	//connect(createuserw, SIGNAL(accepted()), this, SLOT())
		
	createuserw->setWindowTitle("Create New User");
	createuserw->show();
	createuserw->exec();
}


void MainWindow::saveLoginID()	//runs when loginID was successful.
{
	string user_id;
	loginw->getUserID(user_id);	//user_id passed as reference
	
	netflix->setCurrentUser(user_id);
	
	cerr << "current user is: " << netflix->showCurrentUser() << endl;
	
	mainw = new UIWindow(netflix, 0);
	mainw->setWindowTitle("Movie App (Logged in)");
	mainw->show();
	this->hide();

}

#endif