/*!
 * \file update.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Interface du module de mise à jour des moyennes
 * 
 * Ce fichier contient les prototypes des fonctions permettant de calculer
 * et mettre à jour les moyennes des matières et des étudiants.
 */

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "init.h"

#ifndef UPDATE_H
#define UPDATE_H

/*!
 * \fn void update_student_average(Prom* prom)
 * \brief Met à jour les moyennes de tous les étudiants d'une promotion
 * \param prom Pointeur vers la structure Prom contenant les étudiants
 * \pre prom != NULL
 */
void update_student_average(Prom* prom);

/*!
 * \fn void update_course_average(Prom* prom)
 * \brief Met à jour les moyennes de toutes les matières de tous les étudiants
 * \param prom Pointeur vers la structure Prom contenant les étudiants
 * \pre prom != NULL
 */
void update_course_average(Prom* prom);

#endif