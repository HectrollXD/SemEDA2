/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:10:00
*/


#include <iostream>
#include <cstring>
#include "products.h"


using std::string;
using std::endl;
using std::to_string;


///------------------------------------------------------------------------------------------------- Constructor
//-------------------------------------------------------------------------------------------------- base
Product::Product() : isDeleted(false) {}

///------------------------------------------------------------------------------------------------- Getters
//-------------------------------------------------------------------------------------------------- name
const char *Product::getDescription() {
	return this->description;
}

//-------------------------------------------------------------------------------------------------- id
const char *Product::getId() {
	return this->id;
}

//-------------------------------------------------------------------------------------------------- deleted
bool Product::getIsDeleted() const {
	return this->isDeleted;
}

//-------------------------------------------------------------------------------------------------- name
const char *Product::getName(){
	return this->name;
}

//-------------------------------------------------------------------------------------------------- price
float Product::getPrice() const {
	return this->price;
}

//-------------------------------------------------------------------------------------------------- weight unit
const char *Product::getWeightUnit() {
	return this->weightUnit;
}

///------------------------------------------------------------------------------------------------- Setters
//-------------------------------------------------------------------------------------------------- description
void Product::setDescription(const char description[MAX_CHARS_OF_DESCRIPTION]) {
	strcpy(this->description, description);
}

//-------------------------------------------------------------------------------------------------- id
void Product::setId(const char id[MAX_CHARS_OF_ID]) {
	strcpy(this->id, id);
}

//-------------------------------------------------------------------------------------------------- delete
void Product::setIsDeleted(const bool &isDeleted) {
	this->isDeleted = isDeleted;
}

//-------------------------------------------------------------------------------------------------- name
void Product::setName(const char name[MAX_CHARS_OF_NAME]) {
	strcpy(this->name, name);
}

//-------------------------------------------------------------------------------------------------- price
void Product::setPrice(const float &price) {
	this->price = price;
}

//-------------------------------------------------------------------------------------------------- weight unit
void Product::setWeightUnit(const char weightUnit[MAX_CHARS_OF_WU]) {
	strcpy(this->weightUnit, weightUnit);
}

///------------------------------------------------------------------------------------------------- Methods
//-------------------------------------------------------------------------------------------------- fill with spaces (string)
string Product::fillWithSpaces(const string &str, const unsigned short &weight){
	string strCpy = str;
	unsigned short i = str.length();

	while( i < weight-1){
		strCpy += ' ';
		i++;
	}

	strCpy += '\0';

	return strCpy;
}

//-------------------------------------------------------------------------------------------------- fill with spaces (char)
void Product::fillWithSpaces(char *str, const unsigned short &weight) {
	unsigned short i = strlen(str);

	while( i < weight-1){
		str[i++] = ' ';
	}

	str[i++] = '\0';
}

//-------------------------------------------------------------------------------------------------- to string
string Product::toString() const {
	string prodString = "", aux = "";

	if( ! this->isDeleted ){
		aux = this->id;
		prodString += "Producto: " + aux;
		prodString +=" ----------------------\n";
		aux = this->name;
		prodString +="Nombre: " + aux + " \n";
		prodString +="Precio: " + to_string(this->price) + " \n";
		aux = this->description;
		prodString +="Descripcion: " + aux + " \n";
		aux = this->weightUnit;
		prodString +="Unidad de peso: " + aux + " \n\n";
	}

	return prodString;
}

//-------------------------------------------------------------------------------------------------- from string
void Product::fromString(const string &product) {
	string productCpy(product), aux = "";
	int posOfChar;

	// finding, set and delete ID
	posOfChar = productCpy.find_first_of("|");
	aux = productCpy.substr(0, posOfChar);
	productCpy.erase(0, posOfChar+1);
	this->setId(aux.c_str());
	// finding, set and delete NAME
	posOfChar = productCpy.find_first_of("|");
	aux = productCpy.substr(0, posOfChar);
	productCpy.erase(0, posOfChar+1);
	aux = fillWithSpaces(aux, MAX_CHARS_OF_NAME);
	this->setName(aux.c_str());
	// finding, set and delete PRICE
	posOfChar = productCpy.find_first_of("|");
	aux = productCpy.substr(0, posOfChar);
	productCpy.erase(0, posOfChar+1);
	this->setPrice( (aux.length() > 0) ? (float) stof(aux) : 0.0);
	// finding, set and delete DESCRIPTION
	posOfChar = productCpy.find_first_of("|");
	aux = productCpy.substr(0, posOfChar);
	productCpy.erase(0, posOfChar+1);
	aux = fillWithSpaces(aux, MAX_CHARS_OF_DESCRIPTION);
	this->setDescription(aux.c_str());
	// finding, set and delete WEIGHT UNIT
	posOfChar = productCpy.find_first_of("|");
	aux = productCpy.substr(0, posOfChar);
	productCpy.erase(0, posOfChar+1);
	aux = fillWithSpaces(aux, MAX_CHARS_OF_WU);
	this->setWeightUnit(aux.c_str());
	// set IS DELETE
	this->setIsDeleted((productCpy.length() > 0) ? (bool) stoi(productCpy) : 0);
}


//-------------------------------------------------------------------------------------------------- is empty
bool Product::isEmpty() const {
	return(
		strlen(this->id) == 0 || strcmp(this->name, "") == 0 || strcmp(this->description, "") == 0
	);
}


///------------------------------------------------------------------------------------------------- Operators
//-------------------------------------------------------------------------------------------------- >>
std::istream& operator >> (std::istream &is, Product &product) {
	string strProduct = "";

	getline(is, strProduct, '\n');
	product.fromString(strProduct);

	return is;
}

//-------------------------------------------------------------------------------------------------- <<
std::ostream& operator << (std::ostream &os, Product &product) {
	char strProduct[MAX_STR_PRODUCT] = {};

	sprintf(
		strProduct, "%s|%s|%.2f|%s|%s|%i",
		product.getId(), product.getName(), product.getPrice(), product.getDescription(),
		product.getWeightUnit(), product.getIsDeleted()
	);
	Product::fillWithSpaces(strProduct, MAX_STR_PRODUCT);
	os<<strProduct;

	return os;
}
