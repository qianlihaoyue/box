//选关  选择界面设置

#include<graphics.h>
#include <conio.h>
#include<easyx.h>
#include<windows.h>


#define zoom 240

int i, j, x, y, w1, w2, path, level = 1, step = 0, stepcount = 0;
int map[20][20], count[1000], record[1000];
int bgmopt = 1;

IMAGE man, star, box, boxed, manstar, wall, bk, smallbk;
IMAGE man1, star1, box1, manstar1;
IMAGE bgmon, bgmoff, imgundo, imgreset;


void system_init();
void map_init(int a[20][20]);
void level_init(int level);

void show_map();
void move();
void undo();
void success();
void show_opt();

void up();
void down();
void left();
void right();

int map_1[20][20] = {
	{ 0,0,2,2,2,0,0,0 },
	{ 0,0,2,4,2,0,0,0 },
	{ 0,0,2,0,2,2,2,2 },
	{ 2,2,2,3,3,0,4,2 },
	{ 2,4,0,3,1,2,2,2 },
	{ 2,2,2,2,3,2,0,0 },
	{ 0,0,0,2,4,2,0,0 },
	{ 0,0,0,2,2,2,0,0 },
};

int map_2[20][20] = {
	{ 2,2,2,2,2,0,0,0,0 },
	{ 2,1,0,0,2,0,0,0,0 },
	{ 2,0,3,3,2,0,2,2,2 },
	{ 2,0,3,0,2,0,2,4,2 },
	{ 2,2,2,0,2,2,2,4,2 },
	{ 0,2,2,0,0,0,0,4,2 },
	{ 0,2,0,0,0,2,0,0,2 },
	{ 0,2,0,0,0,2,2,2,2 },
	{ 0,2,2,2,2,2,0,0,0 },
};

int map_3[20][20] = {
	{ 0,2,2,2,2,2,2,2,0,0 },
	{ 0,2,0,0,0,0,0,2,2,2 },
	{ 2,2,3,2,2,2,0,0,0,2 },
	{ 2,0,1,0,3,0,0,3,0,2 },
	{ 2,0,4,4,2,0,3,0,2,2 },
	{ 2,2,4,4,2,0,0,0,2,0 },
	{ 0,2,2,2,2,2,2,2,2,0 },
};

int map_4[20][20] = {
	{ 0,2,2,2,2,0 },
	{ 2,2,0,0,2,0 },
	{ 2,1,3,0,2,0 },
	{ 2,2,3,0,2,2 },
	{ 2,2,0,3,0,2 },
	{ 2,4,3,0,0,2 },
	{ 2,4,4,7,4,2 },
	{ 2,2,2,2,2,2 },
};

int map_5[20][20] = {
	{ 2,2,2,2,2,2,2,0,0 },
	{ 2,0,0,0,0,0,2,0,0 },
	{ 2,0,3,3,3,2,2,0,0 },
	{ 2,0,0,2,4,4,2,2,2 },
	{ 2,2,0,0,4,4,3,0,2 },
	{ 0,2,0,1,0,0,0,0,2 },
	{ 0,2,2,2,2,2,2,2,2 },
};

int map_6[20][20] = {
	{ 0,2,2,2,2,0,0,0 },
	{ 0,2,1,0,2,2,2,0 },
	{ 0,2,0,3,0,0,2,0 },
	{ 2,2,2,0,2,0,2,2 },
	{ 2,4,2,0,2,0,0,2 },
	{ 2,4,3,0,0,2,0,2 },
	{ 2,4,0,0,0,3,0,2 },
	{ 2,2,2,2,2,2,2,2 },
};

void show_opt()
{
	POINT point;
	HWND hwnd = GetHWnd();

	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);


	setaspectratio(0.2, 0.2);              //414  116
	fillcircle(2090, 570, 120);


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		i = point.x / 20;
		j = point.y / 20;
		Sleep(20);

		if (i == 20 && j == 5)
		{
			bgmopt = !bgmopt;
		}

	}

	if (bgmopt) putimage(1000, 480, &box);
	else putimage(1000, 480, &bgmoff);
	settextstyle(80, 0, _T("华文行楷"));
	outtextxy(40, 40, _T("胜出"));


}

void main()
{
	system_init();
	level_init(level);

	//////////////////// 
	while (1)
	{

		move();
		show_map();
		show_opt();

		//while (1);
		success();
		Sleep(20);
	}
}

