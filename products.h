/**
	@Autor: Hector Geovanny Rodriguez Martinez.
	@Time: 00:00:00
*/


#include <iostream>


#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

#define MAX_CHARS_OF_ID 11


class Product{
	private:
		std::string description;
		char id[MAX_CHARS_OF_ID];
		bool isDeleted;
		std::string name;
		float price;
		std::string weightUnit;

	public:
		Product();
		//getters
		std::string getDescription() const;
		const char *getId();
		bool getIsDeleted() const;
		std::string getName() const;
		float getPrice() const;
		std::string getWeightUnit() const;
		//setters
		void setDescription(const std::string &description);
		void setId(const char id[MAX_CHARS_OF_ID] );
		void setIsDeleted(const bool &isDeleted);
		void setName(const std::string &name);
		void setPrice(const float &price);
		void setWeightUnit(const std::string &weightUnit);

		std::string toString() const;
};


#endif // PRODUCTS_H_INCLUDED
