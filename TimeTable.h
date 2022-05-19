class TimeTable {

public:

    //课程名称/上课时间 --> 上课地点
    /*
    课程名称 --> 上课地点
    name[]: 课程名称
    return: 上课地点(s-xxx/b-xxx)
            若未找到，返回空指针
    */
    char* name_to_place(char name[]);

    /*
    上课时间 --> 上课地点
    time[]: 课程名称
    return: 上课地点
    */
    char* time_to_place(char time[]);
};