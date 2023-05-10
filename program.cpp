/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:20:00
*/

#include <iostream>

#include "program.h"
#include "management.h"
#include "products.h"


#ifdef _WIN32
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif // _WIN32
enum {ADD = 'A', SHOW_ALL, FIND, DELETE, EXIT};


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;


///------------------------------------------------------------------------------------------------- Constructor
//-------------------------------------------------------------------------------------------------- Base
Program::Program(): managementList(new Management()) {
	if( managementList == nullptr ){
		throw("Hubo un error al intentar crear el objeto para los registros.");
	}
}

///------------------------------------------------------------------------------------------------- Destructor
//-------------------------------------------------------------------------------------------------- destructor
Program::~Program() {
	delete (this->managementList);
	this->managementList = nullptr;
}

///------------------------------------------------------------------------------------------------- Getters
//-------------------------------------------------------------------------------------------------- management list
const Management* Program::getManagementList(){
	return this->managementList;
}

///------------------------------------------------------------------------------------------------- Setters
//-------------------------------------------------------------------------------------------------- management list
void Program::setManagementList(Management& mng){
	int i = 0;

	if( this->managementList == nullptr ){
		this->managementList = new Management(mng);
	}
	else{
		while( i <= mng.getCounterOfRegs() ){
			try{
				this->managementList->addRegister(mng.getProducts()[i], Program::inCaseOfExisting);
			}
			catch(const char *ex){
				throw(ex);
			}

			i++;
		}
	}
}


///------------------------------------------------------------------------------------------------- Methods
//-------------------------------------------------------------------------------------------------- print menu
char Program::printMenu() const {
	char option = '\0';

	system(CLEAR);
	cout<<"Menú principal"<<endl<<endl;
	cout<<"Ingresa una opción."<<endl;
	cout<<(char)ADD<<") Agregar nuevo registro."<<endl;
	cout<<(char)SHOW_ALL<<") Mostrar todos los registros."<<endl;
	cout<<(char)FIND<<") Buscar un registro."<<endl;
	cout<<(char)DELETE<<") Eliminar un registro."<<endl;
	cout<<(char)EXIT<<") Salir."<<endl<<endl;
	cout<<"Opción ingresada: ";
	cin>>option;
	cin.ignore(1);
	system(CLEAR);

	return toupper(option);
}

//-------------------------------------------------------------------------------------------------- add option
void Program::addProductOption() {
	Product product;
	float price = 0;
	char id[MAX_CHARS_OF_ID], name[MAX_CHARS_OF_NAME],
		description[MAX_CHARS_OF_DESCRIPTION], weightUnit[MAX_CHARS_OF_WU];

	cout<<"Agregar nuevo registro."<<endl<<endl;

	if( this->managementList->isFull() ){
		cout<<"No es posible agregar un nuevo registro."<<endl<<endl;
	}
	else{
		// TODO: Cambiar por char
		cout<<"Código del producto: ";
		cin.getline(id, MAX_CHARS_OF_ID);
		Product::fillWithSpaces(id, MAX_CHARS_OF_ID);
		product.setId(id);
		cout<<"Nombre del producto: ";
		cin.getline(name, MAX_CHARS_OF_NAME);
		Product::fillWithSpaces(name, MAX_CHARS_OF_NAME);
		product.setName(name);
		cout<<"Precio del producto: ";
		cin>>price;
		product.setPrice(price);
		cout<<"Descripción del producto: ";
		cin.getline(description, MAX_CHARS_OF_DESCRIPTION);
		product.fillWithSpaces(description, MAX_CHARS_OF_DESCRIPTION);
		product.setDescription(description);
		cout<<"Unidad de peso del producto: ";
		cin.getline(weightUnit, MAX_CHARS_OF_WU);
		Product::fillWithSpaces(weightUnit, MAX_CHARS_OF_WU);
		product.setWeightUnit(weightUnit);

		try{
			this->managementList->addRegister(product, Program::inCaseOfExisting);
			cout<<endl<<"El producto se agregó satisfactoriamente."<<endl<<endl;
		}
		catch(const char *ex){
			cout<<ex<<endl<<endl;
		}
	}

	pauseProgram();
}

//-------------------------------------------------------------------------------------------------- show option
void Program::showProductsOption() {
	cout<<"Todos los registros."<<endl<<endl;

	if( this->managementList->isEmpty() ){
		cout<<"No hay registros para mostrar :("<<endl<<endl;
	}
	else{
		cout<<managementList->toString();
	}

	pauseProgram();
}

