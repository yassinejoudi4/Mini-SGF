#include <stdio.h>
#include "sgf.h"

Disk disk;

/* disk*/
void init_disk() {
    for (int i = 0; i < NB_INODES; i++) {
        disk.inodes[i].type = 0;
        disk.inodes[i].taille = 0;
        disk.bitmap_inodes[i] = 0;

        for (int j = 0; j < MAX_BLOCS_PAR_FICHIER; j++) {
            disk.inodes[i].blocs[j] = -1;
        }
    }

    for (int i = 0; i < NB_BLOCS; i++) {
        disk.bitmap_blocs[i] = 0;
    }
}

/*inode */
int find_free_inode() {
    for (int i = 0; i < NB_INODES; i++) {
        if (disk.bitmap_inodes[i] == 0) {
            return i;
        }
    }
    return -1;
}

/* bloc */
int find_free_block() {
    for (int i = 0; i < NB_BLOCS; i++) {
        if (disk.bitmap_blocs[i] == 0) {
            return i;
        }
    }
    return -1;
}

/*creation du fichier*/
int mycreat() {
    int inode = find_free_inode();

    if (inode == -1) {
        printf("Erreur : aucun inode libre\n");
        return -1;
    }

    disk.bitmap_inodes[inode] = 1;

    disk.inodes[inode].type = 1;
    disk.inodes[inode].taille = 0;

    for (int i = 0; i < MAX_BLOCS_PAR_FICHIER; i++) {
        disk.inodes[inode].blocs[i] = -1;
    }

    printf("Fichier cree avec inode : %d\n", inode);
    return inode;
}

/*ecriture*/
void mywrite(int inode, char *text) {

    if (inode < 0 || inode >= NB_INODES || disk.bitmap_inodes[inode] == 0) {
        printf("Erreur inode invalide\n");
        return;
    }

    int bloc = find_free_block();

    if (bloc == -1) {
        printf("Disque plein\n");
        return;
    }

    disk.bitmap_blocs[bloc] = 1;

    int placed = 0;

    for (int i = 0; i < MAX_BLOCS_PAR_FICHIER; i++) {
        if (disk.inodes[inode].blocs[i] == -1) {
            disk.inodes[inode].blocs[i] = bloc;
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Pas de place dans l'inode\n");
        return;
    }

    int i = 0;
    while (text[i] != '\0' && i < TAILLE_BLOC) {
        disk.blocs[bloc].data[i] = text[i];
        i++;
    }

    disk.inodes[inode].taille = i;

    printf("Ecriture dans inode %d (bloc %d)\n", inode, bloc);
}

/*lecture*/
void myread(int inode) {

    if (inode < 0 || inode >= NB_INODES || disk.bitmap_inodes[inode] == 0) {
        printf("Erreur inode invalide\n");
        return;
    }

    if (disk.inodes[inode].type != 1) {
        printf("Erreur : pas un fichier\n");
        return;
    }

    printf("Contenu fichier inode %d :\n", inode);

    for (int i = 0; i < MAX_BLOCS_PAR_FICHIER; i++) {
        int bloc = disk.inodes[inode].blocs[i];

        if (bloc == -1) break;

        for (int j = 0; j < TAILLE_BLOC; j++) {
            char c = disk.blocs[bloc].data[j];

            if (c == '\0') {
                printf("\n");
                return;
            }

            printf("%c", c);
        }
    }

    printf("\n");
}

int main() {
    init_disk();

    int f1 = mycreat();
    int f2 = mycreat();

    mywrite(f1, "Bonjour SGF");
    myread(f1);

    return 0;
}