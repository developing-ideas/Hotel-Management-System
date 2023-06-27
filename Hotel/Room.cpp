#include <Windows.h>		//Win32API
#include <iostream>			//STL Input/Output	- cout, cin, getline()
#include <string>			//String class
#include <cstdlib>			//rand()
#include "Room.h"			//Room header
#include "Globals.h"		//Globals
#include "Util.h"			//Util class
#include "Invoice.h"		//Invoice class


/*Forward Declaration*/
std::vector<User> Globals::userList_g;
std::vector<Room> Globals::roomList_g;
std::vector<Invoice> Globals::invoiceList_g;
User Globals::currentUser;


/*Constructors / Destructors*/
Room::Room() {

}



/*Function Definitions / Implementation*/


//Printing
void Room::printAllRooms() {
	system("cls");
	std::cout << "==============================" << std::endl;
	std::cout << "          Room List" << std::endl;
	std::cout << "==============================" << std::endl;

	for (int i = 0; i < Globals::roomList_g.size(); i++) {
			std::cout << "Room User: " << Globals::roomList_g[i].u.username << std::endl;
			std::cout << "Room Name: " << Globals::roomList_g[i].roomName << std::endl;
			std::cout << "Room Number: " << Globals::roomList_g[i].rNumber << std::endl;
			std::cout << "Room Cost (per day): $" << Globals::roomList_g[i].costPerDay << std::endl;
			std::cout << "Room Vacancy status (0 = Occupied, 1 = Vacant): " << Globals::roomList_g[i].isVacant << std::endl;
			std::cout << "------------------" << std::endl;
	}
}

void Room::printAllVacantRooms() {
	system("cls");
	std::cout << "==============================" << std::endl;
	std::cout << "        Vacant Rooms" << std::endl;
	std::cout << "==============================\n" << std::endl;

	for (int i = 0; i < Globals::roomList_g.size(); i++) {
		if (Globals::roomList_g[i].isVacant == true) {
			std::cout << "Room Name: " << Globals::roomList_g[i].roomName << std::endl;
			std::cout << "Room Number: " << Globals::roomList_g[i].rNumber << std::endl;
			std::cout << "Room Cost (per day): " << Globals::roomList_g[i].costPerDay << std::endl;
			std::cout << "------------------" << std::endl;
		}
	}
}


//Check In	- TO DO - Refactor these functions
void Room::checkUserIn() {
	Room::printAllVacantRooms();
	std::cout << "Please enter the room number of the room you wish to book" << std::endl;

	std::cin.clear();				// Restore input stream to working state

	int userPickRoom;
	std::cin >> userPickRoom;
	
	Room::findRoom(userPickRoom);
}

