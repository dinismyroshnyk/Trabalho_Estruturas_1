// --- system specific commands ---
#ifdef _WIN32 // assume Windows
    #define clear_screen() system("cls")
#else // assume POSIX or similar
    #define clear_screen() system("clear")
#endif

// --- includes ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- defines ---
#define DIM 10
#define MAX_PURCHASES 1000

// --- structs ---
typedef struct
{
    char name[50];
    char address[50];
}store;

typedef struct
{
    int value;
    char date[8];
    store store;
} purchase;

typedef struct
{
    int customer_id;
    float total_spent;
    int vouchers;
    purchase purchases[MAX_PURCHASES];
} Card;

typedef struct
{
    char name[50];
    char phone[9];
    char email[50];
    char nif[9];
    bool has_card;
    Card card;
} client;


// --- prototypes ---
void main_menu();
void costmers_menu();
void save_menu();
void insert_any_key();
void invalid_option();
void clear_buffer();
int read_option();

// --- structs functions ---
client new_client()
{
    client func;
    char resp;
    printf("Name: ");
    clear_buffer();
    fgets(func.name, 50, stdin);
    printf("Email: ");
    clear_buffer();
    fgets(func.email, 50, stdin);
    printf("Phone: ");
    clear_buffer();
    fgets(func.phone, 9, stdin);
    printf("NIF: ");
    clear_buffer();
    fgets(func.nif, 9, stdin);
    printf("Has Card(): ");
    clear_buffer();
    fgets(&resp, 2, stdin);
    func.has_card = 's' == resp || 'S' == resp;
    return func;
}

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
    printf("\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500 Manager Client \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n");
    printf("\u2502  [1] - New Client                  \u2502\n");
    printf("\u2502  [2] - Disable Card                \u2502\n");
    printf("\u2502  [3] - List Customer               \u2502\n");
    printf("\u2502  [4] - Costomer Menu               \u2502\n"); // --- menu de cliente ---
    printf("\u2502  [5] - Order Customers ↗           \u2502\n");
    printf("\u2502  [6] - Save as...                  \u2502\n"); // --- menu dde salvar ---
    printf("\u2502  [0] - Sair                        \u2502\n");
    printf("\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n");
    printf("\n>>> ");
}

void customers_menu_text()
{
    clear_screen();
    printf("\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500 Client \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n");
    printf("\u2502  [1] -  Edit Data                  \u2502\n");
    printf("\u2502  [2] -  View All Purchases         \u2502\n");
    printf("\u2502  [3] -  Bank Statement             \u2502\n");
    printf("\u2502  [4] -  View Coupons Available     \u2502\n");
    printf("\u2502  [0] -  Sair                       \u2502\n");
    printf("\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n");
    printf("\n>>> ");
}

void save_menu_text()
{
    clear_screen();
    printf("\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500 Save as... \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n");
    printf("\u2502  [1] -  Save as .csv               \u2502\n");
    printf("\u2502  [2] -  Save as .csv               \u2502\n");
    printf("\u2502  [3] -  Save as .html              \u2502\n");
    printf("\u2502  [0] -  Sair                       \u2502\n");
    printf("\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n");
    printf("\n>>> ");
}

// --- --- menu functions --- ---
void main_menu()
{
   // client func[DIM]; // --- array de clientes ---
    int option;
    do
    {
        main_menu_text();
        option = read_option();
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
            costmers_menu();
            
            insert_any_key();
            break;
        case 5:
            clear_screen();
            printf("Teste 5\n");
            insert_any_key();
            break;
        case 6:
            clear_screen();
            save_menu_text();
            
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

void costmers_menu()
 {
    int option;
    do
    {
        customers_menu_text();
        option = read_option();
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
    
    }while (option != 0);
 }

void save_menu()
{
    int option;
    do
    {
        save_menu_text();
        option = read_option();
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

int read_option()
{
    int option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%d%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789")) {
        option = -1; // set option to an invalid value
    };
    return option;
}