#ifndef SGF_H
#define SGF_H

#define NB_INODES 64
#define NB_BLOCS 256
#define TAILLE_BLOC 1024
#define MAX_BLOCS_PAR_FICHIER 30

typedef struct {
    int type;
    int taille;
    int blocs[MAX_BLOCS_PAR_FICHIER];
} Inode;

typedef struct {
    char data[TAILLE_BLOC];
} Bloc;

typedef struct {
    Inode inodes[NB_INODES];
    Bloc blocs[NB_BLOCS];
    unsigned char bitmap_inodes[NB_INODES];
    unsigned char bitmap_blocs[NB_BLOCS];
} Disk;

#endif