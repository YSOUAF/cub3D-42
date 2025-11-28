/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:42:55 by mozinedd          #+#    #+#             */
/*   Updated: 2025/11/27 16:15:26 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count (char const  *str, char c)
{
    int counter = 0;
    int in_word = 0;
    
    
     while (*str)
     {
        if(*str != c &&  in_word == 0)
        {
            in_word = 1; 
            counter++;
        }
        else if (*str == c && in_word == 1)
            in_word = 0;
      str++;
     }
    return (counter); 
}

static char *print_str (char *final_str, char *start, int len_word)
{
    int i = 0; 
    while (i < len_word)
    {
        final_str[i] = start[i];
        i++;
    }
    final_str[i] = '\0';
    return (final_str);
}

static char **free_split (char **final_str, int i)
{
    int j = 0; 
    while ( j < i)
    {
        free(final_str[j]);
        j++;
    }
    free(final_str);
    return NULL; 
}

char **fill_final_str (char **final_str, char const  *s, char c)
{
    char *start;
    int  len_word;
    int i = 0 ;

    while(*s)
    {
        if(*s != c)
        {
            start = (char *)s;
            while (*s && *s != c)
               {
                    s++;
               }
            len_word = (s - start);
            final_str[i] = (char *)ft_calloc((len_word + 1) , sizeof(char));
            if(final_str[i] == NULL)
                return(free_split(final_str, i)); 
            print_str(final_str[i], start, len_word);
            i++;
        }
        else
        {
            s++;
        }
    }
    return (final_str);
}
char **ft_split(char const *s, char c)
{
    int length = count(s, c);
   char **final_str;
   
   if (s == NULL)
    return (NULL);
    
   final_str = ft_calloc((length + 1) , sizeof(char *));
   if (final_str == NULL)
    return(NULL);
   return (fill_final_str(final_str, s, c));
}
