/**
	@Autor: Hector Geovanny Rodriguez Martinez.
	@Tiempo 00:54:30
*/


#include <iostream>
#include <clocale>
#include "program.h"


using std::cout;
using std::endl;
using std::string;


int main(int argc, char *argv[]){
	setlocale(LC_CTYPE, "spanish");
	string path = "";

	try{
		Program *program = new Program();

		if( argc > 1 ){
			for( int i=1; i<argc; i++){
				path = argv[i];

				program->methodToReadFile(path);
			}
		}

		program->principal();
	}
	catch(const char *ex){
		cout<<ex<<endl;
	}

    return 0;
}
