/*!
 * \file binary.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Interface for binary save/restore module
 * 
 * This file contains the prototypes of functions that allow saving
 * and restoring a complete promotion (students, courses, grades) to a binary file.
 */

#ifndef BINARY_H
#define BINARY_H

#include "init.h"

/*!
 * \fn int save_prom_binary(const char* str_filename, Prom* prom)
 * \brief Saves a complete promotion to a binary file
 * \param str_filename Name of the destination binary file
 * \param prom Pointer to the Prom structure to save
 * \return 0 on success, -1 on error
 * \pre str_filename != NULL
 * \pre prom != NULL
 * 
 * This function saves in order:
 * - The number of students
 * - For each student: ID, last name, first name, age, number of courses, average
 * - For each course of each student: name, coefficient, average, number of grades, grades
 */
int save_prom_binary(const char* str_filename, Prom* prom);

/*!
 * \fn Prom load_prom_binary(const char* str_filename)
 * \brief Restores a promotion from a binary file
 * \param str_filename Name of the source binary file
 * \return Restored Prom structure, or empty structure on error
 * \pre str_filename != NULL
 * 
 * This function reads the binary file and reconstructs in memory:
 * - All students with their information
 * - All courses of each student
 * - All grades of each course
 */
Prom load_prom_binary(const char* str_filename);

#endif