#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* size;
	char* count;
	FILE* temp1;
} fileStructure;

typedef fileStructure fileStruct;

int initFile(FILE *fp, int cellSize, long cellCount, long initValue);
int writeCell(FILE *fp, long cellIndex, long cellValue);
int readCell(FILE *fp, long cellIndex, long *cellBuf);
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf);

main(int argc, char** argv){
	//Error : command not found
	if(argv[0] != "ta"){
		fprintf(stderr, "\nCommand '%s' not found\n", argv[0]);
	}
	
	FILE *in, *out;
	int i;

	long *cellBuf;
	

	//파일 개방(file open) 
	if((fileStruct->temp1 = fopen(argv[1], "w+")) == NULL){
		fprintf(stderr, "Error : file open failed.\n");
		exit(1);
	}
	char* fileName = argv[1];
	
	switch(argv[2]) {
		//배열 파일의 생성 및 초기화
		"-i" :{
			//명령어 형식이 잘못 입력되었을 때  
			if(argc != 6) {
				fprintf(stderr, "ta : Usage: ta %s command size count initial-value\n", argv[0]);
				exit(1);
			}
			
			int cellSize = atoi(argv[3]);
			long cellCount = atol(argv[4]);
			long initValue = atol(argv[5]);
			in = fileStruct->temp1;
			fileStruct->size = (int*)malloc(2);
	
			if((initFile(in, cellSize, cellCount, initValue) < 0){
				fprintf(stderr, "Error : file init failed.\n");
				exit(1);
			}
			
			break;
		}
		//배열 파일의 지정된 셀에 특정 값의 10진 표현을 저장
		"-w" :{
			if(argc != 5) {
				fprintf(stderr, "ta : Usage: ta %s command size count initial-value\n", argv[0]);
				exit(1);
			}
			
			long cellIndex = argv[3];
			long cellValue = argv[4];
			
			if((writeCell(in, cellIndex, cellValue) < 0){
				fprintf(stderr, "ta : Error : file write failed.\n");
				exit(1);
			}
			
			break;
		}
		//배열 파일의 셀들을 지정해 각 셀에 저장된 값을 10진수로 출력
		"-r" :{
			long cellIndex = argv[3];
			long *cellBuf = 
			
			if((readCell(in, cellIndex, cellBuf)) < 0){
				fprintf(stderr, "ta : Error : file write failed.\n");
				exit(1);
			}
			
			break;
		}
		//배열 파일의 지정된 범위의 셀들에 저장된 값들을 저장 순서대로 10진수로 출력
		"-l" :{
			break;
		}
		default:{
			fprintf(stderr, "ta : Command not found : you can use commands -i -w -r -l\n");
			exit(1);
		}
	}
	
	fclose(in);
	fclose(out);
	
}

//개방된 텍스트 파일 fp를 초기화
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴
//셀 크기 cellSize, 셀 개수 cellCount, 셀 초기 값 initValue
int initFile(FILE *fp, int cellSize, long cellCount, long initValue) {
	fp = (FILE*)malloc(cellSize*cellCount)
	
	
}

//개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 값 cellValue를 저장
//오류가 발생할 경우 -1을, 그렇지 않을 경우 0을 리턴 
int writeCell(FILE *fp, long cellIndex, long cellValue){
	
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

