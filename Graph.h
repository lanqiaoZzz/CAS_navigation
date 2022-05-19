#include "Building.h"
#include "Bus.h"

#define INF 100000000

typedef struct road{

    int length;
    double crowd_degree;        //拥挤度
    int can_bike;               //是否可以通行自行车：1可 0不可

    road() {

        length = -1;
        crowd_degree = -1;
        can_bike = -1;
    }
}road;

//无向图
class Graph {

public:
    
    Graph();
    ~Graph();

    road** get_graph();

    building* get_building_array();
    
    //初始化通行车信息
    static void init_bus(const char filename[]);

    /*
    初始化图
    filename[]: 用文件中的数据初始化图信息
    */
    void init_graph(const char filename[]);

    /*
    打印线路
    start_place: 起点(建筑物名)
    end_place: 终点
    type: 选择哪种策略(1/2/3)  
    return: 返回所需的时间(分钟)     
    */
    int print_line(char start_place[], char end_place[], int type, int speed_on_foot, int speed_by_bike);

    //测试用
    void output();

private:
    
    /*
    建筑物名字 --> 建筑物编号
    name[]: 建筑物的名字
    return: 该建筑物的编号
    */
    int name_to_index(char name[]);
    
    /*
    策略一: 最短距离策略
    start: 起点(建筑物编号)
    end: 终点
    return: 返回所需时间
    */
    int shortest_dis(int start, int end, int speed_on_foot);

    /*
    策略二: 最短时间策略(步行)
    start: 起点(建筑物编号)
    end: 终点
    speed_on_foot: 理想步行速度
    return: 返回所需时间
    */
    int shortest_time(int start, int end, int speed_on_foot);

    /*
    策略三: 交通工具的最短时间策略(可以是多种交通工具混合)
    start: 起点(建筑物编号)
    end: 终点
    speed_on_foot: 理想步行速度
    speed_by_bike: 理想骑行速度
    return: 返回所需时间
    */
    int shortest_time_by_vehicle(int start, int end, int speed_on_foot, int speed_by_bike);

    /*
    输出某两个建筑物间的线路
    描述方法: 向xxx(东南西北)走xxx米到达xxx(建筑物名)
    start: 起点(建筑物编号)
    end: 终点
    return: 两点之间的距离     
    */
    int output(int start, int end);
 
private:
    road** graph;                   //图的二维数组
    //int vertex_num;               //顶点数
    int edge_num;                   //边数
    int vertex_num;                 //建筑物数（顶点数）
    building* building_array;       //建筑物数组
    campus campus_name;             //校区

public:
    static Bus* bus_array;          //校区间的通行车（4辆车按照11 12 21 22的顺序依次存储）
};







