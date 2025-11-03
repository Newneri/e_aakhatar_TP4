/*!
* \file sorting.c
* \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
* \version 1.0
* \date November 3, 2025
* \brief Implementation of student sorting module
* 
* This file contains the implementation of functions to sort
* students in a promotion according to their grades.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"
#include "show.h"

/*!
* \fn void sort_students_by_average(Prom* prom)
* \brief Sorts students by descending average
* 
* This function sorts the student array of a promotion
* in descending order of average using selection sort algorithm.
* 
* \param prom Pointer to the Prom structure containing students
*/
void sort_students_by_average(Prom* prom) {
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students <= 1) {
        return;
    }

    /* Selection sort (descending order) */
    for (int i = 0; i < prom->int_nb_students - 1; i++) {
        int max_idx = i;
        
        /* Find the student with the highest average */
        for (int j = i + 1; j < prom->int_nb_students; j++) {
            if (prom->student_students[j].float_average > prom->student_students[max_idx].float_average) {
                max_idx = j;
            }
        }
        
        /* Swap if necessary */
        if (max_idx != i) {
            Student temp = prom->student_students[i];
            prom->student_students[i] = prom->student_students[max_idx];
            prom->student_students[max_idx] = temp;
        }
    }
}

/*!
* \fn void sort_students_from_course(Prom* prom, char* course_name)
* \brief Sorts students by average in a specific subject
* 
* This function sorts the students of a promotion according to
* their average in a given subject and displays the top three.
* 
* \param prom Pointer to the Prom structure containing students
* \param course_name Name of the subject for sorting
*/
void sort_students_from_course(Prom* prom, char* course_name) {
    if (prom == NULL || prom->student_students == NULL || prom->int_nb_students == 0 || course_name == NULL) {
        exit(EXIT_FAILURE);
    }
    
    /* Create copy of students array for sorting */
    Student *students_copy = malloc(prom->int_nb_students * sizeof(Student));
    if (students_copy == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < prom->int_nb_students; i++){
        students_copy[i] = prom->student_students[i];
    }
    
    /* Selection sort (descending order) */
    for (int i = 0; i < prom->int_nb_students - 1; i++){
        int max_idx = i;
        
        /* Find the grade of the student at index max_idx */
        float avg_max = -1.0f;
        for (int k = 0; k < students_copy[max_idx].int_nb_courses; k++) {
            if (strcmp(students_copy[max_idx].course_courses[k].char_course_name, course_name) == 0) {
                avg_max = students_copy[max_idx].course_courses[k].float_average;
                break;
            }
        }

        for(int j = i + 1; j < prom->int_nb_students; j++) {
            /* Search for student j's grade in the subject */
            float avg_j = -1.0f;
            for (int k = 0; k < students_copy[j].int_nb_courses; k++) {
                if (strcmp(students_copy[j].course_courses[k].char_course_name, course_name) == 0) {
                    avg_j = students_copy[j].course_courses[k].float_average;
                    break;
                }
            }

            /* Compare averages */
            if (avg_j > avg_max) {
                max_idx = j;
                avg_max = avg_j;
            }
        }

        /* Swap if necessary */
        if (max_idx != i) {
            Student temp = students_copy[i];
            students_copy[i] = students_copy[max_idx];
            students_copy[max_idx] = temp;  
        }
    }
    
    printf("\n===============================================\n");
    printf("          TOP 3 STUDENTS IN %s         \n", course_name);
    printf("===============================================\n");
    
    for (int i = 0; i < 3; i++) {
        printf("\n[Top Student %d/%d]\n", i + 1, 3);
        printf("Grade in %s: ", course_name);
        /* Search for the subject in the student's courses */
        for (int k = 0; k < students_copy[i].int_nb_courses; k++) {
            if (strcmp(students_copy[i].course_courses[k].char_course_name, course_name) == 0) {
                printf("%.2f\n", students_copy[i].course_courses[k].float_average);
                break;
            }
        }
        show_student_info(students_copy[i]);
    }

    free(students_copy);
}
