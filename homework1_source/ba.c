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
		//���� ����(open) ����  
		if((in = fopen(argv[1], "wb")) == NULL){
			fprintf(stderr, "file open error");
			exit(1);
		}
		//��ɾ� �Է� ���� ����  
		if(argc != 5) {
			fprintf(stderr, "Usage : ba path -i cellCount initValue");
			exit(1);
		}
		//���� ���� 
		long cellCount = atol(argv[3]);
		long initValue = atol(argv[4]);
		//initFile() ȣ�� ����  
		if(initFile(in, cellCount, initValue) < 0){
			fprintf(stderr, "file init error");
			 exit(1);
		}
		
	}
	else if(strcmp(command, "-w") == 0){
		//���� ����(open) ����
		if((in = fopen(argv[1], "rb+")) == NULL) {
			fprintf(stderr, "file open error");
			exit(1);
		}
		//��ɾ� �Է� ���� ����
		if(argc != 5) {
			fprintf(stderr, "Usage : ba path -w cellIndex cellValue");
			exit(1);
		}
		//���� ����
		long cellIndex = atol(argv[3]);
		long cellValue = atol(argv[4]); 
		long cellCount;
		fread(&cellCount, sizeof(long), 1, in);
		fseek(in, 0, SEEK_SET);
		//cellIndex �ʰ� ���� 
		if(atol(argv[3]) >= cellCount){
			fprintf(stderr, "��ȿ�� �ε��� ������ 0���� %ld�����Դϴ�.", cellCount-1);
			exit(1);
		}
		//writeCell() ȣ�� ���� 
		if(writeCell(in, cellIndex, cellValue) < 0) {
			fprintf(stderr, "file write error");
			exit(1);
		}
	}
	else if(strcmp(command, "-r") == 0){
		//���� ����(open) ����
		if((in = fopen(argv[1], "rb")) == NULL) {
			fprintf(stderr, "file open error");
			exit(1);
		}
		//��ɾ� ���� �Է� ����  
		if(argc < 3) {
			fprintf(stderr, "Usage : ba path -r cellIndex...");
			exit(1);
		}
		//���� ����  
		long cellCount;
		fread(&cellCount, sizeof(long), 1, in);
		fseek(in, 0, SEEK_SET);
		//cellIndex �ʰ� ���� 
		for(long i=3; i<argc; i++){
			if(atol(argv[i]) >= cellCount){
				fprintf(stderr, "��ȿ�� �ε��� ������ 0���� %ld�����Դϴ�.", cellCount-1);
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
			//readCell() ȣ�� ���� ����
			if((readCell(in, cellIndex, cellBuf+i)) < 0){
				fprintf(stderr, "\nError : file read failed.\n");
				exit(1);
			}
		}
		//cellBuf ���
		for(long i=0; i<_msize(cellBuf)/sizeof(long); i++){
			fprintf(stdout, "%ld ", *(cellBuf+i));
		}
		fprintf(stdout, "\n");
	}
	else if(strcmp(command, "-l") == 0){
		//���� ����(open) ���� ����  
		if((in = fopen(argv[1], "rb")) == NULL){
			fprintf(stderr, "file open error");
			exit(1);
		}
		//��ɾ� �Է� ���� ����
		if(argc != 5) {
			fprintf(stderr, "Usage : ba path -l ciStart ciEnd");
			exit(1);
		}
		//���� ����
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
		//�ε��� �ʰ� ����  
		if(ciStart >= cellCount || ciEnd >= cellCount){
			fprintf(stderr, "��ȿ�� �ε��� ������ 0���� %ld�����Դϴ�.", cellCount-1);
			exit(1);
		}
		//readAdjacentCells() ȣ�� ���� 
		if(readAdjacentCells(in, ciStart, ciEnd, cellBuf) < 0){
			fprintf(stderr, "file read error");
			exit(1);
		}
		//cellBuf ���
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

//����� ���� ���� fp �ʱ�ȭ
//�� ���� : cellCount, �� �ʱ� �� : initValue 
int initFile(FILE *fp, long cellCount, long initValue) {

	fwrite(&cellCount, sizeof(long), 1, fp);
	for(long i=0; i<cellCount; i++){
		fwrite(&initValue, sizeof(long), 1, fp);
	}
	
	return 0;
}

//����� ���� ���� fp�� cellIndex ��ġ�� �ش��ϴ� ���� cellValue ����  
int writeCell(FILE *fp, long cellIndex, long cellValue) {
	//���� ��� �о����  
	long cellCount;
	if(fread(&cellCount, sizeof(long), 1, fp) < 0) {
		return -1;
	}
	//file_read malloc ����
	long* file_read = (long*)malloc(sizeof(long)*(cellCount));
	if(file_read == NULL){
		return -1;
	}
	//file_read�� ������ �б� (���� ��� ����) 
	for(long i=0; i<cellCount; i++){
		if(fread(&file_read[i], sizeof(long), 1, fp) < 0){
			return -1;
		}
	}
	//file_read ������ ���� 
	file_read[cellIndex] = cellValue; 
	//�б� ��� -> ���� ��� 
	rewind(fp); 
	//fp�� ����� ������ ����  
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

//����� ���� ���� fp�� cellIndex ��ġ�� �ش��ϴ� ���� ����Ǿ� �ִ� ��
//�� �о� cellBuf�� �޸𸮿� ����  
int readCell(FILE *fp, long cellIndex, long *cellBuf) {
	//���� ������ 0���� ����  
	fseek(fp, 0, SEEK_SET);
	long cellCount;
	fread(&cellCount, sizeof(long), 1, fp);
	/*���� ����  
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

//����� ���� ���� fp�� ciStart~ciEnd�� �ش�Ǵ� ���� ����Ǿ� �ִ� ������ 
//�о� �ּ� cellBuf�� �޸𸮿� ����  
int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf) {
	//readCell() ȣ�� ���� 
	for(long i=ciStart; i<=ciEnd; i++){
		if(readCell(fp, i, cellBuf+(i-ciStart)) < 0){
			return -1;
		}
	}
	return 0;
}


