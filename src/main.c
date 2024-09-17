#include "hash_table.h"


#define STRING_SIZE_MAX 255
#define LINE_MAX_SZ 4096
#define WORDS_BUFFER_MAX 4096

void file_read_words(FILE *fp)
{
    hash_table_t *hash_table = hash_table_create();

    struct stat file_stat;
    fstat(fileno(fp), &file_stat);
    const size_t file_max_size = file_stat.st_size + 1;
    char buff[file_max_size];
    const char *delim = " .,?\n";

    while (fgets(buff, file_max_size, fp))
    {
        char *token = strtok(buff, delim);
        while (token)
        {

            hash_table_insert_with_count(hash_table, token, 10);

            token = strtok(NULL, delim);
        }
    }

    // printing and cleaning table;
    hash_table_print(hash_table);

    bucket_list_t *bucket_list = bucket_list_create_ref(hash_table);

    bucket_list_sort_q(bucket_list);
    bucket_list_print(bucket_list, 10);
    bucket_list_free(bucket_list);

    hash_table_destroy(hash_table);
}

int main(int argc, char **argv)
{

    // opening and reading from file;
    if (argc < 2)
    {
        perror("Please provide filename \n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        perror("Error reading file\n");
        exit(1);
    }

    file_read_words(fp);
    fclose(fp);
}