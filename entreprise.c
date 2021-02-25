#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "entreprise.h"
//enregister une nouvelle entreprise dans le fichier
int enregistrerFichierEn(Entreprise p){
    FILE *fp=fopen("entrepriseInfo.txt","a");
    if(fp==NULL){
        printf("Erreur lors d'acces au fichier des entreprises.\n");
        return -1;
    }

    int i=fprintf(fp,"%s %s %s %s %s %s %.2f \n",p->code,p->nom_entreprise,p->mail,p->mot_de_passe_entre,p->adresse,p->specialite,p->cotisation_annuelle);
    if(i==0){
        printf("Erreur lors d'ecriture dans le fichier des entreprises.\n");
        return -1;
    }
    printf("Entreprise enregistre!\n");
    fclose(fp);
    return 0;
}
//allouer une nouvelle structure entreprise ou on stocke les infos por les sauvegarder par la suite dans le fichier
int enregistrerEntreprise(char *code,char *nom_entreprise,char *mot_de_passe_entre,char *mail,char *adresse,char *specialite){
    Entreprise p;
    p=(Entreprise)malloc(sizeof(entreprise));
    strcpy(p->code,code);
    strcpy(p->nom_entreprise,nom_entreprise);
    strcpy(p->mot_de_passe_entre,mot_de_passe_entre);
    strcpy(p->mail,mail);
    strcpy(p->adresse,adresse);
    strcpy(p->specialite,specialite);
    p->cotisation_annuelle=600;
    int x=enregistrerFichierEn(p);
    return x;
}
//ajouter une entreprise au debut d'une une liste chainee
void ajouterEntrepriseListe(ListeEn* liste,entreprise p){

    noeud2* nouveau=(noeud2*)malloc(sizeof(noeud2));
    nouveau->en=(entreprise*)malloc(sizeof(entreprise));

    strcpy(nouveau->en->code,p.code);
    strcpy(nouveau->en->nom_entreprise,p.nom_entreprise);
    strcpy(nouveau->en->mot_de_passe_entre,p.mot_de_passe_entre);
    strcpy(nouveau->en->mail,p.mail);
    strcpy(nouveau->en->adresse,p.adresse);
     strcpy(nouveau->en->specialite,p.specialite);
    nouveau->en->cotisation_annuelle=p.cotisation_annuelle;
     nouveau->suivant=NULL;

		nouveau->suivant=*liste;
		(*liste)=nouveau;
}
//extraire les donnees den entreprises et les stocker par la suite dans une liste chainne
ListeEn* extraireListeEntreprise(){
    ListeEn* l=NULL;
    char ligne[150];
     FILE *fp=fopen("entrepriseInfo.txt","r");
    if(fp==NULL){
        printf("");
        return -1;
    }
    entreprise p;
      while ( fgets( ligne, 81, fp) != NULL )
    {
    sscanf(ligne,"%s %s %s %s %s %s %f", &p.code,p.nom_entreprise,p.mail,p.mot_de_passe_entre,p.adresse,p.specialite,&p.cotisation_annuelle) ;
      ajouterEntrepriseListe(&l,p);
    }
   return l;

}
//connecter au compte d'entreprise en comparant email et password d'entree avec le contenu du fichier
int se_connecterEn(char *email,char *password){
ListeEn l=NULL;
l=extraireListeEntreprise();
 noeud2* q;
q=l;
while(q!=NULL ){
        printf("%s %s",q->en->mail,q->en->mot_de_passe_entre);
    if(strcmp(q->en->mail,email)==0 && strcmp(q->en->mot_de_passe_entre,password)==0){
        return 1;
    }
    q=q->suivant;
}
return 0;
}
//retourner la structure de l'entreprise coourant
Entreprise retournerEntreprise(char *email,char *password){
    ListeEn l=NULL;
    l=extraireListeEntreprise();
    noeud2 *q;
    q=l;
    while(q!=NULL){
        if(strcmp(q->en->mail,email)==0 && strcmp(q->en->mot_de_passe_entre,password)==0){

        return q->en;
    }
    q=q->suivant;
    }
    return NULL;
}
