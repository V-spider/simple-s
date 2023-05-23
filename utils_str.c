#include "shell.h"

/**
 * _strcmp - compare 2 strings
 * @str1: string 1
 * @str2: string 2
 * Return: 0 if equaul and otherwise if not equal
 */
int _strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (str1[i] - str2[i]);
}
/**
 * _strncmp - compare 2 strings
 * @s1: string 1
 * @s2: string
 * @n: size
 * Return: 0 if equaul and otherwise if not equal
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return (s1[i] - s2[i]);
	}
	return (0);
}
/**
 * _strlen - string length
 * @str: string
 * Return: length of string
 */
int _strlen(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
/**
 * _strncpy - string copy of n limit
 * @dest: destination
 * @src: source string
 * @size: number of char to be copied
 * Return: sized of char copied
 */
int _strncpy(char *dest, char *src, int size)
{
	int i = 0;

	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}
/**
 * _strcpy - string copy of n limit
 * @dest: destination
 * @src: source string
 * Return: sized of char copied
 */
int _strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}
