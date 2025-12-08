/*********************************************************************************************************
*
*	Kristaq Vincani, 1/12/25
*	File: day2/sol2.c
*
*	This program solves part #2 of https://adventofcode.com/2025/day/2
*
*********************************************************************************************************/

#include <stdio.h> // printf
#include <stdlib.h> // getchar
#include <ctype.h> // isdigit

#define ull unsigned long long

/* Function Prototypes */
ull sum(ull start, ull end);
ull count(ull N);
ull solve(ull L, ull R);

/* program entry point */
int main(void) {
	
	/* the total sum of all the invalid ids */
	ull solution = 0;
	
	/* the program reads the input file from standard input */
	int c;
	while ((c = getchar()) != EOF) {
		/* skip whitespaces */
		while (c != EOF && !isdigit((unsigned char)c)) {
			c = getchar();
		}
		if (c == EOF) break;
		
		/* read L, the starting number of the range */
		ull L = 0;
		while (isdigit((unsigned char)c)) {
			L = L * 10 + (ull)(c - '0'); // converts a string to an int
			c = getchar();
		}
		if (c != '-') break;
		
		/* read R, the final number of the range */
		c = getchar();
		ull R = 0;
		while (isdigit((unsigned char)c)) {
			R = R * 10 + (ull)(c - '0');
			c = getchar();
		}
		solution += solve(L, R); // get the sum of the invalid ids for this range
		if (c == EOF) break;
	}
	
	printf("Solution: %llu\n", solution);
	
	return 0;
}

/* 
	helper summation function 
	sums all integers between start and end (including those)
*/
ull sum(ull start, ull end) {
	ull cnt = end - start + 1;
	return (start + end) * cnt / 2;
}

/*
	helper number generator
	generates a repeated number 
*/
ull get_factor(int period, int total_len) {
    ull mult = 0;
    ull block_val = 1; 
    // Create 10^period
    for (int i = 0; i < period; i++) block_val *= 10;
    
    ull current_pow = 1;
    for (int len = 0; len < total_len; len += period) {
        mult += current_pow;
        current_pow *= block_val;
    }
    return mult;
}

/*
	our core function, which calculates the sum of all invalid ids <= N
	by using inclusion-exclusion principle over the periods of the numbers
*/
ull sum_invalid(ull N) {
    ull res = 0;
    
	/* iterate over possible lengths of numbers */
    for (int L = 2; L <= 19; L++) {
        
        /* determine min and max values for this length */
        ull min_L_val = 1; 
        for(int i=1; i<L; i++) min_L_val *= 10;
        
        if (min_L_val > N) break; // if we exceed N, stop
        
        /* find proper divisors (periods) of L */
        int periods[10];
        int p_count = 0;
        for (int p = 1; p <= L/2; p++) {
            if (L % p == 0) periods[p_count++] = p;
        }
        
        /* memoization array for unique sums per period */
        ull unique_sums[20] = {0}; 
        
        for (int i = 0; i < p_count; i++) {
            int p = periods[i];
            
            /* calculate the sum of numbers with period p and length L */
            ull multiplier = get_factor(p, L);
            
            /* we bound the seeds to ensure the generated number has length L */
            ull seed_min = 1; 
            for(int k=1; k<p; k++) seed_min *= 10;
            
            ull seed_max = seed_min * 10 - 1;
            
            /* we also cap the seeds to ensure the generated number does not exceed N */
            ull effective_max = N / multiplier;
            if (effective_max < seed_max) seed_max = effective_max;
            
            /* valid range */
            ull current_raw_sum = 0;
            if (seed_max >= seed_min) {
                current_raw_sum = multiplier * sum(seed_min, seed_max);
            }
            
            /* subtract overlaps with previously considered periods */
            ull overlaps = 0;
            for (int j = 0; j < i; j++) {
                int prev_p = periods[j];
                if (p % prev_p == 0) {
                    overlaps += unique_sums[prev_p];
                }
            }
            
			/* store the unique sum for this period */
            if (current_raw_sum > overlaps) {
                unique_sums[p] = current_raw_sum - overlaps;
            } else {
                unique_sums[p] = 0; // Should not happen mathematically unless range is empty
            }
            
            res += unique_sums[p];
        }
    }
    
    return res;
}

/*
	Calculates the sum of all invalid id for the given range
*/
ull solve(ull L, ull R) {
	if (R < L) return 0;
	ull a = sum_invalid(R);
	ull b = (L == 0) ? 0 : sum_invalid(L-1);
	return a-b;
}
