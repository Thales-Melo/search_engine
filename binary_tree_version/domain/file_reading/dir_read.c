#include "dir_read.h"
#include "../../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector *dir_build_file_names(char *dir, char *file_list_file_name) {
    Vector *file_names = vector_construct();

    char path[100];
    sprintf(path, "%s/%s", dir, file_list_file_name);

    FILE *F = fopen(path, "r");

    if (F == NULL) {
        printf("Erro ao abrir o arquivo %s\n", path);
        exit(1);
    }

    char line[100];

    while (fgets(line, 100, F) != NULL) {
        if (line[strlen(line) - 1] != 't') {
            line[strlen(line) - 1] = '\0';
        }
        char file_path[120];
        sprintf(file_path, "%s/%s", dir, line);

        vector_push_back(file_names, strdup(file_path));
    }

    fclose(F);

    return file_names;
}

char *read_file_to_string(const char *file_name) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", file_name);
        exit(1);
    }

    // Obter o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = (char *)malloc(file_size + 1);

    if (file_content == NULL) {
        printf ("Erro ao alocar memória para armazenar o conteúdo do arquivo %s\n", file_name);
        exit(1);
    }

    // Ler o conteúdo do arquivo para a string alocada
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0'; 

    fclose(file);

    return file_content;
}

Vector *read_file_splited(char *file_name) {
    // Ler todo o arquivo e armazenar em uma string
    char *file_content = read_file_to_string(file_name);

    Vector *split = string_split(file_content);

    if (file_content != NULL) {
        free(file_content);
        file_content = NULL;
    }

    return split;
}