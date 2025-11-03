/*!
 * \file init.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Interface for structure construction and destruction module
 * 
 * This file contains the prototypes of creation functions (constructors) 
 * and destruction functions (destructors) for Grades, Course, Student and Prom structures.
 */

#include "structures.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

#ifndef INIT_H
#define INIT_H

/*!
 * \fn Grades create_grades(int int_nb_grades)
 * \brief Creates a Grades structure with dynamic allocation
 * \param int_nb_grades Number of grades to allocate
 * \return Initialized Grades structure with grades set to 0.0
 * \pre int_nb_grades >= 0
 */
Grades create_grades(int int_nb_grades);

/*!
 * \fn Course create_course(const char* char_course_name, float float_coef, int int_nb_grades)
 * \brief Creates a Course structure (subject) with dynamic allocation
 * \param char_course_name Name of the course
 * \param float_coef Coefficient of the course
 * \param int_nb_grades Number of grades to allocate
 * \return Initialized Course structure
 * \pre char_course_name != NULL
 * \pre float_coef >= 0
 * \pre int_nb_grades >= 0
 */
Course create_course(const char* char_course_name, float float_coef, int int_nb_grades);

/*!
 * \fn Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses)
 * \brief Creates a Student structure with dynamic allocation
 * \param int_id Unique identifier of the student
 * \param char_last_name Last name of the student
 * \param char_first_name First name of the student
 * \param int_age Age of the student
 * \param int_nb_courses Number of courses to allocate
 * \return Initialized Student structure
 * \pre int_id > 0
 * \pre char_last_name != NULL
 * \pre char_first_name != NULL
 * \pre int_age > 0
 * \pre int_nb_courses >= 0
 */
Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses);

/*!
 * \fn Prom create_prom(int int_nb_students)
 * \brief Creates a Prom structure (promotion) with dynamic allocation
 * \param int_nb_students Number of students to allocate
 * \return Initialized Prom structure
 * \pre int_nb_students >= 0
 */
Prom create_prom(int int_nb_students);

/*!
 * \fn void destroy_prom(Prom* prom)
 * \brief Frees the memory allocated for a Prom structure
 * \param prom Pointer to the Prom structure to destroy
 * \pre prom != NULL
 */
void destroy_prom(Prom* prom);

/*!
 * \fn void destroy_student(Student* student)
 * \brief Frees the memory allocated for a Student structure
 * \param student Pointer to the Student structure to destroy
 * \pre student != NULL
 */
void destroy_student(Student* student);

/*!
 * \fn void destroy_course(Course* course)
 * \brief Frees the memory allocated for a Course structure
 * \param course Pointer to the Course structure to destroy
 * \pre course != NULL
 */
void destroy_course(Course* course);

/*!
 * \fn void destroy_grades(Grades* grades)
 * \brief Frees the memory allocated for a Grades structure
 * \param grades Pointer to the Grades structure to destroy
 * \pre grades != NULL
 */
void destroy_grades(Grades* grades);

#endif