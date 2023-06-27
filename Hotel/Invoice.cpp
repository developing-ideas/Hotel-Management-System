#include <iostream>				//STL Input/Output - cin, cout, getline()
#include <string>				//String Class	
#include <sstream>				//String Stream class (for type conversion)
#include <ctime>				//ctime class	- time type
#include <fstream>				//fstream class - write to file
#include <cstdlib>				//rand();	
#include "Globals.h"			//Globals
#include "Invoice.h"			//Invoice header
#include "Room.h"				//Room class
#include "Util.h"				//Util class




/*Function Definitions / Implementation*/

void Invoice::printInvoiceMenu() {

	Invoice::printAllUserInvoices();
	if (Util::backspaceCheck() == false) { Util::printLoggedInMenu(); }

}

void Invoice::printInvoice(Invoice invoice) {
	std::cout << "User Name: " << invoice.room.u.username << std::endl;
	std::cout << "Invoice Name: " << invoice.invoiceName << std::endl;
	std::cout << "Invoice Number: " << invoice.invoiceNumber << std::endl;
	std::cout << "Final Cost: " << invoice.finalCost << std::endl;
	std::cout << "Room Number: " << invoice.room.rNumber << std::endl;
}

void Invoice::printAllUserInvoices() {

	system("cls");

	if (!Globals::invoiceList_g.empty()) {

		std::cout << "=======================================" << std::endl;
		std::cout << "Invoice List" << std::endl;
		std::cout << "=======================================" << std::endl;

		for (Invoice i : Globals::invoiceList_g) {
			if (i.room.u.username == Globals::currentUser.username) {
				std::cout << "Invoice Name: " << i.invoiceName << std::endl;
				std::cout << "Invoice Number: " << i.invoiceNumber << std::endl;
				std::cout << "Invoice Total Cost: $" << i.finalCost << std::endl;
				std::cout << "Room Number: " << i.room.rNumber << std::endl;
				std::cout << "--------------------------------------------" << std::endl;
			}
		}

	}

	else {
		std::cout << "=======================================" << std::endl;
		std::cout << "Invoice List" << std::endl;
		std::cout << "=======================================" << std::endl;

		std::cout << "No Invoices Found" << std::endl;
	}
}


//File Handling
void Invoice::writeInvoicesToFile(Invoice invoice) {
	//Using stringStream to convert int to string
	std::stringstream ss;
	ss << Invoice::getLastInvoiceNumber();

	//Add a check later to see if file exists / invoice numbers clashing

	std::string fileName = "Hotel Invoice - Invoice Number " + ss.str() + ".txt";

	std::fstream fStrm;
	fStrm.open(fileName, std::ios::out);


	//Writing Details to File
	fStrm << "Invoice User: " << invoice.room.u.username;
	fStrm << "\n";
	fStrm << "Invoice Name: " << invoice.invoiceName;
	fStrm << "\n";
	fStrm << "Invoice Number: " << invoice.invoiceNumber;
	fStrm << "\n";
	fStrm << "Invoice Cost: $" << invoice.finalCost;
	fStrm << "\n";
	fStrm << "Room Number: " << invoice.room.rNumber;
	fStrm << "\n\n";

	fStrm << "Thank you for staying with us!";
	//Close File, cleanup
	fStrm.close();
	

}


//Getters 
int Invoice::getLastInvoiceNumber() {

	if (!Globals::invoiceList_g.empty()) {							//Prevents crash if this function is called whilst vector is empty
		return Globals::invoiceList_g.back().invoiceNumber;
	}
	else {
		//Do Nothing
	}
}