#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include "queue.h"
#include "data.h"

#define USERS_FILEPATH "db/users.txt"
#define PURCHASES_FILEPATH "db/purchases.txt"

void load_db(student_queue_t* q);
void save_db(student_queue_t* q);
void load_purchases(student_queue_t* q);
void save_purchases(student_queue_t* q);

#endif