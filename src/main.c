//
// Created by Fernando Pimenta on 25/03/2023.
//

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

typedef struct reg {
    int value;
    struct reg *next;
} set;

typedef struct tup {
    int firstValue;
    int secondValue;
    struct tup *next;
} tuple;

typedef struct power {
    set *setA;
    struct power *next;
} powerSet;

int len(set *set_X)
{
    set *helper;
    int size = 0;

    for (helper = set_X->next; helper != NULL; helper = helper->next)
    {
        size++;
    }
    return size;
}

void insert_set(int value, set *n)
{
    set *new;
    new = malloc(sizeof (set));
    new->value = value;
    new->next = n->next;
    n->next = new;
}

void insert_set_in_list(int *values, int size, set *setX)
{
    for (int i = 0; i < size; i++)
    {
        insert_set(values[i], setX);
    }
}

void insert_tuple(int firstValue, int secondValue, tuple *n)
{
    tuple *new;
    new = malloc(sizeof (tuple));
    new->firstValue = firstValue;
    new->secondValue = secondValue;
    new->next = n->next;
    n->next = new;
}

void insert_power_set(set *setA, powerSet *pow)
{
    powerSet *new;
    new = malloc(sizeof (powerSet));
    new->setA = setA;
    new->next = pow->next;
    pow->next = new;
}

void print_set (set *set_X) {
    set *helper;
    printf("(");
    for (helper = set_X->next; helper != NULL; helper = helper->next)
        printf (" %d", helper->value);
    printf(" )");
}

void print_tuple (tuple *set_X) {
    tuple *helper;
    for (helper = set_X->next; helper != NULL; helper = helper->next)
        printf ("( %d, %d )", helper->firstValue, helper->secondValue);
}

void print_power_set (powerSet *pow)
{
    powerSet *helper;
    printf("{ \n");
    for (helper = pow->next; helper != NULL; helper = helper->next)
        print_set(helper->setA);
    printf("}");
}

int check_pertinence(int element, set * set_X)
{
    set *helper;
    for (helper = set_X->next; helper != NULL; helper = helper->next)
    {
        if (element == helper->value)
        {
            return 1;
        }
    }
    return 0;
}

int check_contains(set *setA, set *setB)
{
    set *helper;
    for (helper = setA->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(setA->value, setB) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int check_contains_equals(set *setA, set *setB)
{
    if (check_contains(setA, setB) == 1 && len(setA) == len(setB))
    {
        return 1;
    }
    else if (check_contains(setA, setB))
    {
        return 2;
    }
    return 0;
}

set *make_union(set *setA, set *setB)
{
    set *helper;
    set *unionSet = malloc (sizeof (set));
    for (helper = setA->next; helper != NULL; helper = helper->next)
    {
        insert_set(helper->value, unionSet);
    }
    for (helper = setB->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(helper->value, unionSet) == 0)
        {
            insert_set(helper->value, unionSet);
        }
    }
    return unionSet;
}

set *make_intersection(set *setA, set *setB)
{
    set *helper;
    set *intersection_set = malloc (sizeof (set));
    for (helper = setA->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(helper->value, setB) != 0)
        {
            insert_set(helper->value, intersection_set);
        }
    }
    return intersection_set;
}

tuple *make_cartesian_product(set *setA, set *setB)
{
    set *helperA;
    set *helperB;
    tuple *cartesian_product = malloc (sizeof (tuple));

    for (helperA = setA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = setB->next; helperB != NULL; helperB = helperB->next)
        {
            insert_tuple(helperA->value, helperB->value, cartesian_product);
        }
    }
    return cartesian_product;
}

tuple *greater_than(set *setA, set *setB)
{
    set *helperA;
    set *helperB;
    tuple *greater_than = malloc (sizeof (tuple));

    for (helperA = setA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = setB->next; helperB != NULL; helperB = helperB->next)
        {
            if (helperA->value > helperB->value)
            {
                insert_tuple(helperA->value, helperB->value, greater_than);
            }
        }
    }
    return greater_than;
}

tuple *less_than(set *setA, set *setB)
{
    set *helperA;
    set *helperB;
    tuple *less_than = malloc (sizeof (tuple));

    for (helperA = setA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = setB->next; helperB != NULL; helperB = helperB->next)
        {
            if (helperA->value < helperB->value)
            {
                insert_tuple(helperA->value, helperB->value, less_than);
            }
        }
    }
    return less_than;
}

tuple *relations_equals(set *setA, set *setB)
{
    set *helperA;
    set *helperB;
    tuple *equals_tuple = malloc (sizeof (tuple));

    for (helperA = setA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = setB->next; helperB != NULL; helperB = helperB->next)
        {
            if (helperA->value == helperB->value)
            {
                insert_tuple(helperA->value, helperB->value, equals_tuple);
            }
        }
    }
    return equals_tuple;
}

tuple *relations_square(set *setA, set *setB)
{
    set *helperA;
    set *helperB;
    tuple *square_tuple = malloc (sizeof (tuple));

    for (helperA = setA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = setB->next; helperB != NULL; helperB = helperB->next)
        {
            if (helperA->value * helperA->value == helperB->value)
            {
                insert_tuple(helperA->value, helperB->value, square_tuple);
            }
        }
    }
    return square_tuple;
}

