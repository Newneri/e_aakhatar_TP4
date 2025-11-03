/*!
 * \file structures.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Data structure definitions for the project
 * 
 * This file contains the definitions of the Grades, Course, Student and Prom
 * structures used for managing a student cohort with their courses and grades.
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

/*!
 * \struct Grades
 * \brief Structure representing a set of grades
 */
typedef struct 
{
    float* tab_grades;        /*!< Dynamic array of grades */
    int int_nb_grades;        /*!< Number of grades in the array */
} Grades;

/*!
 * \struct Course
 * \brief Structure representing a course (subject)
 */
typedef struct 
{
    Grades grades;            /*!< Grades for the course */
    char *char_course_name;   /*!< Name of the course */
    float float_coef;         /*!< Coefficient of the course */
    float float_average;      /*!< Average grade for the course */
    int int_nb_grades;        /*!< Number of grades */
} Course;

/*!
 * \struct Student
 * \brief Structure representing a student
 */
typedef struct 
{
    int int_id;               /*!< Unique identifier of the student */
    char *char_last_name;     /*!< Last name */
    char *char_first_name;    /*!< First name */
    int int_age;              /*!< Age of the student */
    int int_nb_courses;       /*!< Number of courses taken */
    Course *course_courses;   /*!< Dynamic array of courses */
    float float_average;      /*!< Overall average of the student */
} Student;

/*!
 * \struct Prom
 * \brief Structure representing a student cohort
 */
typedef struct 
{
    int int_nb_students;      /*!< Number of students in the cohort */
    Student *student_students; /*!< Dynamic array of students */
} Prom;


#endif