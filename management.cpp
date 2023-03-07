/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:25:00
*/


#include <iostream>
#include <cstring>
#include "management.h"


using std::string;


///------------------------------------------------------------------------------------------------- Constructor
//-------------------------------------------------------------------------------------------------- base
Management::Management() : counterOfRegs(-1) {}

///------------------------------------------------------------------------------------------------- Getters
//-------------------------------------------------------------------------------------------------- list
const Product* Management::getProducts() {
	return this->products;
}

//-------------------------------------------------------------------------------------------------- counter
int Management::getCounterOfRegs() const {
	return this->counterOfRegs;
}

///------------------------------------------------------------------------------------------------- Setters
//-------------------------------------------------------------------------------------------------- list
void Management::setProducts(Management &management) {
	int i = 0;

	while( i <= management.getCounterOfRegs() ){
		Product prod(management.getProducts()[i]);

		this->products[i] = prod;
		i++;
	}
}

//-------------------------------------------------------------------------------------------------- counter
void Management::setCounterOfRegs(const int& counter) {
	this->counterOfRegs = counter;
}

///------------------------------------------------------------------------------------------------- Methods
//-------------------------------------------------------------------------------------------------- to string
// Retorna la lista como string.
string Management::toString() const{
	string aux = "";
	int i = 0;

	while( i <= this->counterOfRegs ){
		aux += this->products[i].toString();
		i++;
	}

	return aux;
}

//-------------------------------------------------------------------------------------------------- full
// Verifica si la lista est� llena
bool Management::isFull() const {
	return this->counterOfRegs == (MAX_REGS - 1);
}

//-------------------------------------------------------------------------------------------------- empty
// Verifica si la lista est� vac�a.
bool Management::isEmpty() const {
	return this->counterOfRegs == -1;
}

//-------------------------------------------------------------------------------------------------- valid pos
// Valida si la posici�n otorgada es v�lida.
bool Management::isValidPos(const int& pos) const{
	if( pos == -1 || pos >= MAX_REGS ){
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------- add
// A�ande un nuevo registro en base a un producto, una posici�n y una funci�n que decida si eliminar
// un registro existente o no.
void Management::addRegister(const Product& prodToAdd, bool _replace(const bool &isToDelete)) {
	Product *newProd = nullptr;
	bool isToAdd = true;
	int insertInPos = -1;

	if( isFull() ){
		throw("No se admiten m�s registros. Se ha llenado la capacidad de los registros.");
	}

	newProd = new Product(prodToAdd);

	insertInPos = findProduct(newProd->getId());

	if(insertInPos == -1 ){
		this->counterOfRegs++;
		insertInPos = this->counterOfRegs;
	}
	else{
		if( !this->products[insertInPos].getIsDeleted() ){
			isToAdd = _replace(false);
		}
	}

	if( !isToAdd ){
		throw("\nLa operaci�n fue cancelada por petici�n.");
	}

	this->products[insertInPos] = *newProd;
}

//-------------------------------------------------------------------------------------------------- delete
// Elimina un registro en base a un producto otorgado.
void Management::deleteRegister(Product *prodToDelete, bool _delete(const bool &isToDelete)) {
	if( !_delete(true) ){
		throw("\nLa operaci�n fue cancelada por petici�n.");
	}

	prodToDelete->setIsDeleted(true);
}

//-------------------------------------------------------------------------------------------------- find
// Busca un producto en base a un id y retorna una posici�n.
int Management::findProduct(const char id[MAX_CHARS_OF_ID]) const {
	int i = 0;
	Product aux;

	while( i <= this->counterOfRegs ){
		aux = this->products[i];

		if( strcmp(aux.getId(), id) == 0 ){
			return i;
		}

		i++;
	}

	return -1;
}

//-------------------------------------------------------------------------------------------------- recover
// Retorna un producto en base a una posici�n otorgada.
Product* Management::recoverProduct(const int& posToRecover){
	if( isValidPos(posToRecover) ){
		return &this->products[posToRecover];
	}
	return nullptr;
}
