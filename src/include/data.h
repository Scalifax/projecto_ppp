#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>

// Compras (valor, descrição, data):
typedef struct purchase_t {
    int value;
    char description[100];
    char date[20];
} purchase_t;

typedef struct purchase_node_t {
    purchase_t purchase;
    struct purchase_node_t *prox;
} purchase_node_t;

// Estudante (nome, data de nascimento, curso, ano, número, saldo):
typedef struct student_t {
    char name[100];
    char birth[20];
    char course[20];
    char number[11];
    char year;
    float balance;
    purchase_node_t *purchases;
} student_t;

typedef struct student_node_t {
    student_t student;
    struct student_node_t *prox;
} student_node_t;

typedef struct student_queue_t {
    student_node_t *init;
    student_node_t *end;
    size_t size;
} student_queue_t;

#endif