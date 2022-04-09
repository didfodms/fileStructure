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
	
	//�迭 ������ ���� �� �ʱ�ȭ
	if(strcmp(command, "-i") == 0) {
		//���� ����(file open) 
		if((in = fopen(argv[1], "w+")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//��ɾ� ���� ����  
		if(argc != 6) {
			fprintf(stderr, "\nta : Usage: ta path -i cellSize cellCount initialValue\n");
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
			fprintf(stderr, "\nUsage: ta path -w cellIndex cellValue\n");
			exit(1);
		} 
		
		//������ ����, ���� ��� �о����  
		long cellIndex = atol(argv[3]);
		long cellValue = atol(argv[4]);
		char cellSizeBuf[2];
		char cellCountBuf[6];
		fscanf(in, "%2s%6s", cellSizeBuf, cellCountBuf);
		
		//index �ʰ� ���� 
		if(atol(argv[3]) >= atol(cellCountBuf)){
			fprintf(stderr, "�ε����� ��ȿ ������ 0���� %ld�����Դϴ�.", atol(cellCountBuf)-1); 
			exit(1);
		}
		
		//���� ���� ����  
		if((writeCell(in, cellIndex, cellValue)) < 0){
			fprintf(stderr, "\nta : Error : file write failed.\n");
			exit(1);
		}
			
	}
	//�迭 ������ ������ ������ �� ���� ����� ���� 10������ ���
	else if(strcmp(command, "-r") == 0) {
		//���� ����(file open) 
		if((in = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//��ɾ� ���� ����  
		if(argc < 3) {
			fprintf(stderr, "\nUsage: ta path -r cellIndex...\n");
			exit(1);
		}
		
		//���� ��� �о����  
		char cellSizeBuf[2];
		char cellCountBuf[6];
		fscanf(in, "%2s%6s", cellSizeBuf, cellCountBuf);
		int cellSize = atoi(cellSizeBuf);
		long cellCount = atol(cellCountBuf); 
		
		//index �ʰ� ���� 
		for(long i=3; i<argc; i++){
			if(atol(argv[i]) >= cellCount){
				fprintf(stderr, "�ε����� ��ȿ ������ 0���� %ld�����Դϴ�.", atol(cellCountBuf)-1); 
				exit(1);
			}
		}
		
		//cellBuf ����  
		long *cellBuf = (long*)malloc(sizeof(long)*(argc-3));
		if(cellBuf == NULL){
			fprintf(stderr, "Malloc Error");
			exit(1);
		}
		
		//readCell�Լ��� cellBuf ä���  
		for(long i=0; i<argc-3; i++){
			long cellIndex = atol(argv[3+i]);
			
			if((readCell(in, cellIndex, cellBuf+i)) < 0){
				fprintf(stderr, "\nError : file write failed.\n");
				exit(1);
			}
		}
		
		//cellBuf ���  
		for(int i=0; i<argc-3; i++){
			fprintf(stdout, "%ld ", cellBuf[i]);
		}
		fprintf(stdout, "\n");

	}
	//�迭 ������ ������ ������ ���鿡 ����� ������ ���� ������� 10������ ���
	else if(strcmp(command, "-l") == 0){
		//���� ����(file open) 
		if((in = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "\nError : file open failed.\n");
			exit(1);
		}
		
		//��ɾ� ���� ����  
		if(argc != 5) {
			fprintf(stderr, "\nUsage: ta path -l startIndex endIndex\n");
			exit(1);
		}
		
		//���� ��� �о����  
		char cellSizeBuf[2];
		char cellCountBuf[6];
		fscanf(in, "%2s%6s", cellSizeBuf, cellCountBuf);
		int cellSize = atoi(cellSizeBuf);
		long cellCount = atol(cellCountBuf); 
		//
		if(atol(argv[3]) >= cellCount || atol(argv[4]) >= cellCount){
			fprintf(stderr, "�ε����� ��ȿ ������ 0���� %ld�����Դϴ�.", atol(cellCountBuf)-1); 
			exit(1);
		}
		
		//���� ����  
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
		//command not found ����  
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

//����� �ؽ�Ʈ ���� fp�� Ư�� ��(�ε����� cellIndex�� ��)�� �� cellValue�� ����
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ���� 
int writeCell(FILE *fp, long cellIndex, long cellValue){
	
	//���� ��� �о���� (cellSize, cellCount)
	char cellSizeBuf[2];
	char cellCountBuf[6];
	fscanf(fp, "%2s%6s", cellSizeBuf, cellCountBuf);
	int cellSize = atoi(cellSizeBuf);
	long cellCount = atol(cellCountBuf);

	//���� 
	fseek(fp, 0, SEEK_SET);
	char* file_read = (char*)malloc(8+cellCount*cellSize+1);
	if(file_read == NULL){
		return -1; 
	}
	if(fgets(file_read, _msize(file_read), fp) == NULL) {
		return -1;
	}
	
	//�б� -> ���� ���� ����  
	rewind(fp);
	
	//"%(cellSize)ld"�����  
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

//����� �ؽ�Ʈ ���� fp�� Ư�� ��(�ε����� cellIndex�� ��)�� ����Ǿ� �ִ� ���� �о� 
//�ּ� cellBuf�� ���� 
//�۾� �������� ������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ���� 
int readCell(FILE *fp, long cellIndex, long *cellBuf){
	//���� ��� �о���� (cellSize, cellCount)
	fseek(fp, 0, SEEK_SET);
	char cellSizeBuf[2];
	char cellCountBuf[6];
	fscanf(fp, "%2s%6s", cellSizeBuf, cellCountBuf);
	int cellSize = atoi(cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	//file_read�� �迭 ���� ���� ���� 
	fseek(fp, 0, SEEK_SET); 
	char* file_read = (char*)malloc(8+cellCount*cellSize+1);
	if(file_read == NULL){
		return -1; 
	}
	if(fgets(file_read, _msize(file_read), fp) == NULL) {
		return -1;
	}
	//cellIndex�� �ش��ϴ� �� �б�  
	char buffer[cellSize+1];
	for(int i=0; i<cellSize; i++){
		buffer[i] = file_read[8+cellIndex*cellSize+i];
	}
	//cellBuf�� ����  
	long longBuf = atol(buffer);
	*cellBuf = longBuf;

	return 0;
}

//����� �ؽ�Ʈ ���� fp�� ������ ����(�ε��� ciStart���� ciEnd������ �ش�Ǵ� ��� ����)�� 
//����Ǿ� �ִ� ������ �о� �ּ� cellBuf�������� ���۵Ǵ� �޸� ������ ������� ����
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ����
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf){
	//readCell�Լ� �̿�  
	for(long i=ciStart; i<=ciEnd; i++){
		if(readCell(fp, i, cellBuf+(i-ciStart)) < 0){
			return -1;
		}
	}

	return 0;
}

