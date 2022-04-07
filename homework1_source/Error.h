//error header file
void commandError(){
	fprintf(stderr, "\nCommand not found\n");
	exit(1);
}

void mallocFailError(){
	fprintf(stderr, "\nMemory allocation failed\n");
	exit(1);
}

void fileOpenError(){
	fprintf(stderr, "\nFile open failed\n");
	exit(1);
}
