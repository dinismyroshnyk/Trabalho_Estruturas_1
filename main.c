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
#define MAX_STORES 100 // NOTE: MAY BE REMOVED LATER
#define MAX_CLIENTS 100
#define DISCOUNT 0.15
#define VOUCHER_VALUE 5

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
    int purchase_counter;
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
void main_menu(Client clients[]);                                      // WORKING // NOTE - MAY NEED TO BE REWORKED
void main_menu_text();                                                  // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void register_new_client(Client clients[]);                             // WORKING // NOTE - MAY NEED TO BE REWORKED
void remove_client(Client clients[]);                                   // WORKING // NOTE - MAY NEED TO BE REWORKED
void list_active_clients(Client clients[]);                             // WORKING // NOTE - MAY NEED TO BE REWORKED
void client_management_menu(Client clients[]);                          // WORKING // NOTE - MAY NEED TO BE REWORKED
void sort_by_total_spent(Client clients[]);                             // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void save_as_csv_menu(Client clients[]);                                // WORKING // NOTE - MAY NEED TO BE REWORKED
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
void client_management_menu_text();                                     // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void edit_client_menu(Client clients[]);                                     // WORKING // NOTE - MAY NEED TO BE REWORKED
void add_purchase(Client clients[]);                                    // WORKING // NOTE - WILL BE REWORKED
void list_purchases(Client clients[]);                                  // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void purchase_details(Client clients[]);                                // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void verify_vouchers(Client clients[]);                                 // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void (*client_management_menu_options[])() =
{
    edit_client_menu,
    add_purchase,
    list_purchases,
    purchase_details,
    verify_vouchers
};
// --- --- save as csv menu functions --- ---
void save_as_csv_menu_text();                                           // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void save_1_store(Client clients[]);                                    // WORKING // NOTE - MAY NEED TO BE REWORKED
void save_all_stores(Client clients[]);                                 // WORKING // NOTE - MAY NEED TO BE REWORKED
void (*save_as_csv_menu_options[])() =
{
    save_1_store,
    save_all_stores
};
// --- --- edit client menu functions --- ---
void edit_client_menu_text();                                           // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
void edit_name(Client clients[], int customer_id);                      // WORKING // NOTE - MAY NEED TO BE REWORKED
void edit_phone(Client clients[], int customer_id);                     // WORKING // NOTE - MAY NEED TO BE REWORKED
void edit_email(Client clients[], int customer_id);                     // WORKING // NOTE - MAY NEED TO BE REWORKED
void edit_nif(Client clients[], int customer_id);                       // WORKING // NOTE - MAY NEED TO BE REWORKED
void reactivate_card(Client clients[], int customer_id);                // WORKING // NOTE - MAY NEED TO BE REWORKED
void (*edit_client_menu_options[])() =                                  // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    edit_name,
    edit_phone,
    edit_email,
    edit_nif,
    reactivate_card
};

// --- --- utility functions --- ---
void insert_any_key();                                                  // WORKING
void invalid_option();                                                  // WORKING
void clear_buffer();                                                    // WORKING
int validate_integer();                                                 // WORKING
float validate_float();                                                 // WORKING
void program_exit(Client clients[]);                                                    // WORKING
void set_purchase_counter(Client clients[], int client_id);             // WORKING // NOTE - AT LEAST IT SEEMS TO BE
void save_counter_bin(int counter);                                     // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
int read_counter_bin();                                                 // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
void save_clients_bin(Client client[], int counter);                    // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
Client* read_clients_bin(int* counter);                                 // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
void set_clients(Client clients[]);                                     // WORKING // NOTE: WORKING BUT MAY CHANGE LATER
void select_date(struct tm *date);
int validate_date(int day, int month, int year);                        // WORKING
bool is_leap_year(int year);
int get_max_day(int month, int year);
bool is_date_in_range(struct tm date, struct tm start, struct tm end);  // WORKING
bool is_year_in_range(struct tm date, struct tm start, struct tm end);
bool is_month_in_range(struct tm date, struct tm start, struct tm end);
bool is_day_in_range(struct tm date, struct tm start, struct tm end);
void select_time_interval(struct tm* start_date, struct tm* end_date);
int validate_customer_id(Client clients[]);

