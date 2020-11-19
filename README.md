# Rod-Cutting
Various approaches to solve the Rod Cutting Problem

# Problem-Statement
Suppose you have a rod of length n, and you want to cut up the rod and sell the pieces in
a way that maximizes the total amount of money you get. A piece of length i is worth pi
dollars.

For example:

For the Revenue List


length  i | 1   2   3   4   5   6   7   8   9   10

price p i | 1   5   8   9  10  17  17  20  24   30

What is the maximum amount that a rod of size 4 will fetch?

Program should output:
1. The maximum amount R that the rod of length n can fetch for a given revenue list
2. A list of size of cuts that need to be made to earn R Dollars.

# Different Approaches to the Problem

1. Recursive Approach (rod_cut_recursive.c)

    In this recursive approach, we take the price of the first cut (iterating over the various lengths and taking their price)
    and then recursively get the best price of the remaining rod. In this effort we keep updating the best price whenever, the
    calculated price is more than the best price. At the end of the processing we get the best price of the rod.

2. Memoization Approach (rod_cut_memoize.c)
    The order of the recursive approach is exponential since we consider all possible combinations for obtaining the best price,
    and in this effort we calculate and re-calculate the same sub-problem again and again.

    In order to optimize the recursive approach, we maintain an array of best Price list, where we save the results obtained from
    the recursive calls. This way we ensure that every sub-problem is solved only once, and thus the overall time of the program 
    reduces to the order of about O(n*m).
    
    The performance benefits of this approach over recursive approach are clearly seen through test case 8 and test case 10

3. Dynamic Programming Approach (rod_cut_dynamic.c)
    In this approach, instead of recursing over the various possibilities, we follow an iterative approach, where we calculate
    the best prices of ALL rod lengths starting from 1 and going till n. At the end of the iteration we have the best price
    for all the rod lengths from 1 to n, and thus we have the best price for rod of length n.

    The advantage of this approach is that when we are calculating the best price for rod of length x, we already have the best prices
    for rod of length lesser than x. Hence our iterations reduce to m per size of length x (from 1 to n), where m is the number of price
    options available.
    Hence overall order of the program is O(n*m) and space complexity is of the order of O(n).

--

In order to obtain the various cuts, which led to the best price, we maintain a bestCut array where we save the best first cut for
the various lengths whenever we got a best Price.

By iterating over the array for starting from length = n and then reducing the lengths of the cuts, we get the series of cuts that 
lead to the best Price.

--

PS: The code works only when the input is in expected format. Hence, invalid inputs or incorrect entry will lead the program to fail.
Test cases have been provided and can be taken as reference for valid input format.

Input format is:
(length of rod) (number of prices)
(space separated lengths for which price is provided)
(space separated prices for lengths specified above)

Example Input:

16 10

5 7 10 12 15 20 22 25 30 50

1 5 8 9 10 12 20 31 39 45

16 is the length of rod
10 is the size of the length/price array
5 7 .. are the lengths for which price is provided
1 is the price of rod of length 5
5 is the price of rod of length 7
8 is the price of rod of length 10
and so on..

The length/price array should be input in sorted order, sorted on lengths from least to largest.
