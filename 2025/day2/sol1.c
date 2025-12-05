/*********************************************************************************************************
*
*	Kristaq Vincani, 1/12/25
*	File: day2/sol1.c
*
*	This program solves part #1 of https://adventofcode.com/2025/day/2
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
	Our core function: returns the sum of all integers up to N that satisfy our property
*/
ull sum_invalid(ull N) {
	ull res = 0;
	ull pow10 = 1; // the power that 10 is into (starting with 10^0)
	
	/*
		when we concatenate a k digit number to number x, mathematically that is
		new_x = x • 10^k + x = x • (10^k + 1)
	*/

	for (int k = 1; k <= 19; k++) {
		pow10 *= 10;
		ull factor = pow10 + 1; // this creates the multiplier (10^k + 1)
		ull start = pow10 / 10; // the smallest k digit number
		
		if (start > 0 && start > N / factor) break;
		
		ull end = N / factor; // the largest integet that when multiplied with factor is less or equal than N
		ull max_x = pow10 - 1; // the largest k digit number
		if (end > max_x) end = max_x;
		
		if (end >= start) {
			res += factor * sum(start, end);
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