// --- main function start---
int main()
{
    Client* clients = malloc(sizeof(Client) * MAX_CLIENTS);
    if (clients == NULL)
    {
        printf("Error allocating memory!\n");
        exit(1);
    }
    main_menu(clients);
    return 0;
}
// --- main function end ---

// --- auxiliary functions ---
// --- --- menu texts --- ---
void main_menu_text()                                                   // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
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

void client_management_menu_text()                                      // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
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

void save_as_csv_menu_text()                                            // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
{
    clear_screen();
    printf("[1] - Save 1 store\n");
    printf("[2] - Save all stores\n");
    printf("[0] - Back\n");
    printf("\n>>> ");
}

void edit_client_menu_text()                                            // WORKING // NOTE - THE STYLE OF THE MENU MAY BE CHANGED LATER
{
    clear_screen();
    printf("[1] - Edit name\n");
    printf("[2] - Edit phone\n");
    printf("[3] - Edit email\n");
    printf("[4] - Edit NIF\n");
    printf("[5] - Reactivate card\n");
    printf("[0] - Cancel operation\n");
    printf("\n>>> ");
}

// --- --- main menu functions --- ---
void main_menu(Client clients[])                                        // DONE
{
    set_clients(clients);
    int option;
    do
    {
        main_menu_text();
        option = validate_integer();
        clear_buffer();
        if(option >= 1 && option <= 6) (*main_menu_options[option-1])(clients);
        else if (option == 0) program_exit(clients);
        else invalid_option();
    } while (option != 0);
}

void register_new_client(Client clients[])                              // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    int counter = read_counter_bin();
    char answer;
    clear_screen();
    if (counter == MAX_CLIENTS)
    {
        printf("The maximum number of clients has been reached.\n");
        insert_any_key();
        main_menu(clients);
    }
    printf("Register new client\n");
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
    set_purchase_counter(clients, counter);
    save_clients_bin(clients, counter);
}

void remove_client(Client clients[])                                    // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Remove client\n");                          // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    int customer_id = validate_customer_id(clients);
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
            main_menu(clients);
        }
        else 
        {
            printf("Invalid answer. Operation canceled.\n");
            insert_any_key();
            main_menu(clients);
        }
    }
    else
    {
        printf("The client doesn't have a card.\n");
        insert_any_key();
        main_menu(clients);
    }
}

void list_active_clients(Client clients[])                              // WORKING // NOTE - MAY NEED TO BE REWORKED
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
    insert_any_key();
}

void client_management_menu(Client clients[])
{
    int option;
    do
    {
        client_management_menu_text();
        option = validate_integer();
        clear_buffer();
        if(option >= 1 && option <= 5) (*client_management_menu_options[option-1])(clients);
        else if (option == 0) break;
        else invalid_option();
    } while (option != 0);
}

