#include "snake.h"

// 设置光标位置函数
void gotoxy(int x, int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

// 隐藏光标函数
void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 生成地图函数
void CreateMap( unit map[width][length], int *score){

    //每次画图前，把光标移回左上角
    gotoxy(0, 0);
    //首排######
    for ( int i = 0; i < length + 2; i++){
        printf("#");
    }
    printf("\n");
    //主要地图
    for ( int i = 0; i < width; i++){
        printf("#");
        for ( int j = 0; j < length; j++){
            if ( map[i][j] == 0){
                printf(" ");
            }
            else if ( map[i][j] == 1){
                printf("o");
            }
            else if ( map[i][j] == 2){
                printf("*");
            }
            else {
                printf("%c", map[i][j]); 
            }
        }
        printf("#");
        printf("\n");
    }
    //尾排######
    for ( int i = 0; i < length + 2; i++){
        printf("#");
    }
    printf("\n");
    printf("Your current score: %d\n", *score);
}

// 将除果实外的地图刷新为空函数
void RefreshMap( unit map[width][length]){
    for ( int i = 0; i < width; i++){
        for ( int j = 0; j < length; j++){
            if ( map[i][j] != 2){
                map[i][j] = 0;
            }
        }
    }
}

// 读取按键并更新方向函数
char UpdateDirection(char old_dir){

    // 如果没按键直接返回原方向
    if (!_kbhit()) {
        return old_dir;
    }
    // 读取按键
    unsigned char input = _getch();
    // 通过方向键特殊标记判断是不是方向键
    if (input == 224 || input == 0) {
        //立刻再读一次方向键
        input = _getch();
    }
    // 判断输入和当前蛇头运动方向是否相反
    if (input == LEFT && old_dir != RIGHT) return LEFT;
    if (input == RIGHT && old_dir != LEFT) return RIGHT;
    if (input == UP && old_dir != DOWN) return UP;
    if (input == DOWN && old_dir != UP) return DOWN;

    // 如果按了其他键(比如空格)，或者试图掉头，就保持原方向不变
    return old_dir;
}

// 根据方向移动蛇函数
void MoveSnake(LinkList dummy, unit map[width][length], char dir){
    Lnode *newbody = (LinkList)malloc(sizeof(Lnode));
    newbody->next = NULL;
    switch (dir) {
        case LEFT:  newbody->x = dummy->next->x - 1;
                    newbody->y = dummy->next->y; break; // 左
        case RIGHT: newbody->x = dummy->next->x + 1; 
                    newbody->y = dummy->next->y; break; // 右
        case UP:    newbody->y = dummy->next->y - 1; 
                    newbody->x = dummy->next->x; break; // 上
        case DOWN:  newbody->y = dummy->next->y + 1; 
                    newbody->x = dummy->next->x; break; // 下
    }
    //新结点插入到首元位置
    newbody->next = dummy->next;
    dummy->next = newbody;
}

// 随机生成果子函数
void CreateFruit(unit map[width][length]){
    int x, y;
    while (1) {
        // 随机生成果子坐标
        x = rand() % length;
        y = rand() % width;
        // 检查位置是否为空
        if (map[y][x] == 0) {
            map[y][x] = 2;
            break;
        }
    }
}

//判断是否吃到果实函数
void IfEatFruit(unit map[width][length], LinkList dummy, int *score){
    // 吃到了果子
    if ( map[dummy->next->y][dummy->next->x] == 2 ){
        CreateFruit(map);
        (*score)++;
    }
    // 没吃到果子
    else {
        LinkList p = dummy;
        while ( p->next->next){
            p = p->next;
        }
        map[p->next->y][p->next->x] = 0; 
        free(p->next);
        p->next = NULL;
    }
}
