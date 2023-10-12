#include <stdio.h>
#include "headers.h"

int main() {

    node_pointer ptr_to_head;
    FILE *fp;

    char option;
    int exit = 0;
    char config_filename[] = "default_config_file.txt" ;
    FILE *config_file;

    config_pointer con_ptr;
    config_pointer changed_structure_ptr;

    // opening default config file at start of the program
    config_file = fopen(config_filename, "r");
    con_ptr = reading_config(config_file);
    changed_structure_ptr = con_ptr;
    printf("***************************** Welcome to Analysing Sheep Behaviour program *******************************************\n");
    printf("\n");
    do {

        printf("********************************************* Menu *******************************************************************\n");
        printf("\n");
        printf("\n");
        printf("1. Load configuration file \n");
        printf("2. Load the data and generate the csv output file and graph plots \n");
        printf("3. Change current configuration information \n");
        printf("4. Update the current configuration file \n");
        printf("5. Exit the program \n");
        printf("\n");
        printf("What would you like to do?\n");


        scanf(" %c", &option);


        switch (option) {

            case '1':
                config_file = NULL;
                printf("Please insert name of the configuration file: ");
                scanf("%s", config_filename);
                config_file = fopen(config_filename, "r");
                if (config_file == NULL) {
                    printf("File doesn't exist\n");
                    printf("Try again\n");
                    break;
                } else {
                    printf("File %s open!\n", config_filename);
                    con_ptr = reading_config(config_file);
                    changed_structure_ptr = con_ptr;
                    break;
                }

            case '2':
                fp = fopen(con_ptr->data_name, "r");
                if (fp == NULL) {
                    printf("File doesn't exist\n");
                    printf("Try again\n");
                    break;
                } else {
                    printf("File %s open!\n", con_ptr->data_name);
                    ptr_to_head = reading_from_file(fp);
                    generate_movement(ptr_to_head,con_ptr);
                    printf("*******Creating plot******** \n");
                    printf("\n");
                    createTestPlot(con_ptr);
                    break;
                }
            case '3':
                changed_structure_ptr = change_config(con_ptr);
                break;
            case '4':
                save_new_configuration_file(changed_structure_ptr);
                break;
            case '5':
                exit = 1;
                printf("\n");
                printf("Thank you for using Analysing Sheep Behaviour program\n");
            default:
                break;

        }
    } while (exit != 1);
    return 0;

}


