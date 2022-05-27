#include"mouse.h"

void mouseEvent(){
    static int judgeUp = 0;
	if(mouse_down == 0 && judgeUp == 0)	return; 
    //�����ȡ���������״̬����ֵ
    double mouseX = mouse_x;
    double mouseY = mouse_y;
    //���︳ֵһ������ԭ��
    double X_zero = width / 10;
    double Y_zero =  height - f * 2 ;
    //����꿪ʼ���ʱ��ʼ����,ͬʱ�����Ǻ�judgeUp����һ���ɿ�����ʱ���ٴμ�¼����

    if( mouse_down == 1 && judgeUp == 0){
        //������Ҫȷ���������λ�õĹ��,���ø�������mouseEventCursor
        cursorBegin = mouseEventCursor( mouseX, mouseY, X_zero, Y_zero, textwidth, textheight);
        //��������һ�¹�����λ��
        cursorTail = cursorBegin;
        judgeUp = 1;
    }
    //�����ж�һ�£���갴���ɿ��ˣ������ǵ�һ��
    if( mouse_down == 0 && judgeUp == 1 ){
        //�Ȱ��жϸ�һ�£��Ѿ��ɿ���
        judgeUp = 0;
        //����ͬ����Ҫȷ���������λ�õĹ�꣬������������
        cursorTail = mouseEventCursor( mouseX, mouseY, X_zero, Y_zero, textwidth, textheight);
        //�����ٽ���һ�����ԣ�ȷ��cursorTailС��cursorBegin
        if(cursorTail < cursorBegin){
            int temp;
            temp = cursorTail;
            cursorTail = cursorBegin;
            cursorBegin = temp;
        }
    }
}




/*
mouseEventCursor����(��������)
{
1.����������������壺
	double mouseX;//�������λ�õ�X����
    double mouseY;//�������λ�õ�Y����
    double X;     //����ԭ���X����
    double Y;     //����ԭ���Y����
    double width; //�����ַ��Ŀ��
    double height;//�����ַ��ĸ߶�
 2.����ֵ�����ͣ�int ���壺�����λ�����ı��еĹ��λ��
 3.ʵ�ֵĹ��ܣ�����굱ǰ�����λ��ת��Ϊ�ı��й��λ�ò����� 
 4.��Ҫ�õ���ȫ�ֱ����� int charCount[1000];
 5.���Ż��Ĺ��� 
 
  ���ּ��ݣ���ʱ��˼·�޷����ֺ��ֺ�Ӣ����ĸ��
 
 6.���Ժ��� 
 
 //��д
}
*/



int mouseEventCursor(double mouseX,double mouseY, double X, double Y, double width, double height){
    //����һ�����λ�ã�����任����ԭ��Ϊ��X��Y�����������Ϸ���������Ϊ���£�����
    mouseX = mouseX - X;
    mouseY = Y - mouseY;
    //�������������������Ϊ��charY�У���charX��
    int charX;
    int charY;
    //ȷ����һ���еĵڼ�����������ƶ���������ǰ��ʱ����Ҫ�����ƶ�����λ��
    charX = (int )((mouseX+textwidth/2)/textwidth);
    //ȷ���ڵڼ��У�������ڵڼ����г���
    charY = (int )(mouseY/textheight + 1);
    //����Ҫ��ʼ�������ڵĹ��λ����,locationΪ�������λ��
    int location = 0;
    //���ȷ�ֹy�������ѡ��λ���������ݵĻ�Ĭ��Ϊ����������ݵ�һ��,��ൽ��һ��
    while( !charCount[charY] && charY!=1 )   charY--;
    //��ǰ�����еĹ����������ӵ�location�У���ʱlocation�Ѿ��ƶ�����charY�е�0��λ������
    //�˴�ע�⣬i�Ǵ�1��ʼ����
    int i;
    for( i = 1;i < charY;i++){
        location+=charCount[i] + 1;
    }
    //�ٶ�location����charY���ڵĵ���
    location += charX;
    
    printf("location is %d\ncharX is %d\ncharY is %d\n",location,charX,charY);
    
    
    //��ʱ���ļ�ͷ��ʼ����ƶ�location����꼴Ϊ������Ĺ��
    return location;
}
