#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "recrutement.h"
//enregistrer les donnees d'un recrutement dans le fichier
int enregistrerRecrutementFichier(Recrutement p){
    FILE *fp=fopen("recrutementInfo.txt","a");
     printf("j");
    if(fp==NULL){
        printf("Erreur lors d'acces au fichier des recrutement.\n");
        return -1;
    }

    int i=fprintf(fp,"%s %s %s %s %s %s %s %s %d %d %d %d %d %d \n",p->code,p->nom,p->prenom,p->poste,p->type,p->adresse,p->adresse,p->email,p->anneD,p->moisD,p->jourD,p->anneF,p->moisF,p->jourF);

    if(i==0){
        printf("Erreur lors d'ecriture dans le fichier des Recrutement.\n");
        return -1;
    }
    printf("Recrutement enregistre!\n");
    fclose(fp);
    return 0;
}
////enregistrer les donnes d'un recrutement dans une structure  candidat
int enregistrerRecrutement(char *code,char *nom,char *prenom,char *type,char *adresse,char *mail,char *poste,int anneD,int moisD,int jourD,int anneF,int moisF,int jourF){
    Recrutement p;
    p=(Recrutement)malloc(sizeof(recrutement));
    strcpy(p->code,code);
    strcpy(p->nom,nom);
    strcpy(p->prenom,prenom);
    strcpy(p->type,type);
    strcpy(p->adresse,adresse);
    strcpy(p->email,mail);
    strcpy(p->poste,poste);
    p->anneD=anneD;
    p->moisD=moisD;
    p->jourD=jourD;
    p->anneF=anneF;
    p->jourF=jourF;
    p->moisF=moisF;

    int x=enregistrerRecrutementFichier(p);
    return x;
}
