#ifndef POPUP_CPP
#define POPUP_CPP

#include "PopUp.h"

#include <string>
#include <iostream>
#include <exception>

using namespace std;

PopUp::PopUp(string s, QWidget * parent) : QDialog(parent)
{
	//MY VARIABLES
	//**********
	
	
	//QVARIABLES
	winLayout = new QVBoxLayout;
	message = new QLabel(QString::fromStdString(s));
	acceptButton = new QPushButton("Okay");
	//**********
	
	
	//DECORATIONS
	QVBoxLayout *mainLayout = new QVBoxLayout;
	
	mainLayout->addWidget(message);
	mainLayout->addWidget(acceptButton);
	
	setLayout(mainLayout);
	//**********
	
	
	//CONNECTIONS
	connect(acceptButton, SIGNAL(clicked()), this, SLOT(acknowledged()));
	//**********

	
}

PopUp::~PopUp() {
	qDeleteAll(this->children());
}

void PopUp::acknowledged()
{
	accept();
}


#endif