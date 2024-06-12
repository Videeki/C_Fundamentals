#include <stdio.h>
#include <unistd.h>

int main() {
    if (!isatty(fileno(stdin))) {
        printf("The application was not started from a terminal.\n");
    } else {
        printf("The application was started from a terminal.\n");
    }

    return 0;
}
