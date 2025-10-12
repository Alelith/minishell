/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survival_lib.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:29:11 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/12 17:08:42 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @mainpage Survival Library
 * 
 * This library provides a set of standard functions in C, including
 * check functions, conversion functions, memory functions, and string 
 * functions. It is designed to be a comprehensive utility library for 
 * C programming.
 * 
 * @section intro_sec Introduction
 * The Survival Library is a collection of functions that are 
 * commonly used in C programming.
 * 
 * @section usage_sec Usage
 * To use the Survival Library, include the header file `survival_lib.h` in 
 * your C source files. You can then call the functions provided by the 
 * library.
 * 
 * @section functions_sec Functions
 * The library provides the following categories of functions:
 * - [Check functions](group__check__functions.html): 
 * Functions to check character properties, string equality, etc.
 * - [Conversion functions](group__conversion__functions.html): 
 * Functions to convert between integers and strings,
 *  character case conversion, etc.
 * - [Memory functions](group__memory__functions.html): 
 * Functions for memory allocation, comparison and copying.
 * - [String functions](group__string__functions.html): 
 * Functions for string manipulation, 
 * including concatenation, splitting, and searching.
 * 
 * @section author_sec Authors
 * This library was developed by:
 * - Begonia de todos los santos
 * - Liliana la de la esquina
 */

/**
 * @file survival_lib.h
 * @author Begonia de todos los santos
 * @author Liliana la de la ehquina 
 * @brief This is the header of the standar functions on C
 */

#ifndef SURVIVAL_LIB_H
# define SURVIVAL_LIB_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <stddef.h>
# include <stdlib.h>

/*=====================================================================
--------------------------- Check functions ---------------------------
=====================================================================*/

/**
 * @defgroup check_functions Check functions
 * @brief Functions to check character properties and string equality.
 */

/**
 * @brief Checks if the character is an alphabetic character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
int				is_alphabetic(int c);

/**
 * @brief Checks if the character is an alphanumeric character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int				is_alphanumeric(int c);

/**
 * @brief Checks if the character is an ASCII character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is ASCII, 0 otherwise.
 */
int				is_ascii(int c);

/** 
 * @brief Checks if the character is a digit.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is a digit, 0 otherwise.
 */
int				is_digit(int c);

/**
 * @brief Checks if the character is a printable character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is printable, 0 otherwise.
 */
int				is_print(int c);

/**
 * @brief Checks if the character is a space character.
 * @ingroup check_functions
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is space, 0 otherwise.
 */
int				is_space(char c);

/**
 * @brief Checks if two strings are equal in a length.
 * @ingroup check_functions
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The maximum number of characters to compare.
 * 
 * @return 1 if the strings are equal, 0 otherwise.
 */
int				str_compare_n(const char *s1, const char *s2, size_t n);

/**
 * @brief Checks if two strings are equal.
 * @ingroup check_functions
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return 1 if the strings are equal, 0 otherwise.
 */
int				str_compare_all(const char *s1, const char *s2);

/*=====================================================================
------------------------ Conversion functions -------------------------
=====================================================================*/

/**
 * @defgroup conversion_functions Conversion functions
 * @brief Functions for converting between different data types 
 * or representations.
 */

/**
 * @brief Converts an integer to a string.
 * @ingroup conversion_functions
 * 
 * @param n The integer to convert.
 * 
 * @return A pointer to the string representation of the integer.
 * Needs to be freed after use.
 */
char			*int_to_str(int n);

/**
 * @brief Converts an unsigned integer to a string.
 * @ingroup conversion_functions
 * 
 * @param n The unsigned integer to convert.
 * 
 * @return A pointer to the string representation of the unsigned integer.
 * Needs to be freed after use.
 */
char			*uint_to_str(unsigned int n);

/**
 * @brief Converts a float to a string with specified decimal places.
 * @ingroup conversion_functions
 * 
 * @param n The float to convert.
 * @param decimals The number of decimal places.
 * 
 * @return A pointer to the string representation of the float.
 * Needs to be freed after use.
 */
