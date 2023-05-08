//
// Created by Fernando Pimenta on 25/03/2023.
//

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

struct element
{
    int value;
    int index;
};

typedef struct reg {
    struct element value;
    struct reg *next;
} set;

typedef struct tup {
    struct element firstValue;
    struct element secondValue;
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

void free_tuple(tuple *tupleA)
{
    tuple *helper;
    for (helper = tupleA->next; helper != NULL; helper = helper->next)
        free(helper);
}

void set_index(set *set_X)
{
    set *helper;
    int index = 0;

    for (helper = set_X->next; helper != NULL; helper = helper->next)
    {
        helper->value.index = index;
        index++;
    }
}

void insert_set(int value, set *n)
{
    set *new;
    new = malloc(sizeof (set));
    new->value.value = value;
    new->next = n->next;
    n->next = new;
    set_index(n);
}

void insert_set_in_list(int *values, int size, set *setX)
{
    for (int i = 0; i < size; i++)
    {
        insert_set(values[i], setX);
    }
}

void insert_tuple(struct element firstValue, struct element secondValue, tuple *n)
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
        printf (" %d", helper->value.value);
    printf(" )");
}

void print_tuple (tuple *set_X) {
    tuple *helper;
    for (helper = set_X->next; helper != NULL; helper = helper->next)
        printf ("( %d, %d )", helper->firstValue.value, helper->secondValue.value);
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
        if (element == helper->value.value)
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
        if (check_pertinence(setA->value.value, setB) == 0)
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
        insert_set(helper->value.value, unionSet);
    }
    for (helper = setB->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(helper->value.value, unionSet) == 0)
        {
            insert_set(helper->value.value, unionSet);
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
        if (check_pertinence(helper->value.value, setB) != 0)
        {
            insert_set(helper->value.value, intersection_set);
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

int **create_matrix(int rows, int columns)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    int row;

    for (row = 0; row < rows; row++) {
        matrix[row] = (int *)malloc(columns * sizeof(int));
    }

    return matrix;
}

void free_matrix(int **matrix, int rows)
{
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < rows; col++)
        {
            free(matrix[row][col]);
        }
    }
 }

 void print_matrix(int **matrix)
 {
    printf("\n");
    for(int x = 0 ; x < 4 ; x++) {
        printf(" (");
        for(int y = 0 ; y < 4 ; y++){
            printf("%d     ", matrix[x][y]);
        }
        printf(")\n");
    }
 }

void fill_matrix(tuple *relation_set, int **matrix)
{
    tuple *helper;

    for (helper = relation_set->next; helper != NULL; helper = helper->next)
    {
        matrix[helper->firstValue.index][helper->secondValue.index] = 1;
    }
}

int is_functional(int **matrix, int size_i, int size_j)
{
    int aux_functional = 0;

    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            if (matrix[i][j] != 0)
            {
                aux_functional++;
            }
        }
        if (aux_functional > 1)
        {
            return 0;
        }
        aux_functional = 0;
    }
    return 1;
}

int is_injective(int **matrix, int size_i, int size_j)
{
    int aux_functional = 0;

    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            if (matrix[j][i] != 0)
            {
                aux_functional++;
            }
        }
        if (aux_functional > 1)
        {
            return 0;
        }
        aux_functional = 0;
    }
    return 1;
}

int is_total(int **matrix, int size_i, int size_j)
{
    int aux_functional = 0;

    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            if (matrix[i][j] != 0)
            {
                aux_functional++;
            }
        }
        if (aux_functional == 0)
        {
            return 0;
        }
        aux_functional = 0;
    }
    return 1;
}

int is_surjective(int **matrix, int size_i, int size_j)
{
    int aux_functional = 0;

    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            if (matrix[j][i] != 0)
            {
                aux_functional++;
            }
        }
        if (aux_functional == 0)
        {
            return 0;
        }
        aux_functional = 0;
    }
    return 1;
}

int is_monomorphism(int **matrix, int size_i, int size_j)
{
    if (is_total(matrix, size_i, size_j) == 1 &&
        is_injective(matrix, size_i, size_j))
    {
        return 1;
    }
    return 0;
}

int is_epimorphisms(int **matrix, int size_i, int size_j)
{
    if (is_functional(matrix, size_i, size_j) == 1 &&
        is_surjective(matrix, size_i, size_j))
    {
        return 1;
    }
    return 0;
}

int is_isomorphism(int **matrix, int size_i, int size_j)
{
    if (is_monomorphism(matrix, size_i, size_j) == 1 &&
        is_epimorphisms(matrix, size_i, size_j))
    {
        return 1;
    }
    return 0;
}

