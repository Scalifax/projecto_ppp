#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/data.h"
#include "include/file.h"
#include "include/queue.h"

#define MAX_ARGS 10

student_queue_t student_queue;

void str_to_float(const char *str, float *result)
{
    float num = 0.0f;
    float decimal_factor = 0.1f;
    int sign = 1;
    int i = 0;
    int has_decimal = 0;

    // Sinal negativo.
    if(str[i] == '-'){
        sign = -1;
        i++;
    }

    // String vazia ou apenas "-".
    if(str[i] == '\0') return;

    while(str[i] != '\0')
    {
        // Ponto decimal.
        if(str[i] == '.'){

            // Dois pontos é inválido.
            if (has_decimal) return;
            has_decimal = 1;
            
            i++;
            continue;
        }

        // Verifica se é dígito
        if(str[i] < '0' || str[i] > '9') return;

        int digit = str[i] - '0';
        if(!has_decimal){ // Parte inteira
            num = num * 10.0f + digit;
        } 
        else{ // Parte decimal
            num += digit * decimal_factor;
            decimal_factor *= 0.1f;
        }

        i++;
    }

    *result = num * sign;
}

int main()
{
    // Carrega os estudantes que estão no banco de dados.
    load_db(&student_queue);

    char cmd[128];          // Buffer para guardar o comando digitado.
    char* args[MAX_ARGS];   // Array de ponteiros para os argumentos do comando.
    printf("Comandos disponíveis (add, remove, purchase, deposit)\n");

    // Loop Principal.
    while(1)
    {   
        // Lê o comando digitado pelo utilizador.
        printf("> ");
        if(fgets(cmd, sizeof(cmd), stdin) == NULL){
            printf("Erro ao ler comando.\n");
            return 1;
        }
        cmd[strcspn(cmd, "\n")] = '\0'; // Remove o '\n' do fgets
        
        int argi = 0;
        char *token = strtok(cmd, " ");

        // Carrega os os argumentos no array "args".
        while(token != NULL && argi < MAX_ARGS)
        {
            args[argi] = token;
            argi++;
            token = strtok(NULL, " ");
        }

        // Parse do comando.
        if(!strcmp(args[0], "add")){
            // Código para criar um novo estudante na fila.
            // Cria uma nova estrutra de estudante e copia os argumentos.
            student_t s;
            strcpy(s.name, args[1]);
            strcpy(s.birth, args[2]);
            strcpy(s.course, args[3]);
            strcpy(s.number, args[4]);
            s.year = *args[5];
            float f;
            str_to_float(args[6], &f);
            s.balance = f;

            // Chama a função para criar na fila o estudante.
            new_student(&student_queue, s);
        }
        else if(!strcmp(args[0], "list")){
            // Código para exibir todos os estudantes da fila.
            printf("Fila atual de estudante:\n");
            student_node_t* node_c = student_queue.init;
            while(node_c != NULL)
            {
                printf("%s %s %s %s %c %.2f\n", node_c->student.name, node_c->student.birth,
                    node_c->student.course, node_c->student.number, node_c->student.year, node_c->student.balance);
                node_c = node_c->prox;
            }
        }
        else if(!strcmp(args[0], "remove")){
            // TODO
        }
        else if(!strcmp(args[0], "purchase")){
            // TODO
        }
        else if(!strcmp(args[0], "deposit")){
            // TODO
        }
        else if(!strcmp(args[0], "exit")){
            printf("Encerrando o programa.\n");
            break;
        }
        else{
            printf("Comando desconhecido.\n");
        }
    }

    return 0;
}