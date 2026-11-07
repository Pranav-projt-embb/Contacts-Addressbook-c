#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL)
    {
        printf("Erro detected: Unable to open file\n");
        return;
    }

    fprintf(fp, "Name,Phone,Email\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
       fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);

    printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        return;
    }

    char line[150];

    fgets(line, sizeof(line), fp);

    addressBook->contactCount = 0;

    while (addressBook->contactCount < MAX_CONTACTS && fgets(line, sizeof(line), fp) != NULL)
    {
        if (sscanf(line, " %49[^,],%19[^,],%49[^\n]",
                   addressBook->contacts[addressBook->contactCount].name,
                   addressBook->contacts[addressBook->contactCount].phone,
                   addressBook->contacts[addressBook->contactCount].email) == 3)
        {
            addressBook->contactCount++;
        }
    }

    fclose(fp);
}
