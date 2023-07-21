<<<<<<< HEAD
//
// Adeeb Sait and Matthew Boote
//

/**
  * \file main.cpp */ 
#include <iostream>
#include <fstream>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

CargoOwnerUserInterface cargoui;
DriverUserInterface driverui;
TransportationCompanyUserInterface transui;
int choice;
std::string inp;
int type;

while(1) { 		// Come play with us... Come play with us forever and ever and ever

	//
	// Ask the user what kind of user they are
	//
	std::cout << "I am a..." << std::endl; 
	std::cout << std::endl;
	std::cout << "1. Cargo Owner (send orders)" << std::endl;
	std::cout << "2. Driver (register as a driver)" << std::endl;
	std::cout << "3. Transportation company (receive orders and deliver)" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

        std::cout << "Enter type of account:";
	getline(std::cin,inp,'\n');
	
	type=stoi(inp);		// convert to integer

	switch(type) {
		case 1:
			cargoui.MainMenu();		// Main menu for cargo owner
			break;

		case 2:
			driverui.MainMenu();
			break;

		case 3:
			transui.MainMenu();
			break;

		case 4:
			std::cout << "Thanks for using" << std::endl;
		  	exit(1);

		default:
		       std::cout << "Invalid choice" << std::endl; 
	  }

 }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
