/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:00:30
*/

#include <iostream>
#include "management.h"


#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED


class Program{
	private:
		Management *managementList;

	protected:
		//Methods
		void addProductOption();
		void deleteProductOption();
		void findProductOption();
		static bool inCaseOfExisting(const bool &isToDelete);
		void invalidOption();
		void pauseProgram();
		char printMenu() const;
		void saveRegisters();
		void showProductsOption();

	public:
		// Constructor
		Program();
		// Destructor
		~Program();
		// Getters
		const Management *getManagementList();
		// Setters
		void setManagementList(Management &mng);
		// Methods
		void methodToReadFile(const std::string &path);
		void principal();
};


#endif // PROGRAM_H_INCLUDED
