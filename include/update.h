/*!
 * \file update.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Interface for the average update module
 * 
 * This file contains the prototypes of functions for calculating
 * and updating course and student averages.
 */

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "init.h"

#ifndef UPDATE_H
#define UPDATE_H

/*!
 * \fn void update_student_average(Prom* prom)
 * \brief Updates the averages of all students in a cohort
 * \param prom Pointer to the Prom structure containing the students
 * \pre prom != NULL
 */
void update_student_average(Prom* prom);

/*!
 * \fn void update_course_average(Prom* prom)
 * \brief Updates the averages of all courses for all students
 * \param prom Pointer to the Prom structure containing the students
 * \pre prom != NULL
 */
void update_course_average(Prom* prom);

#endif