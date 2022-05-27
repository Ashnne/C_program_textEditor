#include"display.h"

//无输入输出，画出五个menu 
void DrawMenu()
{
	//SetPointSize(10);
	//menu字符指针数组 ，用于画menu 
	setMenuColors("Dark Grey","Black","Dark Grey","Red",1);
	char* menuListFile[6]={ "文件", "打开 | Ctrl-O", "保存 | Ctrl-S", "另存为 | Ctrl-N", "关闭 | Ctrl-E" };//另存为的快捷键待定 
	char* menuListEdit[4]={ "编辑", "复制 | Ctrl-C", "剪切 | Ctrl-X", "粘贴 | Ctrl-V" };
	char* menuListSearch[3]={ "搜索", "查找 | Ctrl-F", "替换 | Ctrl-R" };
	char* menuListSize[4]={ "大小", "10", "20", "30" };
	char* menuListFont[4]={ "字体", "Times", "Courier", "Default" };
	char* menuListColor[9]={ "背景颜色", "白色", "粉色", 
	"翡翠绿", "黄色", "紫色", "蓝色", "橙色" };
	// int型变量存放返回值 
	int selection_1,selection_2,selection_3,selection_4,selection_5,selection_6;
	selection_1=menuList( GenUIID(0), 0, height-f, width/6, width/6, f, menuListFile, 5 );
	selection_2=menuList( GenUIID(0), width/6, height-f, width/6, width/6, f, menuListEdit, 4 );
	selection_3=menuList( GenUIID(0), width/6*2, height-f, width/6, width/6, f, menuListSearch, 3 );
	selection_4=menuList( GenUIID(0), width/6*3, height-f, width/6, width/6, f, menuListSize, 4 );
	selection_5=menuList( GenUIID(0), width/6*4, height-f, width/6, width/6, f, menuListFont, 4 );
	selection_6=menuList( GenUIID(0), width/6*5, height-f, width/6, width/6, f, menuListColor, 8 );
	switch ( selection_1 )
	{
		case 1:openFile();break;//openallow *= -1;
		case 2:FileSave();break;
		case 3:newAllow *= -1;offput *= -1;break;
		case 4:CloseFile();break;
	}
	switch ( selection_2 )
	{
		case 1:Copy();break;
		case 2:Cut();break;
		case 3:Paste();break;		
	}
	switch ( selection_3 )
	{
		case 1:searchallow*=-1;break;
		case 2:changeallow*=-1;break;		
	}
	switch ( selection_4 )
	{
		case 1: size = 10;textheight=0.14;break;
		case 2:	size = 20;textheight=0.22;break;	
		case 3: size = 30;textheight=0.38;break;	
	}
	switch ( selection_5 )
	{
		case 1:SetFont("Times" );break;
		case 2:SetFont("Courier" );break;
		case 3:SetFont("Default");break;
	}
    if(selection_6){
        k=selection_6;
    }
}


//画出按钮"帮助"
void DrawButton()
{
	setButtonColors("Dark Grey","Black","Dark Grey","Red",1);
	if(button(GenUIID(0),width/5,f,width/5,f,"帮助"))
	{
		helpallow *= -1;
	}
}

void BackgroundColor(){
	SetPenColor(color[k]);
	drawRectangle(0,0,width,height,1);
}

void Text(){
	if(buffFile == NULL) return;
	
	SetPointSize(size);
	
    //X的坐标原点
	double X_zero = width / 10;
    //Y的坐标原点
    double Y_zero =  height - f * 2;
    
    /*MovePen(X_zero,Y_zero);
    SetPenColor("Red");
    DrawLine(1,0);*/	
    
    //光标的位置，便于实现光标
    int count = 0;
    //判断，如果是选中的字符串的话，后面加个背景
    int judgeChosen = 0;
    //临时字符中转
    int tempChar[2] = {'a','\0'};
    
    int i;
    for( i = 1;i <= rawMax; i++){
    	int j;
    	//printf("%s","Now is fine");
        for( j = 0; j <= charCount[i] ;j++){
            //根据光标在文本中的位置，把笔放到不同的位置上
            MovePen( X_zero + j * textwidth, Y_zero - i * textheight);
            //把笔设计好，分两类，count在不在光标内
            if( count >= cursorBegin && count <= cursorTail - 1 )   judgeChosen = 1;
            else    judgeChosen = 0;
            
            //读一下文件里的字符
            fseek(buffFile,count,0); 
            tempChar[0] = fgetc(buffFile);
            //这是个填补条件，因为我发现用dev的话，换行算两个字符 
            if(tempChar[0] == '\n')	count++;

            //如果是选中的，就在后面画个格子，突出嘛
            if( judgeChosen)	drawLighting();
            
            //先放着吧，写个字（写字,暂时就用DrawTextString把，我想换成更简单的。。。。
            //看不透，不换了，就这个吧,\n也打，但是没啥用 
            //颜色改回来
            SetPenColor(color[k-1]);
            DrawTextString( tempChar);   
	    	//画光标
            if( count == cursorTail - 1)    drawCursor();
            //数数加一个
            count ++;
        } 
    }
}


