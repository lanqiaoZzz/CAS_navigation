#include "Student.h"

//初始化
Graph Student::s_graph;
Graph Student::b_graph;

Student::Student()
{
    Graph::init_bus("bus.txt");
    s_graph.init_graph("沙河地图2.0.txt");
    b_graph.init_graph("本部地图1.0.txt");

    this->speed_on_foot = 75;
    this->speed_by_bike = 100;
}

TimeTable* Student::get_timetable() {

    return table;
}

void Student::start_navigation() {

    //1. 向系统输入课程名称、上课时间或者上课地点
    cout << "---开始查找目的地---" << endl;
    cout << "请选择您要输入的信息类型：" << endl;
    cout << "1.课程名称" << endl;
    cout << "2.上课时间" << endl;
    cout << "3.上课地点(s-xxx / b-xxx)" << endl;

    int type;
    cin >> type;

    cout << "请按照格式输入信息：" << endl;

    char str[30];
    cin >> str;

    char* dest;

    //2. 课程名称 / 上课时间-- > 上课地点
    if (type == 1) {

        dest = get_timetable()->name_to_place(str);
    }
    else if (type == 2) {

        dest = get_timetable()->time_to_place(str);
    }
    else dest = str;

    //未查找到
    if (dest == NULL) {

        cout << "未查找到目的地，已退出" << endl;
        return;
    }
    else {

        cout << "您将前往的目的地是：" << dest << endl;
    }

    //3. 输入自己当前所在的位置(建筑物名)、导航策略和当前时间(精确到分钟)
    cout << "请输入您当前所在的位置(s-xxx / b-xxx)：" << endl;

    char source[30];
    cin >> source;

    cout << "请输入您要选择的导航策略" << endl;
    cout << "1.最短距离" << endl;
    cout << "2.最短时间" << endl;
    cout << "3.交通工具的最短时间" << endl;
    cin >> type;

    cout << "即将开始导航(" << source << " -- " << dest << " 策略" << type << ")" << endl;
    cout << "------------------------" << endl;

    //4. 判断当前位置和上课地点是否处于两个不同的校区       
    
    //记录总共花费的时间
    int sum = 0;

    //4.1 若都在沙河
    if (dest[0] == 's' && source[0] == 's') {

        sum += s_graph.print_line(source, dest, type, speed_on_foot, speed_by_bike);
        if (sum == -1)
        {
            cout << "目的地或出发地不存在，已退出" << endl;
            return;
        }
    }
    //4.2 若都在本部
    else if (dest[0] == 'b' && source[0] == 'b') {

        sum += b_graph.print_line(source, dest, type, speed_on_foot, speed_by_bike);
        if (sum == -1)
        {
            cout << "目的地或出发地不存在，已退出" << endl;
            return;
        }
    }
    //4.3 若不在同一校区，分为三段(1.当前位置到学校门口 2.一个校区到另一个校区 3.学校门口到上课地点)
    else if(dest[0] == 's' && source[0] == 'b' || dest[0] == 'b' && source[0] == 's') 
    {

        char temp1[] = "s-西门";
        char temp2[] = "b-南门";

        struct time cur;
        cur.hour = Timer::curTime;
        cur.minute = 0;

        if (source[0] == 's') {
           
            sum += s_graph.print_line(source, temp1, type, speed_on_foot, speed_by_bike);
            if (sum == -1)
            {
                cout << "目的地或出发地不存在，已退出" << endl;
                return;
            }

            //按照实际情况，此时的minute不会超过60
            cur.minute = sum;
            int t1;

            //两校区间通行
            //默认选择花费时间最少的通行车，若时间相同，则选择校车
            if (Graph::bus_array[0].calculate_time(cur) <= Graph::bus_array[1].calculate_time(cur)) {

                t1 = Graph::bus_array[0].calculate_time(cur);
                sum += t1;
                cout << "推荐选择校车通行，";
            }
            else if (Graph::bus_array[0].calculate_time(cur) > Graph::bus_array[1].calculate_time(cur)) {

                t1 = Graph::bus_array[1].calculate_time(cur);
                sum += t1;
                cout << "推荐选择公交车通行，";
            }

            cout << "预计需" << t1 << "分钟可到达[b-南门]" << endl;
            
            int t = b_graph.print_line(temp2, dest, type, speed_on_foot, speed_by_bike);
            if (t == -1)
            {
                cout << "目的地或出发地不存在，已退出" << endl;
                return;
            }
            sum += t;
        }
        else {

            sum += b_graph.print_line(source, temp2, type, speed_on_foot, speed_by_bike);
            if (sum == -1)
            {
                cout << "目的地或出发地不存在，已退出" << endl;
                return;
            }

            cur.minute = sum;
            int t2;

            //两校区间通行
            //默认选择花费时间最少的通行车，若时间相同，则选择校车
            if (Graph::bus_array[2].calculate_time(cur) <= Graph::bus_array[3].calculate_time(cur)) {

                t2 = Graph::bus_array[2].calculate_time(cur);
                sum += t2;
                cout << "经计算，推荐选择校车通行，";
            }
            else if (Graph::bus_array[2].calculate_time(cur) > Graph::bus_array[3].calculate_time(cur)) {

                t2 = Graph::bus_array[3].calculate_time(cur);
                sum += t2;
                cout << "经计算，推荐选择公交车通行，";
            }

            cout << "预计需" << t2 << "分钟可到达[s-西门]" << endl;

            int t = s_graph.print_line(temp1, dest, type, speed_on_foot, speed_by_bike);
            if (t == -1)
            {
                cout << "目的地或出发地不存在，已退出" << endl;
                return;
            }
            sum += t;
        }
    }
    else
    {
        cout << "输入格式不正确，已退出" << endl;
        return;
    }

    cout << "预计全程需" << sum << "分钟可到达目的地" << endl;
    cout << "------------------------" << endl;
    cout << "导航结束" << endl;
}
