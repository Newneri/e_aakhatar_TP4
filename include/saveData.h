/*!
 * \file saveData.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date October 23, 2025
 * \brief Interface for the data loading module from a file
 * 
 * This file contains the prototypes of functions for loading
 * students, courses and grades from a formatted data file.
 */

#include "read.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SAVEDATA_H
#define SAVEDATA_H

/*!
 * \fn Prom get_all_students(FILE* file)
 * \brief Loads all students from a file
 * \param file Pointer to the file containing the data
 * \return Prom structure containing all loaded students
 * \pre file != NULL
 */
void get_all_students(FILE* file, Prom* prom);

/*!
 * \fn void get_all_courses(FILE* file, Prom* prom)
 * \brief Loads all courses and assigns them to each student
 * \param file Pointer to the file containing the data
 * \param prom Pointer to the Prom structure to fill
 * \pre file != NULL
 * \pre prom != NULL
 */
void get_all_courses(FILE* file, Prom* prom);

/*!
 * \fn void get_all_grades(FILE* file, Prom* prom)
 * \brief Loads all grades and assigns them to student courses
 * \param file Pointer to the file containing the data
 * \param prom Pointer to the Prom structure to fill
 * \pre file != NULL
 * \pre prom != NULL
 */
void get_all_grades(FILE* file, Prom* prom);

#endif