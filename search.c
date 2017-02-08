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
    int idx = 0, n = strlen(buffer);
    for (idx = 0; idx < n; ++idx) {
        if (match(key, buffer + idx)) printf("%d\n", idx);
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
    
    search(key, buffer);
    
    return EXIT_SUCCESS;
}
