#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char* cellSize;
	char* cellCount;
} fileHeader;

typedef struct {
	fileHeader* header;
	FILE* temp;
	
	char* fileName;
} fileStructure;

typedef fileStructure fileStruct;

int initFile(FILE *fp, int cellSize, long cellCount, long initValue);

main(int argc, char** argv){
	//Error : command not found
	if(argv[0] != "ta"){
		fprintf(stderr, "\nCommand '%s' not found\n", argv[0]);
		exit(1);
	}
	
	FILE *in, *out;
	
	//���� ����(file open) 
	if((in = fopen(argv[1], "w+")) == NULL){
		fprintf(stderr, "\nError : file open failed.\n");
		exit(1);
	}
	
	char* command = argv[2];
	if(command=="-i"){ 
		//�迭 ������ ���� �� �ʱ�ȭ
		//Command not found 
		if(argc != 6) {
			fprintf(stderr, "\nta : Usage: ta %s command size count initial-value\n", argv[1]);
			exit(1);
		}
			
		//file(header, temp) ����ü ���� �Ҵ�, cellSize cellCount �Ҵ� 
		fileStruct* file = (fileStruct*)malloc(sizeof(fileStruct));
		file->header->cellSize = (char*)malloc(sizeof(char)*2);
		file->header->cellCount = (char*)malloc(sizeof(char)*6);
		//temp1 �ݺ������� �� ���� ���� �Ҵ�  
		FILE* temp1 = (file*)malloc(sizeof(file));
		for(long i=0; i<cellCount; i++){
			*(temp1+(cellSize*i)) = (char*)malloc(sizeof(char)*atoi(cellSize));
			*(temp1+(cellSize*i)) = argv[5];
		}
		//file����ü�� temp�� temp1 �Ҵ� 
		//file(header, temp)������ ����  
		file->temp = temp1; 
			
		if((initFile(in, cellSize, cellCount, initValue)) < 0){
			fprintf(stderr, "\nError : file init failed.\n");
			exit(1);
		}
		
		break;
	}

}
