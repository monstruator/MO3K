#include <unistd.h>
#include <sys/osinfo.h>
#include <time.h>
#include <process.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/dev.h>

void main(int argc, char *argv[])
{
printf("module b start\n");
delay(500);
system("//9/home/m3_B &");
}