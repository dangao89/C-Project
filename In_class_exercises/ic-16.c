#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int value;
    struct node *next;
};

int main ()
{
    struct node *head = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        // Allocate memory for a new node
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->value = num;
        new_node->next = NULL;
        if (head == NULL) {
            head = new_node; // First node becomes head
        } else {
            struct node *current = head;
            // Traverse to the end of the list
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node; // Link the new node at the end
        }
    }       
    // Print the linked list
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
    // Free the allocated memory
    current = head;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}