#ifndef UIWINDOW_CPP
#define UIWINDOW_CPP

#include "UIWindow.h"
#include "MainWindow.h"

#include <string>
#include <sstream>
#include <iostream>
#include <exception>

using namespace std;

//[WORKING] Constructor
UIWindow::UIWindow(Netflix * netflix, QWidget * parent) : QMainWindow(parent)
{
	
	//MY VARIABLES
	this->netflix = netflix;
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	
	currentMovieBox = new QGroupBox("Current Movie");
	returnMovieButton = new QPushButton("&Return Movie");
	
	movieQueueBox = new QGroupBox("Movie Queue");
	rentMovieButton = new QPushButton("R&ent Movie");
	deleteMovieButton = new QPushButton("&Delete from Queue");
	moveMovieButton = new QPushButton("&Move to Back of Queue");
	
	searchBox = new QGroupBox("Search for a Movie");
	searchBar = new QLineEdit();
	titleSearchButton = new QPushButton("Search by &Title");
	keywordSearchButton = new QPushButton("Search by &Keyword");
	actorSearchButton = new QPushButton("Search by &Actor");
	
	recommendation = new QGroupBox("Recommended");
	recButton = new QPushButton("Add Movie to &Queue");
	
	infoBox = new QGroupBox("Your info");
	cardNumberBar = new QLineEdit();
	chargeCardButton = new QPushButton("Pa&y Charge");
	changeCardButton = new QPushButton("Change Car&d");
	
	string s1 = "Signed in as " + netflix->showCurrentUser() + ".";
	userLabel = new QLabel(QString::fromStdString(s1));
	
	string s2 = "You have " + netflix->showCurrentMovie() + " checked out.";
	currentMovieLabel = new QLabel(QString::fromStdString(s2));
	
	string s3;
	if(netflix->showCurrentUserObj()->userQueue.empty())
		s3 = "Your queue is empty.";
	else
		s3 = "You have " + netflix->showCurrentUserObj()->userQueue.front()->getTitle() + " at the front of your queue.";
	queueFrontLabel = new QLabel(QString::fromStdString(s3));
	
	string s4 = "We think you'll like: " + netflix->calculateRecommendation(netflix->showCurrentUserObj())->getTitle();
	recLabel = new QLabel(QString::fromStdString(s4));
	
	string s5 = "Address: " + netflix->showCurrentUserObj()->address;
	address_label = new QLabel(QString::fromStdString(s5));
	
	string s6 = "Credit Card: " + netflix->showCurrentUserObj()->cc_number;
	cc_number_label = new QLabel(QString::fromStdString(s6));
	
	std::ostringstream s7;
	s7 << netflix->showCurrentUserObj()->charges;
	
	charges_label = new QLabel(QString::fromStdString("Dollars owed: $" + s7.str() + ".00"));
	
	
	searchLabel = new QLabel("Search:");
	
	logoutButton = new QPushButton("Log&out");
	
	refreshButton = new QPushButton("Refres&h");
	
	editRatingsButton = new QPushButton("Edit Ratings");
	
	currentMovieLayout = new QVBoxLayout();
	
	queueLayout = new QVBoxLayout();
	queueButtonsLayout = new QHBoxLayout();
	
	searchLayout = new QVBoxLayout();
	searchBarLayout = new QHBoxLayout();
	searchButtonsLayout = new QHBoxLayout();
	
	recLayout = new QVBoxLayout();
	
	buttonsLayout = new QHBoxLayout();
	
	infoLayout = new QVBoxLayout();
	cardLayout = new QHBoxLayout();
	//**********
	
	
	//DECORATIONS
	centerWidget = new QWidget(this);
	centerWidget->setLayout(winLayout);
	this->setCentralWidget(centerWidget);
	
	winLayout->addWidget(userLabel);	
	
	winLayout->addWidget(currentMovieBox);
	currentMovieBox->setLayout(currentMovieLayout);
	currentMovieLayout->addWidget(currentMovieLabel);
	currentMovieLayout->addWidget(returnMovieButton);
	
	winLayout->addWidget(movieQueueBox);
	movieQueueBox->setLayout(queueLayout);
	queueLayout->addWidget(queueFrontLabel);
	queueLayout->addLayout(queueButtonsLayout);
	queueButtonsLayout->addWidget(rentMovieButton);
	queueButtonsLayout->addWidget(deleteMovieButton);
	queueButtonsLayout->addWidget(moveMovieButton);
	
	winLayout->addWidget(searchBox);
	searchBox->setLayout(searchLayout);
	searchLayout->addLayout(searchBarLayout);
	searchBarLayout->addWidget(searchLabel);
	searchBarLayout->addWidget(searchBar);
	searchLayout->addLayout(searchButtonsLayout);
	searchButtonsLayout->addWidget(titleSearchButton);
	searchButtonsLayout->addWidget(keywordSearchButton);
	searchButtonsLayout->addWidget(actorSearchButton);
	
	winLayout->addWidget(recommendation);
	recommendation->setLayout(recLayout);
	recLayout->addWidget(recLabel);
	recLayout->addWidget(recButton);
	
	winLayout->addWidget(infoBox);
	infoBox->setLayout(infoLayout);
	infoLayout->addWidget(address_label);
	infoLayout->addWidget(cc_number_label);
	infoLayout->addWidget(charges_label);
	infoLayout->addLayout(cardLayout);
	cardLayout->addWidget(cardNumberBar);
	cardLayout->addWidget(changeCardButton);
	infoLayout->addWidget(chargeCardButton);
	
	winLayout->addLayout(buttonsLayout);
	buttonsLayout->addWidget(refreshButton);
	buttonsLayout->addWidget(logoutButton);
	buttonsLayout->addWidget(editRatingsButton);

	
	//**********
	
	
	//CONNECTIONS
	connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
	connect(returnMovieButton, SIGNAL(clicked()), this, SLOT(returnMovie()));
	connect(rentMovieButton, SIGNAL(clicked()), this, SLOT(rentMovie()));
	connect(deleteMovieButton, SIGNAL(clicked()), this, SLOT(deleteMovie()));
	connect(moveMovieButton, SIGNAL(clicked()), this, SLOT(moveMovie()));
	connect(titleSearchButton, SIGNAL(clicked()), this, SLOT(titleSearch()));
	connect(keywordSearchButton, SIGNAL(clicked()), this, SLOT(keywordSearch()));
	connect(recButton, SIGNAL(clicked()), this, SLOT(addToQueue()));
	connect(refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
	connect(editRatingsButton, SIGNAL(clicked()), this, SLOT(editRatings()));
	connect(changeCardButton, SIGNAL(clicked()), this, SLOT(changeCard()));
	connect(chargeCardButton, SIGNAL(clicked()), this, SLOT(chargeCard()));
	connect(actorSearchButton, SIGNAL(clicked()), this, SLOT(actorSearch()));
	//**********

	//recommended movie for current user
	recommended = netflix->calculateRecommendation(netflix->showCurrentUserObj());
}


UIWindow::~UIWindow() {
	qDeleteAll(this->children());
}

//[WORKING]
void UIWindow::rentMovie() {
	
	if(!(netflix->showCurrentUserObj()->checkedOut) && !(netflix->showCurrentUserObj()->movieQueue()->empty())) 
	{
		netflix->showCurrentUserObj()->checkedOut = netflix->showCurrentUserObj()->movieQueue()->front();
		netflix->showCurrentUserObj()->movieQueue()->pop();
		netflix->showCurrentUserObj()->charges += netflix->showCurrentUserObj()->checkedOut->price;
		popw = new PopUp("Enjoy the movie!", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		refreshHelper();
	}
	else {
		popw = new PopUp("You already have a movie rented, or there's no movie selected.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
	}
	
}

//[WORKING]
void UIWindow::deleteMovie() {
	
	if(!(netflix->showCurrentUserObj()->movieQueue()->empty())) {
		netflix->showCurrentUserObj()->movieQueue()->pop();
		popw = new PopUp("Movie was successfully removed from queue.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		refreshHelper();
	}
	else {
		popw = new PopUp("Your queue is empty. There's nothing to remove.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
	}
	
}

//[WORKING]
void UIWindow::moveMovie() {
	if(!(netflix->showCurrentUserObj()->movieQueue()->empty())) {
		Movie* saveMovie = netflix->showCurrentUserObj()->movieQueue()->front();
		netflix->showCurrentUserObj()->movieQueue()->pop();
		netflix->showCurrentUserObj()->movieQueue()->push(saveMovie);
		delete saveMovie;
		popw = new PopUp("Moved movie to the back of queue.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		
		refreshHelper();
	}
	else {
		popw = new PopUp("Your queue is empty. There's nothing to postpone.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
	}
}


void UIWindow::keywordSearch() {
	set<Movie*>* found_set;
	string search_this_keyword = searchBar->displayText().toUtf8().constData();
	
	//Search algo
	found_set = netflix->searchKeyword(search_this_keyword);
	
	//Search for title, if no set found
	if(found_set == NULL) {		
		titleSearch();
	}
	
	//Prints result
	else {
		for(set<Movie*>::iterator sI = (*found_set).begin(); sI != (*found_set).end(); ++sI)
		{
			queuew = new queueWindow(netflix, *sI, 0);
			queuew->show();
		}
	}
}

void UIWindow::titleSearch() {
	Movie* found_movie;
	string search_this_title = searchBar->displayText().toUtf8().constData();
	
	//Search algorithm
	found_movie = netflix->searchTitle(search_this_title);
	
	//Prints result
	if(found_movie == NULL) {
		popw = new PopUp("No movie found.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
	}
	else {
		//just one result- no looping
		queuew = new queueWindow(netflix, found_movie, 0);
		queuew->show();	
	}
}

void UIWindow::actorSearch()
{
	set<Movie*>* found_set;
	string search_this_actor = searchBar->displayText().toUtf8().constData();
	
	//Search algorithm
	found_set = netflix->searchKeyword(search_this_actor);
	
	//Prints result
	if(found_set == NULL) {
		popw = new PopUp("No movie found.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
	}
	else {
		for(set<Movie*>::iterator sI = (*found_set).begin(); sI != (*found_set).end(); ++sI)
		{
			queuew = new queueWindow(netflix, *sI, 0);
			queuew->show();
		}
	}
}

//[DONE] Runs when "Return Movie" button is pressed
void UIWindow::returnMovie()
{
	//if the user has a movie checked out, run this
	if(netflix->showCurrentUserObj()->currentMovie() != NULL) {
		Movie* action_on_this = netflix->showCurrentUserObj()->currentMovie();
		if(*(netflix->showCurrentUserObj()->ratedMovies.find(netflix->showCurrentUserObj()->currentMovie())) != NULL) {
			
			reratew = new ReRate(action_on_this, netflix, 0);
			reratew->setWindowTitle("Modify your rating");
			reratew->show();
			reratew->exec();
			
			netflix->showCurrentUserObj()->returnMovie();
		}
		//catch (NoSuchElementException & e)
		else
		{
			ratew = new RateMovie(action_on_this, netflix, 0);
			ratew->setWindowTitle("Rate this film");
			ratew->show();
			ratew->exec();
			
			netflix->showCurrentUserObj()->returnMovie();
		}
	}
	//if the user has no movie checked out, run this
	else {
		popw = new PopUp("You don't have any movies checked out.", 0);
		popw->setWindowTitle("Error");
		popw->show();
		popw->exec();
	}
}


void UIWindow::logout()
{
	this->hide();

	netflix->userLogOut();
	popw = new PopUp("Bug: Do not log back in with the same username. Read README.md", 0);
	popw->setWindowTitle("Notice");
	popw->show();
	popw->exec();
	
	MainWindow * startw = new MainWindow(netflix, 0);
	startw->show();
}

void UIWindow::refresh()
{
	//refreshes window
	nextw = new UIWindow(netflix, 0);
	nextw->show();
	this->hide();
}

void UIWindow::refreshHelper()
{
	nextw = new UIWindow(netflix, 0);
	nextw->show();
	this->hide();
}

void UIWindow::closeEvent(QCloseEvent *event)
{
	logoutHelper();
	event->accept();
}

void UIWindow::logoutHelper()
{
	this->hide();

	netflix->userLogOut();
	popw = new PopUp("Bug: Do not log back in with the same username. Read README.md", 0);
	popw->setWindowTitle("Notice");
	popw->show();
	popw->exec();
	
	MainWindow * startw = new MainWindow(netflix, 0);
	startw->show();
}

//adds the recommended movie to queue
void UIWindow::addToQueue() {
	if(recommended->getTitle() == "No recommendations available") {
		popw = new PopUp("You watched everything we have.", 0);
		popw->setWindowTitle("Notice");
		popw->show();
		popw->exec();
		return;
	}
	netflix->showCurrentUserObj()->userQueue.push(recommended);
	popw = new PopUp("Movie added to queue. Press refresh to reflect changes.", 0);
	popw->setWindowTitle("Notice");
	popw->show();
	popw->exec();
}


//opens window to edit ratings
void UIWindow::editRatings() {
	
	if(netflix->showCurrentUserObj()->ratedMovies.empty()) {
		cerr << "User's rated movies is empty" << endl;
		return;
	}
	
	for(set<Movie*>::iterator sI = netflix->showCurrentUserObj()->ratedMovies.begin(); sI != netflix->showCurrentUserObj()->ratedMovies.end(); ++sI)
	{
		reratew = new ReRate((*sI), netflix, 0);
		reratew->setWindowTitle("Modify your rating");
		reratew->show();
		reratew->exec();
	}
}

void UIWindow::chargeCard() {

	netflix->showCurrentUserObj()->charges = 0;
	popw = new PopUp("You now have $0.00 due.", 0);
	popw->setWindowTitle("Notice");
	popw->show();
	popw->exec();
	this->refresh();
	
}

void UIWindow::changeCard() {
	netflix->showCurrentUserObj()->cc_number = cardNumberBar->displayText().toUtf8().constData();
	popw = new PopUp("Your card has been changed.", 0);
	popw->setWindowTitle("Notice");
	popw->show();
	popw->exec();
	refresh();
}

#endif