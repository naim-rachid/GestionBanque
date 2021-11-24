#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // pour utiliser le type bool
#include <math.h>
#define SIZE 100
static int N = 0;
// Fonction de Menu Principal qui permet de choisir l'opération à effectuer
int menu(){
	int c;
	printf("\n------------------------------------------------------------------------------------------------");
	printf("\n---------------------- Bienvenu dans une application Gestion Bancaire --------------------------\n");
	printf("------------------------------------------------------------------------------------------------\n");
	printf("-------- 1: Introduire un compte bancaire (CIN, Nom et Prenom, Montant) ------------------------\n");
	printf("-------- 2: Introduire plusieurs comptes bancaires (CIN, Nom et Prenom, Montant) ---------------\n");
	printf("-------- 3: Operations : ( Retrait | Depot ) ---------------------------------------------------\n");
	printf("-------- 4: Affichage --------------------------------------------------------------------------\n");
	printf("-------- 5: Fidelisation (Ajout 1.3%c aux comptes ayant les 3 premiers montants superieurs)------\n", '%');
	printf("-------- 0: Quitter l'application --------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------\n");
	printf("Votre operation : ");
	scanf("%d", &c);
//	printf("Operation saisis est = %d \n", c);
	printf("------------------------------------------------------------------------------------------------\n");
	
	return c;
}
// Fonction de Menu simple d'opération (Retrait | Depot)
int menuOp() {
	int cOp;
	printf("\n\t----------- Le type d'operation ----------\n");
	printf("\t------------------------------------------\n");
	printf("\t-------- 1: Retrait ----------------------\n");
	printf("\t-------- 2: Depot ------------------------\n");
	printf("\t-------- 0: Retour au Menu Principal ------\n");
	printf("\t------------------------------------------\n");
	printf("\t-->  ");
	scanf("%d", &cOp);
//	printf("choix d'operation : %d \n", cOp);
	printf("\t------------------------------------------\n");
	
	return cOp;
}
// Fonction de Menu simple de type d'affichage
int menuAff() {
	int cAff;
	printf("\n\t--------------------------------------- Le type d'affichage ------------------------------------------\n");
	printf("\t------------------------------------------------------------------------------------------------------\n");
	printf("\t--- 1: Par Ordre Ascendant \n");
	printf("\t--- 2: Par Ordre Descendant \n");
	printf("\t--- 3: Par Ordre Ascendant (les comptes bancaires ayant un montant superieur a un chiffre introduit) \n");
	printf("\t--- 4: Par Ordre Descendant (les comptes bancaires ayant un montant superieur a un chiffre introduit) \n");
	printf("\t--- 5: Par recherche par CIN \n");
	printf("\t--- 0: Retour au Menu Principal \n");
	printf("\t------------------------------------------------------------------------------------------------------\n");
	printf("\t-->  ");
	scanf("%d", &cAff);
//	printf("Type d'operation : %d \n", cAff);
	printf("\t-------------------------------------------------------\n");
	
	return cAff;
}
// Procédure d'insérer un compte bancaire
void insererCompte(char tableComptes[][4][50]) {
	char chaineSaisie[50];
	printf("Entrez Vos infos (CIN puis Nom puis Prenom puis montant) : \n");
	int positionCinCompteRecherche;
	N += 1; // N = 3 + 1; pour ajouter un seul compte
	int position = N - 1; // position = 3;
	for(int j = 0; j < 4; j++) {
		switch (j) {
			case 0: printf("- CIN : ");
					break;
			case 1: printf("- Nom : ");
					break;
			case 2: printf("- Prenom : "); 
					break;
			case 3: printf("- Montant : "); 
					break;
		}
		scanf("%s", &chaineSaisie);
		positionCinCompteRecherche = rechercherCompte(tableComptes, chaineSaisie);
		if (positionCinCompteRecherche == 1) { // cin est déjà existé
			printf("\t --> Le compte dont le CIN %s est deja existe !\n", chaineSaisie);
			N -= 1;
			break;
		} else {
			strcpy(tableComptes[position][j], chaineSaisie);// [3][0];
		}
	}		
}
// procédure d'insérer plusieurs comptes bancaires
void insererListComptes(char tableComptes[][4][50], int nbrComptesInsere) {
	// Total des lignes remplies
	N = N + nbrComptesInsere;// N = 3 + 2 = 5;
	int position = N - nbrComptesInsere; // position = 5 - 2 = 3;
	printf("Entrez Vos infos (CIN puis Nom puis Prenom puis montant) : \n");
	for (int i = position, j = 1; i < N; i++, j++) {
		printf("------> Compte %d : \n", j);
//		printf("Entrez Vos infos (CIN puis Nom puis Prenom puis montant) : \n");
		for(int j = 0; j < 4; j++) {
			switch (j) {
				case 0: printf("- CIN : ");
						break;
				case 1: printf("- Nom : ");
						break;
				case 2: printf("- Prenom : "); 
						break;
				case 3: printf("- Montant : "); 
						break;
			}
			scanf("%s", tableComptes[i][j]);
		}
		if (i != (N - 1)) {
			printf("\n");
		}
	}
}
// Fonction de recherche d'un compte par son CIN
int rechercherCompte(char tableComptes[][4][50], char cin[50]) {
	int indice = -1;
	bool existe = false;
	
	for (int i = 0; i < N && !existe; i++) {
		if (strcmp(tableComptes[i][0], cin) == 0) {
			existe = true;
			indice = i;
		} 
	}
	if (existe) { // existe == true
		indice = indice;
//		printf("\n\t --> Votre compte bancaire existe !\t => \t");
	} else {
//		printf("\t --> Le compte dont le CIN %s n'existe pas", cin);
	}
	return indice;
}
// Procédure de Retrait montant d'un compte quelconque
void retrait(char tableComptes[][4][50], char cin[50]) {
	int positionCompteRecherche = rechercherCompte(tableComptes, cin);
//	printf("-- 1\n");
	if (positionCompteRecherche != -1) { // cin est existe
//		printf("-- 2\n");
		afficherCompte(tableComptes, cin);
		/*------ Retrait montant d'un compte quelconque -------- */
		// fonction qui convertit le chaine de caractères en un float
//		float montantC = strtof(tableComptes[positionCompteRecherche][3], NULL);
		float montantC = strtod(tableComptes[positionCompteRecherche][3], NULL);
		
//		printf("\n montantC avant = %f", montantC);
		float montantRetrait;
		printf("\n --- Entrez le montant que vous voulez retirer : ");
		scanf("%f", &montantRetrait);
		if (montantRetrait <= montantC) {
			montantC -= montantRetrait;
			int nbrChiffres = log10(montantC) + 1;
			char montantNew[50];
			// fonction qui convertit float en une chaine de caractères
			gcvt(montantC, (nbrChiffres + 3), montantNew);
			printf("Le montant de votre compte devient egale a : %s\n", montantNew);
			// copier montant obtenu dans une case memoire specifiee de tableComptes
			strcpy(tableComptes[positionCompteRecherche][3], montantNew);
		} else {
			printf("\t²²²² Desole !!! Votre solde ne suffit pas ²²²²\n");
		}
//		printf("tableComptes[%d][3] devient egale a : %s\n", positionCompteRecherche, tableComptes[positionCompteRecherche][3]);
	} else {
		printf("\t --> Le compte dont le CIN %s n'existe pas\n", cin);
	}
}
// Procédure de Dépôt un montant dans un compte quelconque
void depot(char tableComptes[][4][50], char cin[50]) {
	int positionCompteRecherche = rechercherCompte(tableComptes, cin);
	if (positionCompteRecherche != -1) { // cin est existe
//		printf("-- 2\n");
		afficherCompte(tableComptes, cin);
		/*------ Dépôt un montant dans un compte quelconque -------- */
		// fonction qui convertit le chaine de caractères en un float
//		float montantC = strtof(tableComptes[positionCompteRecherche][3], NULL);
		float montantC = strtod(tableComptes[positionCompteRecherche][3], NULL);

//		printf("\n montantC avant = %f", montantC);
		float montantDepot;
		printf("\n --- Entrez le montant que vous voulez deposer : ");
		scanf("%f", &montantDepot);
		// Ajouter le montant à déposer à le compte concerné
		montantC += montantDepot;
		int nbrChiffres = log10(montantC) + 1;
//		printf("\n montantC apres = %f", montantC);
		char montantNew[50];
		// fonction qui convertit float en une chaine de caractères
		gcvt(montantC, (nbrChiffres + 3), montantNew);
		printf("Le montant de votre compte devient egale a : %s\n", montantNew);
		// copier montant obtenu dans une case memoire specifiee de tableComptes
		strcpy(tableComptes[positionCompteRecherche][3], montantNew);
//		printf("tableComptes[%d][3] devient egale a : %s\n", positionCompteRecherche, tableComptes[positionCompteRecherche][3]);
	} else {
		printf("\t --> Le compte dont le CIN %s n'existe pas\n", cin);
	}
}
// procedure d'Affichage un compte bancaire spécifié
void afficherCompte(char tableComptes[][4][50], char cin[50]){
//	printf("--------- Affichage un Compte : \n");
	int positionCompteRecherche = rechercherCompte(tableComptes, cin);
//	printf("-- 3\n");
	if (positionCompteRecherche != -1) {
		
		printf("\n\t --> Votre compte bancaire existe !\t => \t");
		for (int j = 0; j < 4; j++) {
			printf("%s | ", tableComptes[positionCompteRecherche][j]);
		}
		printf("\n");
	} else {
		printf("\n\t --> Le compte dont le CIN %s n'existe pas !!!\n", cin);
	}
}
// Procédure d'Affichage des comptes bancaires
void afficherComptes(char tableComptes[][4][50]) {
//	printf("tableComptes[0][1] : %s\n", tableComptes[0][1]);
	printf("--------- Affichage des Comptes : \n");
	for (int i = 0; i < N; i++) {
		if (tableComptes[i] != NULL) {
			for (int j = 0; j < 4; j++) {
				printf("%s | ", tableComptes[i][j]);
			}
		}
		printf("\n");
	}	
}
// fonction qui retourne un tableau des comptes triés par Ascendant ou par Descendant
//char (*triComptes(char tableComptes[][4][50], int typeTri))[SIZE][4][50] {
char* triComptes(char tableComptes[][4][50], int typeTri) {
	int minOuMax;
	for (int i = 0; i < N - 1; i++) {
		minOuMax = i; // minOuMax = 0;  |  
		for (int j = i + 1 ; j < N; j++) { // j = 1;  |  j = 2;  
			// fonction qui convertit le chaine de caractères en un float
			float montantC1 = strtof(tableComptes[minOuMax][3], NULL);
			float montantC2 = strtof(tableComptes[j][3], NULL);
			if (typeTri == 1 || typeTri == 3) { // Tri Ascendant
				/* Comparer le montant de chaque compte avec celui de suivant */
				if (montantC1 > montantC2) {
					minOuMax = j; // minOuMax = 1;  ||  minOuMax = 1;
				}
			} else if (typeTri == 2 || typeTri == 4) { // Tri Descendant
				if (montantC1 < montantC2) {
					minOuMax = j; // minOuMax = 1;  ||  minOuMax = 1;
				}
			}
			
		}
		if (i != minOuMax) { // i = 0; and minOuMax = 1;
			for (int j = 0; j < 4; j++) { // j = 0; | j = 1; |
				char temp[50];
				strcpy(temp, tableComptes[i][j]);			   // temp = [0][0]   | temp = [0][1]   |
				strcpy(tableComptes[i][j], tableComptes[minOuMax][j]);  // [0][0] = [1][0]  | [0][1] = [1][1] |
				strcpy(tableComptes[minOuMax][j], temp);				 // [1][0] = temp     | [1][1] = temp   |
			}
		}
	}
//	printf("--> Fin de tri | tableComptes[0][1] = %s \n", tableComptes[0][1]);
	return tableComptes;
}
// fonction qui retourne par Ascendant ou par Descendant un tableau des comptes triés ayant un montant supérieur à un chiffre donné
void affComptesParMontantSuperieur(char tableComptesTrie[][4][50], float chiffre) {
//	printf("=> tableComptes[0][1] = %s\n", tableComptesTrie[0][1]);
	for (int i = 0; i < N; i++) {
		// fonction qui convertit le chaine de caractères en un float
		float montantC = strtof(tableComptesTrie[i][3], NULL);
		if (montantC > chiffre) {
			printf("\t=> ");
			for (int j = 0; j < 4; j++) {
				printf("%s | ", tableComptesTrie[i][j]);
			}
		}
		printf("\n");
	}	
}
// Fonction fidélise les 3 premiers Comptes par ajouter 1.3% à leur montant
void afficherComptesFidelises(char comptesTriesDescendant[][4][50]) {
	for (int i = 0; i < 3; i++) {
		float montantC = strtod(comptesTriesDescendant[i][3], NULL);
//		printf("\n montantC avant = %f", montantC);
		montantC += montantC * (1.3 / 100);
//		printf("\n montantC apres = %f", montantC);
		int nbrChiffres = log10(montantC) + 1;
//		printf("\n nbrChiffres = %d", nbrChiffres);
		// fonction qui convertit float en une chaine de caractères
		gcvt(montantC, (nbrChiffres + 3), comptesTriesDescendant[i][3]);
		for (int j = 0; j < 4; j++) {
			printf("%s | ", comptesTriesDescendant[i][j]);
		}
		printf("\n");
	}
	
//	printf("%s | ", comptes3Fideliser[0][3]);
//	printf("%s | ", comptes3Fideliser[1][3]);
//	printf("%s | ", comptes3Fideliser[2][3]);
//	printf("%s | ", comptes3Fideliser[3]);
//	free(comptes3Fideliser[3][0]);
	
	return comptesTriesDescendant;
}
// Main de Programme
int main(int argc, char *argv[]) {
//	printf("%d \n", menu());
	
	char tableComptes[SIZE][4][50] = { {"KY111", "KUDU", "Yussaku", "700.50"}, {"HH771", "NAIM", "Rachid", "250.556"}, {"AA333", "AKAI", "Chouitchi", "1000.50"} };
	N = 3;
	int choix;
	START:
	do {
		choix = menu();
		switch (choix) {
			case 1: printf("-------- 1: Introduire un compte bancaire --------\n\n");
					insererCompte(tableComptes);
					break;
			case 2: printf("-------- 2: Introduire plusieurs comptes bancaires --------\n");
					printf("Cmbien de compte voulez-vous introduire : ");
					int nbrComptesInsere;
					scanf("%d", &nbrComptesInsere);
					insererListComptes(tableComptes, nbrComptesInsere);
					break;
			CASE_3:
			case 3: printf("\n---------- 3: Operations  ------------\n");
					int chMOp;
					do {
						int chMOp = menuOp();
						char cin[50];
						switch (chMOp) {
							case 1: printf("--- 1- Retrait ----------------\n");
									printf("--> Entrez votre CIN : ");
									scanf("%s", &cin);
									// L'appel de la fonction retrait
									retrait(tableComptes, cin);
									goto CASE_3;
							case 2: printf("--- 2- Depot ------------------\n");
									printf("--> Entrez votre CIN : ");
									scanf("%s", &cin);
									// L'appel de la fonction retrait
									depot(tableComptes, cin);
									goto CASE_3;
							case 0: goto START;
						}
					} while (chMOp != 0);
					break;
			CASE_4:
			case 4: printf("\n-------- 4: Affichage --------");
					int chMAff;
					do {
						int chMAff = menuAff();
						int typeTri;
						float chiffre;
						char cin[50];
						switch (chMAff) {
							case 1: printf("\n--- 1- Par Ordre Ascendant ----------------\n\n");
									typeTri = 1;
									char* comptesAscendant = triComptes(tableComptes, typeTri);
									afficherComptes(comptesAscendant);
									goto CASE_4;
							case 2: printf("\n--- 2- Par Ordre Descendant ----------------\n\n");
									typeTri = 2;
									char* comptesDescendant = triComptes(tableComptes, typeTri);
									afficherComptes(comptesDescendant);
									goto CASE_4;
							case 3: printf("\n--- 3- Par Ordre Ascendant (les comptes bancaires ayant un montant superieur a un chiffre introduit) \n\n");
									typeTri = 3;
									// demander de saisir le chiffre pour le filtrage
									printf("--> Introduit le chiffre : ");
									scanf("%f", &chiffre);
									char *triercomptesAsc = triComptes(tableComptes, typeTri);
									affComptesParMontantSuperieur(triercomptesAsc, chiffre);
									goto CASE_4;							
							case 4: printf("\n--- 4- Par Ordre Descendant (les comptes bancaires ayant un montant superieur a un chiffre introduit) \n\n");
									typeTri = 4;
									// demander de saisir le chiffre pour le filtrage 
									printf("--> Introduit le chiffre : ");
									scanf("%f", &chiffre);
									char *triercomptesDesc = triComptes(tableComptes, typeTri);
									affComptesParMontantSuperieur(triercomptesDesc, chiffre);
									goto CASE_4;
							case 5: printf("\n--- 5- Recherche par CIN \n\n");
									printf("--> Entrez votre CIN : ");
									scanf("%s", &cin);
									afficherCompte(tableComptes, cin);
									goto CASE_4;
									break;
							case 0: goto START;
						}
					} while (chMAff != 0);
					break;
			case 5: printf("\n-------- 5: Fidelisation --------\n\n");
					int typeTri = 2;
					char *comptesTriesDescendant = triComptes(tableComptes, typeTri);
//					printf("-- Aff tri Desc :\n");
					afficherComptesFidelises(comptesTriesDescendant);
					break;
			case 0: printf("-------- 0: Vous avez quitte l'application --------\n");
					break;
			default:
					printf("------- Veulliez choisir une operation valide ! -------\n");
		}
	} while (choix != 0);
	
	
	return 0;
}
