#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Error.h"

int initFile(FILE *fp, int cellSize, long cellCount, long initValue);
int writeCell(FILE *fp, long cellIndex, long cellValue);
int readCell(FILE *fp, long cellIndex, long *cellBuf);
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf);

int main(int argc, char** argv){
	
	FILE *in, *out;
	char* command = argv[2];
	
	//�迭 ������ ���� �� �ʱ�ȭ
	if(strcmp(command, "-i") == 0) {
		//���� ����(file open) 
		if((in = fopen(argv[1], "w+")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//��ɾ� ���� ����  
		if(argc != 6) {
			fprintf(stderr, "\nta : Usage: ta path command cellSize cellCount initialValue\n");
			exit(1);
		}
		//������ ����  
		int cellSize = atoi(argv[3]);
		long cellCount = atol(argv[4]);
		long initValue = atol(argv[5]);
		//�ʱ�ȭ ���� ����  
		if((initFile(in, cellSize, cellCount, initValue)) < 0){
			fprintf(stderr, "\nError : file init failed.\n");
			exit(1);
		}
	}
	//�迭 ������ ������ ���� Ư�� ���� 10�� ǥ���� ����
	else if(strcmp(command, "-w") == 0) {
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
		
		//������ ����  
		long cellIndex = atol(argv[3]);
		long cellValue = atol(argv[4]);
		//���� ���� ����  
		if((writeCell(in, cellIndex, cellValue)) < 0){
			fprintf(stderr, "\nta : Error : file write failed.\n");
			exit(1);
		}
			
	}
	//�迭 ������ ������ ������ �� ���� ����� ���� 10������ ���
	else if(strcmp(command, "-r") == 0) {
		
		//long cellIndex = argv[3];
		long *cellBuf;
		/*
		if((readCell(in, cellIndex, cellBuf)) < 0){
			fprintf(stderr, "\nta : Error : file write failed.\n");
			exit(1);
		}
		*/
		
	}
	//�迭 ������ ������ ������ ���鿡 ����� ������ ���� ������� 10������ ���
	else if(strcmp(command, "-l") == 0){

	}
	else {
		
		fprintf(stderr, "\nta : Command not found : you can use commands -i -w -r -l\n");
		exit(1);
	}
	
	
	fclose(in);
	fclose(out);
}

//����� �ؽ�Ʈ ���� fp�� �ʱ�ȭ 
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ����
//�� ũ�� cellSize, �� ���� cellCount, �� �ʱ� �� initValue
int initFile(FILE *fp, int cellSize, long cellCount, long initValue) {
	//���� �Ҵ�  
	char *text = (char*)malloc(2+6+cellSize*cellCount+1);
	if(text == NULL){
		return -1;
	}
	
	char input[100] = "%";
	char temp[100];
	sprintf(temp, "%d", cellSize);
	strcat(input, temp);
	strcat(input, "ld");
	
	sprintf(text, "%2d", cellSize);
	sprintf(text+2, "%6ld", cellCount);
	for(int i=0; i<cellSize; i++){
		sprintf(text+(i*cellCount), input, initValue);
	}
	
	fprintf(fp, "%s", text);
	
	return 0;
}

//����� �ؽ�Ʈ ���� fp�� Ư�� ��(�ε����� cellIndex�� ��)�� �� cellValue�� ����
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ���� 
int writeCell(FILE *fp, long cellIndex, long cellValue){
	//2byte (�� ũ��) �о�� ����
	char* cellSizeBuf = (char*)malloc(2);
	if(cellSizeBuf == NULL){
		return -1;
	}  
	fscanf(fp, "%s", cellSizeBuf);  
	int cellSize = atoi(cellSizeBuf);
	//�����Ϸ��� ���� ���� ���  
	if(cellSize <= cellIndex){
		return -1;
	}
	
	//2~8byte (�� ����) �о�� ����	
	char* cellCountBuf = (char*)malloc(6);
	if(cellCountBuf == NULL){
		return -1;
	}  
	fscanf(fp+2, "%s", cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	
	//���ۿ� ������ �� ����  
	char* cellValueBuf = (char*)malloc(cellSize);
	if(cellValueBuf == NULL){
		return -1;
	}
	sprintf(cellValueBuf, "%s", cellValue);
	
	//Ư�� �� ��ġ ã��  
	//if(fseek(fp, 8+cellSize*cellIndex, cellIndex < 0? SEEK_END : SEEK_SET) != 0){
	//	return -1;
	//}
	fprintf(fp, "%s", cellValueBuf);
	
	free(cellSizeBuf);	
	free(cellCountBuf);
	free(cellValueBuf);
	
	return 0;
}

//����� �ؽ�Ʈ ���� fp�� Ư�� ��(�ε����� cellIndex�� ��)�� ����Ǿ� �ִ� ���� �о� 
//�ּ� cellBuf�� ����
//�۾� �������� ������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ���� 
int readCell(FILE *fp, long cellIndex, long *cellBuf){
	
}

//����� �ؽ�Ʈ ���� fp�� ������ ����(�ε��� ciStart���� ciEnd������ �ش�Ǵ� ��� ����)�� 
//����Ǿ� �ִ� ������ �о� �ּ� cellBuf�������� ���۵Ǵ� �޸� ������ ������� ����
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ����
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf){
	
}

