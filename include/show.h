/*!
 * \file show.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Interface du module d'affichage des structures
 * 
 * Ce fichier contient les prototypes des fonctions permettant d'afficher
 * les informations des structures Grades, Course, Student et Prom de manière formatée.
 */

#ifndef SHOW_H
#define SHOW_H

#include "structures.h"
#include <stdio.h>

/*!
 * \fn void show_grades(Grades grades)
 * \brief Affiche toutes les notes d'une structure Grades
 * \param grades Structure Grades à afficher
 * 
 * Affiche le nombre de notes et la liste de toutes les notes
 * au format : "Grades (n): note1; note2; note3; ..."
 */
void show_grades(Grades grades);

/*!
 * \fn void show_course(Course course)
 * \brief Affiche les informations complètes d'un cours
 * \param course Structure Course à afficher
 * 
 * Affiche :
 * - Le nom du cours
 * - Le coefficient
 * - La moyenne du cours
 * - Toutes les notes du cours
 */
void show_course(Course course);

/*!
 * \fn void show_student(Student student)
 * \brief Affiche les informations complètes d'un étudiant
 * \param student Structure Student à afficher
 * 
 * Affiche :
 * - L'identifiant de l'étudiant
 * - Le nom et prénom
 * - L'âge
 * - La moyenne générale
 * - Tous les cours avec leurs détails
 */
void show_student(Student student);

/*!
 * \fn void show_prom(Prom prom)
 * \brief Affiche les informations complètes d'une promotion
 * \param prom Structure Prom à afficher
 * 
 * Affiche :
 * - Le nombre total d'étudiants
 * - Les informations complètes de chaque étudiant
 * - Tous les cours et notes de chaque étudiant
 */
void show_prom(Prom prom);

#endif