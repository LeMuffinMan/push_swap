
#include <unistd.h>
#include <limits.h>  // For INT_MAX

// Utility function to find the maximum element in the stack.
int find_max(t_list *la)
{
    int max = INT_MIN;
    t_list *tmp = la;
    while (tmp != NULL)
    {
        if (tmp->n > max)
            max = tmp->n;
        tmp = tmp->next;
    }
    return max;
}

// Utility function to check if all elements in a list are sorted in ascending order.
int is_sorted(t_list *la)
{
    t_list *tmp = la;
    while (tmp->next != NULL)
    {
        if (tmp->n > tmp->next->n)
            return 0;
        tmp = tmp->next;
    }
    return 1;
}

// Function to perform radix sort on stacks a and b using base 2 (bitwise operations).
void radix_sort(t_list **la, t_list **lb)
{
    int max = find_max(*la);  // Get the maximum element to determine how many bits we need.
    int max_bits = 0;
    while ((max >> max_bits) != 0)
        max_bits++;  // Find the number of bits needed to represent the max value.

    for (int bit = 0; bit < max_bits; bit++)
    {
        // Step 1: Distribute elements to stack b based on current bit.
        int size = lst_size(*la);
        for (int i = 0; i < size; i++)
        {
            // Check the current bit of the top element of stack a.
            if ((((*la)->n >> bit) & 1) == 0)
            {
                // If the bit is 0, push it to stack b.
                push(lb, la);
                write(1, "pb\n", 3);  // Print the move.
            }
            else
            {
                // If the bit is 1, rotate the element to the back of stack a.
                rotate(la);
                write(1, "ra\n", 3);  // Print the move.
            }
        }

        // Step 2: Gather elements back to stack a (all the 0's should be in front).
        while (*lb != NULL)
        {
            push(la, lb);
            write(1, "pa\n", 3);  // Print the move.
        }
    }
}

int main(int ac, char **av)
{
    t_list *la;
    t_list *lb = NULL;

    // Input validation and initialization.
    if (ac <= 1)
    {
        write(1, "ERROR : not enough arguments\n", 29);
        exit(1);
    }
    init_stack(&la, av);

    if (lst_size(la) <= 3)
        homegrown_algo(la);  // Use another sorting algorithm for small stacks.
    else
        radix_sort(&la, &lb);  // Use radix sort for larger stacks.

    // Check if the stack is sorted.
    if (is_sorted(la))
        write(1, "list sorted\n", 12);
    else
        write(1, "list unsorted\n", 15);

    free_list(&la);
    free_list(&lb);

    return 0;
}

/* Key steps for Radix Sort in Base 2: */
/* Determine the maximum value in your list to know how many bits are needed to represent it. You can use int max = find_max(la); to get the maximum value in stack a. */
/* Iterate through all bits of the numbers, starting from the least significant bit (bit 0) to the most significant bit. */
/* For each bit, distribute the numbers into stack b based on whether that bit is 0 or 1: */
/* Move the numbers with a 0 at the current bit to stack b using pb. */
/* Move the numbers with a 1 at the current bit to the end of stack a using ra. */
/* Gather the numbers back into stack a (so that all the numbers with 0s in the current bit are in front of those with 1s). */
/* Repeat the process for each bit position, moving from LSB to MSB. */
/* Explanation: */
/* find_max: This function finds the maximum value in stack a to determine how many bits are needed for radix sort. */
/* radix_sort: This function sorts the stack a using radix sort in base 2. It distributes elements into stack b based on the current bit, then gathers them back into stack a. It does this for each bit from the least significant to the most significant. */
/* Bitwise operations: The expression ((*la)->n >> bit) & 1 checks the value of the current bit of the element in stack a. */
/* Rotate operations: If the current bit is 1, we use rotate to move the element to the back of stack a. If it's 0, we use push to move it to stack b. */
/* Additional Considerations: */
/* The lst_size function should return the size of the stack a and be used to determine how many elements are in the stack during each pass of the radix sort. */
/* You should handle edge cases, such as when the stack is empty or contains only one element, which would not require sorting. */
/* Radix sort works best for large datasets, and its performance is determined by the number of bits in the largest number, so it has a time complexity of O(n * k), where n is the number of elements and k is the number of bits. */
