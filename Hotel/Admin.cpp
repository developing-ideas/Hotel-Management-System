#include <Windows.h>			//Win32 API
#include <iostream>				//STL Input Output - cout, cin, getline()
#include <string>				//String class
#include "Admin.h"				//Admin header
#include "User.h"				//User class
#include "Util.h"				//Util class
#include "Globals.h"			//Globals



/*Function Definitions / Implementation for Admin*/


//Printing
void Admin::printAdminMenu() {
	SetConsoleTitle(L"Hotel Management - Logged In As: ");
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
	std::cout << "Logged In As: " << Globals::currentUser.username.c_str() << std::endl;			//Add User Name here later
	std::cout << "=================================================\n" << std::endl;
	//std::cout << "----------------------------\nADMIN MANAGEMENT\n----------------------------" << std::endl;
	std::cout << "1. View All Rooms \n2. Add Room \n3. Delete Room \n4. Set Room Vacancy Status\n\n5. View All Users\n6. Ban User \n7. Set User Privilege\n\n8. View All Invoices\n\n\n9. Log Out " << std::endl;


	//Clear And Reset Cin Buffer State
	std::cin.clear();				// Restore input stream to working state

	//Get Admin Input for Menu Selection
	short int adminSelection;
	std::cin >> adminSelection;

	std::cin.clear();				// Restore input stream to working state
	std::cin.ignore(100, '\n');    // Get rid of any garbage that user might have entered

	switch (adminSelection) {
	case 1:
		Admin::viewAllRooms();
		return;
	case 2:
		Admin::addRoom();
		return;
	case 3:
		Admin::delRoom();
		return;
	case 4:
		Admin::setRoomStatus();
		return;
	case 5:
		Admin::printAllUsers();
		break;
	case 6:
		Admin::banUser();
		break;
	case 7:
		Admin::setUserPriv();
		break;
	case 8:
		Admin::viewAllInvoices();
		break;
	case 9:
		system("cls");
		Util::printMainMenu();
		break;
	default:
		system("cls");
		Admin::printAdminMenu();
		return;
	}
}

void Admin::printAllUsers() {
	system("cls");

	std::cout << "=======================================" << std::endl;
	std::cout << "User List" << std::endl;
	std::cout << "=======================================" << std::endl;


	for (User u : Globals::userList_g) {
		std::cout << "Username: " << u.username << std::endl;
		std::cout << "Password: " << u.password << std::endl;
		std::cout << "Privilege Level (0 = user, 1 = admin): " << u.privID << std::endl;
		std::cout << "Ban Status (0 = unbanned, 1 = banned): " << u.isBanned << std::endl;
		std::cout << "Ban Reason: " << u.banReason << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
	}

	if (Util::backspaceCheck() == false) { Admin::printAdminMenu(); }
}

void Admin::printAllUsersWithoutBackspace() {
	system("cls");

	std::cout << "=======================================" << std::endl;
	std::cout << "User List" << std::endl;
	std::cout << "=======================================" << std::endl;


	for (User u : Globals::userList_g) {
		std::cout << "Username: " << u.username << std::endl;
		std::cout << "Password: " << u.password << std::endl;
		std::cout << "Privilege Level (0 = user, 1 = admin): " << u.privID << std::endl;
		std::cout << "Ban Status (0 = unbanned, 1 = banned:) " << u.isBanned << std::endl;
		std::cout << "Ban Reason: " << u.banReason << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
	}
}




//User Functions
void Admin::setUserPriv() {

	Admin::printAllUsersWithoutBackspace();


	bool loopStatus = true;

	while (loopStatus) {

		//Clear Cin Buffer
		std::cin.clear();

		//Get User Input
		std::cout << "\nPlease enter the username of the user you wish to assign privileges to:" << std::endl;
		std::string userBuffer;
		std::getline(std::cin, userBuffer);


		//Search Through Global User List and find index of the desired user

		bool foundUser = false;
		int userIndex = 0;

		for (int i = 0; i < Globals::userList_g.size(); i++) {
			if (Globals::userList_g[i].username == userBuffer) { foundUser = true; userIndex = i; }
			else { foundUser = false; }
		}

		if (foundUser == true && Globals::userList_g[userIndex].username == userBuffer) {
			std::cout << "\nPlease enter the user privilege level to assign. (0 = User, 1 = Admin):" << std::endl;
			short userPriv;
			std::cin >> userPriv;

			switch (userPriv) {
			case 0:
				Globals::userList_g[userIndex].privID = 0;
				std::cout << "\n" << Globals::userList_g[userIndex].username << " has been assigned as a User!" << std::endl;
				Sleep(2000);
				break;
			case 1:
				Globals::userList_g[userIndex].privID = 1;
				std::cout << "\n" << Globals::userList_g[userIndex].username << " has been assigned as an Administrator!" << std::endl;
				Sleep(2000);
				break;
			default:
				std::cout << "\nInvalid Privilege Level, please try again...." << std::endl;
				Sleep(2000);
				Admin::printAdminMenu();
				break;
			}
		}

		else {
			std::cout << "\nAn error occured, could not set privilege level..." << std::endl;
			loopStatus = false;
			Sleep(2500);
		}

		Admin::printAdminMenu();
	}

}	

