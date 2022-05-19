#include<iostream>
#include "TimeTable.h"
#include "Graph.h"
#include "Timer.h"

using namespace std;

class Student {

public:

	Student();
	
	
	TimeTable* get_timetable();

	/*
	向系统输入课程名称、上课时间或者上课地点，系统自动进行路径规划：
	1. 向系统输入课程名称、上课时间或者上课地点
	2. 课程名称/上课时间 --> 上课地点
	   2.1 调用TimeTable中的 name_to_place() / time_to_place()
	3. 输入自己当前所在的位置(建筑物名)、导航策略
	4. 判断当前位置和上课地点是否处于两个不同的校区
	   4.1 若都在沙河
	   4.2 若都在本部
	   4.3 若不在同一校区，分为三段：
		   1.当前位置到学校门口
		   2.一个校区到另一个校区(默认选择时间最短的通行车，若时间相同，则选择校车)
		   3.学校门口到上课地点
	   以上步骤调用相应的 print_line()
	5. 系统自动进行路径规划
	*/
	void start_navigation();

private:

	int speed_on_foot;    //理想步行速度
	int speed_by_bike;    //理想骑车速度

	TimeTable* table;

public:
	static Graph s_graph;        //沙河校区的图
	static Graph b_graph;        //本部校区的图  
};