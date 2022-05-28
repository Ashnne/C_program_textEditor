#include"mouse.h"


/*
mouseEvent函数
{
1.输入变量，及其意义：
 2.无返回值 
 3.实现的功能，将鼠标选中的字符串在文本中的指针位置头尾赋值给全局变量cursorBegin,cursorTail 
 4.需要用到的头文件："imgui.h" "math.h"
   需要用到的全局变量： FILE *buffFile;int cursorBegin;int cursorTail;
   需要调用的函数： int mouseEventCursor(double mouseX,double mouseY, double X, double Y, double width, double height);
   需要用到的全局变量 ：double textwidth;//两个字之间的左右距离
                     double textheight;//两个字之间的上下
                     double width;
                     double height;
   				 	 int cursorBegin;
   				 	 int cursorTail;
                     int rawMax;
                     static UIState gs_UIState;//鼠标、键盘等一系列状态
typedef struct {
	double mousex;
	double mousey;
	int    mousedown;
	int    clickedItem;// item that was clicked
	int    actingMenu; // acting menu list 
	int    kbdItem;    // item that takes keyboard
	int    lastItem;   // item that had focus just before
	int    keyPress;   // input key
	int    charInput;  // input char
	int    keyModifiers;  //  key modifier (shift, ctrl)
} UIState;
                     
 5.待优化的功能 
 
  汉字兼容（暂时的思路无法区分汉字和英文字母）
 
 6.测试函数 
 
 //待写
}
*/
void mouseEvent(){
    static int judgeUp = 0;
	if(mouse_down == 0 && judgeUp == 0)	return; 
    //这里读取鼠标的坐标和状态并赋值
    double mouseX = mouse_x;
    double mouseY = mouse_y;
    //这里赋值一下坐标原点
    double X_zero = width / 10;
    double Y_zero =  height - f * 2 ;
    //从鼠标开始点击时开始工作,同时留个记号judgeUp，第一次松开鼠标的时候再次记录坐标

    if( mouse_down == 1 && judgeUp == 0){
        //这里需要确定鼠标所在位置的光标,借用辅助函数mouseEventCursor
        cursorBegin = mouseEventCursor( mouseX, mouseY, X_zero, Y_zero, textwidth, textheight);
        //这里重置一下光标结束位置
        cursorTail = cursorBegin;
        judgeUp = 1;
    }
    //这里判断一下，鼠标按键松开了，而且是第一次
    if( mouse_down == 0 && judgeUp == 1 ){
        //先把判断改一下，已经松开了
        judgeUp = 0;
        //这里同样需要确定鼠标所在位置的光标，借助辅助函数
        cursorTail = mouseEventCursor( mouseX, mouseY, X_zero, Y_zero, textwidth, textheight);
        //这里再进行一个调试，确保cursorTail小于cursorBegin
        if(cursorTail < cursorBegin){
            int temp;
            temp = cursorTail;
            cursorTail = cursorBegin;
            cursorBegin = temp;
        }
    }
}




/*
mouseEventCursor函数(辅助函数)
{
1.输入变量，及其意义：
	double mouseX;//鼠标所在位置的X坐标
    double mouseY;//鼠标所在位置的Y坐标
    double X;     //坐标原点的X坐标
    double Y;     //坐标原点的Y坐标
    double width; //单个字符的宽度
    double height;//单个字符的高度
 2.返回值：类型：int 意义：鼠标点击位置在文本中的光标位置
 3.实现的功能，将鼠标当前点击的位置转化为文本中光标位置并返回 
 4.需要用到的全局变量： int charCount[1000];
 5.待优化的功能 
 
  汉字兼容（暂时的思路无法区分汉字和英文字母）
 
 6.测试函数 
 
 //待写
}
*/



int mouseEventCursor(double mouseX,double mouseY, double X, double Y, double width, double height){
    //计算一个相对位置（坐标变换），原点为（X，Y），在最左上方，正方向为向下，向右
    mouseX = mouseX - X;
    mouseY = Y - mouseY;
    //定义计算出鼠标点击的区域为第charY行，第charX个
    int charX;
    int charY;
    //确定在一行中的第几个，即光标移动到该行最前面时，需要往后移动几个位置
    charX = (int )((mouseX+textwidth/2)/textwidth);
    //确定在第几行，即光标在第几行中出现
    charY = (int )(mouseY/textheight + 1);
    //下面要开始计算所在的光标位置了,location为光标所在位置
    int location = 0;
    //首先防止y溢出，即选中位置行无内容的话默认为到最后有内容的一行,最多到第一行
    while( !charCount[charY] && charY!=1 )   charY--;
    //把前面所有的光标加起来，加到location中，此时location已经移动到第charY行第0个位置上了
    //此处注意，i是从1开始计数
    int i;
    for( i = 1;i < charY;i++){
        location+=charCount[i] + 1;
    }
    //再对location进行charY行内的调整
    location += charX;
    
    printf("location is %d\ncharX is %d\ncharY is %d\n",location,charX,charY);
    
    
    //此时从文件头开始向后移动location个光标即为鼠标点击的光标
    return location;
}
