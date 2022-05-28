#include "file.h"

/*本文件主要包含三个函数OpenFile(),CloseFile(),FileSave()
  三个函数操作的文件的文件名均为NewInterface()中编辑的textbox中的namedefault字符数组（全局） 
1.OpenFile()
 无输入、返回值
 功能：将源文件拷贝到缓冲文件，结合Text将缓冲文件显示，实现将源文件在图形界面上显示的功能
2.CloseFile()
 无输入、返回值
 功能：将缓冲文件清空，结合Text将缓冲文件显示，实现将图形界面清空的功能
3.FileSave()
 无输入、返回值
 功能：将缓冲文件拷贝到源文件，即将图形界面的内容以文本的形式存储到特定文件名的文件中 
*/


//正式函数 
//将整数n转化为字符数组的前m位 
char* IntToArray(int m,int n,char* a){
	a[m]='\0';
	do{
		m--;
		a[m]=n%10+'0';
		n/=10;
	}while(n||m);
	return a;
}

//产生日期相关的默认文件名 
char* FileName(time_t timer,char* b){
/*	time_t timer;
    struct tm *tblock;
    timer = time(NULL);
    */
	struct tm *tblock; 
    tblock = localtime(&timer);
    IntToArray(4,tblock->tm_year+1900,b);
    IntToArray(2,tblock->tm_mon+1,b+4);
    IntToArray(2,tblock->tm_mday,b+6);
    strcat(b,".txt");
    return b;
}

void FileSave(){
	char c;
	char b[13];
	
//	if(!ifopen){
		//写以时间默认命名的源文件 
		sourceFile=fopen(FileName(time(NULL),b),"w");
	//}
	//else{
		//写正在编辑的源文件 
		//sourceFile=fopen(namedefault,"w"); 
	//}
	
	//读缓冲文件
	//buffFile=fopen("buffFile.txt","r");
	
	//缓冲文件拷贝到源文件 
	rewind(buffFile);
	while(!feof(buffFile)){
		c=fgetc(buffFile);
		fputc(c,sourceFile);
	}
	
	fclose(buffFile);
	fclose(sourceFile);
} 

void FileSaveAs(char* name){
	char c;
		
	//打开源文件 
	sourceFile = fopen(name,"w");
	//buffFile=fopen("buffFile.txt","w");
	
	//改变源文件 
	rewind(buffFile);
	while(!feof(buffFile)){
		c=fgetc(buffFile);
		fputc(c,sourceFile);
	}
	
	fclose(buffFile);
	fclose(sourceFile);
	
} 

void openFile(){
    char c;
    
	//打开对应的文件
	sourceFile=fopen(name,"r");
	buffFile=fopen("buffFile.txt","a+");
	rewind(sourceFile);
	
	//改变缓冲文件 
	while(!feof(sourceFile)){
		c=fgetc(sourceFile);
		fputc(c,buffFile);
	}
	
	fclose(sourceFile);
	//fclose(buffFile);
	
	//将打开的文件名存起来，用全局变量表示此时有文件被打开 	
	strcpy(namedefault,name);
	ifopen=1;
} 

void CloseFile(){
	//清空缓冲文件  
	//buffFile=fopen("buffFile.txt","w");
	fclose(buffFile);
	
	//表示文件被打开的全局变量赋为0 
	ifopen=0;
}

void newFile(){
	buffFile=fopen("buffFile.txt","a+");
}
 
