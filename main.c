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
#include <time.h>

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
    int day;
    int month;
    int year;
    Store store;
} Purchase;

typedef struct Card {
    int customer_id;
    float total_spent;
    int vouchers;
    int spent_vouchers;
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
void main_menu_text();                                      // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void register_new_client(Client clients[]);                 // WORKING // NOTE - MAY NEED TO BE REWORKED
void remove_client(Client clients[]);                       // WORKING // NOTE - MAY NEED TO BE REWORKED
void list_active_clients(Client clients[]);                 // WORKING // NOTE - MAY NEED TO BE REWORKED
void client_management_menu(Client clients[]);              // WIP
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
void client_management_menu_text();                         // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void edit_client(Client clients[]);                         // WORKING // NOTE - MAY NEED TO BE REWORKED
void add_purchase(Client clients[]);                        // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void list_purchases(Client clients[]);                      // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void purchase_details(Client clients[]);                    // WIP
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
void save_as_csv_menu_text();                               // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void save_1_store();
void save_all_stores();
void (*save_as_csv_menu_options[])() =
{
    save_1_store,
    save_all_stores
};
// --- --- edit client menu functions --- ---
void edit_client_menu_text();                               // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void edit_name(Client clients[], int customer_id);          // WORKING // NOTE - MAY NEED TO BE REWORKED
void edit_phone(Client clients[], int customer_id);         // WORKING // NOTE - MAY NEED TO BE REWORKED
void edit_email(Client clients[], int customer_id);         // WORKING // NOTE - MAY NEED TO BE REWORKED
void edit_nif(Client clients[], int customer_id);           // WORKING // NOTE - MAY NEED TO BE REWORKED
void reactivate_card(Client clients[], int customer_id);    // WORKING // NOTE - MAY NEED TO BE REWORKED
void deduct_vouchers(Client clients[], int customer_id);    // TESTING // WIP // NOTE - MAY NEED TO BE REWORKED
void (*edit_client_menu_options[])() =                      // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    edit_name,
    edit_phone,
    edit_email,
    edit_nif,
    reactivate_card,
    deduct_vouchers
};

// --- --- utility functions --- ---
void insert_any_key();                                      // WORKING
void invalid_option();                                      // WORKING
void clear_buffer();                                        // WORKING
int validate_integer();                                     // WORKING
float validate_float();                                     // WORKING
void program_exit();                                        // WORKING
void set_purchases_to_zero(Client clients[], int client_id);// WORKING // NOTE - AT LEAST IT SEEMS TO BE
int check_purchase_count(Client clients[], int client_id);  // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void save_counter_bin(int counter);                         // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
int read_counter_bin();                                     // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
void save_clients_bin(Client client[], int counter);        // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
Client* read_clients_bin(int* counter);                     // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
void set_clients(Client clients[]);                         // WORKING // NOTE: WORKING BUT MAY CHANGE LATER

// --- main function start---
int main()
{
    main_menu();
    return 0;
}
// --- main function end ---

// --- auxiliary functions ---
// --- --- menu texts --- ---
void main_menu_text()                                       // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
{
    clear_screen();
    printf("[1] - Register new client\n");
    printf("[2] - Remove client (deactivate card)\n");
    printf("[3] - List active clients\n");
    printf("[4] - Client management\n");
    printf("[5] - Sort by total spent\n");
    printf("[6] - Save as csv\n");
    printf("[0] - Exit\n");
    printf("\n>>> ");
}

void client_management_menu_text()                          // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
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

void save_as_csv_menu_text()                                // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
{
    clear_screen();
    printf("[1] - Save 1 store\n");
    printf("[2] - Save all stores\n");
    printf("[0] - Back\n");
    printf("\n>>> ");
}

void edit_client_menu_text()                                // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
{
    clear_screen();
    printf("[1] - Edit name\n");
    printf("[2] - Edit phone\n");
    printf("[3] - Edit email\n");
    printf("[4] - Edit NIF\n");
    printf("[5] - Reactivate card\n");
    printf("[6] - Deduct vouchers\n");
    printf("[0] - Cancel operation\n");
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
        if(option >= 1 && option <= 8)
        {
            (*main_menu_options[option-1])(clients);
            insert_any_key();                           // TODO // FIXME - REMOVE THIS LINE WHEN THE PROGRAM IS FINISHED
        }
        else if (option == 0) program_exit();
        else invalid_option();
    } while (option != 0);
}

