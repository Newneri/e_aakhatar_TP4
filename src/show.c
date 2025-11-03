/*!
 * \file show.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Module d'affichage des structures de données
 * 
 * Ce fichier contient l'implémentation des fonctions permettant d'afficher
 * de manière formatée les structures Grades, Course, Student et Prom.
 */

#include <stdio.h>
#include <stdlib.h> 
#include "structures.h"
#include "show.h"

/*!
 * \fn void show_grades(Grades grades)
 * \brief Affiche toutes les notes d'une structure Grades
 * \param grades Structure Grades à afficher
 */
void show_grades(Grades grades)
{
    int i;
    
    /* Vérification si des notes existent */
    if (grades.int_nb_grades == 0)
    {
        printf("      No grades available\n");
        return;
    }
    
    /* Affichage du nombre de notes */
    printf("      Grades (%d): ", grades.int_nb_grades);
    
    /* Affichage de chaque note séparée par une virgule */
    for (i = 0; i < grades.int_nb_grades; i++)
    {
        printf("%.2f", grades.tab_grades[i]);
        
        /* Ajouter une virgule sauf pour la dernière note */
        if (i < grades.int_nb_grades - 1)
        {
            printf("; ");
        }
    }
    printf("\n");
}

/*!
 * \fn void show_course(Course course)
 * \brief Affiche les informations complètes d'un cours
 * \param course Structure Course à afficher
 */
void show_course(Course course)
{
    printf("    - %s (Coef: %.2f, Avg: %.2f, %d grades)\n",
           course.char_course_name,
           course.float_coef,
           course.float_average,
           course.grades.int_nb_grades);
    
    /* Affichage de toutes les notes du cours */
    show_grades(course.grades);
}


/*!
 * \fn void show_student(Student student)
 * \brief Affiche les informations complètes d'un étudiant
 * \param student Structure Student à afficher
 */
void show_student(Student student)
{
    int i;
    /* Affichage des informations de base de l'étudiant */
    show_student_info(student);
    
    /* Vérification s'il y a des cours */
    if (student.int_nb_courses == 0)
    {
        printf("  No courses enrolled\n");
        return;
    }
    
    /* Affichage de tous les cours de l'étudiant */
    printf("\n  Courses Details:\n");
    for (i = 0; i < student.int_nb_courses; i++)
    {
        printf("\n  [Course %d/%d]\n", i + 1, student.int_nb_courses);
        show_course(student.course_courses[i]);
    }
}

void show_student_info(Student student)
{
    /* Affichage des informations de base de l'étudiant */
    printf("\n  ========================================\n");
    printf("  Student ID: %d\n", student.int_id);
    printf("  Name: %s %s\n", student.char_first_name, student.char_last_name);
    printf("  Age: %d years old\n", student.int_age);
    printf("  Overall Average: %.2f\n", student.float_average);
    printf("  Number of Courses: %d\n", student.int_nb_courses);
    printf("  ========================================\n");
}

/*!
 * \fn void show_prom(Prom prom)
 * \brief Affiche les informations complètes d'une promotion
 * \param prom Structure Prom à afficher
 */
void show_prom(Prom prom)
{
    int i;
    
    /* Affichage de l'en-tête de la promotion */
    printf("\n");
    printf("===============================================\n");
    printf("          PROMOTION INFORMATION                \n");
    printf("===============================================\n");
    printf("Total Students: %d\n", prom.int_nb_students);
    printf("===============================================\n");
    
    /* Vérification s'il y a des étudiants */
    if (prom.int_nb_students == 0)
    {
        printf("\nNo students in this promotion\n");
        printf("===============================================\n\n");
        return;
    }
    
    /* Affichage de chaque étudiant de la promotion */
    for (i = 0; i < prom.int_nb_students; i++)
    {
        printf("\n[Student %d/%d]", i + 1, prom.int_nb_students);
        show_student(prom.student_students[i]);
    }
    
    /* Affichage du pied de page */
    printf("\n");
    printf("===============================================\n");
    printf("          END OF PROMOTION DATA                \n");
    printf("===============================================\n\n");
}


/*!
 * \fn void show_best(Prom prom, int n)
 * \brief Affiche les n meilleurs étudiants d'une promotion
 * \param prom Structure Prom à afficher
 * \param n Nombre d'étudiants à afficher
 */
void show_best(Student* students, int n){
    int i;
    
    /* Affichage de l'en-tête des meilleurs étudiants */
    printf("\n");
    printf("===============================================\n");
    printf("          TOP %d STUDENTS BY PROMOTION         \n", n);
    printf("===============================================\n");
    
    /* Vérification s'il y a des étudiants */
    if (n == 0)
    {
        printf("\nNo students \n");
        printf("===============================================\n\n");
        return;
    }
    
    /* Affichage des n meilleurs étudiants */
    for (i = 0; i < n; i++)
    {
        printf("\n[Top Student %d/%d]", i + 1, n);
        show_student_info(students[i]);
    }
    
    /* Affichage du pied de page */
    printf("\n");
    printf("===============================================\n");
    printf("          END OF TOP STUDENTS DATA             \n");
    printf("===============================================\n\n");
}