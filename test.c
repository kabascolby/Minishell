// #include <string.h>
// #include <stdio.h>

// char * ft_strtok_r (char *s, const char *filter, char **save_ptr)
// {
//   char *end;
//   if (s == NULL)
//     s = *save_ptr;
//   if (*s == '\0')
//     {
//       *save_ptr = s;
//       return NULL;
//     }
//   /* Scan leading delimiters.  */
//   s += strspn(s, filter);
//   if (*s == '\0')
//     {
//       *save_ptr = s;
//       return NULL;
//     }
//   /* Find the end of the token.  */
//   end = s + strcspn (s, filter);
//   if (*end == '\0')
//     {
//       *save_ptr = end;
//       return s;
//     }
//   /* Terminate the token and make *SAVE_PTR point past it.  */
//   *end = '\0';
//   *save_ptr = end + 1;
//   return s;
// }

// int main(int argc, char **argv)
// {
// 	//   char *str = "Mohamed Lamine Kaba est un eleve * bon";

// 	char *tab[8];
// 	int i = 0;
// 	while ((tab[i] = ft_strtok_r(argv[1], " *est", &argv[1])) != NULL)
// 		i++;
// 	for (int i = 0; tab[i] && i < 8; i++)
// 		printf("%s\n", tab[i]);
// 	return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// #define LSH_TOK_BUFSIZE 64
// #define LSH_TOK_DELIM " \t\r\n\a"

// // #include <stddef.h>
// #include <string.h>

// char *ft_strtok(s, delim)
//     register char *s;
//     register const char *delim;
// {
//     register char *spanp;
//     register int c, sc;
//     char *tok;
//     static char *last;


//     if (s == NULL && (s = last) == NULL)
//         return (NULL);

//     /*
//      * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
//      */
// cont:
//     c = *s++;
//     for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
//         if (c == sc)
//             goto cont;
//     }

//     if (c == 0) {        /* no non-delimiter characters */
//         last = NULL;
//         return (NULL);
//     }
//     tok = s - 1;

//     /*
//      * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
//      * Note that delim must have one NUL; we stop if we see that, too.
//      */
//    while(1) {
//         c = *s++;
//         spanp = (char *)delim;
//         do {
//             if ((sc = *spanp++) == c) {
//                 if (c == 0)
//                     s = NULL;

//                 else
//                     s[-1] = 0;
//                 last = s;
//                 return (tok);
//             }
//         } while (sc != 0);
//     }
//     /* NOTREACHED */
// }

// char **lsh_split_line(char *line)
// {
//   int bufsize = LSH_TOK_BUFSIZE, position = 0;
//   char **tokens = malloc(bufsize * sizeof(char*));
//   char *token;

//   if (!tokens) {
//     fprintf(stderr, "lsh: allocation error\n");
//     exit(EXIT_FAILURE);
//   }

//   token = ft_strtok(line, LSH_TOK_DELIM);
//   while (token != NULL) {
//     printf("%s\n", token);
//     tokens[position] = token;
//     position++;

//     if (position >= bufsize) {
//       bufsize += LSH_TOK_BUFSIZE;
//       tokens = realloc(tokens, bufsize * sizeof(char*));
//       if (!tokens) {
//         fprintf(stderr, "lsh: allocation error\n");
//         exit(EXIT_FAILURE);
//       }
//     }

//     token = ft_strtok(NULL, LSH_TOK_DELIM);
//   }
//   tokens[position] = NULL;
//   return tokens;
// }

// int main() {

// char name[] = "Mohamed Lamine kaba";
// char **tok = lsh_split_line(name);

//   return 0;
// }





// #include <string.h>
// #include <stdio.h>

// char* mystrtok(char str[],char filter[]) 
// {
//     static char *ptr;
//     static int flag;
//     char* ptrReturn;
//     int i;
//     int j;
        
//     ptr = str;
//     if(filter == NULL) {
//         return str;
//     }
//     if(flag == 1) {
//         return NULL;
//     }
    
//     ptrReturn = ptr;
//     j = 0;
//     while(ptr != '\0') {
//         for(int i=0 ; filter[i] != '\0' ; i++) {
//             if(ptr[j] == '\0') {
//                 flag = 1;
//                 return ptrReturn;
//             }
//             if( ptr[j] == filter[i]) {
//                 ptr[j] = '\0';
//                 ptr+=j+1;
//                 return ptrReturn;
//             }
//         }
//         j++;
//     }
//     return NULL;
// }

// int main() {
//   char str [] = "Mohamed Lamine Kaba est un eleve * bon";
//   char *tab[8];
//   int i = 0;
//   char *s;
//   s = tab[0] = mystrtok(str, " *");
//   while(s != NULL)
//   {
//     tab[++i] = s = mystrtok(NULL, " *");
    
//   }
//   for(int i = 0; i < 8; i++){
// 	  printf("%s\n", tab[i]);
//   }

//   return 0;
// }

// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>


/* #include "minishell.h"
# define FREE_ARRAY(array, size) do {\
  unsigned int count;\
  count = 0;\
  while (count++ < size)\
  {\
    printf("------------->%d\n", count);\
    FREE(*array[count]);\
    printf("____________here_____\n");\
  }\
  free(array);\
} while (0)
int main() {
  int **tab;
  
  tab = malloc(8 * sizeof(int *));
  FREE_ARRAY(&tab, 8);

  return 0;
} */