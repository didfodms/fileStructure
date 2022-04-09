#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	
	FILE *in, *out;
	
	in = fopen(argv[1], "r+");
	if(in == NULL){
		fprintf(stderr, "file open error");
		exit(1);
	}
	
	char cellSizeBuf[2];
	char cellCountBuf[6];
	fscanf(in, "%2s", cellSizeBuf);
	fscanf(in, "%6s", cellCountBuf);
	int cellSize = atoi(cellSizeBuf);
	long cellCount = atol(cellCountBuf);
	long cellIndex = atol(argv[3]);
	long cellValue = atol(argv[4]);
	long copyLen = 8+cellSize*cellCount+1;
	
	char* copy = (char*)malloc(sizeof(char)*copyLen);
	sprintf(copy, "%2d", cellSize);
	sprintf(copy+2, "%6d", cellCount);

	char inputD[100] = "%";
	char inputS[100] = "%";
	char temp[2];
	sprintf(temp, "%ld", cellSize);
	strcat(inputD, temp);	strcat(inputS, temp);
	strcat(inputD, "ld");	strcat(inputS, "s");

	char buffer[cellSize];
	for(long i=0; i<cellCount; i++){
		fscanf(in, inputS, buffer);
		
		if(i == cellIndex){
			sprintf(copy+8+(i*cellSize), inputD, cellValue);
		}
		else {
			sprintf(copy+8+(i*cellSize), inputD, atol(buffer));
		}
	}

	fprintf(stdout, "%s", copy);
	fclose(in);
	
	out = fopen(argv[1], "w");
	fprintf(out, "%s", copy);
	fclose(out);


	return 0;

}
