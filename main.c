/*
    Comp 322 - Fall 2024
    Lab 4 - Hole Fitting Algorithms
    Justin Ayson
    To simulate memory allocation with hole-fitting algorithms (First-fit, Best-fit) and
    implement deallocation and defragmentation of memory blocks.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Block {
    int id;
    int start;
    int end;
    struct Block *next;
} Block;

typedef struct Allocated {
    Block *head;
    int count;
    int pm_size;
} Allocated;

Allocated *allocatedBlocks;

void createAllocatedBlocks() {
    int size = 0;
    printf("Enter the size of physical memory: ");
    scanf("%d", &size);
    while(getchar() != '\n');

    allocatedBlocks = malloc(sizeof(Allocated));
    allocatedBlocks->pm_size = size;
    allocatedBlocks->count = 0;
    allocatedBlocks->head = NULL;
    return;
}

void printAllocatedBlocks() {
    Block *curr = allocatedBlocks->head;
    printf("\nID\tStart\tEnd\n");
    printf("-------------------\n");
    while(curr != NULL) {
        printf("%d\t%d\t%d\n", curr->id, curr->start, curr->end);
        curr = curr->next;
    }
    return;
}

void allocateFirstFit() {
    int id = 0;
    int size = 0;
    printf("Enter block id: ");
    scanf("%d", &id);
    while(getchar() != '\n');
    printf("Enter block size: ");
    scanf("%d", &size);
    while(getchar() != '\n');

    if(size > allocatedBlocks->pm_size) {
        printf("\nINVALID: Block size is larger than remaining memory!\n");
        return;
    }
    if(allocatedBlocks->count == 0) {
        Block *newBlock = malloc(sizeof(Block));
        newBlock->id = 0;
        newBlock->start = 0;
        newBlock->end = size;
        newBlock->next = NULL;

        allocatedBlocks->head = newBlock;
        allocatedBlocks->pm_size -= size;
        allocatedBlocks->count++;
        printAllocatedBlocks();
        return;
    }
    Block *curr = allocatedBlocks->head;
    int start = 0;
    int end = 0;
    int hole = 0;
    while(curr != NULL) {
        if(curr->id == id) {
            printf("\nINVALID: ID already exists\n");
            return;
        }
        curr = curr->next;
    }
    curr = allocatedBlocks->head;
    while(curr != NULL) {
        start = curr->end;
        if(curr->next != NULL) {
            end = curr->next->start;
            hole = abs(end - start);
        }
        else
            hole = allocatedBlocks->pm_size;
        if(hole >= size) {
            Block *newBlock = malloc(sizeof(Block));
            newBlock->id = id;
            newBlock->start = curr->end;
            newBlock->end = curr->end + size;
            newBlock->next = curr->next;

            curr->next = newBlock;
            allocatedBlocks->pm_size -= size;
            allocatedBlocks->count++;
            printAllocatedBlocks();
            return; 
        }
        curr = curr->next;
    }
    printf("\nINVALID: No fitting hole\n");
    return;
}

void allocateBestFit() {
    int id = 0;
    int size = 0;
    printf("Enter block id: ");
    scanf("%d",&id);
    while(getchar() != '\n');
    printf("Enter block size: ");
    scanf("%d", &size);
    while(getchar() != '\n');

    if(size > allocatedBlocks->pm_size) {
        printf("\nINVALID: Block size is larger than remaining memory!\n");
        return;
    }
    if(allocatedBlocks->count == 0) {
        Block *newBlock = malloc(sizeof(Block));
        newBlock->id = 0;
        newBlock->start = 0;
        newBlock->end = size;
        newBlock->next = NULL;

        allocatedBlocks->head = newBlock;
        allocatedBlocks->pm_size -= size;
        allocatedBlocks->count++;
        printAllocatedBlocks();
        return;
    }
    Block *curr = allocatedBlocks->head;
    Block *best = NULL;
    int bestHole = __INT_MAX__;
    int start = 0, end = 0, hole = 0;
    while(curr != NULL) {
        if(curr->id == id) {
            printf("\nINVALID: ID already exists\n");
            return;
        }
        curr = curr->next;
    }
    curr = allocatedBlocks->head;
    while(curr != NULL) {
        start = curr->end;
        if(curr->next != NULL) {
            end = curr->next->start;
            hole = end - start;
        }
        else
            hole = allocatedBlocks->pm_size;
        if(hole >= size && hole < bestHole) {
            best = curr;
            bestHole = hole;
        }
        curr = curr->next;
    }
    if(best != NULL) {
        Block *newBlock = malloc(sizeof(Block));
        newBlock->id = id;
        newBlock->start = best->end;
        newBlock->end = best->end + size;
        newBlock->next = best->next;

        best->next = newBlock;
        allocatedBlocks->pm_size -= size;
        allocatedBlocks->count++;
        printAllocatedBlocks();
        return;
    }
    printf("\nINVALID: No hole found large enough\n");
    return;
}

void deallocateBlock() {
    int id = 0;
    Block *curr = allocatedBlocks->head;
    Block *prev = NULL;
    printf("Enter block id: ");
    scanf("%d", &id);
    while(curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL) {
        printf("\nINVALID: id not found\n");
        return;
    }
    prev->next = curr->next;
    allocatedBlocks->pm_size += curr->end - curr->start;
    allocatedBlocks->count--;
    free(curr);
    printAllocatedBlocks();
    return;
}

int main(void) {
    int input = 0;
    do {
        printf("\nHole-fitting Algorithms\n");
        printf("-----------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Allocate memory for block using First-fit\n");
        printf("3) Allocate memory for block using Best-fit\n");
        printf("4) Deallocate memory for block\n");
        printf("5) Defragment memory\n");
        printf("6) Quit program\n");
        
        printf("\nEnter selection: ");
        scanf("%d", &input);
        while(getchar() != '\n');
        switch(input) {
            case 1:
                createAllocatedBlocks();
                break;
            case 2:
                allocateFirstFit();
                break;
            case 3:
                allocateBestFit();
                break;
            case 4:
                deallocateBlock();
                break;
            case 5:
                printf("Defrag");
                break;
            case 6:
                printf("Quitting");
                break;
            default:
                printf("INVALID input, try again");
                break;
        }
    } while(input != 6);
    return 1;
}
