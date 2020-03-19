// EleBasicData.h: interface for the EleBasicData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEBASICDATA_H__431A0619_1CA3_4F04_8045_AD31E5D79372__INCLUDED_)
#define AFX_ELEBASICDATA_H__431A0619_1CA3_4F04_8045_AD31E5D79372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ELEVATOR_NUM 6			//������

#define FLOOR_NUM 10		    //¥����

#define MAX_PASSENGER_NUM 12    //��������ؿ���

#define ELEVATOR_HEIGHT 40	    //��������߶ȣ�MyLabels)

#define ONE_FLOOR_TIME 2	    //��������һ��¥������ʱ��(ms)

#define DOOR_OPEN_TIME 10	    //�����ݵ���ĳһ¥��󡿣����ֿ���״̬��ʱ�䣩(ms)

#define DOOR_CLOSE_TIME 5       //�����ݵ���ĳһ¥��󡿣����ֹ���״̬��ʱ�䣩(ms)

#define DOOR_ONOFF_TIME 2       //�����ſ����һ������ʱ��(ms)

#define PSG_INOUT_TIME  2       //�˿ͽ����һ������ʱ��(ms)

#define BAD_REQUEST_AGE 120	    //�������ĵȴ������еȴ��ʱ�䣨s������ʱû�еõ���������󽫱�ɾ��

#define SCHEDULE_INTERVAL 1	    //�������Ĵ���ȴ����е�ʱ����(ms)

#define DIST_PRIO 3			    //����������ʱ������ռȨ�أ���λʱ������

#define WEIGHT_PRIO 1		    //����������ʱ��������ռȨ�أ���λʱ�䣩



//enum state {IDLE,DOWN,UP,DOOR_OPEN,DOOR_CLOSE,MAL_FUNCTION,BAD_STATE};
enum state {IDLE,DOWN_RUN,UP_RUN,DOWN_PAUSE,UP_PAUSE,DOOR_OPEN,MAL_FUNCTION,BAD_STATE};
//enum state {IDLE,DOWN_RUN,UP_RUN,DOWN_PAUSE,UP_PAUSE,DOOR_OPEN,MAL_FUNCTION,BAD_STATE,DOWN_PAUSE_OPEN,DOWN_PAUSE_CLOSE,UP_PAUSE_OPEN,UP_PAUSE_CLOSE};
enum direction {DOWN,UP,BAD_DIRE};
enum speed {ST_FLS_SLOW,ST_FLS_NORMAL,ST_FLS_FAST};


//�������ĵȴ����нڵ�����

typedef struct {
enum direction eReqDirection;  //Ŀ�귽��
int iReqFloor;                 //Ŀ��¥��
int iAge;                      //�����������ĵ����м�¼������ĵȴ�ʱ��
bool bReClaimed;               //�ýڵ��Ƿ񱻻���
} sOuterRequest;


#endif // !defined(AFX_ELEBASICDATA_H__431A0619_1CA3_4F04_8045_AD31E5D79372__INCLUDED_)
