//采用复合计算
//v2.0 将推出自定义地图    撤销功能
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

void color(int a);
void Cursor(int mode);
void gotoxy(int x,int y);

void system_init();
void map_init();
void level_init(int level);
void show_map();
void success();
void undo();

void move();
void up();
void down();
void left();
void right();


int i,j,x,y,w1,w2,path,level=1,step=0,stepcount=0;
int map[20][20],count[1000],box[1000];

int map_1[20][20]={
{0,0,2,2,2,0,0,0},
{0,0,2,4,2,0,0,0},
{0,0,2,0,2,2,2,2},
{2,2,2,3,3,0,4,2},
{2,4,0,3,1,2,2,2},
{2,2,2,2,3,2,0,0},
{0,0,0,2,4,2,0,0},
{0,0,0,2,2,2,0,0},
};
int map_2[20][20]={
{2,2,2,2,2,0,0,0,0},
{2,1,0,0,2,0,0,0,0},
{2,0,3,3,2,0,2,2,2},
{2,0,3,0,2,0,2,4,2},
{2,2,2,0,2,2,2,4,2},
{0,2,2,0,0,0,0,4,2},
{0,2,0,0,0,2,0,0,2},
{0,2,0,0,0,2,2,2,2},
{0,2,2,2,2,2,0,0,0},
};

int map_3[20][20]={
{0,2,2,2,2,2,2,2,0,0},
{0,2,0,0,0,0,0,2,2,2},
{2,2,3,2,2,2,0,0,0,2},
{2,0,1,0,3,0,0,3,0,2},
{2,0,4,4,2,0,3,0,2,2},
{2,2,4,4,2,0,0,0,2,0},
{0,2,2,2,2,2,2,2,2,0},
};

int map_4[20][20]={
{0,2,2,2,2,0},
{2,2,0,0,2,0},
{2,1,3,0,2,0},
{2,2,3,0,2,2},
{2,2,0,3,0,2},
{2,4,3,0,0,2},
{2,4,4,7,4,2},
{2,2,2,2,2,2},
};

int map_5[20][20]={
{2,2,2,2,2,2,2,0,0},
{2,0,0,0,0,0,2,0,0},
{2,0,3,3,3,2,2,0,0},
{2,0,0,2,4,4,2,2,2},
{2,2,0,0,4,4,3,0,2},
{0,2,0,1,0,0,0,0,2},
{0,2,2,2,2,2,2,2,2},
};

int map_6[20][20]={
{0,2,2,2,2,0,0,0},
{0,2,1,0,2,2,2,0},
{0,2,0,3,0,0,2,0},
{2,2,2,0,2,0,2,2},
{2,4,2,0,2,0,0,2},
{2,4,3,0,0,2,0,2},
{2,4,0,0,0,3,0,2},
{2,2,2,2,2,2,2,2},
};

/*
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
*/

void main()
{  
    system_init();
    level_init(level);
    while(1)
    {
        move();
        show_map();
        success();
    }
}

void move()
{
    begin:
    w1=w2=2;
    path=0;
    switch((int)_getch())             
    {                    
        case 'w':case 'W':case 72: path=1;     break;
        case 'a':case 'A':case 75: path=2;     break;
        case 's':case 'S':case 80: path=3;     break;
        case 'd':case 'D':case 77: path=4;     break;
        case 'z':case 'Z':undo();  goto begin; break;
        default:goto begin;
    } 

    switch(path)
    {
        case 1:w1=map[x][y-1]; w2=map[x][y-2];break;
        case 2:w1=map[x-1][y]; w2=map[x-2][y];break;
        case 3:w1=map[x][y+1]; w2=map[x][y+2];break;
        case 4:w1=map[x+1][y]; w2=map[x+2][y];break;
    }

    if(w1==2||(w1%4==3&&(w2==2||w2%4==3))) 
        goto begin;


    map[x][y]--;

    switch(path)
    {
        case 1: up();    y--; break;
        case 3: down();  y++; break;
        case 2: left();  x--; break;
        case 4: right(); x++; break;
    }

    step++;
    stepcount++;
    count[step]=path;
    if(w1%4==3) box[step]=1;
}

