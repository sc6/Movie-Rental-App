#ifndef POPUP_H
#define POPUP_H

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

class PopUp : public QDialog
{
	Q_OBJECT
	
	public:
		PopUp(string s, QWidget *parent = 0);
		~PopUp();
		
	private slots:
		void acknowledged();
		
	private:
		QVBoxLayout* winLayout;
		QWidget* centerWidget;
		
		QLabel* message;
		QPushButton* acceptButton;


};

#endif