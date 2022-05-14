#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
BUFSIZE is for vcgencmd measure_temp command output
it should not be more then 16 chars.
*/
#define BUFSIZE 16

void print_temp_cmd(void);
void print_temp_file(void);
void print_timestamp(void);
void print_help(void);

int main(int argc, char **argv) {
    short sleepsec = 2;
    /* run-type, 1 for -c flag, 0 for -f flag */
    short run_type = 1;
    /* ts_bool, timestamp, 1 for -t flag, 0 for none */
    short ts_bool = 0;
    /* cls_bool, 1 for -r flag */
    short cls_bool = 0;
    short i = 0;

    /* checking arguments */
    if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-c") == 0)
				run_type = 1;
			else if (strcmp(argv[i], "-f") == 0)
				run_type = 0;
			else if (strcmp(argv[i], "-t") == 0)
				ts_bool = 1;
			else if (strcmp(argv[i], "-r") == 0) {
				cls_bool = 1;
			    printf("\e[1;1H\e[2J");
			}
			else if (strcmp(argv[i], "-d") == 0) {
				i++; 
				sleepsec = atoi(argv[i]);
			} 
			else if ((strcmp(argv[i], "--help")) || (strcmp(argv[i], "-h"))) {
				print_help();
				exit(0);
			}
			else {
				printf("Error: wrong argument\n");
				print_help();
				exit(1);
			}
		}
	}
	
/* main routine */
	if (run_type)
		while (1 > 0) {
			if (ts_bool)
				print_timestamp();
			print_temp_cmd();
			sleep(sleepsec);
			if (cls_bool)
			    printf("\e[1;1H\e[2J");
		}
	else
		while (1 > 0) {
			if (ts_bool)
				print_timestamp();
			print_temp_file();
			sleep(sleepsec);
			if (cls_bool)
			    printf("\e[1;1H\e[2J");
		}
    
    return 0;
}

void print_temp_cmd(void) {
	char *cmd = "/usr/bin/vcgencmd measure_temp";
    char buf[BUFSIZE];
    FILE *fp = NULL;
	
	/* opening pipe and if everything is OK - printing temp */
	if ((fp = popen(cmd, "r")) != NULL) 
        if (fgets(buf, BUFSIZE, fp) != NULL)
			printf("%s", buf);
		else {
			printf("Error getting result from command\n");
			exit(86);
		}
    else {
		printf("Error opening pipe!\n");
        exit(127);
    }
    if (pclose(fp)) {
		printf("Error closing pipe\n");
		exit(1);
	}
}

void print_temp_file(void) {
	char *path = "/sys/class/thermal/thermal_zone0/temp";
    char buf[BUFSIZE];
    FILE *fp = NULL;
    float ftemp = 0.0;
    if ((fp = fopen(path, "r")) != NULL) 
        if (fgets(buf, BUFSIZE, fp) != NULL) {
			ftemp = atof(buf);
			ftemp = ftemp / 1000.0;
			printf("temp=%.1f'C\n", ftemp);
		}
		else {
			printf("Error getting result from file\n");
			exit(5);
		}
    else {
		printf("Error opening file.\n");
        exit(2);
    }
    if (pclose(fp)) {
		printf("Error closing file.\n");
		exit(1);
	}
}

void print_timestamp(void){
	char timebuf[21];
    time_t now;
    struct tm* tm_info;
    
	now = time(NULL);
	tm_info = localtime(&now);
	strftime(timebuf, 21, "%Y.%m.%d %H:%M:%S ", tm_info);
	printf("%s", timebuf);
}

void print_help(void) {
	printf("\n\
Usage: ./[program name] [options]\n\
Monitor CPU temperature.\n\
\n\
Options:\n\
  -c\t\trun using \"vcgencmd measure_temp\" command, this is default\n\
  -f\t\trun reading file /sys/class/thermal/thermal_zone0/temp.\n\
\t\tThis mode is lower on RES and should work on most Debian/Ubuntu.\n\
  -d [NUM]\tdelay in second between measures, this option should be\n\
\t\tused separetely, default is 2.\n\
  -t\t\tprint timestamp before temperature.\n\
  -r\t\tuse monitor mode instead of history mode.\n\
  -h, --help\tshow this help.\n\
\n\
Examples:\n\
  pi-temp -f -t -d 3\n\
\n\
Author: Aleksejs Abrosimovs\n");
}
