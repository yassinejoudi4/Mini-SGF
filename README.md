#Mini SGF - Système de Gestion de Fichiers

Projet réalisé en langage C dans le cadre du module Système d’Exploitation.

Description

Ce projet consiste à développer un mini système de gestion de fichiers inspiré du fonctionnement des systèmes UNIX/Linux. Le système repose sur une structure de disque virtuelle contenant des inodes, des blocs de données et des mécanismes d’allocation mémoire.

Le projet implémente les bases d’un système de fichiers :

gestion des inodes
gestion des blocs
création de fichiers
écriture et lecture de données
allocation d’espace disque
simulation d’un disque virtuel
Structures principales
Inode
Bloc
Disk
bitmap_inodes
bitmap_blocs
Fonctions implémentées
init_disk()
find_free_inode()
find_free_block()
mycreat()
mywrite()
myread()

Réalisé par : 
-Yassine JOUDI
-Marc ELYSÉE
-Ahmed ISHAGH
-Ayman MSIMAR
-Mohamed Elouargouli
