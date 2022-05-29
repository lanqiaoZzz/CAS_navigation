#include <iostream>
#include "Student.h"

using namespace std;

void test_bus() {

	Bus b(1, 1, 1, 8, 20, 1);

	struct time t;
	t.hour = 20;
	t.minute = 1;

	cout << b.calculate_time(t);
}

void test_graph() {

	Graph g;

	Graph::init_bus("C:\\Users\\lanqiao\\Desktop\\bus.txt");
	g.init_graph("C:\\Users\\lanqiao\\Desktop\\É³ºÓµØÍ¼1.0.txt");

	g.output();
}

void test() {

	Student s;
	s.start_navigation();
	/*int node[] = { 20, 21 };
	s.s_graph.shortest_dis_places(30, 10, node, 2);*/

}

int main() {

	test();
	
	
}