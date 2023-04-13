//
// Created by Fernando Pimenta on 25/03/2023.
//

#include "stdio.h"
#include "locale.h"
#define set_size 5

struct tuple
{
    int value_1;
    int value_2;
};

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

void print_union_set(int set[set_size * 2])
{
    for (int count = 0; count < set_size * 2; count++)
    {
        if (count == set_size * 2 - 1)
        {
            printf(" %d }", set[count]);
        }
        else
        {
            printf(" %d,", set[count]);
        }
    }
}

void print_cartesian_product(struct tuple product[set_size * set_size])
{
    for (int i=0; i < set_size * set_size; i++)
    {
        printf("(%d, %d)", product[i].value_1, product[i].value_2);
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

int *make_union(int setA[set_size], int setB[set_size])
{
    static int set[set_size * 2];
    int count_union_set = 0;
    for (int count = 0; count < set_size; count++)
    {
        set[count_union_set] = setA[count];
        count_union_set++;
    }
    for (int count = 0; count < set_size; count++){
        if (check_pertinence(setB[count], set) == 0)
        {
            set[count_union_set] = setB[count];
            count_union_set++;
        }
    }
    return set;
}

int *make_intersection(int setA[set_size], int setB[set_size])
{
    static int set[set_size];
    int count_intersection_set = 0;
    for (int count = 0; count < set_size; count++)
    {
        if (check_pertinence(setA[count], setB) != 0)
        {
            set[count_intersection_set] = setA[count];
            count_intersection_set++;
        }
    }
    return set;
}

struct tuple *make_cartesian_product(int setA[set_size], int setB[set_size])
{

    static struct tuple tuple[set_size * set_size];
    int tuple_count = 0;

    for (int i=0; i < set_size; i++)
    {
        for (int j=0; j < set_size; j++)
        {
            tuple[tuple_count].value_1 = setA[i];
            tuple[tuple_count].value_2 = setB[j];
            tuple_count++;
        }
    }
    return tuple;
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
               "5-)Print A union B \n"
               "6-)Print A intersection B \n"
               "7-)Print A cartesian product B \n"
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

            case 5:
                printf("A U B {");
                int *union_set = make_union(set_A, set_B);
                print_union_set(union_set);
                break;

            case 6:
                printf("A ∩ B {");
                int *intersection_set = make_intersection(set_A, set_B);
                print_set(intersection_set);
                break;

            case 7:
                printf("A x B ");
                struct tuple *cartesian_product;
                cartesian_product = make_cartesian_product(set_A, set_B);
                printf("%d", cartesian_product[0].value_1);
                print_cartesian_product(cartesian_product);
                break;

            default:
                break;
        }
        printf("\n ----------------------\n");
    }

    return 0;
}


