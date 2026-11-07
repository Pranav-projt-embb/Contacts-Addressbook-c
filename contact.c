#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"

// To list contact according to choice in sorted way
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int choice;
    printf("Enter '1' to list contacts, or '0' to go back to main menu: ");
    scanf("%d", &choice);

    if (choice == 0)
    {
        return;   /* user changed their mind, go back to main menu */
    }
    else if (choice != 1)
    {
        printf("Invalid choice. Going back to main menu.\n");
        return;
    }

    if (addressBook->contactCount == 0)
    {
        printf("No contacts to display!\n");
        return;
    }

    /* Sort contacts based on the chosen criteria */
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            int result;

            if (sortCriteria == 1)
            {
                result = strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
            }
            else if (sortCriteria == 2)
            {
                result = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
            }
            else if (sortCriteria == 3)
            {
                result = strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email);
            }
            else
            {
                printf("Invalid sort criteria\n");
                return;
            }

            if (result > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
    printf("--------------------------------------------------------------------\n");
    printf("\n%-4s %-20s %-15s %-25s\n", "No.", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------------\n");

   for (int i = 0; i < addressBook->contactCount; i++)
   {
        printf("%-4d %-20s %-15s %-25s\n",
           i + 1,
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
   }
   printf("--------------------------------------------------------------------\n");

    return;   /* after listing, goes back to main menu */
}
//To load conatcts
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
// To save contact permanantly 
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//Function to create contact
void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount >= MAX_CONTACTS)//checks contactcount not reached 100
    {
        printf("Addressbook contact creating limit reached(i.e100).Cannot store further conatcts!!!.\n");
        return;
    }
	char name[50];
    char number[12];
    char email[50];
    while(1)
    {
        printf("Enter name: ");
        scanf(" %49[^\n]",name);

        if(validateName(name))//Validate name before saveing
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            break;
        }
    }
    while(1)
    {
        printf("Enter phone number: ");
        scanf(" %11[^\n]",number);

        if(validateMobile(number) && isunique_number(addressBook,number))//validate number and its uniqness
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, number);
            break;
        }
    }
    while(1)
    {
        printf("Enter Email id : ");
        scanf(" %49[^\n]",email);

        if(validateEmail(email) && isunique_email(addressBook,email))//validate email and its uniqness
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            break;
        }

    }
    addressBook->contactCount++;

    printf("Contact created successfully!\n");
}
// To search contact according to choice
void searchContact(AddressBook *addressBook) 
{
    int choice,continu;
    printf("If you want exit enter 0 or  to continue enter 1 : ");
    scanf("%d", &continu);
    char str[50];
    while(continu)
    {
        printf("Enter proper search choice\nChoice 1-> Name\nChoice 2-> Mobile number\nChoice 3-> Email.id\n");
        printf("Enter your choice: \n");
        scanf("%d",&choice);
        int found=1;
        switch (choice)
        {
        case 1:
            printf("enter the name: ");
            scanf(" %49[^\n]",str);
            printf("--------------------------------------------------------------------\n");
            printf("\n%-4s %-20s %-15s %-25s\n", "No.", "Name", "Phone", "Email");
            printf("--------------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].name,str)==0)
                {
                          printf("%-4d %-20s %-15s %-25s\n",
                                i + 1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                    found=0;
                }
            }
            printf("--------------------------------------------------------------------\n");
            break;
         
        case 2:
            printf("enter the phone number: ");
            scanf(" %49[^\n]",str);
            printf("--------------------------------------------------------------------\n");
            printf("\n%-4s %-20s %-15s %-25s\n", "No.", "Name", "Phone", "Email");
            printf("--------------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].phone,str)==0)
                {
                          printf("%-4d %-20s %-15s %-25s\n",
                                i + 1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                    found=0;
                }
            }
            printf("--------------------------------------------------------------------\n");
            break;

        case 3:
            printf("enter the email: ");
            scanf(" %49[^\n]",str);
            printf("--------------------------------------------------------------------\n");
            printf("\n%-4s %-20s %-15s %-25s\n", "No.", "Name", "Phone", "Email");
            printf("--------------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].email,str)==0)
                {
                          printf("%-4d %-20s %-15s %-25s\n",
                                i + 1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                    found=0;
                }
            }
            printf("--------------------------------------------------------------------\n");
            break;

            default:
            printf("Error detected: Invalid search choice!!!.\n");
            found = -1;
        }
        if(found==1)
        {
            printf("Contact not found\n");
            printf("If you want to search again if yes enter '1',no enter '0' : ");
            scanf("%d",&continu);
        }
        else if(found == 0 || found == -1)
        {
            printf("If you want to search again if yes enter '1',no enter '0' : ");
            scanf("%d",&continu);
        }
    }
    return;

}
// To edit contact according to choice
void editContact(AddressBook *addressBook, int editChoice)
{
    int continu, indexChoice, matchedIndex;
    char data[50];

    printf("If you want to exit enter '0' or edit contact enter '1': ");
    scanf("%d", &continu);

    while (continu)
    {
        matchedIndex = -1;

        switch (editChoice)
        {
            case 1:
            {
                printf("Enter contact name you want to edit: ");
                scanf(" %49[^\n]", data);
        
                int matchedIndices[MAX_CONTACTS];
                int matchCount = 0;
                printf("--------------------------------------------------------------------\n");
                printf("\n%-3s %-18s %-12s %-18s\n", "No.", "Name", "Phone", "Email");
                printf("--------------------------------------------------------------------\n");

                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].name, data) == 0)
                    {
                        matchedIndices[matchCount] = i;
                        matchCount++;
                        printf("%-3d %-18s %-12s %-18s\n", i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
                printf("--------------------------------------------------------------------\n");

                if (matchCount == 0)
                {
                    printf("Error detected : Entered contact name not found!!!\n");
                }
                else
                {
                    int chosenIndex = -1;

                    if (matchCount == 1)
                    {
                        chosenIndex = matchedIndices[0];
                    }
                    else
                    {
                        while (1)
                        {
                            printf("Multiple contacts found with this name.\n");
                            printf("Enter the index number (from the list above) you want to edit: ");
                            scanf("%d", &indexChoice);

                            int valid = 0;
                            for (int k = 0; k < matchCount; k++)
                            {
                                if (matchedIndices[k] == indexChoice)
                                {
                                    valid = 1;
                                    break;
                                }
                            }

                            if (valid)
                            {
                                chosenIndex = indexChoice;
                                break;
                            }
                            else
                            {
                                printf("Error detected: This index choice is invalid!!! Please enter a valid index.\n");
                            }
                        }
                    }
                    //user enterd proper index then store new name
                    char newname[50];
                    printf("Enter the new name you want to add: ");
                    scanf(" %49[^\n]", newname);

                    if (validateName(newname))//newname validate before updating
                    {
                        strcpy(addressBook->contacts[chosenIndex].name, newname);
                        printf("Name updated successfully.\n");
                    }
                    else
                    {
                        printf("Error detected: Invalid name. Edit cancelled.\n");
                    }
                }
                break;
            }

            case 2:
            {
                char editphone[12];
                printf("Enter phone number you want to edit: ");
                scanf(" %11[^\n]", editphone);

                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, editphone) == 0)
                    {
                        matchedIndex = i;
                        break;
                    }
                }

                if (matchedIndex == -1)
                {
                    printf("Error detected : Entered contact number not found!!!\n");
                }
                else
                {
                    char newNumber[12];//contact number found then update it
                    printf("Enter the new number you want to add: ");
                    scanf(" %11[^\n]", newNumber);

                    if (validateMobile(newNumber) && isunique_number(addressBook, newNumber))
                    {
                        strcpy(addressBook->contacts[matchedIndex].phone, newNumber);
                        printf("Phone number updated successfully.\n");
                    }
                    else
                    {
                        printf("Invalid or duplicate number.Edit cancelled.\n");
                    }
                }
                break;
            }

            case 3:
            {
                char editEmail[50];
                printf("Enter user email you want to edit: ");
                scanf(" %49[^\n]", editEmail);

                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].email, editEmail) == 0)
                    {
                        matchedIndex = i;
                        break;
                    }
                }

                if (matchedIndex == -1)
                {
                    printf("Error detected: Entered Email not found!!!\n");
                }
                else
                {
                    char newEmail[50];//Email found then update it 
                    printf("Enter the new email you want to add: ");
                    scanf(" %49[^\n]", newEmail);

                    if (validateEmail(newEmail) && isunique_email(addressBook, newEmail))
                    {
                        strcpy(addressBook->contacts[matchedIndex].email, newEmail);
                        printf("Email updated successfully.\n");
                    }
                    else
                    {
                        printf("Invalid or duplicate email. Edit cancelled.\n");
                    }
                }
                break;
            }

            default:
            printf("Error detected: Invalid edit criteria choice!!!!\n");
        }

        printf("If you want to edit enter '1' else to exit enter '0': ");
        scanf("%d", &continu);
    }
    return;
}
// To delete contact according to choice
void deleteContact(AddressBook *addressBook,int deleteChoice)
{
	/* Define the logic for deletecontact */
    int stay,indexChoice;//indexchoice for multiple same name contacts
    char data[50] = {0};
    printf("If you want to exit enter '0' or delete contact enter '1': ");
    scanf("%d", &stay);
    while(stay)
    {
        int found = 0;
        int arrayDelt[100];
        for (int k = 0; k < 100; k++) 
        {
           arrayDelt[k] = -1;
        }
        switch(deleteChoice)
        {
            case 1:
            printf("Enter the contact name you want to delete: ");
            scanf(" %49[^\n]", data);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name,data) == 0)
                {
                    found = 1;
                    arrayDelt[i] = i;
                    printf("%-3d %-18s %-12s %-18s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);

                }
            }
            if(found == 0)
            {
                printf("Error detected: Entered name doesn't exsists in addressBook.");
            }
            else
            {
               while(1)
                {
                    printf("Enter proper index number you want to delete: ");
                    scanf(" %d", &indexChoice);

                    if (indexChoice < 0 || indexChoice >= 100 || arrayDelt[indexChoice] == -1)
                    {
                        printf("Error: Entered index is invalid or for another contact. Enter again.\n");
                        continue;
                    }

                    int sure;
                    printf("Are you sure? enter '1' for yes, '0' for no: ");
                    scanf(" %d", &sure);
                    if (sure)
                    {
                        Delete(addressBook, indexChoice);
                    }
                    break;
                }
            }
            printf("To go back to main menu enter '0' and if want to delete again still enter '0': ");
            scanf("%d", &stay);
            break;

            case 2:
            printf("Enter the contact number you want to delete: ");
            scanf(" %11[^\n]", data);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone,data) == 0)
                {
                    found = 1;
                    arrayDelt[i] = i;
                    printf("%-3d %-18s %-12s %-18s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);

                }
            }
            if(found == 0)
            {
                printf("Error detected: Entered number doesn't exsists in addressBook.");
            }
            else
            {
                while (1)
                {
                    printf("Enter proper index number you want to delete: ");
                    scanf(" %d", &indexChoice);

                    if (indexChoice < 0 || indexChoice >= 100 || arrayDelt[indexChoice] == -1)
                    {
                        printf("Error: Entered index is invalid or for another contact. Enter again.\n");
                        continue;
                    }

                    int sure;
                    printf("Are you sure? enter '1' for yes, '0' for no: ");
                    scanf(" %d", &sure);
                    if (sure)
                    {
                        Delete(addressBook, indexChoice);
                    }
                    break;
                }
            }
            printf("To go back to main menu enter '0' and if want to delete again still enter '0': ");
            scanf("%d", &stay);
            break;

            case 3:
            printf("Enter the email you want to delete: ");
            scanf(" %49[^\n]", data);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email,data) == 0)
                {
                    found = 1;
                    arrayDelt[i] = i;
                    printf("%-3d %-18s %-12s %-18s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);

                }
            }
            if(found == 0)
            {
                printf("Error detected: Entered name doesn't exsists in addressBook.");
            }
            else
            {
                while (1)
                {
                    printf("Enter proper index number you want to delete: ");
                    scanf(" %d", &indexChoice);

                    if (indexChoice < 0 || indexChoice >= 100 || arrayDelt[indexChoice] == -1)
                    {
                        printf("Error: Entered index is invalid or for another contact. Enter again.\n");
                        continue;
                    }

                    int sure;
                    printf("Are you sure? enter '1' for yes, '0' for no: ");
                    scanf("%d", &sure);
                    if (sure)
                    {
                        Delete(addressBook, indexChoice);
                    }
                    break;
                }
                
            }
            printf("To go back to main menu enter '0' and if want to delete again still enter '0': ");
            scanf("%d", &stay);
            break;

            default:
            printf("Error detected: Entered delete criteria choice is not from given choices!!!\n");
            printf("Now enter only '0' to go back to main menu: ");
            scanf("%d", &stay);
        }
    }
    return;
   
}
// To validate name
int validateName(char *name)
{
    if (strlen(name) < 3)//to validate name length ,should not be less than 3
        {
            printf("Error detected: Name must contain at least 3 characters.\n");
            return 0;
        }
        else if (name[0] == ' ')//To validate name should not be start with space
        {
            printf("Error detected: Name cannot start with a space.\n");
            return 0;
        }
        else if (name[strlen(name) - 1] == ' ')//To validate name shuld not end with space
        {
            printf("Error detected: Name cannot end with a space.\n");
            return 0;
        }
        else
        {
            for (int i = 0; i < strlen(name); i++)
            {
                char c = name[i];

                if (isdigit((c)))//To validate that name must not conatin any digit
                {
                    printf("Error detected: Digits are not allowed.\n");
                    return 0;
                }
                else if (!(isalpha(c) || c == ' ' || c == '.'))//To validate name must not contain any special characters
                {
                    printf("Error detected: Only alphabets, spaces, and dots are allowed.\n");
                    return 0;
                }
                else if (c == ' ' && i + 1 < strlen(name) && name[i + 1] == ' ')//To validate name must not contain consecutive spaces
                {
                    printf("Error detected: Consecutive spaces are not allowed.\n");
                    return 0;
                }
            }
        }
    return 1;
}
// To validate mobile number
int validateMobile(char *number)
{
    if (strlen(number) != 10)//To validate number lenght must be 10 digits
        {
            printf("Error detected: Mobile number is less than 10 digits.\n");
            return 0;
        }
        else if (!(number[0] >= '6' && number[0] <= '9'))//To validate number first digit must be start with between 6 to 9
        {
            printf("Error detected: The first digit is not between 6 and 9.\n");
            return 0;
        }
        else
        {
            int i = 0;
            while (number[i] != '\0')
            {
                if (!(number[i] >= '0' && number[i] <= '9'))//To validate number must not contain other characters than digits
                {
                    printf("Error detected: Mobile number containing other characters.Please enter only digits.\n");
                    return 0;
                }
                i++;
            }
        }
    return 1;
}
// To validate email
int validateEmail(char *email)
{
    int len;
    char *atPtr;
    len = strlen(email);

    if (email[0] == '@' || email[0] == '.')//To validate email should not start with @ or .
    {
        printf("Error detected:Email Cannot start with '@' or '.'.\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            char c = email[i];
            if (isupper((email[i])))//To validate characters must be in lowercase only
            {
                printf("Error detected: Uppercase characters are not allowed.\n");
                return 0;
            }
            if (!((isalnum(c)) || c == '.' || c == '_' ||
                c == '-' || c == '@'))//To validate email not contain other special characters than @,-,_ and .
            {
                printf("Error detected: Contains illegal character '%c'.\n", c);
                return 0;
            }
        }
        atPtr = strchr(email, '@');
        if (atPtr == NULL)//To validate email must contain atleast one @ symbol
        {
            printf("Error detected: Missing '@' symbol.\n");
            return 0;
        }
        else if (strchr(atPtr + 1, '@') != NULL)//To validate email must not contain more than one @ symbol
        {
            printf("Error detected: More than one '@' is not allowed.\n");
            return 0;
        }
        else if(*(atPtr + 1) == '.')//To validate after @ their must be domain name only
        {
            printf("Error detected: After '@' their should be domain name.\n");
            return 0;
        }
        else if (strchr(email, '.') != NULL && strchr(email, '.') < atPtr)//To validate email must not contain more than one dots
        {
            printf("Error detected: More than one dots are not allowed.\n");
            return 0;
        }
        else
        {
            if (strcmp(atPtr + 1, "gmail.com") != 0)//To validate after @ their must be only gmail domain
            {
                printf("Error detected:Other domain not allowed. Only gmail.com domain is allowed.\n");
                return 0;
            }
        }
    }
    return 1;
}
// To validate entered mobile number is unique
int isunique_number(AddressBook *addressBook,char *number)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone,number) == 0)
        {
            printf("Error detected: This mobile number already exists.\n");
            return 0;
        }
    }
    return 1;
}
// To validate entered email is unique
int isunique_email(AddressBook *addressBook,char *email)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
        {
            printf("Error detected: This email id already exists.\n");
            return 0;
        }
    }
    return 1;
}
// To delete contact
void Delete(AddressBook *addressBook, int position)
{
    for (int i = position; i < addressBook->contactCount - 1; i++)
    {
        strcpy(addressBook->contacts[i].name,  addressBook->contacts[i+1].name);
        strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
        strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email);
    }
    addressBook->contactCount--;
    printf("Contact deleted Successfully.\n");
}
