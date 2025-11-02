/*!
 * \file read.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Interface du module de lecture de fichier
 * 
 * Ce fichier contient les prototypes des fonctions permettant de lire
 * et parser les données depuis un fichier texte formaté.
 */

#include "init.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

#ifndef READ_H
#define READ_H

/*!
 * \fn char* read_line(FILE* file)
 * \brief Lit une ligne complète depuis un fichier
 * \param file Pointeur vers le fichier à lire
 * \return Pointeur vers la chaîne lue (allocation dynamique) ou NULL si fin de fichier
 * \pre file != NULL
 */
char* read_line(FILE* file);

/*!
 * \fn char* get_to_type(FILE* file, char* type)
 * \brief Parcourt le fichier jusqu'à trouver un séparateur de section
 * \param file Pointeur vers le fichier à lire
 * \param type Nom de la section recherchée (ex: "ETUDIANTS", "MATIERES", "NOTES")
 * \return Pointeur vers la première ligne de données après le séparateur
 * \pre file != NULL
 * \pre type != NULL
 */
char* get_to_type(FILE* file, char* type);

/*!
 * \fn Course parse_course_line(const char* line)
 * \brief Parse une ligne de données pour créer une structure Course
 * \param line Ligne à parser au format "nom;coefficient"
 * \return Structure Course créée à partir de la ligne
 * \pre line != NULL
 */
Course parse_course_line(const char* line);

/*!
 * \fn Student parse_student_line(const char* line)
 * \brief Parse une ligne de données pour créer une structure Student
 * \param line Ligne à parser au format "id;prenom;nom;age"
 * \return Structure Student créée à partir de la ligne
 * \pre line != NULL
 */
Student parse_student_line(const char* line);

#endif
