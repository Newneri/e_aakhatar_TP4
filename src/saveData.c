/*!
 * \file saveData.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Data loading module from a file
 * 
 * This file contains the implementation of reading and storing 
 * data (students, courses, grades) from the data.txt file.
 */

#include "saveData.h"
#include "update.h"

/*!
 * \fn Prom get_all_students(FILE* file)
 * \brief Reads all students from the file
 * \param file Pointer to the data file
 * \return Prom structure containing all students
 */
void get_all_students(FILE* file, Prom* prom) 
{
    char* line;
    Student student;
        
    /* Position to the ETUDIANTS section */
    line = get_to_type(file, "ETUDIANTS");

    /* Read all student lines */
    while (line != NULL && strlen(line) > 0) 
    {
        /* Parse the line to create a student */
        student = parse_student_line(line);
        
        /* Reallocate the students array to add the new student */
        prom->student_students = (Student*)realloc(prom->student_students, (prom->int_nb_students + 1) * sizeof(Student));
        
        /* Add the student to the array */
        prom->student_students[prom->int_nb_students] = student;
        
        /* Increment the number of students */
        prom->int_nb_students++;
        
        /* Free the line and read the next one */
        free(line);
        line = read_line(file);
    }
}


/*!
 * \fn void get_all_courses(FILE* file, Prom* prom)
 * \brief Reads all courses and assigns them to each student
 * \param file Pointer to the data file
 * \param prom Pointer to the cohort containing the students
 */
void get_all_courses(FILE* file, Prom* prom)
{
    char* line;
    char name[128];
    float coef;
    size_t i;
    Course new_course;
    
    /* Position to the MATIERES section */
    line = get_to_type(file, "MATIERES");

    /* Read all course lines */
    while (line != NULL && strlen(line) > 0)
    {
        /* Extract the course name and coefficient */
        sscanf(line, "%[^;];%f", name, &coef);
        
        /* Assign the course to each student */
        for (i = 0; i < prom->int_nb_students; i++)
        {
            /* Reallocate the student's courses array */
            prom->student_students[i].course_courses = (Course*)realloc(
                prom->student_students[i].course_courses, 
                (prom->student_students[i].int_nb_courses + 1) * sizeof(Course)
            );
            
            /* Create a new course (deep copy) */
            new_course = create_course(name, coef, 0);
            
            /* Add the course to the student's array */
            prom->student_students[i].course_courses[prom->student_students[i].int_nb_courses] = new_course;
            
            /* Increment the student's number of courses */
            prom->student_students[i].int_nb_courses++;
        }
        
        /* Free the line and read the next one */
        free(line);
        line = read_line(file);
    }
}


/*!
 * \fn void get_all_grades(FILE* file, Prom* prom)
 * \brief Reads all grades and assigns them to students in their respective courses
 * \param file Pointer to the data file
 * \param prom Pointer to the cohort containing the students
 */
void get_all_grades(FILE* file, Prom* prom)
{
    char* line;
    int student_id;
    char course_name[128];
    float grade;
    int i;
    int j;
    Student* student;
    Course* course;
    int n;
    
    /* Position to the NOTES section */
    line = get_to_type(file, "NOTES");

    /* Read all grade lines */
    while (line != NULL && strlen(line) > 0) 
    {
        /* Extract student ID, course name and grade */
        if (sscanf(line, "%d;%127[^;];%f", &student_id, course_name, &grade) == 3) 
        {
            /* Search for the corresponding student */
            for (i = 0; i < prom->int_nb_students; i++) 
            {
                student = &prom->student_students[i];
                
                /* If the ID matches */
                if (student->int_id == student_id) 
                {
                    /* Search for the corresponding course */
                    for (j = 0; j < student->int_nb_courses; j++) 
                    {
                        course = &student->course_courses[j];
                        
                        /* If the course name matches */
                        if (strcmp(course->char_course_name, course_name) == 0) 
                        {
                            /* Get the current number of grades */
                            n = course->grades.int_nb_grades;
                            
                            /* Reallocate the grades array to add the new one */
                            course->grades.tab_grades = (float*)realloc(
                                course->grades.tab_grades, 
                                (n + 1) * sizeof(float)
                            );
                            
                            /* Check if allocation was successful */
                            if (course->grades.tab_grades != NULL) 
                            {
                                /* Add the grade to the array */
                                course->grades.tab_grades[n] = grade;
                                
                                /* Increment the number of grades */
                                course->grades.int_nb_grades++;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        /* Free the line and read the next one */
        free(line);
        line = read_line(file);
    }

    /* Update all course averages */
    update_course_average(prom);
    
    /* Update all student overall averages */
    update_student_average(prom);
    
    /* Free the last line if necessary */
    if (line != NULL) 
    {
        free(line);
    }
}
