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
		char printMenu() const;
		void addProductOption();
		void showProductsOption();
		void findProductOption();
		void deleteProductOption();
		void pauseProgram();
		void invalidOption();
		static bool inCaseOfExisting(const bool &isToDelete);

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
		void principal();
		void insertWithBuffer();
};


#endif // PROGRAM_H_INCLUDED