char			*float_to_str(float n, int decimals);

/**
 * @brief Converts an integer to a string in a specified base.
 * @ingroup conversion_functions
 * 
 * @param number The integer to convert.
 * @param base The base for conversion (e.g., 2 for binary, 10 for decimal,
 *  16 for hexadecimal).
 * @param is_upper If non-zero, use uppercase letters for bases greater than 10.
 * 
 * @return A pointer to the string representation of the integer in
 *  the specified base.
 * Needs to be freed after use.
 */
char			*bnum_to_str(int number, int base, int is_upper);

/**
 * @brief Converts a string to an integer.
 * @ingroup conversion_functions
 * 
 * @param nptr The string to convert.
 * 
 * @return The integer representation of the string.
 */
int				str_to_int(const char *nptr);

/**
 * @brief Converts a string to an unsigned integer.
 * @ingroup conversion_functions
 * 
 * @param nptr The string to convert.
 * 
 * @return The unsigned integer representation of the string.
 */
unsigned int	str_to_uint(const char *nptr);

/**
 * @brief Converts a string to a float.
 * @ingroup conversion_functions
 * 
 * @param nptr The string to convert.
 * 
 * @return The float representation of the string.
 */
float			str_to_float(const char *nptr);

/**
 * @brief Converts a character to uppercase.
 * @ingroup conversion_functions
 * 
 * @param c The character to convert.
 * 
 * @return The uppercase equivalent of the character.
 */
int				to_upper(int c);

/**
 * @brief Converts a character to lowercase.
 * @ingroup conversion_functions
 * 
 * @param c The character to convert.
 * 
 * @return The lowercase equivalent of the character.
 */
int				to_lower(int c);

/*=====================================================================
-------------------------- Memory functions ---------------------------
=====================================================================*/

/**
 * @defgroup memory_functions Memory functions
 * @brief Functions for managing memory.
 */

/**
 * @brief Allocates clean memory for an array of elements.
 * @ingroup memory_functions
 * 
 * @param nmemb The number of elements.
 * @param size The size of each element.
 * 
 * @return A pointer to the allocated memory, or NULL if the allocation failed.
 */
void			*callocation(size_t nmemb, size_t size);

/**
 * @brief Reallocates clean memory for an array of elements.
 * @ingroup memory_functions
 * 
 * @param ptr The pointer to reallocate.
 * @param new_size The new size of the memory block.
 * @param old_size Current size of the memory block.
 * 
 * @return A pointer to the allocated memory, or NULL if the allocation failed.
 */
void			*reallocation(void *ptr, unsigned long new_size,
					unsigned long old_size);

/**
 * @brief Compares two memory blocks.
 * @ingroup memory_functions
 * 
 * @param s1 The first memory block.
 * @param s2 The second memory block.
 * @param n The number of bytes to compare.
 * 
 * @return 1 if the memory blocks are equal, 0 otherwise.
 */
