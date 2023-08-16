#include "shell.h"

/**
 * convert_long_to_string - Transform a numerical value into
 * a string representation.
 * @number: The numerical value to be changed into a string.
 * @string: Buffer to contain the resultant string.
 * @base: Base used for the conversion process.
 * using if else and while loop
 *
 * Description: This function transforms a provided numerical
 * value into a string representation using the designated base.
 * The resulting string is placed into the provided buffer.
 *
 * Return: None.
 */

void convert_long_to_string(long number, char *string, int base)
{
	int index = 0, isNegative = 0;
	long quotient = number;
	char letters[] = {"0123456789abcdef"};

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

/**
 * convert_to_integer - Transform a string into an integer.
 * @s: Pointer to the input string.
 *
 * Description: This function converts the given string into an
 * integer value.
 *
 * Return: The resulting integer value or 0 if conversion fails.
 */

int convert_to_integer(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	/* Step 1: Analyze the sign */
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}
	/* Step 2: Extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_char_occurrences - Calculate the occurrences of a specific
 * character in a string.
 *
 * @string: Pointer to the input string.
 * @character: String containing the characters to be counted.
 *
 * Description: This function tallies the occurrences of the provided
 * character within
 *
 * the given string and returns the resulting count.
 *
 * Return: The count of character occurrences.
 */

int count_char_occurrences(char *string, char *character)
{
	int index = 0, count = 0;

	for (; string[index]; index++)
	{
	if (string[index] == character[0])
	count++;
	}
	return (count);
}

