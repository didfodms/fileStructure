#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
			fprintf(stderr, "\nta : Usage: ta path -i cellSize cellCount initialValue\n");
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
			fprintf(stderr, "\nUsage: ta path -w cellIndex cellValue\n");
			exit(1);
		} 
		
		//변수명 설정, 파일 헤더 읽어오기  
		long cellIndex = atol(argv[3]);
		long cellValue = atol(argv[4]);
		char cellSizeBuf[2];
		char cellCountBuf[6];
		fscanf(in, "%2s%6s", cellSizeBuf, cellCountBuf);
		
		//index 초과 에러 
		if(atol(argv[3]) >= atol(cellCountBuf)){
			fprintf(stderr, "인덱스의 유효 범위는 0부터 %ld까지입니다.", atol(cellCountBuf)-1); 
			exit(1);
		}
		
		//쓰기 실패 에러  
		if((writeCell(in, cellIndex, cellValue)) < 0){
			fprintf(stderr, "\nta : Error : file write failed.\n");
			exit(1);
		}
			
	}
	//배열 파일의 셀들을 지정해 각 셀에 저장된 값을 10진수로 출력
	else if(strcmp(command, "-r") == 0) {
		//파일 개방(file open) 
		if((in = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//명령어 형식 에러  
		if(argc < 3) {
			fprintf(stderr, "\nUsage: ta path -r cellIndex...\n");
			exit(1);
		}
		
		//파일 헤더 읽어오기  
		char cellSizeBuf[2];
		char cellCountBuf[6];
		fscanf(in, "%2s%6s", cellSizeBuf, cellCountBuf);
		int cellSize = atoi(cellSizeBuf);
		long cellCount = atol(cellCountBuf); 
		
		//index 초과 에러 
		for(long i=3; i<argc; i++){
			if(atol(argv[i]) >= cellCount){
				fprintf(stderr, "인덱스의 유효 범위는 0부터 %ld까지입니다.", atol(cellCountBuf)-1); 
				exit(1);
			}
		}
		
		//cellBuf 생성  
		long *cellBuf = (long*)malloc(sizeof(long)*(argc-3));
		if(cellBuf == NULL){
			fprintf(stderr, "Malloc Error");
			exit(1);
		}
		
		//readCell함수로 cellBuf 채우기  
		for(long i=0; i<argc-3; i++){
			long cellIndex = atol(argv[3+i]);
			
			if((readCell(in, cellIndex, cellBuf+i)) < 0){
				fprintf(stderr, "\nError : file write failed.\n");
				exit(1);
			}
		}
		
		//cellBuf 출력  
		for(int i=0; i<argc-3; i++){
			fprintf(stdout, "%ld ", cellBuf[i]);
		}
		fprintf(stdout, "\n");

	}
	//배열 파일의 지정된 범위의 셀들에 저장된 값들을 저장 순서대로 10진수로 출력
	else if(strcmp(command, "-l") == 0){
		//파일 개방(file open) 
		if((in = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//명령어 형식 에러  
		if(argc != 5) {
			fprintf(stderr, "\nUsage: ta path -l startIndex endIndex\n");
			exit(1);
		}
		
		//파일 헤더 읽어오기  
		char cellSizeBuf[2];
		char cellCountBuf[6];
		fscanf(in, "%2s%6s", cellSizeBuf, cellCountBuf);
		int cellSize = atoi(cellSizeBuf);
		long cellCount = atol(cellCountBuf); 
		//
		if(atol(argv[3]) >= cellCount || atol(argv[4]) >= cellCount){
			fprintf(stderr, "인덱스의 유효 범위는 0부터 %ld까지입니다.", atol(cellCountBuf)-1); 
			exit(1);
		}
		
		//변수 설정  
		long ciStart = atol(argv[3]);
		long ciEnd = atol(argv[4]);
		int cellBufLen = (int)(ciEnd-ciStart)+1;
		long *cellBuf = (long*)malloc(sizeof(long)*cellBufLen);
		if(cellBuf == NULL){
			fprintf(stderr, "Malloc Error");
			exit(1);
		}	
		
		if((readAdjacentCells(in, ciStart, ciEnd, cellBuf)) < 0){
			fprintf(stderr, "\nError : file write failed.\n");
			exit(1);
		}
		
		for(int i=0; i<cellBufLen; i++){
			fprintf(stdout, "%ld ", cellBuf[i]);
		}
		fprintf(stdout, "\n");
	}
	else {
		//command not found 에러  
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
	
	char input[100] = "%";
	char temp[100];
	sprintf(temp, "%d", cellSize);
	strcat(input, temp);
	strcat(input, "ld");
	
	fprintf(fp, "%2d", cellSize);
	fprintf(fp, "%6ld", cellCount);
	for(long i=0; i<cellCount; i++) {
		fprintf(fp, input, initValue);
	}
	
	return 0;
}

//개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 값 cellValue를 저장
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴 
int writeCell(FILE *fp, long cellIndex, long cellValue){
	
	//파일 헤더 읽어오기 (cellSize, cellCount)
	char cellSizeBuf[2];
	char cellCountBuf[6];
	fscanf(fp, "%2s%6s", cellSizeBuf, cellCountBuf);
	int cellSize = atoi(cellSizeBuf);
	long cellCount = atol(cellCountBuf);

	//수정 
	fseek(fp, 0, SEEK_SET);
	char* file_read = (char*)malloc(8+cellCount*cellSize+1);
	if(file_read == NULL){
		return -1; 
	}
	if(fgets(file_read, _msize(file_read), fp) == NULL) {
		return -1;
	}
	
	//읽기 -> 쓰기 모드로 변경  
	rewind(fp);
	
	//"%(cellSize)ld"만들기  
	char* buffer = (char*)malloc(cellSize);
	char input[100] = "%";
	char temp[2];
	sprintf(temp, "%ld", cellSize);
	strcat(input, temp);
	strcat(input, "ld");
	sprintf(buffer, input, cellValue);

	for(long i=0; i<_msize(file_read); i++){
		if(i==8+cellIndex*cellSize){
			for(long j=0; j<cellSize; j++){
				fputc(buffer[j], fp);
			}
			i += cellSize-1;
			continue;
		}
		fputc(file_read[i], fp);
	}
	
	return 0;
	 
}

//개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 저장되어 있는 값을 읽어 
//주소 cellBuf에 저장 
//작업 과정에서 오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴 
int readCell(FILE *fp, long cellIndex, long *cellBuf){
	//파일 헤더 읽어오기 (cellSize, cellCount)
	fseek(fp, 0, SEEK_SET);
	char cellSizeBuf[2];
	char cellCountBuf[6];
	fscanf(fp, "%2s%6s", cellSizeBuf, cellCountBuf);
	int cellSize = atoi(cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	//file_read에 배열 파일 내용 저장 
	fseek(fp, 0, SEEK_SET); 
	char* file_read = (char*)malloc(8+cellCount*cellSize+1);
	if(file_read == NULL){
		return -1; 
	}
	if(fgets(file_read, _msize(file_read), fp) == NULL) {
		return -1;
	}
	//cellIndex에 해당하는 값 읽기  
	char buffer[cellSize+1];
	for(int i=0; i<cellSize; i++){
		buffer[i] = file_read[8+cellIndex*cellSize+i];
	}
	//cellBuf에 저장  
	long longBuf = atol(buffer);
	*cellBuf = longBuf;

	return 0;
}

//개방된 텍스트 파일 fp의 연이은 셀들(인덱스 ciStart부터 ciEnd까지에 해당되는 모든 셀들)에 
//저장되어 있는 값들을 읽어 주소 cellBuf에서부터 시작되는 메모리 영역에 순서대로 저장
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf){
	//readCell함수 이용  
	for(long i=ciStart; i<=ciEnd; i++){
		if(readCell(fp, i, cellBuf+(i-ciStart)) < 0){
			return -1;
		}
	}

	return 0;
}

