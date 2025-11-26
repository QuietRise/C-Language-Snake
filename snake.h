#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>    // 使用Sleep函数
#include <conio.h>  // 用于检测键盘输入
// 地图左右长度
#define length 40
// 地图上下宽度
#define width 20
// 蛇每秒移动格子数
#define speed 5
// Windows方向键键值
#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77

typedef char unit;

typedef struct snake{
    int x;
    int y;
    struct snake *next;
}Lnode, *LinkList;

// 设置光标位置函数
void gotoxy(int x, int y);
// 隐藏光标函数
void HideCursor();
// 生成地图函数
void CreateMap( unit map[width][length], int *score);
// 将除果实外的地图刷新为空函数
void RefreshMap( unit map[width][length]);
// 读取按键并更新方向函数
char UpdateDirection(char old_dir);
// 根据方向移动蛇函数
void MoveSnake(LinkList dummy, unit map[width][length], char dir);
// 随机生成果子函数
void CreateFruit(unit map[width][length]);
//判断是否吃到果实函数
void IfEatFruit(unit map[width][length], LinkList dummy, int *score);

#endif