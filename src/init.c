/*!
 * \file init.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Module de construction et destruction des structures de données
 * 
 * Ce fichier contient l'implémentation des fonctions de création (constructeurs) 
 * et de destruction (destructeurs) pour les structures Grades, Course, Student et Prom.
 */

#include "init.h"
#include <string.h>

/*!
 * \fn Grades create_grades(int int_nb_grades)
 * \brief Crée une structure Grades avec allocation dynamique
 * \param int_nb_grades Nombre de notes à allouer
 * \return Structure Grades initialisée avec les notes à 0.0
 */
Grades create_grades(int int_nb_grades) 
{
    Grades grades;
    int i;
    
    /* Initialisation du nombre de notes */
    grades.int_nb_grades = int_nb_grades;
    
    /* Allocation dynamique du tableau de notes */
    grades.tab_grades = (float*)malloc(int_nb_grades * sizeof(float));
    
    /* Vérification de la réussite de l'allocation */
    if (grades.tab_grades != NULL) 
    {
        /* Initialisation de toutes les notes à 0.0 */
        for (i = 0; i < int_nb_grades; i++) 
        {
            grades.tab_grades[i] = 0.0f;
        }
    }
    
    return (grades);
}


/*!
 * \fn Course create_course(const char* char_course_name, float float_coef, int int_nb_grades)
 * \brief Crée une structure Course (matière) avec allocation dynamique
 * \param char_course_name Nom de la matière
 * \param float_coef Coefficient de la matière
 * \param int_nb_grades Nombre de notes à allouer
 * \return Structure Course initialisée
 */
Course create_course(const char* char_course_name, float float_coef, int int_nb_grades) 
{
    Course course;
    
    /* Duplication du nom de la matière (allocation dynamique + copie) */
    course.char_course_name = strdup(char_course_name);
    
    /* Initialisation du coefficient */
    course.float_coef = float_coef;
    
    /* Création de la structure Grades associée */
    course.grades = create_grades(int_nb_grades);
    
    /* Initialisation de la moyenne à 0 */
    course.float_average = 0.0f;
    
    return (course);
}

/*!
 * \fn Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses)
 * \brief Crée une structure Student (étudiant) avec allocation dynamique
 * \param int_id Identifiant unique de l'étudiant
 * \param char_last_name Nom de famille de l'étudiant
 * \param char_first_name Prénom de l'étudiant
 * \param int_age Age de l'étudiant
 * \param int_nb_courses Nombre de matières à allouer
 * \return Structure Student initialisée
 */
Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses) 
{
    Student student;
    
    /* Initialisation de l'identifiant */
    student.int_id = int_id;
    
    /* Duplication du nom de famille (allocation dynamique + copie) */
    student.char_last_name = strdup(char_last_name);
    
    /* Duplication du prénom (allocation dynamique + copie) */
    student.char_first_name = strdup(char_first_name);
    
    /* Initialisation de l'âge */
    student.int_age = int_age;
    
    /* Initialisation du nombre de matières */
    student.int_nb_courses = int_nb_courses;
    
    /* Allocation dynamique du tableau de matières */
    student.course_courses = (Course*)malloc(int_nb_courses * sizeof(Course));
    
    /* Initialisation de la moyenne générale à 0 */
    student.float_average = 0.0f;
    
    return (student);
}

/*!
 * \fn Prom create_prom(int int_nb_students)
 * \brief Crée une structure Prom (promotion) avec allocation dynamique
 * \param int_nb_students Nombre d'étudiants à allouer
 * \return Structure Prom initialisée
 */
Prom create_prom(int int_nb_students) 
{
    Prom prom;
    
    /* Initialisation du nombre d'étudiants */
    prom.int_nb_students = int_nb_students;
    
    /* Allocation dynamique du tableau d'étudiants */
    prom.student_students = (Student*)malloc(int_nb_students * sizeof(Student));
    
    return (prom);
}


/*!
 * \fn void destroy_grades(Grades* grades)
 * \brief Libère la mémoire allouée pour une structure Grades
 * \param grades Pointeur vers la structure Grades à détruire
 */
void destroy_grades(Grades* grades) 
{
    /* Vérification que le tableau de notes existe */
    if (grades->tab_grades != NULL) 
    {
        /* Libération de la mémoire du tableau */
        free(grades->tab_grades);
        
        /* Mise à NULL du pointeur pour éviter les double free */
        grades->tab_grades = NULL;
    }
    
    /* Réinitialisation du nombre de notes */
    grades->int_nb_grades = 0;
}

/*!
 * \fn void destroy_course(Course* course)
 * \brief Libère la mémoire allouée pour une structure Course
 * \param course Pointeur vers la structure Course à détruire
 */
void destroy_course(Course* course) 
{
    /* Vérification que le nom de la matière existe */
    if (course->char_course_name != NULL) 
    {
        /* Libération de la mémoire du nom */
        free(course->char_course_name);
        
        /* Mise à NULL du pointeur pour éviter les double free */
        course->char_course_name = NULL;
    }
    
    /* Destruction de la structure Grades associée */
    destroy_grades(&course->grades);
    
    /* Réinitialisation du coefficient */
    course->float_coef = 0.0f;
    
    /* Réinitialisation de la moyenne */
    course->float_average = 0.0f;
}


/*!
 * \fn void destroy_student(Student* student)
 * \brief Libère la mémoire allouée pour une structure Student
 * \param student Pointeur vers la structure Student à détruire
 */
void destroy_student(Student* student) 
{
    int i;
    
    /* Vérification et libération du nom de famille */
    if (student->char_last_name != NULL) 
    {
        free(student->char_last_name);
        student->char_last_name = NULL;
    }
    
    /* Vérification et libération du prénom */
    if (student->char_first_name != NULL) 
    {
        free(student->char_first_name);
        student->char_first_name = NULL;
    }
    
    /* Vérification que le tableau de matières existe */
    if (student->course_courses != NULL) 
    {
        /* Destruction de chaque matière du tableau */
        for (i = 0; i < student->int_nb_courses; i++) 
        {
            destroy_course(&student->course_courses[i]);
        }
        
        /* Libération du tableau de matières */
        free(student->course_courses);
        
        /* Mise à NULL du pointeur pour éviter les double free */
        student->course_courses = NULL;
    }
    
    /* Réinitialisation de tous les champs numériques */
    student->int_id = 0;
    student->int_age = 0;
    student->int_nb_courses = 0;
    student->float_average = 0.0f;
}

/*!
 * \fn void destroy_prom(Prom* prom)
 * \brief Libère la mémoire allouée pour une structure Prom
 * \param prom Pointeur vers la structure Prom à détruire
 */
void destroy_prom(Prom* prom) 
{
    int i;
    
    /* Vérification que le tableau d'étudiants existe */
    if (prom->student_students != NULL) 
    {
        /* Destruction de chaque étudiant du tableau */
        for (i = 0; i < prom->int_nb_students; i++) 
        {
            destroy_student(&prom->student_students[i]);
        }
        
        /* Libération du tableau d'étudiants */
        free(prom->student_students);
        
        /* Mise à NULL du pointeur pour éviter les double free */
        prom->student_students = NULL;
    }
    
    /* Réinitialisation du nombre d'étudiants */
    prom->int_nb_students = 0;
}

