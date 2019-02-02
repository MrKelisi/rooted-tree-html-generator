#include <stdlib.h>

typedef struct Noeud {
	char Valeur;
	struct Noeud *fg, *fd;
} TNoeud, *TExprArb;

const TExprArb VIDE = NULL;


void Erreur(char *Msg) {
// Affiche un message d'erreur contenant *Msg

	printf("\n\n  * * * E R R E U R :  %s\n", Msg);
	getchar();
	exit(EXIT_FAILURE);
}


///////////////////////////////////////
//
//  Primitives de CONSULTATION
//
///////////////////////////////////////

char Racine(TExprArb A) {
// Donne le caract�re � la racine de l'EAA E (E non vide)

	if (A == VIDE) 
		Erreur("Erreur fonction Racine(TExprArb A) : A ne peut pas �tre vide!");

	return (*A).Valeur;
}

TExprArb Fg(TExprArb A) {
// Donne, si possible, le fils gauche de E (E non vide)

	if (A == VIDE) 
		Erreur("Erreur fonction Fg(TExprArb A) : A ne peut pas �tre vide!");

	return A->fg;
}

TExprArb Fd(TExprArb A) {
// Donne, si possible, le fils droit de E (E non vide)

	if (A == VIDE) 
		Erreur("Erreur fonction Fd(TExprArb A) : A ne peut pas �tre vide!");

	return A->fd;
}



///////////////////////////////////////
//
//  Primitives de CONSTRUCTION
//
///////////////////////////////////////

TExprArb Cons2(char X, TExprArb fg, TExprArb fd) {
// Construit le noeud d'EAA : <c, F_g, F_d>

	TExprArb NA = (TNoeud *) malloc(sizeof(TNoeud));
	NA->Valeur = X;
	NA->fg = fg;
	NA->fd = fd;

	return NA;
}

TExprArb ConsF(char X) {
// Construit le noeud externe (c�d une feuille) d'EAA : <c, VIDE, VIDE>

	TExprArb NA = (TNoeud *)malloc(sizeof(TNoeud));
	NA->Valeur = X;
	NA->fg = VIDE;
	NA->fd = VIDE;

	return NA;
}

bool EstFeuille(TExprArb A) {
	//Donne true ssi E (non vide) est r�duit � une feuille

	return (A->fg) == (A->fd);
}