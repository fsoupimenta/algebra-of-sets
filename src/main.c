//
// Created by Fernando Pimenta on 25/03/2023.
//

#include "stdio.h"
#include "locale.h"
#define set_size 5

void print_set(int set[set_size])
{
    for (int count = 0; count < set_size; count++)
    {
        if (count == set_size - 1)
        {
            printf(" %d }", set[count]);
        }
        else
        {
            printf(" %d,", set[count]);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");

    int set_A[set_size] = {0, 1, 2, 3, 4},
        set_B[set_size] = {4, 5, 6, 7, 8},
        element, key = -1;

    while (key != 0)
    {
        printf("What do you want to do? \n"
               "1-)Print set A \n"
               "2-)Print set B \n"
               "0-)Exit \n");
        scanf("%d", &key);

        switch (key) {
            case 1:
                printf("A = {");
                print_set(set_A);
                break;

            case 2:
                printf("B = {");
                print_set(set_B);
                break;

            default:
                break;
        }
        printf("\n ----------------------\n");
    }

    return 0;
}


