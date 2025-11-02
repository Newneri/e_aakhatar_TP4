/*!
 * \file saveData.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Module de chargement des données depuis un fichier
 * 
 * Ce fichier contient l'implémentation des fonctions de lecture et stockage 
 * des données (étudiants, matières, notes) depuis le fichier data.txt.
 */

#include "saveData.h"
#include "update.h"

/*!
 * \fn Prom get_all_students(FILE* file)
 * \brief Lit tous les étudiants depuis le fichier
 * \param file Pointeur vers le fichier de données
 * \return Structure Prom contenant tous les étudiants
 */
void get_all_students(FILE* file, Prom* prom) 
{
    char* line;
    Student student;
        
    /* Positionnement sur la section ETUDIANTS */
    line = get_to_type(file, "ETUDIANTS");

    /* Lecture de toutes les lignes d'étudiants */
    while (line != NULL && strlen(line) > 0) 
    {
        /* Parsing de la ligne pour créer un étudiant */
        student = parse_student_line(line);
        
        /* Réallocation du tableau d'étudiants pour ajouter le nouvel étudiant */
        prom->student_students = (Student*)realloc(prom->student_students, (prom->int_nb_students + 1) * sizeof(Student));
        
        /* Ajout de l'étudiant dans le tableau */
        prom->student_students[prom->int_nb_students] = student;
        
        /* Incrémentation du nombre d'étudiants */
        prom->int_nb_students++;
        
        /* Libération de la ligne et lecture de la suivante */
        free(line);
        line = read_line(file);
    }
}


/*!
 * \fn void get_all_courses(FILE* file, Prom* prom)
 * \brief Lit toutes les matières et les attribue à chaque étudiant
 * \param file Pointeur vers le fichier de données
 * \param prom Pointeur vers la promotion contenant les étudiants
 */
void get_all_courses(FILE* file, Prom* prom)
{
    char* line;
    char name[128];
    float coef;
    size_t i;
    Course new_course;
    
    /* Positionnement sur la section MATIERES */
    line = get_to_type(file, "MATIERES");

    /* Lecture de toutes les lignes de matières */
    while (line != NULL && strlen(line) > 0)
    {
        /* Extraction du nom et du coefficient de la matière */
        sscanf(line, "%[^;];%f", name, &coef);
        
        /* Attribution de la matière à chaque étudiant */
        for (i = 0; i < prom->int_nb_students; i++)
        {
            /* Réallocation du tableau de matières de l'étudiant */
            prom->student_students[i].course_courses = (Course*)realloc(
                prom->student_students[i].course_courses, 
                (prom->student_students[i].int_nb_courses + 1) * sizeof(Course)
            );
            
            /* Création d'une nouvelle matière (copie profonde) */
            new_course = create_course(name, coef, 0);
            
            /* Ajout de la matière au tableau de l'étudiant */
            prom->student_students[i].course_courses[prom->student_students[i].int_nb_courses] = new_course;
            
            /* Incrémentation du nombre de matières de l'étudiant */
            prom->student_students[i].int_nb_courses++;
        }
        
        /* Libération de la ligne et lecture de la suivante */
        free(line);
        line = read_line(file);
    }
}


/*!
 * \fn void get_all_grades(FILE* file, Prom* prom)
 * \brief Lit toutes les notes et les attribue aux étudiants dans leurs matières respectives
 * \param file Pointeur vers le fichier de données
 * \param prom Pointeur vers la promotion contenant les étudiants
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
    
    /* Positionnement sur la section NOTES */
    line = get_to_type(file, "NOTES");

    /* Lecture de toutes les lignes de notes */
    while (line != NULL && strlen(line) > 0) 
    {
        /* Extraction de l'ID étudiant, nom de matière et note */
        if (sscanf(line, "%d;%127[^;];%f", &student_id, course_name, &grade) == 3) 
        {
            /* Recherche de l'étudiant correspondant */
            for (i = 0; i < prom->int_nb_students; i++) 
            {
                student = &prom->student_students[i];
                
                /* Si l'ID correspond */
                if (student->int_id == student_id) 
                {
                    /* Recherche de la matière correspondante */
                    for (j = 0; j < student->int_nb_courses; j++) 
                    {
                        course = &student->course_courses[j];
                        
                        /* Si le nom de matière correspond */
                        if (strcmp(course->char_course_name, course_name) == 0) 
                        {
                            /* Récupération du nombre actuel de notes */
                            n = course->grades.int_nb_grades;
                            
                            /* Réallocation du tableau de notes pour ajouter la nouvelle */
                            course->grades.tab_grades = (float*)realloc(
                                course->grades.tab_grades, 
                                (n + 1) * sizeof(float)
                            );
                            
                            /* Vérification de la réussite de l'allocation */
                            if (course->grades.tab_grades != NULL) 
                            {
                                /* Ajout de la note dans le tableau */
                                course->grades.tab_grades[n] = grade;
                                
                                /* Incrémentation du nombre de notes */
                                course->grades.int_nb_grades++;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        /* Libération de la ligne et lecture de la suivante */
        free(line);
        line = read_line(file);
    }

    /* Mise à jour de toutes les moyennes des matières */
    update_course_average(prom);
    
    /* Mise à jour de toutes les moyennes générales des étudiants */
    update_student_average(prom);
    
    /* Libération de la dernière ligne si nécessaire */
    if (line != NULL) 
    {
        free(line);
    }
}
