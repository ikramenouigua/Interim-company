#ifndef ENTREPRISE_H_INCLUDED
#define ENTREPRISE_H_INCLUDED

typedef struct _entreprise{
    char code[30];
	char nom_entreprise[50];
	char mot_de_passe_entre[50];
	char mail[50];//code
	char adresse[30];
	char specialite[30];
	float cotisation_annuelle;
}entreprise;
typedef entreprise  *Entreprise;
typedef struct noeud2{
    Entreprise en;
    struct noeud* suivant;
}noeud2;
typedef noeud2* ListeEn;

int enregistrerFichierEn(Entreprise p);
int enregistrerEntreprise(char *code,char *nom_entreprise,char *mot_de_passe_entre,char *mail,char *adresse,char *specialite);
void ajouterEntrepriseListe(ListeEn* liste,entreprise p);
ListeEn* extraireListeEntreprise();
int se_connecterEn(char *email,char *password);
Entreprise retournerEntreprise(char *email,char *password);
#endif

