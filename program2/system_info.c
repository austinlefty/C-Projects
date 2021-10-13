#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("System Information: \n\n");

    //Host Name
    system("cat /proc/sys/kernel/hostname");

    //CPU Type and Model
    system("cat /proc/cpuinfo | grep -m1 model");
    system("cat /proc/cpuinfo | grep -m1 name");

    //Linux Version
    system("cat /proc/version");

    //Last Boot Date
    system("procinfo | grep Bootup");

    //Total CPU Time For User Mode, System Mode, And Idle
    system("cat /proc/stat | grep -m1 cpu");

    //Memory Total
    system("cat /proc/meminfo | grep -m1 MemTotal");

    //Memory Available
    system("cat /proc/meminfo | grep -m1 MemAvailable");

    //Disk Read/Write Requests
    system("cat /proc/$$/io | grep -m1 rchar");
    system("cat /proc/$$/io | grep -m1 wchar");

    //Context Switches
    system("cat /proc/$$/status | grep -m1 voluntary_ctxt_switches");
    system("cat /proc/$$/status | grep -m1 nonvoluntary_ctxt_switches");

    //Processes Created Since Boot Up
    system("cat /proc/stat | grep -m1 processes");

    return 0;
}