#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

/*
INPUT:
    Node **meals_head: reference of the meal's linked list
    char *name: name of the meal
    int count: number of the meals

METHOD:
    Creates a meal and a node containing that meal. Append it to meal's linked list end.
*/
Node *make_node_meal(Meal *to_meal){
    Node *n = malloc(sizeof(Node *));
    if(n){
        n -> node = to_meal;
        n -> next = NULL;
    }
    return n;
}

Node *make_node_for_phil(Philosopher *to_phil){
    Node *n = malloc(sizeof(Node *));
    if(n){
        n -> node = to_phil;
        n -> next = NULL;
    }
    return n;
}

Meal *make_meal(char *name, int count){
    Meal *n = malloc(sizeof(Meal *));
    if(n){
        n-> name = name;
        n -> count = count;
    }
    return n;
}

Philosopher *make_philo(char *name, char *favorite_meal, int age){
    Philosopher *n = malloc(sizeof(Philosopher *));
    if(n){
        n -> name = name;
        n -> age = age;
        n -> favorite_meal = favorite_meal;
    }
    return n;
}


void add_meal(Node **meals_head, char *name, int count){
    Meal *to_meal; 
    Node *to_add;
    Node *first = *meals_head;
    to_meal= make_meal(name, count);
    to_add = make_node_meal(to_meal);
    
    if(!(*meals_head)){
        *meals_head = to_add;
    }
    
    else{
        while(first->next){
            first = first -> next;
        }
        first -> next = to_add;
    }
    
}

/*
INPUT:
    Node **philosophers_head: reference of the philosopher's linked list
    char *name: name of the philosopher
    char *favorite_meal: favorite meal
    int age: age of the philosopher

METHOD:
    Creates a philosopher and a node containing that philosopher. 
    Append it to philosopher's linked list end.
*/

void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age){
    Philosopher *to_phil; 
    Node *to_add;
    Node *first = *philosophers_head;
    to_phil = make_philo(name, favorite_meal, age);
    to_add = make_node_for_phil(to_phil);
    
    if(!(*philosophers_head)){
        *philosophers_head = to_add;
    }
    
    else{
        while(first->next){
            first = first -> next;
        }
        first -> next = to_add;
    }
}

/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    Node *philosophers: philosopher's linked list

METHOD:
    Places philosophers into a circular linked list in ascending order of ages.
*/
int greatest_age(Node *philosophers){
    Node *first_help = philosophers;
    int age_prev = 0, age_curr;
    
    while(first_help){
        age_curr = (*(Philosopher *)(first_help -> node)).age;
        if(age_prev < age_curr){
            age_prev = age_curr;
        }
        first_help = first_help -> next;
    }
    return age_prev; 
}

Node *waiter(Node **table_head, Node *phil_point, Node *philosophers){
    Node *n = malloc(sizeof(Node));
    Node *cursor;
    Node *follow_up;
    n -> node = phil_point -> node;
    n -> next = NULL;
    
    if(n){
        cursor = *table_head;
        follow_up = NULL;
        while(cursor && (*(Philosopher *)(cursor -> node)).age < (*(Philosopher *)(n -> node)).age){
            follow_up = cursor;
            cursor = cursor->next;
        }
        n -> next = cursor;
        
        if(follow_up){
            follow_up -> next = n;
        }
        
        else{
            *table_head = n;
        }
    }
    
    return n;
}

void place_philosophers(Node **table_head, Node *philosophers){
    Node *traverse = *table_head;
    Node *traverse_2;
    Node *trav_phil = philosophers;
    Node *traverse_3;
    int index = 0;

    while(trav_phil){
        traverse = waiter(table_head, trav_phil, philosophers);
        trav_phil = trav_phil -> next;
        traverse = traverse -> next;
    }

    traverse_3 = *table_head;
    while(traverse_3){
        (*(Philosopher *)(traverse_3->node)).sitting = index;
        index++;
        traverse_3 = traverse_3 -> next;
    }
    
    traverse_2 = *table_head;
    while(traverse_2){
        if((*(Philosopher *)(traverse_2 -> node)).age == greatest_age(philosophers)){
            traverse_2 -> next = *table_head;
            break;
        }
        traverse_2 = traverse_2 ->next;
    }
    
}

/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    int index: index of the philosopher to be removed
    int size_of_table: number of philosophers in the table

METHOD:
    Removes a philosopher from table.
