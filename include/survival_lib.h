/**
 * @file survival_lib.h
 * @brief Comprehensive utility library for C programming
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-11-03
 */

#ifndef SURVIVAL_LIB_H
# define SURVIVAL_LIB_H

/**
 * @def BUFFER_SIZE
 * @brief Default buffer size for I/O operations
 * 
 * @details Defines the default size in bytes for buffers used in
 * read operations and temporary storage. Can be overridden at
 * compile time.
 * 
 * @ingroup io_module
 */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/**
 * @defgroup char_check_module Character Checking Module
 * @brief Character classification and validation functions
 * 
 * @details This module provides functions for checking character types
 * and properties, similar to the standard ctype.h functions but with
 * custom implementations.
 * 
 * @section char_check_features_sec Features
 * - Alphabetic character detection
 * - Numeric character detection
 * - ASCII range validation
 * - Custom set membership checking
 * - Whitespace detection
 * 
 * @section char_check_usage_sec Usage
 * All functions return non-zero (true) if the character matches the
 * criteria, or zero (false) otherwise.
 */

/**
 * @ingroup char_check_module
 * @{
 */
int				is_alphabetic(int c);
int				is_alphanumeric(int c);
int				is_ascii(int c);
int				is_digit(int c);
int				is_from_set(char c, const char *set);
int				is_print(int c);
int				is_space(char c);
/** @} */

/**
 * @defgroup str_compare_module String Comparison Module
 * @brief String comparison and search functions
 * 
 * @details This module provides functions for comparing strings and
 * checking for substring or character set containment.
 * 
 * @section str_compare_features_sec Features
 * - Full string comparison
 * - Length-limited comparison
 * - Character set containment checking
 * 
 * @section str_compare_usage_sec Usage
 * Comparison functions return 0 if strings are equal, negative if
 * the first is less than the second, and positive otherwise.
 */

/**
 * @ingroup str_compare_module
 * @{
 */
int				str_compare_all(const char *s1, const char *s2);
int				str_compare_n(const char *s1, const char *s2, size_t n);
int				str_contains(char *str, char *set);
/** @} */

/**
 * @defgroup conversion_module Type Conversion Module
 * @brief Functions for converting between different data types
 * 
 * @details This module provides comprehensive type conversion utilities
 * for converting between strings and numeric types, as well as case
 * conversion for characters.
 * 
 * @section conversion_features_sec Features
 * - Integer to string conversion
 * - Unsigned integer to string conversion
 * - Floating point to string conversion
 * - Base conversion for numbers (binary, octal, hex)
 * - String to integer/float parsing
 * - Character case conversion
 * 
 * @section conversion_usage_sec Usage
 * String conversion functions allocate memory that must be freed by
 * the caller. Numeric parsing functions return the converted value.
 */

/**
 * @ingroup conversion_module
 * @{
 */
char			*int_to_str(int n);
char			*uint_to_str(unsigned int n);
char			*float_to_str(float n, int decimals);
char			*bnum_to_str(int n, int base, int is_upper);
int				str_to_int(const char *nptr);
unsigned int	str_to_uint(const char *nptr);
float			str_to_float(const char *nptr);
int				to_upper(int c);
int				to_lower(int c);
/** @} */

/**
 * @defgroup memory_module Memory Management Module
 * @brief Low-level memory manipulation and allocation functions
 * 
 * @details This module provides functions for memory allocation,
 * manipulation, and inspection, similar to standard library functions
 * but with additional features and custom implementations.
 * 
 * @section memory_features_sec Features
 * - Zero-initialized allocation (callocation)
 * - Memory reallocation with size tracking
 * - Memory comparison and search
 * - Memory copying and moving
 * - Memory initialization and zeroing
 * - Memory block length calculation
 * 
 * @section memory_usage_sec Usage
 * All allocation functions return NULL on failure. Memory manipulation
 * functions handle overlapping regions safely when using mem_move.
 */

/**
 * @ingroup memory_module
 * @{
 */
void			*callocation(size_t nmemb, size_t size);
void			*reallocation(void *ptr, unsigned long new_size,
					unsigned long old_size);
int				mem_compare(const void *s1, const void *s2, size_t n);
void			*mem_copy(void *dest, const void *src, size_t n);
int				mem_len(void *ptr, size_t blk_size);
void			*mem_move(void *dest, const void *src, size_t n);
void			*mem_search(const void *s, int c, size_t n);
void			*mem_set(void *s, int c, size_t n);
void			set_zero(void *s, size_t n);
/** @} */

/**
 * @defgroup string_module String Manipulation Module
 * @brief High-level string manipulation and utility functions
 * 
 * @details This module provides comprehensive string manipulation
 * capabilities including concatenation, copying, searching, splitting,
 * and trimming operations.
 * 
 * @section string_features_sec Features
 * - Safe string concatenation and copying with size limits
 * - String duplication and joining
 * - String length calculation
 * - Character and substring searching (forward and reverse)
 * - String splitting by delimiter
 * - Substring extraction
 * - String trimming by character set
 * 
 * @section string_usage_sec Usage
 * Functions that allocate memory (str_duplicate, str_join, str_split,
 * str_substring, str_trim) return pointers that must be freed by the
 * caller. Safe copy/concat functions never write beyond the specified
 * buffer size.
 */

/**
 * @ingroup string_module
 * @{
 */
size_t			str_concat(char *dst, const char *src, size_t size);
size_t			str_copy(char *dst, const char *src, size_t size);
char			*str_duplicate(const char *s);
char			*str_join(char const *s1, char const *s2);
size_t			str_len(const char *str);
char			*str_search_char(const char *s, int c);
char			*str_search_rev_char(const char *s, int c);
char			*str_search_str(const char *big, const char *little,
					size_t len);
char			**str_split(char const *s, char c);
char			*str_substring(char const *s, unsigned int start, size_t len);
char			*str_trim(char const *s1, char const *set);
/** @} */

/**
 * @defgroup io_module Input/Output Module
 * @brief Formatted output and file reading functions
 * 
 * @details This module provides functions for formatted printing and
 * line-by-line file reading with automatic buffer management.
 * 
 * @section io_features_sec Features
 * - Formatted printing with variable arguments (printf-like)
 * - Line-by-line file reading with dynamic memory allocation
 * - Support for multiple file descriptors simultaneously
 * 
 * @section io_usage_sec Usage
 * print_format() works like printf. get_next_line() returns one line
 * at a time from a file descriptor and must be called repeatedly to
 * read the entire file. The returned string must be freed by the caller.
 */

/**
 * @ingroup io_module
 * @{
 */
int				print_format(const char *format, ...);
char			*get_next_line(int fd);
/** @} */

#endif
