#include <Windows.h>	//Win32 API Functions - GetAsyncKeyState()
#include <iostream>		//STL Input/Output - cin, cout
#include <string>		//std::string class
#include <algorithm>	//Max();
#include <limits>		//max();
#include "Globals.h"	//Global.h (Global Variables)
#include "Util.h"		//Utilities Class
#include "User.h"		//User Class
#include "Admin.h"		//Admin Class



/*Function Definitions / Implementation*/


//Printing
void Util::printMainMenu() {

	SetConsoleTitle(L"Hotel Management System - Main Menu");

	std::cout << R"(

 _   _       _       _   _____           _                 
| | | |     | |     | | /  ___|         | |                
| |_| | ___ | |_ ___| | \ `--. _   _ ___| |_ ___ _ __ ___  
|  _  |/ _ \| __/ _ \ |  `--. \ | | / __| __/ _ \ '_ ` _ \ 
| | | | (_) | ||  __/ | /\__/ / |_| \__ \ ||  __/ | | | | |
\_| |_/\___/ \__\___|_| \____/ \__, |___/\__\___|_| |_| |_|
                                __/ |                      
                               |___/                       
)" << std::endl;

	std::cout << "F1. Login\nF2. Register Account\n\nF8. Exit" << std::endl;
	
	

	while (!GetAsyncKeyState(VK_F8) & 0x01) {

		if (GetAsyncKeyState(VK_F1) & 0x8000) {
			Util::loginCheck(); 
		}

		else if (GetAsyncKeyState(VK_F2) & 0x8000) {
			User::registerAccount(); 
		}
		
		else {
			//Do Nothing
		}
	}
	
}

void Util::printLoggedInMenu() {

	SetConsoleTitle(L"Hotel Management System - Logged In As: ");		//add user here
	system("cls");
	std::cout << R"(

 _   _       _       _   _____           _                 
| | | |     | |     | | /  ___|         | |                
| |_| | ___ | |_ ___| | \ `--. _   _ ___| |_ ___ _ __ ___  
|  _  |/ _ \| __/ _ \ |  `--. \ | | / __| __/ _ \ '_ ` _ \ 
| | | | (_) | ||  __/ | /\__/ / |_| \__ \ ||  __/ | | | | |
\_| |_/\___/ \__\___|_| \____/ \__, |___/\__\___|_| |_| |_|
                                __/ |                      
                               |___/                       
)" << std::endl;

	std::cout << "=================================================" << std::endl;
	std::cout << "Logged In As: " << Globals::currentUser.username.c_str() << std::endl;
	std::cout << "=================================================\n" << std::endl;
	std::cout << "1. Check In Room\n2. Check Out Room\n3. View Invoices\n4. Change Password\n\n5. Log Out" << std::endl;



	//Get User Input for Menu Selection
	short int userSelection;
	std::cin >> userSelection;

	std::cin.clear();				// Restore input stream to working state
	std::cin.ignore(1000, '\n');    // Get rid of any garbage that user might have entered

	switch (userSelection) {
	case 1:
		Room::checkUserIn();
		return;

	case 2:
		Room::checkUserOut();
		break;

	case 3:
		Invoice::printInvoiceMenu();
		break;
	case 4:
		User::changePassword();
		break;
	case 5:
		system("cls");
		Util::printMainMenu();
		break;

	default:
		Util::printLoggedInMenu();
		break;

	}
}


//Login
void Util::loginCheck() {

	std::cin.clear();

	std::cout << "\nPlease enter your username" << std::endl;
	std::string usernameBufferCheck;
	std::getline(std::cin, usernameBufferCheck);


	std::cout << "\nPlease enter your password" << std::endl;
	std::string passwordBufferCheck;
	std::getline(std::cin, passwordBufferCheck);


	//Iterate through global userList and check user/pass against Users

	bool isValid = false;

	for (User u : Globals::userList_g) {
		if (u.username == usernameBufferCheck && u.password == passwordBufferCheck) {

			//Assign user global variable to user found
			Globals::currentUser = u;

			isValid = true;
		}
	}



	//BAN CHECK
	if (isValid && Globals::currentUser.isBanned == true) {
		system("cls");
		std::cout << "YOU HAVE BEEN BANNED! (" << Globals::currentUser.username.c_str() << ")" << "\nReason: " << Globals::currentUser.banReason << std::endl;
		Util::printMainMenu();
	}


	if (isValid && Globals::currentUser.privID == 0) {							//User Menu
		Util::printLoggedInMenu();
	}

	else if (isValid && Globals::currentUser.privID == 1) {						//Admin Menu
		Admin::printAdminMenu();
	}

	else {
		system("cls");
		std::cout << "Error: Invalid Username or Password!" << std::endl;
		Util::printMainMenu();
	}




}


//Misc
time_t Util::dateToTimeT(int month, int day, int year) {					//Credits to O'Reilly for this function https://www.oreilly.com/library/view/c-cookbook/0596007612/ch05s04.html
	// january 5, 2000 is passed as (1, 5, 2000)
	tm tmp = tm();
	tmp.tm_mday = day;
	tmp.tm_mon = month - 1;
	tmp.tm_year = year - 1900;
	return mktime(&tmp);
}

bool Util::backspaceCheck() {
	std::cout << "\nPlease press BACKSPACE to return to the menu" << std::endl;

	bool backspaceLoop = true;

	while (backspaceLoop) {
		if (GetAsyncKeyState(VK_BACK)) { backspaceLoop = false; }
	}

	return backspaceLoop;
}