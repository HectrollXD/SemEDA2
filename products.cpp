/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:14:00
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
string Product::getDescription() const {
	return this->description;
}

//-------------------------------------------------------------------------------------------------- id
const char* Product::getId() {
	return this->id;
}

//-------------------------------------------------------------------------------------------------- deleted
bool Product::getIsDeleted() const {
	return this->isDeleted;
}

//-------------------------------------------------------------------------------------------------- name
string Product::getName() const {
	return this->name;
}

//-------------------------------------------------------------------------------------------------- price
float Product::getPrice() const {
	return this->price;
}

//-------------------------------------------------------------------------------------------------- weight unit
string Product::getWeightUnit() const {
	return this->weightUnit;
}

///------------------------------------------------------------------------------------------------- Setters
//-------------------------------------------------------------------------------------------------- description
void Product::setDescription(const std::string& description) {
	this->description = description;
}

//-------------------------------------------------------------------------------------------------- id
void Product::setId(const char id[MAX_CHARS_OF_ID]) {
	strcpy(this->id, id);
}

//-------------------------------------------------------------------------------------------------- delete
void Product::setIsDeleted(const bool& isDeleted) {
	this->isDeleted = isDeleted;
}

//-------------------------------------------------------------------------------------------------- name
void Product::setName(const std::string& name) {
	this->name = name;
}

//-------------------------------------------------------------------------------------------------- price
void Product::setPrice(const float& price) {
	this->price = price;
}

//-------------------------------------------------------------------------------------------------- weight unit
void Product::setWeightUnit(const std::string& weightUnit) {
	this->weightUnit = weightUnit;
}

///------------------------------------------------------------------------------------------------- Methods
//-------------------------------------------------------------------------------------------------- to string
string Product::toString() const {
	string aux = "";
	string id = this->id;

	if( ! this->isDeleted ){
		aux += "Producto: " + id;
		aux +=" ----------------------\n";
		aux +="Nombre: " + this->name + " \n";
		aux +="Precio: " + to_string(this->price) + " \n";
		aux +="Descripcion: " + this->description + " \n";
		aux +="Unidad de peso: " + this->weightUnit + " \n\n";
	}

	return aux;
}

//-------------------------------------------------------------------------------------------------- is empty
bool Product::isEmpty() const {
	return(
		strlen(this->id) == 0 || this->name.compare("") == 0 || this->description.compare("") == 0
	);
}


///------------------------------------------------------------------------------------------------- Operators
//-------------------------------------------------------------------------------------------------- >>
std::istream& operator >> (std::istream &is, Product &product) {
	string aux = "";

	// id
	getline(is, aux, '|');
	product.setId(aux.c_str());
	// name
	getline(is, aux, '|');
	product.setName(aux);
	// price
	getline(is, aux, '|');
	product.setPrice((float) stof(aux));
	// description
	getline(is, aux, '|');
	product.setDescription(aux);
	// weight
	getline(is, aux, '|');
	product.setWeightUnit(aux);
	// is deleted
	getline(is, aux, '\n');
	product.setIsDeleted((bool) stoi(aux));

	return is;
}

//-------------------------------------------------------------------------------------------------- <<
std::ostream& operator << (std::ostream &os, Product &product) {
	os<<product.getId()<<"|";
	os<<product.getName()<<"|";
	os<<to_string(product.getPrice())<<"|";
	os<<product.getDescription()<<"|";
	os<<product.getWeightUnit()<<"|";
	os<<product.getIsDeleted()<<endl;

	return os;
}
