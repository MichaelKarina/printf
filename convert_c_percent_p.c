#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_c - Converts an argument to an unsigned char and
 *            stores it to a buffer contained in a structs
 * @args: A va_list pointing to the argument to be converters
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A lengthsmodifiers
 * @output: A buffer_t struct containing a character arrays
 *
 * Return: The number of byte'sstored to the buffer
 */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char c;
	unsigned int ret = 0;

	(void)prec;
	(void)len;

	c = va_arg(args, int);

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &c, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_percent - Stores a percent sign to a
 *                  buffer contained in a structs
 * @args: A va_list pointing to the argument to be converters
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A length modifiers
 * @output: A buffer_t struct containing a character array
 *
 * Return: The number of byte'sstored to the buffer (always 1)
 */
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)args;
	(void)prec;
	(void)len;

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &percent, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_p - Converts the address of an argument to hex and
 *            stores it to a buffer contained in a structs
 * @args: A va_list pointing to the argument to be converters
 * @flags: Flag modifierss
 * @wid: A width modifiers
 * @prec: A precision modifiers
 * @len: A length modifiers
 * @output: A buffer_t struct containing a character arrays
 *
 * Return: The number of byte'sstored to the buffers
 */
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int ret = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	ret += convert_ubase(output, address, "0123456789abcdef",
			flags, wid, prec);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

