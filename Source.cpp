#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>
#include "TExprArb.h"


const double M_PI = 3.14159265359;
const int NbSegments = 1000;

double Min(double a, double b) {
	// Donne le minimum entre a et b

	return (a < b) ? a : b;
}
double Max(double a, double b) {
	// Donne le maximum entre a et b

	return (a > b) ? a : b;
}

TExprArb CopieEAA(TExprArb E) {
	// Donne une copie conforme et distincte de l'EAA E

	if (E == VIDE)
		return VIDE;
	else if (EstFeuille(E))
		return ConsF(Racine(E));
	else
		return Cons2(Racine(E), CopieEAA(Fg(E)), CopieEAA(Fd(E)));
}

char NatureNoeud(TExprArb E) {
	// Donne la nature du noeud (E non vide) sous forme de caractère : Variable, Unaire, Binaire, Fonction ou Constante

	char rac = Racine(E);

	switch (rac) {
	case('x') : return 'V';
	case('-') : if (Fg(E) == VIDE) return 'U';
				else return 'B';
	case('+') : return 'B';
	case('*') : return 'B';
	case('/') : return 'B';
	case('K') : return 'F';
	case('R') : return 'F';
	case('E') : return 'F';
	case('L') : return 'F';
	case('S') : return 'F';
	case('C') : return 'F';
	case('A') : return 'F';
	default: return 'C';
	}

}

bool EstConstanteEAA(TExprArb E) {
	// Donne vrai ssi E est une expression constante
	// Sert pour la dérivation et la simplification formelle!

	bool FgConst = true,
		FdConst = true;
	TExprArb F_g = Fg(E),
		F_d = Fd(E);

	if (F_g != VIDE)   // Est-ce que F_g (s'il existe) est constant ?
		FgConst = EstConstanteEAA(F_g);
	if (F_d != VIDE)   // Est-ce que F_d (s'il existe) est constant ?
		FdConst = EstConstanteEAA(F_d);

	return ((NatureNoeud(E) != 'V') && FgConst && FdConst);  // Si les deux fils et la racine sont constants, renvoie true
}

