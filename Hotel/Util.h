#pragma once

static class Util {
private:

public:

	/*Function Prototypes / Declaration*/

	//Menus
	static void printMainMenu();
	static void printLoggedInMenu();

	//Login
	static void loginCheck();

	//Type Conversion
	static time_t dateToTimeT(int month, int day, int year);

	//Misc
	static bool backspaceCheck();

};
