/*
    Comp 322 - Fall 2024
    Lab 4 - Hole Fitting Algorithms
    Justin Ayson
    To simulate memory allocation with hole-fitting algorithms (First-fit, Best-fit) and
    implement deallocation and defragmentation of memory blocks.
*/
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int input = 0;
    do
    {
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
        printf("\n");

        switch(input) {
            case 1:
                printf("Enter params");
                break;
            case 2:
                printf("First-fit");
                break;
            case 3:
                printf("Best-fit");
                break;
            case 4:
                printf("Deallocate");
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
    

    return 0;
}
