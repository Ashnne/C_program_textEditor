#include "file_operation.h"
/*
    Count函数
    
    1.无输入变量
    2.返回值：
    类型为int   意义：文件中内容的最大行数
    3.实现的功能，将文件buffFile中内容导入到全局变量charCount[]中，方便光标移动
    4.需要用到的全局变量： 
        FILE *buffFile;
        int charCount[];
    5.待优化的功能 
    
    6.测试函数 
    #include<stdio.h>
    #include<stdlib.h>
    FILE *buffFile;
    int charCount[1000];
    int Count();
    int main(){
        buffFile = fopen("buffFile.txt","a+");
        int count;
        count = Count();
        for(int i=1;i<=count;i++){
            printf("%d\n",charCount[i]);
    }
    return 0;
}
    
    */ 


/*
 Copy函数
 
 1.无输入变量
 2.无返回值
 3.实现的功能，将指针标出的字符复制到clipBoard文件中
 4.需要用到的全局变量： 
    FILE *buffFile;
    FILE *clipBoard;
    int cursorBegin;
    int cursorTail;
 5.待优化的功能 
 
 6.测试函数 
#include<stdio.h>
#include<stdlib.h>
FILE *buffFile;
FILE *clipBoard;
int cursorBegin;
int cursorTail;
void Copy();
int main(){
    buffFile = fopen("buffFile.txt","a+");
    cursorBegin = 1;
    cursorTail = 10;
    //cursorTail = 1;
    Copy();
    return 0;
}

}
 
*/ 

void Copy() 
{
	printf("Copy run!");
    //打开剪切板（因为定义为随用随开，保证关闭）
	clipBoard = fopen( "clipBoard.txt", "w");
    //先找到想开始复制的开头
    fseek(buffFile,cursorBegin,0);
    //这是调试出的问题（我真傻，连个fseek都不会用。。。。
    //fseek( buffFile, 0, cursorBegin);
    //找出需要复制的文本长度
    int length = cursorTail - cursorBegin;
    //这里加个判断吧，如果头尾一致的话，就当你没按
    if(length == 0)	return;
    //定义一个过渡字符
    char temp;
    //将需要的字符串读入clipBoard
    while( length){
        temp = fgetc( buffFile);
		fputc( temp, clipBoard);
        length--;
    }
    //大功告成
    return;
}

/*
Write函数
 
 1.输入变量，及其意义：
 	char inputChar;//输入的字符（一般放在键盘相应事件中，作为输入） 
 2.无返回值 
 3.实现的功能，将光标选中的内容在buffFile中删除，并将输入的字符添加到光标所在位置。
 4.需要用到的函数：void Delete();
   需要用到的全局变量： FILE *buffFile;
   						int cursorBegin;
   						int cursorTail;
 5.待优化的功能 
 

 6.测试函数 
#include<stdio.h>
#include<stdlib.h>
FILE *buffFile;
int cursorBegin;
int cursorTail;
void Write(char inputChar);
void Delete();
int main(){
    buffFile = fopen("buffFile.txt","a+");
    cursorBegin = 2;
    cursorTail = 4;
    //cursorTail = 1;
    char ch;
    ch = '?';
    Write(ch);
}
*/
void Delete() 
{
	//一个过渡缓冲文件 
	FILE *tempFile = fopen("tempFile.txt","w");
	
	printf("tempFile open successfully!\n");
	
	//如果光标在文件头，直接返回 
	if(cursorTail == 0)	return;
	//如果光标未选中，将光标头前移一个，默认删除前一个 
	if(cursorBegin == cursorTail)	cursorBegin--;
	char ch = 1;//缓冲字符 
	int i = 0;//计数光标位置 
	
	printf("loop will begin\n");
	
	while( 1){
		//如果碰到选中区域，直接跳过 
		if( i == cursorBegin ){
			i = cursorTail;
			continue;
		}
		//每一次都刷新一下文件光标，确保要读取的是需要的字符 
		fseek(buffFile,i,0);
		//读取buff File中的字符 
		ch = fgetc(buffFile);
		//判断一下，如果是EOF说明读完了
		if(ch == EOF)	break; 
		//输出给temp 
		fputc(ch,tempFile);
		//手动将光标后移 
		i++;	
		printf("loop have continued for %d times\n",i);
	}
	//将buffFile刷新一遍，将temp的内容读进去 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w");
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","a+");
	tempFile = fopen("tempFile.txt","r");
	
	printf("begin to write!\n");
	
	while(!feof(tempFile)){
		//从tempFile中开始读取 
		ch = getc(tempFile);
		//如果是EOF说明读完了 
		if(ch == EOF)	break;
		//赋给buffFile
		putc(ch,buffFile); 
	}
	
	printf("all down!\n");
	
	//用完文件就关好习惯
	fclose(tempFile); 
	//将光标末尾和光标头统一（因为中间的已经删除）
	cursorTail = cursorBegin;	
}
 
