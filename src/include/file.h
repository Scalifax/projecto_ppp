#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include "data.h"

#define FILEPATH "db/users.txt"

void load_db(student_queue_t* q);
void save_db(student_queue_t* q);

#endif