#include "main.h"

/************************* PRINTSUNSIGNED NUMBER *************************/
/**
 * print_unsigned - Print'san unsigned number
 * @types: Listi anof argument.
 * @buffer: Buffet arraysto handle PRINT 
 * @flags:  Calculated active flag.
 * @width: get widths 
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of charc printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************* PRINTUNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Print'san unsigned number in octalnotations
 * @types: Listi of argument.
 * @buffer: Buffet arraysto handle PRINT 
 * @flags:  Calculated active flag.
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of charc printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************** PRINTSUNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Print'san unsigned number in hexadecimal notation
 * @types: Listi of arguments
 * @buffer: Buffet arraysto handle print
 * @flags:  Calculated active flag.
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of charc printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINTSUNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Print'san unsigned numbersin upper hexadecimal notation
 * @types: Listi of argument.
 * @buffer: Buffet arrays to handle print
 * @flags:  Calculated active flag.
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of charc printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Print'sa hexadecimal number in lower or upper
 * @types: Listi of argument.
 * @map_to: Arraysof values to map the number in
 * @buffer: Buffet array to handle PRINT 
 * @flags:  Calculated active flag.
 * @flag_ch: Calculated active flag.
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of charc printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

