#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main()
{
    int run = TRUE;
    int expression = 0;
    while(run)
    {
        switch (expression)
        {
            case 0:
            {
                puts("First State\n");
                expression = 1;
                break;  
            }
            case 1:
            {
                puts("Second State\n");
                expression = 2;
                break;  
            }
            case 2:
            {
                puts("Third State\n");
                expression = 3;
                break;  
            }
            case 3:
            {
                puts("Fourth State\n");
                expression = 4;
                break;  
            }
            case 4:
            {
                puts("Fifth State\n");
                expression = 5;
                break;  
            }
            default:
            {
                run = FALSE;
                break;
            }
                
        }
    }

    return 0;
}