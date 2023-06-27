#include <iostream>			//STL Input / Output - cin, cout, getline()
#include <string>			//String class
#include "User.h"			//User class
#include "Util.h"			//Util class
#include "Globals.h"		//Globals




/*Function Definitions and Implementation*/

User::User() {					
	privID = 0;				//Initialize Our Privilige Lvl				0 = user; 1 = admin
}


//Register
void User::registerAccount() {

	//Define new user object
	User newUser;

	bool regAccStatus = true;

	while (regAccStatus) {

		std::cin.clear();

		//Get User Input for Username
		std::cout << "\nPlease enter your username:" << std::endl;
		std::string userBuffer;
		std::getline(std::cin, userBuffer);

		
		/*Input Validation*/
		//Check If Username Is Taken
		for (User u : Globals::userList_g) {
			if (u.username == userBuffer) {
				std::cout << "\nUsername is taken sorry!" << std::endl;
				User::registerAccount();
			}
		}


		if (userBuffer.size() == 0) {
			std::cout << "\nPlease enter a valid username:" << std::endl;
			User::registerAccount();
		}

		else if (userBuffer.size() > 15) {
			std::cout << "\nPlease enter a username between 0 and 15 characters:" << std::endl;
			User::registerAccount();
		}

		//Assign User object user property to our input buffer
		newUser.username = userBuffer;


		//Get User Input for Password
		std::cout << "\nPlease enter your password:" << std::endl;
		std::string passBuffer;
		std::getline(std::cin, passBuffer);



		//Password constraint checks
		bool passValidStatus = false;

		if (passBuffer.empty()) {
			system("cls");
			std::cout << "Error: Your password can not be empty, please try again..." << std::endl;
			Util::printMainMenu();
		}

		else if (passBuffer.length() >= 0 && passBuffer.length() <= 15) {
			passValidStatus = true;
		}

		else {
			system("cls");
			std::cout << "Error: Please make sure your password is between 0-15 characters long, please try again..." << std::endl;
			Util::printMainMenu();
		}


		if (passValidStatus) {	//Assign User object password property to our input buffer
			newUser.password = passBuffer;
			
			//Add User To List
			Globals::userList_g.push_back(newUser);
			system("cls");

			//Print Success
			std::cout << newUser.username << " account has been created succesfully!" << std::endl;
		}


		regAccStatus = false;
	}

	Util::printMainMenu();
}

//Change Password
void User::changePassword() {
	system("cls");
	
	std::cout << "Please enter your current password" << std::endl;
	std::string curPassBuffer;
	std::getline(std::cin, curPassBuffer);

	bool validCurPass = false;
	if (Globals::currentUser.password == curPassBuffer) { validCurPass = true; }

	else {
		std::cout << "\nError: Invalid Current Password, please try again..." << std::endl; 
		Sleep(2000);
		Util::printLoggedInMenu();
	}

	if (validCurPass) {					//To Do: nested if's, see if its possible to refactor/neaten this 
		std::cout << "\nPlease enter your new password (0-15 characters):" << std::endl;
		std::string newPassBuffer;
		std::getline(std::cin, newPassBuffer);

		//Password Constraints
		if (newPassBuffer.length() <= 15 && newPassBuffer.length() >= 0) {

			//Double Check password
			std::cout << "\nPlease re-enter and confirm your new password:" << std::endl;
			std::string dblChkPassBuff;
			std::getline(std::cin, dblChkPassBuff);

			//Set New Password
			if (dblChkPassBuff == newPassBuffer) {
				Globals::currentUser.password = dblChkPassBuff;
				
				//Search through userList and update list with users new detials
				for (int i = 0; i < Globals::userList_g.size(); i++) {
					if (Globals::userList_g[i].username == Globals::currentUser.username) {
						//Set User in the list and update the password property to rhe new password assigned to the currentUser
						Globals::userList_g[i].password = Globals::currentUser.password;
					}
				}

				std::cout << "\nSuccess, your new password has been set!" << std::endl;
			}

			else {
				std::cout << "\nError: Your password does not match the one you entered, please try again..." << std::endl;
				Sleep(2500);
				Util::printLoggedInMenu();
			}
			Sleep(2000);
			Util::printLoggedInMenu();
		}

		else {
			std::cout << "\nError: Please make sure your password is between (0-15) characters long" << std::endl;
			Sleep(2000);
			Util::printLoggedInMenu();
		}
	}
}



