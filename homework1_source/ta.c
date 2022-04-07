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
	

	//���� ����(file open) 
	if((fileStruct->temp1 = fopen(argv[1], "w+")) == NULL){
		fprintf(stderr, "Error : file open failed.\n");
		exit(1);
	}
	char* fileName = argv[1];
	
	switch(argv[2]) {
		//�迭 ������ ���� �� �ʱ�ȭ
		"-i" :{
			//��ɾ� ������ �߸� �ԷµǾ��� ��  
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
		//�迭 ������ ������ ���� Ư�� ���� 10�� ǥ���� ����
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
		//�迭 ������ ������ ������ �� ���� ����� ���� 10������ ���
		"-r" :{
			long cellIndex = argv[3];
			long *cellBuf = 
			
			if((readCell(in, cellIndex, cellBuf)) < 0){
				fprintf(stderr, "ta : Error : file write failed.\n");
				exit(1);
			}
			
			break;
		}
		//�迭 ������ ������ ������ ���鿡 ����� ������ ���� ������� 10������ ���
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

//����� �ؽ�Ʈ ���� fp�� �ʱ�ȭ
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ����
//�� ũ�� cellSize, �� ���� cellCount, �� �ʱ� �� initValue
int initFile(FILE *fp, int cellSize, long cellCount, long initValue) {
	fp = (FILE*)malloc(cellSize*cellCount)
	
	
}

//����� �ؽ�Ʈ ���� fp�� Ư�� ��(�ε����� cellIndex�� ��)�� �� cellValue�� ����
//������ �߻��� ��� -1��, �׷��� ���� ��� 0�� ���� 
int writeCell(FILE *fp, long cellIndex, long cellValue){
	
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

