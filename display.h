#ifndef _DISPLAY_H
#define _DISPLAY_H

#include<stdio.h>
#include<stdlib.h>
#include"extgraph.h"
#include"graphics.h"
#include"imgui.h"

//����λ�ã�   ���壺�����ļ����ļ�ָ��ͷ
extern FILE *buffFile;
extern char namedefault[101];
//������ɫ����ţ������ı�����ɫ 
extern int k;
//������ɫָ������ ��ɫ����ɫ������̡���ɫ����ɫ����ɫ����ɫ 
extern char* color[];
extern double height,width;
//GetFontHeight()������ 
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
extern char content[100];
extern int size;
extern int offput;

extern void Copy();
extern void Delete();
extern void Write(char inputChar);
extern void Cut();
extern void Paste();
extern void Search(char *temp);
extern void Change(char *temp);

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
void display();

#endif
