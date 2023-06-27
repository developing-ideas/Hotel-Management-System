#pragma once
#include <set>
#include <vector>
#include "User.h"
#include "Room.h"
#include "Invoice.h"

namespace Globals {

	//Global Variables
	extern std::vector<User> userList_g;
	extern std::vector<Room> roomList_g;
	extern std::vector<Invoice> invoiceList_g;

	extern User currentUser;

	


}
