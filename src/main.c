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
    int i;
    int j;
    
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

    /* Affichage des informations complètes de tous les étudiants */
    printf("\n=== RESULTS ===\n\n");
    for (i = 0; i < prom.int_nb_students; i++)
    {
        /* Affichage des informations de base de l'étudiant */
        printf("Student: %s %s, Age: %d, ID: %d, Overall Average: %.2f\n",
               prom.student_students[i].char_first_name,
               prom.student_students[i].char_last_name,
               prom.student_students[i].int_age,
               prom.student_students[i].int_id,
               prom.student_students[i].float_average);
        
        /* Affichage de toutes les matières et notes de l'étudiant */
        for (j = 0; j < prom.student_students[i].int_nb_courses; j++)
        {
            Course* course = &prom.student_students[i].course_courses[j];
            int k;
            
            /* Affichage du nom de la matière et de sa moyenne */
            printf("  Course: %s, Coefficient: %.2f, Average: %.2f\n",
                   course->char_course_name,
                   course->float_coef,
                   course->float_average);
            
            /* Affichage de toutes les notes de cette matière */
            printf("    Grades: ");
            for (k = 0; k < course->grades.int_nb_grades; k++)
            {
                printf("%.2f ", course->grades.tab_grades[k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    /* Fermeture du fichier */
    fclose(file);

    /* Libération de toute la mémoire allouée */
    printf("Freeing memory...\n");
    destroy_prom(&prom);
    
    printf("Program completed successfully.\n");
    return (0);
}