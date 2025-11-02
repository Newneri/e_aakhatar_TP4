/*!
 * \file main.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Programme principal de gestion des étudiants et leurs notes
 * 
 * Ce fichier contient la fonction main qui charge les données depuis un fichier,
 * affiche les informations des étudiants avec leurs moyennes, et libère la mémoire.
 */

#include "read.h"
#include "init.h"
#include "structures.h"
#include "saveData.h"
#include "binary.h"
#include "show.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \fn int main(int argc, char** argv)
 * \brief Fonction principale du programme
 * \param argc Nombre d'arguments de la ligne de commande
 * \param argv Tableau des arguments de la ligne de commande
 * \return 0 si succès, 1 en cas d'erreur
 * 
 * Cette fonction:
 * - Ouvre le fichier de données
 * - Charge les étudiants, matières et notes
 * - Affiche les informations complètes
 * - Libère toute la mémoire allouée
 */
int main(int argc, char** argv) 
{
    const char* filename = "data.txt";
    FILE* file;
    Prom prom;
    
    /* Ouverture du fichier de données en lecture */
    file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Error: Cannot open file %s\n", filename);
        return (1);
    }

    /* Initialisation de la structure Prom */
    printf("Initializing promotion...\n");
    prom = create_prom(0);

    /* Chargement de tous les étudiants depuis le fichier */
    printf("Loading students...\n");
    get_all_students(file, &prom);
    
    /* Chargement de toutes les matières pour chaque étudiant */
    printf("Loading courses...\n");
    get_all_courses(file, &prom);

    /* Chargement de toutes les notes et calcul des moyennes */
    printf("Loading grades and calculating averages...\n");
    get_all_grades(file, &prom);

    /* Fermeture du fichier */
    fclose(file);
    
    /* Affichage de la promotion */
    printf("Displaying promotion information...\n");
    show_prom(prom);

    /* Enregistrement de la promotion dans le fichier binaire */
    printf("Saving promotion to binary file...\n");
    if (save_prom_binary("promotion.bin", &prom) != 0)
    {
        printf("Error: Failed to save promotion to binary file.\n");
    } else {
        printf("Promotion saved successfully to binary file: promotion.bin\n");
    }
    

    /* Libération de toute la mémoire allouée */
    printf("Freeing memory...\n");
    destroy_prom(&prom);

    /* Lecture de la promotion depuis le fichier binaire */
    prom = load_prom_binary("promotion.bin");

    /* Libération de toute la mémoire allouée */
    printf("Freeing memory...\n");
    destroy_prom(&prom);

    printf("Program completed successfully.\n");
    return (0);
}