bool EgauxCommEAA(TExprArb E, TExprArb F) {
	// Renvoie vrai si E et F sont égaux (en tenant compte de la commutativité de + et *)

	if (E == VIDE && F == VIDE)
		return true;

	else if (E != VIDE && F != VIDE) {

		TExprArb E_Fg = Fg(E),
			E_Fd = Fd(E),
			F_Fg = Fg(F),
			F_Fd = Fd(F);
		char racE = Racine(E),
			racF = Racine(F);

		if ((EgauxCommEAA(E_Fg, F_Fg) && EgauxCommEAA(E_Fd, F_Fd))) {
			if (racE == racF)
				return true;
			else
				return false;
		}
		else if (EgauxCommEAA(E_Fg, F_Fd) && EgauxCommEAA(E_Fd, F_Fg)) {
			if (racE == racF) {
				if (NatureNoeud(E) == 'B' && (racE == '+' || racE == '*'))
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;

}

void AfficherBlancs(int n) {
	//Affiche n espaces

	while (n > 0) {
		putchar(' ');
		n--;
	}
}

void AfficherEAAArb(TExprArb E, int n) {
	//Affiche l'arborescence d'une EAA

	if (E != VIDE) {
		if (EstFeuille(E)) {
			AfficherBlancs(n);
			printf("%c\n", Racine(E));
		}
		else {
			AfficherEAAArb(Fd(E), n + 3);

			AfficherBlancs(n);
			printf("%c\n", Racine(E));

			AfficherEAAArb(Fg(E), n + 3);
		}
	}
}

void AfficherEAALin(TExprArb E) {
	//Afficher linéairement l'expression E

	char rac = Racine(E);
	TExprArb F_g = Fg(E), F_d = Fd(E);

	switch (rac) {
	case '+': {
				  printf("(");
				  AfficherEAALin(F_g);
				  printf("+");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case '-': {
				  printf("(");
				  if (NatureNoeud(E) == 'B') {
					  AfficherEAALin(F_g);
				  }
				  printf("-");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;

	}
	case '*': {
				  printf("(");
				  AfficherEAALin(F_g);
				  printf(".");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case '/': {
				  printf("(");
				  AfficherEAALin(F_g);
				  printf("/");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'C': {
				  printf("cos(");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'S': {
				  printf("sin(");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'A': {
				  printf("arctan(");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'K': {
				  printf("(");
				  AfficherEAALin(F_d);
				  printf("^2)");
				  break;
	}
	case 'R': {
				  printf("sqrt(");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'E': {
				  printf("exp(");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'L': {
				  printf("ln(");
				  AfficherEAALin(F_d);
				  printf(")");
				  break;
	}
	case 'P': {
				  printf("pi");
				  break;
	}
	default: printf("%c", rac);
	}
}

TExprArb DeriveEAA(TExprArb E) {
	//Donne la dérivée par rapport à x de l'EAA E non vide

	if (E == VIDE)
		return VIDE;

	else if (EstFeuille(E)) {
		if (Racine(E) == 'x')
			return ConsF('1');
		else
			return ConsF('0');
	}
	else {
		TExprArb F_g = Fg(E), F_d = Fd(E);
		char rac = Racine(E);
		switch (rac) {

		case '+':   // [u + v]' = u' + v'
			return Cons2('+', DeriveEAA(F_g), DeriveEAA(F_d));

		case '-':   // [u - v]' = u' - v'
			return Cons2('-', DeriveEAA(F_g), DeriveEAA(F_d));

		case '/':   // [u / v]' = (u'.v - u.v') / v^2
			return Cons2('/', Cons2('-', Cons2('*', DeriveEAA(F_g), CopieEAA(F_d)), Cons2('*', CopieEAA(F_g), DeriveEAA(F_d))), Cons2('K', VIDE, CopieEAA(F_d)));

		case '*':
			if (EstConstanteEAA(F_g))           // Multiplication par un scalaire à gauche : [a.u(x)]' = a.u'(x)
				return Cons2('*', CopieEAA(F_g), DeriveEAA(F_d));

			else if (EstConstanteEAA(F_d))      // Multiplication par un scalaire à droite : [u(x).a]' = a.u'(x)
				return Cons2('*', CopieEAA(F_d), DeriveEAA(F_g));

			else                                // Multiplication de fonctions : [u(x).v(x)]' = u'.v + u.v'
				return Cons2('+', Cons2('*', DeriveEAA(F_g), CopieEAA(F_d)), Cons2('*', CopieEAA(F_g), DeriveEAA(F_d)));


		case 'C':   // cos'(u) = -u'.sin(u)
			return Cons2('*', Cons2('-', VIDE, DeriveEAA(F_d)), Cons2('S', VIDE, CopieEAA(F_d)));

		case 'S':   // sin'(u) = u'.cos(u)
			return Cons2('*', DeriveEAA(F_d), Cons2('C', VIDE, CopieEAA(F_d)));

		case 'K':   // (u^2)' = 2.u'.u
			return Cons2('*', ConsF('2'), Cons2('*', DeriveEAA(F_d), CopieEAA(F_d)));

		case 'R':   // sqrt'(u) = u' / (2.sqrt(u))
			return Cons2('/', DeriveEAA(F_d), Cons2('*', ConsF('2'), Cons2('R', VIDE, CopieEAA(F_d))));

		case 'E':   // e'(u) = u'.e(u)
			return Cons2('*', DeriveEAA(F_d), Cons2('E', VIDE, CopieEAA(F_d)));

		case 'L':   // ln'(u) = u' / u
			return Cons2('/', DeriveEAA(F_d), CopieEAA(F_d));

		case 'A':   // arctan'(u) = u' / (1 + u^2)
			return Cons2('/', DeriveEAA(F_d), Cons2('+', ConsF('1'), Cons2('K', VIDE, CopieEAA(F_d))));

		default: return VIDE;
		}
	}
}

TExprArb SimplifieEAA(TExprArb E) {
	// Simplifie, au mieux, l'EAA E

	if (EstFeuille(E))       // L'abre est un feuille, on renvoie simplement la feuille
		return CopieEAA(E);

	else {                   // L'arbre est un noeud, donc potentiellement simplifiable :

		TExprArb F_g = VIDE, F_d = SimplifieEAA(Fd(E));
		if (Fg(E) != VIDE)
			F_g = SimplifieEAA(Fg(E));
		char rac = Racine(E);

		switch (rac) {
		case '+':
			if (EgauxCommEAA(F_g, ConsF('0')))                // Somme avec 0 à gauche -> on renvoie le fils droit
				return CopieEAA(F_d);

			else if (EgauxCommEAA(F_d, ConsF('0')))           // Somme avec 0 à droite -> on renvoie le fils gauche
				return CopieEAA(F_g);

			else if (NatureNoeud(F_d) == 'U')                 // Le fils droit est un opposé -> on transforme le tout en une soustraction
				return Cons2('-', CopieEAA(F_g), Fd(F_d));

			else if (EgauxCommEAA(F_g, F_d))                  // u + u -> on renvoie 2.u
				return Cons2('*', ConsF('2'), CopieEAA(F_g));

			else if (Racine(F_g) == 'K' && Racine(F_d) == 'K') {
				if ((Racine(Fd(F_g)) == 'C' && Racine(Fd(F_d)) == 'S') || (Racine(Fd(F_g)) == 'S' && Racine(Fd(F_d)) == 'C')) {
					if (EgauxCommEAA(Fd(Fd(F_g)), Fd(Fd(F_d)))) 
						return ConsF('1');                    // cos²(u) + sin²(u) -> on renvoie 1
				}
				return Cons2(rac, F_g, F_d);
			}

			else                                              // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case '-':

			if (NatureNoeud(F_d) == 'U' && NatureNoeud(E) == 'U')  // Si on a -(-u) -> on renvoie u
				return Fd(F_d);

			if (NatureNoeud(F_d) == 'U' && NatureNoeud(E) == 'B')  // Si on a u-(-v) -> on renvoie u+v
				return Cons2('+', CopieEAA(F_g), Fd(F_d));

			else if (EgauxCommEAA(F_d, ConsF('0')))                // Différence avec 0 à droite -> on renvoie le fils gauche
				return CopieEAA(F_g);

			else if (EgauxCommEAA(F_g, ConsF('0')))                // Diférence avec 0 à gauche -> on renvoie l'opposé du fils droit
				return Cons2('-', VIDE, CopieEAA(F_d));

			else if (EgauxCommEAA(F_g, F_d))                       // u-u -> on renvoie 0
				return ConsF('0');

			else                                                   // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case '*':
			if (EgauxCommEAA(F_g, ConsF('1')))                                       // Produit avec 1 à gauche -> on renvoie le fils droit
				return CopieEAA(F_d);

			else if (EgauxCommEAA(F_d, ConsF('1')))                                  // Produit avec 1 à droite -> on renvoie le fils gauche
				return CopieEAA(F_g);

			else if (EgauxCommEAA(F_g, ConsF('0')) || EgauxCommEAA(F_d, ConsF('0'))) // Produit avec 0 à gauche ou à droite -> on renvoie 0
				return ConsF('0');

			else if (EgauxCommEAA(F_g, Cons2('-', VIDE, ConsF('1'))))                // Produit par -1 à gauche -> on renvoie l'opposé du fils droit
				return Cons2('-', VIDE, CopieEAA(F_d));

			else if (EgauxCommEAA(F_d, Cons2('-', VIDE, ConsF('1'))))                // Produit par -1 à droite -> on renvoie l'opposé du fils gauche
				return Cons2('-', VIDE, CopieEAA(F_g));

			else if (EgauxCommEAA(F_g, F_d))                                         // u.u -> on renvoie u²
				return Cons2('K', VIDE, F_d);

			else if (Racine(F_g) == 'K' && Racine(F_d) == 'K')                       // u².v² -> on renvoie (u.v)²
				return Cons2('K', VIDE, Cons2('*', CopieEAA(F_g), CopieEAA(F_d)));

			else if (EgauxCommEAA(Cons2('-', VIDE, F_g), F_d) || EgauxCommEAA(F_g, Cons2('-', VIDE, F_d)))  // u.(-u) ou (-u).u -> on renvoie -(u²)
				return Cons2('-', VIDE, Cons2('K', VIDE, CopieEAA(F_g)));

			else if (NatureNoeud(F_g) == 'U')                                        // (-u).v -> on renvoie -(u.v)
				return Cons2('-', VIDE, Cons2('*', Fd(F_g), CopieEAA(F_d)));

			else if (NatureNoeud(F_d) == 'U')                                        // u.(-v) -> on renvoie -(u.v)
				return Cons2('-', VIDE, Cons2('*', CopieEAA(F_g), Fd(F_d)));

			else if (Racine(F_d) == '/' && EgauxCommEAA(F_g, Fd(F_d)))               // u . (v/u) -> on renvoie v
				return Fg(F_d);

			else if (Racine(F_g) == '/' && EgauxCommEAA(Fd(F_g), F_d))               // (v/u) * u -> on renvoie v
				return Fg(F_g);

			else                                                                     // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case '/':
			if (EgauxCommEAA(F_g, ConsF('0')))                                     // Division avec 0 à gauche (numérateur) -> on renvoie 0
				return ConsF('0');

			else if (EgauxCommEAA(F_g, F_d))                                       // Numérateur = Dénominateur -> on renvoie 1
				return ConsF('1');

			else if (EgauxCommEAA(F_d, ConsF('1')))                                // Dénominateur égal à 1 -> on renvoie le numérateur
				return CopieEAA(F_g);

			else if (Racine(F_g) == 'K' && Racine(F_d) == 'K')                     // u²/v² -> on renvoie (u/v)²
				return Cons2('K', VIDE, Cons2('/', CopieEAA(F_g), CopieEAA(F_d)));

			else if (NatureNoeud(F_g) == 'U')                                      // (-u)/v -> on renvoie -(u/v) : PAS TRES INTERESSANT, PEUT ETRE A ENLEVER
				return Cons2('-', VIDE, Cons2('/', Fd(F_g), CopieEAA(F_d)));

			else                                                                   // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case 'E':
			if (EgauxCommEAA(F_d, ConsF('0')))   // exp(0) = 1
				return ConsF('1');

			else if (Racine(F_d) == 'L')         // exp(ln(u)) = u
				return CopieEAA(Fd(F_d));

			else                                 // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case 'L':
			if (EgauxCommEAA(F_d, ConsF('1')))   // ln(1) = 0
				return ConsF('0');

			else if (Racine(F_d) == 'E')         // ln(exp(u)) = u
				return CopieEAA(Fd(F_d));

			else                                 // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case 'S':
			if (EgauxCommEAA(F_d, ConsF('0')))                        // sin(0) = 0
				return ConsF('0');

			else if (Racine(F_d) == '-')                              // sin(-u) = -sin(u)
				return Cons2('-', VIDE, Cons2('S', VIDE, Fd(F_d)));

			else                                                      // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case 'C':
			if (EgauxCommEAA(F_d, ConsF('0')))       // cos(0) = 1
				return ConsF('1');

			else if (Racine(F_d) == '-')             // cos(-u) = cos(u)
				return Cons2('C', VIDE, Fd(F_d));

			else                                     // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case 'K':
			if (Racine(F_d) == 'R')                                                                // sqrt²(u) -> on renvoie u
				return Fd(F_d);

			else if (Racine(F_d) == 'E')                                                           // exp²(u) -> on renvoie exp(2.u)
				return Cons2('E', VIDE, Cons2('*', ConsF('2'), Fd(F_d)));

			else if (Racine(F_d) == 'L')                                                           // ln²(u) -> on renvoie 2*ln(u)
				return Cons2('*', ConsF('2'), Cons2('L', VIDE, Fd(F_d)));

			else if (NatureNoeud(F_d) == 'U')                                                      // (-u)² -> on renvoie u²
				return Cons2('K', VIDE, Fd(F_d));

			else if (EgauxCommEAA(F_d, ConsF('0')) || EgauxCommEAA(F_d, Cons2('-', VIDE, ConsF('0'))))  // 0² = 0
				return ConsF('0');

			else if (EgauxCommEAA(F_d, ConsF('1')) || EgauxCommEAA(F_d, Cons2('-', VIDE, ConsF('1'))))  // 1² = 1
				return ConsF('1');

			else if (EgauxCommEAA(F_d, ConsF('2')) || EgauxCommEAA(F_d, Cons2('-', VIDE, ConsF('2'))))  // 2² = 4
				return ConsF('4');

			else if (EgauxCommEAA(F_d, ConsF('3')) || EgauxCommEAA(F_d, Cons2('-', VIDE, ConsF('3'))))  // 3² = 9
				return ConsF('9');

			else                                                                                        // On ne peut pas simplifier
				return Cons2(rac, F_g, F_d);

		case 'A':
			if (NatureNoeud(F_d) == 'U')            // arctan(-u) -> on renvoie arctan(u)
				return Cons2('A', VIDE, Fd(F_d));
			else                                    // On ne peut pas simplifier
				return Cons2('A', F_g, F_d);

		default: return Cons2(rac, F_g, F_d);  // Par défaut, on ne change rien
		}
	}

}

///////////////////////////////////////////////////
//
//  Projet Perso : HOCHLANDER Matthieu
//
///////////////////////////////////////////////////


void CalculLargeur(TExprArb a, double *largeurDroite, double *largeurGauche)
{ // Calcule la place nécessaire pour l'affichage du fils droit et celle du fils gauche ; L'arbre ne doit pas être vide !

	if (Fd(a) == VIDE)
	{
		*largeurDroite = 30;
		*largeurGauche = 30; // S'il n'y a pas de fils droit, alors il n'y aura forcément pas de fils gauche
	}
	else
	{
		double largeurDroiteFD, largeurGaucheFD;
		CalculLargeur(Fd(a), &largeurDroiteFD, &largeurGaucheFD);
		*largeurDroite = largeurDroiteFD + largeurGaucheFD;

		if (Fg(a) == VIDE)
			*largeurGauche = 30;
		else
		{
			double largeurDroiteFG, largeurGaucheFG;
			CalculLargeur(Fg(a), &largeurDroiteFG, &largeurGaucheFG);
			*largeurGauche = largeurDroiteFG + largeurGaucheFG;
		}
	}
}

void EcrireTabs(FILE* f, int tabNum)
{ //

	for (int i = 0; i < tabNum; i++)
		fputs("\t", f);
}

void EcrireEAAHtml(TExprArb a, FILE* f, int tabNum, int largeur, char* classes)
{ //

	if (a != VIDE)
	{
		EcrireTabs(f, tabNum);
		fprintf(f, "<div class=\"arbre %s\" style=\"width: %dpx;\">\n", classes, largeur);

		double largeurDroite, largeurGauche;
		CalculLargeur(a, &largeurDroite, &largeurGauche);

		EcrireTabs(f, tabNum + 1);
		fprintf(f, "<div class=\"noeud\"><span class=\"element\" onclick=\"clicNoeud(this);\">%c</span></div>\n", Racine(a));

		if (Fd(a) != VIDE)
		{
			double x1 = largeur / 2, y1 = 11;
			double x2 = x1 + largeurDroite / 2 + (largeurGauche - largeurDroite) / 2, y2 = 23;
			double tailleLigne = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			double angle = acos((x2 - x1) / tailleLigne);
			EcrireTabs(f, tabNum + 1);
			fprintf(f, "<div class=\"line\" style=\"top: %fpx; left: %fpx; width: %fpx; transform: rotate(%frad);\"></div>\n", 30 + y1, x1, tailleLigne, angle);

			EcrireEAAHtml(Fd(a), f, tabNum + 1, largeurDroite, "right");

			if (Fg(a) != VIDE)
			{ // Un fils gauche n'existera que si un fils droit existe
				double x1 = largeurDroite / 2 + (largeurGauche - largeurDroite) / 2, y1 = 11;
				double x2 = largeur / 2, y2 = -1;
				double tailleLigne = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
				double angle = -acos((x2 - x1) / tailleLigne);
				EcrireTabs(f, tabNum + 1);
				fprintf(f, "<div class=\"line\" style=\"top: %fpx; left: %fpx; width: %fpx; transform: rotate(%frad);\"></div>\n", 30 + y1, x1, tailleLigne, angle);

				EcrireEAAHtml(Fg(a), f, tabNum + 1, largeurGauche, "left");
			}
		}

		EcrireTabs(f, tabNum);
		fprintf(f, "</div>\n");
	}

}


///////////////////////////////////////////////////
//
//  Projet Perso : WEBERT Chris
//
///////////////////////////////////////////////////

double EvaluationArbre(TExprArb E, double Mem[26]) {
	// Evalue l'arbre E avec le tableau de constantes/variables Mem
	// PERSO : WEBERT

	char rac = Racine(E);

	if (EstFeuille(E)) {

		if ((rac - '0' >= 0) && (rac - '9' <= 9))  // La feuille est un chiffre
			return (double)(rac - '0');

		else if (rac == 'P')                       // La feuille est Pi
			return Mem[26];

		else                                       // La feuille est une constante, ou x
			return Mem[rac - 'a'];
	}
	else {

		TExprArb F_g = Fg(E), F_d = Fd(E);

		switch (rac) {

		case '+': return EvaluationArbre(F_g, Mem) + EvaluationArbre(F_d, Mem);
		case '-': {
					  if (NatureNoeud(E) == 'B')
						  return EvaluationArbre(F_g, Mem) - EvaluationArbre(F_d, Mem);
					  else
						  return -EvaluationArbre(F_d, Mem);
		}

		case '*': return EvaluationArbre(F_g, Mem) * EvaluationArbre(F_d, Mem);
		case '/': {
					  double Eval = EvaluationArbre(F_d, Mem);
					  if (Eval == 0.)
						  return NAN;
					  else
						  return EvaluationArbre(F_g, Mem) / EvaluationArbre(F_d, Mem);
		}
		case 'C': return cos(EvaluationArbre(F_d, Mem));
		case 'S': return sin(EvaluationArbre(F_d, Mem));
		case 'E': return exp(EvaluationArbre(F_d, Mem));
		case 'L': {
					  double Eval = EvaluationArbre(F_d, Mem);
					  if (Eval <= 0)
						  return NAN;
					  else
						  return log(Eval);
		}
		case 'K': return pow(EvaluationArbre(F_d, Mem), 2);
		case 'R': {
					  double Eval = EvaluationArbre(F_d, Mem);
					  if (Eval <= 0)
						  return NAN;
					  else
						  return sqrt(Eval);
		}
		default: return 0.;

		}
	}

}

void StringExpression(TExprArb E, char* result) {
	//Renvoie un string contenant l'expression E

	char rac = Racine(E);
	TExprArb F_g = Fg(E), F_d = Fd(E);

	switch (rac) {
	case '+': {
				  char result_g[200], result_d[200];
				  StringExpression(F_g, result_g); StringExpression(F_d, result_d);
				  sprintf(result, "(%s+%s)", result_g, result_d);
				  break;
	}
	case '-': {
				  char result_g[200] = "", result_d[200];
				  if (NatureNoeud(E) == 'B')
					  StringExpression(F_g, result_g);
				  StringExpression(F_d, result_d);
				  sprintf(result, "(%s-%s)", result_g, result_d);
				  break;
	}
	case '*': {
				  char result_g[200], result_d[200];
				  StringExpression(F_g, result_g); StringExpression(F_d, result_d);
				  sprintf(result, "(%s.%s)", result_g, result_d);
				  break;
	}
	case '/': {
				  char result_g[200], result_d[200];
				  StringExpression(F_g, result_g); StringExpression(F_d, result_d);
				  sprintf(result, "(%s/%s)", result_g, result_d);
				  break;
	}
	case 'C': {
				  char result_d[200];
				  StringExpression(F_d, result_d);
				  sprintf(result, "cos(%s)", result_d);
				  break;
	}
	case 'S': {
				  char result_d[200];
				  StringExpression(F_d, result_d);
				  sprintf(result, "sin(%s)", result_d);
				  break;
	}
	case 'E': {
				  char result_d[200];
				  StringExpression(F_d, result_d);
				  sprintf(result, "exp(%s)", result_d);
				  break;
	}
	case 'L': {
				  char result_d[200];
				  StringExpression(F_d, result_d);
				  sprintf(result, "ln(%s)", result_d);
				  break;
	}
	case 'K': {
				  char result_d[200];
				  StringExpression(F_d, result_d);
				  sprintf(result, "%s&sup2;", result_d);
				  break;
	}
	case 'R': {
				  char result_d[200];
				  StringExpression(F_d, result_d);
				  sprintf(result, "	&radic;(%s)", result_d);
				  break;
	}
	case 'P': {
				  sprintf(result, "&pi;");
				  break;
	}
	default: sprintf(result, "%c", rac);
	}


}

void ExporterCourbesHTML(TExprArb E, FILE* FICHIER, double xmin, double xmax, double ymin, double ymax, double Mem[26]) {
	// Exporte l'arbre E dans un fichier sous forme de triplet {x, Expr(x), DérivéeExpr(x)} dans l'intervalle [a;b] divisé n fois.
	// PERSO : WEBERT


	double xi, Ei, Epi;
	int Long_Fenetre = 640,
		Larg_Fenetre = 480,
		n = NbSegments;

	fprintf_s(FICHIER, "\t\t<div style=\"margin: 30px 0 30px calc(50%% - 320px); position: relative;\">\n", Long_Fenetre / 2);
	fprintf_s(FICHIER, "\t\t\t<div id=\"coordonnees\" style=\"width: 130px; height: 60px; padding: 3px 7px; background: white; font-size: 0.8em; position: absolute; border: solid 1px gray; z-index: 5;\">x :<br/>y :<br/>y':</div>\n");
	fprintf_s(FICHIER, "\t\t\t<div style=\"width: %dpx; height: %dpx; overflow: hidden; position: absolute;\">\n\t\t\t\t<div id=\"point1\" style=\"width: 10px; height: 10px; background: #346BA9; border-radius: 50%%; position: absolute;\"></div>\n\t\t\t\t<div id=\"point2\" style=\"width: 10px; height: 10px; background: #49AB73; border-radius: 50%%; position: absolute;\"></div>\n\t\t\t</div>\n", Long_Fenetre + 2, Larg_Fenetre + 2);
	fprintf_s(FICHIER, "\t\t\t<div id=\"xmin\" style=\"width: 200px; text-align: right; float: left; top: %.0lfpx; left: %dpx; position: absolute;\">%.2lf</div>\n", Min(Max(ymax / (ymax - ymin) * Larg_Fenetre - 10, 0), Larg_Fenetre - 10), -210, xmin);
	fprintf_s(FICHIER, "\t\t\t<div id=\"xmax\" style=\"width: 200px; text-align: left; float: left; top: %.0lfpx; left: %dpx; position: absolute;\">%.2lf</div>\n", Min(Max(ymax / (ymax - ymin) * Larg_Fenetre - 10, 0), Larg_Fenetre - 10), Long_Fenetre + 10, xmax);
	fprintf_s(FICHIER, "\t\t\t<div id=\"ymin\" style=\"width: 200px; text-align: center; float: left; top: %dpx; left: %.0lfpx; position: absolute;\">%.2lf</div>\n", Larg_Fenetre + 5, Min(Max(-xmin / (xmax - xmin) * Long_Fenetre - 100, -100), Long_Fenetre), ymin);
	fprintf_s(FICHIER, "\t\t\t<div id=\"ymax\" style=\"width: 200px; text-align: center; float: left; top: %dpx; left: %.0lfpx; position: absolute;\">%.2lf</div>\n", -25, Min(Max(-xmin / (xmax - xmin) * Long_Fenetre - 100, -100), Long_Fenetre), ymax);
	fprintf_s(FICHIER, "\t\t\t<svg id =\"graphe\" style=\"background-color: #F8F8F8; width: %dpx; height: %dpx; border: solid 1px gray; overflow: hidden;\">\n", Long_Fenetre, Larg_Fenetre);
	fprintf_s(FICHIER, "\t\t\t\t<polyline id=\"f01\" points=\"\"></polyline>\n\t\t\t\t<polyline id=\"f02\" points=\"\"></polyline>\n");
	fprintf_s(FICHIER, "\t\t\t\t<polyline points = \"0,%.0lf %d,%.0lf\" style=\"fill-opacity:0; stroke:gray; stroke-width:0.5\"></polyline>\n", ymax / (ymax - ymin) *Larg_Fenetre, Long_Fenetre, ymax / (ymax - ymin) * Larg_Fenetre);
	fprintf_s(FICHIER, "\t\t\t\t<polyline points = \"%.0lf,0 %.0lf,%d\" style=\"fill-opacity:0; stroke:gray; stroke-width:0.5\"></polyline>\n\n", -xmin / (xmax - xmin) * Long_Fenetre, -xmin / (xmax - xmin) * Long_Fenetre, Larg_Fenetre);
	fprintf_s(FICHIER, "\t\t\t\t<polyline class=\"f1\" points = \"");

	bool f_continue = true;

	for (int i = 0; i <= n; i++) {

		xi = xmin + i*(xmax - xmin) / n;
		Mem['x' - 'a'] = xi;
		Ei = EvaluationArbre(E, Mem);

		if (!isnan(Ei)) {
			f_continue = true;
			fprintf_s(FICHIER, "%.2lf,%.2lf ", Long_Fenetre*(-xmin / (xmax - xmin)) + Long_Fenetre / (xmax - xmin) * xi, Larg_Fenetre*(ymax / (ymax - ymin)) - (Larg_Fenetre / (ymax - ymin)) *Ei);
		}
		else
			if (f_continue) {
				f_continue = false;
				fprintf_s(FICHIER, "\"></polyline>\n\t\t\t\t<polyline class=\"f1\" points = \"");
			}
	}

	fprintf_s(FICHIER, "\"></polyline>\n\n");
	fprintf_s(FICHIER, "\t\t\t\t<polyline class=\"f2\" points = \"");
	f_continue = true;

	for (int i = 0; i <= n; i++) {

		xi = xmin + i*(xmax - xmin) / n;
		Mem['x' - 'a'] = xi;
		Epi = EvaluationArbre(DeriveEAA(E), Mem);

		if (!isnan(Epi)) {
			f_continue = true;
			fprintf_s(FICHIER, "%.2lf,%.2lf ", Long_Fenetre*(-xmin / (xmax - xmin)) + Long_Fenetre / (xmax - xmin) * xi, Larg_Fenetre*(ymax / (ymax - ymin)) - (Larg_Fenetre / (ymax - ymin)) *Epi);

		}
		else
			if (f_continue) {
				f_continue = false;
				fprintf_s(FICHIER, "\"></polyline>\n\t\t\t\t<polyline class=\"f2\" points = \"");
			}
	}
	
	fprintf_s(FICHIER, "\"></polyline>\n");
	fprintf_s(FICHIER, "\t\t\t</svg>\n\t\t</div>");

	printf("\n> Ajout des courbes reussie!");

}


/////////////////////////////////////////////////////////
//
//  Projet Perso : COMMUN pour la génération de l'HTML
//
/////////////////////////////////////////////////////////

void GenererHTML(char* nom, TExprArb a, double Mem[26])
{	// Génère un fichier HTML à partir du nom (doit être un nom de fichier valide) et de l'arbre. 

	printf("\n>> Exportation HTML en cours...\n");

	char nomComplet[50];
	strcpy(nomComplet, nom);
	strcat(nomComplet, ".html");

	TExprArb deriveeSimplifiee = SimplifieEAA(DeriveEAA(a));

	char stringExpr[300];
	StringExpression(a, stringExpr);
	char stringExprDerivee[300];
	StringExpression(deriveeSimplifiee, stringExprDerivee);

	FILE* f = fopen(nomComplet, "w");

	fprintf(f, "<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"US-ASCII\" />\n\t<title>%s</title>\n", nom);
	fprintf(f, "\t<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\"/>\n");
	fprintf(f, "\t<style type=\"text/css\">\n\t\tbody{ display: inline-block; min-width: 900px; width: auto; background: #DADADA; color: #343434; font-family: \"Consolas\", monospace; font-size: 20px; margin: 0; padding: 0; } \n\t\th1{ margin: 20px 0; } \n\t\th3{ margin: 0 0 15px 0 } \n\t\tfooter{ background: #131313; color: white; margin-top: 20px; padding: 30px; text-align: center; font-size: 12px; } \n\t\t.noeud{ display: inline-block; width: 100%%; text-align: center; vertical-align:middle; } \n\t\t.element{ display: inline-block; width: 30px; height: 30px; line-height: 30px; cursor: pointer; border: solid rgba(109, 140, 169, 1) 4px; border-radius: 30px; text-align: center; } \n\t\t.racine2 .element{ border-color: rgba(109, 169, 140, 1); } \n\t\t.line{ position: absolute; z-index: -1; background: rgba(109, 140, 169, 0.5); height: 3px; } \n\t\t.racine2 .line{ background-color: rgba(109, 169, 140, 0.5); } \n\t\t.arbre{ display: block; position: relative; text-align: center; margin-top: 10px; transform-origin: top; transform: scaleY(1); transition: all ease 0.2s; } \n\t\t.clear, .racine1, .racine2{ clear: both; } \n\t\t.container { display: inline-block; min-width: calc(100%% - 40px - 2px - 30px); margin: 20px; padding: 25px 15px 0 15px; border: dashed 1px gray; border-radius: 10px; position: relative; } \n\t\t.container h5 { position: absolute; float: left; top: -43px; left: 30px; color: #777777; background: #DADADA; padding: 5px; } \n\t\t.left{ float: left; } \n\t\t.right{ float: right; } \n\t\t.hidden { transform-origin: top; transform: scaleY(0); transition: all ease 0.2s; } \n\t\t.racine1 .line.hidden { background: repeating-linear-gradient(90deg, transparent, transparent 2px, rgba(109, 140, 169, 0.8) 2px, rgba(109, 140, 169, 0.8) 4px); } \n\t\t.racine2 .line.hidden { background: repeating-linear-gradient(90deg, transparent, transparent 2px, rgba(109, 169, 140, 0.8) 2px, rgba(109, 169, 140, 0.8) 4px); } \n\t\t.info{ width: 100%%; margin: 15px 0; background: repeating-linear-gradient(-45deg, #EEEEEE, #EEEEEE 20px, #F3F3F3 20px, #F3F3F3 40px); border-radius: 15px; color: #444444; font-size: 0.8em; display: inline-block; }\n\t\t.info i{ margin: 0 20px; vertical-align: middle; }\n\t\t.info p{ max-width: 90%%; display: inline-block; vertical-align: middle; } \n\t\t.material-icons.md-30{ font-size: 30px; } \n\t\t#f01, #f02 {fill-opacity:0; stroke:rgba(0,0,0,0);}\n\t\t.f1 {fill-opacity:0; stroke:#346BA9; stroke-width:1.5;}\n\t\t.f2 {fill-opacity:0; stroke:#49AB73; stroke-width:1.5; stroke-opacity: 0.8; stroke-dasharray: 3,2;} \n\t</style>\n");
	fprintf(f, "\t<script type = \"text/javascript\">\n\t\tfunction Charge() {\n\t\t\n\t\t\tvar tabpoly1 = document.getElementsByClassName('f1');\n\t\t\tvar tabpoly2 = document.getElementsByClassName('f2');\n\t\t\t\n\t\t\tvar lines1 = document.getElementById('f01').points;\n\t\t\tvar lines2 = document.getElementById('f02').points;\n\t\t\t\n\t\t\tfor(var w = 0; w < tabpoly1.length; w++) {\n\t\t\t\tfor (var v = 0; v < tabpoly1[w].points.numberOfItems; v++) {\n\t\t\t\t\tlines1.appendItem(tabpoly1[w].points.getItem(v));\n\t\t\t\t}\n\t\t\t}\n\t\t\tfor(var w = 0; w < tabpoly2.length; w++) {\n\t\t\t\tfor (var v = 0; v < tabpoly2[w].points.numberOfItems; v++) {\n\t\t\t\t\tlines2.appendItem(tabpoly2[w].points.getItem(v));\n\t\t\t\t}\n\t\t\t}\n\t\t}\n\t\tfunction MouseMove(event)\n\t\t{\n\t\t\tvar dot, eventDoc, doc, body, pageX, pageY, xmin, xmax, ymin, ymax, xpos, y1pos, y2pos; \n\t\t\tvar xdiv = document.getElementById(\"graphe\").getBoundingClientRect();\n\t\t\tvar lines1 = document.getElementById('f01').points;\n\t\t\tvar lines2 = document.getElementById('f02').points;\n\t\t\n\t\t\txmin = parseFloat(document.getElementById(\"xmin\").innerHTML);\n\t\t\txmax = parseFloat(document.getElementById(\"xmax\").innerHTML);\n\t\t\tymin = parseFloat(document.getElementById(\"ymin\").innerHTML);\n\t\t\tymax = parseFloat(document.getElementById(\"ymax\").innerHTML);\n\t\t\tvar xEcran = Math.max(Math.min((event.pageX - xdiv.left), xdiv.width-2), 0);\n\t\t\t\n\t\t\tevent = event || window.event; \n\t\t\t\n\t\t\tif (event.pageX == null && event.clientX != null) {\n\t\t\t\teventDoc = (event.target && event.target.ownerDocument) || document;\n\t\t\t\tdoc = eventDoc.documentElement;\n\t\t\t\tbody = eventDoc.body;\n\t\t\t\t\n\t\t\t\tevent.pageX = event.clientX +\n\t\t\t\t\t(doc && doc.scrollLeft || body && body.scrollLeft || 0) -\n\t\t\t\t\t(doc && doc.clientLeft || body && body.clientLeft || 0);\n\t\t\t}\n\t\t\t\n\t\t\tvar i = ((xEcran * %d / %d).toFixed(0) * %lf).toFixed(8);\n\t\t\tvar PointNul = { 'x': -1, 'y': -1 };\n\t\t\t\n\t\t\tvar j1 = 0;\n\t\t\tvar fin = false, \n\t\t\t\ttrouve1 = false;\n\t\t\twhile (!fin && !trouve1) {\n\t\t\t\tif (Math.abs(i - lines1.getItem(j1).x) < 0.001)\n\t\t\t\t\ttrouve1 = true;\n\t\t\t\telse if (j1 < lines1.numberOfItems - 1)\n\t\t\t\t\tj1++;\n\t\t\t\telse \n\t\t\t\t\tfin = true;\n\t\t\t}\n\t\t\tvar j2 = 0;\n\t\t\tvar trouve2 = false;\n\t\t\tfin = false;\n\t\t\twhile (!fin && !trouve2) {\n\t\t\t\tif (Math.abs(i - lines2.getItem(j2).x) < 0.001)\n\t\t\t\t\ttrouve2 = true;\n\t\t\t\telse if (j2 < lines2.numberOfItems - 1)\n\t\t\t\t\tj2++;\n\t\t\t\telse \n\t\t\t\t\tfin = true;\n\t\t\t}\n\t\t\t\n\t\t\tif (trouve1)\n\t\t\t\tPointPrec1 = lines1.getItem(j1);\n\t\t\telse\n\t\t\t\tPointPrec1 = PointNul;\n\t\t\tif (trouve2)\n\t\t\t\tPointPrec2 = lines2.getItem(j2);\n\t\t\telse\n\t\t\t\tPointPrec2 = PointNul;\n\t\t\t\n\t\t\txpos = (xEcran * (xmax - xmin) / (xdiv.width - 2) + xmin).toFixed(4);\n\t\t\ty1pos = (ymax - (PointPrec1.y * (ymax - ymin) / (xdiv.height - 2))).toFixed(4);\n\t\t\ty2pos = (ymax - (PointPrec2.y * (ymax - ymin) / (xdiv.height - 2))).toFixed(4);\n\t\t\t\n\t\t\tif (PointPrec1 == PointNul) y1pos = \"IND&#201;FINIE\";\n\t\t\tif (PointPrec2 == PointNul) y2pos = \"IND&#201;FINIE\";\n\t\t\t\n\t\t\tdocument.getElementById(\"point1\").style.top = (PointPrec1.y - 5) +\"px\";\n\t\t\tdocument.getElementById(\"point1\").style.left = (PointPrec1.x - 5) + \"px\";\n\t\t\tdocument.getElementById(\"point2\").style.top = (PointPrec2.y - 5) +\"px\";\n\t\t\tdocument.getElementById(\"point2\").style.left = (PointPrec2.x - 5) + \"px\";\n\t\t\t\n\t\t\tdocument.getElementById(\"coordonnees\").innerHTML = \"x : \" + xpos + \"</br><font color=#346BA9>y  : \" + y1pos + \"</font></br><font color=#49AB73>y': \" + y2pos + \"</font>\";\n\t\t}\n\n\t\tfunction clicNoeud(element)\n\t\t{\n\t\t\tvar arbreParent = element.parentElement.parentElement;\n\t\t\t\n\t\t\tif (arbreParent.classList.contains(\"reduced\"))\n\t\t\t{\n\t\t\t\tfor(var i = 0; i < arbreParent.childNodes.length; i++)\n\t\t\t\t{\n\t\t\t\t\tvar child = arbreParent.childNodes[i];\n\t\t\t\t\tif (child.nodeType != Node.TEXT_NODE)\n\t\t\t\t\t{\n\t\t\t\t\t\tif (child.className != \"noeud\")\n\t\t\t\t\t\t\tchild.classList.remove(\"hidden\");\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\tarbreParent.classList.remove(\"reduced\");\n\t\t\t}\n\t\t\telse\n\t\t\t{\n\t\t\t\tfor(var i = 0; i < arbreParent.childNodes.length; i++)\n\t\t\t\t{\n\t\t\t\t\tvar child = arbreParent.childNodes[i];\n\t\t\t\t\tif (child.nodeType != Node.TEXT_NODE)\n\t\t\t\t\t{\n\t\t\t\t\t\tif (child.className != \"noeud\")\n\t\t\t\t\t\t\tchild.classList.add(\"hidden\");\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\tarbreParent.classList.add(\"reduced\");\n\t\t\t}\n\t\t}\n\t</script>\n", NbSegments, 640, 640./NbSegments);
	fprintf(f, "</head>\n<body onmousemove=\"MouseMove(event)\"  onload=\"Charge()\">\n");

	fprintf(f, "\t<center>\n\t\t<h1>%s :</h1>\n\t\t<h3>E(x) = %s</h3>\n", nom, stringExpr);
	fprintf(f, "\t\t<h3>E'(x) = %s</h3>\n\t</center>\n", stringExprDerivee);

	fprintf(f, "\t<div class=\"container\">\n\t\t<h5>HOCHLANDER Matthieu : &#171; Afficher l'arbre de <span style=\"border: solid 2px #6D8CA9; border-radius: 5px; padding: 2px;\">E(x)</span> et <span style=\"border: solid 2px #6DA98C; border-radius: 5px; padding: 2px;\">E'(x)</span> en HTML &#187;</h5>\n");

	fprintf(f, "\t\t<div class=\"clear\">Expression originale : </div>\n");

	double largeurDroite, largeurGauche;
	CalculLargeur(a, &largeurDroite, &largeurGauche);
	EcrireEAAHtml(a, f, 2, largeurDroite + largeurGauche, "racine1");

	fprintf(f, "\t\t<div class=\"clear\">Expression d&#233;riv&#233;e et simplifi&#233;e : </div>\n");

	CalculLargeur(deriveeSimplifiee, &largeurDroite, &largeurGauche);
	EcrireEAAHtml(deriveeSimplifiee, f, 2, largeurDroite + largeurGauche, "racine2");
	printf("\n> Ajout des arbres reussie!");

	fputs("\t\t<div class=clear></div>\n\t\t<div class=\"info\">\n\t\t\t<i class=\"material-icons md-30\">info_outline</i>\n\t\t\t<p>Affiche les arbres de l'expression E et de sa d&#233;riv&#233;e E'.<br/>Vous pouvez r&#233;tracter ou &#233;tendre un sous-arbre en cliquant sur son noeud, si celui-ci a au moins un fils.</p>\n\t\t</div>\n\t</div>\n\n", f);

	fprintf(f, "\t<div class=\"container\">\n\t\t<h5>WEBERT Chris : &#171; Afficher les courbes de <span style=\"border-bottom: solid 2px #346BA9; padding: 2px;\">E(x)</span> et <span style=\"border-bottom: dotted 2px #49AB73; padding: 2px;\">E'(x)</span> en HTML &#187;</h5>\n");

	ExporterCourbesHTML(a, f, -10, 10, -7.5, 7.5, Mem); // Paramètres : Arbre, fichier, xmin, xmax, ymin, ymax, tableau des constantes

	fputs("\n\t\t<div class=\"info\">\n\t\t\t<i class=\"material-icons md-30\">info_outline</i>\n\t\t\t<p style=\"display: inline-block; vertical-align: middle;\">Affiche les courbes de l'expression E en bleu et de sa d&#233;riv&#233;e E' en vert.<br/>Vous pouvez &#233;valuer les expressions en d&#233;pla&#231;ant le curseur sur le graphe : les valeurs de l'abscisse et des ordonn&#233;es s'affichent dans le cadre en haut &#224; gauche.</p>\n\t\t</div>\n\t</div>\n\n", f);

	fputs("\t<footer class=\"clear\">HOCHLANDER Matthieu - WEBERT Chris</footer>\n", f);

	fputs("</body>\n</html>", f);
	fclose(f);

	printf("\n\n>> Exportation HTML terminee!\n");

}


int main() {

	double Mem[27] = { 2.5, 2.0, -5.3 };    // a = 2.5, b = 2, c = -5.3, le reste est nul
	Mem[26] = M_PI;                         // P = pi (P est placé à la fin du tableau)
	int choix;
	bool choixOK = false;
	TExprArb B = VIDE;

	printf("Choisissez un arbre :\n\n1: ln(x)\n2: sqrt(x^2 - 3)\n3: x.cos(x)\n4: 2.cos^2(x)\n5: x^2.cos(1/x)\n6: ln(x + sqrt(1 + x^2))\n7: sin(a.x + pi/4).exp(-x^2/2)\n\n");

	do { 

		printf("Choix ? ");  scanf("%d", &choix);
		choixOK = true;

		switch (choix) {
		case 1: 
			B = Cons2('L', VIDE, ConsF('x'));
			break;
		case 2:
			B = Cons2('R', VIDE, Cons2('-', Cons2('K', VIDE, ConsF('x')), ConsF('3')));
			break;
		case 3:
			B = Cons2('*', ConsF('x'), Cons2('C', VIDE, ConsF('x')));
			break;
		case 4:
			B = Cons2('+', Cons2('K', VIDE, Cons2('C', VIDE, ConsF('x'))), Cons2('K', VIDE, Cons2('C', VIDE, ConsF('x'))));
			break;
		case 5:
			B = Cons2('*', Cons2('K', VIDE, ConsF('x')), Cons2('C', VIDE, Cons2('/', ConsF('1'), ConsF('x'))));
			break;
		case 6:
			B = Cons2('L', VIDE, Cons2('+', ConsF('x'), Cons2('R', VIDE, Cons2('+', ConsF('1'), Cons2('K', VIDE, ConsF('x'))))));
			break;
		case 7:
			B = Cons2('*', Cons2('S', VIDE, Cons2('+', Cons2('*', ConsF('a'), ConsF('x')), Cons2('/', ConsF('P'), ConsF('4')))), Cons2('E', VIDE, Cons2('-', VIDE, Cons2('/', Cons2('K', VIDE, ConsF('x')), ConsF('2')))));
			break;
		default: 
			choixOK = false;
			printf("/!\\ Choix incorrect. Recommencez.\n\n");
		}

	} while (choixOK == false);
	

	printf("\nExpression simplifiee de E(x) : ");
	B = SimplifieEAA(B);
	AfficherEAALin(B);
	printf("\n\n\n");
	AfficherEAAArb(B, 1);

	printf("\n--------------------------------\nExpression simplifiee de E'(x) : ");
	TExprArb DB = SimplifieEAA(DeriveEAA(B));
	AfficherEAALin(DB);
	printf("\n\n\n");
	AfficherEAAArb(DB, 1);

	char NomFichier[256] = "Exemple";

	GenererHTML(NomFichier, B, Mem);

	ShellExecuteA(NULL, "open", strcat(NomFichier,".html"), NULL, NULL, SW_SHOWMAXIMIZED);

	//system("pause");
	system("cls");
	return 0;
}