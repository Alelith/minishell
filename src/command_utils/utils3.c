/**
 * @file utils3.c
 * @brief Environment variable sorting and display utilities
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-10-04
 */

#include "minishell.h"

/**
 * @brief Counts the number of nodes in environment list
 * 
 * @details Traverses the linked list to determine total count of
 * environment variables.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] env Head of environment variable linked list
 * @return Number of environment variables in list
 */
static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * @brief Converts environment linked list to array
 * 
 * @details Creates a NULL-terminated array of pointers to environment
 * nodes. Used for efficient sorting operations.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] env Head of environment variable linked list
 * @return NULL-terminated array of environment node pointers
 * @retval NULL if allocation fails
 */
static t_env	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	t_env	**arr;

	size = env_list_size(env);
	arr = malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * @brief Compares two strings using ASCII values
 * 
 * @details Performs character-by-character comparison based on ASCII
 * values. Used for alphabetical sorting of environment variables.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] s1 First string to compare
 * @param[in] s2 Second string to compare
 * @return Difference between first differing characters
 * @retval 0 if strings are equal
 * @retval <0 if s1 < s2
 * @retval >0 if s1 > s2
 */
static int	ascii_cmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * @brief Sorts environment variable array alphabetically
 * 
 * @details Implements bubble sort algorithm to sort environment variables
 * by key name in ASCII order. Modifies the array in place.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in,out] arr NULL-terminated array of environment node pointers
 */
static void	sort_env_array(t_env **arr)
{
	int		i;
	int		sorted;
	t_env	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i + 1])
		{
			if (ascii_cmp(arr[i]->pair.key, arr[i + 1]->pair.key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

/**
 * @brief Prints environment variables in sorted order
 * 
 * @details Converts environment list to array, sorts alphabetically,
 * and prints each variable using export format. Used by the export
 * built-in when called without arguments.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] env Head of environment variable linked list
 * @return 0 on success, 1 on allocation failure
 */
int	print_sorted_env(t_env *env)
{
	t_env	**arr;
	int		i;

	if (!env)
		return (0);
	arr = env_to_array(env);
	if (!arr)
		return (1);
	sort_env_array(arr);
	i = 0;
	while (arr[i])
	{
		if (arr[i]->pair.value)
			print_export(arr[i]->pair.key, arr[i]->pair.value);
		else
			print_export(arr[i]->pair.key, 0);
		i++;
	}
	free(arr);
	return (0);
}
