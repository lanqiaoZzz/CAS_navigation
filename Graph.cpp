#include<fstream>
#include <iostream>
#include "Graph.h"
using namespace std;

//��ʼ��
Bus* Graph::bus_array = new Bus[4];

Graph::Graph() {

}

Graph::~Graph() {

}

road** Graph::get_graph() {

    return graph;
}

building* Graph::get_building_array() {

    return building_array;
}

void Graph::init_bus(const char filename[]) {

    ifstream fin;
    fin.open(filename, ios::in);

    if (!fin) cout << "can not open the file" << endl;
    else {

        int type1, type2, station, start_time, end_time, gap;
        for (int i = 0; i < 4; i++) {

            fin >> type1 >> type2 >> station >> start_time >> end_time >> gap;
            Graph::bus_array[i] = Bus(type1, type2, station, start_time, end_time, gap);
        }

        fin.close();
    }
}

void Graph::init_graph(const char filename[]) {

    ifstream fin;
    fin.open(filename, ios::in);

    if (!fin) cout << "can not open the file" << endl;
    else {

        char campus;
        fin >> campus;

        if (campus == 's') this->campus_name = shahe;
        else this->campus_name = benbu;

        //���ؽ����������Ϣ
        fin >> this->vertex_num;
        this->building_array = new building[vertex_num + 1];

        for (int i = 1; i <= vertex_num; i++) {

            building_array[i].index = i;

            fin >> building_array[i].name >> building_array[i].pos.x >> building_array[i].pos.y;
        }

        //����ͼ�����Ϣ
        this->graph = new road*[vertex_num + 1];
        for (int i = 1; i <= vertex_num; i++) {

            graph[i] = new road[vertex_num + 1];
        }

        fin >> this->edge_num;

        int x, y;
        for (int i = 0; i < edge_num; i++) {

            fin >> x >> y;

            fin >> graph[x][y].length >> graph[x][y].crowd_degree >> graph[x][y].can_bike;    

            graph[y][x] = graph[x][y];
        }

        fin.close();
    }
}

int Graph::shortest_time(int start, int end, int speed_on_foot)
{
    return 0;
}

void Graph::output() {

    for (int i = 0; i < 4; i++) {

        cout << Graph::bus_array[i].type1 << " " << Graph::bus_array[i].type2 << " "
            << Graph::bus_array[i].station << " " << Graph::bus_array[i].start_time << " "
            << Graph::bus_array[i].end_time << " " << Graph::bus_array[i].gap << endl;
    }

    cout << campus_name << endl << vertex_num << endl;

    for (int i = 1; i < vertex_num; i++) {

        cout << building_array[i].name << " " << building_array[i].pos.x << " " << building_array[i].pos.y << endl;
    }

    cout << edge_num << endl;

    for (int i = 1; i < vertex_num; i++) {

        for (int j = 1; j < vertex_num; j++) {

            cout << graph[i][j].length << " " << graph[i][j].crowd_degree << " " << graph[i][j].can_bike << endl;
        }
    }
}

int Graph::shortest_time_by_vehicle(int start, int end, int speed_on_foot, int speed_by_bike)
{
    return 0;
}

int Graph::name_to_index(char name[]) {

    char str[30];
    int j = 0;

    for (int i = 2; name[i] != '\0'; i++)
    {
        str[j++] = name[i];
    }
    str[j] = '\0';
        
    for (int i = 1; i <= this->vertex_num; i++) {

        if (strcmp(this->building_array[i].name, str) == 0) {

            return i;
        }
    }

    return 0;   
}

int Graph::print_line(char start_place[], char end_place[], int type, int speed_on_foot, int speed_by_bike){

    int start, end;
    
    //�ѽ�������ת��Ϊ���
    start = this->name_to_index(start_place);
    end = this->name_to_index(end_place);

    if (start == 0 || end == 0)
    {
        return -1;
    }
    
    int ret = 0;
    if (type == 1) {
        
        ret += this->shortest_dis(start, end, speed_on_foot);
    }
    else if (type == 2) {
        
        ret += this->shortest_time(start, end, speed_on_foot);
    }
    else {
        
        ret += this->shortest_time_by_vehicle(start, end, speed_on_foot, speed_by_bike);
    }

    return ret;   
}

//��xxx(��������)��xxx�׵���xxx(��������)
int Graph::output(int start, int end) {

    int x1 = this->building_array[start].pos.x;
    int y1 = this->building_array[start].pos.y;
    int x2 = this->building_array[end].pos.x;
    int y2 = this->building_array[end].pos.y;
    int length = this->graph[start][end].length;
          
    if (x1 == x2) 
    {        
        if (y1 > y2) cout << "������";                  
        else cout << "����";             
    }
    else if(x1 > x2) 
    {
        if (y1 == y2) cout << "������";
        else if (y1 > y2) cout << "��������";
        else cout << "��������";
    }
    else
    {
        if (y1 == y2) cout << "����";
        else if (y1 > y2) cout << "������";
        else cout << "�򶫱���";
    }

    cout << length << "�׵���";
    cout << this->building_array[end].name << endl;
    return length;
}

int Graph::shortest_dis(int start, int end, int speed_on_foot)
{
    //Dijkstra
    int* dis = new int[this->vertex_num + 1];
    int* vis = new int[this->vertex_num + 1];
    //��¼���ĸ��㵽�õ�
    int* forward = new int[this->vertex_num + 1];

    //��ʼ��
    for (int i = 1; i <= this->vertex_num; i++)
    {
        dis[i] = INF;
        vis[i] = 0;
        forward[i] = 0;
    }

    dis[start] = 0;
    
    
    for (int i = 1; i <= this->vertex_num; i++)
    {
        //�ҵ�������������ĵ�
        int min_dis = INF;
        int index = 0;

        for (int j = 1; j <= this->vertex_num; j++)
        {
            if (!vis[j] && dis[j] <= min_dis)
            {
                min_dis = dis[j];
                index = j;
            }
        }

        //��Ǹõ�
        vis[index] = 1;

        //���¾���
        for (int j = 1; j <= this->vertex_num; j++)
        {
            if (!vis[j] && this->graph[index][j].length != -1 &&
                dis[j] > dis[index] + this->graph[index][j].length)
            {
                dis[j] = dis[index] + this->graph[index][j].length;
                forward[j] = index;
            }
        }
    }

    //�����·
    int temp[30];
    int i = 0, time = 0;
    temp[i] = end;
    while (temp[i] != start)
    {
        i++;
        temp[i] = forward[temp[i - 1]];
    }
    
    for (int j = i; j > 0; j--)
    {
        int len = output(temp[j], temp[j - 1]);

        time += len / (speed_on_foot * this->graph[temp[j]][temp[j - 1]].crowd_degree);
    }

    delete[] dis;
    delete[] vis;
    delete[] forward;

    return time;
}