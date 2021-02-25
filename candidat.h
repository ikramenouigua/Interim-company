#ifndef CANDIDAT_H_INCLUDED
#define CANDIDAT_H_INCLUDED
typedef struct {
       int code;
       char nom[30];
       char *prenom;
       char *password;
       char email[30];
       char *adresse;
       char *specialite;
       float cotisation_annuelle;
       int age;
       int nb_stage;
       int nb_projet;
       int nb_experience;
}candidat;
typedef candidat* Candidat;
typedef struct noeud{
    Candidat c1;
    struct ListeCandidat* suivant;
}noeud;
typedef noeud* Liste;


int enregistrerCandidat(char* nom,char* prenom,char* adresse,char* password,char*email,char *specialite,int age,int nb_stage,int nb_projet,int nb_experience);
int enregistrerFichier(Candidat p);
void ajouterCandidatListe(Liste* liste,candidat p);
Liste* extraireListeCandidat();
int se_connecter(char *email,char *password);
Candidat retournerCandidat(char *email,char *password);
int supprimerFich(char *nom,char *password);
Liste supprimerCandidat(char *email,char *password);
Liste trierCandidat(Liste liste);
Liste* extraireCandidat(char *specialite);
int modifierFich(char *femail,char *fpassword,char *nom,char *prenom,char *adresse,char *specialite,int age,int nb_stage,int nb_projet,int nb_experience);
Liste modifierCandidat(char *femail,char *fpassword,char *nom,char *prenom,char *adresse,char *specialite,int age,int nb_stage,int nb_projet,int nb_experience);

#endif // CANDIDAT_H_INCLUDED
