#include <iostream>             //STL Input/Output - cout, cin, getline()
#include "Util.h"               //Util class
#include "Room.h"               //Room class
#include "Globals.h"            //Globals
#include "Admin.h"              //Admin class


//Forward Declaration
void initializeOnLaunch();


int main()
{
    initializeOnLaunch();
    Util::printMainMenu();

}



void initializeOnLaunch() {
    //Set Rand() seed
    srand(time(NULL));


    //Create Admin Account
    User admin;
    admin.username = "admin";
    admin.password = "admin";
    admin.privID = 1;

    //Add Admin User to User List
    Globals::userList_g.push_back(admin);

    //Populate Room List
    Room::populateRoomList(10);

}

