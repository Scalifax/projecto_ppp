#include <stdio.h>
#include "include/file.h"
#include "include/queue.h"

void load_db(student_queue_t* q)
{   
    FILE *f = fopen(FILEPATH, "r");
    if(f == NULL) return;

    student_t s;
    while (fscanf(f, "%99s %19s %19s %10s %c %f", s.name, s.birth, s.course, s.number, &s.year, &s.balance) == 6)
        new_student(q, s);

    fclose(f);
}