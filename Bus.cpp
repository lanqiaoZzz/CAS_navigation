#include "Bus.h"

int Bus::time_need = 60;

Bus::Bus() {

}

Bus::~Bus() {
	
}

Bus::Bus(int type1, int type2, int station, int start_time, int end_time, int gap) {

	this->type1 = type1;
	this->type2 = type2;
	this->station = station;
	this->start_time = start_time;
	this->end_time = end_time;
	this->gap = gap;
}

int Bus::calculate_time(struct time time_at_station) {

	if (time_at_station.hour > this->end_time ||
		time_at_station.hour == this->end_time && time_at_station.minute != 0) {

		return -1;
	}
	
	int temp = this->start_time;

	while (temp < time_at_station.hour) {

		temp += this->gap;
	}

	int ret = Bus::time_need;
	if (temp == time_at_station.hour) {

		if (time_at_station.minute != 0) {

			ret += this->gap * 60 - time_at_station.minute;
		}
	}
	else {

		ret += (temp - time_at_station.hour) * 60 - time_at_station.minute;
	}

	return ret;	
}
