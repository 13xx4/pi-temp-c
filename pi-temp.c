#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 32

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
