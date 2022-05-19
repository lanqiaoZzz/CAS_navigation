#include "Student.h"

//��ʼ��
Graph Student::s_graph;
Graph Student::b_graph;

Student::Student()
{
    Graph::init_bus("bus.txt");
    s_graph.init_graph("ɳ�ӵ�ͼ2.0.txt");
    b_graph.init_graph("������ͼ1.0.txt");

    this->speed_on_foot = 75;
    this->speed_by_bike = 100;
}

TimeTable* Student::get_timetable() {

    return table;
}

void Student::start_navigation() {

    //1. ��ϵͳ����γ����ơ��Ͽ�ʱ������Ͽεص�
    cout << "---��ʼ����Ŀ�ĵ�---" << endl;
    cout << "��ѡ����Ҫ�������Ϣ���ͣ�" << endl;
    cout << "1.�γ�����" << endl;
    cout << "2.�Ͽ�ʱ��" << endl;
    cout << "3.�Ͽεص�(s-xxx / b-xxx)" << endl;

    int type;
    cin >> type;

    cout << "�밴�ո�ʽ������Ϣ��" << endl;

    char str[30];
    cin >> str;

    char* dest;

    //2. �γ����� / �Ͽ�ʱ��-- > �Ͽεص�
    if (type == 1) {

        dest = get_timetable()->name_to_place(str);
    }
    else if (type == 2) {

        dest = get_timetable()->time_to_place(str);
    }
    else dest = str;

    //δ���ҵ�
    if (dest == NULL) {

        cout << "δ���ҵ�Ŀ�ĵأ����˳�" << endl;
        return;
    }
    else {

        cout << "����ǰ����Ŀ�ĵ��ǣ�" << dest << endl;
    }

    //3. �����Լ���ǰ���ڵ�λ��(��������)���������Ժ͵�ǰʱ��(��ȷ������)
    cout << "����������ǰ���ڵ�λ��(s-xxx / b-xxx)��" << endl;

    char source[30];
    cin >> source;

    cout << "��������Ҫѡ��ĵ�������" << endl;
    cout << "1.��̾���" << endl;
    cout << "2.���ʱ��" << endl;
    cout << "3.��ͨ���ߵ����ʱ��" << endl;
    cin >> type;

    cout << "������ʼ����(" << source << " -- " << dest << " ����" << type << ")" << endl;
    cout << "------------------------" << endl;

    //4. �жϵ�ǰλ�ú��Ͽεص��Ƿ���������ͬ��У��       
    
    //��¼�ܹ����ѵ�ʱ��
    int sum = 0;

    //4.1 ������ɳ��
    if (dest[0] == 's' && source[0] == 's') {

        sum += s_graph.print_line(source, dest, type, speed_on_foot, speed_by_bike);
        if (sum == -1)
        {
            cout << "Ŀ�ĵػ�����ز����ڣ����˳�" << endl;
            return;
        }
    }
    //4.2 �����ڱ���
    else if (dest[0] == 'b' && source[0] == 'b') {

        sum += b_graph.print_line(source, dest, type, speed_on_foot, speed_by_bike);
        if (sum == -1)
        {
            cout << "Ŀ�ĵػ�����ز����ڣ����˳�" << endl;
            return;
        }
    }
    //4.3 ������ͬһУ������Ϊ����(1.��ǰλ�õ�ѧУ�ſ� 2.һ��У������һ��У�� 3.ѧУ�ſڵ��Ͽεص�)
    else if(dest[0] == 's' && source[0] == 'b' || dest[0] == 'b' && source[0] == 's') 
    {

        char temp1[] = "s-����";
        char temp2[] = "b-����";

        struct time cur;
        cur.hour = Timer::curTime;
        cur.minute = 0;

        if (source[0] == 's') {
           
            sum += s_graph.print_line(source, temp1, type, speed_on_foot, speed_by_bike);
            if (sum == -1)
            {
                cout << "Ŀ�ĵػ�����ز����ڣ����˳�" << endl;
                return;
            }

            //����ʵ���������ʱ��minute���ᳬ��60
            cur.minute = sum;
            int t1;

            //��У����ͨ��
            //Ĭ��ѡ�񻨷�ʱ�����ٵ�ͨ�г�����ʱ����ͬ����ѡ��У��
            if (Graph::bus_array[0].calculate_time(cur) <= Graph::bus_array[1].calculate_time(cur)) {

                t1 = Graph::bus_array[0].calculate_time(cur);
                sum += t1;
                cout << "�Ƽ�ѡ��У��ͨ�У�";
            }
            else if (Graph::bus_array[0].calculate_time(cur) > Graph::bus_array[1].calculate_time(cur)) {

                t1 = Graph::bus_array[1].calculate_time(cur);
                sum += t1;
                cout << "�Ƽ�ѡ�񹫽���ͨ�У�";
            }

            cout << "Ԥ����" << t1 << "���ӿɵ���[b-����]" << endl;
            
            int t = b_graph.print_line(temp2, dest, type, speed_on_foot, speed_by_bike);
            if (t == -1)
            {
                cout << "Ŀ�ĵػ�����ز����ڣ����˳�" << endl;
                return;
            }
            sum += t;
        }
        else {

            sum += b_graph.print_line(source, temp2, type, speed_on_foot, speed_by_bike);
            if (sum == -1)
            {
                cout << "Ŀ�ĵػ�����ز����ڣ����˳�" << endl;
                return;
            }

            cur.minute = sum;
            int t2;

            //��У����ͨ��
            //Ĭ��ѡ�񻨷�ʱ�����ٵ�ͨ�г�����ʱ����ͬ����ѡ��У��
            if (Graph::bus_array[2].calculate_time(cur) <= Graph::bus_array[3].calculate_time(cur)) {

                t2 = Graph::bus_array[2].calculate_time(cur);
                sum += t2;
                cout << "�����㣬�Ƽ�ѡ��У��ͨ�У�";
            }
            else if (Graph::bus_array[2].calculate_time(cur) > Graph::bus_array[3].calculate_time(cur)) {

                t2 = Graph::bus_array[3].calculate_time(cur);
                sum += t2;
                cout << "�����㣬�Ƽ�ѡ�񹫽���ͨ�У�";
            }

            cout << "Ԥ����" << t2 << "���ӿɵ���[s-����]" << endl;

            int t = s_graph.print_line(temp1, dest, type, speed_on_foot, speed_by_bike);
            if (t == -1)
            {
                cout << "Ŀ�ĵػ�����ز����ڣ����˳�" << endl;
                return;
            }
            sum += t;
        }
    }
    else
    {
        cout << "�����ʽ����ȷ�����˳�" << endl;
        return;
    }

    cout << "Ԥ��ȫ����" << sum << "���ӿɵ���Ŀ�ĵ�" << endl;
    cout << "------------------------" << endl;
    cout << "��������" << endl;
}
