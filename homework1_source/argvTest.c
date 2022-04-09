#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	FILE *in;
	//���� ����(file open) 
	if((in = fopen(argv[1], "r+")) == NULL){
		fprintf(stderr, "\nError : file open failed.\n");
		exit(1);
	}
	//��ɾ� ���� ����  
	if(argc != 5) {
		fprintf(stderr, "\nUsage: ta path command cellIndex cellValue\n");
		exit(1);
	}
	
	char buffer[2];
	fscanf(in, "%s", buffer);
	long cellSize = atol(buffer);
	fprintf(stdout, "%s\n%d\n", buffer, cellSize);
	/*
	//������ ����  
	long cellIndex = atol(argv[3]);
	long cellValue = atol(argv[4]);
	
	//2byte (�� ũ��) �о�� ����
	char* cellSizeBuf = (char*)malloc(2);
	if(cellSizeBuf == NULL){
		return -1;
	}  
	fscanf(in, "%s", cellSizeBuf);  
	int cellSize = atoi(cellSizeBuf);
	printf("%s\n%d\n%d", &cellSizeBuf, cellSize, _msize(cellSizeBuf));
	
	//2~8byte (�� ����) �о�� ����	
	char* cellCountBuf = (char*)malloc(6);
	if(cellCountBuf == NULL){
		return -1;
	}  
	fscanf(in+2, "%s", cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	
	//���ۿ� ������ �� ����  
	char* cellValueBuf = (char*)malloc(cellSize);
	if(cellValueBuf == NULL){
		return -1;
	}
	sprintf(cellValueBuf, "%s", cellValue);
	
	//Ư�� �� ��ġ ã��  
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
