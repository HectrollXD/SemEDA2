/**
	@Autor: Hector Geovanny Rodriguez Martinez.
	@Tiempo 01:13:46
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

		program->principal();
	}
	catch(const char *ex){
		cout<<ex<<endl;
	}

    return 0;
}
