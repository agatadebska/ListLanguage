#include "ioModule.h"

int ioModule::openFile(const std::string name){
	inFile.open(name.c_str(), std::ios::in);
	if (inFile.good())
		return 0;
	std::cerr << "Blad owarcia pliku" << endl;
	return 1;
}
void ioModule::readData(string* str, const char& delim){
//	(*this).inFile.get((*str).c_str(), delim);
//	(*this).inFile.get(*str, delim);
}

bool ioModule::getline(string& str){
	if ((*this).inFile.eof())
		return false;
	std::getline((*this).inFile, str);
	return true;
}

bool ioModule::eof(){
	return inFile.eof();
}

int ioModule::getChar() {
	return inFile.get();
}

int ioModule::peekChar(){
	return inFile.peek();
}

ostream& operator<< (ostream &wyjscie, ioModule &io){
	string ss;
	while (!io.inFile.eof()){
		ss = "";
		getline(io.inFile, ss);
		wyjscie << ss << endl;
	}
	io.inFile.seekg(0);
	return wyjscie;
}