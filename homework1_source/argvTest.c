#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	FILE *in;
	//파일 개방(file open) 
	if((in = fopen(argv[1], "r+")) == NULL){
		fprintf(stderr, "\nError : file open failed.\n");
		exit(1);
	}
	//명령어 형식 에러  
	if(argc != 5) {
		fprintf(stderr, "\nUsage: ta path command cellIndex cellValue\n");
		exit(1);
	}
	
	char buffer[2];
	fscanf(in, "%s", buffer);
	long cellSize = atol(buffer);
	fprintf(stdout, "%s\n%d\n", buffer, cellSize);
	/*
	//변수명 설정  
	long cellIndex = atol(argv[3]);
	long cellValue = atol(argv[4]);
	
	//2byte (셀 크기) 읽어와 저장
	char* cellSizeBuf = (char*)malloc(2);
	if(cellSizeBuf == NULL){
		return -1;
	}  
	fscanf(in, "%s", cellSizeBuf);  
	int cellSize = atoi(cellSizeBuf);
	printf("%s\n%d\n%d", &cellSizeBuf, cellSize, _msize(cellSizeBuf));
	
	//2~8byte (셀 개수) 읽어와 저장	
	char* cellCountBuf = (char*)malloc(6);
	if(cellCountBuf == NULL){
		return -1;
	}  
	fscanf(in+2, "%s", cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	
	//버퍼에 저장할 값 저장  
	char* cellValueBuf = (char*)malloc(cellSize);
	if(cellValueBuf == NULL){
		return -1;
	}
	sprintf(cellValueBuf, "%s", cellValue);
	
	//특정 셀 위치 찾기  
	fseek(in, 8+cellSize*cellIndex, SEEK_SET);
	fprintf(in, "%s", cellValueBuf);
	
	fprintf(stdout, "%d\n", 8+cellSize*cellIndex);
	
	free(cellSizeBuf);	
	free(cellCountBuf);
	free(cellValueBuf);
	*/
	fclose(in);
	return 0;
}