void register_new_client(Client clients[])                  // WORKING // NOTE - MAY NEED TO BE REWORKED
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
    printf("Register new client\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
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
    clients[counter].card.spent_vouchers = 0;
    save_counter_bin(++counter);
    set_purchases_to_zero(clients, counter);
    save_clients_bin(clients, counter);
}

void remove_client(Client clients[])                        // WORKING // NOTE - MAY NEED TO BE REWORKED
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

void list_active_clients(Client clients[])                  // WORKING // NOTE - MAY NEED TO BE REWORKED
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
void edit_client(Client clients[])                          // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Edit client: \n");                              // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("Select the customer ID: ");
    int customer_id = validate_integer();
    clear_buffer();
    if (customer_id > read_counter_bin() || customer_id < 1)
    {
        printf("Invalid customer ID.\n");
        insert_any_key();
        main_menu();
    }
    edit_client_menu_text();
    int option = validate_integer();
    clear_buffer();
    if(option >= 1 && option <= 6)
    {
        (*edit_client_menu_options[option-1])(clients, customer_id);
        insert_any_key();
    }
    else if (option == 0) main_menu();
    else invalid_option();
}

void add_purchase(Client clients[])                         // WORKING // NOTE - AT LEAST IT SEEMS TO BE
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    clear_screen();
    printf("Add purchase\n");                               // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("Select the customer ID: ");
    int customer_id = validate_integer();
    clear_buffer();
    if (customer_id > read_counter_bin() || customer_id < 1)
    {
        printf("Invalid customer ID.\n");
        insert_any_key();
        main_menu();
    }
    printf("Purchase value: ");
    float purchase_value = validate_float();
    clear_buffer();
    if (purchase_value < 0)
    {
        printf("Invalid purchase value.\n");
        insert_any_key();
        main_menu();
    }
    int purchase_count = check_purchase_count(clients, customer_id);
    if (clients[customer_id - 1].card.purchases[purchase_count].value == MAX_PURCHASES)
    {
        printf("The client has reached the maximum number of purchases.\n");
        insert_any_key();
        main_menu();
    }
    if (clients[customer_id - 1].has_card == true)
    {
        clients[customer_id - 1].card.total_spent += purchase_value;
        clients[customer_id - 1].card.vouchers = (int)(clients[customer_id - 1].card.total_spent / 50.0 - clients[customer_id - 1].card.spent_vouchers);
    }
    clients[customer_id - 1].card.purchases[purchase_count].value += purchase_value;
    clients[customer_id - 1].card.purchases[purchase_count].day = tm.tm_mday;
    clients[customer_id - 1].card.purchases[purchase_count].month = tm.tm_mon + 1;
    clients[customer_id - 1].card.purchases[purchase_count].year = tm.tm_year + 1900;
    save_clients_bin(clients, read_counter_bin());
}

void list_purchases(Client clients[])                       // WORKING // NOTE - AT LEAST IT SEEMS TO BE
{
    clear_screen();
    printf("List purchases\n");                             // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("Select the customer ID: ");
    int customer_id = validate_integer();
    clear_buffer();
    if (customer_id > read_counter_bin() || customer_id < 1)
    {
        printf("Invalid customer ID.\n");
        insert_any_key();
        main_menu();
    }
    for (int i = 0; i < MAX_PURCHASES; i++)
    {
        if (clients[customer_id - 1].card.purchases[i].value != 0)
        {
            printf("Purchase ID: %d\n", i+1);
            printf("Purchase value: %.2f\n", clients[customer_id - 1].card.purchases[i].value);
            printf("Purchase date: %d/%d/%d\n", clients[customer_id - 1].card.purchases[i].day, clients[customer_id - 1].card.purchases[i].month, clients[customer_id - 1].card.purchases[i].year);
        }
    }
}

