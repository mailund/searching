#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char * read_file_content(char *fname)
{
    FILE *f = fopen(fname, "rb");
    if (!f) return 0;
    
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    
    string[fsize] = 0;
    
    return string;
}

static int match(char * key, char * buffer)
{
    char * k;
    char * b;
    
    for (k = key, b = buffer; *k && *b; ++k, ++b) {
        if (*k != *b) return 0;
    }
    
    return 1;
}

static void search(char * key, char * buffer)
{
    unsigned long idx = 0, n = strlen(buffer);
    for (idx = 0; idx < n; ++idx) {
        if (match(key, buffer + idx))
            printf("%lu\n", idx);
    }
}

static void ba_search(char * key, char * buffer)
{
    unsigned long n = strlen(buffer);
    unsigned long m = strlen(key);
    unsigned long ba[m];
    
    ba[0] = 0;
    for (unsigned long i = 1; i < m; ++i) {
        unsigned long b = ba[i-1];
        while (b > 0 && key[i] != key[b])
            b = ba[b-1];
        ba[i] = (key[i] == key[b]) ? b + 1 : 0;
    }
    
    unsigned long b = 0;
    for (unsigned long i = 0; i < n; ++i) {
        while (b > 0 && buffer[i] != key[b])
            b = ba[b-1];
        b = (buffer[i] == key[b]) ? b + 1 : 0;
        if (b == m)
            printf("%lu\n", i - m + 1);
    }
}

static void kmp_search(char * key, char * buffer)
{
    unsigned long n = strlen(buffer);
    unsigned long m = strlen(key);
    unsigned long ba[m];
    
    ba[0] = 0;
    for (unsigned long i = 1; i < m; ++i) {
        unsigned long b = ba[i-1];
        while (b > 0 && key[i] != key[b])
            b = ba[b-1];
        ba[i] = (key[i] == key[b]) ? b + 1 : 0;
    }
    
    unsigned long i, j; i = j = 0;
    while (i < n - m + j) {
        while (buffer[i] == key[j] && j < m) {
            ++i; ++j;
        }
        if (j == m) printf("%lu\n", i - m);
        if (j == 0) ++i;
        else j = ba[j-1];
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s key file\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char * key = argv[1];
    char * buffer = read_file_content(argv[2]);
    
    if (!buffer) {
        fprintf(stderr, "Error reading file \"%s\".\n", argv[2]);
        perror("Error");
        return EXIT_FAILURE;
    }
    
    //search(key, buffer);
    //ba_search(key, buffer);
    kmp_search(key, buffer);
    
    return EXIT_SUCCESS;
}
