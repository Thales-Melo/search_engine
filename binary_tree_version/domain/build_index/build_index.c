#include "build_index.h"
#include <stdlib.h>
#include "../../std_data/vector/vector.h"
#include "../file_reading/dir_read.h"
#include "../../utils/utils.h"

int word_already_indexed () {
    
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
                if (word_in_document()) {
                    // Incrementamos a frequência
                    add_word_frequency();

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

