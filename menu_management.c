#include <stdio.h>
#include <stdlib.h>
#include "include\prototypes.h"

void main_menu_text()
{
    clear_screen();
    printf("[1] - Contabilizar o número de linhas de um ficheiro\n");
    printf("[2] - Contabilizar o número de palavras de um ficheiro\n");
    printf("[3] - Contabilizar o número de caracteres de um ficheiro\n");
    printf("[4] - Contabilizar o número de caracteres de um ficheiro introduzido pelo utilizador\n");
    printf("[0] - Sair\n");
}

void main_menu()
{
    FILE *file;
    char file_name[50];
    int option;
    do
    {
        main_menu_text();
        printf("Insira a opção: ");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
            case 1: 
                break;
            case 2: 
                break;
            case 3: 
                break;
            case 4: 
                break;
            case 0: clear_screen();
                break;
            default: invalid_option();
                break;
        }
    } while (option != 0);
}

void insert_any_key()
{
    printf("Insira qualquer tecla para continuar...");
    getchar();
    fflush(stdin);
}

void invalid_option()
{
    clear_screen();
    printf("Opção inválida!\n");
    insert_any_key();
}