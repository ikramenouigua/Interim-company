#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "offre.h"
//enregistrer les donnees d'une offre dans le fichier
int enregistrerOffreFichier(Offre o){
    FILE *fp=fopen("offreInfo.txt","a");
     printf("j");
    if(fp==NULL){
        printf("Erreur lors d'acces au fichier des offres.\n");
        return -1;
    }

    int i=fprintf(fp,"%s %s %s %f %s %s %s %s %s %d %d %d %d %d %d \n",o->code,o->specialite,o->etat,o->salaire,o->nomEn,o->typeContrat,o->adresse,o->ville,o->poste,o->anneD,o->moisD,o->jourD,o->anneF,o->moisF,o->jourF);
    if(i==0){
        printf("Erreur lors d'ecriture dans le fichier des offres.\n");
        return -1;
    }
    printf("offre enregistre!\n");
    fclose(fp);
    return 0;
}
//enregistrer les donnes d'une offre dans une structure  offre
int enregistrerOffre(char *code,char *specialite,char *etat,float salaire,char *nomEn,char *typeContrat,char *adresse,char *ville,char *poste,int anneD,int moisD,int jourD,int anneF,int moisF,int jourF){
Offre p;
    p=(Offre)malloc(sizeof(offre));
    strcpy(p->code,code);
    strcpy(p->specialite,specialite);
    strcpy(p->etat,etat);
    p->salaire=salaire;
    strcpy(p->nomEn,nomEn);
    strcpy(p->typeContrat,typeContrat);
    strcpy(p->adresse,adresse);
    strcpy(p->ville,ville);
    strcpy(p->poste,poste);
    p->anneD=anneD;
    p->moisD=moisD;
    p->jourD=jourD;
    p->anneF=anneF;
    p->jourF=jourF;
    p->moisF=moisF;

    int x=enregistrerOffreFichier(p);
    return x;
}
//ajouter les offres extrait du fichier au liste chainnee
void ajouterOffreListe(ListeOf *liste,offre p){
    noeud3* nouveau=(noeud3*)malloc(sizeof(noeud3));
    nouveau->off=(offre*)malloc(sizeof(offre));

    strcpy(nouveau->off->code,p.code);
    strcpy(nouveau->off->specialite,p.specialite);
    strcpy(nouveau->off->etat,p.etat);
    strcpy(nouveau->off->nomEn,p.nomEn);
    strcpy(nouveau->off->typeContrat,p.typeContrat);
    strcpy(nouveau->off->adresse,p.adresse);
    strcpy(nouveau->off->ville,p.ville);
      strcpy(nouveau->off->poste,p.poste);
    nouveau->off->salaire=p.salaire;
     nouveau->off->anneD=p.anneD;
      nouveau->off->moisD=p.moisD;
       nouveau->off->jourD=p.jourD;
        nouveau->off->anneF=p.anneF;
         nouveau->off->moisF=p.moisF;
          nouveau->off->jourF=p.jourF;
     nouveau->suivant=NULL;

		nouveau->suivant=*liste;
		(*liste)=nouveau;
}
//extraire donnee de chaque offre du fichier et les stocker dans une liste chainee
ListeOf* extraireListeOffre(){
    printf("hh\n");
     ListeOf* l=NULL;
    char ligne[150];
     FILE *fp=fopen("offreInfo.txt","r");
    if(fp==NULL){
        printf("");
        return -1;
    }
    offre o;

      while ( fgets( ligne, 200, fp) != NULL )
    {
    sscanf(ligne,"%s %s %s %f %s %s %s %s %s %d %d %d %d %d %d \n",&o.code,o.specialite,o.etat,&o.salaire,o.nomEn,o.typeContrat,o.adresse,o.ville,o.poste,&o.anneD,&o.moisD,&o.jourD,&o.anneF,&o.moisF,&o.jourF) ;
      ajouterOffreListe(&l,o);
    }
   return l;
}
//extraire les offres du fichier qui ont la meme specialite donne en parametres
ListeOf* extraireOffre(char *specialite){
     ListeOf* l=NULL;
    char ligne[150];
     FILE *fp=fopen("offreInfo.txt","r");

    if(fp==NULL){
        printf("");
        return -1;
    }
    offre o;
      while ( fgets( ligne, 200, fp) != NULL )
    {
    sscanf(ligne,"%s %s %s %f %s %s %s %s %s %d %d %d %d %d %d \n",&o.code,o.specialite,o.etat,&o.salaire,o.nomEn,o.typeContrat,o.adresse,o.ville,o.poste,&o.anneD,&o.moisD,&o.jourD,&o.anneF,&o.moisF,&o.jourF) ;
     if(strcmp(o.specialite,specialite)==0){
        ajouterOffreListe(&l,o);
        printf("annee %d",o.anneD);
     }
    }
   return l;
}
//affichage offres dans console
void afficherOffre(ListeOf l){
     noeud3* p;
    p=l;
while(p!=NULL){
    printf(" %s %s %s %s\n",p->off->code,p->off->adresse,p->off->specialite,p->off->etat);
    p=p->suivant;
}
}
