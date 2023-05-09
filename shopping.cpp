#include<stdio.h>
#include<iostream>
using namespace std;
struct woods
{
	char ID[20], Name[20], Grade[20], From[20];//编号   名称   等级   过期时间   产地
	int Num;
	char MONEY[10],time[10];
	woods* next;
};
woods* create()
{
	woods* head = new woods,*pre = head, *p = NULL;
	FILE* fp;
	p = new woods;
	fopen_s(&fp, "data.txt", "r");
	while (fscanf_s(fp, "%s", p->ID, 8)!=EOF)
	{
		char num[10];
		fscanf_s(fp, "%s", p->Name, 9);
		fscanf_s(fp, "%s",num , 4);
		p->Num = 0;
		for (int n = 0;n < strlen(num);n++)
		{
			p->Num = p->Num * 10+ ( num[n]-48);
		}
		fscanf_s(fp, "%s", p->MONEY, 5);
		fscanf_s(fp, "%s", p->Grade, 2);
		fscanf_s(fp, "%s", p->time, 4);
		fscanf_s(fp, "%s", p->From, 5);
		pre->next = p;
		pre = p;
		p->next = NULL;
		p = new woods;
	}
	return head;
}
void print(woods*head)
{
	woods* p = head->next;
	while (p)
	{
		cout << "编号:" << p->ID<<endl
			<< "名称:" << p->Name << endl
			<< "现存数量:" << p->Num << endl
			<< "单价:" << p->MONEY << "元"<<endl
			<< "等级:" << p->Grade << endl
			<< "保质期:" << p->time <<"天"<< endl
			<< "产地:" << p->From << endl << endl;
		p = p->next;
	}
}
void Add(woods* head)
{
	woods* temp = head->next,*p=new woods,*pre=head;
	cout << "请输入要添加的商品信息：" << endl;
	int flag = 0;//0表示没有该商品，1表示有该商品
	cin >> p->ID;
	cin >> p->Name >> p->Num >> p->MONEY >>
		p->Grade >> p->time >> p->From;
	while (temp)
	{
		if (strcmp(temp->ID, p->ID) == 0)
		{
			temp->Num += p->Num;
			flag = 1;
			break;
		}
		pre = pre->next;
		temp = temp->next;
	}
	if (flag == 0)
	{
		pre->next = p;
		p->next = NULL;
	}
  }
void start()
{
	cout << "**********************************************************************************" << endl;
	cout << "                               超市销售管理系统                  " << endl;
	cout << "                    1.输入Show可查看当前商品情况      " << endl;
	cout << "                    2.输入Add可开始进行添加库存操作                " << endl;
	cout << "                    3.输入Sale可开始进行销售商品操作，并保存销售情况于文件中                " << endl;
	cout << "                    4.输入Check可开始进行核对信息操作                " << endl;
	cout << "                    5.输入Sort可开始进行排序操作                " << endl;
	cout << "                    6.输入over结束程序                " << endl;
	cout << "**********************************************************************************" << endl;
}

void sale(woods* head)
{
	int  Num_sale;
	char ID_sale[20];
	cout << "请输入出售商品的编号:" ;
	cin >> ID_sale;
	cout<< "请输入出售数量:";
	cin >> Num_sale;
	woods* p = head->next;
	FILE* fp;
	int error = fopen_s(&fp, "销售情况.txt", "w+");
	while (p)
	{
		if (strcmp(p->ID, ID_sale) == 0)
		{
			if (p->Num > +Num_sale)
			{
				p->Num = p->Num - Num_sale;
				fprintf(fp, "出售商品编号:%s\n", p->ID);
				fprintf(fp, "出售商品名称:%s\n", p->Name);
				fprintf(fp, "出售商品数量:%d\n", Num_sale);
				fprintf(fp, "剩余商品数量:%d\n\n", Num_sale);
			}
			else
				cout << "该商品库存不足！";
		}
		p = p->next;
	}
}
void check(woods* head)
{
	woods* temp = head->next, * p = new woods;
	cout << "输入要核对的商品信息:";
	cin >> p->ID;
	cin >> p->Name >> p->Num >> p->MONEY >> 
		p->Grade >> p->time >> p->From;
	int flag = 1;
	while (temp)
	{
		if (strcmp(temp->ID, p->ID) == 0)
		{
			if (strcmp(temp->Name, p->Name) != 0)
			{
				flag = 0;
				cout << "名称错误，正确名称应为:" << temp->Name;
			}
			if (temp->Num!=p->Num)
			{
				flag = 0;
				cout << "数量错误，正确数量应为:" << temp->Num;
			}
			if (strcmp(temp->MONEY, p->MONEY) != 0)
			{
				flag = 0;
				cout << "价格错误，正确价格应为:" << temp->MONEY;
			}
			if (strcmp(temp->Grade , p->Grade) != 0)
			{
				flag = 0;
				cout << "等级错误，正确等级应为:" << temp->Grade;
			}
			if (strcmp(temp->time , p->time) != 0)
			{
				flag = 0;
				cout << "保质期错误，正确保质期应为:" << temp->time;
			}
			if (strcmp(temp->From, p->From) != 0)
			{
				flag = 0;
				cout << "产地错误，正确产地应为:" << temp->From;
			}
		}
  temp = temp->next;
	}
	if (flag == 1)
		cout << "商品信息完全正确！";
}
void sort(woods* head)
{
	woods* pre = head->next, * p = pre->next, * temp;
	while (pre->next != NULL)
	{
		p = pre->next;
		while (p)
		{
			if (pre->Num > p->Num)
			{
				temp = new woods;
				//7个
				strcpy_s(temp->Grade, pre->Grade);
				strcpy_s(temp->MONEY , pre->MONEY);
				temp->Num = pre->Num;
				strcpy_s(temp->time , pre->time);
				strcpy_s(temp->From, pre->From);
				strcpy_s(temp->ID, pre->ID);
				strcpy_s(temp->Name, pre->Name);
				//
				strcpy_s(pre->Grade, p->Grade);
				strcpy_s(pre->MONEY , p->MONEY);
				strcpy_s(pre->time, p->time);				
				pre->Num = p->Num;				
				strcpy_s(pre->From, p->From);
				strcpy_s(pre->ID, p->ID);
				strcpy_s(pre->Name, p->Name);
				//
				strcpy_s(p->Grade , temp->Grade);
				strcpy_s(p->MONEY , temp->MONEY);
				strcpy_s(p->time , temp->time);
				
				
				p->Num = temp->Num;
				
				strcpy_s(p->From, temp->From);
				strcpy_s(p->ID, temp->ID);
				strcpy_s(p->Name, temp->Name);
			}
			p = p->next;
		}
		pre = pre->next;
	}
}
void main()
{
	start();
	woods* head = create();
	char order[10];
	cin >> order;
	while (strcmp(order, "over") != 0)
	{
		if (strcmp(order, "Show") == 0)
			print(head);
		else if (strcmp(order, "Add") == 0)
			Add(head);
		else if (strcmp(order, "Sale") == 0)
			sale(head);
		else if (strcmp(order, "Check") == 0)
			check(head);
		else if (strcmp(order, "Sort") == 0)
			sort(head);
		else
			cout << "输入指令错误，请重新输入！"<<endl;
		cin >> order;
	}
}
