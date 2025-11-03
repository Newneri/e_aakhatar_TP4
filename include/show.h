/*!
 * \file show.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Interface for display module
 * 
 * This file contains the prototypes of functions to display
 * information about students, courses and promotions.
 */

#ifndef SHOW_H
#define SHOW_H

#include "structures.h"
#include <stdio.h>

/*!
 * \fn void show_grades(Grades grades)
 * \brief Displays all grades
 * \param grades Grades structure to display
 */
void show_grades(Grades grades);

/*!
 * \fn void show_course(Course course)
 * \brief Displays complete information about a course
 * \param course Course structure to display
 */
void show_course(Course course);

/*!
 * \fn void show_student(Student student)
 * \brief Displays complete information about a student
 * \param student Student structure to display
 */
void show_student(Student student);

/*!
 * \fn void show_student_info(Student student)
 * \brief Displays basic information about a student
 * \param student Student structure to display
 */
void show_student_info(Student student);

/*!
 * \fn void show_prom(Prom prom)
 * \brief Displays complete information about a promotion
 * \param prom Prom structure to display
 */
void show_prom(Prom prom);

/*!
* \fn void show_best(Student* students, int n)
* \brief Displays the n best students of a promotion
* \param students Array of students
* \param n Number of students to display
* 
* Displays the n students with the highest averages
*/
void show_best(Student* students, int n);

#endif