void sort_by_total_spent(Client clients[])                              // WORKING // NOTE - AT LEAST IT SEEMS TO BE
{
    clear_screen();
    printf("Sort by total spent:\n\n");                 // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    Client sorted_clients[read_counter_bin()];
    for (int i = 0; i < read_counter_bin(); i++) sorted_clients[i] = clients[i];
    for (int i = 0; i < read_counter_bin() - 1; i++)
    {
        for (int j = 0; j < read_counter_bin() - i - 1; j++)
        {
            if (sorted_clients[j].card.total_spent < sorted_clients[j + 1].card.total_spent)
            {
                Client temp = sorted_clients[j];
                sorted_clients[j] = sorted_clients[j + 1];
                sorted_clients[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < read_counter_bin(); i++)
    {
        printf("Customer ID: %d\n", sorted_clients[i].card.customer_id + 1);
        printf("Name: %s", sorted_clients[i].name);
        printf("Phone: %d\n", sorted_clients[i].phone);
        printf("Email: %s\n", sorted_clients[i].email);
        printf("NIF: %d\n", sorted_clients[i].nif);
        printf("Total spent: %.2f\n", sorted_clients[i].card.total_spent);
        printf("\n");
    }
    insert_any_key();
}

void save_as_csv_menu(Client clients[])
{
    int option;
    do
    {
        save_as_csv_menu_text();
        option = validate_integer();
        clear_buffer();
        if(option >= 1 && option <= 2) (*save_as_csv_menu_options[option-1])(clients);
        else if (option == 0) break;
        else invalid_option();
    } while (option != 0);
}

// --- --- client management menu functions --- ---
void edit_client_menu(Client clients[])                                      // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    int customer_id = validate_customer_id(clients), option;
    do
    {
        edit_client_menu_text();
        option = validate_integer();
        clear_buffer();
        if(option >= 1 && option <= 5) (*edit_client_menu_options[option-1])(clients, customer_id);
        else if (option == 0) break;
        else invalid_option();
    } while (option != 0);
}

void add_purchase(Client clients[])                                     // WORKING // NOTE - WILL BE REWORKED
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    clear_screen();
    printf("Add purchase\n");                                           // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    int customer_id = validate_customer_id(clients);
    printf("Purchase value: ");
    float purchase_value = validate_float();
    clear_buffer();
    if (purchase_value < 0)
    {
        printf("Invalid purchase value.\n");
        insert_any_key();
        main_menu(clients);
    }
    if (clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].value == MAX_PURCHASES)
    {
        printf("The client has reached the maximum number of purchases.\n");
        insert_any_key();
        main_menu(clients);
    }
    printf("Insert the store name: ");
    fgets(clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].store.name, 50, stdin);
    clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].store.name[strcspn(clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].store.name, "\n")] = '\0';
    printf("Insert the store address: ");
    fgets(clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].store.address, 50, stdin);
    clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].store.address[strcspn(clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].store.address, "\n")] = '\0';
    if (clients[customer_id - 1].has_card == true)
    {
        purchase_value -= purchase_value * DISCOUNT;
        printf("Discount applied, the purchase value is now: %.2f\n", purchase_value);
        if (clients[customer_id - 1].card.vouchers > 0)
        {
            while (1)
            {
                printf("You have %d vouchers, do you want to use them? (y/n)", clients[customer_id - 1].card.vouchers);
                char answer;
                scanf("%c", &answer);
                clear_buffer();
                if (answer == 'y' || answer == 'Y')
                {
                    printf("How many vouchers do you want to use? ");
                    int vouchers = validate_integer();
                    clear_buffer();
                    if (vouchers > clients[customer_id - 1].card.vouchers)
                    {
                        printf("Not enough vouchers.\n");
                        insert_any_key();
                    }
                    else
                    {
                        purchase_value -= (float)vouchers * VOUCHER_VALUE;
                        if (purchase_value < 0)
                        {
                            purchase_value = 0;
                            printf("Voucher(s) used, you are not entitled to change.\n");
                            clients[customer_id - 1].card.spent_vouchers += vouchers;
                        }
                        else
                        {
                            printf("Voucher(s) used, the purchase value is now: %.2f\n", purchase_value);
                            clients[customer_id - 1].card.spent_vouchers += vouchers;
                        }
                        break;
                    }
                }
                else if (answer == 'n' || answer == 'N')
                {
                    printf("Voucher(s) not used.\n");
                    break;
                }
                else
                {
                    printf("Invalid answer.\n");
                    insert_any_key();
                }
            }
        }
        clients[customer_id - 1].card.total_spent += purchase_value;
        clients[customer_id - 1].card.vouchers = (int)(clients[customer_id - 1].card.total_spent / 50.0 - clients[customer_id - 1].card.spent_vouchers);
    }else clients[customer_id - 1].card.total_spent += purchase_value;
    clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].value += purchase_value;
    clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].day = tm.tm_mday;
    clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].month = tm.tm_mon + 1;
    clients[customer_id - 1].card.purchases[clients[customer_id - 1].card.purchase_counter].year = tm.tm_year + 1900;
    clients[customer_id - 1].card.purchase_counter++;
    save_clients_bin(clients, read_counter_bin());

    insert_any_key();
}

