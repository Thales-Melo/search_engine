#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

// Um tipo Document armazena o nome do arquivo e a frequência da palavra no arquivo
typedef struct document {
    char *file_name;
    int freq;
} Document;

#endif