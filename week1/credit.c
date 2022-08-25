#include <cs50.h>
#include <stdio.h>
int main(void)
{
    long n;
    long productDigitSum = 0;
    long productSum = 0;
    long sumOfNotMultiplier = 0;
    long check;
    bool creditCardIsValid = false;

    while (!creditCardIsValid) {
        do {
            n = get_long("please enter your credit card number: \n");
        }
        while (n < 1);
        long save_n = n;
        long save_n_2 = n;
        long save_n_3 = n;
        long save_n_4 = n;
        long save_n_5 = n;
        n = n / 10;
        do {
            productSum = productSum + (n % 10) * 2;
            if (((n % 10) * 2) < 10) {
                productDigitSum = productDigitSum + (n % 10) * 2;
            }
            else {
                productDigitSum = productDigitSum + (((n % 10) * 2) % 10) + ((((n % 10) * 2) / 10) % 10);
            }
            n = n / 100;
        }
        while (n > 0 || (n / 10) > 10);

        do {
            sumOfNotMultiplier = sumOfNotMultiplier + (save_n % 10);
            save_n = save_n / 100;
        }
        while(save_n > 0 || (save_n / 100) >= 10);

        check = sumOfNotMultiplier + productDigitSum;
        if (check % 10 == 0) {
            int i = 0;
            while (save_n_2 > 0) {
                save_n_2 = save_n_2 / 10;
                i++;
            }
                if (i == 15) {
                    while (save_n_3 > 100) {
                        save_n_3 = save_n_3 / 10;
                    }
                    if (save_n_3 == 34 || save_n_3 == 37) {
                        printf("AMEX\n");
                        creditCardIsValid = true;
                    }
                    else if ((save_n_3 / 10) == 4) {
                        printf("VISA\n");
                        creditCardIsValid = true;
                    }
                    else {
                        printf("Unknown credit id, ");
                    }
                }
                else if (i == 16) {
                    while (save_n_4 > 100) {
                        save_n_4 = save_n_4 / 10;
                    }
                    if (save_n_4 == 51 || save_n_4 == 52 || save_n_4 == 53 || save_n_4 == 54 || save_n_4 == 55) {
                        printf("MASTER\n");
                        creditCardIsValid = true;
                    }
                    else if ((save_n_4 / 10) == 4) {
                        printf("VISA\n");
                        creditCardIsValid = true;
                    }
                    else {
                        printf("Unknown credit id, ");
                    }
                }
                else if (i == 13 || i == 14) {
                    while (save_n_5 > 100) {
                        save_n_5 = save_n_5 / 10;
                    }
                    if ((save_n_5 / 10) == 4) {
                        printf("VISA\n");
                        creditCardIsValid = true;
                    }
                    else {
                        printf("Unknown credit id, ");
                    }
                }
                else {
                    printf("Unknown credit id, ");
                }
            }
        else {
            printf("INVALID\n");
        }
    }
}
