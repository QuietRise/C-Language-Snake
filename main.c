#include "snake.h"

//主函数
int main(){

    // 隐藏光标
    HideCursor();
    // 初始化随机数种子
    srand((unsigned int)time(NULL));
    // 当前得分
    int score = 0;
    // 首次生成地图
    unit map[width][length] = {0};
    CreateMap( map, &score);
    // 生成蛇头
    LinkList snake = (LinkList)malloc(sizeof(Lnode));
    snake->x = length / 2;
    snake->y = width / 2;
    snake->next = NULL;
    // 设置虚拟头节点
    LinkList dummy = (LinkList)malloc(sizeof(Lnode));
    dummy->next = snake;
    // 默认蛇头朝右移动
    char dir = RIGHT;
    // 默认生成果子
    CreateFruit(map); 
    CreateMap( map, &score);
    while( 1 ){
        // 获取新方向
        dir = UpdateDirection(dir);
        // 根据方向移动蛇链表
        MoveSnake( dummy, map, dir);
        // snake 指针指向最新的头
        snake = dummy->next;

// **********失败检测**********
{       
        // 判断是否撞墙越界
         if (  0 > snake->x || snake->x >= length || 0 > snake->y || snake->y >= width){
            break;
        }
        // 判断是否撞自己身体
        if ( map[snake->y][snake->x] == 1 ){
            break;
        }
}
        //判断是否吃到果实和返回当前分数
        IfEatFruit(map, dummy, &score);
        // 将全地图除果实外的格子刷新为空
        RefreshMap(map);
        // 遍历蛇链表将全部坐标在二维数组中设为1
        Lnode *p = snake;
        while ( p){
            map[p->y][p->x] = 1;
            p = p->next;
        }
        // 生成地图
        CreateMap( map, &score);
        Sleep(1000 / speed);
    }
    // 失败后全部格子刷新为空
    for ( int i = 0; i < width; i++){
        for ( int j = 0; j < length; j++){
            map[i][j] = 0;
        }
    }
    CreateMap( map, &score);

// **********失败提示**********
{    // 失败提示存入数组
    char msg[] = "You are lose!";
    int row = width / 2 - 1; 
    int start_col = (length - sizeof(msg) + 1) / 2 ;
    // 防止数组越界
    for (int i = 0; i < sizeof(msg) - 1; i++) {
        if (start_col + i >= 0 && start_col + i < length) {
            map[row][start_col + i] = msg[i];
        }
    }
    // 生成失败提示
    CreateMap( map, &score);
    getchar();
}

    return 0;
}