//-------------------------------------------------------------------------------------------------- find option
void Program::findProductOption() {
	char idToFind[MAX_CHARS_OF_ID];
	Product *posOfProduct = nullptr;

	cout<<"Buscar un registro."<<endl<<endl;

	if( this->managementList->isEmpty() ){
		cout<<"No hay registros para buscar :("<<endl<<endl;
	}
	else{
		cout<<"Ingrese el codigo del producto a localizar."<<endl;
		cout<<"Codigo: ";
		cin>>idToFind;
		cin.ignore(1);
		cout<<endl;

		posOfProduct = this->managementList->recoverProduct(
			this->managementList->findProduct(idToFind)
		);

		if( posOfProduct == nullptr || posOfProduct->getIsDeleted() ){
			cout<<"No se ha podido localizar el producto solicitado :("<<endl<<endl;
		}
		else{
			cout<<posOfProduct->toString()<<endl<<endl;
		}
	}

	pauseProgram();
}

//-------------------------------------------------------------------------------------------------- delete option
void Program::deleteProductOption() {
	char idToFind[MAX_CHARS_OF_ID];
	Product *posOfProduct = nullptr;

	cout<<"Eliminar un registro."<<endl<<endl;

	if( this->managementList->isEmpty() ){
		cout<<"No hay registros para eliminar :("<<endl<<endl;
	}
	else{
		cout<<"Ingrese el codigo del producto a eliminar."<<endl;
		cout<<"Codigo: ";
		cin>>idToFind;
		cin.ignore(1);
		cout<<endl;

		posOfProduct = this->managementList->recoverProduct(
			this->managementList->findProduct(idToFind)
		);

		if( posOfProduct == nullptr || posOfProduct->getIsDeleted() ){
			cout<<"No se ha podido localizar el producto solicitado :("<<endl<<endl;
		}
		else{
			cout<<posOfProduct->toString();

			try{
				this->managementList->deleteRegister(posOfProduct, Program::inCaseOfExisting);
				cout<<endl<<"El producto se eliminó satisfactoriamente."<<endl<<endl;
			}
			catch( const char *ex ){
				cout<<ex<<endl<<endl;
			}
		}
	}

	pauseProgram();
}

//-------------------------------------------------------------------------------------------------- pause program
void Program::pauseProgram() {
	cout<<"presiona entrar para continuar...";
	cin.ignore(1);
	system(CLEAR);
}

//-------------------------------------------------------------------------------------------------- invalid option
void Program::invalidOption() {
	cout<<"Opción inválida."<<endl;
	pauseProgram();
}

//-------------------------------------------------------------------------------------------------- in case of existing register
// Static function to send a option menu for the add function in management class
bool Program::inCaseOfExisting(const bool &isToDelete){
	char option = '\0';
	string title = "El ID ingresado ya existe en los registros.";
	string message = "¿Desea remplazar el registro actual por el ingresado? [S / N]: ";

	if( isToDelete ){
		title = "Registro encontrado.";
		message = "¿Desea eliminar el registro? [S / N]: ";
	}

	cout<<endl<<title<<endl<<message;
	cin>> option;
	cin.ignore(1);

	if( toupper(option) == 'S' ){
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------- save registers to file
void Program::saveRegisters() {
	char option = '\0';

	cout<<"¿Desea guardar los registros? [S / N]: ";
	cin>>option;
	cin.ignore(1);
	option = toupper(option);

	if( option == 'S' ){
		try{
			this->managementList->saveRegistersToFile();
		}
		catch(const char *ex){
			cout<<ex<<endl;
			pauseProgram();
		}
	}
}

//-------------------------------------------------------------------------------------------------- method to read file
void Program::methodToReadFile(const string &path) {
	char option = '\0';

	cout<<"Archivo: " + path<<endl<<endl;
	cout<<"¿Desea elegir el método de lectura del archivo de linea por linea? [S / N]: ";
	cin>>option;
	cin.ignore(1);
	option = toupper(option);

	try{
		if( option == 'S' ){
			this->managementList->readRegistersFromFileLXL(path);
		}
		else{
			this->managementList->readRegistersFromFileCXC(path);
		}
	}
	catch(const char *ex){
		cout<<ex<<endl;
		pauseProgram();
	}
}

//-------------------------------------------------------------------------------------------------- principal logic
void Program::principal() {
	char option = '\0';

	do{
		option = printMenu();

		switch( option ){
			case ADD:
				addProductOption();
				break;
			case SHOW_ALL:
				showProductsOption();
				break;
			case FIND:
				findProductOption();
				break;
			case DELETE:
				deleteProductOption();
				break;
			case EXIT:
				saveRegisters();
				break;
			default:
				invalidOption();
				break;
		}
	} while( option != EXIT );
}
