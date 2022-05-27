#include "file_operation.h"
/*
    Count����
    
    1.���������
    2.����ֵ��
    ����Ϊint   ���壺�ļ������ݵ��������
    3.ʵ�ֵĹ��ܣ����ļ�buffFile�����ݵ��뵽ȫ�ֱ���charCount[]�У��������ƶ�
    4.��Ҫ�õ���ȫ�ֱ����� 
        FILE *buffFile;
        int charCount[];
    5.���Ż��Ĺ��� 
    
    6.���Ժ��� 
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
 Copy����
 
 1.���������
 2.�޷���ֵ
 3.ʵ�ֵĹ��ܣ���ָ�������ַ����Ƶ�clipBoard�ļ���
 4.��Ҫ�õ���ȫ�ֱ����� 
    FILE *buffFile;
    FILE *clipBoard;
    int cursorBegin;
    int cursorTail;
 5.���Ż��Ĺ��� 
 
 6.���Ժ��� 
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
    //�򿪼��а壨��Ϊ����Ϊ�����濪����֤�رգ�
	clipBoard = fopen( "clipBoard.txt", "w");
    //���ҵ��뿪ʼ���ƵĿ�ͷ
    fseek(buffFile,cursorBegin,0);
    //���ǵ��Գ������⣨����ɵ������fseek�������á�������
    //fseek( buffFile, 0, cursorBegin);
    //�ҳ���Ҫ���Ƶ��ı�����
    int length = cursorTail - cursorBegin;
    //����Ӹ��жϰɣ����ͷβһ�µĻ����͵���û��
    if(length == 0)	return;
    //����һ�������ַ�
    char temp;
    //����Ҫ���ַ�������clipBoard
    while( length){
        temp = fgetc( buffFile);
		fputc( temp, clipBoard);
        length--;
    }
    //�󹦸��
    return;
}

/*
Write����
 
 1.����������������壺
 	char inputChar;//������ַ���һ����ڼ�����Ӧ�¼��У���Ϊ���룩 
 2.�޷���ֵ 
 3.ʵ�ֵĹ��ܣ������ѡ�е�������buffFile��ɾ��������������ַ���ӵ��������λ�á�
 4.��Ҫ�õ��ĺ�����void Delete();
   ��Ҫ�õ���ȫ�ֱ����� FILE *buffFile;
   						int cursorBegin;
   						int cursorTail;
 5.���Ż��Ĺ��� 
 

 6.���Ժ��� 
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
	//һ�����ɻ����ļ� 
	FILE *tempFile = fopen("tempFile.txt","w");
	
	printf("tempFile open successfully!\n");
	
	//���������ļ�ͷ��ֱ�ӷ��� 
	if(cursorTail == 0)	return;
	//������δѡ�У������ͷǰ��һ����Ĭ��ɾ��ǰһ�� 
	if(cursorBegin == cursorTail)	cursorBegin--;
	char ch = 1;//�����ַ� 
	int i = 0;//�������λ�� 
	
	printf("loop will begin\n");
	
	while( 1){
		//�������ѡ������ֱ������ 
		if( i == cursorBegin ){
			i = cursorTail;
			continue;
		}
		//ÿһ�ζ�ˢ��һ���ļ���꣬ȷ��Ҫ��ȡ������Ҫ���ַ� 
		fseek(buffFile,i,0);
		//��ȡbuff File�е��ַ� 
		ch = fgetc(buffFile);
		//�ж�һ�£������EOF˵��������
		if(ch == EOF)	break; 
		//�����temp 
		fputc(ch,tempFile);
		//�ֶ��������� 
		i++;	
		printf("loop have continued for %d times\n",i);
	}
	//��buffFileˢ��һ�飬��temp�����ݶ���ȥ 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w");
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","a+");
	tempFile = fopen("tempFile.txt","r");
	
	printf("begin to write!\n");
	
	while(!feof(tempFile)){
		//��tempFile�п�ʼ��ȡ 
		ch = getc(tempFile);
		//�����EOF˵�������� 
		if(ch == EOF)	break;
		//����buffFile
		putc(ch,buffFile); 
	}
	
	printf("all down!\n");
	
	//�����ļ��͹غ�ϰ��
	fclose(tempFile); 
	//�����ĩβ�͹��ͷͳһ����Ϊ�м���Ѿ�ɾ����
	cursorTail = cursorBegin;	
}
 
void Write(char inputChar) 
{
	//�����ѡ�е����ݣ���ֱ��ɾ����
	if(cursorBegin<cursorTail)	Delete();
	
	//���濪ʼͨ�������ļ������ַ����� 
	//һ�����ɻ����ļ� 
	FILE *tempFile = fopen("tempFile.txt","w");
	char ch = 1;//�����ַ�
	int i=0;//�������λ�� 
	while( 1){
		//�������ѡ�����򣬾ͽ��ַ��ӽ�ȥ 
		if( i == cursorBegin )	fputc(inputChar,tempFile);
		//ÿһ�ζ�ˢ��һ���ļ���꣬ȷ��Ҫ��ȡ������Ҫ���ַ� 
		fseek(buffFile,i,0);
		//��ȡbuff File�е��ַ� 
		ch = fgetc(buffFile);
		//�ж�һ�£������EOF˵��������
		if(ch == EOF)	break; 
		//�����temp 
		fputc(ch,tempFile);
		//�ֶ��������� 
		i++;
	}
	//��buffFileˢ��һ�飬��tempFile�����ݶ���ȥ 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//��tempFile�п�ʼ��ȡ 
		ch = getc(tempFile);
		//�����EOF˵�������� 
		if(ch == EOF)	break;
		//����buffFile
		putc(ch,buffFile); 
	}
	//�����ļ��͹غ�ϰ��
	fclose(tempFile); 
	//���ڼ�����һ���ַ������Ӧ��Ҫ����һ��
	cursorBegin++;
	cursorTail++; 
}

/*
5.Cut����

Cut����
 
1.����������������壺
 	//����Ҫ�õ��������룬�ݻ� 
 2.�޷���ֵ 
 3.ʵ�ֵĹ��ܣ���ѡ�е�������buffFile��ɾ�� 
 4.��Ҫ�õ���ͷ�ļ���"graphics.h" 
   ��Ҫ�õ���ȫ�ֱ����� FILE *buffFile;
   						FILE *clipBoard;
   						int cursorBegin;
   						int cursorTail;
 5.���Ż��Ĺ��� 
 

 6.���Ժ��� 
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
	//һ�����ɻ����ļ� 
	FILE *tempFile = fopen("tempFile.txt","w");
	//���������ļ�ͷ��ֱ�ӷ��� 
	if(cursorTail == 0)	return;
	//������δѡ�У������ͷǰ��һ����Ĭ��ɾ��ǰһ�� 
	if(cursorBegin == cursorTail)	cursorBegin--;
	char ch = 1;//�����ַ� 
	int i = 0;//�������λ�� 
	while( !feof(buffFile)){
		//�������ѡ������ֱ������ 
		if( i == cursorBegin ){
			i = cursorTail;
			continue;
		}
		//ÿһ�ζ�ˢ��һ���ļ���꣬ȷ��Ҫ��ȡ������Ҫ���ַ� 
		fseek(buffFile,i,0);
		//��ȡbuff File�е��ַ� 
		ch = fgetc(buffFile);
		//�ж�һ�£������EOF˵��������
		if(ch == EOF)	break; 
		//�����temp 
		fputc(ch,tempFile);
		//�ֶ��������� 
		i++;
	}
	//��buffFileˢ��һ�飬��temp�����ݶ���ȥ 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//��tempFile�п�ʼ��ȡ 
		ch = getc(tempFile);
		//�����EOF˵�������� 
		if(ch == EOF)	break;
		//����buffFile
		putc(ch,buffFile); 
	}
	//�����ļ��͹غ�ϰ��
	fclose(tempFile); 
	//�����ĩβ�͹��ͷͳһ����Ϊ�м���Ѿ�ɾ����
	cursorTail = cursorBegin;	
}*/

 
void Cut() 
{
	//���δѡ���ַ�������ֱ�ӷ��� 
	if(cursorBegin == cursorTail)	return;
	//�Ƚ�����ַ������ƣ���ɾ���ַ��� 
	Copy();
	Delete();
}

