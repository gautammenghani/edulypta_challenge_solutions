#include<stdio.h>
#include <sys/syscall.h>

int main (){
        long res;
        syscall(451, 0xdead, 0xbeef);

        if (syscall(451, 0xdead, 0xbeef)== 0)
                printf("right ans!\n");
        else
                printf("wrong id\n");

        if (syscall(451, 1, 1)== 0)
                printf("right ans!\n");
        else
                printf("wrong id\n");

        return 0;
}

