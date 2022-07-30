/*
*	FileIOクラス
*	作成者：崎山
*/

#pragma once

#include <vector>
#include <sys/stat.h>
#include <string>

using namespace std;

class FileIO{
	private:

	public:
	int8_t read(vector<char>& destination,char* file_path);
	
};