void list_purchases(Client clients[])                                   // WORKING // NOTE - AT LEAST IT SEEMS TO BE
{
    clear_screen();
    printf("List purchases\n");                             // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    int customer_id = validate_customer_id(clients);
    for (int i = 0; i < clients[customer_id - 1].card.purchase_counter; i++)
    {
        printf("Purchase ID: %d\n", i+1);
        printf("Purchase value: %.2f\n", clients[customer_id - 1].card.purchases[i].value);
        printf("Purchase date: %d/%d/%d\n", clients[customer_id - 1].card.purchases[i].day, clients[customer_id - 1].card.purchases[i].month, clients[customer_id - 1].card.purchases[i].year);
        printf("Store name: %s\n", clients[customer_id - 1].card.purchases[i].store.name);
        printf("Store address: %s\n", clients[customer_id - 1].card.purchases[i].store.address);
    }
    insert_any_key();
}

void purchase_details(Client clients[])                                 // WORKING // NOTE - AT LEAST IT SEEMS TO BE
{
    clear_screen();
    printf("Purchase details\n");                           // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    int customer_id = validate_customer_id(clients);
    printf("Total ammount spent: %.2f\n", clients[customer_id - 1].card.total_spent);
    printf("Average ammount spent: %.2f\n", clients[customer_id - 1].card.total_spent / clients[customer_id - 1].card.purchase_counter);
    printf("Spent vouchers: %d\n", clients[customer_id - 1].card.spent_vouchers);
    insert_any_key();
}

void verify_vouchers(Client clients[])                                  // WORKING // NOTE - AT LEAST IT SEEMS TO BE
{
    clear_screen();
    printf("Verify vouchers\n");                            // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    int customer_id = validate_customer_id(clients);
    printf("Vouchers: %d\n", clients[customer_id - 1].card.vouchers);
    insert_any_key();
}

// --- --- edit client menu functions --- ---
void edit_name(Client clients[], int customer_id)                       // WORKING // NOTE - MAY NEED TO BE REWORKED
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

void edit_phone(Client clients[], int customer_id)                      // WORKING // NOTE - MAY NEED TO BE REWORKED
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

void edit_email(Client clients[], int customer_id)                      // WORKING // NOTE - MAY NEED TO BE REWORKED
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

void edit_nif(Client clients[], int customer_id)                        // WORKING // NOTE - MAY NEED TO BE REWORKED
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

void reactivate_card(Client clients[], int customer_id)                 // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Reactivate card\n");                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    clients[customer_id - 1].has_card = true;
    save_clients_bin(clients, read_counter_bin());
    printf("Card reactivated.\n");
    insert_any_key();
    client_management_menu(clients);
}

// --- --- save as csv menu functions --- ---
void save_1_store(Client clients[])                                     // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Save 1 store\n");  
    char store_name[50], store_address[50];
    printf("Select the store name: ");
    fgets(store_name, 50, stdin);
    printf("Select the store address: ");
    fgets(store_address, 50, stdin);
    struct tm start_date, end_date;
    select_time_interval(&start_date, &end_date);
    store_name[strcspn(store_name, "\n")] = '\0';
    store_address[strcspn(store_address, "\n")] = '\0';
    char filename[150];
    sprintf(filename, "%s_%s_%d%d%d_%d%d%d.csv", store_name, store_address, start_date.tm_mday, start_date.tm_mon, start_date.tm_year, end_date.tm_mday, end_date.tm_mon, end_date.tm_year);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create the file.\n");
        return;
    }
    fprintf(file, "Date,Purchase Value,Client Number\n");
    for (int i = 0; i < read_counter_bin(); i++)
    {
        for (int j = 0; j < clients[i].card.purchase_counter; j++)
        {
            if (strcasecmp(clients[i].card.purchases[j].store.name, store_name) == 0 && strcasecmp(clients[i].card.purchases[j].store.address, store_address) == 0)
            {
                struct tm purchase_date;
                purchase_date.tm_mday = clients[i].card.purchases[j].day;
                purchase_date.tm_mon = clients[i].card.purchases[j].month;
                purchase_date.tm_year = clients[i].card.purchases[j].year;
                if (is_date_in_range(purchase_date, start_date, end_date))
                {
                    if (clients[i].has_card == true) fprintf(file, "%d/%d/%d,%.2f,%d\n", purchase_date.tm_mday, purchase_date.tm_mon, purchase_date.tm_year, clients[i].card.purchases[j].value, clients[i].card.customer_id + 1);
                    else fprintf(file, "%d/%d/%d,%.2f,\n", purchase_date.tm_mday, purchase_date.tm_mon, purchase_date.tm_year, clients[i].card.purchases[j].value);
                }
            }
        }
    }
    fclose(file);
    printf("CSV file created successfully.\n");
    insert_any_key();
}

