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

// --- definitions ---
#define MAX_PURCHASES 1000

// --- structures ---
typedef struct Store {
    char name[50];
    char address[50];
} Store;

typedef struct Purchase {
    float value;
    char date[8];
    Store store;
} Purchase;

typedef struct Card {
    int customer_id;
    float total_spent;
    int vouchers;
    Purchase purchases[MAX_PURCHASES];
} Card;

typedef struct Client {
    char name[50];
    int phone;
    char email[50];
    int nif;
    bool has_card;
    Card card;
} Client;


// --- prototypes ---
// --- --- main menu functions --- ---
void main_menu();
void main_menu_text();
void register_new_client();
void remove_client();
void list_active_clients();
void client_management_menu();
void sort_by_total_spent();
void save_as_csv_menu();
void (*main_menu_options[])() =
{
    register_new_client, 
    remove_client, 
    list_active_clients, 
    client_management_menu, 
    sort_by_total_spent, 
    save_as_csv_menu
};
// --- --- client management menu functions --- ---
void client_management_menu_text();
void edit_client();
void add_purchase();
void list_purchases();
void purchase_details();
void verify_vouchers();
void (*client_management_menu_options[])() =
{
    edit_client,
    add_purchase,
    list_purchases,
    purchase_details,
    verify_vouchers
};
// --- --- save as csv menu functions --- ---
void save_as_csv_menu_text();
void save_1_store();
void save_all_stores();
void (*save_as_csv_menu_options[])() =
{
    save_1_store,
    save_all_stores
};

// --- --- utility functions --- ---
void insert_any_key();
void invalid_option();
void clear_buffer();
int read_option();
void program_exit();

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
    printf("[1] - Register new client\n");
    printf("[2] - Remove client (deactivate card)\n");
    printf("[3] - List active clients\n");
    printf("[4] - Client management\n");
    printf("[5] - Sort by total spent\n");
    printf("[6] - Save as csv\n");
    //printf("[7] - Register new store\n");
    //printf("[8] - Remove store\n");
    printf("[0] - Exit\n");
    printf("\n>>> ");
}

void client_management_menu_text()
{
    clear_screen();
    printf("[1] - Edit client\n");
    printf("[2] - Add purchase\n");
    printf("[3] - List purchases\n");
    printf("[4] - Purchases details\n");
    printf("[5] - Verify vouchers\n");
    printf("[0] - Back\n");
    printf("\n>>> ");
}

void save_as_csv_menu_text()
{
    clear_screen();
    printf("[1] - Save 1 store\n");
    printf("[2] - Save all stores\n");
    printf("[0] - Back\n");
    printf("\n>>> ");
}

// --- --- main menu functions --- ---
void main_menu()
{
    int option;
    do
    {
        main_menu_text();
        option = read_option();
        clear_buffer();
        if(option >= 1 && option <= 6)
        {
            (*main_menu_options[option-1])();
            insert_any_key();
        }
        else if (option == 0) program_exit();
        else invalid_option();
    } while (option != 0);
}

void register_new_client()
{
    clear_screen();
    printf("Register new client\n");
}

void remove_client()
{
    clear_screen();
    printf("Remove client\n");
}

void list_active_clients()
{
    clear_screen();
    printf("List active clients\n");
}

void client_management_menu()
{
    int option;
    do
    {
        client_management_menu_text();
        option = read_option();
        clear_buffer();
        if(option >= 1 && option <= 5)
        {
            (*client_management_menu_options[option-1])();
            insert_any_key();
        }
        else if (option == 0) main_menu();
        else invalid_option();
    } while (option != 0);
}

void sort_by_total_spent()
{
    clear_screen();
    printf("Sort by total spent\n");
}

void save_as_csv_menu()
{
    int option;
    do
    {
        save_as_csv_menu_text();
        option = read_option();
        clear_buffer();
        if(option >= 1 && option <= 2)
        {
            (*save_as_csv_menu_options[option-1])();
            insert_any_key();
        }
        else if (option == 0) main_menu();
        else invalid_option();
    } while (option != 0);
}

// --- --- client management menu functions --- ---
void edit_client()
{
    clear_screen();
    printf("Edit client\n");
}

void add_purchase()
{
    clear_screen();
    printf("Add purchase\n");
}

void list_purchases()
{
    clear_screen();
    printf("List purchases\n");
}

void purchase_details()
{
    clear_screen();
    printf("Purchase details\n");
}

void verify_vouchers()
{
    clear_screen();
    printf("Verify vouchers\n");
}

// --- --- save as csv menu functions --- ---
void save_1_store()
{
    clear_screen();
    printf("Save 1 store\n");
}

void save_all_stores()
{
    clear_screen();
    printf("Save all stores\n");
}

// --- --- utility functions --- ---
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insert_any_key()
{
    printf("Press any key to continue...");
    getchar();
}

void invalid_option()
{
    clear_screen();
    printf("Invalid option!\n");
    insert_any_key();
}

void program_exit()
{
    clear_screen();
    printf("Exiting...\n");
    exit(0);
}

int read_option()
{
    int option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%d%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789")) {
        option = -1;
    };
    return option;
}