/*
6.Paste����

Paste����
 
 1.����Ҫ����ı�����
 2.�޷���ֵ 
 3.ʵ�ֵĹ��ܣ���ѡ�е�������buffFile��ɾ������clipBoard��������ڹ�괦���뵽buffFile��
 4.��Ҫ�õ��ĺ�����void Write(char);
                void Delete();
   ��Ҫ�õ���ȫ�ֱ�����FILE *buffFile;
   					FILE *clipBoard;
   					int cursorBegin;
   					int cursorTail;
 5.���Ż��Ĺ��� 
 

 6.���Ժ��� 
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
	//�����ѡ�е����ݣ���ֱ��ɾ����
	if(cursorBegin<cursorTail)	Delete();
	
	//���濪ʼͨ�������ļ������ַ����� 
	//һ�����ɻ����ļ� 
	FILE *tempFile = fopen("tempFile.txt","w");
	char ch = 1;//�����ַ�
	int i=0;//�������λ�� 
	while( !feof(buffFile)){
		//�������ѡ�����򣬾ͽ��ַ��ӽ�ȥ 
		if( i == cursorBegin )	fputc(inputChar,tempFile);
		//ÿһ�ζ�ˢ��һ���ļ���꣬ȷ��Ҫ��ȡ������Ҫ���ַ� 
		fseek(buffFile,i,0);
		//��ȡbuff File�е��ַ� 
		ch = fgetc(buffFile);
		//�ж�һ�£������EOF˵��������
		if(ch == EOF)	break; 
		//�����temp 
		fputc(ch,tempFile);
		//�ֶ��������� 
		i++;
	}
	//��buffFileˢ��һ�飬��tempFile�����ݶ���ȥ 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//��tempFile�п�ʼ��ȡ 
		ch = getc(tempFile);
		//�����EOF˵�������� 
		if(ch == EOF)	break;
		//����buffFile
		putc(ch,buffFile); 
	}
	//�����ļ��͹غ�ϰ��
	fclose(tempFile); 
	//���ڼ�����һ���ַ������Ӧ��Ҫ����һ��
	cursorBegin++;
	cursorTail++; 
}

void Delete() 
{
	//һ�����ɻ����ļ� 
	FILE *tempFile = fopen("tempFile.txt","w");
	//���������ļ�ͷ��ֱ�ӷ��� 
	if(cursorTail == 0)	return;
	//������δѡ�У������ͷǰ��һ����Ĭ��ɾ��ǰһ�� 
	if(cursorBegin == cursorTail)	cursorBegin--;
	char ch = 1;//�����ַ� 
	int i = 0;//�������λ�� 
	while( !feof(buffFile)){
		//�������ѡ������ֱ������ 
		if( i == cursorBegin ){
			i = cursorTail;
			continue;
		}
		//ÿһ�ζ�ˢ��һ���ļ���꣬ȷ��Ҫ��ȡ������Ҫ���ַ� 
		fseek(buffFile,i,0);
		//��ȡbuff File�е��ַ� 
		ch = fgetc(buffFile);
		//�ж�һ�£������EOF˵��������
		if(ch == EOF)	break; 
		//�����temp 
		fputc(ch,tempFile);
		//�ֶ��������� 
		i++;
	}
	//��buffFileˢ��һ�飬��temp�����ݶ���ȥ 
	fclose(tempFile);
	fclose(buffFile);
	buffFile = fopen("buffFile.txt","w+");
	tempFile = fopen("tempFile.txt","r");
	while(!feof(tempFile)){
		//��tempFile�п�ʼ��ȡ 
		ch = getc(tempFile);
		//�����EOF˵�������� 
		if(ch == EOF)	break;
		//����buffFile
		putc(ch,buffFile); 
	}
	//�����ļ��͹غ�ϰ��
	fclose(tempFile); 
	//�����ĩβ�͹��ͷͳһ����Ϊ�м���Ѿ�ɾ����
	cursorTail = cursorBegin;	
}
}
 
*/ 
void Paste() 
{
	printf("Paste run!");
	
	if(cursorBegin < cursorTail)	Delete();
	//�򿪼��а��ļ�
	clipBoard = fopen("clipBoard.txt","r");
	//�Ѽ��а�����ļ����뵽buffFile��ȥ
	char ch;//�����ַ� 
	while( 1){
		ch = fgetc(clipBoard);
		if(ch == EOF)	break;//EOF˵�������� 
		//������ַ���buffFile����ȥ 
		Write( ch); 
	}
	//�ļ�����͹غ�ϰ��
	fclose(clipBoard); 
}