tuple *relations_square_root(set *setA, set *setB)
{
    set *helperA;
    set *helperB;
    tuple *square_root_tuple = malloc (sizeof (tuple));

    for (helperA = setA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = setB->next; helperB != NULL; helperB = helperB->next)
        {
            if (helperA->value == helperB->value * helperB->value)
            {
                insert_tuple(helperA->value, helperB->value, square_root_tuple);
            }
        }
    }
    return square_root_tuple;
}

set *make_difference(set *setA, set *setB)
{
    set *helper;
    set *difference_set = malloc (sizeof (set));
    for (helper = setA->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(helper->value, setB) == 0)
        {
            insert_set(helper->value, difference_set);
        }
    }
    return difference_set;
}

set *undo_cartesian_product(tuple *cartesian_tuple)
{
    tuple *helper;
    set *setA = malloc (sizeof (set));

    for (helper = cartesian_tuple->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(helper->firstValue, setA) == 0)
        {
            insert_set(helper->firstValue, setA);
        }
    }
    return setA;
}

int *set_to_vector(set *setA, int set_size)
{
    set *helper;
    int *newSet = malloc (set_size * sizeof (int));
    int count = 0;
    for (helper = setA->next; helper != NULL; helper = helper->next)
    {
        newSet[count] = helper->value;
        count++;
    }
    return newSet;
}

powerSet *make_power_set(set *setA)
{
    int *newSet = set_to_vector(setA, len(setA));
    unsigned int pow_set_size = pow(2, len(setA));
    int counter, j;
    powerSet *pSet = malloc (sizeof (powerSet));
    set *helper;

    for(counter = 0; counter < pow_set_size; counter++)
    {
        helper = malloc (sizeof (set));
        for(j = 0; j < len(setA); j++)
        {
            if(counter & (1<<j))
            {
                insert_set(newSet[j], helper);
            }
        }
        insert_power_set(helper, pSet);
    }
    return pSet;
}

set *undo_power_set(powerSet *pSet)
{
    powerSet *helper;
    set *undo_set = malloc(sizeof (set));
    for (helper = pSet->next; helper != NULL; helper = helper->next)
    {
        undo_set = make_union(undo_set, helper->setA);
    }
    return undo_set;
}

int main()
{
    setlocale(LC_ALL, "");

    set *set_A = malloc (sizeof (set));
    set *set_B = malloc (sizeof (set));
    int key = -1;
    int set1[] = {3, 2, 1, 0};
    int set2[] = {6, 5, 4, 3};

    insert_set_in_list(set1, 4, set_A);
    insert_set_in_list(set2, 4, set_B);

    tuple *cartesian_product = make_cartesian_product(set_A, set_B);

    while (key != 0)
    {
        printf("What do you want to do? \n"
               "1-)Print set A \n"
               "2-)Print set B \n"
               "3-)To check if an element belongs to A \n"
               "4-)To check if set A contains set B \n"
               "5-)Print A union B \n"
               "6-)Print A intersection B \n"
               "7-)Print A cartesian product B \n"
               "8-)To check if set A contains and equals set Y \n"
               "9-)Print A - B \n"
               "10-)To undo an cartesian product and print it \n"
               "11-)To print powerSet A \n"
               "12-)To undo powerSet and print it \n"
               "0-)Exit \n");
        scanf("%d", &key);

        switch (key) {
            case 1:
                printf("A = ");
                print_set(set_A);
                break;

            case 2:
                printf("B = ");
                print_set(set_B);
                break;

            case 3:
                printf("Type the element: \n");
                int element;
                scanf("%d", &element);
                if (check_pertinence(element, set_A) != 0)
                {
                    printf("%d belongs to the set", element);
                }
                else
                {
                    printf("%d does not belongs to the set", element);
                }
                break;

            case 4:
                if (check_contains(set_A, set_B) != 0)
                {
                    printf("A contains B");
                }
                else
                {
                    printf("A does not contains B");
                }
                break;

            case 5:
                printf("A U B = ");
                set *union_set = make_union(set_A, set_B);
                print_set(union_set);
                break;

            case 6:
                printf("A ∩ B = ");
                set *intersection_set = make_intersection(set_A, set_B);
                print_set(intersection_set);
                break;

            case 7:
                printf("A x B = ");
                print_tuple(cartesian_product);
                break;

            case 8:
                if (check_contains_equals(set_A, set_B) == 1)
                {
                    printf("A contains and is equals to B");
                } else if (check_contains_equals(set_A, set_B) == 2)
                {
                    printf("A contains and is not equals to B");
                } else
                {
                    printf("A does not contains B");
                }
                break;

            case 9:
                printf("A - B = ");
                set *difference_set = make_difference(set_A, set_B);
                print_set(difference_set);
                break;

            case 10:
                printf("Set A = ");
                set *setA = undo_cartesian_product(cartesian_product);
                print_set(setA);
                break;

            case 11:
                printf("PowerSet A = ");
                powerSet *pow = make_power_set(set_A);
                print_power_set(pow);
                break;

            case 12:
                printf("Undo PowerSet A = ");
                powerSet *pSet = make_power_set(set_A);
                set *undo_set = undo_power_set(pSet);
                print_set(undo_set);
                break;

            default:
                break;
        }
        printf("\n ----------------------\n");
    }

    return 0;
}


