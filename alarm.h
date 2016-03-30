/* Alarm get/set status values */
#define ALARM_1 	5
#define ALARM_2		6

#define AFLGS		0b11111111

#ifndef _ALARM_DEFINED
struct _alarm
{
	struct _tm time;
	char ip[24];
	u_short port;
	char url[24];
	char name[16];
	int snooze;
	int id;
	int state;
};
#define _ALARM_DEFINED
#endif

void handleAlarm(int idx);
int checkAlarms(void);
void setAlarm(struct _tm time, char* name, char* ip, u_short port, char* url, int snooze, int id, int idx);
int alarmExist(int id);
void deleteAlarm(int idx);
void eenmaligAlarmCheck(int idx);
void eenmaligAlarm(struct _tm time, char* name, char* ip, u_short port, char* url, int snooze, int id, int idx);
int compareTime(tm t1, tm t2);
void setState(int idx);
int getState(int idx);
struct _alarm getAlarm(int idx);