#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define Snake_Len 500//������
#define Number 25//�ϰ�����
//ö�ٷ���
enum DIR	//����
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};   
//�ߵĽṹ
struct Snake
{
	int size;                             //�ߵĽ���
	int dir;                              //�ߵķ���
	int speed;							  //�ߵ��ٶ�
	POINT coor[Snake_Len];                //�ߵ�����
}S;
//ʳ��ṹ
struct Food
{
	int x;
	int y;
	int r;//ʳ���С
	bool flag;//ʳ���Ƿ񱻳�
	DWORD color;//ʳ����ɫ
	int grade;
}F;
//�ϰ��ṹ
struct Obstacle
{
	POINT xy[Number];
	int n;
}O;
//���ݳ�ʼ��
void Gameinit()
{	//����
	initgraph(640, 480);
	HWND hWnd = GetHWnd();       //��ȡ���ھ��
	SetWindowText(hWnd,"̰����");//�޸Ĵ��ڱ���
	//�ϰ�
	O.n = Number;
	srand(GetTickCount());
	for (int i = 0; i < Number; i++)
	{
		O.xy[i].x = rand() % 63 * 10 + 10;
		O.xy[i].y = rand() % 47 * 10 + 10;
	}
	//�ϰ��鲻���ص�
	for (int i = 0; i < Number-1; i++)
	{
		for (int t = 1; t < Number; t++)
		{
			if (O.xy[i].x == O.xy[t].x && O.xy[i].y == O.xy[t].y)
			{
				O.xy[i].x = rand() % 63 * 10 + 10;
				O.xy[i].y = rand() % 47 * 10 + 10;
			}
		}
	}
	//��
	S.size = 1;
	S.speed = 10;
	S.dir=RIGHT;
	for (int i = 0; i < S.size; i++)
	{
		S.coor[i].x = 320-i*10;
		S.coor[i].y = 240;
	}
	//�ϰ��鲻�ܳ�������ͷ��Χ��������
	for (int i = 0; i < Number; i++)
	{
		if (O.xy[i].x >= S.coor[0].x && O.xy[i].x<S.coor[0].x + 5 && O.xy[i].y>S.coor[0].y - 4 && O.xy[i].y < S.coor[0].y + 4)
		{
			O.xy[i].x = rand() % 63 * 10 + 10;
			O.xy[i].y = rand() % 47 * 10 + 10;
		}
		for (int t = 1; t < S.size; t++)
		{
			if (O.xy[i].x == S.coor[i].x && O.xy[t].y == S.coor[t].y)
			{
				O.xy[i].x = rand() % 63 * 10 + 10;
				O.xy[i].y = rand() % 47 * 10 + 10;
			}
		}
	}
	//ʳ��
	F.x = rand() % 63 * 10 + 10;
	F.y = rand() % 47 * 10 + 10;
	F.color = RGB(205, 155, 29);
	F.r = 5;
	F.flag = true;
	F.grade = 0;
	//���ʳ�������������
	for (int i = 0; i < S.size; i++)
	{
		if (F.x == S.coor[i].x && F.y == S.coor[i].y)
		{
			F.x = rand() % 63 * 10+10;
			F.y = rand() % 47 * 10+10;
		}
	}
	//���ʳ��������ϰ���
	for (int i = 0; i < Number; i++)
	{
		if (F.x == O.xy[i].x && F.y == O.xy[i].y)
		{
			O.xy[i].x = rand() % 63 * 10 + 10;
			O.xy[i].y = rand() % 47 * 10 + 10;
		}
	}
}
//��ʼ����
void Start()
{
	IMAGE start,illustraion;
	loadimage(&start, "./Snake_LI.jpg", 640, 480);
	loadimage(&illustraion, "./Illusrtation.png", 200, 100);
	mciSendString("open ��ѩ����-��ѩ����������_�ٷ���_.mp3 alias Start", NULL, 0, NULL);
	mciSendString("play Start repeat", NULL, 0, NULL);
	putimage(0, 0, &start);
	putimage(180, 200, &illustraion);
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	outtextxy(380, 300, "��PRESS�� �������������Ϸ");
	system("pause");
	mciSendString("pause Start", NULL, 0, NULL);
	PlaySound("./ɵ��һ��¬��ΰ׼������.wav", NULL, 0);
	mciSendString("resume Start", NULL, 0, NULL);
}
//����
void Gamedraw()
{	//���Ʊ���
	BeginBatchDraw();
	setbkcolor(RGB(250, 249, 222));
	cleardevice();
	//������
	for (int i = 0; i < S.size; i++)
	{
		setfillcolor(RGB(rand()%255, rand() % 255, rand() % 255));
		setlinecolor(GREEN);
		fillroundrect(S.coor[i].x-5, S.coor[i].y+5, S.coor[i].x+5, S.coor[i].y-5, 2, 2);
	}
	//����ʳ��
	if (F.flag)
	{
		setfillcolor(F.color);
		setlinecolor(BLACK);
		fillcircle(F.x, F.y, F.r);
	}
	//�����ϰ���
	for (int i = 0; i < Number; i++)
	{
		setfillcolor(BLACK);
		setlinecolor(BLACK);
		fillrectangle(O.xy[i].x - 5, O.xy[i].y + 5, O.xy[i].x + 5, O.xy[i].y - 5);
	}
	//��ӡ����
	char grades[100] = " ";
	sprintf_s(grades, "%d", F.grade);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(580, 15, "����:");
	outtextxy(620, 15, grades);
	EndBatchDraw();
}
//�ƶ���
void move()
{
	for (int i = S.size-1; i > 0; i--)
	{
		S.coor[i] = S.coor[i - 1];
	}
	switch (S.dir)
	{
	case RIGHT:
		S.coor[0].x+=10;
		if (S.coor[0].x - 5 >= 640)//������Ե
		{
			S.coor[0].x = 0;
		}
		break;
	case LEFT:
		S.coor[0].x-=10;
		if (S.coor[0].x + 5 <= 0)
		{
			S.coor[0].x = 640;
		}
		break;
	case UP:
		S.coor[0].y-=10;
		if (S.coor[0].y+5 <= 0)
		{
			S.coor[0].y = 480;
		}
		break;
	case DOWN:
		S.coor[0].y+=10;
		if (S.coor[0].y - 5 >= 480)
		{
			S.coor[0].y = 0;
		}
		break;
	default:
		break;
	}
}
//�����ı��ߵķ���
void keyControl()
{
	if(_kbhit())//�ж��Ƿ�������,�а����ͷ�����
	{
		switch (_getch())
		{
		case'w':
		case'W':
		case 72:
			if (S.dir != DOWN)
			{
				S.dir = UP;
			}
			break;
		case's':
		case'S':
		case 80:
			if (S.dir != UP)
			{
				S.dir = DOWN;
			}
			break;
		case'a':
		case'A':
		case 75:
			if (S.dir != RIGHT)
			{
				S.dir = LEFT;
			}
			break;
		case'd':
		case'D':
		case 77:
			if (S.dir != LEFT)
			{
				S.dir = RIGHT;
			}
			break;
		case 27:
			MessageBox(NULL, "                ������","��ͣ ", MB_OK| MB_SETFOREGROUND);
			break;
		default:
			break;
		}
	}
}
void Eatfood()
{
	if (S.coor[0].x+3 >= F.x && S.coor[0].x-3 <= F.x&&
		S.coor[0].y+3 >= F.y && S.coor[0].y-3 <= F.y&&
		F.flag)
	{
		F.flag = false;
		S.size++;
		F.grade++;
	}
	if (!F.flag)
	{
		F.x = rand() % 63 * 10 + 10;
		F.y = rand() % 47 * 10 + 10;
		//���ʳ����������
		for (int i = 0; i < S.size; i++)
		{
			if (F.x == S.coor[i].x && F.y == S.coor[i].y)
			{
				F.x = rand() % 63 * 10+10;
				F.y = rand() % 47 * 10+10;
			}
		}
		//ʮ�ָ���һ���ϰ���
		if (F.grade % 10 == 0)
		{
			for (int i = 0; i < Number; i++)
			{
				O.xy[i].x = rand() % 63 * 10 + 10;
				O.xy[i].y = rand() % 47 * 10 + 10;
			}
			//�ϰ��鲻���ص�
			for (int i = 0; i < Number - 1; i++)
			{
				for (int t = 1; t < Number; t++)
				{
					if (O.xy[i].x == O.xy[t].x && O.xy[i].y == O.xy[t].y)
					{
						O.xy[i].x = rand() % 63 * 10 + 10;
						O.xy[i].y = rand() % 47 * 10 + 10;
					}
				}
			}
			//�ϰ��鲻�ܳ�������ͷ��Χ��������
			for (int i = 0; i < Number; i++)
			{
				if (O.xy[i].x >= S.coor[0].x && O.xy[i].x<S.coor[0].x + 5 && O.xy[i].y>S.coor[0].y - 4 && O.xy[i].y < S.coor[0].y + 4)
				{
					O.xy[i].x = rand() % 63 * 10 + 10;
					O.xy[i].y = rand() % 47 * 10 + 10;
				}
				for (int t = 1; t < S.size; t++)
				{
					if (O.xy[i].x == S.coor[i].x && O.xy[t].y == S.coor[t].y)
					{
						O.xy[i].x = rand() % 63 * 10 + 10;
						O.xy[i].y = rand() % 47 * 10 + 10;
					}
				}
			}
			//ʳ�ﲻ�����ϰ�����
			for (int i = 0; i < Number; i++)
			{
				if (F.x == O.xy[i].x && F.y == O.xy[i].y)
				{
					O.xy[i].x = rand() % 63 * 10 + 10;
					O.xy[i].y = rand() % 47 * 10 + 10;
				}
			}
		}
			F.flag = true;
	}
}
int Gameover()
{
	int result;
	for (int i = 1; i < S.size; i++)
	{
		if (S.coor[0].x == S.coor[i].x && S.coor[0].y == S.coor[i].y)
		{
			settextcolor(RED);
			settextstyle(100, 30, "΢���ź�");
			outtextxy(180, 190, "You Died!");
			mciSendString("close Start ", NULL, 0, NULL);
			PlaySound("./����.wav", NULL, 0);
			result = MessageBox(NULL, "\t�ؿ���", "����", MB_ICONHAND| MB_SETFOREGROUND| MB_YESNO);
			switch (result)
			{
			case IDYES:
				mciSendString("play Start repeat", NULL, 0, NULL);
				Gameinit();
				return 0;
				break;
			case IDNO:
				return 1;
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < Number; i++)
	{
		if (S.coor[0].x==O.xy[i].x&&S.coor[0].y==O.xy[i].y)
		{
			settextcolor(RED);
			settextstyle(100,30,"΢���ź�");
			outtextxy(180, 190, "You Died!");
			mciSendString("close Start ", NULL, 0, NULL);
			PlaySound("./����.wav", NULL, 0);
			mciSendString("open ��ѩ����-��ѩ����������_�ٷ���_.mp3 alias Start", NULL, 0, NULL);
			result = MessageBox(NULL, "\t�ؿ���", "����", MB_ICONHAND | MB_SETFOREGROUND | MB_YESNO);
			switch (result)
			{
			case IDYES:
				mciSendString("play Start repeat", NULL, 0, NULL);
				Gameinit();
				return 0;
				break;
			case IDNO:
				return 1;
				break;
			default:
				break;
			}
			return 1;
		}
	}
	return 0;
}
int main()
{
	Gameinit();
	Start();
	while (1)
	{
		move();
		keyControl();
		Gamedraw();
		if (Gameover())
			break;
		Eatfood();
		Sleep(80);
	}
	return 0;
}