#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>

int main(){
        int fd, len;  // fd - file descriptor
        char buf[255]; // define buffer
        struct termios options; // serial port settings

        fd = open("/dev/ttySTM2", O_RDWR | O_NDELAY | O_NOCTTY);
        if(fd < 0){
                perror("Error in opening in serial port\n");
                return -1;
        }
        /* Read current serial port settings */
        // Set up serial port
        tcgetattr(fd,&options);

        options.c_cflag = B115200 | CS8 | CLOCAL |CREAD;
        // or cfsetspeed(&options, B115200);
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;

        // Apply the settings
        tcflush(fd,TCIFLUSH);
        tcsetattr(fd,TCSANOW,&options);

        /* Write to serial port */
        strcpy(buf,"Hello World !\n\r");
        len = strlen(buf);
        len = write(fd , buf , len);
        printf("write %d bytes over UART\n",len);

        printf("You have 5 secs to send data...\n");
        sleep(5);

        /* Read from serial port */
        len = read(fd , buf , sizeof(buf));
        printf("Received %d bytes \n",len);
        printf("Received string.. %s\n",buf);

        close(fd);
        return 0;
}
