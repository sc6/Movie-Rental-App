#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "Netflix.h"
#include "LoginWindow.h"
#include "createUser.h"
#include "UIWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
		
	public:
		//[WORKING] MainWindow constructor
		MainWindow(Netflix * netflix, QWidget *parent = 0);
		
		//[WORKING] MainWindow destructor
		~MainWindow();
		
	private slots:
		void showLogin();
		void saveLoginID();
		void showCreateUser();
		
	private:
		QVBoxLayout* winLayout;
		
		QHBoxLayout* userOptionsLayout;
		
		QVBoxLayout* labelLayout;
		QLabel* preloginLabel;
		QLabel* signupLabel;
		
		QVBoxLayout* buttonsLayout;
		QPushButton* preloginButton;
		QPushButton* signupButton;
		

		QWidget* centerWidget;
		
		Netflix* netflix;
		LoginWindow* loginw;
		createUser* createuserw;
		UIWindow* mainw;
		
};

#endif