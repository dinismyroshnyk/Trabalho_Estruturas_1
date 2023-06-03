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
#define MAX_STORES 100
#define MAX_CLIENTS 10
#define DISCOUNT 0.15

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
void main_menu_text();                                  // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void register_new_client(Client clients[]);             // WORKING // NOTE - MAY NEED TO BE REWORKED
void remove_client(Client clients[]);                   // WORKING // NOTE - MAY NEED TO BE REWORKED
void list_active_clients(Client clients[]);             // WORKING // NOTE - MAY NEED TO BE REWORKED
void client_management_menu(Client clients[]);
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
void client_management_menu_text();                     // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void edit_client(Client clients[]);                                     // WIP
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
void save_as_csv_menu_text();                           // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void save_1_store();
void save_all_stores();
void (*save_as_csv_menu_options[])() =
{
    save_1_store,
    save_all_stores
};

// --- --- utility functions --- ---
void insert_any_key();                                  // WORKING
void invalid_option();                                  // WORKING
void clear_buffer();                                    // WORKING
int validate_integer();                                 // WORKING
void program_exit();                                    // WORKING
void save_counter_bin(int counter);                     // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
int read_counter_bin();                                 // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
void save_clients_bin(Client client[], int counter);    // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
Client* read_clients_bin(int* counter);                 // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
void set_clients(Client clients[]);                     // TESTING // NOTE: WORKING BUT MAY CHANGE LATER

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
    Client clients[MAX_CLIENTS];
    set_clients(clients);                               // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
    int option;
    do
    {
        main_menu_text();
        option = validate_integer();
        clear_buffer();
        if(option >= 1 && option <= 6)
        {
            (*main_menu_options[option-1])(clients);
            insert_any_key();                           // TODO // FIXME - REMOVE THIS LINE WHEN THE PROGRAM IS FINISHED
        }
        else if (option == 0) program_exit();
        else invalid_option();
    } while (option != 0);
}

void register_new_client(Client clients[])              // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    int counter = read_counter_bin();
    char answer;
    clear_screen();
    if (counter == MAX_CLIENTS)
    {
        printf("The maximum number of clients has been reached.\n");
        printf("Please remove a client to register a new one.\n");
        insert_any_key();
        main_menu();
    }
    printf("Register new client\n");                    // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("Name: ");
    fgets(clients[counter].name, 50, stdin);
    printf("Phone: ");
    clients[counter].phone = validate_integer();
    clear_buffer();
    printf("Email: ");
    scanf("%s", clients[counter].email);
    clear_buffer();
    printf("NIF: ");
    clients[counter].nif = validate_integer();
    clear_buffer();
    while (1)
    {
        printf("The client has a card? (y/n) ");
        scanf("%c", &answer);
        if (answer == 'y' || answer == 'Y') 
        {
            clients[counter].has_card = true;
            clients[counter].card.customer_id = counter;
            clients[counter].card.total_spent = 0;
            clients[counter].card.vouchers = 0;
            clear_buffer();
            break;
        }
        if (answer == 'n' || answer == 'N') 
        {
            clients[counter].has_card = false;
            clients[counter].card.customer_id = counter;
            clients[counter].card.total_spent = 0;
            clients[counter].card.vouchers = 0;
            clear_buffer();
            break;
        }
        else printf("Invalid answer. Please try again.\n");
    };
    save_counter_bin(++counter);
    save_clients_bin(clients, counter);
}

void remove_client(Client clients[])                    // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Remove client\n");                          // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("Customer ID: ");
    int customer_id = validate_integer();
    clear_buffer();
    if (customer_id > read_counter_bin() || customer_id < 1)
    {
        printf("Invalid customer ID.\n");
        insert_any_key();
        main_menu();
    }
    if (clients[customer_id - 1].has_card == true)
    {
        printf("The client has a card. Are you sure you want to deactivate it? (y/n) ");
        char answer;
        scanf("%c", &answer);
        clear_buffer();
        if (answer == 'y' || answer == 'Y') 
        {
            clients[customer_id - 1].has_card = false;
            save_clients_bin(clients, read_counter_bin());
            printf("Card deactivated.\n");
        }
        else if (answer == 'n' || answer == 'N') 
        {
            printf("Operation canceled.\n");
            insert_any_key();
            main_menu();
        }
        else 
        {
            printf("Invalid answer. Operation canceled.\n");
            insert_any_key();
            main_menu();
        }
    }
    else
    {
        printf("The client doesn't have a card.\n");
        insert_any_key();
        main_menu();
    }
}

