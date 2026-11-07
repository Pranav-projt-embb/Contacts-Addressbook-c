/*
Name : Pranav More
Batch Id : 26018F-380
Project name : AddressBook
Discription : To create addressbook to save contact details(name,phone number,email) by user.Also after 
              saving contact deatils in future he will able to edit,delete,list,serach.
*/


#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save entered contacts and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                printf("Select criteria to edit:\n");
                printf("1. Edit name\n");
                printf("2. Edit phone\n");
                printf("3. Edit email\n");
                printf("Enter your choice: ");
                int editChoice;
                scanf("%d", &editChoice);
                editContact(&addressBook,editChoice);
                break;
            case 4:
                printf("Select criteria to delete contact details:\n");
                printf("1. Delete by name\n");
                printf("2. Delete by phone number\n");
                printf("3. Delete by email\n");
                printf("Enter your choice: ");
                int deleteChoice;
                scanf("%d", &deleteChoice);
                deleteContact(&addressBook,deleteChoice);
                break;
            case 5:
                printf("Select criteria to delete contact details:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone number\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int SortChoice;
                scanf("%d", &SortChoice);                
                listContacts(&addressBook,SortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
