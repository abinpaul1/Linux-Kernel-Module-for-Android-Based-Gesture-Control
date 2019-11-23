#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
    char str[200];
    int sim_fd;
    int key;
    char buffer[10];
    
    // Open the sysfs shortcut node
    sim_fd = open("/sys/devices/platform/gesture/gevent", O_RDWR);
    if (sim_fd < 0) {
        perror("Couldn't open gesture shortcut file\n");
        exit(-1);
    }
    while (1) {
      
        
        gets(str);
        key=str[43];
      
        // Convey simulated keypress to the gesture control driver
        
	    sprintf(buffer, "%d",key);
	    write(sim_fd, buffer, strlen(buffer));
	    fsync(sim_fd);
    }
    
    close(sim_fd);
}
