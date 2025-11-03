/*!
* \file sorting.h
* \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
* \version 1.0
* \date November 3, 2025
* \brief Interface for student sorting module
* 
* This file contains the prototypes of functions to sort
* students in a promotion according to their grades.
*/

#ifndef SORTING_H
#define SORTING_H

#include "init.h"

/*!
* \fn void sort_students_by_average(Prom* prom)
* \brief Sorts students by descending average
* 
* This function sorts the student array of a promotion
* in descending order of average using selection sort algorithm.
* 
* \param prom Pointer to the Prom structure containing students
*/
void sort_students_by_average(Prom* prom);

/*!
* \fn void sort_students_from_course(Prom* prom, char* course_name)
* \brief Sorts students by average in a specific course
* 
* This function sorts students in a promotion according to
* their average in a given course and displays the top three.
* 
* \param prom Pointer to the Prom structure containing students
* \param course_name Name of the course for sorting
*/
void sort_students_from_course(Prom* prom, char* course_name);

#endif