void Admin::banUser() {
	system("cls");
	Admin::printAllUsersWithoutBackspace();
	
	std::cout << "Please enter the username of the user you wish to ban:" << std::endl;
	std::string userBuffer;
	std::getline(std::cin, userBuffer);

	std::cout << "\nPlease enter the reason for the ban:" << std::endl;
	std::string banReasonBuffer;
	std::getline(std::cin, banReasonBuffer);

	//Search through userlist and if theres a match, ban them
	bool isUserMatch = false;
	int userIndex = 0;

	for (int i = 0; i < Globals::userList_g.size(); i++) {
		if (Globals::userList_g[i].username == userBuffer) { isUserMatch = true; userIndex = i; }
	}
	

	/// <summary>
	/// Ban Constraints - Prevent Admin Ban
	/// </summary>
	if (Globals::userList_g[userIndex].privID == 1) { isUserMatch = false; }


	//Set the users ban property and the reason
	if (isUserMatch) {		
		Globals::userList_g[userIndex].isBanned = true;
		Globals::userList_g[userIndex].banReason = banReasonBuffer;
		std::cout << "\nSuccess! " << Globals::userList_g[userIndex].username << " has been banned!" << std::endl;
		Sleep(2000);
		Admin::printAdminMenu();

	}

	else {
		std::cout << "\nError: Could not find user, please try again..." << std::endl;
		Sleep(2000);
		Admin::printAdminMenu();
	}
}



//Invoice Functions
void Admin::viewAllInvoices() {
	system("cls");

	bool adminInvoiceMenuStatus = true;


	std::cout << "=======================================" << std::endl;
	std::cout << "Invoice List" << std::endl;
	std::cout << "=======================================" << std::endl;

	if (Globals::invoiceList_g.empty()) {
		std::cout << "No Invoices Found" << std::endl;
	}

	else {
		for (int i = 0; i < Globals::invoiceList_g.size(); i++) {
			std::cout << "Invoice User: " << Globals::invoiceList_g[i].room.u.username << std::endl;
			std::cout << "Invoice Name: " << Globals::invoiceList_g[i].invoiceName << std::endl;
			std::cout << "Invoice Number: " << Globals::invoiceList_g[i].invoiceNumber << std::endl;
			std::cout << "Invoice Total Cost: $" << Globals::invoiceList_g[i].finalCost << std::endl;
			std::cout << "Room Number: " << Globals::invoiceList_g[i].room.rNumber << std::endl;
			std::cout << "--------------------------------------------" << std::endl;

		}
	}

	if (Util::backspaceCheck() == false) { Admin::printAdminMenu(); }
}


//Room Functions
void Admin::viewAllRooms() {

	Room::printAllRooms();
	if (Util::backspaceCheck() == false) { Admin::printAdminMenu(); }

}

