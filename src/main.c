#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/data.h"
#include "include/file.h"
#include "include/queue.h"

#define DEBUG    0
#define MAX_ARGS 10

student_queue_t student_queue;

// Função de Debug:
void print_debug()
{
    printf("    > DEBUG: init: %p  | name:%s\n", student_queue.init, student_queue.init->student.name);
    printf("    > DEBUG: end:  %p  | name:%s\n", student_queue.end, student_queue.end->student.name);
    printf("    > DEBUG: size: %ld\n", student_queue.size);
}

// Funções para converter uma string ("10.99") em float (10.99):
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

        // Verifica se é dígito.
        if(str[i] < '0' || str[i] > '9') return;

        int digit = str[i] - '0';
        if(!has_decimal){
            // Parte inteira
            num = num * 10.0f + digit;
        } 
        else{ 
            // Parte decimal
            num += digit * decimal_factor;
            decimal_factor *= 0.1f;
        }

        i++;
    }

    *result = num * sign;
}

// Função para limpar os argumentos da linha de comando:
void clean_args(char** args)
{
    for(int i = 0; i < MAX_ARGS; i++)
        args[i] = NULL;
}

int main()
{
    // Carrega os estudantes que estão no banco de dados.
    load_db(&student_queue);

    // Carrega as compras dos estudantes que estão no ficheiro.
    load_purchases(&student_queue);

    char cmd[128];          // Buffer para guardar o comando digitado.
    char* args[MAX_ARGS];   // Array de ponteiros para os argumentos do comando.
    printf("Comandos disponíveis (add, list, remove, purchase, deposit, exit)\n");

    // Loop Principal.
    while(1)
    {   
        // Lê o comando digitado pelo utilizador.
        printf("> ");
        if(fgets(cmd, sizeof(cmd), stdin) == NULL){
            printf("Error: falha ao ler comando.\n");
            return 1;
        }
        cmd[strcspn(cmd, "\n")] = '\0'; // Remove o '\n' do fgets
        
        if(cmd[0] == '\0') continue;    // Verifica se algo foi digitado

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

            // Verifica se os argumentos não são vazios.
            if(!args[1] || !args[2] || !args[3] || !args[4] || !args[5] || !args[6])
            {
                printf("Error: faltam argumentos para o comando 'add'\n");
                clean_args(args);
                continue;
            }

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
            
            // Função para organizar a lista em ordem alfabética.
            sort_student_alphabetically(&student_queue);

            printf("Fila atual de estudante (ordem alfabética):\n");
            student_node_t* node_c = student_queue.init;
            while(node_c != NULL)
            {
                printf(" * %s %s %s %s %c %.2f\n", node_c->student.name, node_c->student.birth,
                    node_c->student.course, node_c->student.number, node_c->student.year, node_c->student.balance);
                node_c = node_c->prox;
            }
        }
        else if(!strcmp(args[0], "remove")){
            // Código para remover um estudante da fila
            
            // Verifica se o argumento não é vazio.
            if(!args[1])
            {
                printf("Error: faltam argumentos para o comando 'remove'\n");
                clean_args(args);
                continue;
            }

            // Chama a função de remover o estudante.
            remove_student(&student_queue, args[1]);
        }
        else if(!strcmp(args[0], "purchase")){
            // Código para realizar uma compra para um estudante.

            // Verifica se os argumentos não são vazios.
            if(!args[1] || !args[2] || !args[3] || !args[4])
            {
                printf("Error: faltam argumentos para o comando 'purchase'\n");
                clean_args(args);
                continue;
            }

            purchase_t purchase;
            float f;
            str_to_float(args[2], &f);
            purchase.value = f;
            strcpy(purchase.description, args[3]);
            strcpy(purchase.date, args[4]);

            // Chama a função para criar a nova compra.
            new_student_purchase(&student_queue, args[1], purchase, true);
        }
        else if(!strcmp(args[0], "deposit")){
            // Código para realizar um depósito para um estudante.

            // Verifica se os argumentos não são vazios.
            if(!args[1] || !args[2] || !args[3])
            {
                printf("Error: faltam argumentos para o comando 'purchase'\n");
                clean_args(args);
                continue;
            }

            purchase_t purchase;
            float f;
            str_to_float(args[2], &f);
            purchase.value = -f;
            strcpy(purchase.description, "depósito.");
            strcpy(purchase.date, args[3]);

            // Chama a função para criar a nova compra (no caso de ser um depósisto, é uma compra com valor negativo).
            new_student_purchase(&student_queue, args[1], purchase, true);
        }
        else if(!strcmp(args[0], "exit")){
            // Sequência de eventos para encerrar o programa.

            printf("Encerrando o programa.\n");
            save_purchases(&student_queue);
            save_db(&student_queue);
            break;
        }
        else{
            printf("Comando desconhecido.\n");
        }

        if(DEBUG) print_debug();

        // Limpa os argumentos para o próximo loop.
        clean_args(args);
    }

    return 0;
}