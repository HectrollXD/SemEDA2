/**
	@Autor: Hector Geovanny Rodriguez Martinez.
*/


#include <iostream>


#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

#define MAX_CHARS_OF_ID 11


struct Product{
	std::string description;
	char id[MAX_CHARS_OF_ID];
	bool isDeleted;
	std::string name;
	float price;
	std::string weightUnit;
};


#endif // PRODUCTS_H_INCLUDED
