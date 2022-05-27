#include"display.h"
#include"file.h"
#include"file_operation.h" 
#include <windows.h>
#define ID_1  10

//缓冲文件指针 
FILE *buffFile;
//定义位置：   意义：剪切板文件的文件指针头
FILE *clipBoard;  //特别注意：需要自行打开关闭
//源文件指针 
FILE *sourceFile;

//窗口的高和宽 
extern double height, width;
//GetFontHeight()的两倍 
extern double f;
extern row;
extern double height, width;
extern int timer_interval;
extern char charCh;
extern double mouse_x;  //鼠标位置的x轴位置
extern double mouse_y;  //鼠标位置的y轴位置
extern int mouse_down;  //鼠标是否点击，1为点击状态，0为松开状态
extern void display();
extern void Delete();

void CharEventProcess( int ch )
{
    uiGetChar( ch ); /*获取字符*/
    charCh = ch;
    //printf("%c",charCh);
    if (charCh >= 32 && charCh < 127 || charCh < 0 ) {
		Write(charCh); 
	}
    
}

void KeyboardEventProcess( int key, int event )
{
   uiGetKeyboard( key,event ); /*获取键盘*/
   /*一次只能删除一个*/ 
   static int delete_allow = 1; 
   if ( event == KEY_DOWN )
	{
		switch (key)
		{
			case VK_BACK:
				if(delete_allow = 1){
					Delete();
					delete_allow = 0;
				}
				break;
			case VK_RETURN:
				fprintf(buffFile,"\n");
				break;
		}
	}
	else if(event == KEY_UP){
		delete_allow = 1;
	}
}

void MouseEventProcess( int x, int y, int button, int event )
{
    uiGetMouse(x,y,button,event);
	mouse_x = ScaleXInches(x);
	mouse_y = GetWindowHeight()- ScaleXInches(y) ;
	switch (event){
		case BUTTON_DOWN:
			mouse_down = 1;
			break;
		case BUTTON_UP:
			mouse_down = 0;
			break;
	}
}

// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{
	if( timerID==ID_1) 
	{
		display();	
	}	
}

void Main()
{
	SetWindowTitle( "文本编辑器" );
	InitGraphics();
	InitConsole();
	
	//buffFile = fopen("buffFile.txt","a+");
	
	DefineColor("Gainsboro", 0.863, 0.863, 0.863);
	DefineColor("Turquoise", 0.251, 0.878, 0.816);
	DefineColor("Sandy Brown", 0.957, 0.643, 0.376);
	DefineColor("Light Sky Blue", 0.529, 0.808, 1.000);
	DefineColor("Navy Blue", 0.000, 0.000, 0.502);
	DefineColor("Hot Pink", 1.000, 0.412, 0.706);
	DefineColor("Light Green", 0.564, 0.933, 0.565);
	DefineColor("Snow4", 0.545, 0.537, 0.537);
	DefineColor("Dark Cyan", 0.000, 0.545, 0.545);
	DefineColor("Lemon Chiffon", 1.000, 0.980, 0.804);
	DefineColor("Medium Purple", 0.576, 0.439, 0.859);
	DefineColor("Salmon1", 1.000, 0.549, 0.412);
	DefineColor("Dodger Blue", 0.000, 0.749, 1.000);
	SetPenColor("Black");
	
	height=GetWindowHeight();
	width=GetWindowWidth();
	
	registerCharEvent( CharEventProcess );
	registerKeyboardEvent( KeyboardEventProcess );
	registerMouseEvent( MouseEventProcess );
	registerTimerEvent(TimerEventProcess);      	
	
	// 开启定时器
	startTimer(ID_1, timer_interval);
	
}
