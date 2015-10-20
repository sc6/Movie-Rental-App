#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

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

#include "Netflix.h"
#include "PopUp.h"

class LoginWindow : public QDialog
{
	Q_OBJECT
	
	public:
		//[WORKING] LoginWindow constructor
		LoginWindow(Netflix * netflix, QWidget *parent = 0);
		
		//[WORKING] LoginWindow destructor
		~LoginWindow();
		
	public slots:
		void getUserID(string & user_id);
		
	private slots:
		void loginClicked();
		void quitClicked();

		
	private:
		QVBoxLayout* winLayout;
		
		QHBoxLayout* loginLayout;
		QHBoxLayout* buttonsLayout;
		
		QPushButton* loginButton;
		QPushButton* quitButton;
		
		QLabel* loginLabel;
		QLabel* passwordLabel;
		QLineEdit* loginField;
		QLineEdit* passwordField;
		
		QWidget* centerWidget;
		
		Netflix* netflix;
		PopUp* popw;
};


#endif