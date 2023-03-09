/**
	@Autor: Hector Geovanny Rodriguez Martinez
	@Time: 00:01:00
*/

#include "program.h"

#include <iostream>
#include "management.h"
#include "products.h"


#ifdef _WIN32
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif // _WIN32
enum {ADD = 'A', SHOW_ALL, FIND, DELETE, EXIT};


using std::string;
using std::cout;
using std::cin;
using std::endl;
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
//--------------------------------------------------------------------------------------------------
const Management* Program::getManagementList(){
	return this->managementList;
}

///------------------------------------------------------------------------------------------------- Setters
//--------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
void Program::addProductOption() {
	string aux = "";
	Product product;

	cout<<"Agregar nuevo registro."<<endl<<endl;

	if( this->managementList->isFull() ){
		cout<<"No es posible agregar un nuevo registro."<<endl<<endl;
	}
	else{
		cout<<"Código del producto: ";
		getline(cin, aux, '\n');
		product.setId(aux.c_str());
		cout<<"Nombre del producto: ";
		getline(cin, aux, '\n');
		product.setName(aux);
		cout<<"Precio del producto: ";
		getline(cin, aux, '\n');
		product.setPrice((float) stof(aux));
		cout<<"Descripción del producto: ";
		getline(cin, aux, '\n');
		product.setDescription(aux);
		cout<<"Unidad de peso del producto: ";
		getline(cin, aux, '\n');
		product.setWeightUnit(aux);

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

//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
void Program::pauseProgram() {
	cout<<"presiona entrar para continuar...";
	cin.ignore(1);
	system(CLEAR);
}

//--------------------------------------------------------------------------------------------------
void Program::invalidOption() {
	cout<<"Opción inválida."<<endl;
	pauseProgram();
}

//--------------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------------- read file character per character
void Program::readFileCPerC(const string& pathOfFile) {
	//TODO: Terminar la lectura de caracter por caracter.
}

//-------------------------------------------------------------------------------------------------- read file line per line
void Program::readFileLPerL(const string& pathOfFile) {
	try{
		this->managementList->readRegistersFromFile(pathOfFile);
	}
	catch( const char *ex ){
		cout<<ex<<endl;
	}

	pauseProgram();
}

//-------------------------------------------------------------------------------------------------- save registers to file
void Program::saveRegisters() {

}

//-------------------------------------------------------------------------------------------------- principal logig
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
				break;
			default:
				invalidOption();
				break;
		}
	} while( option != EXIT );
}
