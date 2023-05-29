// --- system specific commands ---
#ifdef _WIN32 // assume Windows
    #define clear_screen() system("cls")
#else // assume POSIX or similar
    #define clear_screen() system("clear")
#endif

// --- includes ---
#include <stdio.h>
#include <stdlib.h>

// --- structs ---
typedef struct
{
    int id;
    char name[50];
    char email[50];
    char phone[20];
    char nif[20];
} client;


// --- prototypes ---
void main_menu();
void insert_any_key();
void invalid_option();
void clear_buffer();

// --- main function start---

int main()
{
    main_menu();
    return 0;
}
// --- main function end ---

// --- auxiliary functions ---
// --- --- menu texts --- ---
void main_menu_text()
{
    clear_screen();
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Manager Client \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("[1] - Teste 1\n");
    printf("[2] - Teste 2\n");
    printf("[3] - Teste 3\n");
    printf("[4] - Teste 4\n");
    printf("[0] - Sair\n");
    printf("\n>>> ");
}

// --- --- menu functions --- ---
void main_menu()
{
    int option;
    do
    {
        main_menu_text();
        scanf("%d", &option);
        clear_buffer();
        switch (option)
        {
        case 1:
            clear_screen();
            printf("Teste 1\n");
            insert_any_key();
            break;
        case 2:
            clear_screen();
            printf("Teste 2\n");
            insert_any_key();
            break;
        case 3:
            clear_screen();
            printf("Teste 3\n");
            insert_any_key();
            break;
        case 4:
            clear_screen();
            printf("Teste 4\n");
            insert_any_key();
            break;
        case 0:
            clear_screen();
            printf("Saindo...\n");
            break;
        default:
            invalid_option();
            break;
        }
    } while (option != 0);
}

// --- --- utility functions --- ---
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insert_any_key()
{
    printf("Pressione qualquer tecla para continuar...");
    getchar();
}

void invalid_option()
{
    clear_screen();
    printf("Opção inválida!\n");
    insert_any_key();
}