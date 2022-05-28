#ifndef _FILE_H
#define _FILE_H

#include<stdio.h>
#include<time.h>

extern int ifopen;
//源文件指针 
extern FILE *sourceFile;
//缓冲文件指针 
extern FILE* buffFile;
extern char namedefault[101];

char* IntToArray(int m,int n,char* a);
char* FileName(time_t timer,char* b);
void FileSave();
void FileSaveAs(char* name);
void openFile();
void CloseFile();
void newFile();

#endif