*/
void remove_philosopher(Node **table_head, int index, int size_of_table){
    Node *cursor = *table_head;
    Node *follow_up = NULL;
    Node *cursor_2;
    Node *cursor_initial = *table_head;
    int index_zero = 1, index_others = 0, index_print_2 = 0;

    /*while(index_print_2 < size_of_table){
        cursor_initial = cursor_initial -> next;
        index_print_2++;
    }*/
    
    if(index == 0){
        while(index_zero < size_of_table){
            cursor = cursor -> next;
            index_zero++;
        }
        cursor -> next  = (*table_head) -> next;
        *table_head = (*table_head) -> next;
    }
    
    else{
        cursor_2 = *table_head;
        while(index_others < index){
            follow_up = cursor_2;
            cursor_2 = cursor_2 -> next;
            index_others++;
        }
        follow_up -> next = cursor_2 -> next;
    }
}

/*
INPUT:
    Node *table: Circular linked list
    Node *meals: Meal's linked list

METHOD:
    Serves favorite meals and reduce their counts. Use strcmp function from string.h
*/
void serve_meals(Node *table, Node *meals){
    Node *trav_table = table;
    Node *trav_meal = meals; 
    Node *gobstopper = table;

    while(trav_meal){
        if(!strcmp((*(Meal *) (trav_meal -> node)).name, (*(Philosopher *) (trav_table -> node)).favorite_meal)){
            (*(Meal *) (trav_meal -> node)).count -= 1;
        }
        trav_table = trav_table -> next;
        while(trav_table != gobstopper){
            if(!strcmp((*(Meal *) (trav_meal -> node)).name, (*(Philosopher *) (trav_table -> node)).favorite_meal)){
                (*(Meal *) (trav_meal -> node)).count--;
            }
            trav_table = trav_table -> next;
        }
        trav_meal = trav_meal -> next;    
    }
}

/*
INPUT:
    Node *list: A linked list
    void (*helper_print)(void *): Reference of a helper print function

METHOD:
    Prints items in the linked list using helper print function
*/
void print_list(Node *list, void (*helper_print)(void *)){
    Node *trav = list;
    
    while(trav){
        helper_print(trav-> node);
        trav = trav -> next;
    }
}

/*
INPUT:
    void *meal: void meal pointer

METHOD:
    Cast void pointer to a meal pointer and prints it's content
*/
void print_meal_node(void *meal){
    printf("Name: %s, count: %d\n", ((Meal *) meal) -> name, ((Meal *) meal) -> count);
}

/*
INPUT:
    void *philosopher: void philosopher pointer

METHOD:
    Cast void pointer to a philosopher pointer and prints it's content
*/
void print_philosopher_node(void *philosopher){
    printf("Name: %s, favorite meal: %s, age: %d\n", ((Philosopher *) philosopher) -> name, ((Philosopher *) philosopher) -> favorite_meal, ((Philosopher *) philosopher) -> age);
}

/*
INPUT:
    Node *table: Circular linked list

METHOD:
    Prints the formation as <prev> <current> <next>
*/
void print_table(Node *table){
    int len = get_length(table);
    Node *cursor = table;
    Node *follow_up = NULL;
    Node *follow_up_2 = NULL;
    Node *cursor_2;
    Node *cursor_initial = table;
    int index_zero = 1, index_others = 0, index_print_2 = 0;

    while(index_zero < len+1){
        follow_up = cursor;
        cursor = cursor -> next;
        index_zero++;
    }
    
    printf("%s -> %s -> %s\n", (*(Philosopher *) (follow_up -> node)).name, (*(Philosopher *) (cursor -> node)).name, (*(Philosopher *) ((cursor->next) -> node)).name);
    
    cursor_2 = table;
    while(index_others < len-1){
        follow_up_2 = cursor_2;
        cursor_2 = cursor_2 -> next;
        index_others++;
        printf("%s -> %s -> %s\n", (*(Philosopher *) (follow_up_2 -> node)).name, (*(Philosopher *) (cursor_2 -> node)).name, (*(Philosopher *) ((cursor_2->next) -> node)).name);
    }
    
    
}

/*
INPUT:
    Node *list: A linked list

OUTPUT:
    Size of the linked list in an integer format

METHOD:
    Calculates the size of the linked list and returns it.
*/
int get_length(Node *list){ 
    Node *first_element = list;
    Node *traverse = list;
    int length = 1;
    
    while(1){
        traverse = traverse -> next;
        if(traverse == first_element){
            break;
        }
        length++;
    }
    return length; 
}

/*
INPUT:
    Node *philosophers: Philosopher's linked list

OUTPUT:
    Philosopher pointer at given index.

METHOD:
    Finds the philosopher at given index and returns it's reference.
*/
Philosopher *get_philosopher(Node *philosophers, int index){ return NULL; }
