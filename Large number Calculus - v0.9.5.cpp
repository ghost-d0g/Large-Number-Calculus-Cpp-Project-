/* ---------------------------------------------------------------------------------------------- */
/* LARGE NUMBER CALCULUS (NUMERS ARE GIVEN AS ARRAYS OF DIGITS)                                   */
/* AUTOR: Nikola Vukicevic                                                                        */
/* NOVEMBAR 2016.                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

#include <iostream>
#include <cstdio>

using namespace std;

int LOWER_LIMIT = 0, ARRAY_LENGTH = 0, MAX_OPERAND_LENGTH = 5000;


int compare(int a[], int n_a, int b[], int n_b)
{
	int i, tmp_a[ARRAY_LENGTH], tmp_b[ARRAY_LENGTH];

	for(i = 0; i < ARRAY_LENGTH; i++)             tmp_a[i] = tmp_b[i] = 0;
	for(i = 0; i < n_a; i++) tmp_a[ARRAY_LENGTH - n_a + i] = a[ARRAY_LENGTH - n_a + i];
	for(i = 0; i < n_b; i++) tmp_b[ARRAY_LENGTH - n_b + i] = b[ARRAY_LENGTH - n_b + i];


	for(i = 0; i < ARRAY_LENGTH; i++)
	{
		if(tmp_a[i] > tmp_b[i]) return 0;
		if(tmp_b[i] > tmp_a[i]) return 1;
	}

	return 2;
}

void addition(int *a, int n_a, int *b, int n_b, int *c, int n_c)
{
	int i, transfer = 0, tmp_a[ARRAY_LENGTH], tmp_b[ARRAY_LENGTH], tmp_c[ARRAY_LENGTH];

	for(i = 0; i < ARRAY_LENGTH; i++)  tmp_a[i] = tmp_b[i] = tmp_c[i] = 0;
	for(i = 0; i < n_a; i++) tmp_a[ARRAY_LENGTH - n_a + i] = a[ARRAY_LENGTH - n_a + i];
	for(i = 0; i < n_b; i++) tmp_b[ARRAY_LENGTH - n_b + i] = b[ARRAY_LENGTH - n_b + i];

	for(i = ARRAY_LENGTH - 1; i >= LOWER_LIMIT; i--)
	{
		tmp_c[i] = (tmp_a[i] + tmp_b[i] + transfer) % 10;
		transfer = (tmp_a[i] + tmp_b[i] + transfer) / 10;
	}

	for(i = 0; i < n_c; i++) *(c + ARRAY_LENGTH - n_c + i) = tmp_c[ARRAY_LENGTH - n_c + i];
}

void subtraction(int *a, int n_a, int *b, int n_b, int *c, int n_c)
{
	int i, complement, transfer = 0, tmp_a[ARRAY_LENGTH], tmp_b[ARRAY_LENGTH], tmp_c[ARRAY_LENGTH];

	for(i = 0; i < ARRAY_LENGTH; i++)  tmp_a[i] = tmp_b[i] = tmp_c[i] = 0;
	for(i = 0; i < n_a; i++) tmp_a[ARRAY_LENGTH - n_a + i] = a[ARRAY_LENGTH - n_a + i];
	for(i = 0; i < n_b; i++) tmp_b[ARRAY_LENGTH - n_b + i] = b[ARRAY_LENGTH - n_b + i];

	for(i = ARRAY_LENGTH - 1; i >= LOWER_LIMIT; i--)
	{
		complement = 10 - tmp_b[i];
		tmp_c[i]   =   (tmp_a[i] + complement - transfer) % 10;
		transfer   = !((tmp_a[i] + complement - transfer) / 10);
	}

	for(i = 0; i<ARRAY_LENGTH; i++) *(c + i) = tmp_c[i];
}

int firstDigitIndex(int *a, int n)
{
	for(int i=0; i<n; i++)
		if(*(a+i) != 0)
			return i;

	return n - 1;
}

void multiplication(int a[], int n_a, int b[], int n_b, int *c, int n_c)
{
	int i, counter_b, beginning_b = 0, tmp_a[ARRAY_LENGTH], tmp_b[ARRAY_LENGTH], tmp_c[ARRAY_LENGTH],
	    temporary[ARRAY_LENGTH];

	for(i = 0; i<ARRAY_LENGTH; i++)  tmp_a[i] = tmp_b[i] = tmp_c[i] = temporary[i] = 0;
	for(i = 0; i < n_a; i++) tmp_a[ARRAY_LENGTH - n_a + i] = a[ARRAY_LENGTH - n_a + i];
	for(i = 0; i < n_b; i++) tmp_b[ARRAY_LENGTH - n_b + i] = b[ARRAY_LENGTH - n_b + i];

	while(tmp_b[beginning_b] == 0) beginning_b++;

	for(counter_b = beginning_b; counter_b < ARRAY_LENGTH; counter_b++)
	{
		for(i = 0; i < ARRAY_LENGTH; i++) temporary[i] = 0;

		for(i = 0; i < tmp_b[counter_b]; i++)
			addition(tmp_a, ARRAY_LENGTH, temporary, ARRAY_LENGTH, temporary, ARRAY_LENGTH);

		int korekcija = ARRAY_LENGTH - counter_b - 1; // Broj nula za dopisivanje

		for(i = korekcija; i < ARRAY_LENGTH; i++) temporary[i - korekcija] = temporary[i];
		for(i = ARRAY_LENGTH - korekcija; i < ARRAY_LENGTH; i++) temporary[i] = 0;

		addition(tmp_c, ARRAY_LENGTH, temporary, ARRAY_LENGTH, tmp_c, ARRAY_LENGTH);
	}

	for(i = 0; i < ARRAY_LENGTH; i++) *(c + i) = tmp_c[i];
}

int dos(int a[], int n_a, int b[], int n_b)
{
	int i, tmp_a[ARRAY_LENGTH], tmp_b[ARRAY_LENGTH], quotient = 0;

	for(i = 0; i<ARRAY_LENGTH; i++)    tmp_a[i] = tmp_b[i] = 0;
	for(i = 0; i < n_a; i++) tmp_a[ARRAY_LENGTH - n_a + i] = a[ARRAY_LENGTH - n_a + i];
	for(i = 0; i < n_b; i++) tmp_b[ARRAY_LENGTH - n_b + i] = b[ARRAY_LENGTH - n_b + i];

	while(compare(tmp_a, ARRAY_LENGTH, tmp_b, ARRAY_LENGTH) != 1)
	{
		subtraction(tmp_a, ARRAY_LENGTH, tmp_b, ARRAY_LENGTH, tmp_a, ARRAY_LENGTH);
		quotient++;
	}

	return quotient;
}

void spped_mult(int *a, int n, int index, int *c)
{
	int i, transfer = 0, product;

	for(i = ARRAY_LENGTH - 1; i >= 0; --i)
	{
		product = a[i] * n + transfer;
		*(c + i) = product % 10;
		transfer   = product / 10;
	}

	while(transfer)
	{
		*(c + index) = transfer % 10;
		transfer /= 10;
		--index;
	}
}

void division(int a[], int n_a, int b[], int n_b, int *k, int n_k, int *o, int n_o)
{
	int i, counter_a = 0, tmp_a[ARRAY_LENGTH], tmp_b[ARRAY_LENGTH], tmp_k[ARRAY_LENGTH], working[ARRAY_LENGTH],
						 mult1[ARRAY_LENGTH], multiplier[ARRAY_LENGTH];

	for(i = 0; i < ARRAY_LENGTH; i++) tmp_a[i] = tmp_b[i] = tmp_k[i] = working[i] = mult1[i] = multiplier[i] = 0;
	for(i = 0; i < n_a; i++) tmp_a[ARRAY_LENGTH - n_a + i] = a[ARRAY_LENGTH - n_a + i];
	for(i = 0; i < n_b; i++) tmp_b[ARRAY_LENGTH - n_b + i] = b[ARRAY_LENGTH - n_b + i];

	while(tmp_a[counter_a] == 0) counter_a++;

	while(counter_a < ARRAY_LENGTH)
	{
		while(compare(working, ARRAY_LENGTH, tmp_b, ARRAY_LENGTH) == 1)
		{
			if(counter_a == ARRAY_LENGTH) break;

			for(i=1; i<ARRAY_LENGTH; i++)
				working[i-1] = working[i];

			working[ARRAY_LENGTH - 1] = tmp_a[counter_a];

			for(i=1; i<ARRAY_LENGTH; i++)
				tmp_k[i-1] = tmp_k[i];

			tmp_k[ARRAY_LENGTH - 1] = 0;

			counter_a++;
		}

		tmp_k[ARRAY_LENGTH - 1] = multiplier[ARRAY_LENGTH - 1] = dos(working, ARRAY_LENGTH, tmp_b, ARRAY_LENGTH);
		spped_mult(tmp_b, multiplier[ARRAY_LENGTH - 1], ARRAY_LENGTH - firstDigitIndex(tmp_b, ARRAY_LENGTH), mult1);
		//multiplication(multiplier, ARRAY_LENGTH, tmp_b, n_b, mult1, ARRAY_LENGTH);
		subtraction(working, ARRAY_LENGTH, mult1, ARRAY_LENGTH, working, ARRAY_LENGTH);
	}

	for(i = 0; i < ARRAY_LENGTH; i++) k[i] = tmp_k[i];
	for(i = 0; i < ARRAY_LENGTH; i++) o[i] = working[i];
}

int spped_mult(int *a, int n, int index)
{
	int i, transfer = 0, product;

	for(i = 0; i < index; i++)
	{
		product  = a[i] * n + transfer;
		a[i]     = product % 10;
		transfer = product / 10;
	}

	while(transfer)
	{
		a[index] = transfer % 10;
		transfer /= 10;
		index++;
	}

	return index;
}

void speed_factoriel(int n)
{
	if(n > 50000)
	{
		printf("\nYour input is larger than 50000, which isn't supported ATM!");
		return;
	}

	int i, length = 250000, tmp_c[length], index = 1;

	tmp_c[0] = 1;

	for(i = 1; i < length; i++) tmp_c[i] = 0;

	for(i = 2; i<= n; i++)
		index = spped_mult(tmp_c, i, index);

	FILE *f = fopen("result.txt", "w");

	fprintf(f, "Enter a value (<= 50000): %d\n", n);
	fprintf(f, "Number of digits in the resulting number: %d\n\n", index);
	fprintf(f, "Factoriel(%d) = \n\n", n);

	for(i = index - 1; i >= 0; i--)
			fprintf(f, "%d", tmp_c[i]);
		fprintf(f, "\n");

	printf("\nThe result has been caluclated and placed in the followinf file: \"result.txt\".");

	fclose(f);
}

void calculate_array_length(string name, string *s1, string *s2)
{
	char tmp_char = '0';
	int i, n1, n2;
	string string1 = "", string2 = "";
	FILE *f = fopen(name.c_str() , "r");

	while(tmp_char == '0') fscanf(f, "%c", &tmp_char);

    string1 += tmp_char;

    while(tmp_char != '\n')
    {
    	fscanf(f, "%c", &tmp_char);
    	if(tmp_char >= 48 && tmp_char <= 57) string1 += tmp_char;
	}

    n1 = string1.length();

	fscanf(f, "%c", &tmp_char);

	while(tmp_char == '0') fscanf(f, "%c", &tmp_char);

	string2 += tmp_char;

	while(tmp_char != '\n')
    {
    	fscanf(f, "%c", &tmp_char);
    	if(tmp_char >= 48 && tmp_char <= 57) string2 += tmp_char;
	}

    n2 = string2.length();

	ARRAY_LENGTH = n1 + n2;

    fclose(f);

    *s1 = string1; *s2 = string2;
}


void load_arrays(string name, string s1, int *a, int *n_a, string s2, int *b, int *n_b)
{
	int i;

    *n_a = s1.length();

	for(i = 0; i < *n_a; i++)
    	a[ARRAY_LENGTH - *n_a + i] = s1.at(i) - 48;

    printf("\nOperand 1 loaded successfully.");
    printf("\nNumber of digits in operand 1: %d\n", *n_a);

    *n_b = s2.length();

    for(i = 0; i < *n_b; i++)
    	b[ARRAY_LENGTH - *n_b + i] = s2.at(i) - 48;

    printf("\nOperand 2 loaded successfully.");
    printf("\nNumber of digits in operand 2: %d\n\n\n", *n_b);

}

void write_to_file(char tmp_char, string name, int a[], int n_a, int b[], int n_b, int r1[], int n_r1, int r2[], int n_r2, int longest, int n)
{
	FILE *f = fopen(name.c_str(), "w");
	int i;

	if(tmp_char == '5')
	{
		fprintf(f, "Factoriel(%d) = \n\n", n);
		i = 0;
		while(!r1[i]) i++;

		for(; i < ARRAY_LENGTH; i++)
			fprintf(f, "%d", r1[i]);
		fprintf(f, "\n");
		fclose(f);
		return;
	}

	fprintf(f, " ");
    for(i = 0; i < longest - n_a; i++) fprintf(f, " ");
    for(i = 0; i < n_a; i++) fprintf(f, "%d", a[ARRAY_LENGTH - n_a + i]);
    fprintf(f, "\n");
    switch(tmp_char)
    {
    	case '1' : fprintf(f, "+"); break;
    	case '2' : fprintf(f, "-"); break;
    	case '3' : fprintf(f, "*"); break;
    	case '4' : fprintf(f, "/"); break;
    	default: break;
	}


    for(i = 0; i < longest - n_b; i++) fprintf(f, " ");
    for(i = 0; i < n_b; i++) fprintf(f, "%d", b[ARRAY_LENGTH - n_b + i]);
    fprintf(f, "\n");
    for(i = 0; i <= longest; i++) fprintf(f, "-");
    fprintf(f, "\n=");
    for(i = 0; i < longest - n_r1; i++) fprintf(f, " ");
    for(i = 0; i < n_r1; i++) fprintf(f, "%d", r1[ARRAY_LENGTH - n_r1 + i]);
   	fprintf(f, "\n");

	if(tmp_char == '4')
	{
		fprintf(f, "\n");
		fprintf(f, "REMAINDER:\n ");
   		for(i = 0; i < longest - n_r2; i++) fprintf(f, " ");
		for(i = 0; i < n_r2; i++) fprintf(f, "%d", r2[ARRAY_LENGTH - n_r2 + i]);
   		fprintf(f, "\n");
	}

    fclose(f);
}

int main()
{
    char tmp_char;
	int i, j, k, n, numOfDigits1, numOfDigits2, numOfDigitsR, numOfDigitsO, longest_number;
	string operand_1_string = "", operand_2_string = "";

	calculate_array_length("operands.txt", &operand_1_string, &operand_2_string);

	int	broj1[ARRAY_LENGTH], broj2[ARRAY_LENGTH], rezultat[ARRAY_LENGTH], rezultat2[ARRAY_LENGTH];

	printf("////////////////////////////////////////////////////////////\n");
    printf("// LARGE NUMBER CALCULUS:                                 //\n");
    printf("////////////////////////////////////////////////////////////\n");
    
    ///////////////////////////////////////////////////////////////////////////////////////
    // Operand loading:
	///////////////////////////////////////////////////////////////////////////////////////
	
	for(i = 0; i < ARRAY_LENGTH; i++) broj1[i] = broj2[i] = rezultat[i] = rezultat2[i] = 0;
    load_arrays("operands.txt", operand_1_string, broj1, &numOfDigits1, operand_2_string, broj2, &numOfDigits2);
    longest_number = numOfDigits1 * (numOfDigits1 >= numOfDigits2) + numOfDigits2 * (numOfDigits2 > numOfDigits1);
    LOWER_LIMIT = ARRAY_LENGTH - numOfDigits1 - numOfDigits2 - 10;
    if(LOWER_LIMIT < 0) LOWER_LIMIT = 0;

    if (longest_number > MAX_OPERAND_LENGTH)
    {
    	printf("Even though the operands were loaded sucessfully, at least one of the two operands\n has more than %d digits, which isn't supported ATM!", MAX_OPERAND_LENGTH);
    	printf("\n\nProgram has been terminated.");
    	return 0;
	}

    ///////////////////////////////////////////////////////////////////////////////////////
    // Performing operations:
    ///////////////////////////////////////////////////////////////////////////////////////

    printf("Choose the operation:\n");
    printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Factoriel\n\nYOUR CHOICE: ");


    scanf("%c", &tmp_char);

	///////////////////////////////////////////////////////////////////////////////////////
    // Quick operation selection:
    ///////////////////////////////////////////////////////////////////////////////////////

	//    tmp_char = '1';
	//    tmp_char = '2';
	//    tmp_char = '3';
	//    tmp_char = '4';
	//    tmp_char = '5';

	switch(tmp_char)
	{
		case '1' : addition(broj1, numOfDigits1, broj2, numOfDigits2, rezultat, ARRAY_LENGTH); break;
		case '2' : subtraction(broj1, numOfDigits1, broj2, numOfDigits2, rezultat, ARRAY_LENGTH); break;
		case '3' : multiplication(broj1, numOfDigits1, broj2, numOfDigits2, rezultat, ARRAY_LENGTH); break;
		case '4' : division(broj1, numOfDigits1, broj2, numOfDigits2, rezultat, ARRAY_LENGTH, rezultat2, ARRAY_LENGTH); break;
		//case '5' : printf("\nEnter a value for the factorial calulation: "); n = 10000; speed_factoriel(n); return 0;
		case '5' : printf("\nEnter a value for factorial calulation: "); scanf("%d", &n); speed_factoriel(n); return 0;
		default: printf("Wrong operation code!\n\nProgram has been terminated."); return 0;
	}

	numOfDigitsR = ARRAY_LENGTH - firstDigitIndex(rezultat, ARRAY_LENGTH);
	printf("\n\nNumber of digits in the resulting value: %d\n", numOfDigitsR);
	longest_number = numOfDigitsR * (numOfDigitsR >= longest_number) + longest_number * (longest_number > numOfDigitsR);

	numOfDigitsO = ARRAY_LENGTH - firstDigitIndex(rezultat2, ARRAY_LENGTH);
	if(tmp_char == '4') printf("Number of digits in the remainder: %d\n", numOfDigitsO);
	longest_number = numOfDigitsO * (numOfDigitsO >= longest_number) + longest_number * (longest_number > numOfDigitsO);

	////////////////////////////////////////////
	// Writing to file:
	////////////////////////////////////////////

	write_to_file(tmp_char, "result.txt", broj1, numOfDigits1, broj2, numOfDigits2, rezultat, numOfDigitsR, rezultat2, numOfDigitsO, longest_number, n);

    printf("\nThe resulting value has been calulated and placed in the following file: \"result.txt\".");
}
