

#include "FileIO.hpp"


int main(){

	vector<char> buf;
	char* path= "./test.txt";
	FileIO fileIO;

	fileIO.read(buf,path);

	return 0;
}