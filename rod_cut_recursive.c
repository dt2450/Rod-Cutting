#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

unsigned int *bestCut = NULL;

unsigned long long getBestPrice(unsigned int cut_length, unsigned int num_price_options, unsigned int index, long *length, long *price)
{
    unsigned int bestPrice = 0;
    unsigned int currentPrice = 0;
    unsigned int remaining_length = cut_length;
    
    for(int i = index; i < num_price_options; i++) {
        currentPrice = 0;
        remaining_length = cut_length;
        /* cut with current size and calculate price for rest
         */
        if(remaining_length < length[i]) {
            /* we cannot cut further */
            //currentPrice = 0;
            break;
        } else if(remaining_length == length[i]) {
            currentPrice += price[i];
            remaining_length = 0;
            if(currentPrice > bestPrice) {
                bestPrice = currentPrice;
                bestCut[cut_length - 1] = length[i];
            }
            break;
        } else {
            remaining_length -= length[i];
            currentPrice += price[i];
            unsigned int remainingPrice = getBestPrice(remaining_length, num_price_options, index, length, price);
            currentPrice += remainingPrice;
        }
        if(currentPrice > bestPrice) {
            bestPrice = currentPrice;
            bestCut[cut_length - 1] = length[i];
        }
    }

    return bestPrice;
}

int main() {
    unsigned int n; 
    unsigned int m; 
    scanf("%d %d", &n, &m);
    long *length = malloc(sizeof(long) * m);
    for(int i = 0; i < m; i++){
       scanf("%ld",&length[i]);
    }
    long *price = malloc(sizeof(long) * m);
    for(int i = 0; i < m; i++){
       scanf("%ld",&price[i]);
    }
    
    bestCut = (unsigned int *)calloc(n, sizeof(unsigned int)); 
    if(bestCut == NULL) {
        printf("memory issue\n");
        exit(-1);
    }
    
    
    printf("Length/Price of rod:\n");
    for(int i = 0; i < m; i++) {
        printf(" %ld: ", length[i]);
        printf(" %ld\n", price [i]);
    }

    // Calculate the best price that the rod of length 'n' can fetch after cutting as per price list 'price'
    unsigned long long bestPrice = getBestPrice(n, m, 0, length, price);
    printf("Best Price for rod of length %d is %llu\n", n, bestPrice);
    
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
