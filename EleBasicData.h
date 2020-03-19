// EleBasicData.h: interface for the EleBasicData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEBASICDATA_H__431A0619_1CA3_4F04_8045_AD31E5D79372__INCLUDED_)
#define AFX_ELEBASICDATA_H__431A0619_1CA3_4F04_8045_AD31E5D79372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ELEVATOR_NUM 6			//电梯数

#define FLOOR_NUM 10		    //楼层数

#define MAX_PASSENGER_NUM 12    //电梯最大载客数

#define ELEVATOR_HEIGHT 40	    //电梯箱体高度（MyLabels)

#define ONE_FLOOR_TIME 2	    //电梯运行一个楼层所需时间(ms)

#define DOOR_OPEN_TIME 10	    //【电梯到达某一楼层后】（保持开门状态的时间）(ms)

#define DOOR_CLOSE_TIME 5       //【电梯到达某一楼层后】（保持关门状态的时间）(ms)

#define DOOR_ONOFF_TIME 2       //电梯门开或闭一次所需时间(ms)

#define PSG_INOUT_TIME  2       //乘客进或出一次所需时间(ms)

#define BAD_REQUEST_AGE 120	    //主控中心等待队列中等待最长时间（s），超时没有得到处理的请求将被删除

#define SCHEDULE_INTERVAL 1	    //主控中心处理等待队列的时间间隔(ms)

#define DIST_PRIO 3			    //计算优先数时距离所占权重（单位时间数）

#define WEIGHT_PRIO 1		    //计算优先数时载重量所占权重（单位时间）



//enum state {IDLE,DOWN,UP,DOOR_OPEN,DOOR_CLOSE,MAL_FUNCTION,BAD_STATE};
enum state {IDLE,DOWN_RUN,UP_RUN,DOWN_PAUSE,UP_PAUSE,DOOR_OPEN,MAL_FUNCTION,BAD_STATE};
//enum state {IDLE,DOWN_RUN,UP_RUN,DOWN_PAUSE,UP_PAUSE,DOOR_OPEN,MAL_FUNCTION,BAD_STATE,DOWN_PAUSE_OPEN,DOWN_PAUSE_CLOSE,UP_PAUSE_OPEN,UP_PAUSE_CLOSE};
enum direction {DOWN,UP,BAD_DIRE};
enum speed {ST_FLS_SLOW,ST_FLS_NORMAL,ST_FLS_FAST};


//主控中心等待队列节点类型

typedef struct {
enum direction eReqDirection;  //目标方向
int iReqFloor;                 //目标楼层
int iAge;                      //用于主控中心调度中记录该请求的等待时间
bool bReClaimed;               //该节点是否被回收
} sOuterRequest;


#endif // !defined(AFX_ELEBASICDATA_H__431A0619_1CA3_4F04_8045_AD31E5D79372__INCLUDED_)
