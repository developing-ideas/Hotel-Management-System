#pragma once
#include "User.h"

class Admin : public User {
private:
	
public:
	static void printAdminMenu();
	static void printAllUsers();
	static void printAllUsersWithoutBackspace();			//Test, refactor this later


	static void banUser();
	static void setUserPriv();


	static void viewAllRooms();
	static void addRoom();
	static void delRoom();
	static void setRoomStatus();

	static void viewAllInvoices();


	

};