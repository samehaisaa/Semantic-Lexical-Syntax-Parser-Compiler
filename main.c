#include "AnalyseurLexical.h"
#include "AnalyseurSemantique.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//ce programme principal commence par lire le contenu du fichier source à compiler dans notre cas le le programme pascal dans le dossier 




char *readFileToString(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier '%s'\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END); 
    long fileSize = ftell(file); 
    fseek(file, 0, SEEK_SET); 
    char *fileContent = (char *)malloc(fileSize + 1);

    if (fileContent == NULL) {
        fclose(file);
        fprintf(stderr, "Allocation mémoire échouée\n");
        return NULL;
    }
    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    fileContent[bytesRead] = '\0'; 
    fclose(file);
    return fileContent;
}


int main() {
    const char *filename = "program.txt"; 
    char *content = readFileToString(filename);
    if (content != NULL) {
        printf("Contenu du fichier à compiler:\n%s\n", content);
    } else {
        printf("Lecture échouée.\n");
    }
    //Analyse lexicale
    size_t numTokens;
     /*La fonction analyseur de l'analyseur lexical( dans le fichier analyseur_lexical.h) est 
     appelée pour convertir le contenu du fichier en une séquence d'unités lexicales.*/

    UnitLex *ul = analyseur(content, &numTokens);
    if (ul != NULL) {
        printf("Nombre d'unités lexicales: %zu\n", numTokens);
        printf("Unité lexicale:\n");
        for (size_t i = 0; i < numTokens; ++i) {
            printf("%d - %s \n",i+1, UnitLexTab[ul[i]]); 
            strcpy(unitelexicales[i],UnitLexTab[ul[i]]);
        }
        printf("\n");
        free(ul); 
    } else {
        printf("Analyse lexicale échouée.\n");
    }
    //debut de l'analyse syntaxique et sémantique
    printf("************************************************** \n");
    printf("Erreurs Syntaxiques: \n");
    printf("\n");
    /*La fonction P() est appelée, marquant le début de l'analyse syntaxique et sémantique selon les règles de la grammaire*/
    P(); 

    
    free(content);
    return EXIT_SUCCESS;
}
