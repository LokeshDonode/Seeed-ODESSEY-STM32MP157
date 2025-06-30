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
        tcgetattr(fd,&options); // get current setting before modifying

        options.c_cflag = B115200 | CS8 | CLOCAL |CREAD;
        // or cfsetspeed(&options, B115200);
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;
        
        // To avoid indefinite blocking if no data is received, configure read timeouts
        options.c_cc[VMIN]  = 0; // Minimum number of characters for non-canonical read
        options.c_cc[VTIME] = 10; // Timeout in deciseconds (1s)

        // Apply the settings
        tcflush(fd,TCIFLUSH);
        if (tcsetattr(fd, TCSANOW, &options) != 0) {
                perror("Failed to set serial port attributes");
                return -1;
            }
        /* Write to serial port */
        strcpy(buf,"Hello World !\n\r");
        len = strlen(buf);
        len = write(fd , buf , len);
        printf("write %d bytes over UART\n",len);

        printf("You have 5 secs to send data...\n");
        sleep(5);

        /* Read from serial port */
        memset(buf, 0, sizeof(buf));  // Clear buffer before reading
        len = read(fd , buf , sizeof(buf));
        printf("Received %d bytes \n",len);
        printf("Received string.. %.*s\n", len, buf); // If the received data is not null-terminated.

        close(fd);
        return 0;
}
