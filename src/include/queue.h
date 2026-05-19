#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include "data.h"

void new_student(student_queue_t* q, student_t s);
void remove_student(student_queue_t* q, const char* student_name);
void sort_alphabetically(student_queue_t* q);

#endif