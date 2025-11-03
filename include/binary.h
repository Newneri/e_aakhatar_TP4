/*!
 * \file binary.h
 * \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
 * \version 1.0
 * \date 2 novembre 2025
 * \brief Interface du module de sauvegarde/restauration binaire
 * 
 * Ce fichier contient les prototypes des fonctions permettant de sauvegarder
 * et restaurer une promotion complète (étudiants, matières, notes) dans un fichier binaire.
 */

#ifndef BINARY_H
#define BINARY_H

#include "init.h"

/*!
 * \fn int save_prom_binary(const char* str_filename, Prom* prom)
 * \brief Sauvegarde une promotion complète dans un fichier binaire
 * \param str_filename Nom du fichier binaire de destination
 * \param prom Pointeur vers la structure Prom à sauvegarder
 * \return 0 si succès, -1 en cas d'erreur
 * \pre str_filename != NULL
 * \pre prom != NULL
 * 
 * Cette fonction sauvegarde dans l'ordre :
 * - Le nombre d'étudiants
 * - Pour chaque étudiant : ID, nom, prénom, âge, nombre de cours, moyenne
 * - Pour chaque cours de chaque étudiant : nom, coefficient, moyenne, nombre de notes, notes
 */
int save_prom_binary(const char* str_filename, Prom* prom);

/*!
 * \fn Prom load_prom_binary(const char* str_filename)
 * \brief Restaure une promotion depuis un fichier binaire
 * \param str_filename Nom du fichier binaire source
 * \return Structure Prom restaurée, ou structure vide en cas d'erreur
 * \pre str_filename != NULL
 * 
 * Cette fonction lit le fichier binaire et reconstruit en mémoire :
 * - Tous les étudiants avec leurs informations
 * - Tous les cours de chaque étudiant
 * - Toutes les notes de chaque cours
 */
Prom load_prom_binary(const char* str_filename);

#endif