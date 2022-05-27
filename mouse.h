#ifndef _MOUSE_H
#define _MOUSE_H

extern int mouse_down;
extern int cursorBegin;
extern int cursorTail;
extern double mouse_x;//鼠标位置的x轴位置
extern double mouse_y;
extern double height, width;
//GetFontHeight()的两倍 
extern double f;
extern double textwidth;//两个字之间的左右距离
extern double textheight;
extern int charCount[1000];

#endif