void move()
{
begin:
	w1 = w2 = 2;
	path = 0;
	if (_kbhit())
	{
		switch ((int)_getch())
		{
		case 'w':case 'W':case 72: path = 1;     break;
		case 'a':case 'A':case 75: path = 2;     break;
		case 's':case 'S':case 80: path = 3;     break;
		case 'd':case 'D':case 77: path = 4;     break;
		case 'z':case 'Z':undo();  goto begin; break;
		default:goto begin;
		}
		switch (path)
		{
		case 1:w1 = map[x][y - 1]; w2 = map[x][y - 2]; break;
		case 2:w1 = map[x - 1][y]; w2 = map[x - 2][y]; break;
		case 3:w1 = map[x][y + 1]; w2 = map[x][y + 2]; break;
		case 4:w1 = map[x + 1][y]; w2 = map[x + 2][y]; break;
		}

		if (w1 == 2 || (w1 % 4 == 3 && (w2 == 2 || w2 % 4 == 3)))
			goto begin;


		map[x][y]--;

		switch (path)
		{
		case 1: up();    y--; break;
		case 3: down();  y++; break;
		case 2: left();  x--; break;
		case 4: right(); x++; break;
		}

		step++;
		stepcount++;
		count[step] = path;
		if (w1 % 4 == 3) record[step] = 1;
	}

}
void undo()
{
	if (!step) move();
	map[x][y]--;
	if (count[step] == 1)
	{
		map[x][y + 1]++;
		if (map[x][y - 1] % 4 == 3 && record[step])
		{
			map[x][y - 1] -= 3;
			map[x][y] += 3;
		}
		y++;
	}
	if (count[step] == 3)
	{
		map[x][y - 1]++;
		if (map[x][y + 1] % 4 == 3 && record[step])
		{
			map[x][y + 1] -= 3;
			map[x][y] += 3;
		}
		y--;
	}
	if (count[step] == 2)
	{
		map[x + 1][y]++;
		if (map[x - 1][y] % 4 == 3 && record[step])
		{
			map[x - 1][y] -= 3;
			map[x][y] += 3;
		}
		x++;
	}
	if (count[step] == 4)
	{
		map[x - 1][y]++;
		if (map[x + 1][y] % 4 == 3 && record[step])
		{
			map[x + 1][y] -= 3;
			map[x][y] += 3;
		}
		x--;
	}
	step--;
	stepcount++;
	show_map();
}

void show_map()
{
	setaspectratio(1, 0.5);
	loadimage(0, _T("res\\bk.png"));
	setaspectratio(0.25, 0.25);
	BeginBatchDraw();

	for (j = 0; j < 20; j++)
	{
		for (i = 0; i < 20; i++)
		{
			switch (map[i][j])
			{
				//	case 0:putimage(i*zoom, j*zoom, &smallbk); break;
			case 1:putimage(i * zoom, j * zoom, &man1, SRCAND); putimage(i * zoom, j * zoom, &man, SRCPAINT); break;    //人
			case 2:putimage(i * zoom, j * zoom, &wall); break;															//墙
			case 3:putimage(i * zoom, j * zoom, &box1, SRCAND); putimage(i * zoom, j * zoom, &box, SRCPAINT); break; //空箱子

			case 4:putimage(i * zoom, j * zoom, &star1, SRCAND); putimage(i * zoom, j * zoom, &star, SRCPAINT); break; //星

			case 5:putimage(i * zoom, j * zoom, &manstar1, SRCAND); putimage(i * zoom, j * zoom, &manstar, SRCPAINT); break; //人 星        
			case 7:putimage(i * zoom, j * zoom, &box1, SRCAND); putimage(i * zoom, j * zoom, &boxed, SRCPAINT); break;  //实箱子


			}
		}
	}
	FlushBatchDraw();
}


void system_init()
{

	loadimage(&bgmon, _T("res\\bgmon.png"));
	loadimage(&bgmoff, _T("res\\bgmoff.png"));

	loadimage(&imgreset, _T("res\\reset.png"));
	loadimage(&imgundo, _T("res\\undo.png"));



	loadimage(&smallbk, _T("res\\smallbk.png"));
	loadimage(&bk, _T("res\\bk.png"));
	loadimage(&wall, _T("res\\wall.png"));

	loadimage(&box, _T("res\\box.png"));
	loadimage(&boxed, _T("res\\boxed.png"));
	loadimage(&box1, _T("res\\box1.png"));

	loadimage(&man, _T("res\\man.png"));
	loadimage(&man1, _T("res\\man1.png"));

	loadimage(&manstar, _T("res\\manstar.png"));
	loadimage(&manstar1, _T("res\\manstar1.png"));

	loadimage(&star, _T("res\\star.png"));
	loadimage(&star1, _T("res\\star1.png"));
	int w, h;

	w = bk.getwidth();					//将图片的宽高赋值给变量 w、h
	h = bk.getheight();
	initgraph(w/5*4, h / 2);

	setaspectratio(0.8, 0.5);
	loadimage(0, _T("res\\bk.png"));

	setbkmode(TRANSPARENT);
}


void up()
{
	map[x][y - 1]++;
	if (w1 % 4 == 3)
	{
		map[x][y - 1] -= 3;
		map[x][y - 2] += 3;
	}
}

void down()
{
	map[x][y + 1]++;
	if (w1 % 4 == 3)
	{
		map[x][y + 1] -= 3;
		map[x][y + 2] += 3;
	}
}

void left()
{
	map[x - 1][y]++;
	if (w1 % 4 == 3)
	{
		map[x - 1][y] -= 3;
		map[x - 2][y] += 3;
	}
}

void right()
{
	map[x + 1][y]++;
	if (w1 % 4 == 3)
	{
		map[x + 1][y] -= 3;
		map[x + 2][y] += 3;
	}
}


void level_init(int level)
{
	switch (level)
	{
	case 1: map_init(map_1); break;
	case 2: map_init(map_2); break;
	case 3: map_init(map_3); break;
	case 4: map_init(map_4); break;
	case 5: map_init(map_5); break;
	case 6: map_init(map_6); break;
	default:
		system("pause>nul");
		exit(0);
	}
}


void map_init(int a[20][20])
{
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			map[i][j] = a[j][i];
			if (map[i][j] == 1)
			{
				x = i; y = j;
			}
		}
	}
}


void success()
{
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (map[i][j] == 3) goto end;
		}
	}
	system("pause>nul");
	level++;
	stepcount = 0;
	level_init(level);
end:i = 0;
}