/*
 Search����
 
 1.������������壺
 	char *temp ��Ҫ�������ַ��� 
 2.�޷���ֵ
 3.ʵ�ֵĹ��ܣ��õ������ַ���ͷβָ���λ�� 
 4.��Ҫ�õ���ȫ�ֱ����� 
    FILE *buffFile;
    int cursorBegin;
    int cursorTail;
 5.���Ż��Ĺ��� 
 
 6.���Ժ��� 
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
	//�ҵ��ڼ���ָ��λ����
	int i=0;
    int tempLength = strlen(temp);
    char buff[100];
	while(!feof(buffFile)){
        //�����ַ�
        fseek(buffFile,i,0);
        char ch = fgetc(buffFile);
        //���������EOF��˵����ĩβ�ˣ������,û�ҵ�
        if(ch == EOF){
        	break;
		}
		//�����һ���ַ���û���ϣ�ֱ��continue
		if(ch != temp[0]){
			i++;
			continue;	
		}
        //���ƹ��
        fseek(buffFile,i,0);
        //��ȡ���ȵ�����,���ж��Ƿ��ȡ�ɹ���û�ɹ��ͱ���ˣ���ĩβ��
        while(fgets(buff,tempLength+1,buffFile)){
        	//��ȡ�ɹ��ˣ��Ա�һ�£�����ǣ��Ͱ���ѡ�У���������
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
        //���û�ɹ�������ѭ����ȱʡ���У�        
	}
	cursorBegin = cursorTail = 0;
	
    return;
} 

void Change(char* temp)
{
	
}
