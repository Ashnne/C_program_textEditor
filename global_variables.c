//����λ�ã�   ���壺����¼�ѡ���ı���ͷβָ��λ�ã���ѡ�е��ı����ݣ�
int cursorBegin = 1;
int cursorTail = 8;

//����λ�ã�   ���壺�ı��е�i����ӵ���ַ��ĸ���,
//�ر�ע�⣺1.��1��ʼ��������charCount[i] == �ı��е�i���ַ��ĸ��� 2.�ַ�������ĩβ��/n���ȵ�������Ҳ��һ���ַ�
int charCount[1000];

//������ɫ����ţ������ı�����ɫ 
int k=1;
//������ɫָ������ ��ɫ����ɫ������̡���ɫ����ɫ����ɫ����ɫ 
char* color[]={"Black","White","Hot Pink","Turquoise","Yellow","Medium Purple","Light Sky Blue","Salmon1"};

//���ڵĸߺͿ� 
double height, width;
//GetFontHeight()������ 
double f;

//����λ�ã�mouseEvent������������λ��   ���壺����ı����о�ͼ��
double textwidth = 0.187;//������֮������Ҿ���
double textheight = 0.14;//������֮�������

//���Ϊ�ļ���Ĭ������ 
char namedefault[101]="xxx.txt";
//textbox���� 
char content[100]="xxx.txt";

//���ֵ�ǰ�����ļ������ڴ򿪱༭�Ļ���δ�����
//ǰ���ڱ���ʱ���浽ԭ�ļ��������½��������������ļ�
int ifopen = 0;
//���������Ŀ��� 
int searchallow = -1;
//�����Ϊ���Ŀ��� 
int newAllow = -1;
//���������Ŀ��� 
int helpallow = -1;
//���滻���Ŀ��� 
int changeallow = -1;
//���ļ��򿪡��Ŀ���
int openallow = -1; 
//���ַ����롱�Ŀ���
int offput = 1; 

//��ʱ����� 
int timer_interval = 1;

//����λ�ã�   ���壺�ı����������
//�ر�ע�⣬��Count������ֵ
int rawMax;

//�Ӽ��̶�ȡ���ַ�
char charCh;  

//����λ�ã�   ���壺���״̬
double mouse_x;//���λ�õ�x��λ��
double mouse_y;//���λ�õ�y��λ��
int mouse_down;//����Ƿ�����1Ϊ���״̬��0Ϊ�ɿ�״̬
//�ر�ע�⣺ʹ�õ�λΪimgui�ģ�ԭ�������½�

//�����С
int size = 10; 

