/**
	@Autor: Hector Geovanny Rodriguez Martinez.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "products.h"


using namespace std;


#ifdef _WIN32
	#define CLEAR "cls"
	#define IS_WINDOWS true
#else
	#define CLEAR "clear"
	#define IS_WINDOWS false
#endif // _WIN32
#define MAX_REGS 50
enum {ADD = 'A', SHOW_ALL, FIND, DELETE, EXIT};


void addRegister(Product *array[MAX_REGS], short &counterRegs);
void showAllRegisters(Product *array[MAX_REGS], short &counterRegs);
void findProduct(Product *array[MAX_REGS], short &counterRegs);
short findByID(
	Product *array[MAX_REGS], short &counterRegs, const char idToFind[MAX_CHARS_OF_ID]
);
void deleteRegister(Product *array[MAX_REGS], short &counterRegs);
char printMenu();
void color();
void pauseProgram();
void invalidOption();
void principalProgram(Product *array[MAX_REGS], short &counterRegs);
void printProduct(Product *product);


void color(){
	if( IS_WINDOWS ){
		system("color f0");
	}
}

//--------------------------------------------------------------------------------------------------
void printProduct(Product *product){
	if( ! product->isDeleted ){
		std::cout<<"Producto: "<<product->id;
		std::cout<<" ----------------------"<<std::endl;
		std::cout<<"Nombre: "<<product->name<<std::endl;
		std::cout<<"Precio: "<<product->price<<std::endl;
		std::cout<<"Descripcion: "<<product->description<<std::endl;
		std::cout<<"Unidad de peso: "<<product->weightUnit<<std::endl<<std::endl;
	}
}


//--------------------------------------------------------------------------------------------------
void addRegister(Product *array[MAX_REGS], short &counterRegs){
	Product *product = new Product;
	short regExistPos = -1, insertInPos = -1;
	bool isToAdd = false;
	char option = '\0';
	string aux = "";

	cout<<"Agregar nuevo registro."<<endl<<endl;

	if( product == nullptr || (counterRegs + 1) == MAX_REGS ){
		cout<<"No fue posible crear un nuevo registro :("<<endl<<endl;
	}
	else{
		product->isDeleted = false;
		cout<<"Codigo del producto: ";
		cin>>product->id;
		cin.ignore(1);
		cout<<"Nombre del producto: ";
		getline(cin, product->name, '\n');
		cout<<"Precio del producto: ";
		cin>>product->price;
		cin.ignore(1);
		cout<<"Descripcion del producto: ";
		getline(cin, product->description, '\n');
		cout<<"Unidad de peso del producto: ";
		getline(cin, product->weightUnit, '\n');

		regExistPos = findByID(array, counterRegs, product->id);

		if( regExistPos == -1 ){
			isToAdd = true;
			insertInPos = ++counterRegs;
		}
		else{
			insertInPos = regExistPos;

			if( array[regExistPos]->isDeleted ){
				isToAdd = true;
			}
			else{
				cout<<endl<<"Ya existe un producto con el mismo ID."<<endl;
				cout<<"¿Desea remplazarlo? (S / N): ";
				cin>>option;
				option = toupper(option);
				cin.ignore(1);

				if( option == 'S' ){
					isToAdd = true;
				}
			}
		}

		if ( isToAdd ){
			array[insertInPos] = product;
			cout<<endl<<"El producto se agrego satisfactoriamente."<<endl<<endl;
		}
	}

	pauseProgram();
}

//--------------------------------------------------------------------------------------------------
void showAllRegisters(Product *array[MAX_REGS], short &counterRegs){
	short i = 0;

	cout<<"Todos los registros."<<endl<<endl;

	if( counterRegs == -1 ){
		cout<<"No hay registros para mostrar :("<<endl<<endl;
	}
	else{
		while( i <= counterRegs ){
			printProduct(array[i]);
			i++;
		}
	}

	pauseProgram();
}

//--------------------------------------------------------------------------------------------------
void findProduct(Product *array[MAX_REGS], short &counterRegs){
	char idToFind[MAX_CHARS_OF_ID];
	short posOfFind;

	cout<<"Buscar un registro."<<endl<<endl;

	if( counterRegs == -1 ){
		cout<<"No hay registros para buscar :("<<endl<<endl;
	}
	else{
		cout<<"Ingrese el codigo del producto a localizar."<<endl;
		cout<<"Codigo: ";
		cin>>idToFind;
		cin.ignore(1);
		cout<<endl;

		posOfFind = findByID(array, counterRegs, idToFind);

		if( posOfFind == -1 || array[posOfFind]->isDeleted ){
			cout<<"No se ha podido localizar el producto solicitado :("<<endl<<endl;
		}
		else{
			printProduct(array[posOfFind]);
		}
	}

	pauseProgram();
}

//--------------------------------------------------------------------------------------------------
short findByID(
	Product *array[MAX_REGS], short &counterRegs, const char idToFind[MAX_CHARS_OF_ID]
){
	short i = 0;

	while( i <= counterRegs ){
		if( strcmp(array[i]->id, idToFind ) == 0 ){
			return i;
		}
		i++;
	}

	return -1;
}

//--------------------------------------------------------------------------------------------------
void deleteRegister(Product *array[MAX_REGS], short &counterRegs){
	char idToFind[MAX_CHARS_OF_ID];
	char option = '\0';
	short posOfFind = -1;

	cout<<"Eliminar un registro."<<endl<<endl;

	if( counterRegs == -1 ){
		cout<<"No hay registros para eliminar :("<<endl<<endl;
	}
	else{
		cout<<"Ingrese el codigo del producto a eliminar."<<endl;
		cout<<"Codigo: ";
		cin>>idToFind;
		cin.ignore(1);
		cout<<endl;

		posOfFind = findByID(array, counterRegs, idToFind);

		if( posOfFind == -1 || array[posOfFind]->isDeleted ){
			cout<<"No se ha podido localizar el producto solicitado :("<<endl<<endl;
		}
		else{
			printProduct(array[posOfFind]);
			cout<<"¿Desea eliminarlo? (S / N): ";
			cin>>option;
			cin.ignore(1);
			option = toupper(option);

			if( option == 'S' ){
				array[posOfFind]->isDeleted = true;
				cout<<endl<<"Se ha eliminado el registro."<<endl<<endl;
			}
			else{
				cout<<endl<<"No se elimino el registro por cancelacion."<<endl<<endl;
			}
		}
	}

	pauseProgram();
}

//--------------------------------------------------------------------------------------------------
char printMenu(){
	char option = '\0';

	color();

	system(CLEAR);
	cout<<"Menu principal"<<endl<<endl;
	cout<<"Ingresa una opcion."<<endl;
	cout<<(char)ADD<<") Agregar nuevo registro."<<endl;
	cout<<(char)SHOW_ALL<<") Mostrar todos los registros."<<endl;
	cout<<(char)FIND<<") Buscar un registro."<<endl;
	cout<<(char)DELETE<<") Eliminar un registro."<<endl;
	cout<<(char)EXIT<<") Salir."<<endl<<endl;
	cout<<"Opcion ingresada: ";
	cin>>option;
	cin.ignore(1);
	system(CLEAR);

	return toupper(option);
}

//--------------------------------------------------------------------------------------------------
void pauseProgram(){
	cout<<"presiona entrar para continuar...";
	cin.ignore(1);
	system(CLEAR);
}

//--------------------------------------------------------------------------------------------------
void invalidOption(){
	cout<<"Opcion invalida."<<endl;
	pauseProgram();
}

//--------------------------------------------------------------------------------------------------
void principalProgram(Product *array[MAX_REGS], short &counterRegs){
	char option = '\0';
	do{
		option = printMenu();

		switch( option ){
			case ADD:
				addRegister(array, counterRegs);
				break;
			case SHOW_ALL:
				showAllRegisters(array, counterRegs);
				break;
			case FIND:
				findProduct(array, counterRegs);
				break;
			case DELETE:
				deleteRegister(array, counterRegs);
				break;
			case EXIT:
				break;
			default:
				invalidOption();
				break;
		}
	} while( option != EXIT );
}
