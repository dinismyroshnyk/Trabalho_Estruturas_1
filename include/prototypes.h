// system specific commands
#ifdef _WIN32 // assume Windows
    #define clear_screen() system("cls")
#else // assume POSIX or similar
    #define clear_screen() system("clear")
#endif

// menuManager headers
void main_menu();
void insert_any_key();
void invalid_option();