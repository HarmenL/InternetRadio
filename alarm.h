
#ifndef _ALARM_DEFINED
typedef struct _alarm
{
    struct _tm time;   // Alarm time                          ?
    u_long ip;         // IP of the stream to be played       4
	u_short port;      // Port of the stream to be played     2
	char url[24];      // Get url                            24
	char name[16];     // Name of the alarm                  16
	char snooze;       // Snooze time in minutes              1
	int id;            // Database identifier                 2
	signed char state; // Enum: [-1 ... 2]                    1
} AAlarm;              // Total size:                        50 + ?


void handleAlarm(int idx);
int checkAlarms(void);
void setAlarm(struct _tm time, char* name, u_long ip, u_short port, char* url, char snooze, int id, int idx); // TODO: Linked list?
int alarmExist(int id);
void deleteAlarm(int idx);
void setState(int idx);
int getState(int idx);
struct _alarm getAlarm(int idx);

#define _ALARM_DEFINED
#endif