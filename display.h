#ifndef _DISPLAY_H
#define _DISPLAY_H

#include<stdio.h>
#include<stdlib.h>
#include"extgraph.h"
#include"graphics.h"
#include"imgui.h"

//定义位置：   意义：缓冲文件的文件指针头
extern FILE *buffFile;
extern char namedefault[101];
//背景颜色的序号，用来改背景颜色 
extern int k;
//定义颜色指针数组 白色、粉色、翡翠绿、黄色、紫色、蓝色、橙色 
extern char* color[];
extern double height,width;
//GetFontHeight()的两倍 
extern double f;
extern int newAllow;
extern int searchallow;
extern int helpallow;
extern int changeallow;
extern int openallow;
extern int rawMax;
extern int charCount[1000];
extern double textwidth;
extern double textheight;
extern int cursorBegin;
extern int cursorTail;
extern int fontSize;
extern int offput;
extern int fontSize_allow;
extern int textheight_allow;
extern int textwidth_allow;

extern void Copy();
extern void Delete();
extern void Write(char inputChar);
extern void Cut();
extern void Paste();
extern void Search(char *temp);
extern void Change(char *temp,char* replaceContain);

void DrawMenu();
void DrawButton();
void BackgroundColor();
void Text();
void drawLighting();
void drawCursor();
void NewInterface(); 
void searchFace();
void helpFace();
void changeFace();
int Count();
void format();
int charToNumber( char *temp );
void display();

#endif
