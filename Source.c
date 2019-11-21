/*
Program Description: Program to find the increasingly additive prime sequence 
between a lower and upper bound-- where an increasingly additive prime sequence is a
list of integer numbers such that the next number in the sequence is greater than the sum of
the previous numbers. Necessary variables, as well as any input/output is handled in C, while the
main logic (testing if prime, testing if greater than sum, testing if still in bounds) 
is done through Intel assembly code.
*/
#include <stdio.h>
#pragma warning(disable : 4996)

void main() {
	int start = 0;
	int end = 0;
	printf("Please enter the lower bound.\n"); //take input for lower and upper bounds from user
	scanf("%d", &start);
	printf("Please enter the upper bound.\n");
	scanf("%d", &end);
	//int start = 300; //number to start searching for primes from
	//int end = 5000; //number to stop search loop
	int sum = 0; //number to add prime numbers to and compare if the next prime number is greater
	printf("The additively prime sequence from %d to %d is: \n", start, end);
	__asm {
	restart:mov	eax, start //moving the current number to find if prime into the eax
	mov	ecx, 2 //move the divisor into the ecx
	mov	ebx, end //placing upper bound into ebx register
	top : mov	edx, 0 //prime for division
	div	ecx //divide current number by current value of ecx, remainder goes to edx
	cmp	edx, 0 //compare remainder to 0
	je	loopI //remainder = 0, not prime, jump to increment start
	cmp	ecx, eax //else see if ecx has reached the number in question
	jge	testS //compare counter to current iterated number, if >= it made it through without being divisible, send to testS to test sum
	inc	ecx //else we can increment the divisor 
	mov	eax, start //reset the eax from holding quotient to the iterated number
	jmp	top //and repeat the division loop
	testS : mov	eax, start
	cmp	eax, sum //if start > sum add to sum and print the number
	jle	loopI //else not larger, increment to next number
	add	sum, eax
	}
	printf("%d ", start); //print the next additively prime value
	__asm {
	loopI:	cmp	start, ebx //compare the current number in iteration to the end number
	jge	endP //if current is >= the end, we made it to the end of the loop, end program
	inc	start //else we go to the next number
	jmp	restart //and go back to the top
	endP : nop
	}
}

/*OUTPUT EXAMPLES
The additively prime sequence from 3 to 1000 is:
3 5 11 23 43 89 179 359 719

The additively prime sequence from 300 to 5000 is:
307 311 619 1249 2503 4993
*/