void save_all_stores(Client clients[])                                  // WORKING // NOTE - MAY NEED TO BE REWORKED
{
    clear_screen();
    printf("Save all stores\n");                                        // TODO // FIXME - THIS LINE MAY NEED TO BE REWORKED OR REMOVED
    struct tm start_date, end_date;
    printf("Select the time interval");
    select_time_interval(&start_date, &end_date);
    char filename[150];
    sprintf(filename, "all_stores_%d%d%d_%d%d%d.csv", start_date.tm_mday, start_date.tm_mon, start_date.tm_year, end_date.tm_mday, end_date.tm_mon, end_date.tm_year);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create the file.\n");
        return;
    }
    fprintf(file, "Date,Purchase Value,Client Number,Store Name,Store Address\n");
    for (int i = 0; i < read_counter_bin(); i++)
    {
        for (int j = 0; j < clients[i].card.purchase_counter; j++)
        {
            struct tm purchase_date;
            purchase_date.tm_mday = clients[i].card.purchases[j].day;
            purchase_date.tm_mon = clients[i].card.purchases[j].month;
            purchase_date.tm_year = clients[i].card.purchases[j].year;
            if (is_date_in_range(purchase_date, start_date, end_date))
            {
                if (clients[i].has_card == true) fprintf(file, "%d/%d/%d,%.2f,%d,%s,%s\n", purchase_date.tm_mday, purchase_date.tm_mon, purchase_date.tm_year, clients[i].card.purchases[j].value, clients[i].card.customer_id + 1, clients[i].card.purchases[j].store.name, clients[i].card.purchases[j].store.address);
                else fprintf(file, "%d/%d/%d,%.2f,,%s,%s\n", purchase_date.tm_mday, purchase_date.tm_mon, purchase_date.tm_year, clients[i].card.purchases[j].value, clients[i].card.purchases[j].store.name, clients[i].card.purchases[j].store.address);
            }
        }
    }
    fclose(file);
    printf("CSV file created successfully.\n");
    insert_any_key();
}

// --- --- utility functions --- ---
void clear_buffer()                                                     // DONE
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insert_any_key()                                                   // DONE
{
    printf("Press any key to continue...");
    getchar();
}

void invalid_option()                                                   // DONE
{
    clear_screen();
    printf("Invalid option!\n");
    insert_any_key();
}

void program_exit(Client clients[])                                     // DONE
{
    clear_screen();
    free(clients);
    printf("Exiting...\n");
    exit(0);
}

int validate_integer()                                                  // DONE
{
    int option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%d%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789")) {
        option = -1;
    };
    return option;
}

float validate_float()                                                  // DONE
{
    float option;
    char input[50];
    scanf("%s", input);
    if (sscanf(input, "%f%*c", &option) != 1 || strlen(input) != strspn(input, "0123456789.")) {
        option = -1;
    };
    return option;
}

void select_date(struct tm *date)                                       // DONE
{
    bool is_valid_date = false;
    while (!is_valid_date) {
        printf("Enter the day: ");
        scanf("%d", &date->tm_mday);
        printf("Enter the month: ");
        scanf("%d", &date->tm_mon);
        printf("Enter the year: ");
        scanf("%d", &date->tm_year);
        is_valid_date = validate_date(date->tm_mday, date->tm_mon, date->tm_year);
        if (!is_valid_date) printf("Invalid date. Please enter a valid date.\n");
    }
}

