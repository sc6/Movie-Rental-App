#ifndef UIWINDOW_H
#define UIWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QGroupBox>

#include "PopUp.h"
#include "RateMovie.h"
#include "ReRate.h"
#include "queueWindow.h"
#include "Netflix.h"


class UIWindow : public QMainWindow
{
	Q_OBJECT
			
	public:
	
		UIWindow(Netflix * netflix, QWidget *parent = 0);
		
		~UIWindow();
		
	private slots:
		void returnMovie();
		void rentMovie();
		void deleteMovie();
		void moveMovie();
		void titleSearch();
		void keywordSearch();
		void logout();
		void refresh();
		void addToQueue();
		void editRatings();
		void changeCard();
		void chargeCard();
		void actorSearch();
		
	private:
		
		QVBoxLayout* winLayout;
		QWidget* centerWidget;
		
		QGroupBox* currentMovieBox;
		QVBoxLayout* currentMovieLayout;
		QPushButton* returnMovieButton;
		
		QGroupBox* movieQueueBox;
		QPushButton* rentMovieButton;
		QPushButton* deleteMovieButton;
		QPushButton* moveMovieButton;
		QVBoxLayout* queueLayout;
		QHBoxLayout* queueButtonsLayout;
		
		QGroupBox* searchBox;
		QVBoxLayout* searchLayout;
		QHBoxLayout* searchBarLayout;
		QHBoxLayout* searchButtonsLayout;
		QLineEdit* searchBar;
		QLabel* searchLabel;
		QPushButton* titleSearchButton;
		QPushButton* keywordSearchButton;
		QPushButton* actorSearchButton;
		
		QGroupBox* recommendation;
		QVBoxLayout* recLayout;
		QLabel* recLabel;
		QPushButton* recButton;
		
		QHBoxLayout* buttonsLayout;
		QPushButton* editRatingsButton;
		QPushButton* logoutButton;
		QPushButton* refreshButton;
		
		QGroupBox* infoBox;
		QVBoxLayout* infoLayout;
		QHBoxLayout* cardLayout;
		QLabel* address_label;
		QLabel* cc_number_label;
		QLabel* charges_label;
		QLineEdit* cardNumberBar;
		QPushButton *chargeCardButton;
		QPushButton *changeCardButton;

		QLabel* userLabel;
		QLabel* currentMovieLabel;
		QLabel* queueFrontLabel;
		
		Netflix* netflix;
		Movie* recommended;
		
		queueWindow* queuew;
		UIWindow* nextw;
		PopUp *popw;
		RateMovie *ratew;
		ReRate *reratew;

		void closeEvent(QCloseEvent *event);
		void refreshHelper();
		void logoutHelper();

};

#endif