#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/queue.h"

void new_student(student_queue_t* q, student_t s)
{
    if(q == NULL) return;

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