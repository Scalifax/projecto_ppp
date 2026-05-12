#include <stdio.h>
#include "include/data.h"
#include "include/file.h"

student_queue_t student_queue;

int main()
{
    // Carrega os estudantes que estão no banco de dados.
    load_db(&student_queue);
    
    // TEMPORÁRIO: imprime os estudantes no terminal.
    student_node_t* node_c = student_queue.init;
    while(node_c != NULL)
    {
        printf("%s %s %s %d %d %.2f\n", node_c->student.name, node_c->student.birth,
            node_c->student.course, node_c->student.year, node_c->student.number, node_c->student.balance);
        node_c = node_c->prox;
    }

    return 0;
}