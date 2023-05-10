/**
	@Autor: Hector Geovanny Rodriguez Martinez.
	@Time: 00:02:00
*/


#include <iostream>


#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED


#define MAX_CHARS_OF_FLOAT 16
#define MAX_STR_PRODUCT 91
#define MAX_CHARS_OF_ID 11
#define MAX_CHARS_OF_NAME 17
#define MAX_CHARS_OF_DESCRIPTION 33
#define MAX_CHARS_OF_WU 9


class Product{
	private:
		char description[MAX_CHARS_OF_DESCRIPTION];
		char id[MAX_CHARS_OF_ID];
		bool isDeleted;
		char name[MAX_CHARS_OF_NAME];
		float price;
		char weightUnit[MAX_CHARS_OF_WU];

	public:
		Product();
		//getters
		const char *getDescription();
		const char *getId();
		bool getIsDeleted() const;
		const char *getName();
		float getPrice() const;
		const char *getWeightUnit();
		//setters
		void setDescription(const char description[MAX_CHARS_OF_DESCRIPTION]);
		void setId(const char id[MAX_CHARS_OF_ID]);
		void setIsDeleted(const bool &isDeleted);
		void setName(const char name[MAX_CHARS_OF_NAME]);
		void setPrice(const float &price);
		void setWeightUnit(const char weightUnit[MAX_CHARS_OF_WU]);

		// Methods
		static std::string fillWithSpaces(const std::string &str, const unsigned short &weight);
		static void fillWithSpaces(char *str, const unsigned short &weight);
		bool isEmpty() const;
		std::string toString() const;
		void fromString(const std::string &product);

		friend std::istream &operator >> (std::istream &is, Product &product);
		friend std::ostream &operator << (std::ostream &os, Product &product);
};


#endif // PRODUCTS_H_INCLUDED
