#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct ioModule{

	ifstream inFile;

	int openFile(const string name);
	void readData(string* str, const char& delim);
	friend ostream& operator<< (ostream &wyjscie, ioModule &s);
	int getChar();
	int peekChar();
	bool getline(string& str);
	bool eof();
};