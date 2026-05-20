#include <stdio.h>
#include "include/file.h"
#include "include/queue.h"

void load_db(student_queue_t* q)
{   
    FILE *f = fopen(USERS_FILEPATH, "r");
    if(f == NULL) return;

    student_t s;
    while (fscanf(f, "%99s %19s %19s %10s %c %f", s.name, s.birth, s.course, s.number, &s.year, &s.balance) == 6)
        new_student(q, s);

    fclose(f);
}

void save_db(student_queue_t* q)
{
    FILE *f = fopen(USERS_FILEPATH, "w");
    if(f == NULL) return;

    student_node_t* node_c = q->init;

    while(node_c != NULL)
    {
        student_t s = node_c->student;
        fprintf(f, "%s %s %s %s %c %f\n", s.name, s.birth, s.course, s.number, s.year, s.balance);
        node_c = node_c->prox;
    }
    
    fclose(f);
}

void load_purchases(student_queue_t* q)
{
    FILE *f = fopen(PURCHASES_FILEPATH, "r");
    if(f == NULL) return;

    char name[100]; purchase_t purchase;
    while (fscanf(f, "%99s %f %99s %19s", name, &purchase.value, purchase.description, purchase.date) == 4)
        new_student_purchase(q, name, purchase, false);

    fclose(f);
}

void save_purchases(student_queue_t* q)
{
    FILE *f = fopen(PURCHASES_FILEPATH, "w");
    if(f == NULL) return;

    student_node_t* node_c = q->init;

    while(node_c != NULL)
    {
        purchase_node_t* purchase_c = node_c->student.purchases;

        while(purchase_c != NULL)
        {
            fprintf(f, "%s %f %s %s\n", node_c->student.name, purchase_c->purchase.value, 
                purchase_c->purchase.description, purchase_c->purchase.date);
            purchase_c = purchase_c->prox;
        }

        node_c = node_c->prox;
    }

    fclose(f);
}