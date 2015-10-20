#ifndef CREATEUSER_H
#define CREATEUSER_H

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
#include "PopUp.h"

class createUser : public QDialog
{
	Q_OBJECT
	
	public:
		//[WORKING] LoginWindow constructor
		createUser(Netflix * netflix, QWidget *parent = 0);
		
		//[WORKING] LoginWindow destructor
		~createUser();
		
	public slots:
	
	private slots:
		void submitClicked();
		void returnClicked();
	
	private:
		QHBoxLayout* windowLayout;
		QHBoxLayout* buttonsLayout;
		QVBoxLayout* labelsLayout;
		QVBoxLayout* fieldsLayout;
		
		QLabel* idLabel;
		QLabel* nameLabel;
		QLabel* passwordLabel;
		QLabel* addressLabel;
		QLabel* ccLabel;
		
		QLineEdit* idField;
		QLineEdit* nameField;
		QLineEdit* passwordField;
		QLineEdit* addressField;
		QLineEdit* ccField;
		
		QPushButton* submitButton;
		QPushButton* returnButton;
		
		Netflix * netflix;
		PopUp * popw;
		
};

#endif