/*!
 * \file init.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Interface du module de construction et destruction des structures
 * 
 * Ce fichier contient les prototypes des fonctions de création (constructeurs) 
 * et de destruction (destructeurs) pour les structures Grades, Course, Student et Prom.
 */

#include "structures.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

#ifndef INIT_H
#define INIT_H

/*!
 * \fn Grades create_grades(int int_nb_grades)
 * \brief Crée une structure Grades avec allocation dynamique
 * \param int_nb_grades Nombre de notes à allouer
 * \return Structure Grades initialisée avec les notes à 0.0
 * \pre int_nb_grades >= 0
 */
Grades create_grades(int int_nb_grades);

/*!
 * \fn Course create_course(const char* char_course_name, float float_coef, int int_nb_grades)
 * \brief Crée une structure Course (matière) avec allocation dynamique
 * \param char_course_name Nom de la matière
 * \param float_coef Coefficient de la matière
 * \param int_nb_grades Nombre de notes à allouer
 * \return Structure Course initialisée
 * \pre char_course_name != NULL
 * \pre float_coef >= 0
 * \pre int_nb_grades >= 0
 */
Course create_course(const char* char_course_name, float float_coef, int int_nb_grades);

/*!
 * \fn Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses)
 * \brief Crée une structure Student (étudiant) avec allocation dynamique
 * \param int_id Identifiant unique de l'étudiant
 * \param char_last_name Nom de famille de l'étudiant
 * \param char_first_name Prénom de l'étudiant
 * \param int_age Age de l'étudiant
 * \param int_nb_courses Nombre de matières à allouer
 * \return Structure Student initialisée
 * \pre int_id > 0
 * \pre char_last_name != NULL
 * \pre char_first_name != NULL
 * \pre int_age > 0
 * \pre int_nb_courses >= 0
 */
Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses);

/*!
 * \fn Prom create_prom(int int_nb_students)
 * \brief Crée une structure Prom (promotion) avec allocation dynamique
 * \param int_nb_students Nombre d'étudiants à allouer
 * \return Structure Prom initialisée
 * \pre int_nb_students >= 0
 */
Prom create_prom(int int_nb_students);

/*!
 * \fn void destroy_prom(Prom* prom)
 * \brief Libère la mémoire allouée pour une structure Prom
 * \param prom Pointeur vers la structure Prom à détruire
 * \pre prom != NULL
 */
void destroy_prom(Prom* prom);

/*!
 * \fn void destroy_student(Student* student)
 * \brief Libère la mémoire allouée pour une structure Student
 * \param student Pointeur vers la structure Student à détruire
 * \pre student != NULL
 */
void destroy_student(Student* student);

/*!
 * \fn void destroy_course(Course* course)
 * \brief Libère la mémoire allouée pour une structure Course
 * \param course Pointeur vers la structure Course à détruire
 * \pre course != NULL
 */
void destroy_course(Course* course);

/*!
 * \fn void destroy_grades(Grades* grades)
 * \brief Libère la mémoire allouée pour une structure Grades
 * \param grades Pointeur vers la structure Grades à détruire
 * \pre grades != NULL
 */
void destroy_grades(Grades* grades);

#endif