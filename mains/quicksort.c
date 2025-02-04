
#include <unistd.h>

void    quicksort(t_list **la, t_list **lb, t_list *start, t_list *end) {
    if (!start || start == end || start == end->prev) // base case: one or no element
        return;

    t_list *pivot = start;
    t_list *left = start->next;
    t_list *right = end;

    // Partitioning: elements smaller than pivot go to the left,
    // elements greater than pivot go to the right.
    while (left != right && left != right->next) {
        while (left != end && left->n < pivot->n) {
            left = left->next;
        }
        while (right != start && right->n > pivot->n) {
            right = right->prev;
        }
        if (left != right && left != right->next) {
            // Swap values to reorder
            int tmp = left->n;
            left->n = right->n;
            right->n = tmp;
        }
    }

    // At this point, 'right' is the correct position for the pivot.
    // Swap pivot to its correct position.
    int tmp = pivot->n;
    pivot->n = right->n;
    right->n = tmp;

    // Recursively sort left and right partitions
    quicksort(la, lb, start, right->prev);
    quicksort(la, lb, right->next, end);
}

void    quicksort_algorithm(t_list **la, t_list **lb) {
    if (!*la)
        return;

    // Find the start and end of the list (circular linked list)
    t_list *start = *la;
    t_list *end = start;
    while (end->next != start) {
        end = end->next;
    }

    // Call the quicksort function
    quicksort(la, lb, start, end);
}

// Main function with the quicksort implementation
int	main(int ac, char **av) {
    t_list	*la;
    t_list *lb = NULL;

    if (ac <= 1) {
        printf("ERROR : not enough arguments\n");
        exit(1);
    }

    init_stack(&la, av);

    if (lst_size(la) <= 3) {
        homegrown_algo(la);
    } else {
        quicksort_algorithm(&la, &lb);  // Use quicksort here
    }

    free_list(&la);
    free_list(&lb);
    return (0);
}

/* Key Changes: */
/* Partitioning logic: Quicksort relies on partitioning the list into two sublists based on a pivot element. You’ll need a function to do this partitioning. */
/* Recursive sorting: You need to recursively apply quicksort to the left and right partitions. */
/* Handling linked lists: Make sure to correctly handle circular linked lists in the partitioning and sorting process. */
/* Let's break down the steps and provide an implementation outline for quicksort. */
/**/
/* 1. Partitioning the List: */
/* To partition the list, you can choose the first element of the list as the pivot, then reorder the list such that all elements less than the pivot are placed before it, and all elements greater than the pivot are placed after it. */
/**/
/* You'll need to traverse the list and move elements around (using push, swap, rotate, etc.) to divide it into two parts. */
/* Once the partitioning is complete, the pivot element will be in its correct position in the sorted list. */
/* 2. Recursive Quicksort: */
/* After partitioning, apply the quicksort algorithm recursively to the left and right parts of the list. */
/**/
/* 3. Helper Functions for QuickSort: */
/* You’ll need a few helper functions: */
/**/
/* partition function: This will partition the list around a pivot. */
/* quicksort function: This will recursively apply quicksort on the left and right sublists. */
/* Here’s an example implementation of quicksort in your code structure: */
/**/
/* Key Points: */
/* Partitioning (partition): This function is crucial because quicksort works by partitioning the list around a pivot element, placing smaller elements on the left side and larger ones on the right. This partitioning is done using a two-pointer approach. */
/**/
/* Recursive Calls: After partitioning the list around the pivot, you recursively apply the same logic to the left and right parts of the list. */
/**/
/* Handling Circular Lists: This algorithm works with circular linked lists by taking care of the next and prev pointers properly. The list must be partitioned and swapped correctly without breaking the circular nature of the list. */

