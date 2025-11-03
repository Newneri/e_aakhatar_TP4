/*!
 * \file read.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief File reading module
 * 
 * This file contains the implementation of functions for reading and parsing
 * the data file (students, courses, grades).
 */

#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "init.h"
#include "update.h"

/*!
 * \fn char* read_line(FILE* file)
 * \brief Reads a complete line from a file with dynamic allocation
 * \param file Pointer to the file to read
 * \return String containing the read line (to be freed by the caller)
 */
char* read_line(FILE* file) 
{
    size_t size;
    size_t len;
    char *buffer;
    int c;
    char *new_buffer;
    
    size = 128;
    len = 0;
    
    /* Initial buffer allocation */
    buffer = malloc(size);
    if (!buffer) 
    {
        return (NULL);
    }

    /* Read character by character until end of line */
    while ((c = fgetc(file)) != EOF && c != '\n') 
    {
        buffer[len++] = (char)c;
        
        /* Reallocation if buffer is too small */
        if (len >= size) 
        {
            size *= 2;
            new_buffer = realloc(buffer, size);
            if (!new_buffer) 
            {
                free(buffer);
                return (NULL);
            }
            buffer = new_buffer;
        }
    }
    
    /* If no character was read and EOF reached */
    if (len == 0 && c == EOF) 
    {
        free(buffer);
        return (NULL);
    }
    
    /* Add string terminator */
    buffer[len] = '\0';
    
    return (buffer);
}


/*!
 * \fn char* get_to_type(FILE* file, char* type)
 * \brief Positions in the file at the specified section
 * \param file Pointer to the file
 * \param type Name of the section to search for (e.g., "ETUDIANTS", "MATIERES", "NOTES")
 * \return First data line after the found section
 */
char* get_to_type(FILE* file, char* type)
{
    char* line;
    int found;
    
    line = NULL;
    found = 0;

    /* Search for the section in the file */
    while ((line = read_line(file)) != NULL) 
    {
        /* Comparison with the searched type */
        if (strcmp(line, type) == 0) 
        {
            found = 1;
            free(line);
            
            /* Skip the header line (e.g., "numero;prenom;nom;age") */
            line = read_line(file);
            break;
        }
        free(line);
    }
    
    /* Display if the section was not found */
    if (!found) 
    {
        printf("%s not found in file\n", type);
    }
    
    /* Read the first data line */
    line = read_line(file);
    
    return (line);
}

/*!
 * \fn Course parse_course_line(const char* line)
 * \brief Parses a file line to create a Course structure
 * \param line Line in format "name;coefficient"
 * \return Initialized Course structure
 */
Course parse_course_line(const char* line) 
{
    char name[128];
    float coef;
    
    /* Extract name and coefficient from the line */
    sscanf(line, "%[^;];%f", name, &coef);
    
    /* Create and return the Course structure */
    return (create_course(name, coef, 0));
}

/*!
 * \fn Student parse_student_line(const char* line)
 * \brief Parses a file line to create a Student structure
 * \param line Line in format "id;firstname;lastname;age"
 * \return Initialized Student structure
 */
Student parse_student_line(const char* line) 
{
    int id;
    int age;
    char first_name[128];
    char last_name[128];
    
    /* Extract data from the line */
    sscanf(line, "%d;%127[^;];%127[^;];%d", &id, first_name, last_name, &age);
    
    /* Create and return the Student structure */
    return (create_student(id, last_name, first_name, age, 0));
}