void drawLighting(){
    //选好背景色
    SetPenColor("Yellow");
    //打开填充
    StartFilledRegion(1);
    //填充
    DrawLine(textwidth,0);
    DrawLine(0,textheight);
    DrawLine(-textwidth,0);
    DrawLine(0,-textheight);
    //把填充模式关闭
    EndFilledRegion();
    return;
}

void drawCursor(){
    //选好背景色
    SetPenColor("Black");
    //打开填充
    StartFilledRegion(1);
    //填充
    DrawLine(0.04,0);
    DrawLine(0,textheight);
    DrawLine(-0.04,0);
    DrawLine(0,-textheight);
    //把填充模式关闭
    EndFilledRegion();
    return;
}

/*NewInterface()函数
	1.功能：画出一行提示语和textbox(),用户可以编辑需要打开/保存的文件的名称
	2.无输入变量、返回值
*/
void NewInterface(){
//	newAllow*=-1;
	if(newAllow == -1)	return;
	SetPenColor("Dark Grey");
	drawRectangle(width/10-0.06,height-f*2.8,width/10*6,f,1);
	MovePen(width/10,height-f*2.5);
	SetPenColor("Black");
	DrawTextString("File name (open/save):");
	setTextBoxColors("Dark Grey","Black","Dark Grey","Black",1);
	textbox(GenUIID(0),width/10*4+0.2,height-f*2.8,width/10*5,f,namedefault,100);
	if(button(GenUIID(0),width/10*4+2.5,height-f*2.8,width/10,f,"确定")){
		FileSaveAs(namedefault); 
	}
}

void searchFace(){
	if(searchallow == 1){
		setTextBoxColors("Dark Grey","Black","Dark Grey","Black",1);
		textbox(GenUIID(1),width/10*3.5,height-f*4,width/10*3,f,content,100); 
		if(button(GenUIID(0),width/10*2,height-f*4,width/10,f,"搜索")){
			Search(content);
		}
	}
	else return;
}

void changeFace(){
	if(changeallow == 1){
		setTextBoxColors("Dark Grey","Black","Dark Grey","Black",1);
		textbox(GenUIID(1),width/10*3.5,height-f*4,width/10*3,f,content,100); 
		if(button(GenUIID(0),width/10*2,height-f*4,width/10,f,"替换")){
			Change(content);
		}
	}
	else return;
}

/*void openFace(){
	if(openallow == -1)	return;
	SetPenColor("Dark Grey");
	drawRectangle(width/10-0.06,height-f*2.8,width/10*6,f,1);
	MovePen(width/10,height-f*2.5);
	SetPenColor("Black");
	DrawTextString("File name:");
	setTextBoxColors("Dark Grey","Black","Dark Grey","Black",1);
	textbox(GenUIID(0),width/10*4+0.2,height-f*2.8,width/10*5,f,content,100);
	if(button(GenUIID(0),width/10*4+2.5,height-f*2.8,width/10,f,"打开")){
		openallow *= -1;
		OpenFile(content); 
	}
}*/

void helpFace(){
	if(helpallow == 1){
		SetPenColor("Dark Grey");
		drawRectangle(width/10,1,width/10*8,height-f*4.6,1);
	}
	else return;
}

int Count() 
{
    //这个是每一行的计数个数
    int i = 0;
    //这个是在数行
    int j = 1;
    //开始数
    fseek(buffFile,0,0);
    //过度字符
    char ch = 1;
    while(!feof(buffFile)){
        ch = fgetc(buffFile);
        //如果字符为EOF，就说明结束了
        if( ch == EOF){
            charCount[j] = i;
            return j;
        }
        //如果字符为\n，说明该跳转下一行了
        else if( ch == '\n'){
            //赋值
            charCount[j] = i;
            //计数清零
            i = 0;
            //行数跳转下一个
            j++;
        }
        //其他情况计数+1
        else    i++;
    }
    //如果因为读取到文件末尾了，也说明结束了
    charCount[j] = i;
    return j;
}

void display()
{
	DefineColor( "Dark Grey", 0.60, 0.60, 0.60 );
	DisplayClear();
	BackgroundColor();
	f=GetFontHeight()*2;
    
	DrawMenu();
	DrawButton();
	rawMax = Count();
	Text();
	NewInterface();
	searchFace();
	helpFace();
	changeFace();
	//openFace();
	
	mouseEvent();
	
}
