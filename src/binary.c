/*!
 * \file binary.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Binary save/restore module for student cohorts
 * 
 * This file contains the implementation of functions allowing to save
 * and restore a complete cohort in a binary file.
 */

#include "binary.h"
#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \fn int save_prom_binary(const char* str_filename, Prom* prom)
 * \brief Saves a complete cohort to a binary file
 * \param str_filename Name of the destination binary file
 * \param prom Pointer to the Prom structure to save
 * \return 0 if success, -1 in case of error
 */
int save_prom_binary(const char* str_filename, Prom* prom)
{
    FILE* file;
    int i;
    int j;
    int str_len;
    
    /* Parameter verification */
    if (str_filename == NULL || prom == NULL)
    {
        return (-1);
    }
    
    /* Open file in binary write mode */
    file = fopen(str_filename, "wb");
    if (file == NULL)
    {
        return (-1);
    }
    
    /* Write the number of students in the cohort */
    fwrite(&prom->int_nb_students, sizeof(int), 1, file);
    
    /* Loop through all students */
    for (i = 0; i < prom->int_nb_students; i++)
    {
        Student* student = &prom->student_students[i];
        
        /* Write student's basic information */
        fwrite(&student->int_id, sizeof(int), 1, file);
        fwrite(&student->int_age, sizeof(int), 1, file);
        fwrite(&student->float_average, sizeof(float), 1, file);
        fwrite(&student->int_nb_courses, sizeof(int), 1, file);
        
        /* Write last name (length + string) */
        str_len = strlen(student->char_last_name) + 1;
        fwrite(&str_len, sizeof(int), 1, file);
        fwrite(student->char_last_name, sizeof(char), str_len, file);
        
        /* Write first name (length + string) */
        str_len = strlen(student->char_first_name) + 1;
        fwrite(&str_len, sizeof(int), 1, file);
        fwrite(student->char_first_name, sizeof(char), str_len, file);
        
        /* Loop through all student's courses */
        for (j = 0; j < student->int_nb_courses; j++)
        {
            Course* course = &student->course_courses[j];
            
            /* Write course information */
            fwrite(&course->float_coef, sizeof(float), 1, file);
            fwrite(&course->float_average, sizeof(float), 1, file);
            
            /* Write course name (length + string) */
            str_len = strlen(course->char_course_name) + 1;
            fwrite(&str_len, sizeof(int), 1, file);
            fwrite(course->char_course_name, sizeof(char), str_len, file);
            
            /* Write number of grades */
            fwrite(&course->grades.int_nb_grades, sizeof(int), 1, file);
            
            /* Write all course grades */
            if (course->grades.int_nb_grades > 0)
            {
                fwrite(course->grades.tab_grades, sizeof(float), 
                       course->grades.int_nb_grades, file);
            }
        }
    }
    
    /* Close file */
    fclose(file);
    
    return (0);
}

/*!
 * \fn Prom load_prom_binary(const char* str_filename)
 * \brief Restores a cohort from a binary file
 * \param str_filename Name of the source binary file
 * \return Restored Prom structure, or empty structure in case of error
 */
Prom load_prom_binary(const char* str_filename)
{
    FILE* file;
    Prom prom;
    int i;
    int j;
    int str_len;
    char buffer[256];
    
    /* Parameter verification */
    if (str_filename == NULL)
    {
        prom.int_nb_students = 0;
        prom.student_students = NULL;
        return (prom);
    }
    
    /* Open file in binary read mode */
    file = fopen(str_filename, "rb");
    if (file == NULL)
    {
        printf("Error: Cannot open binary file %s\n", str_filename);
        prom.int_nb_students = 0;
        prom.student_students = NULL;
        return (prom);
    }
    
    /* Read number of students */
    fread(&prom.int_nb_students, sizeof(int), 1, file);
    
    /* Allocate student array */
    prom.student_students = (Student*)malloc(prom.int_nb_students * sizeof(Student));
    if (prom.student_students == NULL)
    {
        fclose(file);
        prom.int_nb_students = 0;
        return (prom);
    }
    
    /* Loop through all students */
    for (i = 0; i < prom.int_nb_students; i++)
    {
        Student* student = &prom.student_students[i];
        
        /* Read student's basic information */
        fread(&student->int_id, sizeof(int), 1, file);
        fread(&student->int_age, sizeof(int), 1, file);
        fread(&student->float_average, sizeof(float), 1, file);
        fread(&student->int_nb_courses, sizeof(int), 1, file);
        
        /* Read last name */
        fread(&str_len, sizeof(int), 1, file);
        fread(buffer, sizeof(char), str_len, file);
        student->char_last_name = strdup(buffer);
        
        /* Read first name */
        fread(&str_len, sizeof(int), 1, file);
        fread(buffer, sizeof(char), str_len, file);
        student->char_first_name = strdup(buffer);
        
        /* Allocate course array */
        student->course_courses = (Course*)malloc(student->int_nb_courses * sizeof(Course));
        
        /* Loop through all student's courses */
        for (j = 0; j < student->int_nb_courses; j++)
        {
            Course* course = &student->course_courses[j];
            
            /* Read course information */
            fread(&course->float_coef, sizeof(float), 1, file);
            fread(&course->float_average, sizeof(float), 1, file);
            
            /* Read course name */
            fread(&str_len, sizeof(int), 1, file);
            fread(buffer, sizeof(char), str_len, file);
            course->char_course_name = strdup(buffer);
            
            /* Read number of grades */
            fread(&course->grades.int_nb_grades, sizeof(int), 1, file);
            
            /* Allocate and read grades */
            if (course->grades.int_nb_grades > 0)
            {
                course->grades.tab_grades = (float*)malloc(course->grades.int_nb_grades * sizeof(float));
                fread(course->grades.tab_grades, sizeof(float), course->grades.int_nb_grades, file);
            }
            else
            {
                course->grades.tab_grades = NULL;
            }
        }
    }
    
    /* Close file */
    fclose(file);
    
    printf("Promotion loaded successfully from binary file: %s\n", str_filename);
    return (prom);
}