void list_active_clients(Client clients[])              // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("List active clients:\n\n");                 // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    for (int i = 0; i < read_counter_bin(); i++)
    {
        if (clients[i].has_card == true)
        {
            printf("Customer ID: %d\n", i+1);
            printf("Name: %s", clients[i].name);
            printf("Phone: %d\n", clients[i].phone);
            printf("Email: %s\n", clients[i].email);
            printf("NIF: %d\n", clients[i].nif);
            printf("\n");
        }
    }
}

void client_management_menu(Client clients[])
{
    int option;
    do
    {
        client_management_menu_text();
        option = validate_integer();
        clear_buffer();
        if(option >= 1 && option <= 5)
        {
            (*client_management_menu_options[option-1])(clients);
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
        option = validate_integer();
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
void edit_client(Client clients[])                      // WIP
{
    clear_screen();
    printf("Edit client: \n");                          // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("Select the customer ID: ");
    int customer_id = validate_integer();
}

void add_purchase()
{
    clear_screen();
    printf("Add purchase\n");                           // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

void list_purchases()
{
    clear_screen();
    printf("List purchases\n");                         // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

void purchase_details()
{
    clear_screen();
    printf("Purchase details\n");                       // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

void verify_vouchers()
{
    clear_screen();
    printf("Verify vouchers\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

// --- --- save as csv menu functions --- ---
void save_1_store()
{
    clear_screen();
    printf("Save 1 store\n");                           // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

void save_all_stores()
{
    clear_screen();
    printf("Save all stores\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

// --- --- utility functions --- ---
void clear_buffer()                                     // WORKING
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insert_any_key()                                   // WORKING
{
    printf("Press any key to continue...");
    getchar();
}

void invalid_option()                                   // WORKING
{
    clear_screen();
    printf("Invalid option!\n");
    insert_any_key();
}

void program_exit()                                     // WORKING
{
    clear_screen();
    printf("Exiting...\n");
    exit(0);
}

int validate_integer()                                  // WORKING
{
    int option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%d%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789")) {
        option = -1;
    };
    return option;
}

void save_counter_bin(int counter)                      // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
{
    FILE *save_bin;
    save_bin = fopen("counter.bin", "wb");
    if (save_bin == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fwrite(&counter, sizeof(int), 1, save_bin);
    fclose(save_bin);
}

int read_counter_bin()                                  // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
{
    FILE *read_bin;
    int counter;
    read_bin = fopen("counter.bin", "rb");
    if (read_bin == NULL)
    {
        return 0;
    }
    fread(&counter, sizeof(int), 1, read_bin);
    fclose(read_bin);
    return counter;
}

void save_clients_bin(Client clients[], int counter)    // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
{
    FILE *save_bin;
    save_bin = fopen("clients.bin", "wb");
    if (save_bin == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fwrite(clients, sizeof(Client), (size_t)counter, save_bin);
    fclose(save_bin);
}


Client* read_clients_bin(int* counter)                  // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
{
    FILE *read_bin;
    Client* clients;
    read_bin = fopen("clients.bin", "rb");
    if (read_bin == NULL)
    {
        *counter = 0;
        return NULL;
    }
    fseek(read_bin, 0, SEEK_END);
    long file_size = ftell(read_bin);
    rewind(read_bin);
    *counter = (int)((unsigned long)file_size / sizeof(Client));
    clients = (Client*)malloc(sizeof(Client) * (unsigned long)(*counter));
    if (clients == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    fread(clients, sizeof(Client), (size_t)(*counter), read_bin);
    fclose(read_bin);
    return clients;
}

void set_clients(Client clients[])                      // TESTING // NOTE: WORKING BUT MAY CHANGE LATER
{
    int counter = read_counter_bin();
    Client* read_clients = read_clients_bin(&counter);
    for (int i = 0; i < counter; i++) {
        clients[i] = read_clients[i];
    }
    free(read_clients);
}
