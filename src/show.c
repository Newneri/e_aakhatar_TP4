/*!
 * \file show.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Data structure display module
 * 
 * This file contains the implementation of functions allowing to display
 * in a formatted way the Grades, Course, Student and Prom structures.
 */

#include <stdio.h>
#include <stdlib.h> 
#include "structures.h"
#include "show.h"

/*!
 * \fn void show_grades(Grades grades)
 * \brief Displays all grades from a Grades structure
 * \param grades Grades structure to display
 */
void show_grades(Grades grades)
{
    int i;
    
    /* Check if grades exist */
    if (grades.int_nb_grades == 0)
    {
        printf("      No grades available\n");
        return;
    }
    
    /* Display the number of grades */
    printf("  |    Grades (%d): ", grades.int_nb_grades);
    
    /* Display each grade separated by a comma */
    for (i = 0; i < grades.int_nb_grades; i++)
    {
        printf("%.2f", grades.tab_grades[i]);
        
        /* Add a comma except for the last grade */
        if (i < grades.int_nb_grades - 1)
        {
            printf("; ");
        }
    }
    printf("\n");
}

/*!
 * \fn void show_course(Course course)
 * \brief Displays complete information of a course
 * \param course Course structure to display
 */
void show_course(Course course)
{
    printf("  |  - %s (Coef: %.2f, Avg: %.2f)\n",
           course.char_course_name,
           course.float_coef,
           course.float_average);
    
    /* Display all grades of the course */
    show_grades(course.grades);
}


/*!
 * \fn void show_student(Student student)
 * \brief Displays complete information of a student
 * \param student Student structure to display
 */
void show_student(Student student)
{
    int i;
    /* Display student's basic information */
    show_student_info(student);
    
    /* Check if there are any courses */
    if (student.int_nb_courses == 0)
    {
        printf("  No courses enrolled\n");
        return;
    }
    
    /* Display all student's courses */
    printf("\n  Courses Details:\n");
    for (i = 0; i < student.int_nb_courses; i++)
    {
        printf("\n  [Course %d/%d]\n", i + 1, student.int_nb_courses);
        show_course(student.course_courses[i]);
    }
}

void show_student_info(Student student)
{
    /* Display student's basic information */
    printf("\n  ========================================\n");
    printf("  Student ID: %d\n", student.int_id);
    printf("  Name: %s %s\n", student.char_first_name, student.char_last_name);
    printf("  Age: %d years old\n", student.int_age);
    printf("  Overall Average: %.2f\n", student.float_average);
    printf("  Number of Courses: %d\n", student.int_nb_courses);
    printf("  ========================================\n");
}

/*!
 * \fn void show_prom(Prom prom)
 * \brief Displays complete information of a cohort
 * \param prom Prom structure to display
 */
void show_prom(Prom prom)
{
    int i;
    
    /* Display cohort header */
    printf("\n");
    printf("===============================================\n");
    printf("          PROMOTION INFORMATION                \n");
    printf("===============================================\n");
    printf("Total Students: %d\n", prom.int_nb_students);
    printf("===============================================\n");
    
    /* Check if there are any students */
    if (prom.int_nb_students == 0)
    {
        printf("\nNo students in this promotion\n");
        printf("===============================================\n\n");
        return;
    }
    
    /* Display each student in the cohort */
    for (i = 0; i < prom.int_nb_students; i++)
    {
        printf("\n[Student %d/%d]", i + 1, prom.int_nb_students);
        show_student(prom.student_students[i]);
    }
    
    /* Display footer */
    printf("\n");
    printf("===============================================\n");
    printf("          END OF PROMOTION DATA                \n");
    printf("===============================================\n\n");
}


/*!
 * \fn void show_best(Prom prom, int n)
 * \brief Displays the n best students of a cohort
 * \param prom Prom structure to display
 * \param n Number of students to display
 */
void show_best(Student* students, int n){
    int i;
    
    /* Display top students header */
    printf("\n");
    printf("===============================================\n");
    printf("          TOP %d STUDENTS BY AVERAGE         \n", n);
    printf("===============================================\n");
    
    /* Check if there are any students */
    if (n == 0)
    {
        printf("\nNo students \n");
        printf("===============================================\n\n");
        return;
    }
    
    /* Display the n best students */
    for (i = 0; i < n; i++)
    {
        printf("\n[Top Student %d/%d]", i + 1, n);
        show_student_info(students[i]);
    }
    
    /* Display footer */
    printf("\n");
    printf("===============================================\n");
    printf("          END OF TOP STUDENTS DATA             \n");
    printf("===============================================\n\n");
}