void Admin::addRoom() {
	
	bool addRoomLoopStatus = true;
	Room newRoom;
	newRoom.isVacant = true;

	system("cls");

	while(addRoomLoopStatus) {


		std::cout << "Please enter the details of the room you wish to add\n" << std::endl;

		/*Room Name*/
		std::cout << "Please enter the room name:" << std::endl;
		std::string roomNameBuffer;
		std::getline(std::cin, roomNameBuffer);

		if (roomNameBuffer.size() > 50 || roomNameBuffer.size() <= 0) {
			std::cout << "Please enter a room name between 1-50 characters:" << std::endl;
			Sleep(3000);
			Admin::addRoom();
		}

		else {
			newRoom.roomName = roomNameBuffer;
		}

		/*Room Number*/
		std::cout << "\nPlease enter the room number you wish to assign to the room (1-200):" << std::endl;
		int roomNumberBuffer;
		std::cin >> roomNumberBuffer;

		//Check For Duplicate Room ID
		bool doesRoomNumbExist = false;

		for (Room r : Globals::roomList_g) {
			if (r.rNumber == roomNumberBuffer) {
				doesRoomNumbExist = true;
			}
		}

		if (doesRoomNumbExist == false && roomNumberBuffer >=1 && roomNumberBuffer <=200) {
			newRoom.rNumber = roomNumberBuffer;
		}

		else {
			std::cout << "\nRoom Number either already exists or is outside the range of 0-200, please try again...." << std::endl;
			Sleep(3000);
			Admin::printAdminMenu();
		}



		/*Room Cost*/
		std::cout << "\nPlease enter the cost per day of the room ($1-1000):" << std::endl;
		int costBuffer;
		std::cin >> costBuffer;


		if (costBuffer >= 0 && costBuffer <= 2000) {
			newRoom.costPerDay = costBuffer;
		}
		else {
			std::cout << "Invalid cost price, please enter a price per day between 1-1000:" << std::endl;
			Sleep(3000);
			Admin::printAdminMenu();
		}


		/*Vacancy Status*/
		bool loopStatus = true;
		char setRoomStatus;
		while (loopStatus) {
			std::cout << "\nEnter the rooms vacancy status:" << std::endl;
			std::cout << "y = Vacant, n = Occupied" << std::endl;
			
			std::cin >> setRoomStatus;

			switch (setRoomStatus) {
			case 'y':
				newRoom.isVacant = true;
				loopStatus = false;
				break;
			case 'n':
				newRoom.isVacant = false;
				loopStatus = false;
				break;
			default:
				std::cout << "\nInvalid Input for room vacancy, please try again...." << std::endl;
				Sleep(2000);
				Admin::printAdminMenu();
				break;

			}
		}

		Globals::roomList_g.push_back(newRoom);
		


		//Print Success
		system("cls");
		std::cout << R"(
   _____                             _ 
  / ____|                           | |
 | (___  _   _  ___ ___ ___  ___ ___| |
  \___ \| | | |/ __/ __/ _ \/ __/ __| |
  ____) | |_| | (_| (_|  __/\__ \__ \_|
 |_____/ \__,_|\___\___\___||___/___(_)
		)" << std::endl;

		std::cout << "\nRoom " << newRoom.roomName << " has been created sucessfully!" << std::endl;
		
		std::cout << "\n------------------------" << std::endl;
		std::cout << "Room Name: " << newRoom.roomName << std::endl;
		std::cout << "------------------------" << std::endl;
		std::cout << "Room Number: " << newRoom.rNumber << std::endl;
		std::cout << "------------------------" << std::endl;
		std::cout << "Room Cost Per Day: $" << newRoom.costPerDay << std::endl;
		std::cout << "------------------------" << std::endl;
		std::cout << "Vacant: " << newRoom.isVacant << std::endl;
		std::cout << "------------------------" << std::endl;
		Sleep(2500);
		addRoomLoopStatus = false;
	} 

	Admin::printAdminMenu();
}

void Admin::delRoom() {
	bool delRoomLoopStatus = true;

	Room::printAllRooms();
	
	while (delRoomLoopStatus) {

		//Get User Input
		std::cout << "Please enter the room number of the room you wish to delete" << std::endl;
		short roomNumbBuffer;
		std::cin >> roomNumbBuffer;


		//Check If Room Exists in List
		bool doesRoomExist = false;
		int roomIndex = 0;

		for (int i = 0; i < Globals::roomList_g.size(); i++) {
			if (Globals::roomList_g[i].rNumber == roomNumbBuffer) {
				roomIndex = i;
				doesRoomExist = true;
			}
		}

		if (doesRoomExist == true) {
			std::cout << "\nRoom number " << Globals::roomList_g[roomIndex].rNumber << " has been removed from the list!" << std::endl;
			//erase() parameters are erase(position); We found the index of the element we want to remove above
			Globals::roomList_g.erase(Globals::roomList_g.begin() + roomIndex);
			Sleep(2500);
		}

		else {
			std::cout << "\nRoom could not be found, please try again..." << std::endl;
			Sleep(2500);
		}

		Admin::printAdminMenu();
	}
}

void Admin::setRoomStatus() {
	system("cls");
	bool match = false;
	bool loopStatus = true;
	int roomIndex = 0;
	
		//Initializing our new room object
		Room room;

		//Print Room List
		Room::printAllRooms();

		while (loopStatus) {
			std::cout << "Please enter the room number of the room in which you want to change the vacancy status in:" << std::endl;

			int roomNumbBuffer;
			std::cin >> roomNumbBuffer;

			for (int i = 0; i < Globals::roomList_g.size(); i++) {
				if (Globals::roomList_g[i].rNumber == roomNumbBuffer) {
					match = true;
					roomIndex = i;
				}
			}

			if (match) {
				std::cout << "\nPlease enter either 'y' or 'n' to set the room status.\ny = Vacant\nn = Occupied" << std::endl;
				char decideOnStatus;
				std::cin >> decideOnStatus;

				switch (decideOnStatus) {
				case 'y':
					Globals::roomList_g[roomIndex].isVacant = true;
					std::cout << "\nRoom number " << Globals::roomList_g[roomIndex].rNumber << " has been set to vacant" << std::endl;
					loopStatus = false;
					Sleep(2000);
					break;
				case 'n':
					Globals::roomList_g[roomIndex].isVacant = false;
					std::cout << "\nRoom number " << Globals::roomList_g[roomIndex].rNumber << " has been set to occupied" << std::endl;
					loopStatus = false;
					Sleep(2000);
					break;
				default:
					std::cout << "\nPlease enter a valid status value (y or n), please try again..." << std::endl;
					loopStatus = false;
					Sleep(2000);
					break;
				}
			}

			else {
				std::cout << "\nCould not find room number " << roomNumbBuffer << " please try again..." << std::endl;
				loopStatus = false;
				Sleep(2000);
			}
		}

		Admin::printAdminMenu();
	}