#include <stdio.h>
int main()
{
    #ifdef _WIN32
        printf("Hello, Windows!\n");
    #elif __linux__
        printf("Hello, Linux!\n");
    #endif
    
    return 0;
}