#include "file.h"

/*���ļ���Ҫ������������OpenFile(),CloseFile(),FileSave()
  ���������������ļ����ļ�����ΪNewInterface()�б༭��textbox�е�namedefault�ַ����飨ȫ�֣� 
1.OpenFile()
 �����롢����ֵ
 ���ܣ���Դ�ļ������������ļ������Text�������ļ���ʾ��ʵ�ֽ�Դ�ļ���ͼ�ν�������ʾ�Ĺ���
2.CloseFile()
 �����롢����ֵ
 ���ܣ��������ļ���գ����Text�������ļ���ʾ��ʵ�ֽ�ͼ�ν�����յĹ���
3.FileSave()
 �����롢����ֵ
 ���ܣ��������ļ�������Դ�ļ�������ͼ�ν�����������ı�����ʽ�洢���ض��ļ������ļ��� 
*/


//��ʽ���� 
//������nת��Ϊ�ַ������ǰmλ 
char* IntToArray(int m,int n,char* a){
	a[m]='\0';
	do{
		m--;
		a[m]=n%10+'0';
		n/=10;
	}while(n||m);
	return a;
}

//����������ص�Ĭ���ļ��� 
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
		//д��ʱ��Ĭ��������Դ�ļ� 
		sourceFile=fopen(FileName(time(NULL),b),"w");
	//}
	//else{
		//д���ڱ༭��Դ�ļ� 
		//sourceFile=fopen(namedefault,"w"); 
	//}
	
	//�������ļ�
	//buffFile=fopen("buffFile.txt","r");
	
	//�����ļ�������Դ�ļ� 
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
		
	//��Դ�ļ� 
	sourceFile = fopen(name,"w");
	//buffFile=fopen("buffFile.txt","w");
	
	//�ı�Դ�ļ� 
	rewind(buffFile);
	while(!feof(buffFile)){
		c=fgetc(buffFile);
		fputc(c,sourceFile);
	}
	
	fclose(buffFile);
	fclose(sourceFile);
	
} 

void openFile(){
    /*char c;
    
	//�򿪶�Ӧ���ļ�
	sourceFile=fopen(name,"r");*/
	buffFile=fopen("buffFile.txt","a+");
	/*rewind(sourceFile);
	
	//�ı仺���ļ� 
	while(!feof(sourceFile)){
		c=fgetc(sourceFile);
		fputc(c,buffFile);
	}
	
	fclose(sourceFile);
	//fclose(buffFile);
	
	//���򿪵��ļ�������������ȫ�ֱ�����ʾ��ʱ���ļ����� 	
	strcpy(namedefault,name);*/
	ifopen=1;
} 

void CloseFile(){
	//��ջ����ļ�  
	//buffFile=fopen("buffFile.txt","w");
	fclose(buffFile);
	
	//��ʾ�ļ����򿪵�ȫ�ֱ�����Ϊ0 
	ifopen=0;
}

 
