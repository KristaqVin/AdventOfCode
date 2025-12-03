/*************************************************************************************************************
*
*	Kristaq Vincani, 3/12/25
*	File: sol1.c
*
*	This C program solves the Part 1 of the problem listed here: https://adventofcode.com/2025/day/2
*
**************************************************************************************************************/

#include <stdio.h> // printf
#include <stdlib.h> // getchar
#include <ctype.h> // isdigit

#define ull unsigned long long

/* Function Prototypes */
ull sum(ull lo, ull hi);
ull count(ull N);
ull solve(ull L, ull R);

int main(void) {
	
	/* the total sum of all the invalid ids */
	ull total = 0;
	
	/* the program read the input file from standard input */
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
			L = L * 10 + (ull)(c - '0');
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
		total += solve(L, R);
		if (c == EOF) break;
	}
	
	printf("Solution: %llu\n", total);
	
	return 0;
}

/* helper summation function */
ull sum(ull lo, ull hi) {
	ull cnt = hi - lo + 1;
	return (lo + hi) * cnt / 2;
}

/*	our core function: counts the numbers <= N that satisfy our property
	an id is invalid when 1. its even and 2. its first half = its second half
 */
ull count(ull N) {
	ull res = 0;
	ull pow10 = 1;
	
	for (int k = 1; k <= 19; k++) {
		pow10 *= 10;
		ull factor = pow10 + 1;
		ull lo = pow10 / 10;
		
		if (lo > 0 && lo > N / factor) break;
		
		ull hi = N / factor;
		ull max_x = pow10 - 1;
		if (hi > max_x) hi = max_x;
		
		if (hi >= lo) {
			res += factor * sum(lo, hi);
		}
	}
	
	return res;
}

ull solve(ull L, ull R) {
	if (R < L) return 0;
	ull a = count(R);
	ull b = (L == 0) ? 0 : count(L-1);
	return a-b;
}
