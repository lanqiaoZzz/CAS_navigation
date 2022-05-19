//代表x点x分
struct time{

    int hour;
    int minute;
};

class Bus{

public:

    Bus();
    ~Bus();

    Bus(int type1, int type2, int station, int start_time, int end_time, int gap);

    /*
    time_at_station: 到达车站的时间（精确到分钟）
    return: 到达另一个校区门口所需时间（分钟数）
            若到达时，公交车已不发车，则返回-1
    */
    int calculate_time(struct time time_at_station);

public:

    int type1;               //1：沙河到本部  2：本部到沙河
    int type2;               //1：定点班车  2：公共汽车
    int station;             //站点：默认在学校门口
    
    //默认每天都会发车
    int start_time;         //第一辆车发动的时间（0-24 精确到小时）
    int end_time;           //最后一辆车发动的时间
    int gap;                //相邻两辆车发动的时间间隔
    
public:    
    
    static int time_need;        //从一个校区到另一个校区的时间（分钟）
};