void Room::findRoom(int roomNumber) {


	bool checkUserInLoop = true;
	bool findRoomStatus = false;
	int roomIndex;

	while (checkUserInLoop) {

		for (int i = 0; i < Globals::roomList_g.size(); i++) {
			if (Globals::roomList_g[i].rNumber == roomNumber) {

				roomIndex = i;	//assign roomIndex to the index matched in list
				findRoomStatus = true;

			}
		}

		if (findRoomStatus == true && Globals::roomList_g[roomIndex].isVacant == true) {
			//Get Current Time to set check in property
			SYSTEMTIME currentTime;
			GetLocalTime(&currentTime);


			//Set Room Vacant Status to false
			Globals::roomList_g[roomIndex].isVacant = false;

			//Assign the matched room object in the list to the current user object 
			Globals::roomList_g[roomIndex].u = Globals::currentUser;

			//Assign Check In Time
			Globals::roomList_g[roomIndex].checkIn.wMonth = currentTime.wMonth;
			Globals::roomList_g[roomIndex].checkIn.wDay = currentTime.wDay;

			//Print Confirmation
			system("cls");
			std::cout << R"(
   _____                             _ 
  / ____|                           | |
 | (___  _   _  ___ ___ ___  ___ ___| |
  \___ \| | | |/ __/ __/ _ \/ __/ __| |
  ____) | |_| | (_| (_|  __/\__ \__ \_|
 |_____/ \__,_|\___\___\___||___/___(_)                                      
			)" << std::endl;

			std::cout << "\nRoom " << roomNumber << " has been booked succesfully by " << Globals::roomList_g[roomIndex].u.username << std::endl;
			std::cout << "\n-------------------" << std::endl;
			std::cout << "Check In Month: " << Globals::roomList_g[roomIndex].checkIn.wMonth << std::endl;
			std::cout << "-------------------" << std::endl;
			std::cout << "Check In Day: " << Globals::roomList_g[roomIndex].checkIn.wDay << std::endl;
			std::cout << "-------------------" << std::endl;
			Sleep(2500);
		}

		else {
			std::cout << "\nRoom not found, please try again...." << std::endl;
			Sleep(2000);
		}

		Util::printLoggedInMenu();
	}
}



//Check Out	- TO DO - Refactor this function
void Room::checkUserOut() {

	system("cls");
	std::cout << "==========================" << std::endl;
	std::cout << "Rooms booked under " << Globals::currentUser.username << std::endl;
	std::cout << "==========================" << std::endl;

	//Itereates through RoomList and prints out the current logged in users booked rooms
	for (Room r : Globals::roomList_g) {
		if (r.u.username == Globals::currentUser.username) {
			std::cout << "Room Name: " << r.roomName << std::endl;
			std::cout << "Room Number: " << r.rNumber << std::endl;
			std::cout << "Room Cost (per day): " << "$" << r.costPerDay << std::endl;
			std::cout << "Room Check In Month: " << r.checkIn.wMonth << std::endl;
			std::cout << "Room Check In Day: " << r.checkIn.wDay << std::endl;
			std::cout << "---------------" << std::endl;
		}
	}


	bool chkUserOutLoop = true;

	while (chkUserOutLoop) {
		std::cout << "Please enter the room number you wish to check out from" << std::endl;

		std::cin.clear();

		int userPickRoomChkOut;
		std::cin >> userPickRoomChkOut;


		//Find Room
		bool findRoomStatus = false;
		int roomIndex;

		for (int i = 0; i < Globals::roomList_g.size(); i++) {
			if (Globals::roomList_g[i].rNumber == userPickRoomChkOut) {
				roomIndex = i;
				findRoomStatus = true;
			}
		}

		if (findRoomStatus == true && Globals::roomList_g[roomIndex].u.username == Globals::currentUser.username) {
			//Get Current Time and store it into our buffer
			SYSTEMTIME getCurrentTime;
			GetLocalTime(&getCurrentTime);


			//Set The Room to Vacant
			Globals::roomList_g[roomIndex].isVacant = true;

			//Set Room CheckOut Time
			Globals::roomList_g[roomIndex].checkOut.wMonth = getCurrentTime.wMonth;
			Globals::roomList_g[roomIndex].checkOut.wDay = getCurrentTime.wDay;

			//Create Invoice and add to global invoice vector

			Invoice newInvoice;

			newInvoice.room = Globals::roomList_g[roomIndex];
			newInvoice.invoiceName = "Standard Invoice";
			newInvoice.invoiceNumber = Invoice::getLastInvoiceNumber() + 1;



			/*Calculating Days Between Check In and Check Out*/
			//Variables To Pass to dateToTimeT()
			int chkInDay = Globals::roomList_g[roomIndex].checkIn.wDay;
			int chkInMonth = Globals::roomList_g[roomIndex].checkIn.wMonth;
			int chkInYear = Globals::roomList_g[roomIndex].checkIn.wYear;

			int chkOutDay = Globals::roomList_g[roomIndex].checkOut.wDay;
			int chkOutMonth = Globals::roomList_g[roomIndex].checkOut.wMonth;
			int chkOutYear = Globals::roomList_g[roomIndex].checkOut.wYear;


			time_t checkInDate = Util::dateToTimeT(chkInMonth, chkInDay, 2022);			//<--- fix hardcoding later, keep the year hardcoded because theres no year member for invoices, it throws an error when passing an uninitalized variable
			time_t checkOutDate = Util::dateToTimeT(chkOutMonth, chkOutDay, 2022);		



			double differenceInSecs = difftime(checkOutDate, checkInDate);
			long daysDifference = (long)(differenceInSecs / (60 * 60 * 24));

			newInvoice.finalCost = daysDifference * Globals::roomList_g[roomIndex].costPerDay;



			//Add Invoice Object to Vector
			Globals::invoiceList_g.push_back(newInvoice);

			//Generate Invoice
			Invoice::writeInvoicesToFile(newInvoice);

			//Set Room User to Empty Buffer User (remove user object assosciated with room)
			User bufferUser;
			Globals::roomList_g[roomIndex].u = bufferUser;

			std::cout << "\nRoom Number " << Globals::roomList_g[roomIndex].rNumber << " has been checked out succesfully!" << std::endl;
			std::cout << "Invoice Generated!" << std::endl;
			Sleep(2000);

		}

		else {
			std::cout << "\nCould not find the room you were looking for, please try again...." << std::endl;
			Sleep(2000);
		}

		Util::printLoggedInMenu();
	}
}


//Populating
void Room::populateRoomList(int numOfRooms) {

	for (int i = 0; i < numOfRooms; i++) {
		int randRoomNumb = rand() % 100 + 1;
		int randCost = rand() % 150 + 200;

		//Add Duplicate check here

		Room newRoom;
		newRoom.roomName = "Standard Hotel Room";
		newRoom.rNumber = randRoomNumb;
		newRoom.costPerDay = randCost;

		Globals::roomList_g.push_back(newRoom);
	}

}
