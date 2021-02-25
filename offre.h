#ifndef OFFRE_H_INCLUDED
#define OFFRE_H_INCLUDED
typedef struct offre{
     char code[30];
     char specialite[30];
     char etat[30];
     float salaire;
     char nomEn[30];
     char typeContrat[30];
     char adresse[30];
     char ville[30];
     char poste[30];
     int anneD;
     int moisD;
     int jourD;
     int anneF;
     int moisF;
     int jourF;

     }offre;
typedef offre *Offre;
typedef struct noeud3{
   Offre off;
   struct noeud3 *suivant;
   }noeud3;
typedef noeud3 *ListeOf;
int enregistrerOffre(char *code,char *specialite,char *etat,float salaire,char *nomEn,char *typeContrat,char *adresse,char *ville,char *poste,int anneD,int moisD,int jourD,int anneF,int moisF,int jourF);
int enregistrerOffreFichier(Offre o);
void ajouterOffreListe(ListeOf *liste,offre p);
ListeOf* extraireListeOffre();
ListeOf* extraireOffre(char *specialite);
void afficherOffre(ListeOf l);

#endif // OFFRE_H_INCLUDED