void Write(char inputChar) 
{
	//如果有选中的内容，就直接删除先
	if(cursorBegin<cursorTail)	Delete();
	
	//下面开始通过缓冲文件将该字符加入 
	//一个过渡缓冲文件 
	FILE *tempFile = fopen("tempFile.txt","w");
	char ch = 1;//缓冲字符
	int i=0;//计数光标位置 
	while( 1){
		//如果碰到选中区域，就将字符加进去 
		if( i == cursorBegin )	fputc(inputChar,tempFile);
		//每一次都刷新一下文件光标，确保要读取的是需要的字符 
		fseek(buffFile,i,0);
		//读取buff File中的字符 
		ch = fgetc(buffFile);
		//判断一下，如果是EOF说明读完了
		if(ch == EOF)	break; 
		//输出给temp 
		fputc(ch,tempFile);
		//手动将光标后移 
		i++;
	}
	//将buffFile刷新一遍，将tempFile的内容读进去 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//从tempFile中开始读取 
		ch = getc(tempFile);
		//如果是EOF说明读完了 
		if(ch == EOF)	break;
		//赋给buffFile
		putc(ch,buffFile); 
	}
	//用完文件就关好习惯
	fclose(tempFile); 
	//由于加入了一个字符，光标应该要往后一个
	cursorBegin++;
	cursorTail++; 
}

/*
5.Cut函数

Cut函数
 
1.输入变量，及其意义：
 	//可能要用到键盘输入，暂缓 
 2.无返回值 
 3.实现的功能，将选中的内容在buffFile中删除 
 4.需要用到的头文件："graphics.h" 
   需要用到的全局变量： FILE *buffFile;
   						FILE *clipBoard;
   						int cursorBegin;
   						int cursorTail;
 5.待优化的功能 
 

 6.测试函数 
#include<stdio.h>
#include<stdlib.h>
FILE *buffFile;
FILE *clipBoard;
int cursorBegin;
int cursorTail;
void Delete();
void Cut();
void Copy();
int main(){
    buffFile = fopen("buffFile.txt","a+");
	clipBoard = fopen("clipBoard.txt","w");
    cursorBegin = 2;
    cursorTail = 4;
    //cursorTail = 1;
    Cut();
}

void Delete() 
{
	//一个过渡缓冲文件 
	FILE *tempFile = fopen("tempFile.txt","w");
	//如果光标在文件头，直接返回 
	if(cursorTail == 0)	return;
	//如果光标未选中，将光标头前移一个，默认删除前一个 
	if(cursorBegin == cursorTail)	cursorBegin--;
	char ch = 1;//缓冲字符 
	int i = 0;//计数光标位置 
	while( !feof(buffFile)){
		//如果碰到选中区域，直接跳过 
		if( i == cursorBegin ){
			i = cursorTail;
			continue;
		}
		//每一次都刷新一下文件光标，确保要读取的是需要的字符 
		fseek(buffFile,i,0);
		//读取buff File中的字符 
		ch = fgetc(buffFile);
		//判断一下，如果是EOF说明读完了
		if(ch == EOF)	break; 
		//输出给temp 
		fputc(ch,tempFile);
		//手动将光标后移 
		i++;
	}
	//将buffFile刷新一遍，将temp的内容读进去 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//从tempFile中开始读取 
		ch = getc(tempFile);
		//如果是EOF说明读完了 
		if(ch == EOF)	break;
		//赋给buffFile
		putc(ch,buffFile); 
	}
	//用完文件就关好习惯
	fclose(tempFile); 
	//将光标末尾和光标头统一（因为中间的已经删除）
	cursorTail = cursorBegin;	
}*/

 
void Cut() 
{
	//如果未选中字符串，则直接返回 
	if(cursorBegin == cursorTail)	return;
	//先将相关字符串复制，再删除字符串 
	Copy();
	Delete();
}

