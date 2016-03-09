/* Alarm get/set status values */
#define ALARM_1 	5
#define ALARM_2		6

#define AFLGS		0b11111111

void handleAlaram(void);
void setAlarm(struct _tm time, char *name, int sec);
int getDuration(void);
char* getName(void);
int checkTime(void);