void undo()
{
    if(!step) move();
    map[x][y]--;
    if(count[step]==1)
    {
        map[x][y+1]++;          
        if(map[x][y-1]%4==3&&box[step])
        {
             map[x][y-1]-=3;
             map[x][y]+=3;
        } 
        y++;       
    }
    if(count[step]==3)
    {
        map[x][y-1]++;          
        if(map[x][y+1]%4==3&&box[step])
        {
             map[x][y+1]-=3;
             map[x][y]+=3;
        } 
        y--;       
    }
    if(count[step]==2)
    {
        map[x+1][y]++;          
        if(map[x-1][y]%4==3&&box[step])
        {
             map[x-1][y]-=3;
             map[x][y]+=3;
        } 
        x++;       
    }
    if(count[step]==4)
    {
        map[x-1][y]++;          
        if(map[x+1][y]%4==3&&box[step])
        {
             map[x+1][y]-=3;
             map[x][y]+=3;
        } 
        x--;       
    }        
    step--;   
    stepcount++;
    show_map();
}

void up()
{
    map[x][y-1]++;
    if(w1%4==3)  
    {
        map[x][y-1]-=3;
        map[x][y-2]+=3;
    }
}

void down()
{
    map[x][y+1]++;
    if(w1%4==3)  
    {
        map[x][y+1]-=3;
        map[x][y+2]+=3;
    }
}

void left()
{
    map[x-1][y]++;
    if(w1%4==3)  
    {
        map[x-1][y]-=3;
        map[x-2][y]+=3;
    }  
}

void right()
{
    map[x+1][y]++;
    if(w1%4==3)  
    {
        map[x+1][y]-=3;
        map[x+2][y]+=3;
    }   
}

void show_map()
{
    SetConsoleOutputCP(936); 
    for(j=0;j<20;j++)
    {
        for(i=0;i<20;i++)
        {
            gotoxy(i,j);
            switch(map[i][j])
            {
                case 0:color(15);printf(" ");    break;                //空白
                case 1:color(1); printf("＊");   break;                //人
                case 2:color(2); printf("█");    break;                //墙
                case 3:color(1); printf("■");    break;                //空箱子
                case 4:color(5); printf("★");   break;               
                case 5:color(5); printf("＊");   break;                 //人 星
                case 7:color(5); printf("■");    break;
            }
        }
    }
    color(2);
    gotoxy(20,1);
    printf("Level %d",level);
    gotoxy(20,3);
    printf("Step  %d",stepcount);
    gotoxy(20,5);
    printf("undo  z");
}


void success()
{
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            if(map[i][j]==3) goto end;
        }
    }
    gotoxy(20,7);
    color(6);
    printf("You win!!!\n");
    system("pause>nul");
    system("cls");
    level++;
    stepcount=0;
    level_init(level);
    end:i=0;
}

void level_init(int level)
{
    switch(level)
    {
        case 1: map_init(map_1); break;
        case 2: map_init(map_2); break;
        case 3: map_init(map_3); break;
        case 4: map_init(map_4); break;
        case 5: map_init(map_5); break;
        case 6: map_init(map_6); break;
        default: 
        printf("敬请期待！！！\n");
        system("pause>nul");
        exit(0);
    }
}

void system_init()
{
    system("title 推箱子 V2.1 by Haoyue");
    system("mode con lines=20 cols=60");
    system("color f2");
    Cursor(0);
}

void map_init(int a[20][20])
{
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            map[i][j]=a[j][i];
            if(map[i][j]==1)
            {
                x=i; y=j;
            }
        }     
    }
    show_map();
}

void color(int ForeColor)
{
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
    SetConsoleTextAttribute(handle,ForeColor+15*0x10);//设置颜色
}

void gotoxy(int x,int y)          //位置函数,光标移动到该点
{
	 COORD pos;
	 pos.X=2*x;
	 pos.Y=y;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Cursor(int mode)                       //mode=0 消除光标 
{ 
    CONSOLE_CURSOR_INFO cursor_info = {1, mode};  
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); 
} 



//void deverloper()
//{
//    gotoxy(22,0);
//    printf("                                            ");
//    gotoxy(22,0);
//    printf("x=%d y=%d w1=%d w2=%d",x,y,w1,w2);
//    
//    for(j=0;j<20;j++)
//    {
//        for(i=0;i<20;i++)
//        {
//            gotoxy(i+20,j+2);
//            if(map[i][j])
//             printf("%d",map[i][j]);
//        }
//    }
//}