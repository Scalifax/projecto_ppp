#include <stdio.h>
#include <string.h>
#include "include/data.h"
#include "include/file.h"

student_queue_t student_queue;

int main()
{
    // Carrega os estudantes que estão no banco de dados.
    load_db(&student_queue);
    printf("Arquivo carregado.\n");

    student_node_t node;
    strcpy(node.student.name, "amanda");
    strcpy(node.student.birth, "29/05/2007");
    strcpy(node.student.course, "LEM");
    strcpy(node.student.number, "3456789999");
    node.student.year='1';
    node.student.balance=500.00;
    node.student.purchases=NULL;
    node.prox=NULL;

    student_node_t* node_c = student_queue.init;
    while(node_c->prox != NULL) node_c = node_c->prox;
    node_c->prox = &node;
    save_db(&student_queue);
    printf("Arquivo salvo.\n");

    return 0;
}