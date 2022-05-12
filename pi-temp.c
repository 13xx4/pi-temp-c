#include <stdio.h>
#include <unistd.h>

BUFSIZE is for vcgencmd measure_temp command output
 
#define BUFSIZE 32

/*
Usage:
 pi-temp [options]

Monitor CPU temperature.

Options:
 -c			run using "vcgencmd measure_temp" command, this is defualt
 -f			run reading file /sys/class/thermal/thermal_zone0/temp
 -d	[NUM]	delay in second between measures, this option should be
			used separetely, default is 3.
 -t			print timestamp before temperature
 -l			write results in file, default file ./pi-temp.log

Examples:
 pi-temp -f -t -l -d 3 
*/
 
int main(int arvc, char **argv) {
    char *cmd = "/usr/bin/vcgencmd measure_temp";
    char *cls = "/usr/bin/clear";
    char buf[BUFSIZE];
    FILE *fp;
    int sleepsec = 1;
    long unsigned count = 0;
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }
    pclose(fp);
    while (1 > 0) {
        printf("\e[1;1H\e[2J");
        fp = popen(cmd, "r");
        while (fgets(buf, BUFSIZE, fp) != NULL)
            printf("%d: %s", count, buf);
        sleep(sleepsec);
        count++;
        pclose(fp);
    }

    if (pclose(fp)) {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    return 0;
}
