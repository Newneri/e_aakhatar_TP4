/*!
 * \file saveData.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 23 octobre 2024
 * \brief Interface du module de chargement des données depuis un fichier
 * 
 * Ce fichier contient les prototypes des fonctions permettant de charger
 * les étudiants, matières et notes depuis un fichier de données formaté.
 */

#include "read.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SAVEDATA_H
#define SAVEDATA_H

/*!
 * \fn Prom get_all_students(FILE* file)
 * \brief Charge tous les étudiants depuis un fichier
 * \param file Pointeur vers le fichier contenant les données
 * \return Structure Prom contenant tous les étudiants chargés
 * \pre file != NULL
 */
void get_all_students(FILE* file, Prom* prom);

/*!
 * \fn void get_all_courses(FILE* file, Prom* prom)
 * \brief Charge toutes les matières et les assigne à chaque étudiant
 * \param file Pointeur vers le fichier contenant les données
 * \param prom Pointeur vers la structure Prom à remplir
 * \pre file != NULL
 * \pre prom != NULL
 */
void get_all_courses(FILE* file, Prom* prom);

/*!
 * \fn void get_all_grades(FILE* file, Prom* prom)
 * \brief Charge toutes les notes et les assigne aux matières des étudiants
 * \param file Pointeur vers le fichier contenant les données
 * \param prom Pointeur vers la structure Prom à remplir
 * \pre file != NULL
 * \pre prom != NULL
 */
void get_all_grades(FILE* file, Prom* prom);

#endif