#include <stdlib.h>
#include <stdio.h>
#include "couleurs.h"
#define N 17

void recup_nom_fichier(char *nom_fic) {
    /*
     * Permet de récupérer le nom du fichier demandé. Nécessite un tableau de caractères et ne renvoie rien (car tableau donné en pointeur)
     */

	printf("Entrez le nom du fichier : ");
	scanf("%s", nom_fic);
}

void initialiser_matrice(int matrice[N+2][N+2]) {
     /*
     * Initialise une matrice en la remplissant de zéro. Nécessite la dite matrice et ne renvoie rien
     */

	int i, j;

	for(i = 0; i < N+2; i++) {
		for(j = 0; j < N+2; j++) {
			matrice[i][j] = 0;
		}
	}
}

void afficher_matrice(int matrice[N+2][N+2], int type) {
    /*
     * Affiche la matrice demandée, en fonction de son type (matrice de cellules ou de voisins), avec des couleurs. Nécessite la matrice, son tyoe, et ne renvoie rien
     */

	int i, j;

	if(type == 1) { //Cellules
		for(i = 0; i < N+2; i++) {
			for(j = 0; j < N+2; j++) {
				if(matrice[i][j]) {
					couleur("34");
				} else {
					couleur("37");
				}
				printf("%i ", matrice[i][j]);
			}
			printf("\n");
		}
	}

	if(type == 2) { //Voisins
		for(i = 0; i < N+2; i++) {
			for(j = 0; j < N+2; j++) {
				switch(matrice[i][j]) {
					case 0 : couleur("37"); break;
					case 2 :
					case 3 : couleur("32"); break;
					default : couleur("31"); break;
				}
				printf("%i ", matrice[i][j]);
			}
			printf("\n");
		}
	}

	couleur("37");

	printf("\n");
	printf("\n");
}

void calc_voisins(int matrice_cell[N+2][N+2], int matrice_voisins[N+2][N+2]) {
     /*
     * Permet de calculer les voisins de chaque cellule. Nécessite la matrice de cellules, celle des voisins, et ne renvoie rien
     */

	int i, j;

	for(i = 1; i < N+1; i++) {
		for(j = 1; j < N+1; j++) { // Pour chaque voisins trouvé (case voisine == 1) on incrémente le nombre de voisins
			matrice_voisins[i][j] = matrice_cell[i-1][j-1] + matrice_cell[i-1][j] + matrice_cell[i-1][j+1] + matrice_cell[i][j-1] + matrice_cell[i][j+1] + matrice_cell[i+1][j-1] + matrice_cell[i+1][j] + matrice_cell[i+1][j+1];
		}
	}
}

void calc_gen_suivante(int matrice_cell[N+2][N+2], int matrice_voisins[N+2][N+2]) {
     /*
     * Permet de calculer la génération suivante, à partir de la génération actuelle. Nécessite la matrice de cellules et celles de voisins, et modifie directement la matrice de cellules.
     */

	int i,j;

	for(i = 1; i < N+1; i++) {
		for(j = 1; j < N+1; j++) {
			if(matrice_voisins[i][j] == 2) {
			} else if(matrice_voisins[i][j] == 3) {
				matrice_cell[i][j] = 1;
			} else {
				matrice_cell[i][j] = 0;
			}
		}
	}
}

void game_of_life(int tableau_cell[N+2][N+2], int tableau_voisins[N+2][N+2], int nb_generations) {
    /*
     * Fait les différentes taches du calcul des nb_generations suivantes. Nécessite les deux matrices et le nombre de généraitons
     */

	int i;

	for(i = 0; i < nb_generations; i++) {
		calc_voisins(tableau_cell, tableau_voisins);
		calc_gen_suivante(tableau_cell, tableau_voisins);
		afficher_matrice(tableau_cell, 1);
	}
}

void main() {
	int pos_cel_x;
	int pos_cel_y;
	int tableau_cell[N+2][N+2];
	int tableau_voisins[N+2][N+2];
	int nb_generations;
	char nom_fichier[20];

	recup_nom_fichier(nom_fichier);

	FILE *fic_placement = fopen(nom_fichier, "r");

	initialiser_matrice(tableau_cell);

	while(!feof(fic_placement)) {
		fscanf(fic_placement, "%i", &pos_cel_x);
		fscanf(fic_placement, "%i", &pos_cel_y);

		tableau_cell[pos_cel_x][pos_cel_y] = 1;
	}

	afficher_matrice(tableau_cell, 1);

	printf("Nombre de generations : ");
	scanf("%i", &nb_generations);

	game_of_life(tableau_cell, tableau_voisins, nb_generations);

	fclose(fic_placement);
}
