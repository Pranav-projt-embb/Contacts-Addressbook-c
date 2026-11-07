# Contacts Addressbook in C

A console-based **Contacts Addressbook** application written in **C**. It stores contacts (name, phone number and email), lets you create, search, edit, delete and sort them, validates every input, and saves everything permanently in a CSV file so your contacts are still there the next time you run the program.

---

## Table of Contents

1. [About the Project](#about-the-project)
2. [Features](#features)
3. [Project Structure](#project-structure)
4. [Requirements](#requirements)
5. [Getting Started](#getting-started)
6. [How to Use](#how-to-use)
7. [Input Validation Rules](#input-validation-rules)
8. [Data Storage](#data-storage)
9. [Code Overview](#code-overview)
10. [Limitations](#limitations)
11. [Future Improvements](#future-improvements)
12. [Author](#author)

---

<a id="about-the-project"></a>
## About the Project

This project is a menu-driven contact manager that runs in the terminal. While the program runs, contacts are kept in memory as an array of structures. When the program starts, they are loaded from `contacts.csv`, and when you choose **Save entered contacts and Exit**, they are written back to the same file.

The code is split into separate modules (menu, contact operations, file handling) using header files and a Makefile, so each part has one clear job.

**Concepts used:** structures, arrays, pointers, string handling (`string.h`), character checks (`ctype.h`), file handling (`fopen`, `fgets`, `sscanf`, `fprintf`), modular programming with header files, and Makefile builds.

<a id="features"></a>
## Features

- **Create contact**: add a name, phone number and email, with validation and duplicate checks.
- **Search contact**: find contacts by name, phone number or email.
- **Edit contact**: change the name, phone number or email of an existing contact.
- **Delete contact**: delete by name, phone number or email, with a confirmation step.
- **List contacts with sorting**: display all contacts sorted by name, phone number or email.
- **Unique contacts**: the same phone number or email cannot be saved twice.
- **Input validation**: invalid names, phone numbers and emails are rejected with a clear error message, and you are asked to enter them again.
- **Permanent storage**: contacts are saved to and loaded from a CSV file.
- **Duplicate names handled**: when several contacts share a name, they are listed with index numbers so you can pick the right one to edit or delete.

<a id="project-structure"></a>
## Project Structure

```
AddressBook/
├── main.c             # Program entry point: main menu and menu loop
├── contact.c          # Create, search, edit, delete, list/sort and validation functions
├── contact.h          # Contact and AddressBook structures, function declarations
├── file.c             # Save contacts to CSV / load contacts from CSV
├── file.h             # File function declarations
├── Makefile           # Build instructions
├── contacts.csv       # Contact data file (sample contacts included)
├── documentation.txt  # Short description of every function
├── demo               # demo screenshots
├── .gitignore         # Keeps build output out of the repository
└── README.md          # Project documentation
```

<a id="requirements"></a>
## Requirements

- A C compiler such as **GCC**
- **make** (optional; you can also compile with a single `gcc` command)
- Linux, macOS, or Windows with MinGW / WSL

<a id="getting-started"></a>
## Getting Started

**1. Clone the repository**

```bash
git clone https://github.com/Pranav-projt-embb/Contacts-Addressbook-c.git
cd Contacts-Addressbook-c
```

**2. Build**

```bash
make
```

This creates the executable `26018F_380_AddressBook`.

If you do not have `make`, compile directly:

```bash
gcc main.c contact.c file.c -o 26018F_380_AddressBook
```

**3. Run**

```bash
./26018F_380_AddressBook
```

> Run the program from inside the project folder. It reads and writes `contacts.csv` in the folder you run it from.

**4. Clean build files (optional)**

```bash
make clean
```

<a id="how-to-use"></a>
## How to Use

When the program starts, it shows the main menu:

```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save entered contacts and Exit
Enter your choice:
```

Type the option number and press Enter.

| Option | What it does |
|--------|--------------|
| **1. Create contact** | Asks for name, phone number and email. Each value is checked and asked again until it is valid. A maximum of 100 contacts can be stored. |
| **2. Search contact** | Choose to search by **name**, **phone number** or **email**, then type the value. All contacts that match exactly are displayed. You can keep searching until you enter `0`. |
| **3. Edit contact** | Choose what to edit (**name**, **phone** or **email**), type the current value to find the contact, then type the new value. The new value is validated first. If several contacts have the same name, pick one using the index shown. |
| **4. Delete contact** | Choose to delete by **name**, **phone** or **email**. Matching contacts are shown with index numbers. Enter the index and confirm with `1`. The remaining contacts shift up automatically. |
| **5. List all contacts** | Choose how to sort: **1** by name, **2** by phone number, **3** by email. Enter `1` to display the list (or `0` to go back). Contacts are shown in ascending order. |
| **6. Save entered contacts and Exit** | Writes all contacts to `contacts.csv` and closes the program. |

> **Important:** Changes are written to the file only when you choose option **6**. Always exit with option 6 so your work is saved.

### Sample Session

Listing contacts sorted by name (option 5, then sort option 1):

```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save entered contacts and Exit
Enter your choice: 5
Select criteria to delete contact details:
1. Sort by name
2. Sort by phone number
3. Sort by email
Enter your choice: 1
Enter '1' to list contacts, or '0' to go back to main menu: 1
--------------------------------------------------------------------

No.  Name                 Phone           Email                    
--------------------------------------------------------------------
1    Indela Naren         9887766554      naren333indela@gmail.com 
2    Pranav More          9322783758      pran@gmail.com           
--------------------------------------------------------------------
```

Creating a contact with invalid input (the program shows the error and asks again):

```
Enter your choice: 1
Enter name: Jo1
Error detected: Digits are not allowed.
Enter name: Ram Kumar
Enter phone number: 5123456789
Error detected: The first digit is not between 6 and 9.
Enter phone number: 9876500001
Enter Email id : ram@yahoo.com
Error detected:Other domain not allowed. Only gmail.com domain is allowed.
Enter Email id : ram@gmail.com
Contact created successfully!
```

Searching a contact:

```
Enter your choice: 2
If you want exit enter 0 or  to continue enter 1 : 1
Enter proper search choice
Choice 1-> Name
Choice 2-> Mobile number
Choice 3-> Email.id
Enter your choice: 
1
enter the name: Pranav More
--------------------------------------------------------------------

No.  Name                 Phone           Email                    
--------------------------------------------------------------------
2    Pranav More          9322783758      pran@gmail.com           
--------------------------------------------------------------------
If you want to search again if yes enter '1',no enter '0' : 
```

<a id="input-validation-rules"></a>
## Input Validation Rules

Every value is checked before it is stored (also when editing).

**Name**

- At least 3 characters, up to 49 characters
- Only alphabets, spaces and dots (`.`) are allowed
- No digits or other special characters
- Cannot start or end with a space
- No two spaces in a row

**Phone number**

- Exactly 10 digits, digits only
- First digit must be between 6 and 9
- Must be unique (not already saved for another contact)

**Email**

- Must end with `@gmail.com` (only the `gmail.com` domain is accepted)
- Only lowercase letters, digits, `.`, `_` and `-` are allowed before the `@`, and exactly one `@` is allowed
- Cannot start with `@` or `.`
- The only dot in the address is the one in `gmail.com` (no dots before the `@`)
- Must be unique (not already saved for another contact)

<a id="data-storage"></a>
## Data Storage

Contacts are stored in `contacts.csv` in the following format. The first line is a header, and each following line is one contact:

```
Name,Phone,Email
Anita Sharma,9123456780,anitasharma@gmail.com
Ravi Kumar,9876543210,ravikumar@gmail.com
Suresh Patil,8123456789,sureshpatil@gmail.com
```

- On start-up the file is loaded automatically. If it does not exist, the program starts with an empty address book and creates the file when you save.
- Names never contain commas (the validation does not allow them), so the CSV format stays safe.
- Sorting rearranges the stored order, so the file is saved in the order of the last sort you used.

<a id="code-overview"></a>
## Code Overview

### Data structures (`contact.h`)

```c
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
```

### Functions

| Function | File | Purpose |
|----------|------|---------|
| `main()` | `main.c` | Shows the menu in a loop and calls the selected operation |
| `initialize()` | `contact.c` | Sets the contact count to 0 and loads contacts from the CSV file |
| `createContact()` | `contact.c` | Reads, validates and stores a new contact |
| `searchContact()` | `contact.c` | Searches by name, phone or email and prints all matches |
| `editContact()` | `contact.c` | Updates the name, phone or email of a contact |
| `deleteContact()` | `contact.c` | Finds matching contacts, asks for the index and confirmation, then deletes |
| `Delete()` | `contact.c` | Removes a contact and shifts the remaining contacts up |
| `listContacts()` | `contact.c` | Sorts contacts by name, phone or email and prints them |
| `validateName()` | `contact.c` | Checks the name rules |
| `validateMobile()` | `contact.c` | Checks the phone number rules |
| `validateEmail()` | `contact.c` | Checks the email rules |
| `isunique_number()` | `contact.c` | Makes sure the phone number is not already used |
| `isunique_email()` | `contact.c` | Makes sure the email is not already used |
| `saveContactsToFile()` | `file.c` | Writes all contacts to `contacts.csv` |
| `loadContactsFromFile()` | `file.c` | Reads `contacts.csv` and fills the address book |

A more detailed description of each function is available in [documentation.txt](documentation.txt).

<a id="limitations"></a>
## Limitations

- A maximum of **100 contacts** can be stored.
- Only **`gmail.com`** email addresses in lowercase are accepted.
- Search is an **exact, case-sensitive** match (for example, `ravi kumar` will not find `Ravi Kumar`).
- Menu choices and yes/no prompts expect **numbers**; typing letters there is not handled.
- Contacts are saved **only when you exit using option 6**.

<a id="future-improvements"></a>
## Future Improvements

- Case-insensitive and partial-name search
- Accept email addresses from any valid domain
- Use dynamic memory (`malloc`) so there is no fixed limit of 100 contacts
- Better input handling for non-numeric menu input
- Auto-save after every change
- Faster sorting using `qsort`

<a id="author"></a>
## Author

**More Pranav Shivaji**

- GitHub: [More Pranav Shivaji](https://github.com/Pranav-projt-embb)
- LinkedIn: [More Pranav](https://www.linkedin.com/in/more-pranav-b98290381)

Suggestions and improvements are welcome.
