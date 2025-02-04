
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Function to get the number of digits in a number
int get_num_digits(int n)
{
    int digits = 0;
    if (n < 0) n = -n;  // handle negative numbers
    while (n != 0)
    {
        n /= 10;
        digits++;
    }
    return digits == 0 ? 1 : digits;
}

// Function to find the maximum number in the stack
int find_max(t_list *la)
{
    t_list *tmp = la;
    int max = tmp->n;
    while (tmp != NULL)
    {
        if (tmp->n > max)
            max = tmp->n;
        tmp = tmp->next;
    }
    return max;
}

// Function to sort using radix sort
void radix_sort(t_list **la, t_list **lb)
{
    int max = find_max(*la); // find the max value in the list
    int max_digits = get_num_digits(max); // get the number of digits in the max value
    int divisor = 1;

    for (int i = 0; i < max_digits; i++) // for each digit
    {
        // Step 1: Push elements to `b` based on the current digit
        while (*la != NULL)
        {
            int digit = (*la)->n / divisor % 10;
            if (digit == 0)
            {
                push(lb, la); // push to stack `b`
                printf("pb\n");
            }
            else
            {
                rotate(la); // rotate in `a`
                printf("ra\n");
            }
        }

        // Step 2: Push elements back from `b` to `a`
        while (*lb != NULL)
        {
            push(la, lb); // push back to stack `a`
            printf("pa\n");
        }

        // Step 3: Move to the next digit
        divisor *= 10;
    }
}

// Main function
int main(int ac, char **av)
{
    t_list *la;
    t_list *lb = NULL;

    if (ac <= 1)
    {
        printf("ERROR: not enough arguments\n");
        exit(1);
    }
    
    init_stack(&la, av);
    
    if (lst_size(la) <= 3)
        homegrown_algo(la); // For small stacks, use your existing algorithm
    else
        radix_sort(&la, &lb); // For larger stacks, use radix sort
    
    free_list(&la);
    free_list(&lb);
    
    return 0;
}

/* Radix Sort Overview */
/* Radix sort works by sorting the numbers based on their individual digits. It starts from the least significant digit (LSD) and moves to the most significant digit (MSD). */
/* For each digit (from LSD to MSD), we perform counting sort (by grouping numbers according to their digits). */
/* We use two stacks (a and b) and the operations available to simulate the counting sort. */
/* Steps to Implement Radix Sort: */
/* Determine the maximum number of digits: This will be determined by the maximum value in the stack (a). */
/* Perform sorting by digit: */
/* For each digit, push elements to b based on their current digit (using pb). */
/* After processing all elements, rotate them back to a (using pa). */
/* Repeat for each digit in the number. */

/* Explanation: */
/* get_num_digits(int n): This function calculates the number of digits in a given integer (important for determining how many passes are needed for the radix sort). */
/* find_max(t_list *la): This function finds the largest number in the stack a. This will help determine the maximum number of digits. */
/* radix_sort(t_list **la, t_list **lb): */
/* This function iterates over each digit, starting from the least significant digit. */
/* For each pass, elements are pushed to stack b if the current digit (determined by (*la)->n / divisor % 10) is 0, and elements are rotated if the digit is non-zero. */
/* After processing all elements, they are pushed back into stack a. */
/* The divisor is multiplied by 10 each time, to move to the next digit. */

