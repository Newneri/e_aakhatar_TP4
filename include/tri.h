/*!
* \file tri.h
* \author Akhatar Abdelhamid <abdelhamid.akhatar@etu.cyu.fr>
* \version 1.0
* \date 3 novembre 2025
* \brief Interface du module de tri des étudiants
* 
* Ce fichier contient les prototypes des fonctions permettant de trier
* les étudiants d'une promotion selon différents leurs notes.
*/

#ifndef TRI_H
#define TRI_H

#include "init.h"

/*!
* \fn void trier_etudiants_par_moyenne(Prom* prom)
* \brief Trie les étudiants par moyenne décroissante
* 
* Cette fonction trie le tableau d'étudiants d'une promotion
* par ordre décroissant de moyenne en utilisant l'algorithme
* de tri par sélection.
* 
* \param prom Pointeur vers la structure Prom contenant les étudiants
*/
void trier_etudiants_par_moyenne(Prom* prom);

/*!
* \fn void trier_etudiants_par_matiere(Prom* prom, char* course_name)
* \brief Trie les étudiants par moyenne dans une matière spécifique
* 
* Cette fonction trie les étudiants d'une promotion en fonction de
* leur moyenne dans une matière donnée et affiche les trois meilleurs.
* 
* \param prom Pointeur vers la structure Prom contenant les étudiants
* \param course_name Nom de la matière pour le tri
*/
void trier_etudiants_par_matiere(Prom* prom, char* course_name);

#endif