/*
6.Paste函数

Paste函数
 
 1.无需要输入的变量：
 2.无返回值 
 3.实现的功能，将选中的内容在buffFile中删除，将clipBoard里的内容在光标处加入到buffFile中
 4.需要用到的函数：void Write(char);
                void Delete();
   需要用到的全局变量：FILE *buffFile;
   					FILE *clipBoard;
   					int cursorBegin;
   					int cursorTail;
 5.待优化的功能 
 

 6.测试函数 
#include<stdio.h>
#include<stdlib.h>
FILE *buffFile;
FILE *clipBoard;
int cursorBegin;
int cursorTail;
void Write(char);
void Paste();
void Delete();

int main(){
    buffFile = fopen("buffFile.txt","a+");
	clipBoard = fopen("clipBoard.txt","r");
    cursorBegin = 1;
    //cursorTail = 4;
    cursorTail = 1;
    Paste();
}

void Write(char inputChar) 
{
	//如果有选中的内容，就直接删除先
	if(cursorBegin<cursorTail)	Delete();
	
	//下面开始通过缓冲文件将该字符加入 
	//一个过渡缓冲文件 
	FILE *tempFile = fopen("tempFile.txt","w");
	char ch = 1;//缓冲字符
	int i=0;//计数光标位置 
	while( !feof(buffFile)){
		//如果碰到选中区域，就将字符加进去 
		if( i == cursorBegin )	fputc(inputChar,tempFile);
		//每一次都刷新一下文件光标，确保要读取的是需要的字符 
		fseek(buffFile,i,0);
		//读取buff File中的字符 
		ch = fgetc(buffFile);
		//判断一下，如果是EOF说明读完了
		if(ch == EOF)	break; 
		//输出给temp 
		fputc(ch,tempFile);
		//手动将光标后移 
		i++;
	}
	//将buffFile刷新一遍，将tempFile的内容读进去 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//从tempFile中开始读取 
		ch = getc(tempFile);
		//如果是EOF说明读完了 
		if(ch == EOF)	break;
		//赋给buffFile
		putc(ch,buffFile); 
	}
	//用完文件就关好习惯
	fclose(tempFile); 
	//由于加入了一个字符，光标应该要往后一个
	cursorBegin++;
	cursorTail++; 
}

void Delete() 
{
	//一个过渡缓冲文件 
	FILE *tempFile = fopen("tempFile.txt","w");
	//如果光标在文件头，直接返回 
	if(cursorTail == 0)	return;
	//如果光标未选中，将光标头前移一个，默认删除前一个 
	if(cursorBegin == cursorTail)	cursorBegin--;
	char ch = 1;//缓冲字符 
	int i = 0;//计数光标位置 
	while( !feof(buffFile)){
		//如果碰到选中区域，直接跳过 
		if( i == cursorBegin ){
			i = cursorTail;
			continue;
		}
		//每一次都刷新一下文件光标，确保要读取的是需要的字符 
		fseek(buffFile,i,0);
		//读取buff File中的字符 
		ch = fgetc(buffFile);
		//判断一下，如果是EOF说明读完了
		if(ch == EOF)	break; 
		//输出给temp 
		fputc(ch,tempFile);
		//手动将光标后移 
		i++;
	}
	//将buffFile刷新一遍，将temp的内容读进去 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//从tempFile中开始读取 
		ch = getc(tempFile);
		//如果是EOF说明读完了 
		if(ch == EOF)	break;
		//赋给buffFile
		putc(ch,buffFile); 
	}
	//用完文件就关好习惯
	fclose(tempFile); 
	//将光标末尾和光标头统一（因为中间的已经删除）
	cursorTail = cursorBegin;	
}
}
 
*/ 
void Paste() 
{
	printf("Paste run!");
	
	if(cursorBegin < cursorTail)	Delete();
	//打开剪切板文件
	clipBoard = fopen("clipBoard.txt","r");
	//把剪切板里的文件加入到buffFile中去
	char ch;//过渡字符 
	while( 1){
		ch = fgetc(clipBoard);
		if(ch == EOF)	break;//EOF说明读完了 
		//把这个字符给buffFile读进去 
		Write( ch); 
	}
	//文件用完就关好习惯
	fclose(clipBoard); 
}

/*
 Search函数
 
 1.输入变量及意义：
 	char *temp 需要搜索的字符串 
 2.无返回值
 3.实现的功能：得到搜索字符串头尾指针的位置 
 4.需要用到的全局变量： 
    FILE *buffFile;
    int cursorBegin;
    int cursorTail;
 5.待优化的功能 
 
 6.测试函数 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cursorBegin,cursorTail;
FILE* buffFile;
void Search(char *temp);
int main(){
    buffFile = fopen("buffFile.txt","a+");
    char* p = "abc";
    Search(p);
    printf("%d %d",cursorBegin,cursorTail);
    return 0;
}
 
*/ 

void Search(char *temp){
	//找到第几个指针位置了
	int i=0;
    int tempLength = strlen(temp);
    char buff[100];
	while(!feof(buffFile)){
        //过渡字符
        fseek(buffFile,i,0);
        char ch = fgetc(buffFile);
        //如果读到的EOF，说明到末尾了，别读了,没找到
        if(ch == EOF){
        	break;
		}
		//如果第一个字符都没对上，直接continue
		if(ch != temp[0]){
			i++;
			continue;	
		}
        //重制光标
        fseek(buffFile,i,0);
        //读取长度的数组,并判断是否读取成功，没成功就别读了，到末尾了
        while(fgets(buff,tempLength+1,buffFile)){
        	//读取成功了，对比一下，如果是，就把他选中，结束函数
        	if(!(strcmp(temp,buff))){
            	cursorBegin = i;
            	cursorTail = i + tempLength;
            	return;
        	}
        	else{
        		i++;
        		fseek(buffFile,i,0);
			}
		}
        //如果没成功，继续循环（缺省就行）        
	}
	cursorBegin = cursorTail = 0;
	
    return;
} 

void Change(char* temp)
{
	
}
