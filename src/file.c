#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/file.h"

void load_db(student_queue_t* q)
{   
    FILE *f = fopen(FILEPATH, "r");
    if(f == NULL) return;

    student_t s;
    while (fscanf(f, "%99s %19s %19s %10s %c %f", s.name, s.birth, s.course, s.number, &s.year, &s.balance) == 6)
    {
        student_node_t* node_p = (student_node_t*) malloc(sizeof(student_node_t));

        strcpy(node_p->student.name, s.name);
        strcpy(node_p->student.birth, s.birth);
        strcpy(node_p->student.course, s.course);
        strcpy(node_p->student.number, s.number);
        node_p->student.year = s.year;
        node_p->student.balance = s.balance;
        node_p->student.purchases = NULL;
        node_p->prox = NULL;

        if(q->init == NULL) q->init = node_p;
        else {
            student_node_t* node_c = q->init;
            while(node_c->prox != NULL) node_c = node_c->prox;
            node_c->prox = node_p;
        }
    }

    fclose(f);
}

void save_db(student_queue_t* q)
{
    FILE *f=fopen(FILEPATH, "w");
    if(f == NULL) return;

    student_node_t* node_c=q->init;

    while(node_c!=NULL)
    {
        student_t s=node_c->student;
        fprintf(f, "%s %s %s %s %c %.2f\n", s.name, s.birth, s.course, s.number, s.year, s.balance);
        node_c=node_c->prox;
    }
    fclose(f);
}



   
