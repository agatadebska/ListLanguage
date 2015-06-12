// ListLanguage.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "ioModule/ioModule.h"
#include "parser/scanner/scanner.h"
#include "parser/parser.h"

int main(int argc, char* argv[])
{
	std::cout << "Podaj sciezke do pliku z programem w jezyku Listowym" << std::endl;
	std::string fileName = "";
	getline(std::cin, fileName);

	ioModule ioMod;
	if(	ioMod.openFile(fileName) == 1)
		return 1;

	std::cout << ioMod << endl;

/*	std::string line = "";
	while (ioMod.getline(line)){
		std::cout << "x: " << line << endl;
		line = "";
	}
 */
	parser parser1;
	parser1.parse(fileName);

/*	line = "";
	ioMod.readData(&line, ';');
	std::cout << line;

	line = "";
	ioMod.readData(&line, ';');
	std::cout << line;
*/
	std::cout << "press any key to exit" << std::endl;
	std::string s;
	getline(std::cin, s);
	return 0;
}

