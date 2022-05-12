#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
BUFSIZE is for vcgencmd measure_temp command output
it should not be more then 16 chars.
*/
#define BUFSIZE 16

/*
Usage:
 pi-temp [options]

Monitor CPU temperature.

Options:
 -c			run using "vcgencmd measure_temp" command, this is default
 -f			run reading file /sys/class/thermal/thermal_zone0/temp
 -d	[NUM]	delay in second between measures, this option should be
			used separetely, default is 3.
 -t			print timestamp before temperature
 -l			write results in file, default file ./pi-temp.log

Examples:
 pi-temp -f -t -l -d 3 
*/
void print_temp_cmd(void);

int main(int argc, char **argv) {
    short sleepsec = 3;
    /* run-type, 1 for -c flag, 0 for -f flag */
    short run_type = 1;
    /* ts_bool, timestamp, 1 for -t flag, 0 for none */
    short ts_bool = 0;
    /* log_bool, log write, 1 for -l flag, 0 for none */
    short log_bool = 0;
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
 			else if (strcmp(argv[i], "-l") == 0)
				log_bool = 1;
			else if (strcmp(argv[i], "-d") == 0) {
				i++; 
				sleepsec = atoi(argv[i]);
			}
		}
	}
	
/*
DEBUG
printing out arguments
*/
	if (run_type)
		printf("flag -c was used\n");
	else
		printf("flag -f was used\n");
	
	if (ts_bool)
		printf("flag -t was used\n");
	if (log_bool)
		printf("flag -l was used\n");
	printf("delay = %d seconds\n", sleepsec);
	
	printf("\nprinting arguments:\n");
	for (i = 1; i < argc; i++)
		printf("argument %d = %s\n", i, argv[i]);
/*
END o DEBUG */
					
				
    
/*
clean screen
    printf("\e[1;1H\e[2J");
*/


    
    return 0;
}

void print_temp_cmd(void) {
	char *cmd = "/usr/bin/vcgencmd measure_temp";
    char buf[BUFSIZE];
    FILE *fp;
	
	/* opening pipe and if everything is OK - printing temp */
	if ((fp = popen(cmd, "r")) != NULL) 
        if (fgets(buf, BUFSIZE, fp) != NULL)
			printf("%s", buf);
		else {
			printf("Error getting result from command\n");
			exit(1);
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