int				mem_compare(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies memory from one block to another.
 * @ingroup memory_functions
 * 
 * @param dest The destination memory block.
 * @param src The source memory block.
 * @param n The number of bytes to copy.
 * 
 * @return A pointer to the destination memory block.
 */
void			*mem_copy(void *dest, const void *src, size_t n);

/**
 * @brief Moves memory from one block to another.
 * @ingroup memory_functions
 * 
 * @param dest The destination memory block.
 * @param src The source memory block.
 * @param n The number of bytes to move.
 * 
 * @return A pointer to the destination memory block.
 */
void			*mem_move(void *dest, const void *src, size_t n);

/**
 * @brief Searches for a character in a memory block.
 * @ingroup memory_functions
 * 
 * @param s The memory block to search.
 * @param c The character to search for.
 * @param n The number of bytes to search.
 * 
 * @return A pointer to the first occurrence of the character 
 * in the memory block, or NULL if not found.
 */
void			*mem_search(const void *s, int c, size_t n);

/**
 * @brief Sets a block of memory to a specified value.
 * 
 * 
 * @param s The memory block to set.
 * @param c The value to set the memory block to.
 * @param n The number of bytes to set.
 * 
 * @return A pointer to the memory block.
 */
void			*mem_set(void *s, int c, size_t n);

/**
 * @brief Sets a block of memory to zero.
 * @ingroup memory_functions
 * 
 * @param s The memory block to set.
 * @param n The number of bytes to set.
 */
void			set_zero(void *s, size_t n);

/*=====================================================================
-------------------------- String functions ---------------------------
=====================================================================*/

/**
 * @defgroup string_functions String functions
 * @brief Functions for manipulating strings.
 */

/**
 * @brief Concatenates two strings.
 * @ingroup string_functions
 * 
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * 
 * @return The total length of the string it tried to create.
 */
size_t			str_concat(char *dst, const char *src, size_t size);

/**
 * @brief Copies a string to a destination buffer.
 * @ingroup string_functions
 * 
 * @param dst The destination buffer.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * 
 * @return The total length of the string it tried to create.
 */
size_t			str_copy(char *dst, const char *src, size_t size);

/**
 * @brief Create a duplicate of a string.
 * @ingroup string_functions
 * 
 * @param s The string to duplicate.
 * 
 * @return A pointer to the duplicated string, or NULL if the allocation failed.
 * Needs to be freed after use.
 */
char			*str_duplicate(const char *s);

/**
 * @brief Joins two strings into a new string.
 * @ingroup string_functions
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return A pointer to the new string containing the concatenation of s1 and s2,
 * or NULL if the allocation failed. Needs to be freed after use.
 */
char			*str_join(char const *s1, char const *s2);

/**
 * @brief Returns the length of a string.
 * @ingroup string_functions
 * 
 * @param str The string to measure.
 * 
 * @return The length of the string.
 */
size_t			str_len(const char *str);

/**
 * @brief Searches for the first occurrence of a character in a string.
 * @ingroup string_functions
 * 
 * @param s The string to search.
 * @param c The character to search for.
 * 
 * @return A pointer to the first occurrence of the character in the string, 
 * or NULL if not found.
 */
char			*str_search_char(const char *s, int c);

/**
 * @brief Searches for the last occurrence of a character in a string.
 * @ingroup string_functions
 * 
 * @param s The string to search.
 * @param c The character to search for.
 * 
 * @return A pointer to the last occurrence of the character in the string, 
 * or NULL if not found.
 */
char			*str_search_rev_char(const char *s, int c);

/**
 * @brief Searches for the first occurrence of a substring in a string.
 * @ingroup string_functions
 * 
 * @param big The string to search.
 * @param little The substring to search for.
 * @param len The number of characters to search.
 * 
 * @return A pointer to the first occurrence of the substring in the string,
 */
char			*str_search_str(const char *big, const char *little,
					size_t len);

char			*str_search_set(const char *s, const char *set);

/**
 * @brief Splits a string into an array of strings based on a delimiter.
 * @ingroup string_functions
 * 
 * @param s The string to split.
 * @param c The delimiter character.
 * 
 * @return An array of strings, or NULL if the allocation failed.
 * Needs to be freed after use, including each string in the array.
 */
char			**str_split(char const *s, char c);

/**
 * @brief Returns a substring of a string.
 * @ingroup string_functions
 * 
 * @param s The string to extract the substring from.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * 
 * @return A pointer to the substring, or NULL if the allocation failed.
 * Needs to be freed after use.
 */
char			*str_substring(char const *s, unsigned int start, size_t len);

/**
 * @brief Removes leading and trailing characters from a string.
 * @ingroup string_functions
 * 
 * @param s1 The string to trim.
 * @param set The set of characters to remove.
 * 
 * @return A pointer to the trimmed string, or NULL if the allocation failed.
 * Needs to be freed after use.
 */
char			*str_trim(char const *s1, char const *set);

/*=====================================================================
--------------------------- Print formatted ---------------------------
=====================================================================*/

int				print_format(const char *format, ...);

#endif
