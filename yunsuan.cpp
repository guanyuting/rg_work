#include <reg51.h>
#include <stdio.h>
#include<intrins.h> 
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>

#define uchar unsigned char
#define uint unsigned int
#define lcd_data P1

#define PD1  64        

uchar code dxCode[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //七段译码 
uchar code pxCode[]={0x40,0x20,0x10,0x08,0x04,0x02,0x01};	//数码管选择
xdata unsigned char CWADD1 _at_ 0x8000;  
xdata unsigned char DWADD1 _at_ 0x8001;
xdata unsigned char CRADD1 _at_ 0x8002;
xdata unsigned char DRADD1 _at_ 0x8003;
xdata unsigned char CWADD2 _at_ 0x8004;
xdata unsigned char DWADD2 _at_ 0x8005;
xdata unsigned char CRADD2 _at_ 0x8006;
xdata unsigned char DRADD2 _at_ 0x8007;

unsigned char Column;
unsigned char Page_ ;  
unsigned char Code_ ; 
unsigned char Command; 
unsigned char LCDData; 

code uchar all[][16]={
/*-- ID:0,字符:"0",ASCII编码:30,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0xf0,0x08,0x04,0x04,0x08,0xf0,0x00,0x00,0x07,0x08,0x10,0x10,0x08,0x07,0x00},

/*-- ID:1,字符:"1",ASCII编码:31,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x00,0x08,0x08,0xfc,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x1f,0x10,0x10,0x00},

/*-- ID:2,字符:"2",ASCII编码:32,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x38,0x04,0x04,0x04,0x84,0x78,0x00,0x00,0x18,0x14,0x12,0x11,0x10,0x18,0x00},

/*-- ID:3,字符:"3",ASCII编码:33,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x18,0x04,0x84,0x84,0x44,0x38,0x00,0x00,0x0c,0x10,0x10,0x10,0x11,0x0e,0x00},

/*-- ID:4,字符:"4",ASCII编码:34,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x00,0xc0,0x20,0x18,0xfc,0x00,0x00,0x00,0x03,0x02,0x12,0x12,0x1f,0x12,0x12},

/*-- ID:5,字符:"5",ASCII编码:35,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0xfc,0x44,0x44,0x44,0x84,0x04,0x00,0x00,0x0c,0x10,0x10,0x10,0x08,0x07,0x00},

/*-- ID:6,字符:"6",ASCII编码:36,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0xf0,0x88,0x44,0x44,0x48,0x80,0x00,0x00,0x07,0x08,0x10,0x10,0x10,0x0f,0x00},

/*-- ID:7,字符:"7",ASCII编码:37,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x0c,0x04,0x04,0xc4,0x34,0x0c,0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x00,0x00},

/*-- ID:8,字符:"8",ASCII编码:38,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x38,0x44,0x84,0x84,0x44,0x38,0x00,0x00,0x0e,0x11,0x10,0x10,0x11,0x0e,0x00},

/*-- ID:9,字符:"9",ASCII编码:39,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0xf8,0x04,0x04,0x04,0x88,0xf0,0x00,0x00,0x00,0x09,0x11,0x11,0x08,0x07,0x00},

/*-- ID:10,字符:".",ASCII编码:2E,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/ 
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00},//10

/*-- ID:11,字符:"+",ASCII编码:2B,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x80,0x80,0x80,0xf0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00},//11

/*-- ID:12,字符:"-",ASCII编码:2D,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//12

/*-- ID:13,字符:"*",ASCII编码:2A,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x20,0x20,0xc0,0xf8,0xc0,0x20,0x20,0x00,0x01,0x01,0x00,0x07,0x00,0x01,0x01,0x00},//13

/*-- ID:0,字符:"/",ASCII编码:2F,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x00,0x00,0x80,0x60,0x1c,0x02,0x00,0x00,0x30,0x0c,0x03,0x00,0x00,0x00,0x00},//14


/*-- ID:14,字符:"=",ASCII编码:3D,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00},//15


/*-- ID:0,字符:"(",ASCII编码:28,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x00,0x00,0xf0,0x0c,0x02,0x01,0x00,0x00,0x00,0x00,0x03,0x0c,0x10,0x20,0x00},//16

/*-- ID:1,字符:")",ASCII编码:29,对应字:宽x高=8x16,画布:宽W=8 高H=16,共16字节*/
{0x00,0x01,0x02,0x0c,0xf0,0x00,0x00,0x00,0x00,0x20,0x10,0x0c,0x03,0x00,0x00,0x00}//17

};
void delay(int n)
{
  int i;
  for(;n>0;n--)
	  for(i=500;i>0;i--);
}

void WriteCommandE1()
{
  while(CRADD1 & 0x80);
  CWADD1 = Command;
}

void WriteDataE1()
{
  while(CRADD1 & 0x80);
  DWADD1 = LCDData;
}

void ReadDataE1()
{
  while(CRADD1 & 0x80);
  LCDData = DRADD1;
}

void WriteCommandE2()
{
  while(CRADD2 & 0x80);
  CWADD2 = Command;
}

void WriteDataE2()
{
  while(CRADD2 & 0x80);
  DWADD2 = LCDData;
}

void ReadDataE2()
{
  while(CRADD2 & 0x80);
  LCDData = DRADD2;
}

void Init_LCD()
{
  Command = 0xe2;
  WriteCommandE1();
  WriteCommandE2();
  Command = 0xa4;
  WriteCommandE1();
  WriteCommandE2();
  Command = 0xa9;
  WriteCommandE1();
  WriteCommandE2();
  Command = 0xa1;
  WriteCommandE1();
  WriteCommandE2();
  Command = 0xc0;
  WriteCommandE1();
  WriteCommandE2();
  Command = 0xaf;
  WriteCommandE1();
  WriteCommandE2();
  Command = 0xb1;
  WriteCommandE1();
  WriteCommandE2();
}
// ??
void Clear()
{
  unsigned char i,j;
  i = 0;
  do {
    Command = (i + 0xb8); 
    WriteCommandE1();
    WriteCommandE2();
    Command = 0x00;      
    WriteCommandE1();
    WriteCommandE2();
    j = 0x50;           
    do {
      LCDData = 0x00;   
      WriteDataE1();
      WriteDataE2();
    }while(--j !=0);    
  }while(++i !=4);    
}                         
 void lcd12232_hanzi(char m,char n,char p,char y)   
{
char i,a;
Command = 0x00;       
WriteCommandE1();
WriteCommandE2();
Command = 0xb8+y;        
WriteCommandE1();
WriteCommandE2();
for(a=0;a<m;a++)         
{
  for(i=0;i<8;i++)        
  {
	  LCDData =all[a][i];
	  if(p==1){                  
              WriteDataE1();        
                   }
	  else{
               WriteDataE2();          
               }
  }
}
Command = 0x00;
WriteCommandE1();
WriteCommandE2();
Command = 0xb9+y;           
WriteCommandE1();
WriteCommandE2();
for(a=0;a<m;a++)            
{
  for(i=8;i<16;i++)          
  {
    LCDData =all[a][i];     
	  if(p==1){                               
                  WriteDataE1();               
                 }  
	  else{WriteDataE2();}                    
		}
	}
}

xdata char  calaCode[10]={"\0"};
xdata float calaFl[10];
xdata float stack[10];
//当前栈内的大小
xdata uchar  curSize = 0;
//栈订元素的所在位置
xdata uchar top = 0;
bit isFinish = 0;
char curTemp[1]='n';
int  curAns=0;
float ccf;
xdata char cf[5]={"\0"},cs[5]={"\0"},ct[5]={"\0"};
uchar curChose = 0;
 float pop() {
	 if (top > 0) {
		 curSize--;
		 return stack[--top];
	 }
 }
 void push(float temp) {
	 stack[top++] = temp;
	 curSize++;
 }
 xdata uchar  fLen = 0;
 void toCheck(int start,float base) {
	xdata  float cur,curData;
	 if (curSize &&curSize> start) {
		  cur = pop();
			if (cur == 10001 || cur == 10002) {
				push(cur);
			}
			else {
				curData = pop();
				base = cur ==10003 ? base * curData : curData / base;
			}
	 }
	 push(base);
 }

 void getSum(int start) {
	xdata float fdata;
	 xdata float oper;
	 xdata float sdata;
	 while (curSize >=start + 3) {
		 fdata = pop();
		 oper = pop();
		 sdata = pop();
		 fdata = oper == 10001? fdata + sdata : sdata - fdata;
		 push(fdata);
	 }
 }
 float getAns() {
	idata int i = 0, j;
	idata float base = 0;
	 for (; i < fLen; i++) {
		 if (calaFl[i] < 10000) {
			 base = calaFl[i];
		 }
		 else if (calaFl[i] != 10005) {
			 if (base != 0) {
				 toCheck(0, base);
			 }
			 push(calaFl[i]);
			 base = 0;
		 }
		 else {
			 j = i++;
			 while (calaFl[i] != 10006) {
				 if (calaFl[i] < 10000) {
					 base = calaFl[i];
				 }
				 else {
					 toCheck(j, base);
					 push(calaFl[i]);
				 }
				 i++;
			 }
			 push(base);
			 getSum(j);
			 base = 0;
			 }
		 }
	 if (base != 0) {
		 push(base);
	 }
	 toCheck(0, pop());
	 getSum(0);
	 return stack[0];
 }
 void toFunCaclF() {
	xdata float  base = 0;
	xdata float dase = 10;
	 uchar isZ = 0;
	uchar i= 0;
	 for (; i < 10 && calaCode[i] != '\0'; i++) {
			if(calaCode[i]=='='){
			break;
}
		 if (calaCode[i] >= '0' && calaCode[i] <= '9') {
			 if (isZ == 0) {
				 base = base * 10 + calaCode[i] - '0';
			 }
			 else {
				 base += (calaCode[i] - '0') / dase;
				 dase *= 10;
			 }
		 }
		 else if (calaCode[i] == '.') {
			 isZ = 1;
		 }
		 else {
			 if (base != 0) {
				 calaFl[fLen++] = base;

			 }
			 base = 0;
			 dase = 10;
			 isZ = 0;
			 switch (calaCode[i]) {
			 case '+': calaFl[fLen] = 10001; break;
			 case '-':calaFl[fLen] = 10002; break;
			 case '*': calaFl[fLen] = 10003; break;
			 case'/': calaFl[fLen] = 10004; break;
			 case'(':calaFl[fLen] = 10005; break;
			 case')':calaFl[fLen] = 10006; break;
			 }
			 fLen++;
		 }
	 }
	 if (base != 0) {
		 calaFl[fLen++] = base;
	 }
 }

xdata unsigned char px _at_ 0x9002;	//片选px
xdata unsigned char dx _at_	0x9004;//段选dx 
xdata unsigned char key_in _at_	0x9001;
//外部中断1
void my_int1() interrupt 2{
		curChose=(curChose+1)%3;
		
}
//定时器0
void my_time0() interrupt 1{	
	
}
//定时器1
void my_time1() interrupt 3{

}
void toCheck(float base);
//扫描键盘按键
struct Info toFunAns(char  * s,uchar curlen, uchar index);
char  key_scanner(void);

//外部中斷0清零功能
void my_int0() interrupt 0{
	int i = 0;
  for(;i<5;i++){
    cf[i]='\0';
    cs[i]='\0';
    ct[i]='\0';
    calaCode[i]='\0';
	stack[i]=0;
	calaFl[i]=0;
  }
  for(;i<10;i++){
    calaCode[i]='\0';
	stack[i]=0;
	calaFl[i]=0;
  }
	top = 0;
	curSize=0;
  isFinish=0;
	fLen = 0;
  
}

void Init(){
  EX0 = 1;
  EX1 = 1;
  IT0 = 1;
  IT1 = 1;
  EA  = 1;
}

/*键盘新扫描*/
char key_scanner(){
	uchar   column=0xfe;//列扫描值
	uint    result=0x0000;
	while(column!=0xbf){
		px=column;
		if((key_in&0x0f)!=0x0f){
			delay(15);//消抖
			if((key_in&0x0f)!=0x0f){
				result=((~key_in&0x0f)<<8)+(~column&0x3f);//高位为行值地位为列值
	while((key_in&0x0f)!=0x0f){}
				switch (result){
					//第一行
					case 0x0120:
					return '0';
					case 0x0110:
					return '.';
					case 0x0108:
					return '=';
					case 0x0104:
					return '(';
					case 0x0102:
					return ')';
					case 0x0101:
					return '.';
					case 0x0220:
					//第二行
					return '1';
					case 0x0210:
					return '2';
					case 0x0208:
					return '3';
					case 0x0204:
					return '*';
					case 0x0202:
					return '(';
					case 0x0201:
					return '.';
					//第三行
					case 0x0420:
					return '4';
					case 0x0410:
					return '5';
					case 0x0408:
					return '6';
					case 0x0404:
					return '-';
					case 0x0402:
					return ')';
					case 0x0401:
					return '.';
					//第四行
					case 0x0820:
					return '7';
					case 0x0810:
					return '8';
					case 0x0808:
					return '9';
					case 0x0804:
					return '+';
					case 0x0802:
					return '(';
					case 0x0801:
					return '.';
				}
			}
		}
		column=(column<<1)+1;//左移列扫描值
		delay(1);
	}
	return 'n';
}



int get_check_lcd(char cur){
	if(cur>='0'&&cur<='9'){
		return cur-'0';
	}else if(cur == '.'){
			return 10;}
else if(cur == '+'){
			return 11;}
else if(cur == '-'){
			return 12;}
else if(cur == '*'){
			return 13;}
else if(cur == '/'){
			return 14;}
else if(cur == '('){
			return 15;}
else if(cur == ')'){
			return 16;}
}
void lcd_show_12232(int *cur,int len,char p,char y)   
{
char i,a;
Command = 0x00;       
WriteCommandE1();
WriteCommandE2();
Command = 0xb8+y;        
WriteCommandE1();
WriteCommandE2();
for(a=0;a<len;a++)         
{
  for(i=0;i<8;i++)        
  {
	  LCDData =all[cur[a]][i];
	  if(p==1){                  
              WriteDataE1();        
                   }
	  else{
               WriteDataE2();          
               }
  }
}
Command = 0x00;
WriteCommandE1();
WriteCommandE2();
Command = 0xb9+y;           
WriteCommandE1();
WriteCommandE2();
for(a=0;a<len;a++)            
{
  for(i=8;i<16;i++)          
  {
    LCDData =all[cur[a]][i];     
	  if(p==1){                               
                  WriteDataE1();               
                 }  
	  else{WriteDataE2();}                    
		}
	}
}
int curLen = 0;
xdata int left_check[7];
xdata int right_check[7];
void lcd_show(char *p,uchar pageIndex){
	 curLen = 0;
	while(p[curLen]!='\0'){
		if(curLen <7){
		left_check[curLen] = get_check_lcd(p[curLen]);
		}else {
		right_check[curLen-7] = get_check_lcd(p[curLen]);
	}
	curLen++;
	}
 Clear();
	lcd_show_12232(left_check,curLen<7?curLen:7,1,pageIndex);
	
   if(curLen>=7){
		lcd_show_12232(right_check,curLen-7,2,pageIndex);
	}
}
int main(){
	uchar curCS = 0,preChose  = -1;
	Init();
Init_LCD();
 Clear();
while(1){
	if(!isFinish){
	curTemp[0]=key_scanner();
	if(curTemp[0]!='n'){
	strcat(calaCode,curTemp);
	if(curTemp[0]=='='){
	isFinish=1;
	curCS = 0;
	}
lcd_show(calaCode,0);
	}
}else if(isFinish==1){
	if(curCS==0){
	toFunCaclF() ;
	ccf = getAns();
	curAns=ccf;
	sprintf(cf,"%x",curAns);
	sprintf(cs,"%o",curAns);
	sprintf(ct,"%.2f",ccf);
	curCS = 1;
}
 if(curChose==0){
	if(preChose!=curChose){
	lcd_show(ct,2);
	preChose=curChose;
	}
}else if(curChose==1){
	if(preChose!=curChose){
		lcd_show(cs,2);
preChose=curChose;
	}
	  }else{
	if(preChose!=curChose){
		lcd_show(cf,2);
		preChose=curChose;
				}
			}
		}
	}
  return 0;
} 
