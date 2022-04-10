#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initFile(FILE *fp, long cellCount, long initValue);
int writeCell(FILE *fp, long cellIndex, long cellValue);
int readCell(FILE *fp, long cellIndex, long *cellBuf);
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf);

int main(int argc, char** argv) {
	
	FILE *in;
	char* command = argv[2]; 
	
	if(strcmp(command, "-i") == 0){
		//파일 개방(open) 오류  
		if((in = fopen(argv[1], "wb")) == NULL){
			fprintf(stderr, "file open error");
			exit(1);
		}
		//명령어 입력 형식 오류  
		if(argc != 5) {
			fprintf(stderr, "Usage : ba path -i cellCount initValue");
			exit(1);
		}
		//변수 설정 
		long cellCount = atol(argv[3]);
		long initValue = atol(argv[4]);
		//initFile() 호출 오류  
		if(initFile(in, cellCount, initValue) < 0){
			fprintf(stderr, "file init error");
			 exit(1);
		}
		
	}
	else if(strcmp(command, "-w") == 0){
		//파일 개방(open) 오류
		if((in = fopen(argv[1], "rb+")) == NULL) {
			fprintf(stderr, "file open error");
			exit(1);
		}
		//명령어 입력 형식 오류
		if(argc != 5) {
			fprintf(stderr, "Usage : ba path -w cellIndex cellValue");
			exit(1);
		}
		//변수 설정
		long cellIndex = atol(argv[3]);
		long cellValue = atol(argv[4]); 
		long cellCount;
		fread(&cellCount, sizeof(long), 1, in);
		fseek(in, 0, SEEK_SET);
		//cellIndex 초과 오류 
		if(atol(argv[3]) >= cellCount){
			fprintf(stderr, "유효한 인덱스 범위는 0부터 %ld까지입니다.", cellCount-1);
			exit(1);
		}
		//writeCell() 호출 오류 
		if(writeCell(in, cellIndex, cellValue) < 0) {
			fprintf(stderr, "file write error");
			exit(1);
		}
	}
	else if(strcmp(command, "-r") == 0){
		//파일 개방(open) 오류
		if((in = fopen(argv[1], "rb")) == NULL) {
			fprintf(stderr, "file open error");
			exit(1);
		}
		//명령어 형식 입력 오류  
		if(argc < 3) {
			fprintf(stderr, "Usage : ba path -r cellIndex...");
			exit(1);
		}
		//변수 설정  
		long cellCount;
		fread(&cellCount, sizeof(long), 1, in);
		fseek(in, 0, SEEK_SET);
		//cellIndex 초과 오류 
		for(long i=3; i<argc; i++){
			if(atol(argv[i]) >= cellCount){
				fprintf(stderr, "유효한 인덱스 범위는 0부터 %ld까지입니다.", cellCount-1);
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
			//readCell() 호출 실패 오류
			if((readCell(in, cellIndex, cellBuf+i)) < 0){
				fprintf(stderr, "\nError : file read failed.\n");
				exit(1);
			}
		}
		//cellBuf 출력
		for(long i=0; i<_msize(cellBuf)/sizeof(long); i++){
			fprintf(stdout, "%ld ", *(cellBuf+i));
		}
		fprintf(stdout, "\n");
	}
	else if(strcmp(command, "-l") == 0){
		//파일 개방(open) 실패 오류  
		if((in = fopen(argv[1], "rb")) == NULL){
			fprintf(stderr, "file open error");
			exit(1);
		}
		//명령어 입력 형식 오류
		if(argc != 5) {
			fprintf(stderr, "Usage : ba path -l ciStart ciEnd");
			exit(1);
		}
		//변수 설정
		long ciStart = atol(argv[3]);
		long ciEnd = atol(argv[4]); 
		long cellBufLen = ciEnd-ciStart+1;
		long *cellBuf = (long*)malloc(sizeof(long)*(cellBufLen));
		if(cellBuf == NULL){
			fprintf(stderr, "malloc error");
			exit(1);
		}
		long cellCount;
		fread(&cellCount, sizeof(long), 1, in);
		fseek(in, 0, SEEK_SET);
		//인덱스 초과 오류  
		if(ciStart >= cellCount || ciEnd >= cellCount){
			fprintf(stderr, "유효한 인덱스 범위는 0부터 %ld까지입니다.", cellCount-1);
			exit(1);
		}
		//readAdjacentCells() 호출 오류 
		if(readAdjacentCells(in, ciStart, ciEnd, cellBuf) < 0){
			fprintf(stderr, "file read error");
			exit(1);
		}
		//cellBuf 출력
		for(long i=0; i<cellBufLen; i++){
			fprintf(stdout, "%ld ", cellBuf[i]);
		}
		fprintf(stdout, "\n");
		
	}
	else {
		fprintf(stderr, "command not found.");
		exit(1);
	}
	
	fclose(in);

}

//개방된 이진 파일 fp 초기화
//셀 개수 : cellCount, 셀 초기 값 : initValue 
int initFile(FILE *fp, long cellCount, long initValue) {

	fwrite(&cellCount, sizeof(long), 1, fp);
	for(long i=0; i<cellCount; i++){
		fwrite(&initValue, sizeof(long), 1, fp);
	}
	
	return 0;
}

//개방된 이진 파일 fp의 cellIndex 위치에 해당하는 셀에 cellValue 저장  
int writeCell(FILE *fp, long cellIndex, long cellValue) {
	//파일 헤더 읽어오기  
	long cellCount;
	if(fread(&cellCount, sizeof(long), 1, fp) < 0) {
		return -1;
	}
	//file_read malloc 오류
	long* file_read = (long*)malloc(sizeof(long)*(cellCount));
	if(file_read == NULL){
		return -1;
	}
	//file_read에 데이터 읽기 (파일 헤더 제외) 
	for(long i=0; i<cellCount; i++){
		if(fread(&file_read[i], sizeof(long), 1, fp) < 0){
			return -1;
		}
	}
	//file_read 데이터 변경 
	file_read[cellIndex] = cellValue; 
	//읽기 모드 -> 쓰기 모드 
	rewind(fp); 
	//fp에 변경된 데이터 쓰기  
	if(fwrite(&cellCount, sizeof(long), 1, fp) < 0){
		return -1;
	}
	for(long i=0; i<cellCount; i++){
		if(fwrite(&file_read[i], sizeof(long), 1, fp) < 0){
			return -1;
		}
	}
	
	return 0;
}

//개방된 이진 파일 fp의 cellIndex 위치에 해당하는 셀에 저장되어 있는 값
//을 읽어 cellBuf의 메모리에 저장  
int readCell(FILE *fp, long cellIndex, long *cellBuf) {
	//파일 오프셋 0으로 설정  
	fseek(fp, 0, SEEK_SET);
	long cellCount;
	fread(&cellCount, sizeof(long), 1, fp);
	/*순차 접근  
	long buffer;
	for(long i=0; i<cellCount; i++){
		fread(&buffer, sizeof(long), 1, fp);
		if(i==cellIndex) {
			break;
		}
	}
	*/
	long* file_read = (long*)malloc(sizeof(long)*cellCount);
	if(file_read == NULL){
		return -1;
	}
	for(long i=0; i<cellCount; i++) {
		if(fread(&file_read[i], sizeof(long), 1, fp) < 0){
			return -1;
		}
	}
	
	*cellBuf = file_read[cellIndex];
	
	return 0;
}

//개방된 이진 파일 fp의 ciStart~ciEnd에 해당되는 셀에 저장되어 있는 값들을 
//읽어 주소 cellBuf의 메모리에 저장  
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf) {
	//readCell() 호출 실패 
	for(long i=ciStart; i<=ciEnd; i++){
		if(readCell(fp, i, cellBuf+(i-ciStart)) < 0){
			return -1;
		}
	}
	return 0;
}


