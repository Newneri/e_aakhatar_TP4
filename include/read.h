/*!
 * \file read.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Interface for file reading module
 * 
 * This file contains the prototypes of functions to read
 * and parse data from a formatted text file.
 */

#include "init.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

#ifndef READ_H
#define READ_H

/*!
 * \fn char* read_line(FILE* file)
 * \brief Reads a complete line from a file
 * \param file Pointer to the file to read
 * \return Pointer to the read string (dynamic allocation) or NULL if end of file
 * \pre file != NULL
 */
char* read_line(FILE* file);

/*!
 * \fn char* get_to_type(FILE* file, char* type)
 * \brief Navigates through the file until finding a section separator
 * \param file Pointer to the file to read
 * \param type Name of the section to find (e.g., "ETUDIANTS", "MATIERES", "NOTES")
 * \return Pointer to the first data line after the separator
 * \pre file != NULL
 * \pre type != NULL
 */
char* get_to_type(FILE* file, char* type);

/*!
 * \fn Course parse_course_line(const char* line)
 * \brief Parses a data line to create a Course structure
 * \param line Line to parse in format "name;coefficient"
 * \return Course structure created from the line
 * \pre line != NULL
 */
Course parse_course_line(const char* line);

/*!
 * \fn Student parse_student_line(const char* line)
 * \brief Parses a data line to create a Student structure
 * \param line Line to parse in format "id;firstname;lastname;age"
 * \return Student structure created from the line
 * \pre line != NULL
 */
Student parse_student_line(const char* line);

#endif
