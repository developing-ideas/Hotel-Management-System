#pragma once
#include <Windows.h>
#include "User.h"			//User class


class Room {
private:


public:
	std::string roomName = "";
	int rNumber;
	int costPerDay;
	User u;
	SYSTEMTIME checkIn;
	SYSTEMTIME checkOut;

	bool isVacant = true;

	/*Function Prototypes / Declarations*/
	Room();

	static void populateRoomList(int numOfRooms);

	static void printAllRooms();
	static void printAllVacantRooms();

	static void checkUserIn();
	static void checkUserOut();

	static void findRoom(int roomNumber);

};