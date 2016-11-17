#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
void openwww(char *str);
void input();
void click();
int main()
{
        openwww("http://www.baidu.com");
        Sleep(5000);
        input();
        Sleep(5000);
        click();
        system("pause");
        return 0;
}
void openwww(char *str)
{
        ShellExecuteA(0, "open", str, 0, 0, 1);
}
void input()
{
        keybd_event('Y', 0, 0, 0);//按下
        keybd_event('Y', 0, 2, 0);//松开
        Sleep(50);
        keybd_event('A', 0, 0, 0);//按下
        keybd_event('A', 0, 2, 0);//松开
        Sleep(50);
        keybd_event('O', 0, 0, 0);//按下
        keybd_event('O', 0, 2, 0);//松开
        Sleep(500);
        keybd_event('2', 0, 0, 0);//松开
        keybd_event('2', 0, 2, 0);//松开
        Sleep(50);
        keybd_event(0X0D, 0, 0, 0);//按下
        keybd_event(0X0D, 0, 2, 0);//松开
}
void click()
{
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 380*65525/1920, 300*65525/1080,0,1);//鼠标定位函数，关于鼠标在屏幕上的位置，不同
 //不同的分辨率会有不同的表示方法，我的电脑是1902*1080的，关于位置，推荐一款软件，自动显示鼠标位置，下面给出附件。
        Sleep(500);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//鼠标点下
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//鼠标松开

}