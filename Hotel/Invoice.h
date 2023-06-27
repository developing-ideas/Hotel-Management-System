#pragma once
#include <Windows.h>

class Invoice {
private:

public:
	std::string invoiceName = "";
	int finalCost = 0;
	int invoiceNumber = 0;
	Room room;

	/*Function Declarations / Prototypes */

	static void printInvoiceMenu();
	void printInvoice(Invoice invoice);
	static void printAllUserInvoices();

	static int getLastInvoiceNumber();

	static void writeInvoicesToFile(Invoice invoice);

};