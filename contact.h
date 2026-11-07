#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook,int editChoice);
void deleteContact(AddressBook *addressBook,int deleteChoice);
void listContacts(AddressBook *addressBook,int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validateName(char *name);
int validateMobile(char *number);
int validateEmail(char *email);
int isunique_number(AddressBook *addressBook,char *number);
int isunique_email(AddressBook *addressBook,char *email);
void Delete(AddressBook *addressBook,int position);

#endif
