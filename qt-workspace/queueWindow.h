#ifndef QUEUEWINDOW_H
#define QUEUEWINDOW_H

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

#include "Netflix.h"
#include "PopUp.h"

class queueWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
	
		queueWindow(Netflix * netflix, Movie* movie, QWidget *parent = 0);
		
		~queueWindow();
		
	private slots:
		void nextMovie();
		void addMovie();
		void returnToMenu();
		
	private:
		QVBoxLayout* winLayout;
		QWidget* centerWidget;
		
		QPushButton* nextMovieButton;
		QPushButton* addMovieButton;
		QPushButton* returnButton;
		
		QLabel* title;
		QLabel* keywords;
		QLabel* price;
		
		Movie* movie;
		
		string movie_title;
		set<string> movie_keywords;
	
		Netflix* netflix;
		PopUp* popw;
};

	#endif