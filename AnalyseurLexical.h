#ifndef ANALYSEURLEXICAL_H
#define ANALYSEURLEXICAL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Déclarations et Inclusions de Bibliothèques

//La première partie du fichier inclut les bibliothèques nécessaires et définit les constantes pour les différents codes de l'unité lexicale.

typedef enum {
    MOT_CLE_PROGRAM,
    MOT_CLE_BEGIN,
    MOT_CLE_END,
    MOT_CLE_IF,
    MOT_CLE_THEN,
    MOT_CLE_ELSE,
    MOT_CLE_WHILE,
    MOT_CLE_DO,
    MOT_CLE_READ,
    MOT_CLE_READLN,
    MOT_CLE_WRITE,
    MOT_CLE_WRITELN,
    MOT_CLE_INTEGER,
    MOT_CLE_CHAR,
    MOT_CLE_VAR,
    POINT_VIRGULE,
    VIRGULE,
    EGAL,
    EGAL_EGAL,
    DIFF,
    INF,
    INF_EGAL,
    SUP,
    SUP_EGAL,
    PLUS,
    MOINS,
    OU,
    MULT,
    DIV,
    MODULO,
    ET,
    IDENTIFICATEUR,
    NOMBRE,
    PARENTHESE_OUVRANTE,
    PARENTHESE_FERMANTE,
    COMMENTAIRE,
    INVALIDE= -1,
} UnitLex;


//Il y a deux tableaux importants : UnitLexTab qui stocke les noms correspondant aux codes des unités lexicales, et unitTab qui associe les lexèmes aux codes
const char *UnitLexTab[] = {
    "MOT_CLE_PROGRAM", "MOT_CLE_BEGIN", "MOT_CLE_END", "MOT_CLE_IF", "MOT_CLE_THEN",
    "MOT_CLE_ELSE", "MOT_CLE_WHILE", "MOT_CLE_DO", "MOT_CLE_READ", "MOT_CLE_READLN",
    "MOT_CLE_WRITE", "MOT_CLE_WRITELN", "MOT_CLE_INTEGER", "MOT_CLE_CHAR","MOT_CLE_VAR", "POINT_VIRGULE",
    "VIRGULE", "EGAL", "EGAL_EGAL", "DIFF", "INF", "INF_EGAL", "SUP", "SUP_EGAL", "PLUS",
    "MOINS", "OU", "MULT", "DIV", "MODULO", "ET", "IDENTIFICATEUR", "NOMBRE",
    "PARENTHESE_OUVRANTE", "PARENTHESE_FERMANTE", "COMMENTAIRE", "INVALIDE"
};

typedef struct {
    const char *lexeme;
    UnitLex uniLexCode;
} UniteInfo;



UniteInfo unitTab[] = {
    {"program", MOT_CLE_PROGRAM},
    {"begin", MOT_CLE_BEGIN},
    {"end", MOT_CLE_END},
    {"if" , MOT_CLE_IF},
    {"then", MOT_CLE_THEN},
    {"else", MOT_CLE_ELSE},
    {"while", MOT_CLE_WHILE},
    {"do" , MOT_CLE_DO},
    {"read", MOT_CLE_READ},
    {"readln" , MOT_CLE_READLN},
    {"write" , MOT_CLE_WRITE},
    {"writeln" , MOT_CLE_WRITELN},
    {"integer" , MOT_CLE_INTEGER},
    {"char", MOT_CLE_CHAR},
    {"var", MOT_CLE_VAR},
    {";", POINT_VIRGULE},
    {"," , VIRGULE},
    {":=" , EGAL},
    {"==" , EGAL_EGAL},
    {"<>" , DIFF},
    {"<" , INF},
    {"<=" , INF_EGAL},
    {">" , SUP},
    {">=" , SUP_EGAL},
    {"+" , PLUS},
    {"-" , MOINS},
    {"||" , OU},
    {"*" , MULT},
    {"/", DIV},
    {"%", MODULO},
    {"&&", ET},
    {"id", IDENTIFICATEUR},
    {"nb", NOMBRE},
    {"(" ,PARENTHESE_OUVRANTE},
    {")", PARENTHESE_FERMANTE},
    {"**", COMMENTAIRE}
};
//estIdentificateur, estCommentaire, et estChiff sont des fonctions utilitaires pour déterminer le type du lexème.

int estIdentificateur(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    if (!isalpha(*str)) {
        return 0;
    }
    while (*(++str) != '\0') {
        if (!isalnum(*str)) {
            return 0;
        }
    }
    return 1;
}

int estCommentaire(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    size_t len = strlen(str);
    if (len < 2) {
        return 0;
    }
    if (str[0] == '*' && str[len - 1] == '*') {
        return 1;
    }
    return 0;
}

int estChiff(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return 0;
        }
        str++;
    }
    return 1;
}
//Cette fonction prend un lexème en entrée et renvoie le code correspondant de l'unité lexicale en utilisant le tableau unitTab
UnitLex getUniLexCode(const char *lexeme) {
    for (size_t i = 0; i < sizeof(unitTab) / sizeof(unitTab[0]); ++i) {
        if (strcmp(unitTab[i].lexeme, lexeme) == 0) {
            return unitTab[i].uniLexCode;
        }
    }
    if(estChiff(lexeme)){
        return 32;
    }
    else if(estCommentaire(lexeme)){
        return 35;
    }
    else if(estIdentificateur(lexeme)){
        return 31;
    }
    return INVALIDE;
}
//Cette fonction prend une chaîne de caractères en entrée, la divise en jetons (tokens) en utilisant l'espace comme délimiteur, et attribue un code d'unité lexicale à chaque jeton en utilisant la fonction getUniLexCode
UnitLex *analyseur(const char *input, size_t *numTokens) {

    char *inputSTR = strdup(input);
    if (inputSTR == NULL) {
        fprintf(stderr, "Allocation mémoire échouée.\n");
        *numTokens = 0;
        return NULL;
    }
    UnitLex *UL = (UnitLex *)malloc(strlen(inputSTR) * sizeof(UnitLex));
    if (UL == NULL) {
        fprintf(stderr, "Allocation mémoire échouée.\n");
        free(inputSTR);
        *numTokens = 0;
        return NULL;
    }
    char *token = strtok(inputSTR, " ");
    size_t count = 0;
    while (token != NULL) {
        UnitLex unilexCode = getUniLexCode(token);
        UL[count++] = unilexCode;
        token = strtok(NULL, " ");
    }
    *numTokens = count;
    free(inputSTR);
    return UL;
}

#endif ANALYSEURLEXICAL_H