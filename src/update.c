/*!
 * \file update.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Module de mise à jour des moyennes
 * 
 * Ce fichier contient l'implémentation des fonctions de mise à jour 
 * des moyennes pour les matières et les étudiants.
 */

#include "update.h"
#include "init.h"

/*!
 * \fn void update_course_average(Prom* prom)
 * \brief Met à jour les moyennes de toutes les matières de tous les étudiants
 * \param prom Pointeur vers la structure Prom contenant tous les étudiants
 */
void update_course_average(Prom* prom) 
{
    int i;
    int j;
    int k;
    Student* student;
    Course* course;
    float sum_grades;
    
    /* Vérification des paramètres d'entrée */
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students <= 0) 
    {
        return;
    }
    
    /* Parcours de tous les étudiants de la promotion */
    for (i = 0; i < prom->int_nb_students; i++) 
    {
        student = &prom->student_students[i];
        
        /* Vérification que l'étudiant et ses matières sont valides */
        if (student != NULL && student->course_courses != NULL && student->int_nb_courses > 0) 
        {
            /* Parcours de toutes les matières de l'étudiant */
            for (j = 0; j < student->int_nb_courses; j++) 
            {
                course = &student->course_courses[j];
                
                /* Vérification que la matière contient des notes */
                if (course->grades.tab_grades != NULL && course->grades.int_nb_grades > 0) 
                {
                    sum_grades = 0.0f;
                    
                    /* Calcul de la somme de toutes les notes */
                    for (k = 0; k < course->grades.int_nb_grades; k++) 
                    {
                        sum_grades += course->grades.tab_grades[k];
                    }
                    
                    /* Calcul de la moyenne de la matière */
                    course->float_average = sum_grades / course->grades.int_nb_grades;
                } 
                else 
                {
                    /* Pas de notes : moyenne à 0 */
                    course->float_average = 0.0f;
                }
            }
        }
    }
}


/*!
 * \fn void update_student_average(Prom* prom)
 * \brief Met à jour les moyennes générales de tous les étudiants
 * \param prom Pointeur vers la structure Prom contenant tous les étudiants
 */
void update_student_average(Prom* prom)  
{
    int i;
    int j;
    Student* student;
    float sum_averages;
    float sum_coefs;
    
    /* Vérification des paramètres d'entrée */
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students <= 0) 
    {
        return;
    }
    
    /* Parcours de tous les étudiants de la promotion */
    for (i = 0; i < prom->int_nb_students; i++) 
    {
        student = &prom->student_students[i];
        
        /* Vérification que l'étudiant et ses matières sont valides */
        if (student != NULL && student->course_courses != NULL && student->int_nb_courses > 0) 
        {
            sum_averages = 0.0f;
            sum_coefs = 0.0f;
            
            /* Calcul de la somme pondérée des moyennes de matières */
            for (j = 0; j < student->int_nb_courses; j++) 
            {
                /* Somme des moyennes multipliées par leurs coefficients */
                sum_averages += student->course_courses[j].float_average * student->course_courses[j].float_coef;
                
                /* Somme des coefficients */
                sum_coefs += student->course_courses[j].float_coef;
            }
            
            /* Calcul de la moyenne générale pondérée */
            student->float_average = sum_averages / sum_coefs;
        } 
        else 
        {
            /* Pas de matières : moyenne à 0 */
            student->float_average = 0.0f;
        }
    }
}