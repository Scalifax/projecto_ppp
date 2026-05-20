#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/queue.h"

void free_student_node(student_node_t* n)
{
    if(n->student.purchases != NULL)
    {
        purchase_node_t *purchase_c = n->student.purchases, *purchase_o = NULL;
        while(purchase_c != NULL)
        {
            purchase_o = purchase_c;
            purchase_c = purchase_c->prox;
            free(purchase_o);
        }
    }

    free(n);
}

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
            printf("Estudante não encontrado.\n");
            return;
        }
    }

    // Remove o elemento.
    if (q->init == q->end){
        q->init = NULL;
        q->end = NULL;
    }
    else if (node_c == q->init){
        q->init = node_c->prox;
    }
    else if (node_c == q->end){
        node_o->prox = NULL;
        q->end = node_o;
    }
    else{
        node_o->prox = node_c->prox;
    }
    q->size--;

    // Libera na memória o nó removido.
    free_student_node(node_c);
}

void sort_student_alphabetically(student_queue_t* q) 
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

void new_student_purchase(student_queue_t* q, const char* student_name, purchase_t p, bool op_flag)
{
    if(q == NULL || q->init == NULL) return;

    // Acha o estudante.
    student_node_t* node_c = q->init;
    while(strcmp(node_c->student.name, student_name) != 0)
    {
        // Passa pro próximo elemento da fila.
        // Se for o último elemento retorna.
        if(node_c->prox != NULL)
            node_c = node_c->prox;
        else{
            printf("Estudante não encontrado.\n");
            return;
        }
    }

    // Se a flag estiver True, subtrai o valor da compra (ou depósito) do saldo do estudante.
    if(op_flag) node_c->student.balance -= p.value;

    // Cria o novo nó da fila de compras.
    purchase_node_t* node_p = (purchase_node_t*) malloc(sizeof(purchase_node_t));

    node_p->purchase.value = p.value;
    strcpy(node_p->purchase.description, p.description);
    strcpy(node_p->purchase.date, p.date);
    node_p->prox = NULL;

    if(node_c->student.purchases == NULL)
        node_c->student.purchases = node_p;
    else{
        purchase_node_t* p_node_c = node_c->student.purchases;
        while(p_node_c->prox != NULL) p_node_c = p_node_c->prox;
        p_node_c->prox = node_p;
    }
}