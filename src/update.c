/*!
 * \file update.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Average update module
 * 
 * This file contains the implementation of functions for updating
 * averages for courses and students.
 */

#include "update.h"
#include "init.h"

/*!
 * \fn void update_course_average(Prom* prom)
 * \brief Updates the averages of all courses for all students
 * \param prom Pointer to the Prom structure containing all students
 */
void update_course_average(Prom* prom) 
{
    int i;
    int j;
    int k;
    Student* student;
    Course* course;
    float sum_grades;
    
    /* Check input parameters */
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students <= 0) 
    {
        return;
    }
    
    /* Loop through all students in the promotion */
    for (i = 0; i < prom->int_nb_students; i++) 
    {
        student = &prom->student_students[i];
        
        /* Check that the student and their courses are valid */
        if (student != NULL && student->course_courses != NULL && student->int_nb_courses > 0) 
        {
            /* Loop through all courses of the student */
            for (j = 0; j < student->int_nb_courses; j++) 
            {
                course = &student->course_courses[j];
                
                /* Check that the course contains grades */
                if (course->grades.tab_grades != NULL && course->grades.int_nb_grades > 0) 
                {
                    sum_grades = 0.0f;
                    
                    /* Calculate the sum of all grades */
                    for (k = 0; k < course->grades.int_nb_grades; k++) 
                    {
                        sum_grades += course->grades.tab_grades[k];
                    }
                    
                    /* Calculate the course average */
                    course->float_average = sum_grades / course->grades.int_nb_grades;
                } 
                else 
                {
                    /* No grades: set average to 0 */
                    course->float_average = 0.0f;
                }
            }
        }
    }
}


/*!
 * \fn void update_student_average(Prom* prom)
 * \brief Updates the overall averages of all students
 * \param prom Pointer to the Prom structure containing all students
 */
void update_student_average(Prom* prom)  
{
    int i;
    int j;
    Student* student;
    float sum_averages;
    float sum_coefs;
    
    /* Check input parameters */
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students <= 0) 
    {
        return;
    }
    
    /* Loop through all students in the promotion */
    for (i = 0; i < prom->int_nb_students; i++) 
    {
        student = &prom->student_students[i];
        
        /* Check that the student and their courses are valid */
        if (student != NULL && student->course_courses != NULL && student->int_nb_courses > 0) 
        {
            sum_averages = 0.0f;
            sum_coefs = 0.0f;
            
            /* Calculate the weighted sum of course averages */
            for (j = 0; j < student->int_nb_courses; j++) 
            {
                /* Sum of averages multiplied by their coefficients */
                sum_averages += student->course_courses[j].float_average * student->course_courses[j].float_coef;
                
                /* Sum of coefficients */
                sum_coefs += student->course_courses[j].float_coef;
            }
            
            /* Calculate the weighted overall average */
            student->float_average = sum_averages / sum_coefs;
        } 
        else 
{
            /* No courses: set average to 0 */
            student->float_average = 0.0f;
        }
    }
}