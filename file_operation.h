#ifndef _FILE_OPERATION_H
#define _FILE_OPERATION_H

#include<stdio.h>
#include<stdlib.h>
#include"graphics.h" 

extern FILE *buffFile;
extern int charCount[];
extern FILE *clipBoard;
extern int cursorBegin;
extern int cursorTail;


void Copy();
void Delete();
void Write(char inputChar);
void Cut();
void Paste();
void Search(char *temp);
void Change(char *temp);

#endif