void set_classifications(tuple *relation_set, int size_i, int size_j)
{
    print_tuple(relation_set);
    int** matrix = create_matrix(size_i, size_j);
    fill_matrix(relation_set, matrix);

    if (is_functional(matrix, size_i, size_j) == 1)
    {
        printf("\n Is functional");
    }
    if (is_injective(matrix, size_i, size_j) == 1)
    {
        printf("\n Is injective");
    }
    if (is_total(matrix, size_i, size_j) == 1)
    {
        printf("\n Is total");
    }
    if (is_surjective(matrix, size_i, size_j) == 1)
    {
        printf("\n Is surjective");
    }
    if (is_monomorphism(matrix, size_i, size_j) == 1)
    {
        printf("\n Is monomorphism");
    }
    if (is_epimorphisms(matrix, size_i, size_j) == 1)
    {
        printf("\n Is epimorphisms");
    }
    if (is_isomorphism(matrix, size_i, size_j) == 1)
    {
        printf("\n Is isomorphism");
    }
    free_matrix(matrix, size_i);
    free_tuple(relation_set);
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
            if (helperA->value.value > helperB->value.value)
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
            if (helperA->value.value < helperB->value.value)
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
            if (helperA->value.value == helperB->value.value)
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
            if (helperA->value.value * helperA->value.value == helperB->value.value)
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
            if (helperA->value.value == helperB->value.value * helperB->value.value)
            {
                insert_tuple(helperA->value, helperB->value, square_root_tuple);
            }
        }
    }
    return square_root_tuple;
}

tuple *relations_compose(tuple *tupleA, tuple *tupleB)
{
    tuple *helperA;
    tuple *helperB;
    tuple *relations_compose = malloc (sizeof (tuple));

    for (helperA = tupleA->next; helperA != NULL; helperA = helperA->next)
    {
        for (helperB = tupleB->next; helperB != NULL; helperB = helperB->next)
        {
            if (helperA->secondValue.value == helperB->firstValue.value)
            {
                insert_tuple(helperA->firstValue, helperB->secondValue, relations_compose);
            }
        }
    }
    return relations_compose;
}

set *make_difference(set *setA, set *setB)
{
    set *helper;
    set *difference_set = malloc (sizeof (set));
    for (helper = setA->next; helper != NULL; helper = helper->next)
    {
        if (check_pertinence(helper->value.value, setB) == 0)
        {
            insert_set(helper->value.value, difference_set);
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
        if (check_pertinence(helper->firstValue.value, setA) == 0)
        {
            insert_set(helper->firstValue.value, setA);
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
        newSet[count] = helper->value.value;
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
    set *set_C = malloc (sizeof (set));
    int key = -1;
    int set1[] = {3, 2, 1, 0};
    int set2[] = {6, 5, 4, 3};
    int set3[] = {10, 9, 8, 3};

    insert_set_in_list(set1, 4, set_A);
    insert_set_in_list(set2, 4, set_B);
    insert_set_in_list(set3, 4, set_C);

    tuple *cartesian_product = make_cartesian_product(set_A, set_B);

    while (key != 0)
    {
        printf("\n ----------------------\n");
        printf("What do you want to do? \n"
               "1-)A greater than B \n"
               "2-)A smaller than B \n"
               "3-)A equals to B \n"
               "4-)B equals the square of A \n"
               "5-)B equals the square root of A \n"
               "6-)SoR : A -> C: \n"
               "13-)To exit\n");
               scanf("%d", &key);

        switch (key) {
            case 1:
                printf("A > B = \n");
                set_classifications(greater_than(set_A, set_B), len(set_A), len(set_B));
                break;

            case 2:
                printf("A < B = \n");
                set_classifications(less_than(set_A, set_B), len(set_A), len(set_B));
                break;

            case 3:
                printf("A = B = \n");
                set_classifications(relations_equals(set_A, set_B), len(set_A), len(set_B));
                break;

            case 4:
                printf("A^2 = B = \n");
                set_classifications(relations_square(set_A, set_B), len(set_A), len(set_B));
                break;

            case 5:
                printf("A^1/2 = B = \n");
                set_classifications(relations_square_root(set_A, set_B), len(set_A), len(set_B));
                break;

            case 6:
                printf("SoR : A -> C = \n");
                set_classifications(relations_compose(relations_equals(set_A, set_B),
                                                      relations_equals(set_B, set_C)), len(set_A), len(set_C));
                break;

            default:
                break;
        }
        printf("\n ----------------------\n");
    }
    return 0;
}


