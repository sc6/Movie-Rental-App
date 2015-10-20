#ifndef RERATE_CPP
#define RERATE_CPP

#include "ReRate.h"

#include <string>
#include <iostream>
#include <exception>
#include <stdlib.h>

using namespace std;

ReRate::ReRate(Movie * movie, Netflix * netflix, QWidget * parent) : QDialog(parent)
{
	//MY VARIABLES
	this->netflix = netflix;
	this->movie = movie;
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	rating_buttons_box = new QVBoxLayout;
	buttons_box = new QHBoxLayout;
	
	int rating = netflix->showCurrentUserObj()->myRatings.at(movie);
	string str_rating;
	
	if(rating == 1) str_rating = "Bad - 1 star";
	else if (rating == 2) str_rating = "OK - 2 stars";
	else if (rating == 3) str_rating = "Good - 3 stars";
	else if (rating == 4) str_rating = "Great - 4 stars";
	else str_rating = "Excellent - 5 stars";

	message = new QLabel(QString::fromStdString("Rate: " + movie->getTitle() + " (current rating: " + str_rating + ")"));
	//message = new QLabel(QString::fromStdString("Rate: " + movie->getTitle()));
	modifyButton = new QPushButton("Modify Rating");
	leaveButton = new QPushButton("Leave It");
	
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
	
	buttons_box->addWidget(modifyButton);
	buttons_box->addWidget(leaveButton);
	
	setLayout(mainLayout);
	//**********
	
	
	//CONNECTIONS
	connect(modifyButton, SIGNAL(clicked()), this, SLOT(modifyRating()));
	connect(leaveButton, SIGNAL(clicked()), this, SLOT(acknowledged()));
	//**********

	
}

ReRate::~ReRate() {
	qDeleteAll(this->children());
}

void ReRate::modifyRating()
{
	Movie* rateThis = movie;
	
	if(one_star->isChecked()) {
		int rating = 1;
		
		netflix->showCurrentUserObj()->myRatings.erase(rateThis);	
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Your rating has been modified.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
	}
	else if(two_star->isChecked()) {
		int rating = 2;
		
		netflix->showCurrentUserObj()->myRatings.erase(rateThis);		
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Your rating has been modified.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
	}
	else if(three_star->isChecked()) {
		int rating = 3;

		netflix->showCurrentUserObj()->myRatings.erase(rateThis);		
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Your rating has been modified.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
		}
	else if(four_star->isChecked()) {
		int rating = 4;

		netflix->showCurrentUserObj()->myRatings.erase(rateThis);		
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Your rating has been modified.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		accept();
		}
	else if(five_star->isChecked()) {
		int rating = 5;

		netflix->showCurrentUserObj()->myRatings.erase(rateThis);		
		netflix->showCurrentUserObj()->myRatings.insert(std::pair<Movie*, int>(rateThis, rating));
		popw = new PopUp("Your rating has been modified.", 0);
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

void ReRate::acknowledged()
{
	accept();
}


#endif