#include"display.h"

//������������������menu 
void DrawMenu()
{
	//SetPointSize(10);
	//menu�ַ�ָ������ �����ڻ�menu 
	setMenuColors("Dark Grey","Black","Dark Grey","Red",1);
	char* menuListFile[6]={ "�ļ�", "�� | Ctrl-O", "���� | Ctrl-S", "���Ϊ | Ctrl-N", "�ر� | Ctrl-E" };//���Ϊ�Ŀ�ݼ����� 
	char* menuListEdit[4]={ "�༭", "���� | Ctrl-C", "���� | Ctrl-X", "ճ�� | Ctrl-V" };
	char* menuListSearch[3]={ "����", "���� | Ctrl-F", "�滻 | Ctrl-R" };
	char* menuListSize[4]={ "��С", "10", "20", "30" };
	char* menuListFont[4]={ "����", "Times", "Courier", "Default" };
	char* menuListColor[9]={ "������ɫ", "��ɫ", "��ɫ", 
	"�����", "��ɫ", "��ɫ", "��ɫ", "��ɫ" };
	// int�ͱ�����ŷ���ֵ 
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


//������ť"����"
void DrawButton()
{
	setButtonColors("Dark Grey","Black","Dark Grey","Red",1);
	if(button(GenUIID(0),width/5,f,width/5,f,"����"))
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
	
    //X������ԭ��
	double X_zero = width / 10;
    //Y������ԭ��
    double Y_zero =  height - f * 2;
    
    /*MovePen(X_zero,Y_zero);
    SetPenColor("Red");
    DrawLine(1,0);*/	
    
    //����λ�ã�����ʵ�ֹ��
    int count = 0;
    //�жϣ������ѡ�е��ַ����Ļ�������Ӹ�����
    int judgeChosen = 0;
    //��ʱ�ַ���ת
    int tempChar[2] = {'a','\0'};
    
    int i;
    for( i = 1;i <= rawMax; i++){
    	int j;
    	//printf("%s","Now is fine");
        for( j = 0; j <= charCount[i] ;j++){
            //���ݹ�����ı��е�λ�ã��ѱʷŵ���ͬ��λ����
            MovePen( X_zero + j * textwidth, Y_zero - i * textheight);
            //�ѱ���ƺã������࣬count�ڲ��ڹ����
            if( count >= cursorBegin && count <= cursorTail - 1 )   judgeChosen = 1;
            else    judgeChosen = 0;
            
            //��һ���ļ�����ַ�
            fseek(buffFile,count,0); 
            tempChar[0] = fgetc(buffFile);
            //���Ǹ����������Ϊ�ҷ�����dev�Ļ��������������ַ� 
            if(tempChar[0] == '\n')	count++;

            //�����ѡ�еģ����ں��滭�����ӣ�ͻ����
            if( judgeChosen)	drawLighting();
            
            //�ȷ��Űɣ�д���֣�д��,��ʱ����DrawTextString�ѣ����뻻�ɸ��򵥵ġ�������
            //����͸�������ˣ��������,\nҲ�򣬵���ûɶ�� 
            //��ɫ�Ļ���
            SetPenColor(color[k-1]);
            DrawTextString( tempChar);   
	    	//�����
            if( count == cursorTail - 1)    drawCursor();
            //������һ��
            count ++;
        } 
    }
}


void drawLighting(){
    //ѡ�ñ���ɫ
    SetPenColor("Yellow");
    //�����
    StartFilledRegion(1);
    //���
    DrawLine(textwidth,0);
    DrawLine(0,textheight);
    DrawLine(-textwidth,0);
    DrawLine(0,-textheight);
    //�����ģʽ�ر�
    EndFilledRegion();
    return;
}

void drawCursor(){
    //ѡ�ñ���ɫ
    SetPenColor("Black");
    //�����
    StartFilledRegion(1);
    //���
    DrawLine(0.04,0);
    DrawLine(0,textheight);
    DrawLine(-0.04,0);
    DrawLine(0,-textheight);
    //�����ģʽ�ر�
    EndFilledRegion();
    return;
}

/*NewInterface()����
	1.���ܣ�����һ����ʾ���textbox(),�û����Ա༭��Ҫ��/������ļ�������
	2.���������������ֵ
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
	if(button(GenUIID(0),width/10*4+2.5,height-f*2.8,width/10,f,"ȷ��")){
		FileSaveAs(namedefault); 
	}
}

void searchFace(){
	if(searchallow == 1){
		setTextBoxColors("Dark Grey","Black","Dark Grey","Black",1);
		textbox(GenUIID(1),width/10*3.5,height-f*4,width/10*3,f,content,100); 
		if(button(GenUIID(0),width/10*2,height-f*4,width/10,f,"����")){
			Search(content);
		}
	}
	else return;
}

void changeFace(){
	if(changeallow == 1){
		setTextBoxColors("Dark Grey","Black","Dark Grey","Black",1);
		textbox(GenUIID(1),width/10*3.5,height-f*4,width/10*3,f,content,100); 
		if(button(GenUIID(0),width/10*2,height-f*4,width/10,f,"�滻")){
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
	if(button(GenUIID(0),width/10*4+2.5,height-f*2.8,width/10,f,"��")){
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
    //�����ÿһ�еļ�������
    int i = 0;
    //�����������
    int j = 1;
    //��ʼ��
    fseek(buffFile,0,0);
    //�����ַ�
    char ch = 1;
    while(!feof(buffFile)){
        ch = fgetc(buffFile);
        //����ַ�ΪEOF����˵��������
        if( ch == EOF){
            charCount[j] = i;
            return j;
        }
        //����ַ�Ϊ\n��˵������ת��һ����
        else if( ch == '\n'){
            //��ֵ
            charCount[j] = i;
            //��������
            i = 0;
            //������ת��һ��
            j++;
        }
        //�����������+1
        else    i++;
    }
    //�����Ϊ��ȡ���ļ�ĩβ�ˣ�Ҳ˵��������
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
