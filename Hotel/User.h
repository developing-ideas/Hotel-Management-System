#pragma once


class User {
private:
	
public:
	bool isBanned = false;
	short privID = 0;
	std::string username, password = "";
	std::string banReason = "";



	User();
	User(std::string uName, std::string pWord, std::string firstName, std::string lastName, short pLvl);



	static void registerAccount();
	static void changePassword();
};