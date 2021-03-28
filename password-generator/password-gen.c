#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define DEFAULTLEN 16
#define FILEPATH "./en_USmodified.dic"
#define FILESIZE 38393
#define LONGESTWORD (23 + 1 + 1)

char *generate_password(int length, int user_friendly);
char get_random_char();
int string_to_int(char const *c);
int sumofarray(int arr[], size_t sz);
int randint(int start, int stop);
int *breakdown(int len);
void printarray(int *arr, size_t sz);
void zeroarray(int *arr, size_t sz);
void printarray_python(int *arr, size_t sz);
int determine_length(char *c);
void printarraychar(char *arr, size_t sz);

int main(int argc, char const *argv[])
{
    srand(time(0));
    int number;
    if (argc > 1)
        number = string_to_int(argv[1]);
    else
    {
        printf("Usage: password <length> [humanfriendly(0|1, default 0)]\n");
        return 0;
    }
    int human_friendly = 0;
    if (argc > 2)
        human_friendly = string_to_int(argv[2]);
    if (number < 8)
    {
        printf("I won't allow you to have such weak password, generating atleast 8 length\n");
        number = 8;
    }
    int check = 1;
    while (check == 1)
    {
        char *g = generate_password(number, human_friendly);
        printf("Generated Password: %s\n", g);
        free(g);
        printf("Press <enter> to generate new\n");
        getchar();
    }

    return 0;
}

// ascii
// 33-47, 58-64 special chars
// 48-57 numbers 0-9
//65-90 uppercase roman
//91- 96 special chars
//97-122 lowercase roman
//123-126 special char

int string_to_int(char const *c)
{
    int i = 0, j = 0;
    int number = 0;
    int max_int[11];
    while (c[i] != '\0')
    {
        if (c[i] > 47 && c[i] < 58)
        {
            max_int[i] = (c[i] - 48) % 10;
        }
        else
        {
            return 0;
        }
        i++;
    }
    max_int[i] = -1;
    i--;
    while (i > -1)
    {
        number += max_int[i] * (pow(10, j));
        i--;
        j++;
    }
    return number;
}

char get_random_char()
{
    return (rand() % (127 - 33)) + 33;
}

char *generate_password(int length, int user_friendly)
{
    char *password = malloc((length + 1) * sizeof(char));
    if (user_friendly == 0)
    {
        for (int i = 0; i < length; i++)
        {
            password[i] = get_random_char();
        }
        password[length] = '\0';
        return password;
    }
    else
    {
        FILE *stream;
        char words[FILESIZE][LONGESTWORD];
        char word[LONGESTWORD];
        int words_collected = 0;
        if (fopen_s(&stream, FILEPATH, "r") == 0)
        {

            while (fgets(word, LONGESTWORD, stream) != NULL)
            {
                strcpy_s(words[words_collected], LONGESTWORD, word);
                words_collected++;
            }
            fclose(stream);
        }
        int *p = breakdown(length);
        int p_iter = 0, wordlen = 0;
        char *w;
        int i = 0;
        while (p[p_iter] != 0)
        {
            do
            {
                w = words[randint(0, FILESIZE - 1)];
                wordlen = determine_length(w);
            } while (wordlen != p[p_iter]);
            for (int j = 0; j < p[p_iter]; j++, i++)
            {
                password[i] = w[j];
            }
            p_iter++;
        }
        free(p);
        password[length] = '\0';
        return password;
    }
}

int determine_length(char *c)
{
    int i = 0;
    while (c[i] != '\n')
    {
        i++;
    }
    return i;
}

int sumofarray(int arr[], size_t sz)
{
    int sum = 0;
    for (int i = 0; i < sz; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int randint(int start, int stop)
{
    stop++;
    int r;
    do
    {
        r = rand();
    } while (r % stop < start);
    return r % stop;
}

int *breakdown(int len)
{
    int smallestpart = len / 4, number = 0, iter = 0;
    int *parts = malloc(64 * sizeof(int));
    zeroarray(parts, 64);
    while (sumofarray(parts, 64) < len - (smallestpart + 1))
    {
        number = randint(2, smallestpart);
        parts[iter++] = number;
    }
    parts[iter] = len - sumofarray(parts, 64);
    return parts;
}

void printarray(int *arr, size_t sz)
{
    for (int i = 0; i < sz; i++)
    {
        printf("%d ==> %d\n", i, arr[i]);
    }
}

void printarraychar(char *arr, size_t sz)
{
    for (int i = 0; i < sz; i++)
    {
        printf("%d ==> %c\n", i, arr[i]);
    }
}

void printarray_python(int *arr, size_t sz)
{
    printf("[");
    for (int i = 0; i < sz; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}

void zeroarray(int *arr, size_t sz)
{
    for (int i = 0; i < sz; i++)
    {
        arr[i] = 0;
    }
}
