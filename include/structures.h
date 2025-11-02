/*!
 * \file structures.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Définitions des structures de données du projet
 * 
 * Ce fichier contient les définitions des structures Grades, Course, Student et Prom
 * utilisées pour la gestion d'une promotion d'étudiants avec leurs matières et notes.
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

/*!
 * \struct Grades
 * \brief Structure représentant un ensemble de notes
 */
typedef struct 
{
    float* tab_grades;        /*!< Tableau dynamique de notes */
    int int_nb_grades;        /*!< Nombre de notes dans le tableau */
} Grades;

/*!
 * \struct Course
 * \brief Structure représentant une matière (cours)
 */
typedef struct 
{
    Grades grades;            /*!< Notes de la matière */
    char *char_course_name;   /*!< Nom de la matière */
    float float_coef;         /*!< Coefficient de la matière */
    float float_average;      /*!< Moyenne de la matière */
    int int_nb_grades;        /*!< Nombre de notes */
} Course;

/*!
 * \struct Student
 * \brief Structure représentant un étudiant
 */
typedef struct 
{
    int int_id;               /*!< Identifiant unique de l'étudiant */
    char *char_last_name;     /*!< Nom de famille */
    char *char_first_name;    /*!< Prénom */
    int int_age;              /*!< Age de l'étudiant */
    int int_nb_courses;       /*!< Nombre de matières suivies */
    Course *course_courses;   /*!< Tableau dynamique de matières */
    float float_average;      /*!< Moyenne générale de l'étudiant */
} Student;

/*!
 * \struct Prom
 * \brief Structure représentant une promotion d'étudiants
 */
typedef struct 
{
    int int_nb_students;      /*!< Nombre d'étudiants dans la promotion */
    Student *student_students; /*!< Tableau dynamique d'étudiants */
} Prom;


#endif