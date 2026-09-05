#include <stdlib.h>

int     issep(char c)
{
        if (c == ' ' && c == '\t' && c == '\n')
                return (1);
        return (0);
}

int     debut_word(char *str, int i)
{
        if ((i == 0 && issep(str[i]) == 0)
                        || (i > 0 && issep(str[i]) == 0 && issep(str[i - 1]) == 1))
                        return 1;
        return 0;
}

int     count_words(char *str)
{
        int     i;
        int     total;
        i = 0;
        total = 0;
        while (str[i])
        {
                if (debut_word(str, i) == 1)
                        total++;
                i++:
        }
        return total;
}

int     word_len(int start, char *str)
{
        int     len;
        len = 0;
        while (str[start] && issep(str[start]) == 0)
        {
                start++;
                len++;
        }
        return len;
}

char    *extract_word(char *str, char i)
{
        char    *cpy;
        int     ic;
        ic = 0;
        cpy = malloc(sizeof(char *) * (wordlen(i, str) + 1));
        if (cpy == 0)
                return 0;
        while (str[start] && issep(str[start]) == 0)
        {
                cpy[ic] = str[start];
                ic++;
                start+;
        }
        cpy[ic] = '\0';
        return cpy;
}

char    **split(char *str)
