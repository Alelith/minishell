/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survival_lib.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:29:11 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 11:36:33 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file libft.h
 * @author Begonia de todos los santos
 * @author Liliana la de la ehquina 
 * @brief This is the header of the standar functions on C
 */

#ifndef SURVIVAL_LIB_H
# define SURVIVAL_LIB_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*=====================================================================
--------------------------- Check functions ---------------------------
=====================================================================*/

/**
 * @brief This function checks if a character is alphabetic (A-Z;a-z)
 * 
 * @param c The character to check
 * 
 * @return 0 if the character is alphabetic 1 otherwise
 */
int		is_alphabetic(int c);

int		is_alphanumeric(int c);
int		is_ascii(int c);
int		is_digit(int c);
int		is_print(int c);
int		str_compare(const char *s1, const char *s2, size_t n);

/*=====================================================================
------------------------ Conversion functions -------------------------
=====================================================================*/
char	*int_to_str(int n);
int		str_to_int(const char *nptr);
int		to_upper(int c);
int		to_lower(int c);

/*=====================================================================
-------------------------- Memory functions ---------------------------
=====================================================================*/
void	*callocation(size_t nmemb, size_t size);
int		mem_compare(const void *s1, const void *s2, size_t n);
void	*mem_copy(void *dest, const void *src, size_t n);
void	*mem_move(void *dest, const void *src, size_t n);
void	*mem_search(const void *s, int c, size_t n);
void	*mem_set(void *s, int c, size_t n);
void	set_zero(void *s, size_t n);

/*=====================================================================
-------------------------- String functions ---------------------------
=====================================================================*/
size_t	str_concat(char *dst, const char *src, size_t size);
size_t	str_copy(char *dst, const char *src, size_t size);
char	*str_duplicate(const char *s);
char	*str_join(char const *s1, char const *s2);
size_t	str_len(const char *str);
char	*str_search_char(const char *s, int c);
char	*str_search_rev_char(const char *s, int c);
char	*str_search_str(const char *big, const char *little, size_t len);
char	**str_split(char const *s, char c);
char	*str_substring(char const *s, unsigned int start, size_t len);
char	*str_trim(char const *s1, char const *set);

#endif