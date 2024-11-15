#ifndef AnalyseurSemantique
#define AnalyseurSemantique
#include <ctype.h>
#include "AnalyseurLexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *unitelexicales[2000][100];
int num_ul =0;
int ul_courant=0;
//Ces fonctions gèrent la progression à travers la séquence d'unités lexicales.


//avancer() passe à l'unité lexicale suivante.

void avancer(){
    ul_courant++;
}

//accepter vérifie si l'unité lexicale actuelle correspond à celle attendue. Si c'est le cas, elle avance ; sinon, elle affiche un message d'erreur
void accepter(const char *ul_attendu){
    if(strcmp(unitelexicales[ul_courant],ul_attendu)==0){
        avancer();
    }else{
        printf("Erreur de syntaxe: '%s' est attendu, mais on a trouvé '%s' \n", ul_attendu,unitelexicales[ul_courant]);
        avancer();
    }
}//cette fonction est une utilité pour afficher un message d'erreur et arrêter le programme en cas d'erreur sémantique
void signaler_erreur(const char *message) {
    printf("Erreur: %s\n", message);
    exit(EXIT_FAILURE);
}

//Ces fonctions correspondent à diverses règles dans la grammaire du langage Pascal simplifié
void P();
void DCL();
void DCL_prime();
void Liste_id();
void Liste_id_prime();
void Type();
void Inst_composee();
void Inst();
void Exp();
void Exp_prime();
void Exp_simple();
void Exp_simple_prime();
void Terme();
void Terme_prime();
void Facteur();
//P() ici correspond au programme principal

//L'analyse sémantique démarre dans P() lors de l'analyse du programme principal.
void P(){
    accepter("MOT_CLE_PROGRAM");
    accepter("IDENTIFICATEUR");
    accepter("POINT_VIRGULE");
    DCL();
    Inst_composee();
    accepter("POINT");
}
//cette fonction correspond aux déclarations
void DCL(){
    if (strcmp(unitelexicales[ul_courant],"var")==0){
        avancer();
        Liste_id();
        accepter("DEUX_POINTS");
        Type();
        DCL_prime();
    }
}
void DCL_prime() {
    if (strcmp(unitelexicales[ul_courant], ";") == 0) {
        avancer();
        DCL();
    }
}
void Liste_id(){
    accepter("IDENTIFICATEUR");
    Liste_id_prime();
}
void Liste_id_prime(){
    if(strcmp(unitelexicales[ul_courant],",")==0){
        avancer();
        accepter("IDENTIFICATEUR");
        Liste_id_prime();
    }
}
//cette fonction gère l'analyse syntaxique des types de variables
void Type(){
    if(strcmp(unitelexicales[ul_courant],'MOT_CLE_INTEGER')==0 || strcmp(unitelexicales[ul_courant],"CHAR")==0){
        avancer();
    }else{
        printf("Erreur de syntaxe: Type invalide 's'\n",unitelexicales[ul_courant]);
    }
}

//ces fonctions gèrent l'analyse syntaxique des instructions composées, des instructions simples et des structures de contrôle telles que if et while
void Inst_composee(){
    accepter("MOT_CLE_BEGIN");
    Inst();
    accepter("MOT_CLE_END");
}
void Inst() {
    if (strcmp(unitelexicales[ul_courant], "IDENTIFICATEUR") == 0) {
        avancer();
        accepter("EGAL");
        Exp_simple();
    } else if (strcmp(unitelexicales[ul_courant], "MOT_CLE_IF") == 0) {
        avancer();
        Exp();
        accepter("then");
        Inst();
        accepter("else");
        Inst();
    } else if (strcmp(unitelexicales[ul_courant], "MOT_CLE_WHILE") == 0) {
        avancer();
        Exp();
        accepter("do");
        Inst();
    } else if (strcmp(unitelexicales[ul_courant], "MOT_CLE_READ") == 0 || strcmp(unitelexicales[ul_courant], "MOT_CLE_READLN") == 0 ||
               strcmp(unitelexicales[ul_courant], "MOT_CLE_WRITE") == 0 || strcmp(unitelexicales[ul_courant], "MOT_CLE_WRITELN") == 0) {
        avancer();
        accepter("PARENTHESE_OUVRANTE");
        accepter("IDENTIFICATEUR");
        accepter("PARENTHESE_FERMENTE");
    } else {
        printf("Erreur de syntaxe: Instruction invalide '%s'\n", unitelexicales[ul_courant]);
    }
}


//Ces fonctions (Exp() .. Exp_Prime etc ..) gèrent l'analyse syntaxique des expressions, en tenant compte des opérateurs tels que ==, <, +, etc
void Exp(){
    Exp_simple();
    Exp_prime();
}
void Exp_prime() {
    if (strcmp(unitelexicales[ul_courant], "EGAL") == 0 || strcmp(unitelexicales[ul_courant], "DIFF") == 0 ||
        strcmp(unitelexicales[ul_courant], "INF") == 0 || strcmp(unitelexicales[ul_courant], "SUP") == 0 ||
        strcmp(unitelexicales[ul_courant], "INF_EGAL") == 0 || strcmp(unitelexicales[ul_courant], "SUP_EGAL") == 0) {
        avancer();
        Exp_simple();
    }
}
void Exp_simple(){
    Terme();
    Exp_simple_prime();
}
void Exp_simple_prime() {
    if (strcmp(unitelexicales[ul_courant], "PLUS") == 0 || strcmp(unitelexicales[ul_courant], "MOIN") == 0) {
        avancer();
        Terme();
        Exp_simple_prime();
    }
}
void Terme(){
    Facteur();
    Terme_prime();
}
void Terme_prime() {
    if (strcmp(unitelexicales[ul_courant], "MULT") == 0 || strcmp(unitelexicales[ul_courant], "DIV") == 0) {
        avancer();
        Facteur();
        Terme_prime();
    }
}

//cette fonction ( Facteur() )gère l'analyse syntaxique des facteurs dans les expressions (les nombres et les expressiosn imbriquées etc ..)

void Facteur() {
    if (strcmp(unitelexicales[ul_courant], "IDENTIFICATEUR") == 0 || strcmp(unitelexicales[ul_courant], "NOMBRE") == 0) {
        avancer();
    } else if (strcmp(unitelexicales[ul_courant], "PARENTHESE_OUVRANTE") == 0) {
        avancer();
        Exp_simple();
        accepter("PARENTHESE_FERMENTE");
    } else {
        printf("Erreur de syntaxe: Facteur invalide '%s'\n", unitelexicales[ul_courant]);
    }
}

#endif AnalyseurSemantique