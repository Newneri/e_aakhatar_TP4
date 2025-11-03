/*!
 * \file init.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Module for constructing and destroying data structures
 * 
 * This file contains the implementation of creation (constructors) 
 * and destruction (destructors) functions for the Grades, Course, Student and Prom structures.
 */

#include "init.h"
#include <string.h>

/*!
 * \fn Grades create_grades(int int_nb_grades)
 * \brief Creates a Grades structure with dynamic allocation
 * \param int_nb_grades Number of grades to allocate
 * \return Initialized Grades structure with grades set to 0.0
 */
Grades create_grades(int int_nb_grades) 
{
    Grades grades;
    int i;
    
    /* Initialize the number of grades */
    grades.int_nb_grades = int_nb_grades;
    
    /* Dynamic allocation of the grades array */
    grades.tab_grades = (float*)malloc(int_nb_grades * sizeof(float));
    
    /* Check if allocation was successful */
    if (grades.tab_grades != NULL) 
    {
        /* Initialize all grades to 0.0 */
        for (i = 0; i < int_nb_grades; i++) 
        {
            grades.tab_grades[i] = 0.0f;
        }
    }
    
    return (grades);
}


/*!
 * \fn Course create_course(const char* char_course_name, float float_coef, int int_nb_grades)
 * \brief Creates a Course structure with dynamic allocation
 * \param char_course_name Name of the course
 * \param float_coef Coefficient of the course
 * \param int_nb_grades Number of grades to allocate
 * \return Initialized Course structure
 */
Course create_course(const char* char_course_name, float float_coef, int int_nb_grades) 
{
    Course course;
    
    /* Duplicate the course name (dynamic allocation + copy) */
    course.char_course_name = strdup(char_course_name);
    
    /* Initialize the coefficient */
    course.float_coef = float_coef;
    
    /* Create the associated Grades structure */
    course.grades = create_grades(int_nb_grades);
    
    /* Initialize the average to 0 */
    course.float_average = 0.0f;
    
    return (course);
}

/*!
 * \fn Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses)
 * \brief Creates a Student structure with dynamic allocation
 * \param int_id Unique identifier of the student
 * \param char_last_name Last name of the student
 * \param char_first_name First name of the student
 * \param int_age Age of the student
 * \param int_nb_courses Number of courses to allocate
 * \return Initialized Student structure
 */
Student create_student(int int_id, const char* char_last_name, const char* char_first_name, int int_age, int int_nb_courses) 
{
    Student student;
    
    /* Initialize the identifier */
    student.int_id = int_id;
    
    /* Duplicate the last name (dynamic allocation + copy) */
    student.char_last_name = strdup(char_last_name);
    
    /* Duplicate the first name (dynamic allocation + copy) */
    student.char_first_name = strdup(char_first_name);
    
    /* Initialize the age */
    student.int_age = int_age;
    
    /* Initialize the number of courses */
    student.int_nb_courses = int_nb_courses;
    
    /* Dynamic allocation of the courses array */
    student.course_courses = (Course*)malloc(int_nb_courses * sizeof(Course));
    
    /* Initialize the overall average to 0 */
    student.float_average = 0.0f;
    
    return (student);
}

/*!
 * \fn Prom create_prom(int int_nb_students)
 * \brief Creates a Prom (cohort) structure with dynamic allocation
 * \param int_nb_students Number of students to allocate
 * \return Initialized Prom structure
 */
Prom create_prom(int int_nb_students) 
{
    Prom prom;
    
    /* Initialize the number of students */
    prom.int_nb_students = int_nb_students;
    
    /* Dynamic allocation of the students array */
    prom.student_students = (Student*)malloc(int_nb_students * sizeof(Student));
    
    return (prom);
}


/*!
 * \fn void destroy_grades(Grades* grades)
 * \brief Frees the memory allocated for a Grades structure
 * \param grades Pointer to the Grades structure to destroy
 */
void destroy_grades(Grades* grades) 
{
    /* Check if the grades array exists */
    if (grades->tab_grades != NULL) 
    {
        /* Free the array memory */
        free(grades->tab_grades);
        
        /* Set pointer to NULL to avoid double free */
        grades->tab_grades = NULL;
    }
    
    /* Reset the number of grades */
    grades->int_nb_grades = 0;
}

/*!
 * \fn void destroy_course(Course* course)
 * \brief Frees the memory allocated for a Course structure
 * \param course Pointer to the Course structure to destroy
 */
void destroy_course(Course* course) 
{
    /* Check if the course name exists */
    if (course->char_course_name != NULL) 
    {
        /* Free the name memory */
        free(course->char_course_name);
        
        /* Set pointer to NULL to avoid double free */
        course->char_course_name = NULL;
    }
    
    /* Destroy the associated Grades structure */
    destroy_grades(&course->grades);
    
    /* Reset the coefficient */
    course->float_coef = 0.0f;
    
    /* Reset the average */
    course->float_average = 0.0f;
}


/*!
 * \fn void destroy_student(Student* student)
 * \brief Frees the memory allocated for a Student structure
 * \param student Pointer to the Student structure to destroy
 */
void destroy_student(Student* student) 
{
    int i;
    
    /* Check and free the last name */
    if (student->char_last_name != NULL) 
    {
        free(student->char_last_name);
        student->char_last_name = NULL;
    }
    
    /* Check and free the first name */
    if (student->char_first_name != NULL) 
    {
        free(student->char_first_name);
        student->char_first_name = NULL;
    }
    
    /* Check if the courses array exists */
    if (student->course_courses != NULL) 
    {
        /* Destroy each course in the array */
        for (i = 0; i < student->int_nb_courses; i++) 
        {
            destroy_course(&student->course_courses[i]);
        }
        
        /* Free the courses array */
        free(student->course_courses);
        
        /* Set pointer to NULL to avoid double free */
        student->course_courses = NULL;
    }
    
    /* Reset all numeric fields */
    student->int_id = 0;
    student->int_age = 0;
    student->int_nb_courses = 0;
    student->float_average = 0.0f;
}

/*!
 * \fn void destroy_prom(Prom* prom)
 * \brief Frees the memory allocated for a Prom structure
 * \param prom Pointer to the Prom structure to destroy
 */
void destroy_prom(Prom* prom) 
{
    int i;
    
    /* Check if the students array exists */
    if (prom->student_students != NULL) 
    {
        /* Destroy each student in the array */
        for (i = 0; i < prom->int_nb_students; i++) 
        {
            destroy_student(&prom->student_students[i]);
        }
        
        /* Free the students array */
        free(prom->student_students);
        
        /* Set pointer to NULL to avoid double free */
        prom->student_students = NULL;
    }
    
    /* Reset the number of students */
    prom->int_nb_students = 0;
}

