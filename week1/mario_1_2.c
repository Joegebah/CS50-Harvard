#include <cs50.h>
#include <stdio.h>

int main(void)
{

    const char HASH = '#';
    const char WHITE = ' ';
    int n;

    do {
        n = get_int("Height: ");
    } 
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++) {
        int k = (n - i);
        do {
            printf("%c", WHITE);
            k--;
        } 
        while (k >= 0);

        int a = 0;
        do{
            printf("%c", HASH);
            a++;
        } 
        while (a <= i);

        printf("%c", WHITE);
        printf("%c", WHITE);

        int j = 0;

        do {
            printf("%c", HASH);
            j++;
        } 
        while (j <= i);

        printf("\n");
    }
}
