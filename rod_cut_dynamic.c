#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

unsigned long long *bestPriceList = NULL;

unsigned int *bestCut = NULL;


unsigned long long getBestPrice(unsigned int cut_length, unsigned int num_price_options, long *length, long *price)
{
    unsigned int bestPrice = 0;
    unsigned int currentPrice = 0;
    unsigned int remaining_length = 0;
    
    for(int curr_length = 1; curr_length <= cut_length; curr_length++) {
        bestPrice = 0;
        for(int i = 0; i < num_price_options; i++) {
            currentPrice = 0;
            /* cut with current size and calculate price for rest
            */
            if(curr_length < length[i]) {
                /* we cannot cut further */
                break;
            } else if(curr_length == length[i]) {
                currentPrice = price[i];
            } else {
                remaining_length = curr_length - length[i];
                currentPrice = price[i] + bestPriceList[remaining_length - 1];
            }
            if(currentPrice > bestPrice) {
                bestPrice = currentPrice;
                bestCut[curr_length - 1] = length[i];
            }
        }
        bestPriceList[curr_length - 1] = bestPrice;

    }

    return bestPriceList[cut_length - 1];
}

int main() {
    unsigned int n; 
    unsigned int m; 
    
    scanf("%d %d", &n, &m);
    
    /* Lengths have to be input in sorted order beginning from the least to the max */
    long *length = malloc(sizeof(long) * m);
    for(int i = 0; i < m; i++){
       scanf("%ld",&length[i]);
    }
    long *price = malloc(sizeof(long) * m);
    for(int i = 0; i < m; i++){
       scanf("%ld",&price[i]);
    }
    
    //scanf("%d %d\n", &n, &x);
    
    printf("Length/Price of rod:\n");
    for(int i = 0; i < m; i++) {
        printf(" %ld: ", length[i]);
        printf(" %ld\n", price [i]);
    }

    bestPriceList = (unsigned long long *)calloc(n, sizeof(unsigned long long));    
    if(bestPriceList == NULL) {
        printf("memory issue\n");
        exit(-1);
    }

    bestCut = (unsigned int *)calloc(n, sizeof(unsigned int)); 
    if(bestCut == NULL) {
        printf("memory issue\n");
        exit(-1);
    }
    // Calculate the best price that the rod of length 'n' can fetch after cutting as per price list 'price'
    unsigned long long bestPrice = getBestPrice(n, m, length, price);
    printf("Best Price for rod of length %d is %llu\n", n, bestPrice);
    
    /* Give the best cuts for the best Price for length x*/
    //scanf("%d", &x);
    printf("Rods should be cut in the following lengths:\n");
    int len = n;
    while(len > 0) {
        if(bestCut[len - 1] == 0) {
            break;
        }
        printf("%d, ", bestCut[len - 1]);
        len -= bestCut[len - 1]; 
    }
    printf("\n"); 
    
    return 0;
}
