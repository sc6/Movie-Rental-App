#ifndef QUEUEWINDOW_CPP
#define QUEUEWINDOW_CPP

#include "queueWindow.h"

#include <string>
#include <iostream>
#include <exception>

using namespace std;

//[WORKING] Constructor
queueWindow::queueWindow(Netflix * netflix, Movie * movie, QWidget * parent) : QMainWindow(parent)
{
	
	//MY VARIABLES
	this->netflix = netflix;
	this->movie = movie;
	this->movie_title = movie->getTitle();
	this->movie_keywords = movie->getAllKeywords();
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	
	title = new QLabel(QString::fromStdString(movie_title));
	
	string s2;
	for(set<string>::iterator sI = movie_keywords.begin(); sI != movie_keywords.end(); ++sI)
		s2 = s2 + *sI + ", ";
	
	keywords = new QLabel(QString::fromStdString(s2));
	
	std::stringstream s3;
	s3 << movie->price;
	price = new QLabel(QString::fromStdString("Price: $" + s3.str() + ".00"));
	

	
	
	
	nextMovieButton = new QPushButton("&Next Movie");
	addMovieButton = new QPushButton("&Add to my Queue");
	returnButton = new QPushButton("&Return to Main Menu");
	
	//**********
	
	
	//DECORATIONS
	centerWidget = new QWidget(this);
	centerWidget->setLayout(winLayout);
	this->setCentralWidget(centerWidget);
	
	winLayout->addWidget(title);
	winLayout->addWidget(keywords);
	winLayout->addWidget(price);
	winLayout->addWidget(nextMovieButton);
	winLayout->addWidget(addMovieButton);
	winLayout->addWidget(returnButton);
	//**********
	
	
	//CONNECTIONS
	connect(nextMovieButton, SIGNAL(clicked()), this, SLOT(nextMovie()));
	connect(addMovieButton, SIGNAL(clicked()), this, SLOT(addMovie()));
	connect(returnButton, SIGNAL(clicked()), this, SLOT(returnToMenu()));
	//**********

	
}

queueWindow::~queueWindow() {
	qDeleteAll(this->children());
}

void queueWindow::nextMovie() {
	this->hide();
}

void queueWindow::addMovie() {
	netflix->showCurrentUserObj()->userQueue.push(movie);
	popw = new PopUp("Movie added to queue. Press refresh to reflect changes.", 0);
	popw->setWindowTitle("Notice");
	popw->show();
	popw->exec();
}

void queueWindow::returnToMenu() {
	this->hide();
}

#endif