/*!
 * \file binary.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Module de sauvegarde/restauration binaire des promotions
 * 
 * Ce fichier contient l'implémentation des fonctions permettant de sauvegarder
 * et restaurer une promotion complète dans un fichier binaire.
 */

#include "binary.h"
#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \fn int save_prom_binary(const char* str_filename, Prom* prom)
 * \brief Sauvegarde une promotion complète dans un fichier binaire
 * \param str_filename Nom du fichier binaire de destination
 * \param prom Pointeur vers la structure Prom à sauvegarder
 * \return 0 si succès, -1 en cas d'erreur
 */
int save_prom_binary(const char* str_filename, Prom* prom)
{
    FILE* file;
    int i;
    int j;
    int str_len;
    
    /* Vérification des paramètres */
    if (str_filename == NULL || prom == NULL)
    {
        return (-1);
    }
    
    /* Ouverture du fichier en mode écriture binaire */
    file = fopen(str_filename, "wb");
    if (file == NULL)
    {
        return (-1);
    }
    
    /* Écriture du nombre d'étudiants dans la promotion */
    fwrite(&prom->int_nb_students, sizeof(int), 1, file);
    
    /* Parcours de tous les étudiants */
    for (i = 0; i < prom->int_nb_students; i++)
    {
        Student* student = &prom->student_students[i];
        
        /* Écriture des informations de base de l'étudiant */
        fwrite(&student->int_id, sizeof(int), 1, file);
        fwrite(&student->int_age, sizeof(int), 1, file);
        fwrite(&student->float_average, sizeof(float), 1, file);
        fwrite(&student->int_nb_courses, sizeof(int), 1, file);
        
        /* Écriture du nom de famille (longueur + chaîne) */
        str_len = strlen(student->char_last_name) + 1;
        fwrite(&str_len, sizeof(int), 1, file);
        fwrite(student->char_last_name, sizeof(char), str_len, file);
        
        /* Écriture du prénom (longueur + chaîne) */
        str_len = strlen(student->char_first_name) + 1;
        fwrite(&str_len, sizeof(int), 1, file);
        fwrite(student->char_first_name, sizeof(char), str_len, file);
        
        /* Parcours de tous les cours de l'étudiant */
        for (j = 0; j < student->int_nb_courses; j++)
        {
            Course* course = &student->course_courses[j];
            
            /* Écriture des informations du cours */
            fwrite(&course->float_coef, sizeof(float), 1, file);
            fwrite(&course->float_average, sizeof(float), 1, file);
            
            /* Écriture du nom du cours (longueur + chaîne) */
            str_len = strlen(course->char_course_name) + 1;
            fwrite(&str_len, sizeof(int), 1, file);
            fwrite(course->char_course_name, sizeof(char), str_len, file);
            
            /* Écriture du nombre de notes */
            fwrite(&course->grades.int_nb_grades, sizeof(int), 1, file);
            
            /* Écriture de toutes les notes du cours */
            if (course->grades.int_nb_grades > 0)
            {
                fwrite(course->grades.tab_grades, sizeof(float), 
                       course->grades.int_nb_grades, file);
            }
        }
    }
    
    /* Fermeture du fichier */
    fclose(file);
    
    return (0);
}

/*!
 * \fn Prom load_prom_binary(const char* str_filename)
 * \brief Restaure une promotion depuis un fichier binaire
 * \param str_filename Nom du fichier binaire source
 * \return Structure Prom restaurée, ou structure vide en cas d'erreur
 */
Prom load_prom_binary(const char* str_filename)
{
    FILE* file;
    Prom prom;
    int i;
    int j;
    int str_len;
    char buffer[256];
    
    /* Vérification du paramètre */
    if (str_filename == NULL)
    {
        prom.int_nb_students = 0;
        prom.student_students = NULL;
        return (prom);
    }
    
    /* Ouverture du fichier en mode lecture binaire */
    file = fopen(str_filename, "rb");
    if (file == NULL)
    {
        printf("Error: Cannot open binary file %s\n", str_filename);
        prom.int_nb_students = 0;
        prom.student_students = NULL;
        return (prom);
    }
    
    /* Lecture du nombre d'étudiants */
    fread(&prom.int_nb_students, sizeof(int), 1, file);
    
    /* Allocation du tableau d'étudiants */
    prom.student_students = (Student*)malloc(prom.int_nb_students * sizeof(Student));
    if (prom.student_students == NULL)
    {
        fclose(file);
        prom.int_nb_students = 0;
        return (prom);
    }
    
    /* Parcours de tous les étudiants */
    for (i = 0; i < prom.int_nb_students; i++)
    {
        Student* student = &prom.student_students[i];
        
        /* Lecture des informations de base de l'étudiant */
        fread(&student->int_id, sizeof(int), 1, file);
        fread(&student->int_age, sizeof(int), 1, file);
        fread(&student->float_average, sizeof(float), 1, file);
        fread(&student->int_nb_courses, sizeof(int), 1, file);
        
        /* Lecture du nom de famille */
        fread(&str_len, sizeof(int), 1, file);
        fread(buffer, sizeof(char), str_len, file);
        student->char_last_name = strdup(buffer);
        
        /* Lecture du prénom */
        fread(&str_len, sizeof(int), 1, file);
        fread(buffer, sizeof(char), str_len, file);
        student->char_first_name = strdup(buffer);
        
        /* Allocation du tableau de cours */
        student->course_courses = (Course*)malloc(student->int_nb_courses * sizeof(Course));
        
        /* Parcours de tous les cours de l'étudiant */
        for (j = 0; j < student->int_nb_courses; j++)
        {
            Course* course = &student->course_courses[j];
            
            /* Lecture des informations du cours */
            fread(&course->float_coef, sizeof(float), 1, file);
            fread(&course->float_average, sizeof(float), 1, file);
            
            /* Lecture du nom du cours */
            fread(&str_len, sizeof(int), 1, file);
            fread(buffer, sizeof(char), str_len, file);
            course->char_course_name = strdup(buffer);
            
            /* Lecture du nombre de notes */
            fread(&course->grades.int_nb_grades, sizeof(int), 1, file);
            
            /* Allocation et lecture des notes */
            if (course->grades.int_nb_grades > 0)
            {
                course->grades.tab_grades = (float*)malloc(course->grades.int_nb_grades * sizeof(float));
                fread(course->grades.tab_grades, sizeof(float), course->grades.int_nb_grades, file);
            }
            else
            {
                course->grades.tab_grades = NULL;
            }
        }
    }
    
    /* Fermeture du fichier */
    fclose(file);
    
    printf("Promotion loaded successfully from binary file: %s\n", str_filename);
    return (prom);
}