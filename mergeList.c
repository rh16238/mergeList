//#region Includes
#include <stdlib.h>
#include <stdio.h>

//#endregion Includes
//#region Variables and Defines
//#endregion Variables and Defines
//#region Structs
typedef struct node_t node_t;
struct node_t
{
    unsigned int v;
    struct node_t* next;
};
//#endregion Structs
//#region Prototypes
void testFunction();
node_t *addItem (unsigned int, node_t *);
node_t *createList(unsigned int);
//#endregion Prototypes

//Takes a pointer to 2 lists
//returns a new list pointer to the merged list
//Destroys initial list in process.
node_t* mergeNodes(struct node_t *listA, struct node_t *listB)
{
  node_t* listAHead = listA;
  node_t* listBHead = listB;
  node_t*  nodePointer;
  node_t** mergeHeadPointer = &nodePointer;
  while ((listAHead)&&(listBHead))
  {
    if ((listAHead->v) < (listBHead -> v))
    {
      *mergeHeadPointer = listAHead;
      listAHead = listAHead -> next;
    }
    else
    {
      *mergeHeadPointer = listBHead;
      listBHead = listBHead -> next;
    }
    mergeHeadPointer = &((*mergeHeadPointer)->next);
  }
  if (listAHead){*mergeHeadPointer = listAHead;}
  else {*mergeHeadPointer = listBHead;}
  return nodePointer;

}

int main(int n, char *args[])
{
    testFunction();
}


//#region Testing Functions

//Takes a pointer to a list
//Frees the lists malloc'd resources.
void freeList(node_t *list)
{
  if (list->next) {freeList(list -> next);}
   free(list);
}
//Takes a list
//Prints its contents to console.
void printList(node_t *list)
{
    int i = 0;
    while(list)
    {
        printf("List Index %d: %d\n",i,list->v );
        list = (node_t *)list->next;
    }
}

//Takes a list and an array of ints (and the arrays length)
//checks list matches array values, returns 1 if a difference if found
int compareList(node_t *listA, unsigned int  *listB, int length)
{
    int i = 0;
    while(listA && (i < length))
    {

        if ((*listA).v != listB[i]) {return 1;}
        listA = listA->next;
        i++;
    }
    if (i > length) {return 1;}
    if (listA) {return 1;}
    return 0;
}

//Takes an unsigned int for a headpointer for a new list
//Returns a pointer to a new node_t list containing specified value
node_t *createList(unsigned int value)
{
    node_t *newHead = malloc(sizeof(node_t));
    newHead->next = NULL;
    newHead->v = value;
    return newHead;
}

//Takes a value and a list
//returns the list with the value added.
//List pointer may be NULL initially.
node_t *addItem (unsigned int value, node_t *head)
{
    node_t *list;
    if (!head)
    {
        head = createList(value);
        return head;
    }
    list = head;
    while (list -> next)
    {
        list = (node_t *)list -> next;
    }
    list -> next = malloc(sizeof(node_t));
    list -> next -> next = NULL;
    list -> next -> v = value;
    return head;
}

//returns list containing digits 1,3,5,7,9
node_t *oddDigitList()
{
    node_t *head = NULL;
    head = addItem(1, head);
    head = addItem(3, head);
    head = addItem(5, head);
    head = addItem(7, head);
    head = addItem(9, head);
    return head;
}

//returns list containing digits 0,2,4,6,8
node_t *evenDigitList()
{
    node_t *head = NULL;
    head = addItem(0, head);
    head = addItem(2, head);
    head = addItem(4, head);
    head = addItem(6, head);
    head = addItem(8, head);
    return head;
}

//returns list designed to cause dangling pointer errors at the end of the list.
node_t *errorAtEndPointerList()
{
    node_t *head = NULL;
    head = addItem(1, head);
    head = addItem(2, head);
    head = addItem(3, head);
    head = addItem(4, head);
    head = addItem(5, head);
    head = addItem(6, head);
    head = addItem(7, head);
    head = addItem(8, head);
    head = addItem(9, head);
    return head;
}

//returns empty list for error checking
node_t *emptyList()
{
    node_t *head = NULL;
    return head;
}

//Tests functionality of functionality
void testFunction()
{
node_t* listA = evenDigitList();
node_t* listB = oddDigitList();
listA = mergeNodes(listA, listB);
unsigned int completeList [10] = {0,1,2,3,4,5,6,7,8,9};
if(compareList(listA, completeList,10)){printf("Error, completeList does not match even and odd digits merged\n");}
freeList(listA);
freeList(listB);

listA = evenDigitList();
listA = mergeNodes(listA, NULL);
unsigned int completeEvenList [5] = {0,2,4,6,8};
if(compareList(listA, completeEvenList,5)){printf("Error, completeList does not match even digits merged with empty list\n");}

listA = mergeNodes(NULL, NULL);
if (listA != NULL){printf("Error, listA not NULL when EmptyList merged with empty list\n");}
printf("All tests completed!\n");


}
//#endregion Testing Functions
