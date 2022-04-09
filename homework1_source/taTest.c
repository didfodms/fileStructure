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
	
	//배열 파일의 생성 및 초기화
	if(strcmp(command, "-i") == 0) {
		//파일 개방(file open) 
		if((in = fopen(argv[1], "w+")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//명령어 형식 에러  
		if(argc != 6) {
			fprintf(stderr, "\nta : Usage: ta path command cellSize cellCount initialValue\n");
			exit(1);
		}
		//변수명 설정  
		int cellSize = atoi(argv[3]);
		long cellCount = atol(argv[4]);
		long initValue = atol(argv[5]);
		//초기화 실패 에러  
		if((initFile(in, cellSize, cellCount, initValue)) < 0){
			fprintf(stderr, "\nError : file init failed.\n");
			exit(1);
		}
	}
	//배열 파일의 지정된 셀에 특정 값의 10진 표현을 저장
	else if(strcmp(command, "-w") == 0) {
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
		
		//변수명 설정  
		long cellIndex = atol(argv[3]);
		long cellValue = atol(argv[4]);
		//쓰기 실패 에러  
		if((writeCell(in, cellIndex, cellValue)) < 0){
			fprintf(stderr, "\nta : Error : file write failed.\n");
			exit(1);
		}
			
	}
	//배열 파일의 셀들을 지정해 각 셀에 저장된 값을 10진수로 출력
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
	//배열 파일의 지정된 범위의 셀들에 저장된 값들을 저장 순서대로 10진수로 출력
	else if(strcmp(command, "-l") == 0){

	}
	else {
		
		fprintf(stderr, "\nta : Command not found : you can use commands -i -w -r -l\n");
		exit(1);
	}
	
	
	fclose(in);
	fclose(out);
}

//개방된 텍스트 파일 fp를 초기화 
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴
//셀 크기 cellSize, 셀 개수 cellCount, 셀 초기 값 initValue
int initFile(FILE *fp, int cellSize, long cellCount, long initValue) {
	//공간 할당  
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

//개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 값 cellValue를 저장
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴 
int writeCell(FILE *fp, long cellIndex, long cellValue){
	//2byte (셀 크기) 읽어와 저장
	char* cellSizeBuf = (char*)malloc(2);
	if(cellSizeBuf == NULL){
		return -1;
	}  
	fscanf(fp, "%s", cellSizeBuf);  
	int cellSize = atoi(cellSizeBuf);
	//접근하려는 셀이 없을 경우  
	if(cellSize <= cellIndex){
		return -1;
	}
	
	//2~8byte (셀 개수) 읽어와 저장	
	char* cellCountBuf = (char*)malloc(6);
	if(cellCountBuf == NULL){
		return -1;
	}  
	fscanf(fp+2, "%s", cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	
	//버퍼에 저장할 값 저장  
	char* cellValueBuf = (char*)malloc(cellSize);
	if(cellValueBuf == NULL){
		return -1;
	}
	sprintf(cellValueBuf, "%s", cellValue);
	
	//특정 셀 위치 찾기  
	//if(fseek(fp, 8+cellSize*cellIndex, cellIndex < 0? SEEK_END : SEEK_SET) != 0){
	//	return -1;
	//}
	fprintf(fp, "%s", cellValueBuf);
	
	free(cellSizeBuf);	
	free(cellCountBuf);
	free(cellValueBuf);
	
	return 0;
}

//개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 저장되어 있는 값을 읽어 
//주소 cellBuf에 저장
//작업 과정에서 오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴 
int readCell(FILE *fp, long cellIndex, long *cellBuf){
	
}

//개방된 텍스트 파일 fp의 연이은 셀들(인덱스 ciStart부터 ciEnd까지에 해당되는 모든 셀들)에 
//저장되어 있는 값들을 읽어 주소 cellBuf에서부터 시작되는 메모리 영역에 순서대로 저장
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf){
	
}

