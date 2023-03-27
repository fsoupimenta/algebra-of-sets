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

int check_pertinence(int element, int set[set_size])
{
    for (int count = 0; count < set_size; count++)
    {
        if (element == set[count])
        {
            return 1;
        }
    }
    return 0;
}

int check_contains(int setA[set_size], int setB[set_size])
{
    for (int count = 0; count < set_size; count++)
    {
        if (check_pertinence(setA[count], setB) == 0)
        {
            return 0;
        }
    }
    return 1;
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
               "3-)To check pertinence \n"
               "4-)To check if set X contains set Y \n"
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

            case 3:
                printf("Type the element: \n");
                scanf("%d", &element);
                if (check_pertinence(element, set_A) != 0)
                {
                    printf("%d belongs to the set", element);
                }
                else
                {
                    printf("%d not belongs to the set", element);
                }
                break;

            case 4:
                if (check_contains(set_A, set_B) != 0)
                {
                    printf("A contains B");
                }
                else
                {
                    printf("A not contains B");
                }
                break;

            default:
                break;
        }
        printf("\n ----------------------\n");
    }

    return 0;
}


