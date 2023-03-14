/**
	@Autor: Hector Geovanny Rodriguez Martinez.
	@Tiempo 01:13:46
*/


#include <iostream>
#include "products.h"
#include "program.cpp"


using std::string;


int main(int argv, char *args[]){
	Product *products[MAX_CHARS_OF_ID];
	short counterRegs = -1;
	string path;

	if( argv > 1 ){
		for( int i=1; i<argv; i++ ){
			path = args[i];
			methodToReadFile(products, counterRegs, path);
		}
	}

	principalProgram(products, counterRegs);

    return 0;
}
