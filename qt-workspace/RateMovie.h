#ifndef RATEMOVIE_H
#define RATEMOVIE_H

#include <QWidget>
#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QRadioButton>

#include "Netflix.h"
#include "PopUp.h"

class RateMovie : public QDialog
{
	Q_OBJECT
	
	public:
		RateMovie(Movie* movie, Netflix* netflix, QWidget *parent = 0);
		~RateMovie();
		
	private slots:
		void submitRating();
		void acknowledged();
		
	private:
		QVBoxLayout* winLayout;
		QHBoxLayout* buttons_box;
		QVBoxLayout* rating_buttons_box;
		QWidget* centerWidget;
		
		QLabel* message;
		QPushButton* acceptButton;
		QPushButton* skipButton;
		
		QRadioButton* one_star;
		QRadioButton* two_star;
		QRadioButton* three_star;
		QRadioButton* four_star;
		QRadioButton* five_star;
		
		Netflix* netflix;
		PopUp *popw;
		Movie *movie;


};

#endif