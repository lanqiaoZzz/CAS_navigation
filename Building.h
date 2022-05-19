enum campus{shahe, benbu};

//用图中的横纵坐标代表位置信息
typedef struct position{

    int x;
    int y;

}position;

typedef struct building{
    
    int index;                  //建筑物的编号（从1开始）
    char name[30];              //建筑物的名字：沙河-xxx / 本部-xxx
    position pos;               //建筑物的位置
    //campus campus_name;       //建筑物所在校区
}building;

// class building {

// public:
    
//     building();

//     building(int index, char name[], position pos);

//     ~building();

// private:
//     int index;      //建筑物的编号
//     char name[15];    //建筑物的名字
//     position pos;   //建筑物的位置
// };