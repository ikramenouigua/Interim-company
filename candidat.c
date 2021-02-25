#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "candidat.h"
static int id;    //un id de type static pr le programme
//enregistrer les donnees d'un candidat dans le fichier
int enregistrerFichier(Candidat p){
    FILE *fp=fopen("candidatInfo.txt","a");
     printf("j");
    if(fp==NULL){
        printf("Erreur lors d'acces au fichier des candidats.\n");
        return -1;
    }

    int i=fprintf(fp,"%d %s %s %s %s %s %s %.2f %d %d %d %d \n",p->code,p->nom,p->prenom,p->email,p->password,p->adresse,p->specialite,p->cotisation_annuelle,p->age,p->nb_stage,p->nb_projet,p->nb_experience);
    if(i==0){
        printf("Erreur lors d'ecriture dans le fichier des candidats.\n");
        return -1;
    }
    printf("Candidat enregistre!\n");
    fclose(fp);
    return 0;
}
//enregistrer les donnes d'un candidat dans une structure  candidat
int enregistrerCandidat(char *nom,char *prenom,char *password,char *email,char *adresse,char *specialite,int age,int nb_stage,int nb_projet,int nb_experience){
    Candidat p;
    p=(Candidat)malloc(sizeof(candidat));
    p->code=++id;
    p->prenom=(char*)malloc(30*sizeof(char));
    p->password=(char*)malloc(30*sizeof(char));
    p->adresse=(char*)malloc(30*sizeof(char));
    p->specialite=(char*)malloc(30*sizeof(char));
    strcpy(p->nom,nom);
    strcpy(p->prenom,prenom);
    strcpy(p->password,password);
    strcpy(p->email,email);
    strcpy(p->adresse,adresse);
    strcpy(p->specialite,specialite);
    p->cotisation_annuelle=600;
    p->age=age;
    p->nb_stage=nb_projet;
    p->nb_projet=nb_projet;
    p->nb_experience=nb_experience;
    int x=enregistrerFichier(p);
    return x;
}
//ajouter les candidats extrait du fichier au liste chainnee
void ajouterCandidatListe(Liste* liste,candidat p){

    noeud* nouveau=(noeud*)malloc(sizeof(noeud));
    nouveau->c1=(candidat*)malloc(sizeof(candidat));
    nouveau->c1->prenom=(char*)malloc(30*sizeof(char));
    nouveau->c1->password=(char*)malloc(30*sizeof(char));
    nouveau->c1->adresse=(char*)malloc(30*sizeof(char));
    nouveau->c1->specialite=(char*)malloc(30*sizeof(char));
    nouveau->c1->code=p.code;
    strcpy(nouveau->c1->nom,p.nom);
    strcpy(nouveau->c1->prenom,p.prenom);
    strcpy(nouveau->c1->password,p.password);
    strcpy(nouveau->c1->email,p.email);
    strcpy(nouveau->c1->adresse,p.adresse);
    strcpy(nouveau->c1->specialite,p.specialite);
    nouveau->c1->cotisation_annuelle=p.cotisation_annuelle;
    nouveau->c1->age=p.age;
    nouveau->c1->nb_stage=p.nb_stage;
    nouveau->c1->nb_projet=p.nb_projet;
    nouveau->c1->nb_experience=p.nb_experience;
     nouveau->suivant=NULL;

		nouveau->suivant=*liste;
		(*liste)=nouveau;
}
//extraire donnee de chaque candidat du fichier et les stocker dans une liste chainee
Liste* extraireListeCandidat(){
    Liste* l=NULL;
    char ligne[150];
     FILE *fp=fopen("candidatInfo.txt","r");
    if(fp==NULL){
        printf("");
        return -1;
    }
    candidat p;
    p.prenom=(char*)malloc(30*sizeof(char));
    p.password=(char*)malloc(30*sizeof(char));
    p.adresse=(char*)malloc(30*sizeof(char));
    p.specialite=(char*)malloc(30*sizeof(char));
      while ( fgets( ligne, 81, fp) != NULL )
    {
    sscanf(ligne,"%d %s %s %s %s %s %s %f %d %d %d %d", &p.code,p.nom,p.prenom,p.password,p.email,p.adresse,p.specialite,&p.cotisation_annuelle,&p.age,&p.nb_stage,&p.nb_projet,&p.nb_experience) ;
      ajouterCandidatListe(&l,p);

    }
   return l;
}
//afficher les donnees des candidat dans console
void afficherCandidat(Liste l){
    noeud* p;
    p=l;
while(p!=NULL){
    printf(" %d %s %s %s\n",p->c1->code,p->c1->nom,p->c1->prenom,p->c1->password);
    p=p->suivant;
}
}
//connexion d'un candidat en comparant son email et mot de passe avec les donnees du fichier
//si le candidat existe on retourne 0 sinon 1
int se_connecter(char *email,char *password){
Liste l=NULL;
l=extraireListeCandidat();
 noeud* q;
q=l;
while(q!=NULL ){
        printf("%s %s",q->c1->email,q->c1->password);
    if(strcmp(q->c1->email,email)==0 && strcmp(q->c1->password,password)==0){
            printf("%s",q->c1->nom);
        return 1;
    }
    q=q->suivant;
}
return 0;
}
//retourner structure du candidat en cours en comparant son email et mot de pases avec les donnees enregistre dans le fichier
Candidat retournerCandidat(char *email,char *password){
    Liste l=NULL;
    l=extraireListeCandidat();
    noeud *q;
    q=l;
    while(q!=NULL){
        if(strcmp(q->c1->email,email)==0 && strcmp(q->c1->password,password)==0){
        return q->c1;
    }
    q=q->suivant;
    }
    return NULL;
}
//supprimer un candidat de la liste chainnee des candidat
Liste supprimerCandidat(char *email,char *password){
    Liste l=NULL;
    l=extraireListeCandidat();
   noeud *p,*q;
     if(l!=NULL){
 if(strcmp(l->c1->email,email)==0 && strcmp(l->c1->password,password)==0){
 p=l;
 l=l->suivant;
 free(p);
 }
 else{
 q=l;
 p=l->suivant;
 while(p != NULL ){
 if (strcmp(p->c1->email,email)==0 && strcmp(p->c1->password,password)==0){
 q->suivant=p->suivant;
 free(p);
 break;
 }
 q=p;
 p=p->suivant;
 }
 }
 }
 return l;
}
//vider le fichier des candats et le remplit par la nouvelle liste ou le candidat est supprime
int supprimerFich(char *nom,char *password){
    Liste l;
    FILE *fc;
    int x=0;

   l=supprimerCandidat(nom,password);
   fc=fopen("candidatInfo.txt","w");
   fclose(fc);
   noeud *p=l;
while(p!=NULL){
x=enregistrerFichier(p->c1);
   p=p->suivant;
}
 return x;
}
//trier les candidats du liste selon age,nb experience,nb projet et nombre de stages
Liste trierCandidat(Liste liste){
    noeud *m, *q;
    Candidat temp=(Candidat)malloc(sizeof(candidat));
    noeud* p=liste;
    int som1=0,som2=0;
   do{
     m=p;
     q=p->suivant;

     do{
        som1=m->c1->age+m->c1->nb_projet+m->c1->nb_stage+m->c1->nb_experience;
        som2=q->c1->age+q->c1->nb_projet+q->c1->nb_stage+q->c1->nb_experience;
        if(som1 < som2){

               temp=m->c1;
                m->c1=q->c1;
                q->c1=temp;
                printf(" age  %d\n",m->c1->age);
            q=q->suivant;
     }
     else{
       q=q->suivant;
     }
     }while(q!=NULL);
     printf("hii");
     p=p->suivant;
     }while(p->suivant!=NULL);


    return liste;
}
//extraire la liste des candidats selon une specialite precis
Liste* extraireCandidat(char *specialite){
   Liste* l=NULL;
    char ligne[200];
     FILE *fp=fopen("candidatInfo.txt","r");
    if(fp==NULL){
        printf("");
        return -1;
    }
    candidat p;
    p.prenom=(char*)malloc(30*sizeof(char));
    p.password=(char*)malloc(30*sizeof(char));
    p.adresse=(char*)malloc(30*sizeof(char));
    p.specialite=(char*)malloc(30*sizeof(char));
      while ( fgets( ligne, 200, fp) != NULL )
    {
    sscanf(ligne,"%d %s %s %s %s %s %s %f %d %d %d %d", &p.code,p.nom,p.prenom,p.password,p.email,p.adresse,p.specialite,&p.cotisation_annuelle,&p.age,&p.nb_stage,&p.nb_projet,&p.nb_experience) ;
     if(strcmp(p.specialite,specialite)==0){
            printf("\n%s",p.specialite);

      ajouterCandidatListe(&l,p);}
    }
    l=trierCandidat(l);
   return l;

}
//modier les infos d'un candidats dans les liste chainnee extrai du fichier des candidats
Liste modifierCandidat(char *femail,char *fpassword,char *nom,char *prenom,char *adresse,char *password,int age,int nb_stage,int nb_projet,int nb_experience){

    Liste l=extraireListeCandidat();
     noeud *p=l;
    while(p != NULL ){
    if (strcmp(p->c1->email,femail)==0 && strcmp(p->c1->password,fpassword)==0){
      strcpy(p->c1->nom,nom);
    strcpy(p->c1->prenom,prenom);
    strcpy(p->c1->adresse,adresse);
    strcpy(p->c1->password,password);
    p->c1->age=age;
    p->c1->nb_stage=nb_stage;
    p->c1->nb_projet=nb_stage;
    p->c1->nb_experience=nb_experience;
    break;
}
p=p->suivant;
    }
    return l;
}
//on essaye de vider le fichier et le remplit par la nouvelle liste ou les infos du candidat en cours est change
int modifierFich(char *femail,char *fpassword,char *nom,char *prenom,char *adresse,char *password,int age,int nb_stage,int nb_projet,int nb_experience){
    Liste *l;
    FILE *fc;
    int x=0;

   l=modifierCandidat(femail,fpassword,nom,prenom,adresse,password,age,nb_stage,nb_projet,nb_experience);
   fc=fopen("candidatInfo.txt","w");
   fclose(fc);
   noeud *p=l;
while(p!=NULL){
x=enregistrerFichier(p->c1);
   p=p->suivant;
}
 return x;
}
