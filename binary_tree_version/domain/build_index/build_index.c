#include "build_index.h"
#include <stdlib.h>
#include "../../std_data/vector/vector.h"
#include "../file_reading/dir_read.h"
#include "../../utils/utils.h"
#include "../collection/collection.h"


int word_already_indexed (Tree *index, char *word) {
    return tree_contains_key(index, word);
}

int word_in_document(Tree *index, char *word, char *doc) {
    // Se word em index
    if (tree_contains_key(index, word)) {
        // Se doc em colecao de documentos
        if (tree_contains_key(((Tree*)tree_search(index, word)), doc)) {
            return 1;
        }
    }

    return 0;
}


void grow_word_frequency (int *frequency) {
    *frequency++;
}













void index_build (Tree *index, Vector *files) {
    double start = get_timestamp();

    // Para cada arquivo na lista de arquivos
    for (int i=0; i<vector_size(files); i++) {
        // Le o conteudo e separa as palavras
        Vector *words = read_file_splited(vector_get(files, i));

        // Para cada palavra
        for (int k=0; k<vector_size(words); k++) {
            char *word = (char*)vector_get(words, k);
            // Se a palavra já está no índice
            if (word_already_indexed(index, word)) {
                 // Se já vimos a palavra no documento
                if (word_in_document(index, word, vector_get(files, i))) {
                    // Incrementamos a frequência
                    Tree* aux = (Tree*)(tree_search(index, word));
                    Collection* col = (Collection*)tree_search(aux, vector_get(files, i));
                    

                }
                // Caso contrário
                else {
                    // Adicionamos o documento com frequência inicial 1
                    add_document();
                }
            }

            else {
                // Se a palavra não está no índice, adicionamos ela
                word_index_add(index, word);
                // Em seguida, associamos a palavra o documento com frequência inicial 1
                connect_word_to_document();
            }
        }

    }

    double end = get_timestamp();

    double dt = (end - start);
    printf ("TEMPO DE CONSTRUÇÃO DO ÍNDICE = ", dt);

}

