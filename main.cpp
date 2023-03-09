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
using std::string;


int main(int argc, char *argv[]){
	setlocale(LC_CTYPE, "spanish");
	string path = "";

	try{
		Program *program = new Program();

		cout<<argc<<endl;

		if( argc > 1 ){
			for( int i=1; i<argc; i++){
				path = argv[i];
				cout<<path<<endl;

				program->readFileLPerL(path);
			}
		}
		std::cin.ignore(1);

		program->principal();
	}
	catch(const char *ex){
		cout<<ex<<endl;
	}

    return 0;
}
