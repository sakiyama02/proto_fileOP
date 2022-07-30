/*
*	FileIOクラス
*	作成者：崎山
*/

#include "../../include/FileOp/FileIO.hpp"

/*
*	ファイル読み込み
*	destinationにファイルデータを格納する
*/
int8_t FileIO::read(vector<char>& destination,char* file_path){
	
	FILE *fp;
	struct stat st;
	int fsize = 0;

	if ( stat( file_path , &st) != 0 ){
		return -1;
	}

	fsize = st.st_size;
	destination.resize(fsize);
	
	if (( fp = fopen ( file_path,"rb" )) == NULL ){
		printf("file open err\n");
		return -1;
	}

	if ( fread( &destination[0],destination.size(),sizeof(destination[0]),fp ) == 0 ){
		printf("file read err\n");
		return -1;
	}

	
	fclose(fp);

	return 0;
}