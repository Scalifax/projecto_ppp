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

void remove_student(student_queue_t* q, const char* student_name)
{
    if(q == NULL) return;

    student_node_t* node_o = NULL;
    student_node_t* node_c = q->init;
    while(strcmp(node_c->student.name, student_name) != 0)
    {
        // Passa pro próximo elemento da fila.
        // Se for o último elemento retorna.
        if(node_c->prox != NULL){
            node_o = node_c;
            node_c = node_c->prox;
        }
        else{
            printf("Estudante não encontrado\n");
            return;
        }
    }
    node_o->prox = node_c->prox;
    free(node_c);
}