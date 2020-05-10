#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOM_DESCRIPTIU 30
#define USER 15
#define PASSWORD 10

char *arxiuUsuaris = "usuaris.bin";

typedef struct {
    char nomDesc[NOM_DESCRIPTIU + 1];
    char user[USER + 1];
    char password[PASSWORD + 1];
} tUsuari;

void llegirProducte(tUsuari *usr)
{
    char s[255];
    do {
        s[0] = '\0';
        printf("\n- NOM DESCRIPTIU ( > 0 i <= 30) ........: ");
        gets(s);
    } while(s[0] == '\0' || strlen(s) > NOM_DESCRIPTIU);
    strcpy(usr->nomDesc, s);

    do {
        s[0] = '\0';
        printf("- NOM D'USUARI ( > 0 i <= 15) ..........: ");
        gets(s);
    } while(s[0] == '\0' || strlen(s) > USER);
    strcpy(usr->user, s);

    do {
        s[0] = '\0';
        printf("- CONTRASENYA ( > 0 i <= 10) ............: ");
        gets(s);
    } while(s[0] == '\0' || strlen(s) > PASSWORD);
    strcpy(usr->password, s);
}

int menu()
{
    int aux;
    /* Comprovar si existeix fitxer i si no hi és, crear-lo buit */
    FILE *f = fopen(arxiuUsuaris, "rb");
    if(f == NULL) {
        f = fopen(arxiuUsuaris, "ab");
        if(f == NULL) {
            printf("Fitxer no existeix i no es pot crear\n");
            printf("Premi tecla per continuar...");
            getch();
            return EXIT_FAILURE;
        }
        fclose(f);
    }
    system("cls");
    printf("1. Afegir usuari\n");
    printf("2. Consultar contrasenya\n");
    printf("3. LListar usuaris\n");
    printf("0. Sortir\n\n");
    do {
        aux = -1;
        printf("Introdueixi opcio: ");
        scanf("%d", &aux);
        fflush(stdin);
    } while(aux < 0 || aux > 3);
    return aux;
}

void afegirUsuari()
{
    tUsuari usr;
    FILE *f;
    int error;

    llegirProducte(&usr);
    f = fopen(arxiuUsuaris, "ab");
    if(f == NULL) {
        printf("Error en obrir el fitxer. No s'enregistra!");
        printf("Premi tecla per continuar...");
        getch();
    }
    else {
        fwrite(&usr, sizeof(tUsuari), 1, f);
        error = ferror(f);
        if(error) {
            printf("\t\n\nError %d en enregistrar l'usuari! Comprovi...\n", error);
            printf("Premi tecla per continuar...");
            getch();
        }
        else {
            printf("\t\n\nOkey! L'usuari donat de alta correctament!\n", error);
            printf("Premi tecla per continuar...");
            getch();
        }
        fclose(f);
    }
}

void consultaPass()
{
    FILE *f = fopen(arxiuUsuaris, "rb");
    char u[255];
    int trobat = false;

    if(f == NULL) {
        printf("Error en obrir el fitxer. No es pot mostrar res!\n");
        printf("Premi tecla per continuar...");
        getch();
        return EXIT_FAILURE;
    }

    tUsuari usr;
    fread(&usr, sizeof(tUsuari), 1, f);
    printf("\n----- CONSULTA PASSWORD -----\n\n");

    do {
        u[0] = '\0';
        printf("- NOM D'USUARI ( > 0 i <= 15) ..........: ");
        gets(u);
    } while(u[0] == '\0' || strlen(u) > USER);

    while(!feof(f) && !trobat) {
        if(strcmp(usr.user, u) == 0) {
            printf("- CONSTRASENYA DEL USUARI ..............: %s\n", usr.password);
            printf("\nPremi tecla per continuar...");
            getch();
            trobat = true;
        }
        fread(&usr, sizeof(tUsuari), 1, f);
    }

    if(!trobat) {
        printf("\n\nError no s'ha trobat cap registre amb aquest usuari!\n");
        printf("Premi tecla per continuar...");
        getch();
    }
    fclose(f);
}

void llistarUsuaris()
{
    FILE *f = fopen(arxiuUsuaris, "rb");
    if(f == NULL) {
        printf("Error en obrir el fitxer. No es pot mostrar res!\n");
        printf("Premi tecla per continuar...");
        getch();
        return EXIT_FAILURE;
    }

    tUsuari usr;
    fread(&usr, sizeof(tUsuari), 1, f);
    printf("\n----- LLISTAT D'USUARIS -----\n\n");
    while(!feof(f)) {
        printf("NOM............: %s\n", usr.user);
        fread(&usr, sizeof(tUsuari), 1, f);
    }
    printf("\n\nPremi tecla per continuar...");
    getch();
    fclose(f);
}

int main(int argc, char **argv)
{
    int opc;
    do {
        opc = menu();
        switch(opc) {
        case 1:
            afegirUsuari();
            break;
        case 2:
            consultaPass();
            break;
        case 3:
            llistarUsuaris();
            break;
        }
    } while(opc != 0);
    return EXIT_SUCCESS;
}