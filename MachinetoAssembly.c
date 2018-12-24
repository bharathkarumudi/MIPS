/* MachinetoAssembly.c - check, substring, binaryToDecimal, main

This program takes the machine code as input and converts to its
corresponding assembly instruction.

Written by Bharath Karumudi for Lab 4 assignment

 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 32
#define ACTUAL_LENGTH LENGTH + 1
#define false 0
#define true 1

// Checks that the char array is 32 bits long
// and only has 0 and 1 in it.

int check(char* bits) {
	if (strlen(bits) != LENGTH) {
	return false;
  }

	for (int i = 0; i < LENGTH; i++) {
		if (bits[i] != '0' && bits[i] != '1') {
			return false;
		}
	}
return true;
}


// Function to get the substring from a given string
// takes input, output, start postion and length
void substring(char s[], char sub[], int p, int l)
{
    int c = 0;
    while (c < l)
    {
        sub[c] = s[p+c-1];
        c++;
    }
    sub[c] = '\0';
}


// Function to convert Binary number to its corresponding decimal
// Takes integer
int binaryToDecimal(int n) 	
{ 
    int num = n; 
    int dec_value = 0; 
      
    int base = 1; 
      
    int temp = num; 
    while (temp) 
    { 
        int last_digit = temp % 10; 
        temp = temp/10; 
          
        dec_value += last_digit*base; 
          
        base = base*2; 
    } 
      
    return dec_value; 
} 


// Main Method
int main(void) {
	char instruction[ACTUAL_LENGTH], opcode[7], rs[10], rt[10], rd[10], shamt[10], functcode[10], imm[30], jimm[30];

	printf("Please enter a 32 bit long string:\n");
	scanf("%s", instruction);

	if (!check(instruction)) {
		printf("Invalid bit string: %s!\n Shutting down.\n", instruction);
		return -1;
	}

	// Array of register names
	const char *registers[32];
	registers[0] = "0";
	registers[1] = "$at";
	registers[2] = "$v0";
	registers[3] = "$v1";
	registers[4] = "$a0";
	registers[5] = "$a1";
	registers[6] = "$a2";
	registers[7] = "$a3";
	registers[8] = "$t0";
	registers[9] = "$t1";
	registers[10] = "$t2";
	registers[11] = "$t3";
	registers[12] = "$t4";
	registers[13] = "$t5";
	registers[14] = "$t6";
	registers[15] = "$t7";
	registers[16] = "$s0";
	registers[17] = "$s1";
	registers[18] = "$s2";
	registers[19] = "$s3";
	registers[20] = "$s4";
	registers[21] = "$s5";
	registers[22] = "$s6";
	registers[23] = "$s7";
	registers[24] = "$t8";
	registers[24] = "$t9";
	registers[26] = "$k0";
	registers[27] = "$k1";
	registers[28] = "$gp";
	registers[29] = "$sp";
	registers[30] = "$fp";
	registers[31] = "$ra";

	// Dividing the machine code
	substring(instruction, opcode, 1, 6);
	substring(instruction, rs, 7, 5);
	substring(instruction, rt, 12, 5);
	substring(instruction, rd, 17, 5);
	substring(instruction, shamt, 22, 5);
	substring(instruction, functcode, 27, 6);
	substring(instruction, imm, 17, 16);
	substring(instruction, jimm, 7, 26);


	// Converting the binary to decimal
	int rsval = binaryToDecimal(atoi(rs));
	int rtval = binaryToDecimal(atoi(rt));
	int rdval = binaryToDecimal(atoi(rd));
	//int shamtval = binaryToDecimal(atoi(shamt));
	int immval = binaryToDecimal(atoi(imm));
	int jimmval = binaryToDecimal(atoi(jimm));



	if (strcmp(opcode, "000000") == 0) {				/* Special */

		if (strcmp(functcode, "100000") == 0) {			//add

			printf("add %s,%s,%s \n", registers[rdval], registers[rsval], registers[rtval]);

		 }

		 else if (strcmp(functcode, "100010") == 0){ 	//sub

			printf("sub %s,%s,%s \n", registers[rdval], registers[rsval], registers[rtval]);
		}

		else if (strcmp(functcode, "101010")==0 ){		//slt

			printf("slt %s,%s,%s \n", registers[rdval], registers[rsval], registers[rtval]);
		}

		else if (strcmp(functcode, "001000")==0 ){		//jr
			printf("jr %s \n", registers[rsval]);
		}

		else {

			printf("sorry, this is not a supported machine code, please try with a valid one.\n");
			return -1;
		}

	 }

	else if (strcmp(opcode, "001000") == 0) {			//addi

		printf("addi %s,%s,%d \n", registers[rtval], registers[rsval], immval);
	 }

	else if (strcmp(opcode, "000100") == 0) {			//beq

		printf("beq %s,%s,%d \n", registers[rsval], registers[rtval], immval);
	 }

	else if (strcmp(opcode, "100011") == 0) {			//lw

		printf("lw %s,%d(%s) \n", registers[rtval], immval, registers[rsval]);
	 }

	else if (strcmp(opcode, "101011") == 0) {			//sw

		printf("sw %s,%d(%s) \n", registers[rtval], immval, registers[rsval]);
	 }

	else if(strcmp(opcode, "000010") == 0) {			//j
	 	
	 	printf("j %d \n", jimmval);
	 }

	else if(strcmp(opcode,"000011") == 0) {				//jal

	 	printf("jal %d\n",jimmval);
	 }

	else {
		printf("sorry, this is not a supported machine code, please try with a valid one.\n");
		return -1;

	}


return 1;
}