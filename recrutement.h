#ifndef RECRUTEMENT_H_INCLUDED
#define RECRUTEMENT_H_INCLUDED
typedef struct recrutement{
    char code[30];
    char nom[30];
    char prenom[30];
    char poste[30];
    char type[30];
    char adresse[30];
    char email[30];
    int anneD;
     int moisD;
     int jourD;
     int anneF;
     int moisF;
     int jourF;
    }recrutement;
typedef recrutement  *Recrutement;
typedef struct noeud4{
    Recrutement rec;
    struct noeud4* suivant;
}noeud4;
typedef noeud4* ListeRec;
int enregistrerRecrutement(char *code,char *nom,char *prenom,char *type,char *adresse,char *mail,char *poste,int anneD,int moisD,int jourD,int anneF,int moisF,int jourF);
int enregistrerRecrutementFichier(Recrutement p);
#endif // RECRUTEMENT_H_included

