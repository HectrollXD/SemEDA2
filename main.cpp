/**
	@Autor: Hector Geovanny Rodriguez Martinez.
	@Tiempo 00:03:00
*/


#include <iostream>
#include <clocale>
#include "program.h"


using std::cout;
using std::cin;
using std::endl;


int main(){
	setlocale(LC_CTYPE, "spanish");

	try{
		Program *program = new Program();

		program->insertWithBuffer();

		program->principal();
	}
	catch(const char *ex){
		cout<<ex<<endl;
	}

    return 0;
}
