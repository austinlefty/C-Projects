#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node *next;
} node;

node *head = NULL;
int size = 0;

void list_append(int element)
{
    printf("\nAdded to list: %d\n\n", element);
    node *temp, *traverse;

    temp = (node*)malloc(sizeof(node));
    temp -> element = element;
    temp -> next = NULL;

    if(head == NULL)
    {
        head = temp;
        size++;
    }

    else
    {
        traverse = head;
        while(traverse -> next != NULL)
        {
            traverse = traverse -> next;
        }

        traverse -> next = temp;
        size++;
    }
}

unsigned int list_insert_at(int element, unsigned int location)
{
    // Incomplete //
}

void *list_remove_at(unsigned int location)
{
    // Incomplete //
}

void list_remove(int element)
{
    // Incomplete //
}

void *list_to_array()
{
    int array[size];

    node *traverse = head;
    printf("\n");

    for (int i = 0; i < size; i++)
    {
        array[i] = traverse -> element;
        traverse = traverse -> next;
        printf("[%d", array[i]);
        printf("] ");
    }

    printf("\n\n");
}

unsigned int list_size()
{
    return size;
}

bool list_is_empty()
{
    return (head == NULL);
}

int main()
{
    int value;
    int location;

    while(1)
    {
        printf("*            LINKED LIST:            *\n");
        printf("* 1: Add at end                      *\n");
        printf("* 2: Add at particular location      *\n");
        printf("* 3: Remove at particular location   *\n");
        printf("* 4: Remove particular element       *\n");
        printf("* 5: Display array                   *\n");
        printf("* 6: Display number of elements      *\n");
        printf("* 7: Check if list is empty          *\n");
        printf("* 8: Quit Program                    *\n\n");

        printf("Enter a menu option: ");
        scanf("%d", &value);

        if(value == 1)
        {
            printf("\nEnter a value: ");
            scanf("%d", &value);
            list_append(value);
        }

        else if(value == 2)
        {
            printf("\nEnter a value: ");
            scanf("%d", &value);
            printf("\nEnter a location: ");
            scanf("%d", &location);
            list_insert_at(value, location);
        }

        else if(value == 3)
        {
            printf("\nEnter a location: ");
            scanf("%d", &location);
            list_remove_at(location);
        }

        else if(value == 4)
        {
            printf("\nEnter a value: ");
            scanf("%d", &value);
            list_remove(value);
        }

        else if(value == 5)
        {
            list_to_array();
        }

        else if(value == 6)
        {
            printf("\n%d", list_size());
            printf(" nodes in this list\n\n");
        }

        else if(value == 7)
        {
            if(list_is_empty() == 1)
            {
                printf("\nList is empty\n\n");
            }
            else
            {
                printf("\nList is not empty\n\n");
            }
        }

        else if(value == 8)
        {
            printf("\nGoodbye.");
            exit(0);
        }

        else
        {
            printf("\nInvalid choice. Try again.\n\n");
        }
    }

    return 0;
}
