#ifndef RATEMOVIE_CPP
#define RATEMOVIE_CPP

#include "RateMovie.h"

#include <string>
#include <iostream>
#include <exception>

using namespace std;

RateMovie::RateMovie(Movie * movie, Netflix * netflix, QWidget * parent) : QDialog(parent)
{
	
	//MY VARIABLES
	this->netflix = netflix;
	this->movie = movie;
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	rating_buttons_box = new QVBoxLayout;
	buttons_box = new QHBoxLayout;
	message = new QLabel(QString::fromStdString("Rate " + movie->getTitle()));
	acceptButton = new QPushButton("Rate");
	skipButton = new QPushButton("Skip");
	
	one_star = new QRadioButton("1 star", this);
	two_star = new QRadioButton("2 star", this);
	three_star = new QRadioButton("3 star", this);
	four_star = new QRadioButton("4 star", this);
	five_star = new QRadioButton("5 star", this);
	//**********
	
	
	//DECORATIONS
	QVBoxLayout *mainLayout = new QVBoxLayout;
	
	mainLayout->addLayout(rating_buttons_box);
	
	mainLayout->addWidget(message);
	
	rating_buttons_box->addWidget(one_star);
	rating_buttons_box->addWidget(two_star);
	rating_buttons_box->addWidget(three_star);
	rating_buttons_box->addWidget(four_star);
	rating_buttons_box->addWidget(five_star);
	
	mainLayout->addLayout(buttons_box);
	
	buttons_box->addWidget(acceptButton);
	buttons_box->addWidget(skipButton);
	
	setLayout(mainLayout);
	//**********
	
	
	//CONNECTIONS
	connect(acceptButton, SIGNAL(clicked()), this, SLOT(submitRating()));
	connect(skipButton, SIGNAL(clicked()), this, SLOT(acknowledged()));
	//**********

	
}

RateMovie::~RateMovie() {
	qDeleteAll(this->children());
}

void RateMovie::submitRating()
{
	Movie* rateThis = movie;
	
	if(one_star->isChecked()) {
		int rating = 1;
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Thanks for your rating!", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
	}
	else if(two_star->isChecked()) {
		int rating = 2;
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Thanks for your rating!", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
	}
	else if(three_star->isChecked()) {
		int rating = 3;
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Thanks for your rating!", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
		}
	else if(four_star->isChecked()) {
		int rating = 4;
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Thanks for your rating!", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
		}
	else if(five_star->isChecked()) {
		int rating = 5;
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Thanks for your rating!", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
		}
	else {
		popw = new PopUp("You haven't rated the movie.", 0);
		popw->setWindowTitle("Error");
		popw->show();
		popw->exec();
	}
}

void RateMovie::acknowledged()
{
	accept();
}


#endif