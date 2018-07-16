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
printf("module a start\n");
delay(1000);

system("//9/bin/devu-ft245 -b 200 -p 20 &");
system("//9/home/KRK12P &");

system("//9/home/m3 &");
system("//9/home/obmen_MO3 &");
system("//9/home/k1 &");
system("//9/home/k2 &");
system("//9/home/read_ft245 &");
}