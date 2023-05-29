#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Person
{
  char name[255], number[255];

  Person *next, *prev;
};

Person *head = NULL;
Person *tail = NULL;

Person *NewPerson()
{
  Person *temp = (Person *)malloc(sizeof(Person));

  temp->next = temp->prev = NULL;

  return temp;
}

Person *CreatePerson(char *name, char *number)
{
  Person *temp = NewPerson();

  strcpy(temp->name, name);
  strcpy(temp->number, number);

  temp->next = temp->prev = NULL;

  return temp;
}

void PushMid(char *name, char *number)
{
  Person *temp = CreatePerson(name, number);

  if(head == NULL && head == tail)
  {
    head = tail = temp;
  }
  else if(strcmp(head->name, temp->name) > 0)
  {
    head->prev = temp;
    temp->next = head;
    head = temp;
  }
  else if(strcmp(tail->name, temp->name) < 0)
  {
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
  }
  else
  {
    Person *prsn = head;

    while(strcmp(prsn->name, temp->name) < 0)
    {
      prsn = prsn->next;
    }
    prsn->next->prev = temp;
    temp->next = prsn->next;
    prsn->next = temp;
    temp->prev = prsn;
  }
}

void PopMid(char *name)
{
  if(head == NULL)
  {
    puts("No contact to delete");
  }
  else if(head == tail)
  {
    head = tail = NULL;
    free(head);
    free(tail);
  }
  else if(strcmp(head->name, name) == 0)
  {
    Person *newHead = head->next;
    newHead->prev = head->next = NULL;
    free(head);
    head = newHead;
  }
  else if(strcmp(tail->name, name) == 0)
  {
    Person *newTail = tail->prev;
    newTail->next = tail->prev = NULL;
    free(tail);
    tail = newTail;
  }
  else
  {
    Person *prsn = head;

    while(strcmp(prsn->name, name) != 0)
    {
      prsn = prsn->next;

      if(prsn->next == NULL)
      {
        break;
      }
    }
    prsn = prsn->next;

    prsn->next->prev = prsn->prev;
    prsn->prev->next = prsn->next;

    prsn->next = prsn->prev = NULL;
  }
}

void View()
{
  Person *temp = head;
  int count = 0;

  puts("--------------");
  puts("|Contact List|");
  puts("--------------");

  while(temp != NULL)
  {
    count++;
    printf(" %d | %s %s\n", count, temp->name, temp->number);
    puts("------------");
    temp = temp->next;
  }
}

void SaveFile()
{
  FILE *p = fopen("ContactList.txt", "r");
}
int check = 0;

void Menu1()
{
  char personName[255], personNumber[255], buffer, count;
  int menu1;

  puts("Contact Manager");
  puts("1. Add Contact");
  puts("2. Remove Contact");
  puts("3. View Contact");
  puts("4. Exit");
  printf(">> ");

  if(check > 0)
  {
    puts("Invalid input");
    puts("Enter number between 1-4");
  }
  scanf("%d", &menu1);
  getchar();

  switch(menu1)
  {
    case 1:
    {
      check = 0;

      count = 0;
      while(count == 0)
      {
        View();

        printf("Insert Name : ");
        scanf("%[^\n]", personName);
        getchar();

        printf("Insert Number : ");
        scanf("%s", personNumber);
        getchar();

        PushMid(personName, personNumber);

        printf("Press enter twice to exit, else press any key : ");
        scanf("%c", &buffer);
        getchar();

        system("cls");

        if(buffer == '\n')
        {
          count++;
        }
      }

      system("cls");
      Menu1();

      break;
    }
    case 2:
    {
      check = 0;

      do {
        View();

        printf("Insert Name : ");
        scanf("%[^\n]", personName);
        getchar();

        PopMid(personName);
        printf("Press enter to exit, else press any key : ");
        scanf("%c", &buffer);

      } while(buffer != '\n');

      system("cls");
      Menu1();

      break;
    }
    case 3:
    {
      check = 0;

      View();
      printf("Press any key to return : ");
      getchar();

      system("cls");
      Menu1();
      break;
    }
    case 4:
    {
      check = 0;

      puts("Thank you for using our program");
      exit(0);

      break;
    }
    default:
    {
      check++;
      system("cls");
      Menu1();
      break;
    }
  }
}

int main()
{
  Menu1();
  return 0;
}