void purchase_details(Client clients[])                     // WIP
{
    clear_screen();
    printf("Purchase details\n");                           // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED

}

void verify_vouchers()
{
    clear_screen();
    printf("Verify vouchers\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
}

// --- --- edit client menu functions --- ---
void edit_name(Client clients[], int customer_id)           // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Edit name\n");                              // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("New name: ");
    fgets(clients[customer_id - 1].name, 50, stdin);
    save_clients_bin(clients, read_counter_bin());
    printf("Name changed.\n");
    insert_any_key();
    client_management_menu(clients);
}

void edit_phone(Client clients[], int customer_id)          // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Edit phone\n");                             // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("New phone: ");
    clients[customer_id - 1].phone = validate_integer();
    clear_buffer();
    save_clients_bin(clients, read_counter_bin());
    printf("Phone changed.\n");
    insert_any_key();
    client_management_menu(clients);
}

void edit_email(Client clients[], int customer_id)          // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Edit email\n");                             // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("New email: ");
    scanf("%s", clients[customer_id - 1].email);
    clear_buffer();
    save_clients_bin(clients, read_counter_bin());
    printf("Email changed.\n");
    insert_any_key();
    client_management_menu(clients);
}

void edit_nif(Client clients[], int customer_id)            // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Edit NIF\n");                               // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("New NIF: ");
    clients[customer_id - 1].nif = validate_integer();
    clear_buffer();
    save_clients_bin(clients, read_counter_bin());
    printf("NIF changed.\n");
    insert_any_key();
    client_management_menu(clients);
}

void reactivate_card(Client clients[], int customer_id)     // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Reactivate card\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    clients[customer_id - 1].has_card = true;
    save_clients_bin(clients, read_counter_bin());
    printf("Card reactivated.\n");
    insert_any_key();
    client_management_menu(clients);
}

void deduct_vouchers(Client clients[], int customer_id)     // TESTING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Deduct vouchers\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    printf("How many vouchers do you want to deduct? ");
    int vouchers = validate_integer();
    clear_buffer();
    if (vouchers > clients[customer_id - 1].card.vouchers)
    {
        printf("Not enough vouchers.\n");
        insert_any_key();
        client_management_menu(clients);
    }
    clients[customer_id - 1].card.vouchers -= vouchers;
    save_clients_bin(clients, read_counter_bin());
    printf("Vouchers deducted.\n");
    insert_any_key();
    client_management_menu(clients);
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
void clear_buffer()                                         // WORKING
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insert_any_key()                                       // WORKING
{
    printf("Press any key to continue...");
    getchar();
}

void invalid_option()                                       // WORKING
{
    clear_screen();
    printf("Invalid option!\n");
    insert_any_key();
}

void program_exit()                                         // WORKING
{
    clear_screen();
    printf("Exiting...\n");
    exit(0);
}

int validate_integer()                                      // WORKING
{
    int option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%d%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789")) {
        option = -1;
    };
    return option;
}

float validate_float()                                      // WORKING
{
    float option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%f%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789.")) {
        option = -1;
    };
    return option;
}

void set_purchases_to_zero(Client clients[], int client_id) // WORKING
{
    for (int i = 0; i < MAX_PURCHASES; i++) clients[client_id - 1].card.purchases[MAX_PURCHASES].value = 0;
    save_clients_bin(clients, read_counter_bin());
}

int check_purchase_count(Client clients[], int client_id)   // WORKING
{
    int purchase_count = 0;
    for (int i = 0; i < MAX_PURCHASES; i++) {
        if (clients[client_id - 1].card.purchases[i].value != 0) purchase_count++;
    }
    return purchase_count;
}

void save_counter_bin(int counter)                          // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
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

int read_counter_bin()                                      // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
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

void save_clients_bin(Client clients[], int counter)        // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
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

Client* read_clients_bin(int* counter)                      // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
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

void set_clients(Client clients[])                          // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
{
    int counter = read_counter_bin();
    Client* read_clients = read_clients_bin(&counter);
    for (int i = 0; i < counter; i++) {
        clients[i] = read_clients[i];
    }
    free(read_clients);
}