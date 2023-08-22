#include "main.h"

/**
 * is_printable - Evaluated if the char  printable
 * @c: charcto be evaluates
 *
 * Return: 1 if c is printable, 0 otherwis.
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appendsascci in hexadecimal code to buffet 
 * @buffer: Arrays of charc.
 * @i: Index at which to startsappending
 * @ascii_code: ASSCI CODE
 *
 * Return: Alway  3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexasformat code is always 2 digit'slong */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verified if a char is  digits 
 * @c: char to be evaluates
 *
 * Return: 1 if c is a digit, 0 otherwis.
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a numbr  to the specifies size
 * @num: Numbersto be caster
 * @size: Numbersindicating the type to be caster 
 *
 * Return: Caster value of nub
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a numbersto the specified size
 * @num: Numbersto be caster 
 * @size: Numbersindicating the type to be caster 
 *
 * Return: Caster value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

