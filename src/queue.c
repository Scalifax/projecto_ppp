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

    if(q->init == NULL){
        q->init = node_p;
        q->end = node_p;
        q->size = 1;
    }
    else{
        student_node_t* node_c = q->init;
        while(node_c->prox != NULL) node_c = node_c->prox;
        node_c->prox = node_p;

        q->end = node_p;
        q->size++;
    }
}

void remove_student(student_queue_t* q, const char* student_name)
{
    if(q == NULL || q->init == NULL) return;

    student_node_t* node_c = q->init, *node_o = NULL;
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

    // Remove o elemento.
    if(node_c == q->init){
        q->init = node_c->prox;
    }
    else if(node_c == q->end){
        node_o->prox = NULL;
        q->end = node_o;
    }
    else{
        node_o->prox = node_c->prox;
    }
    q->size--;

    // Libera na memória o nó removido.
    free(node_c);
}

void sort_alphabetically(student_queue_t* q) 
{
    if(q == NULL || q->init == NULL || q->init->prox == NULL) return;

    int swapped = 1;
    student_node_t* node_o = NULL;

    while(swapped)
    {
        swapped = 0;
        student_node_t* node_c = q->init;

        while(node_c->prox != node_o)
        {
            if(strcmp(node_c->student.name, node_c->prox->student.name) > 0)
            {
                student_t temp = node_c->student;
                node_c->student = node_c->prox->student;
                node_c->prox->student = temp;

                swapped = 1;
            }

            node_c = node_c->prox;
        }

        node_o = node_c;
    }
}