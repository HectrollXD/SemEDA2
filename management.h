/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:02:00
*/

#include <iostream>
#include "products.h"


#ifndef MANAGEMENT_H_INCLUDED
#define MANAGEMENT_H_INCLUDED

#define MAX_REGS 50
#define OUT_FILE_PATH "./files/registros.bin"


class Management{
	private:
		int counterOfRegs;
		Product products[MAX_REGS];

	public:
		// Constructor
		Management();

		// Getters
		const Product *getProducts();
		int getCounterOfRegs() const;
		// Setters
		void setProducts(Management &management);
		void setCounterOfRegs(const int &counter);
		// Methods
		std::string toString() const;
		bool isFull() const;
		bool isEmpty() const;
		bool isValidPos(const int &pos) const;
		void addRegister(const Product &prodToAdd, bool _replace(const bool &isToDelete));
		void deleteRegister(Product *prodToDelete, bool _delete(const bool &isToDelete));
		int findProduct(const char id[MAX_CHARS_OF_ID]) const;
		Product *recoverProduct(const int &posToRecover);
		void saveRegistersToFile();
		void readRegistersFromFileLXL(const std::string &pathOfFile);
		void readRegistersFromFileCXC(const std::string &pathOfFile);
};


#endif // MANAGEMENT_H_INCLUDED