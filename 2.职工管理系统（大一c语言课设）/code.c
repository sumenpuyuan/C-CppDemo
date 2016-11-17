#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<windows.h>
#include<conio.h>
struct workers
{
        char cname[20];//职工工号
        char name[20];//职工姓名
        int money[5];//职工的各种工资,岗位工资，薪级工资，职务津贴 应发工资 实发工资
        int spend[4];//职工的各种花费 工会费 保险费 水电费
};
typedef struct node
{
        struct workers data;//数据区域
        struct node *pnext;//存储下一个节点地址
}Node;//建立链表
void Shownoly(Node *head);
void Showall(Node *head);
void Showallx(Node *head);
Node * Add(Node *head);
void Query(Node *head);
Node * Delete(Node *head);
void Change(Node *head);
void Save(Node *head);
Node * load(Node *head);
void menu();
void Shownoly(Node *head)//展示指定的员工信息
{
        int ii;
        Node *p = head;
        printf("%-15s%-15s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "职工工号", "职工姓名", "岗位工资", "薪级工资", "职务津贴", "应发工资", "实发工资", "工会费", "保险费", "水电费");
        printf("%-15s%-15s", p->data.cname, p->data.name);
        for (ii = 0; ii < 5; ii++)
        {
                printf("%-10d", p->data.money[ii]);
        }
        for (ii = 0; ii < 3; ii++)
                printf("%-10d", p->data.spend[ii]);
        printf("\n");
}
void Showall(Node *head)//仅仅展示所有员工信息
{
        Node *p = head;
        int ii;
        if (!p)
        {
                system("color F4");
                printf("抱歉，没有记录可以查询\n");
                return;
        }
        puts("所有的职工信息为");
        printf("%-15s%-15s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "职工工号", "职工姓名", "岗位工资", "薪级工资", "职务津贴", "应发工资", "实发工资", "工会费", "保险费", "水电费");
        while (p)
        {
                printf("%-15s%-15s", p->data.cname, p->data.name);
                for (ii = 0; ii < 5; ii++)
                {
                        printf("%-10d", p->data.money[ii]);
                }
                for (ii = 0; ii < 3; ii++)
                        printf("%-10d", p->data.spend[ii]);
                p = p->pnext;
                printf("\n");
        }
        return;

}
void Showallx(Node *head)//在展示所有员工信息的基础上加入选择按钮功能
{

        int num;
        system("cls");
        Showall(head);
        printf("\n返回主菜单请按0,继续浏览请勿做任何操作\n");
        scanf("%d", &num);
        if (num == 0);
        else
        {
                system("color F4");
                printf("您输入的序号是非法的，三秒后系统自动跳转到主界面\n");
                Sleep(3000);
                return;
        }
}
Node * Add(Node *head)//添加职工信息函数
{

        Node *p, *tail = head;
        int ii, num, flag = 0;
        system("cls");
        //s = worker->pnext;//使s成为第一个有用的节点
        //        while (tail!= NULL)
        //                tail = tail->pnext;//r就是最后一个节点
        //if(!head)
        while (1)
        {

                p = (Node *)malloc(sizeof(Node));//申请空间
                p->pnext = NULL;
                puts("请输入职工工号");
                scanf("%s", &p->data.cname);
                puts("请输入职工姓名");
                scanf("%s", &p->data.name);
                p->data.money[3] = 0;
                p->data.money[4] = 0;
                p->data.spend[3] = 0;
                puts("请按照岗位工资 薪级工资 职务津贴的顺序输入工资\n应发工资和实发工资程序会自动求出");
                for (ii = 0; ii < 3; ii++)
                {
                        scanf("%d", &p->data.money[ii]);
                        p->data.money[3] += p->data.money[ii];//求应发工资
                }
                puts("请按照工会费 保险费 水电费的顺序输入职工费用");
                for (ii = 0; ii < 3; ii++)
                {
                        scanf("%d", &p->data.spend[ii]);
                        p->data.spend[3] += p->data.spend[ii];//求所有费用之和
                }
                p->data.money[4] = p->data.money[3] - p->data.spend[3];//求实发工资
                puts("您新建的职工信息为");
                printf("%-15s%-15s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "职工工号", "职工姓名", "岗位工资", "薪级工资", "职务津贴", "应发工资", "实发工资", "工会费", "保险费", "水电费");
                printf("%-15s%-15s", p->data.cname, p->data.name);
                for (ii = 0; ii < 5; ii++)
                {
                        printf("%-10d", p->data.money[ii]);
                }
                for (ii = 0; ii < 3; ii++)
                        printf("%-10d", p->data.spend[ii]);
                if (head == NULL)
                        head = tail = p;
                else {

                        tail->pnext = p;//将p与先前的链表连起来构成一条新链表
                        tail = p;
                }//将r又重设为新链表的最后一个有用节点
                printf("\n");
                Save(p);//询问是否保存为文件
                printf("\n返回主菜单请按0，继续新建职工信息则按1\n");
                scanf("%d", &num);
                if (num == 0)
                        break;
                else if (num == 1);
                else
                {
                        system("color F4");
                        printf("您输入的序号是非法的，三秒后系统自动跳转到主界面\n");
                        Sleep(3000);
                        return head;
                }
        }
        return head;
}
void Query(Node *head)//查询职工信息函数
{

        Node *p = head;
        int num, num2, iflag = 0;
        char cname[20];
        system("cls");
        //        p = worker->pnext;
        if (!p)//判断链表是否为空
        {
                system("color F4");
                puts("系统提示：没有职工信息可以查询\n系统三秒之后，将返回主菜单");
                Sleep(3000);
                return;
        }
        puts("\t\t\t\t\t****************************\n");
        puts("\t\t\t\t\t\t1 按职工工号查询\n");
        puts("\t\t\t\t\t\t2 按职工姓名查询\n");
        puts("\t\t\t\t\t\t0 返回主菜单\n");
        puts("\t\t\t\t\t****************************");
        printf("\t\t\t\t\t");
        scanf("%d", &num);
        if (num == 1)
        {
                while (1)
                {
                        puts("请输入要查找的职工工号");
                        scanf("%s", &cname);
                        while (p)
                        {
                                if (strcmp(p->data.cname, cname) == 0)
                                {
                                        puts("找到了,该职工的信息为");
                                        Shownoly(p);//展示员工信息
                                        puts("继续查找请按1 返回上一级菜单请按2 返回主菜单请按0");
                                        scanf("%d", &num2);
                                        if (num2 == 1)
                                                break;
                                        else if (num2 == 2)
                                        {
                                                Query(head);
                                                return;
                                        }
                                        else if (num2 == 0)
                                                return;
                                        else
                                        {
                                                system("color F4");
                                                puts("您输入了非法的序号，三秒后系统自动返回到主界面");
                                                Sleep(3000);
                                                return;
                                        }
                                }
                                else
                                        p = p->pnext;
                        }
                        if (p == NULL)
                        {
                                puts("没有找到该职工");
                                puts("继续查找请按1 返回上一级菜单请按2 返回主菜单请按0");
                                scanf("%d", &num2);
                                if (num2 == 1);
                                else if (num2 == 2)
                                {
                                        Query(head);
                                        return;
                                }
                                else if (num2 == 0)
                                        return;
                                else
                                {
                                        system("color F4");
                                        puts("您输入了非法的序号，系统自动跳转到主界面");
                                        Sleep(3000);
                                        return;
                                }
                        }
                }
        }
        else if (num == 2)//按照职工姓名查询
        {
                while (1)
                {
                        puts("请输入你要查询的职工姓名");
                        scanf("%s", &cname);
                        while (p)
                        {
                                if (strcmp(p->data.name, cname) == 0)
                                {
                                        puts("找到了，该职工的信息为");
                                        Shownoly(p);
                                        puts("继续查找请按1 返回上一级菜单请按2 返回主菜单请按0");
                                        scanf("%d", &num2);
                                        if (num2 == 1)
                                                break;
                                        else if (num2 == 2)
                                        {
                                                Query(head);
                                                return;
                                        }
                                        else if (num2 == 0)
                                                return;
                                        else
                                        {
                                                system("color F4");
                                                puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                                                Sleep(3000);
                                                return;
                                        }
                                }
                                p = p->pnext;
                        }
                        if (p == NULL)
                        {
                                puts("没有找到该职工");
                                puts("继续查找请按1 返回上一级菜单请按2 返回主菜单请按0");
                                scanf("%d", &num2);
                                if (num2 == 1);
                                else if (num2 == 2)
                                {
                                        Query(head);
                                        return;
                                }
                                else if (num2 == 0)
                                        return;
                                else
                                {
                                        system("color F4");
                                        puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                                        Sleep(3000);
                                        return;
                                }
                        }
                }
        }
        else if (num == 0)
                return;
        else {
                system("color F4");
                puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                Sleep(3000);
                return;
        }
}
Node * Delete(Node *head)//删除职工信息函数
{

        Node *p = head, *r, *s;
        char c;
        int num2;
        char cname[20];
        system("cls");
        if (!p)
        {
                system("color F4");
                puts("没有资料可以删除\n系统三秒后返回到主菜单界面");
                Sleep(3000);
                return head;
        }
        Showall(head);
        puts("请输入要删除的职工工号");
        scanf("%s", cname);
        //p = worker->pnext;
        while (p)
        {
                if (strcmp(p->data.cname, cname) == 0)
                {
                        puts("找到了,该员工的信息为");
                        Shownoly(p);
                        puts("您确定要删除该员工吗？\n确认删除请输入y，不删除请输入n");
                        fflush(stdin);
                        scanf("%c", &c);
                        if (c == 'y' || c == 'Y')
                        {
                                if (p == head)
                                {
                                        r = head;
                                        head = head->pnext;
                                        free(r);
                                }
                                else
                                {
                                        r = head;
                                        while (r->pnext != p)
                                                r = r->pnext;//让r指向p的前驱结点
                                        s = r->pnext;
                                        r->pnext = r->pnext->pnext;
                                        free(s);
                                }
                                puts("已经成功删除");
                        }
                        else if (c == 'n' || c == 'N');
                        else
                        {
                                system("color F4");
                                puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                                Sleep(3000);
                                return head;
                        }
                        puts("继续删除请按1  返回主菜单请按0");
                        scanf("%d", &num2);
                        if (num2 == 1)
                        {
                                Delete(head);
                                return head;
                        }
                        else if (num2 == 0)
                                return head;
                        else
                        {
                                system("color F4");
                                puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                                Sleep(3000);
                                return head;
                        }

                }
                p = p->pnext;
        }
        if (p == NULL)
        {
                puts("没有这名职工");
                puts("继续删除请按1  返回主菜单请按0");
                scanf("%d", &num2);
                if (num2 == 1)
                {
                        Delete(head);
                        return head;
                }
                else if (num2 == 0)
                        return head;
                else
                {
                        system("color F4");
                        puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                        Sleep(3000);
                        return head;
                }
        }
        return head;
}
void Change(Node *head)//修改职工信息函数
{

        Node *p = head;
        int num2, ii;
        char cname[20]//存储要修改的职工工号
                , c;
        system("cls");
        if (!p)
        {
                system("color F4");
                puts("提示：没有资料可以查询.三秒后系统自动返回主界面");
                Sleep(3000);
                return;
        }
        Showall(p);//展示所有职工信息
        puts("请输入要修改的职工工号");
        scanf("%s", &cname);
        while (p)
        {
                if (strcmp(p->data.cname, cname) == 0);
                {
                        puts("找到了,该职工信息为");
                        Shownoly(p);
                        break;
                }
                p = p->pnext;
        }
        if (!p)
        {
                puts("没有这名职工");
                puts("继续修改请按1  返回主菜单请按0");
                scanf("%d", &num2);
                if (num2 == 1)
                {
                        Change(head);
                        return;
                }
                else if (num2 == 0)
                        return;
                else
                {
                        puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                        Sleep(3000);
                        return;
                }
        }
        fflush(stdin);
        puts("确认修改请按y，不修改请按n");
        scanf("%c", &c);
        if (c == 'Y' || c == 'y')
        {
                printf("请输入职工工号,原来是%s\n", p->data.cname);
                scanf("%s", &p->data.cname);
                printf("请输入职工姓名,原来是%s\n", p->data.name);
                scanf("%s", &p->data.name);
                p->data.money[3] = 0;
                p->data.money[4] = 0;
                p->data.spend[3] = 0;
                puts("请按照岗位工资 薪级工资 职务津贴的顺序输入工资\n应发工资和实发工资程序会自动求出");
                puts("原来的数据为");
                for (ii = 0; ii < 3; ii++)
                {
                        printf("%-5d", p->data.money[ii]);
                }
                printf("\n");
                for (ii = 0; ii < 3; ii++)
                {
                        scanf("%d", &p->data.money[ii]);
                        p->data.money[3] += p->data.money[ii];//求应发工资
                }
                puts("请按照工会费 水电费的顺序输入职工费用");
                puts("原来数据为");
                for (ii = 0; ii < 3; ii++)
                {
                        printf("%-5d", p->data.spend[ii]);
                }
                printf("\n");
                for (ii = 0; ii < 3; ii++)
                {
                        scanf("%d", &p->data.spend[ii]);
                        p->data.spend[3] += p->data.spend[ii];//求所有费用之和
                }
                p->data.money[4] = p->data.money[3] - p->data.spend[3];
                puts("修改后的的职工信息为");
                printf("%-15s%-15s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "职工工号", "职工姓名", "岗位工资", "薪级工资", "职务津贴", "应发工资", "实发工资", "工会费", "保险费", "水电费");
                printf("%-15s%-15s", p->data.cname, p->data.name);
                for (ii = 0; ii < 5; ii++)
                {
                        printf("%-10d", p->data.money[ii]);
                }
                for (ii = 0; ii < 3; ii++)
                        printf("%-10d", p->data.spend[ii]);
                printf("\n");
                puts("继续修改请按1  返回主菜单请按0");
                scanf("%d", &num2);
                if (num2 == 1)
                {
                        Change(head);
                        return;
                }
                else if (num2 == 0)
                        return;
                else
                {
                        puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                        Sleep(3000);
                        return;
                }
        }
        else if (c == 'n' || c == 'N')
        {
                puts("继续修改请按1  返回主菜单请按0");
                scanf("%d", &num2);
                if (num2 == 1)
                {
                        Change(head);
                        return;
                }
                else if (num2 == 0)
                        return;
                else
                {
                        puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                        Sleep(3000);
                        return;
                }
        }
        else {
                puts("您输入了非法的序号，三秒后系统自动跳转到主界面");
                Sleep(3000);
                return;
        }
}
void Save(Node *head)//保存职工信息为文件
{

        int n;
        Node *p,*q;
        FILE *fp;
        q=head;
        while(q->pnext)
        {
                q=q->pnext;//让q指向最后一个节点
        }
        puts("需要保存到文件吗?（1—保存，0—不保存）");
        scanf("%d", &n);
        if (n == 1)
        {
        p = q;
        if ((fp = fopen("职工管理系统.txt", "a")) == NULL)
        {
        system("color 04");
        puts("打开文件失败");
        puts("三秒后系统自动跳转到主界面");
        Sleep(3000);
        return;
        }
        printf("文件打开成功，正在保存文件>>>>>>>>>>>>>\n");
        while (p)
        {
        fprintf(fp, "%s %s %d %d %d %d %d %d %d %d %d ", &p->data.cname, &p->data.name, p->data.money[0],
        p->data.money[1], p->data.money[2], p->data.money[3], p->data.money[4], p->data.spend[0],
        p->data.spend[1], p->data.spend[2], p->data.spend[3]);//格式化输出函数
        p = p->pnext;                }
        fclose(fp);//关闭文件
        puts("文件保存成功！\n");
        return;

}
}
Node * load(Node *head)
{
        Node *p=head,*q;
        FILE *fp;
        int num;
        if ((fp = fopen("职工管理系统.txt", "r")) == NULL)
        {
                printf("不能打开文件，系统三秒后返回主菜单\n");
                Sleep(3000);
                return head;
        }
        else
        {
                printf("打开文件成功，正在载入文件\n");
        }
        while(p)
                p=p->pnext;//让p指向最后一个节点
        num = 0;
        while (!feof(fp))
        {
                q = (Node *)malloc(sizeof(Node));
                q->pnext = NULL;
                fscanf(fp, "%s %s %d %d %d %d %d %d %d %d %d ", q->data.cname, q->data.name, &q->data.money[0],
                        &q->data.money[1], &q->data.money[2], &q->data.money[3], &q->data.money[4], &q->data.spend[0],
                        &q->data.spend[1], &q->data.spend[2], &q->data.spend[3]);//格式化输入函数
                if (p == NULL)
                {
                        head = p = q;
                }
                else
                {
                        p->pnext = q;
                        //q->pnext = NULL;//使q成为最后一个节点
                        p = q;
                }
                num++;
        }
        fclose(fp);
        printf("文件里有%d个内容\n", num);
        puts("文件载入成功，三秒后返回主界面");
        Sleep(3000);
        return head;
}
void Exit()//退出函数
{
        system("cls");
        puts("\n\t\t\t\t\t\t感谢您的使用，下次再见！");
        Sleep(3000);
        exit(0);
}
void paixu(Node *head)
{
        Node *p, *q, temp;
        puts("排序前为");
        Showall(head);
        for (p = head; p; p = p->pnext)
        {
                for (q = head; q; q = q->pnext)
                {
                        if (q->data.money[3]<p->data.money[3])
                        {
                                temp.data = q->data;//交换
                                q->data = p->data;
                                p->data = temp.data;
                        }
                }
        }
        puts("排序后为");
        Showall(head);
        _getch();
}
void menu()//显示菜单函数
{
        int num;
        Node *head = NULL, *tail = NULL;
        while (1)
        {
                system("cls");
                system("color 0A");//调整字体颜色
                //        SYSTEMTIME sys;
                //GetLocalTime( &sys );
                // printf( "\t\t\t\t\t%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek);
                printf("\n\n");
                puts("\t\t\t\t\t********************************\n");
                printf("\t\t\t\t\t\t<<<职工工资管理程序>>>\n\n");
                puts("\t\t\t\t\t\t1 新建职工信息\n");
                puts("\t\t\t\t\t\t2 查询职工信息\n");
                puts("\t\t\t\t\t\t3 删除职工信息\n");
                puts("\t\t\t\t\t\t4 修改职工信息\n");
                puts("\t\t\t\t\t\t5 浏览所有职工信息（兼归总实发工资）\n");
                puts("\t\t\t\t\t\t6 载入文件中的职工信息\n");
                puts("\t\t\t\t\t\t7 按照应发工资排序\n");
                puts("\t\t\t\t\t\t0 退出这个程序\n");
                puts("\t\t\t\t\t********************************\n");
                printf("\t\t\t\t\t");
                scanf("%d", &num);
                switch (num)
                {
                case 1:head = Add(head);  break;
                case 2:Query(head); break;
                case 3:head = Delete(head); break;
                case 4:Change(head); break;
                case 5:Showallx(head); break;
                case 6:head=load(head); break;
                case 7:paixu(head); break;
                case 0: Exit(); break;
                default:printf("您输入的序号是非法的，请重新输入\n");_getch(); menu();
                        break;
                }
        }
}
int main()//主函数
{
        system("mode con: cols=125 lines=25");//调整窗口大小
        menu();
        system("title 吕雪杰的职工信息管理系统程序");
        system("pause");
}


