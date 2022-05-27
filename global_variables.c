//定义位置：   意义：鼠标事件选中文本的头尾指针位置（既选中的文本内容）
int cursorBegin = 1;
int cursorTail = 8;

//定义位置：   意义：文本中第i行所拥有字符的个数,
//特别注意：1.从1开始计数，即charCount[i] == 文本中第i行字符的个数 2.字符个数含末尾的/n，既单纯空行也算一个字符
int charCount[1000];

//背景颜色的序号，用来改背景颜色 
int k=1;
//定义颜色指针数组 白色、粉色、翡翠绿、黄色、紫色、蓝色、橙色 
char* color[]={"Black","White","Hot Pink","Turquoise","Yellow","Medium Purple","Light Sky Blue","Salmon1"};

//窗口的高和宽 
double height, width;
//GetFontHeight()的两倍 
double f;

//定义位置：mouseEvent（）函数所在位置   意义：输出文本的行距和间宽
double textwidth = 0.187;//两个字之间的左右距离
double textheight = 0.14;//两个字之间的上下

//另存为文件名默认数组 
char namedefault[101]="xxx.txt";
//textbox内容 
char content[100]="xxx.txt";

//区分当前缓冲文件是正在打开编辑的还是未保存过
//前者在保存时保存到原文件，后者新建以日期命名的文件
int ifopen = 0;
//“搜索”的开关 
int searchallow = -1;
//“另存为”的开关 
int newAllow = -1;
//“帮助”的开关 
int helpallow = -1;
//“替换”的开关 
int changeallow = -1;
//“文件打开”的开关
int openallow = -1; 
//“字符输入”的开关
int offput = 1; 

//定时器间隔 
int timer_interval = 1;

//定义位置：   意义：文本中最大行数
//特别注意，用Count函数赋值
int rawMax;

//从键盘读取的字符
char charCh;  

//定义位置：   意义：鼠标状态
double mouse_x;//鼠标位置的x轴位置
double mouse_y;//鼠标位置的y轴位置
int mouse_down;//鼠标是否点击，1为点击状态，0为松开状态
//特别注意：使用单位为imgui的，原点在左下角

//字体大小
int size = 10; 

