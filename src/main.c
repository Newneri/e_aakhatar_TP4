/*!
 * \file main.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date November 2, 2025
 * \brief Main program for managing students and their grades
 * 
 * This file contains the main function that loads data from a file,
 * displays student information with their averages, and frees memory.
 */

#include "read.h"
#include "init.h"
#include "structures.h"
#include "saveData.h"
#include "binary.h"
#include "show.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \fn int main(int argc, char** argv)
 * \brief Main function of the program
 * \param argc Number of command line arguments
 * \param argv Array of command line arguments
 * \return 0 if success, 1 on error
 * 
 * This function:
 * - Opens the data file
 * - Loads students, courses and grades
 * - Displays complete information
 * - Sorts students by average and by course
 * - Saves the promotion to a binary file
 * - Frees all allocated memory
 */
int main(int argc, char** argv) 
{
    const char* filename = "data.txt";
    FILE* file;
    Prom prom;
    
    /* Opening the data file for reading */
    file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Error: Cannot open file %s\n", filename);
        return (1);
    }

    /* Initializing the Prom structure */
    printf("Initializing promotion...\n");
    prom = create_prom(0);

    /* Loading all students from the file */
    printf("Loading students...\n");
    get_all_students(file, &prom);
    
    /* Loading all courses for each student */
    printf("Loading courses...\n");
    get_all_courses(file, &prom);

    /* Loading all grades and calculating averages */
    printf("Loading grades and calculating averages...\n");
    get_all_grades(file, &prom);

    /* Closing the file */
    fclose(file);
    
    /* Sorting students by descending average */
    printf("Sorting students by average...\n");
    sort_students_by_average(&prom);

    /* Displaying the promotion */
    printf("Displaying promotion information...\n");
    show_prom(prom);

    /* Displaying the top 10 students */    
    printf("\n\nDisplaying top 10 students by average...\n");
    show_best(prom.student_students, 10);

    /* Sorting and displaying top 3 students in "Mathematics" */
    printf("\n\nSorting and displaying top 3 students in Mathematics...\n");
    sort_students_from_course(&prom, "Mathematiques");

    /* Saving the promotion to the binary file */
    printf("\n\nSaving promotion to binary file...\n");
    if (save_prom_binary("promotion.bin", &prom) != 0)
    {
        printf("Error: Failed to save promotion to binary file.\n");
    } else {
        printf("Promotion saved successfully to binary file: promotion.bin\n");
    }

    /* Freeing all allocated memory */
    printf("Freeing memory...\n");
    destroy_prom(&prom);

    /* Loading the promotion back from the binary file for verification */
    printf("Loading promotion from binary file for verification...\n");
    prom = load_prom_binary("promotion.bin");

    /* Displaying the loaded promotion */
    printf("Displaying some of the promotion information...\n");
    show_best(prom.student_students, 3);
    return (0);
}