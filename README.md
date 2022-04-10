# 파일처리론 과제 1
---

## 텍스트 파일 입출력 구현 ta.c
---
+ int initFile(FILE *fp, int cellSize, long cellCount, long initValue);
개방된 텍스트 파일 fp를 초기화(셀 크기 cellSize, 셀 개수 cellCount, 셀 초기 값 initValue)시켜 준다. 초기화 작업 중 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 
+ int writeCell(FILE *fp, long cellIndex, long cellValue);
개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 값 cellValue를 저장해 준다. 작업 과정에서 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 
+ int readCell(FILE *fp, long cellIndex, long *cellBuf);
개방된 텍스트 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 저장되어 있는 값을 읽어 주소 cellBuf에 저장해 준다. 작업 과정에서 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 
+ int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf);
개방된 텍스트 파일 fp의 연이은 셀들(인덱스 ciStart부터 ciEnd까지에 해당되는 모든 셀들)에 저장되어 있는 값들을 읽어 주소 cellBuf에서부터 시작되는 메모리 영역에 순서대로 저장해 준다. 작업 과정에서 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 

## 이진 파일 입출력 구현 ba.c
---
+ int initFile(FILE *fp, long cellCount, long initValue);
개방된 이진 파일 fp를 초기화(셀 개수 cellCount, 셀 초기 값 initValue)시켜 준다. 초기화 작업 중 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 
+ int writeCell(FILE *fp, long cellIndex, long cellValue);
개방된 이진 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 값 cellValue를 저장해 준다. 작업 과정에서 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 
+ int readCell(FILE *fp, long cellIndex, long *cellBuf);
개방된 이진 파일 fp의 특정 셀(인덱스가 cellIndex인 셀)에 저장되어 있는 값을 읽어 주소 cellBuf의 메모리에 저장해 준다. 작업 과정에서 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다. 
+ int readAdjacentCells(FILE *fp, long ciStart, long ciEnd, long *cellBuf);
개방된 이진 파일 fp의 연이은 셀들(인덱스 ciStart부터 ciEnd까지에 해당되는 모든 셀들)에 저장되어 있는 값들을 읽어 주소 cellBuf에서부터 시작되는 메모리 영역에 순서대로 저장해 준다. 작업 과정에서 오류가 발생할 경우 –1을, 그렇지 않을 경우 0을 리턴한다.