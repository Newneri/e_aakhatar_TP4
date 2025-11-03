/*!
* \file tri.c
* \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
* \version 1.0
* \date 3 novembre 2025
* \brief Implémentation du module de tri des étudiants
* 
* Ce fichier contient l'implémentation des fonctions permettant de trier
* les étudiants d'une promotion selon leurs notes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tri.h"
#include "show.h"

/*!
* \fn void trier_etudiants_par_moyenne(Prom* prom)
* \brief Trie les étudiants par moyenne décroissante
* 
* Cette fonction trie le tableau d'étudiants d'une promotion
* par ordre décroissant de moyenne en utilisant l'algorithme
* de tri par sélection.
* 
* \param prom Pointeur vers la structure Prom contenant les étudiants
*/
void trier_etudiants_par_moyenne(Prom* prom) {
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students <= 1) {
        return;
    }

    // Tri par sélection (ordre décroissant)
    for (int i = 0; i < prom->int_nb_students - 1; i++) {
        int max_idx = i;
        
        // Trouver l'étudiant avec la plus grande moyenne
        for (int j = i + 1; j < prom->int_nb_students; j++) {
            if (prom->student_students[j].float_average > prom->student_students[max_idx].float_average) {
                max_idx = j;
            }
        }
        
        // Échanger si nécessaire
        if (max_idx != i) {
            Student temp = prom->student_students[i];
            prom->student_students[i] = prom->student_students[max_idx];
            prom->student_students[max_idx] = temp;
        }
    }
}

/*!
* \fn void trier_etudiants_par_matiere(Prom* prom, char* course_name)
* \brief Trie les étudiants par moyenne dans une matière spécifique
* 
* Cette fonction trie les étudiants d'une promotion en fonction de
* leur moyenne dans une matière donnée et affiche les trois meilleurs.
* 
* \param prom Pointeur vers la structure Prom contenant les étudiants
* \param course_name Nom de la matière pour le tri
*/
void trier_etudiants_par_matiere(Prom* prom, char* course_name) {
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students == 0 || course_name == NULL) {
        exit(EXIT_FAILURE);
    }
    
    // Création de copie du tableau des étudiants pour le tri
    Student *students_copy = malloc(prom->int_nb_students * sizeof(Student));
    if (students_copy == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < prom->int_nb_students; i++){
        students_copy[i] = prom->student_students[i];
    }
    
    // Tri par sélection (ordre décroissant)
    for (int i = 0; i < prom->int_nb_students - 1; i++){
        int max_idx = i;
        
        // Trouver la note de l'étudiant à l'index max_idx
        float avg_max = -1.0f;
        for (int k = 0; k < students_copy[max_idx].int_nb_courses; k++) {
            if (strcmp(students_copy[max_idx].course_courses[k].char_course_name, course_name) == 0) {
                avg_max = students_copy[max_idx].course_courses[k].float_average;
                break;
            }
        }

        for(int j = i + 1; j < prom->int_nb_students; j++) {
            // Recherche de la note de l'étudiant j dans la matière
            float avg_j = -1.0f;
            for (int k = 0; k < students_copy[j].int_nb_courses; k++) {
                if (strcmp(students_copy[j].course_courses[k].char_course_name, course_name) == 0) {
                    avg_j = students_copy[j].course_courses[k].float_average;
                    break;
                }
            }

            // Comparaison des moyennes
            if (avg_j > avg_max) {
                max_idx = j;
                avg_max = avg_j;
            }
        }

        // Échanger si nécessaire
        if (max_idx != i) {
            Student temp = students_copy[i];
            students_copy[i] = students_copy[max_idx];
            students_copy[max_idx] = temp;  
        }
    }
    
    printf("\n===============================================\n");
    printf("          TOP 3 STUDENTS IN %s         \n", course_name);
    printf("===============================================\n");
    
    int top_count = (prom->int_nb_students < 3) ? prom->int_nb_students : 3;
    for (int i = 0; i < top_count; i++) {
        printf("\n[Top Student %d/%d]\n", i + 1, top_count);
        printf("Grade in %s: ", course_name);
        // Recherche de la matière dans les cours de l'étudiant
        for (int k = 0; k < students_copy[i].int_nb_courses; k++) {
            if (strcmp(students_copy[i].course_courses[k].char_course_name, course_name) == 0) {
                printf("%.2f\n", students_copy[i].course_courses[k].float_average);
                break;
            }
        }
        show_student_info(students_copy[i]);
    }

    free(students_copy);
}