int validate_date(int day, int month, int year)                         // DONE
{
    if (year < 1900) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > get_max_day(month, year)) return false;
    return true;
}

bool is_leap_year(int year)                                             // DONE
{
    if (year % 4 == 0) {
        if (year % 100 != 0 || year % 400 == 0) return true;
        else return false;
    } else return false;
}

int get_max_day(int month, int year)                                    // DONE
{
    switch (month) {
        case 2: return is_leap_year(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11: return 30;
        default: return 31;
    }
}

bool is_date_in_range(struct tm date, struct tm start, struct tm end)   // DONE
{
    if (!is_year_in_range(date, start, end)) return false;
    if (!is_month_in_range(date, start, end)) return false;
    if (!is_day_in_range(date, start, end)) return false;
    return true;
}

bool is_year_in_range(struct tm date, struct tm start, struct tm end)   // DONE
{
    return date.tm_year >= start.tm_year && date.tm_year <= end.tm_year;
}

bool is_month_in_range(struct tm date, struct tm start, struct tm end)  // DONE
{
    if (date.tm_year == start.tm_year) {
        return date.tm_mon >= start.tm_mon;
    } else if (date.tm_year == end.tm_year) {
        return date.tm_mon <= end.tm_mon;
    } else {
        return true;
    }
}

bool is_day_in_range(struct tm date, struct tm start, struct tm end)    // DONE
{
    if (date.tm_year == start.tm_year && date.tm_mon == start.tm_mon) {
        return date.tm_mday >= start.tm_mday;
    } else if (date.tm_year == end.tm_year && date.tm_mon == end.tm_mon) {
        return date.tm_mday <= end.tm_mday;
    } else {
        return true;
    }
}

void select_time_interval(struct tm* start_date, struct tm* end_date)   // DONE
{
    bool is_valid_interval = false;
    printf("Select the time interval");
    printf("\nStart date: \n");
    select_date(start_date);
    clear_buffer();
    printf("\nEnd date: \n");
    select_date(end_date);
    clear_buffer();
    if (start_date->tm_year <= end_date->tm_year)
        if (start_date->tm_mon <= end_date->tm_mon)
            if (start_date->tm_mday <= end_date->tm_mday)
                is_valid_interval = true;
    if (!is_valid_interval) 
    {
        printf("Invalid interval. Please enter a valid interval.\n");
        select_time_interval(start_date, end_date);
    }
}

void set_purchase_counter(Client clients[], int client_id)              // DONE
{
    for (int i = 0; i < MAX_PURCHASES; i++) clients[client_id - 1].card.purchase_counter = 0;
    save_clients_bin(clients, read_counter_bin());
}

void save_counter_bin(int counter)                                      // DONE // NOTE: WORKING BUT MAY CHANGE LATER
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

int read_counter_bin()                                                  // DONE // NOTE: WORKING BUT MAY CHANGE LATER
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

void save_clients_bin(Client clients[], int counter)                    // DONE // NOTE: WORKING BUT MAY CHANGE LATER
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

Client* read_clients_bin(int* counter)                                  // DONE // NOTE: WORKING BUT MAY CHANGE LATER
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

void set_clients(Client clients[])                                      // DONE // NOTE: WORKING BUT MAY CHANGE LATER
{
    int counter = read_counter_bin();
    Client* read_clients = read_clients_bin(&counter);
    for (int i = 0; i < counter; i++) {
        clients[i] = read_clients[i];
    }
    free(read_clients);
}

int validate_customer_id(Client clients[])                              // DONE
{
    printf("Select the customer ID: ");
    int customer_id = validate_integer();
    clear_buffer();
    if (customer_id > read_counter_bin() || customer_id < 1)
    {
        printf("Invalid customer ID.\n");
        insert_any_key();
        main_menu(clients);
    }
    return customer_id;
}

