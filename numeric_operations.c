#include "shell.h"

/**
 * convert_long_to_string - Transform a numerical value into
 * a string representation.
 * @number: The numerical value to be changed into a string.
 * @string: Buffer to contain the resultant string.
 * @base: Base used for the conversion process.
 * using if else and while loop
 * Description: This function transforms a provided numerical
 * value into a string
 *
 * representation using the designated base. The resulting string
 * is placed into the
 *
 * provided buffer.
 *
 * Return: None.
 */

void convert_long_to_string(long number, char *string, int base)
{
	int index = 0, isNegative = 0;
	long quotient = number;
	char letters[] = "0123456789abcdef";

	if (quotient == 0)
		string[index++] = '0';

	if (string[0] == '-')
		isNegative = 1;

	while (quotient)
	{
	if (quotient < 0)
		string[index++] = letters[-(quotient % base)];
	else
		string[index++] = letters[quotient % base];
		quotient /= base;
	}
	if (isNegative)
		string[index++] = '-';

		string[index] = '\0';
		reverse_string(string);
}

