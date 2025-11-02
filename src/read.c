/*!
 * \file read.c
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Module de lecture de fichier
 * 
 * Ce fichier contient l'implémentation des fonctions de lecture et parsing 
 * du fichier de données (étudiants, matières, notes).
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
 * \brief Lit une ligne complète d'un fichier avec allocation dynamique
 * \param file Pointeur vers le fichier à lire
 * \return Chaîne de caractères contenant la ligne lue (à libérer par l'appelant)
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
    
    /* Allocation initiale du buffer */
    buffer = malloc(size);
    if (!buffer) 
    {
        return (NULL);
    }

    /* Lecture caractère par caractère jusqu'à la fin de ligne */
    while ((c = fgetc(file)) != EOF && c != '\n') 
    {
        buffer[len++] = (char)c;
        
        /* Réallocation si le buffer est trop petit */
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
    
    /* Si aucun caractère n'a été lu et EOF atteint */
    if (len == 0 && c == EOF) 
    {
        free(buffer);
        return (NULL);
    }
    
    /* Ajout du terminateur de chaîne */
    buffer[len] = '\0';
    
    return (buffer);
}


/*!
 * \fn char* get_to_type(FILE* file, char* type)
 * \brief Se positionne dans le fichier à la section spécifiée
 * \param file Pointeur vers le fichier
 * \param type Nom de la section à rechercher (ex: "ETUDIANTS", "MATIERES", "NOTES")
 * \return Première ligne de données après la section trouvée
 */
char* get_to_type(FILE* file, char* type)
{
    char* line;
    int found;
    
    line = NULL;
    found = 0;

    /* Recherche de la section dans le fichier */
    while ((line = read_line(file)) != NULL) 
    {
        /* Comparaison avec le type recherché */
        if (strcmp(line, type) == 0) 
        {
            found = 1;
            free(line);
            
            /* Saut de la ligne d'en-tête (ex: "numero;prenom;nom;age") */
            line = read_line(file);
            break;
        }
        free(line);
    }
    
    /* Affichage si la section n'a pas été trouvée */
    if (!found) 
    {
        printf("%s not found in file\n", type);
    }
    
    /* Lecture de la première ligne de données */
    line = read_line(file);
    
    return (line);
}

/*!
 * \fn Course parse_course_line(const char* line)
 * \brief Parse une ligne du fichier pour créer une structure Course
 * \param line Ligne au format "nom;coefficient"
 * \return Structure Course initialisée
 */
Course parse_course_line(const char* line) 
{
    char name[128];
    float coef;
    
    /* Extraction du nom et du coefficient depuis la ligne */
    sscanf(line, "%[^;];%f", name, &coef);
    
    /* Création et retour de la structure Course */
    return (create_course(name, coef, 0));
}

/*!
 * \fn Student parse_student_line(const char* line)
 * \brief Parse une ligne du fichier pour créer une structure Student
 * \param line Ligne au format "id;prenom;nom;age"
 * \return Structure Student initialisée
 */
Student parse_student_line(const char* line) 
{
    int id;
    int age;
    char first_name[128];
    char last_name[128];
    
    /* Extraction des données depuis la ligne */
    sscanf(line, "%d;%127[^;];%127[^;];%d", &id, first_name, last_name, &age);
    
    /* Création et retour de la structure Student */
    return (create_student(id, last_name, first_name, age, 0));
}

    