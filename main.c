#include <stdlib.h>
#include <gtk/gtk.h>
#include<stdio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include "candidat.h"
#include "entreprise.h"
#include "offre.h"
#include "recrutement.h"
#include<time.h>
static GtkWidget *window;
static GtkBuilder *builder;
static  GtkEntry * email;
static  GtkEntry * password;
char* emailText;
char* passwordText;
void deconnecter(GtkWidget* widget,gpointer* data);
char *combo_box_active_get_text(GtkComboBox *combo_box);
void supprimerCompte(GtkWidget* widget,gpointer* data);
void modifierCompte(GtkWidget* widget,gpointer* data);
void RetourPage(GtkWidget* widget,gpointer* parent);
void accederInfo(GtkWidget* widget,gpointer* parent);
void accederOffre(GtkWidget* widget,gpointer* data);
void connexion(GtkWidget* widget,gpointer* data);
void nouveauOffre(GtkWidget* widget,gpointer* data);
void recruterCandidat(GtkWidget* widget,gpointer* data);
void afficherRecrutement(gchar *nom,gchar *prenom,gchar *email,gchar *adresse);
void view_onRowActivated (GtkTreeView *treeview,GtkTreePath *path,GtkTreeViewColumn *col,gpointer userdata);
void gestionCandidat(GtkWidget* widget,gpointer* data);
void ajouterOffre(GtkWidget* widget,gpointer* data);
void gestionOffre(GtkWidget* widget,gpointer* data);
void connexionEntreprise1(GtkWidget* widget,gpointer* data);
void s_inscrireEntreprise(GtkWidget* btn,gpointer* data);
void s_inscrire(GtkWidget* btn,gpointer data);
void inscription(GtkWidget* btn,GtkWindow* parent);
void inscriptionEntreprise(GtkWidget* btn,GtkWindow* parent);
void connect(GtkWidget* btn,GtkWindow* parent);
void connexionEntreprise(GtkWidget* btn,GtkWindow* parent);
void RetourPage1(GtkWidget* widget,gpointer* parent);
void retour1(GtkWidget* widget,gpointer* data);

//affichage interface principal du programme
int main(int argc,char *argv[]){
    GtkButton  *connectbtn;
    GtkButton  *entreprise;
    GtkLabel *title;
    gtk_init(&argc,&argv);
    gchar *text;

    builder=gtk_builder_new();
    gtk_builder_add_from_file(builder,"demo.glade",NULL);
    window=GTK_WIDGET(gtk_builder_get_object(builder,"mywindow"));
    gtk_builder_connect_signals(builder,NULL);

    title=GTK_LABEL(gtk_builder_get_object(builder,"label1"));
    text=text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#BD2F2F\" size=\"xx-large\"><b>GESTION D'UNE SOCIETE D'INTER </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);


    connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"connect"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connect), NULL);

    entreprise=GTK_BUTTON(gtk_builder_get_object(builder,"entreprise"));
    g_signal_connect(GTK_BUTTON(entreprise), "clicked", G_CALLBACK(connexionEntreprise), NULL);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
//fonction qui fait le retour au menu principal pour les candidats
void RetourPage1(GtkWidget* widget,gpointer* parent){
     if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window3"));
    GtkLabel *title=GTK_LABEL(gtk_builder_get_object(builder,"titl"));
    gchar *text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#BD2F2F\" size=\"xx-large\"><b>Bienvenue dans votre espace de travail </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);
    gtk_widget_show_all(window);
   GtkButton *offre=GTK_BUTTON(gtk_builder_get_object(builder,"offre"));
    g_signal_connect(GTK_BUTTON(offre), "clicked", G_CALLBACK(gestionOffre), NULL);

    GtkButton *gestion=GTK_BUTTON(gtk_builder_get_object(builder,"gestion"));
    g_signal_connect(GTK_BUTTON(gestion), "clicked", G_CALLBACK(gestionCandidat), NULL);

}
//deconnecter
void deconnecter(GtkWidget* widget,gpointer* data){
    if(window!=NULL)
         gtk_widget_hide(window);
builder=gtk_builder_new();
    gtk_builder_add_from_file(builder,"demo.glade",NULL);
    window=GTK_WIDGET(gtk_builder_get_object(builder,"mywindow"));
    gtk_builder_connect_signals(builder,NULL);

   GtkLabel    *title=GTK_LABEL(gtk_builder_get_object(builder,"label1"));
    gchar *text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#BD2F2F\" size=\"xx-large\"><b>GESTION D'UNE SOCIETE D'INTER </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);
         gtk_widget_show_all(window);

GtkButton *connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"connect"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connect), NULL);

GtkButton *entreprise=GTK_BUTTON(gtk_builder_get_object(builder,"entreprise"));
    g_signal_connect(GTK_BUTTON(entreprise), "clicked", G_CALLBACK(connexionEntreprise), NULL);
}
//fonction qui retourne la chaine selectionne dans combo box
char *combo_box_active_get_text(GtkComboBox *combo_box)
{
  gchar *s_text = NULL;
  gboolean b_ret = FALSE;
  GtkTreeIter iter;
  b_ret = gtk_combo_box_get_active_iter (combo_box, &iter);
  if (b_ret)
  {
    GtkTreeModel *p_model = NULL;

    p_model = gtk_combo_box_get_model (combo_box);
    if (p_model != NULL)
    {
      gtk_tree_model_get (p_model, &iter, 0, &s_text, -1);
    }
  }
  return s_text;
}
//suppression d'un compte d'un comte candidat
void supprimerCompte(GtkWidget* widget,gpointer* data){
    GtkDialog *dialog;
    int x;
    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK_CANCEL,"voulez vous supprimer votre compte");
            gtk_window_set_title(GTK_WINDOW(dialog), "  ");
            gtk_dialog_run(GTK_DIALOG(dialog));

            int result = gtk_dialog_run (GTK_DIALOG (dialog));
if(result==GTK_RESPONSE_OK){
    x=supprimerFich(emailText,passwordText);
    if(x==0){
            gtk_widget_destroy(dialog);
        dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Votre compte est supprime");
            gtk_window_set_title(GTK_WINDOW(dialog), "SUCCESSFUL");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

            if(window!=NULL)
         gtk_widget_hide(window);

      builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"demo.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"mywindow"));
   gtk_widget_show_all(window);
    }
}

}
//modifier les infos d'un candidat
void modifierCompte(GtkWidget* widget,gpointer* data){
    GtkEntry *nom;
    GtkEntry *prenom;
    GtkEntry *password1;
    GtkEntry *adresse;
    GtkEntry *age;
    GtkEntry *stage;
    GtkEntry *projet;
    GtkEntry *exp;
    char *textnom;
    char *textprenom;
    char *textpass;
    char *textadr;
    char *textage;
    int nbp;
    int nbexp;
    int nbs;
    int age1;
    nom=GTK_ENTRY(gtk_builder_get_object(builder,"nom"));
    prenom=GTK_ENTRY(gtk_builder_get_object(builder,"prenom"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adresse"));
    password1=GTK_ENTRY(gtk_builder_get_object(builder,"mot"));
    age=GTK_ENTRY(gtk_builder_get_object(builder,"a"));
    stage=GTK_ENTRY(gtk_builder_get_object(builder,"stage"));
    projet=GTK_ENTRY(gtk_builder_get_object(builder,"projet"));
    exp=GTK_ENTRY(gtk_builder_get_object(builder,"exp"));
    textnom=gtk_entry_get_text(nom);
    textprenom=gtk_entry_get_text(prenom);
    textadr=gtk_entry_get_text(adresse);
    textpass=gtk_entry_get_text(password1);
    age1=atoi(gtk_entry_get_text(age));
    nbp=atoi(gtk_entry_get_text(projet));
    nbs=atoi(gtk_entry_get_text(stage));
    nbexp=atoi(gtk_entry_get_text(exp));
    Candidat p=retournerCandidat(emailText,passwordText);
    int x=modifierFich(p->email,p->password,textnom,textprenom,textadr,textpass,age1,nbs,nbp,nbexp);
    if(x==0){
            GtkDialog *dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"Candidat modifie");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

    }
}
//fonction qui fait le retour au menu principal pour les candidats
void RetourPage(GtkWidget* widget,gpointer* parent){
    if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"utilisateur.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
    GtkLabel *title=GTK_LABEL(gtk_builder_get_object(builder,"label1"));
    gchar *text=g_locale_to_utf8("<span face=\"Serif\" foreground=\"#8B5F65\" size=\"xx-large\"><b>Bienvenue dans votre espace de travail  </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);
        gtk_widget_show_all(window);
        GtkButton   *connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"profile"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(accederInfo), NULL);

    GtkButton   *liste_offre=GTK_BUTTON(gtk_builder_get_object(builder,"offre"));
    g_signal_connect(GTK_BUTTON(liste_offre), "clicked", G_CALLBACK(accederOffre), NULL);


}

//recuperer aux infos du candidat en cours et l'afficher  dans l'interface
void accederInfo(GtkWidget* widget,gpointer* parent){

     if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"prof.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window22"));
    gtk_widget_show_all(window);

    GtkEntry *nom;
    GtkEntry *prenom;
    GtkEntry *email1;
    GtkEntry *adresse;
    GtkEntry *mot_de_passe;
    GtkEntry *specialite;
    GtkEntry *age;
    GtkEntry *projets;
    GtkEntry *stage;
    GtkEntry *exp;
    GtkEntry *title;
    gchar *text;
    GtkButton *supprimer;
    GtkButton *modifier;

    char* textnom;
    char* textprenom;
    char* textemail1;
    char* textadresse;
    char* textmot_de_passe;
    char* textspecialite;
    char* textage;
    char* textexp;
    char* textprojet;
    char* textstage;
    int x;
    nom=GTK_ENTRY(gtk_builder_get_object(builder,"nom"));
    prenom=GTK_ENTRY(gtk_builder_get_object(builder,"prenom"));
    email1=GTK_ENTRY(gtk_builder_get_object(builder,"email"));
    mot_de_passe=GTK_ENTRY(gtk_builder_get_object(builder,"mot"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adresse"));
    specialite=GTK_ENTRY(gtk_builder_get_object(builder,"specialite"));
    age=GTK_ENTRY(gtk_builder_get_object(builder,"a"));
    exp=GTK_ENTRY(gtk_builder_get_object(builder,"exp"));
    stage=GTK_ENTRY(gtk_builder_get_object(builder,"stage"));
    projets=GTK_ENTRY(gtk_builder_get_object(builder,"projet"));
    char *xch=(char*)malloc(sizeof(char));
    char *nb_p=(char*)malloc(sizeof(char));
    char *nb_s=(char*)malloc(sizeof(char));
    char *nb_e=(char*)malloc(sizeof(char));


    Candidat p;
    p=retournerCandidat(emailText,passwordText);
     printf("\n%d",p->age);
     int z=8;
     gtk_entry_set_text(nom,p->nom);
     gtk_entry_set_text(prenom,p->prenom);
     gtk_entry_set_text(email1,p->email);
     gtk_entry_set_text(mot_de_passe,p->password);
     gtk_entry_set_text(adresse,p->adresse);
     gtk_entry_set_text(specialite,p->specialite);
     itoa(p->age,xch,10);
     gtk_entry_set_text(age,xch);
      itoa(p->nb_projet,nb_p,10);
     gtk_entry_set_text(projets,nb_p);
      itoa(p->nb_stage,nb_s,10);
     gtk_entry_set_text(stage,nb_s);
      itoa(p->nb_experience,nb_e,10);        //itoa pour la conversion d'un nombre vers une chaine de caractere
     gtk_entry_set_text(exp,nb_e);
     title=GTK_LABEL(gtk_builder_get_object(builder,"titre"));
    text=g_locale_to_utf8("<span face=\"Serif\" foreground=\"#40E0D0\" size=\"xx-large\"><b>Vos informations personnels</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

     supprimer=GTK_BUTTON(gtk_builder_get_object(builder,"supprimer"));
    g_signal_connect(GTK_BUTTON(supprimer), "clicked", G_CALLBACK(supprimerCompte), NULL);

   modifier=GTK_BUTTON(gtk_builder_get_object(builder,"modifier"));
    g_signal_connect(GTK_BUTTON(modifier), "clicked", G_CALLBACK(modifierCompte), NULL);
    GtkButton *retour=GTK_BUTTON(gtk_builder_get_object(builder,"retour"));
    g_signal_connect(GTK_BUTTON(retour), "clicked", G_CALLBACK(RetourPage), NULL);
    GtkButton  *deconnecterB=GTK_BUTTON(gtk_builder_get_object(builder,"b4"));
    g_signal_connect(GTK_BUTTON(deconnecterB), "clicked", G_CALLBACK(deconnecter), NULL);


}
//afficher liste des offres adequat pour le candidat en cours
void accederOffre(GtkWidget* widget,gpointer* data){
     if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"prof.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
    gtk_widget_show_all(window);
  GtkLabel * title=GTK_LABEL(gtk_builder_get_object(builder,"t"));
   gchar * text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#a4ddee\" size=\"medium\"><b>ManPower 124, Rabat Chellah </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"t2"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#a4ddee\" size=\"medium\"><b>Expertise/Innovation </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"t3"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"medium\"><b>Offres proposes :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"t4"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"small\"><b>Candidat :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"t5"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"small\"><b>Spécialités  :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    GtkLabel *date;
    GtkLabel *adresse;
    GtkLabel *specialite;
    GtkLabel *code;
    GtkLabel *nom;
    GtkTreeStore *tree;
     GtkTreeView *view;
     GtkTreeViewColumn *codeOff;
     GtkTreeViewColumn *entreprise;
     GtkTreeViewColumn *intitule;
     GtkTreeViewColumn *ville;
     GtkTreeViewColumn *renum;
     GtkTreeViewColumn *partir;
     GtkTreeViewColumn *mois;
     GtkTreeViewColumn *jour;
     GtkCellRenderer *c1;
    GtkCellRenderer *c2;
    GtkCellRenderer *c3;
    GtkCellRenderer *c4;
    GtkCellRenderer *c5;
    GtkCellRenderer *c6;
    GtkCellRenderer *c7;
    GtkCellRenderer *c8;

    nom=GTK_ENTRY(gtk_builder_get_object(builder,"label11"));
    date=GTK_ENTRY(gtk_builder_get_object(builder,"label23"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"label12"));
    specialite=GTK_ENTRY(gtk_builder_get_object(builder,"label14"));
    code=GTK_ENTRY(gtk_builder_get_object(builder,"label25"));
    time_t now;
    Candidat p;
    p=retournerCandidat(emailText,passwordText);

     time(&now);
        gtk_label_set_text(date,ctime(&now));
        gtk_label_set_text(adresse,p->adresse);
        gtk_label_set_text(specialite,p->specialite);
        gtk_label_set_text(nom,p->prenom);
        ListeOf *L=extraireOffre(p->specialite);

       tree=GTK_TREE_STORE(gtk_builder_get_object(builder,"treestore1"));
    view=GTK_TREE_VIEW(gtk_builder_get_object(builder,"treeview1"));
    codeOff=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"code_off"));
    entreprise=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"entreprise"));
    intitule=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"intitule"));
    ville=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"ville"));
    renum=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"renum"));
    partir=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"annee"));
    mois=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"mois"));
jour=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"jour"));
    c1=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c1"));
    c2=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c2"));
    c3=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c3"));
    c4=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c4"));
    c5=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c5"));
    c6=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c6"));
    c7=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c13"));
    c8=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c14"));

    gtk_tree_view_column_add_attribute(codeOff,c1,"text",0);
    gtk_tree_view_column_add_attribute(entreprise,c2,"text",1);
    gtk_tree_view_column_add_attribute(intitule,c3,"text",2);
    gtk_tree_view_column_add_attribute(ville,c4,"text",3);
    gtk_tree_view_column_add_attribute(renum,c5,"text",4);
    gtk_tree_view_column_add_attribute(partir,c6,"text",5);
     gtk_tree_view_column_add_attribute(mois,c7,"text",6);
      gtk_tree_view_column_add_attribute(jour,c8,"text",7);

    GtkTreeIter iter;
    char *datetext;
    char *m=(char*)malloc(sizeof(char));
     char *m1=(char*)malloc(sizeof(char));
      char *m2=(char*)malloc(sizeof(char));


    noeud3 *q=L;
    while(q!=NULL){
    printf("%s",q->off->nomEn);
    gtk_tree_store_append(tree,&iter,NULL);
    gtk_tree_store_set(tree,&iter,0,q->off->code,-1);
    gtk_tree_store_set(tree,&iter,1,q->off->nomEn,-1);
    gtk_tree_store_set(tree,&iter,2,q->off->poste,-1);
    gtk_tree_store_set(tree,&iter,3,q->off->ville,-1);
    gtk_tree_store_set(tree,&iter,4,q->off->salaire,-1);
    //gtk_tree_store_set(tree,&iter,6,m,-1);
    gtk_tree_store_set(tree,&iter,5,q->off->anneD,-1);
    gtk_tree_store_set(tree,&iter,6,q->off->moisD,-1);
    gtk_tree_store_set(tree,&iter,7,q->off->jourD,-1);
    q=q->suivant;
    }
   GtkButton *retour=GTK_BUTTON(gtk_builder_get_object(builder,"retou"));
    g_signal_connect(GTK_BUTTON(retour), "clicked", G_CALLBACK(RetourPage), NULL);
    GtkButton  *deconnecterB=GTK_BUTTON(gtk_builder_get_object(builder,"b"));
    g_signal_connect(GTK_BUTTON(deconnecterB), "clicked", G_CALLBACK(deconnecter), NULL);


}
//connexion candidat a son compte
void connexion(GtkWidget* widget,gpointer* data){

    GtkButton  *connectbtn;
    GtkWidget *dialog;
    GtkLabel *title;
    gchar *text;
    GtkButton *profile;

    email=GTK_ENTRY(gtk_builder_get_object(builder,"email"));
    password=GTK_ENTRY(gtk_builder_get_object(builder,"password"));
    emailText=(char*)gtk_entry_get_text(email);
    passwordText=(char*)gtk_entry_get_text(password);
   //if(chercherUtlisateur((char*)emailText,(char*)passwordText)==1){

   //}
   int x=se_connecter(emailText,passwordText);
   if(x==1){
    printf("connecte");
    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"vous etes connecte a votre compte avec succes");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

            if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"utilisateur.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
     title=GTK_LABEL(gtk_builder_get_object(builder,"label1"));
    text=text=g_locale_to_utf8("<span face=\"Serif\" foreground=\"#8B5F65\" size=\"xx-large\"><b>Bienvenue dans votre espace de travail  </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);
    gtk_widget_show_all(window);

    GtkButton   *connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"profile"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(accederInfo), NULL);

    GtkButton   *liste_offre=GTK_BUTTON(gtk_builder_get_object(builder,"offre"));
    g_signal_connect(GTK_BUTTON(liste_offre), "clicked", G_CALLBACK(accederOffre), NULL);

   }else{
   printf("incorrect");
           dialog= gtk_message_dialog_new(GTK_WINDOW(data),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"votre email ou votre mot de passe est incorrect");
            gtk_window_set_title(GTK_WINDOW(dialog), "Failed");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
   }
}
//vider les champs d'interface pour ajouter une nouvelle offre
void nouveauOffre(GtkWidget* widget,gpointer* data){
     GtkEntry *specialite;
    GtkEntry *etat;
    GtkEntry *salaire;
    GtkEntry *nomEn;
    GtkEntry *typeContrat;
    GtkEntry *anneD;
    GtkEntry *moisD;
    GtkEntry *jourD;
    GtkEntry *anneF;
    GtkEntry *moisF;
    GtkEntry *jourF;
    GtkEntry *adresse;
    GtkEntry *ville;
    GtkEntry *code;
    specialite=GTK_ENTRY(gtk_builder_get_object(builder,"specialite"));
    typeContrat=GTK_ENTRY(gtk_builder_get_object(builder,"type"));
    etat=GTK_ENTRY(gtk_builder_get_object(builder,"etat"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adress"));
    ville=GTK_ENTRY(gtk_builder_get_object(builder,"ville"));
    salaire=GTK_ENTRY(gtk_builder_get_object(builder,"salaire"));
    anneD=GTK_ENTRY(gtk_builder_get_object(builder,"anneD"));
    moisD=GTK_ENTRY(gtk_builder_get_object(builder,"moisD"));
    jourD=GTK_ENTRY(gtk_builder_get_object(builder,"jourD"));
    anneF=GTK_ENTRY(gtk_builder_get_object(builder,"anneF"));
    moisF=GTK_ENTRY(gtk_builder_get_object(builder,"moisF"));
    jourF=GTK_ENTRY(gtk_builder_get_object(builder,"jourF"));
    code=GTK_ENTRY(gtk_builder_get_object(builder,"code"));
gtk_entry_set_text(specialite," ");
gtk_entry_set_text(typeContrat," ");
gtk_entry_set_text(etat," ");
gtk_entry_set_text(adresse," ");
gtk_entry_set_text(ville," ");
gtk_entry_set_text(salaire," ");
gtk_entry_set_text(anneD," ");
gtk_entry_set_text(moisD," ");
gtk_entry_set_text(jourD," ");
gtk_entry_set_text(anneF," ");
gtk_entry_set_text(jourF," ");
gtk_entry_set_text(moisF," ");
gtk_entry_set_text(code," ");
   }
//recruter un candidat selectionner par l'entreprise
void recruterCandidat(GtkWidget* widget,gpointer* data){
    GtkEntry *nom;
    GtkEntry *prenom;
    GtkEntry *poste;
    GtkEntry *type;
    GtkEntry *adresse;
    GtkEntry *anneD;
    GtkEntry *moisD;
    GtkEntry *jourD;
    GtkEntry *anneF;
    GtkEntry *moisF;
    GtkEntry *jourF;
    GtkEntry *email;
    char *textnom;
    char *textprenom;
    char *texttype;
    char *textposte;
    char *textmail;
    char *textadresse;
    int anneD1;
    int moisD1;
    int jourD1;
    int anneF1;
    int moisF1;
    int jourF1;
    poste=GTK_ENTRY(gtk_builder_get_object(builder,"poste"));
    nom=GTK_ENTRY(gtk_builder_get_object(builder,"nom2"));
    prenom=GTK_ENTRY(gtk_builder_get_object(builder,"prenom2"));
    type=GTK_ENTRY(gtk_builder_get_object(builder,"type"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adresse2"));
    email=GTK_ENTRY(gtk_builder_get_object(builder,"email2"));
    anneD=GTK_ENTRY(gtk_builder_get_object(builder,"d1"));
    moisD=GTK_ENTRY(gtk_builder_get_object(builder,"d2"));
    jourD=GTK_ENTRY(gtk_builder_get_object(builder,"d3"));
    anneF=GTK_ENTRY(gtk_builder_get_object(builder,"f1"));
    moisF=GTK_ENTRY(gtk_builder_get_object(builder,"f2"));
    jourF=GTK_ENTRY(gtk_builder_get_object(builder,"f3"));
    textposte=gtk_entry_get_text(poste);
    textnom=gtk_entry_get_text(nom);
    textprenom=gtk_entry_get_text(prenom);
    texttype=gtk_entry_get_text(type);
    textmail=gtk_entry_get_text(email);
    textadresse=gtk_entry_get_text(adresse);
    anneD1=atoi(gtk_entry_get_text(anneD));
    moisD1=atoi(gtk_entry_get_text(moisD));
    jourD1=atoi(gtk_entry_get_text(jourD));
    anneF1=atoi(gtk_entry_get_text(anneF));
    moisF1=atoi(gtk_entry_get_text(moisF));
    jourF1=atoi(gtk_entry_get_text(jourF));
    printf("%s,%s,%s,%s",textnom,textprenom,textmail,texttype);
    Entreprise p=retournerEntreprise(emailText,passwordText);
    int x=enregistrerRecrutement(p->code,textnom,textprenom,texttype,textadresse,textmail,textposte,jourD1,moisD1,anneD1,jourF1,moisF1,anneF1);
    if(x==0){
        GtkWidget *dialog = dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"Recrutement est bien enregistre");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
    }
   }
//transferer les donnes d'un candidat selectionne au formulaire de recrutement
void afficherRecrutement(gchar *nom,gchar *prenom,gchar *email,gchar *adresse){
    GtkEntry *nom1;
    GtkEntry *prenom1;
    GtkEntry *poste;
    GtkEntry *type;
    GtkEntry *adresse1;
    GtkEntry *email1;
    GtkEntry *deb1;
    GtkEntry *deb2;
    GtkEntry *deb3;
    GtkEntry *fin1;
    GtkEntry *fin2;
    GtkEntry *fin3;
    nom1=GTK_ENTRY(gtk_builder_get_object(builder,"nom2"));
    prenom1=GTK_ENTRY(gtk_builder_get_object(builder,"prenom2"));
    poste=GTK_ENTRY(gtk_builder_get_object(builder,"poste"));
    type=GTK_ENTRY(gtk_builder_get_object(builder,"type"));
    adresse1=GTK_ENTRY(gtk_builder_get_object(builder,"adresse2"));
    email1=GTK_ENTRY(gtk_builder_get_object(builder,"email2"));
    deb1=GTK_ENTRY(gtk_builder_get_object(builder,"d1"));
    deb2=GTK_ENTRY(gtk_builder_get_object(builder,"d2"));
    deb3=GTK_ENTRY(gtk_builder_get_object(builder,"d3"));
    fin1=GTK_ENTRY(gtk_builder_get_object(builder,"f1"));
    fin2=GTK_ENTRY(gtk_builder_get_object(builder,"f2"));
    fin3=GTK_ENTRY(gtk_builder_get_object(builder,"f3"));
    gtk_entry_set_text(nom1,nom);
    gtk_entry_set_text(prenom1,prenom);
    gtk_entry_set_text(email1,email);
    gtk_entry_set_text(adresse1,adresse);

    GtkButton *recruter=GTK_BUTTON(gtk_builder_get_object(builder,"recruter"));
    g_signal_connect(GTK_BUTTON(recruter), "clicked", G_CALLBACK(recruterCandidat),NULL);

}
//selectionner la ligne active par curseur en double cliquant
void view_onRowActivated (GtkTreeView *treeview,GtkTreePath *path,GtkTreeViewColumn *col,gpointer            userdata)
  {
    GtkTreeModel *model;
    GtkTreeIter   iter;
    model = gtk_tree_view_get_model(treeview);
    gchar *nom,*prenom,*adresse,*email;
    if (gtk_tree_model_get_iter(model, &iter, path))
    {
       gchar *name;

       gtk_tree_model_get(model, &iter, 1,&nom, -1);
       gtk_tree_model_get(model, &iter, 2, &prenom, -1);
       gtk_tree_model_get(model, &iter, 3, &email, -1);
       gtk_tree_model_get(model, &iter, 4, &adresse, -1);
       printf("%s",nom);

       afficherRecrutement(nom,prenom,email,adresse);
    }
  }

//afficher les candidats qui repond au critere d'une offre selon specialite et en triant leur age nb projet ,experience et stages
void gestionCandidat(GtkWidget* widget,gpointer* data){
     if(window!=NULL)
        gtk_widget_hide(window);
              GtkLabel *title;
              gchar *text;
              builder = gtk_builder_new();
             gtk_builder_add_from_file (builder,"prof.glade", NULL);
              window = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
             gtk_widget_show_all(window);
     title=GTK_LABEL(gtk_builder_get_object(builder,"titre1"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#a4ddee\" size=\"medium\"><b>ManPower 124, Rabat Chellah </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"titre2"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#a4ddee\" size=\"medium\"><b>Expertise/Innovation </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"titre3"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"medium\"><b>Candidat proposes :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"titre4"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"small\"><b>Entreprise :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    title=GTK_LABEL(gtk_builder_get_object(builder,"titre5"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"small\"><b>Spécialités  :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

     title=GTK_LABEL(gtk_builder_get_object(builder,"t1"));
    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000080\" size=\"x-large\"><b>Choisissez le profil a recruter   :</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

    GtkLabel *date;
    GtkLabel *adresse12;
    GtkLabel *specialite;
    GtkLabel *code12;
    GtkLabel *nomEn;
    GtkTreeStore *tree;
     GtkTreeView *view;
     GtkTreeViewColumn *code;
     GtkTreeViewColumn *nom;
     GtkTreeViewColumn *prenom;
     GtkTreeViewColumn *email;
     GtkTreeViewColumn *adresse;
     GtkTreeViewColumn *age;
     GtkTreeViewColumn *nb_projet;
     GtkTreeViewColumn *nb_exp;
     GtkTreeViewColumn *nb_stage;
     GtkCellRenderer *c1;
    GtkCellRenderer *c2;
    GtkCellRenderer *c3;
    GtkCellRenderer *c4;
    GtkCellRenderer *c5;
    GtkCellRenderer *c6;
    GtkCellRenderer *c7;
    GtkCellRenderer *c8;
    GtkCellRenderer *c9;
    int  day, mois, an;
    date=GTK_LABEL(gtk_builder_get_object(builder,"label16"));
    adresse12=GTK_LABEL(gtk_builder_get_object(builder,"label19"));
    specialite=GTK_LABEL(gtk_builder_get_object(builder,"label21"));
    code12=GTK_LABEL(gtk_builder_get_object(builder,"label26"));
    nomEn=GTK_LABEL(gtk_builder_get_object(builder,"label18"));
    time_t now;
    Entreprise p;
    p=retournerEntreprise(emailText,passwordText);
     time(&now);
       gtk_label_set_text(date,ctime(&now));
        gtk_label_set_text(adresse12,p->adresse);
        gtk_label_set_text(specialite,p->specialite);
        gtk_label_set_text(nomEn,p->nom_entreprise);
        //gtk_label_set_text(code12,p->code
       Liste *L=extraireCandidat(p->specialite);

        noeud *q=L;
  if(q!=NULL){
        afficherCandidat(L);

   tree=GTK_TREE_STORE(gtk_builder_get_object(builder,"treestore2"));
    view=GTK_TREE_VIEW(gtk_builder_get_object(builder,"treeview2"));
    code=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"code"));
    nom=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"prenom"));
    prenom=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"intitule"));
    email=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"email"));
    adresse=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"adresse"));
    age=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"age"));
    nb_projet=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"nb_projet"));
    nb_exp=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"nb_exp"));
    nb_stage=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"nb_stage"));
    c1=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c7"));
    c2=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c8"));
    c3=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c9"));
    c4=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c10"));
    c5=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c11"));
    c6=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c12"));
    c7=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c13"));
    c8=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c14"));
    c9=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c15"));

    gtk_tree_view_column_add_attribute(code,c1,"text",0);
    gtk_tree_view_column_add_attribute(nom,c2,"text",1);
    gtk_tree_view_column_add_attribute(prenom,c3,"text",2);
    gtk_tree_view_column_add_attribute(email,c4,"text",3);
    gtk_tree_view_column_add_attribute(adresse,c5,"text",4);
    gtk_tree_view_column_add_attribute(age,c6,"text",5);
    gtk_tree_view_column_add_attribute(nb_projet,c7,"text",6);
    gtk_tree_view_column_add_attribute(nb_exp,c8,"text",7);
    gtk_tree_view_column_add_attribute(nb_stage,c9,"text",8);

    GtkTreeIter iter;
    char *datetext;


    while(q!=NULL){
    //printf("%s",q->off->nomEn);
    gtk_tree_store_append(tree,&iter,NULL);
    gtk_tree_store_set(tree,&iter,0,q->c1->code,-1);
    gtk_tree_store_set(tree,&iter,1,q->c1->nom,-1);
    gtk_tree_store_set(tree,&iter,2,q->c1->prenom,-1);
    gtk_tree_store_set(tree,&iter,3,q->c1->email,-1);
    gtk_tree_store_set(tree,&iter,4,q->c1->adresse,-1);
    gtk_tree_store_set(tree,&iter,5,q->c1->age,-1);
    gtk_tree_store_set(tree,&iter,6,q->c1->nb_projet,-1);
    gtk_tree_store_set(tree,&iter,7,q->c1->nb_experience,-1);
    gtk_tree_store_set(tree,&iter,9,q->c1->nb_stage,-1);
    q=q->suivant;
    }
  }
  GtkButton  *deconnecterB=GTK_BUTTON(gtk_builder_get_object(builder,"b2"));
    g_signal_connect(GTK_BUTTON(deconnecterB), "clicked", G_CALLBACK(deconnecter), NULL);

     GtkButton  *retour=GTK_BUTTON(gtk_builder_get_object(builder,"tt"));
    g_signal_connect(GTK_BUTTON(retour), "clicked", G_CALLBACK(RetourPage1), NULL);
   g_signal_connect(view, "row-activated", (GCallback) view_onRowActivated, NULL);


}
//ajouter une nouvelle offre au fichier des offres
   void ajouterOffre(GtkWidget* widget,gpointer* data){
    GtkComboBox *specialite;
    GtkComboBox *etat;
    GtkEntry *salaire;
    GtkEntry *nomEn;
    GtkComboBox *typeContrat;
    GtkEntry *anneD;
    GtkEntry *moisD;
    GtkEntry *jourD;
    GtkEntry *anneF;
    GtkEntry *moisF;
    GtkEntry *jourF;
    GtkEntry *adresse;
    GtkEntry *ville;
    GtkEntry *poste;
    GtkEntry *code;
    char *textspecialite;
    char *textType;
    char *textEtat;
    char *textAdresse;
    char *textVille;
    char *textposte;
    char *nom;
    int salaire1;
    char *code1;
    int anneD1;
    int moisD1;
    int jourD1;
    int anneF1;
    int moisF1;
    int jourF1;
    specialite=GTK_COMBO_BOX(gtk_builder_get_object(builder,"specialite"));
    typeContrat=GTK_ENTRY(gtk_builder_get_object(builder,"type"));
    etat=GTK_COMBO_BOX(gtk_builder_get_object(builder,"etat"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adress"));
    nomEn=GTK_ENTRY(gtk_builder_get_object(builder,"nomEn"));
    ville=GTK_ENTRY(gtk_builder_get_object(builder,"ville"));
    poste=GTK_ENTRY(gtk_builder_get_object(builder,"poste"));
    salaire=GTK_ENTRY(gtk_builder_get_object(builder,"salaire"));
    anneD=GTK_ENTRY(gtk_builder_get_object(builder,"anneD"));
    moisD=GTK_ENTRY(gtk_builder_get_object(builder,"moisD"));
    jourD=GTK_ENTRY(gtk_builder_get_object(builder,"jourD"));
    anneF=GTK_ENTRY(gtk_builder_get_object(builder,"anneF"));
    moisF=GTK_ENTRY(gtk_builder_get_object(builder,"moisF"));
    jourF=GTK_ENTRY(gtk_builder_get_object(builder,"jourF"));
    code=GTK_ENTRY(gtk_builder_get_object(builder,"code"));
    textspecialite=combo_box_active_get_text(specialite);
    textEtat=combo_box_active_get_text(etat);
    textType=combo_box_active_get_text(typeContrat);
    textVille=gtk_entry_get_text(ville);
    textAdresse=gtk_entry_get_text(adresse);
    textposte=gtk_entry_get_text(poste);
    nom=gtk_entry_get_text(nomEn);
    salaire1=atoi(gtk_entry_get_text(salaire));
    anneD1=atoi(gtk_entry_get_text(anneD));
    moisD1=atoi(gtk_entry_get_text(moisD));
    jourD1=atoi(gtk_entry_get_text(jourD));
    anneF1=atoi(gtk_entry_get_text(anneF));
    moisF1=atoi(gtk_entry_get_text(moisF));
    jourF1=atoi(gtk_entry_get_text(jourF));
    code1=gtk_entry_get_text(code);
    printf("%s",textspecialite);
   int x=enregistrerOffre(code1,textspecialite,textEtat,salaire1,nom,textType,textAdresse,textVille,textposte,anneD1,moisD1,jourD1,anneF1,moisF1,jourF1);
    if(x==0){
            GtkDialog *dialog = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"Offre enregistre");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
    }else{
        GtkDialog *dialog = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"offre non enregistre");
            gtk_window_set_title(GTK_WINDOW(dialog), "Failed");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
    }
   }
   //afficher l'interface de gestion offre et un tableau qui rassemble les offres cree par l'entreprise courant
void gestionOffre(GtkWidget* widget,gpointer* data){
    GtkButton  *ajouter;
    GtkButton  *nouveau;
    GtkButton  *modifier;
    GtkLabel *title;
    gchar *text;
    if(window!=NULL)
        gtk_widget_hide(window);

              builder = gtk_builder_new();
             gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
              window = GTK_WIDGET(gtk_builder_get_object(builder,"window4"));
              title=GTK_LABEL(gtk_builder_get_object(builder,"titre2"));
            text=text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#E6AA22\" size=\"xx-large\"><b>Creer une nouvelle offre </b></span>\n", -1, NULL, NULL, NULL);
           gtk_label_set_text(title,text);
           gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
            gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
            g_free(text);
            title=GTK_LABEL(gtk_builder_get_object(builder,"t7"));
            text=text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#E6AA22\" size=\"xx-large\"><b>Liste de vos offres </b></span>\n", -1, NULL, NULL, NULL);
           gtk_label_set_text(title,text);
           gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
            gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
            g_free(text);

    Entreprise p;
    p=retournerEntreprise(emailText,passwordText);
    printf("%s",p->code);
    ListeOf *l1=extraireListeOffre();
    noeud3 *q=NULL;
    q=l1;
    afficherOffre(l1);
    GtkTreeStore *tree;
     GtkTreeView *view;
     GtkTreeViewColumn *poste;
     GtkTreeViewColumn *salaire;
     GtkTreeViewColumn *type;
     GtkTreeViewColumn *d1;
     GtkTreeViewColumn *d2;
     GtkTreeViewColumn *d3;
     GtkTreeViewColumn *f1;
     GtkTreeViewColumn *f2;
     GtkTreeViewColumn *f3;
     GtkCellRenderer *c1;
    GtkCellRenderer *c2;
    GtkCellRenderer *c3;
    GtkCellRenderer *c4;
    GtkCellRenderer *c5;
    GtkCellRenderer *c6;
    GtkCellRenderer *c7;
    GtkCellRenderer *c8;
    GtkCellRenderer *c9;

       tree=GTK_TREE_STORE(gtk_builder_get_object(builder,"treestore1"));
    view=GTK_TREE_VIEW(gtk_builder_get_object(builder,"treeview1"));
    poste=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"poste"));
    salaire=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"salaire"));
    type=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"type"));
    d1=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"deb1"));
    d2=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"deb2"));
    d3=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"deb3"));
    f1=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"fin1"));
    f2=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"fin2"));
    f3=GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder,"fin3"));
    c1=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c1"));
    c2=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c2"));
    c3=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c3"));
    c4=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c4"));
    c5=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c5"));
    c6=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c6"));
    c7=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c7"));
    c8=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c8"));
    c9=GTK_CELL_RENDERER(gtk_builder_get_object(builder,"c9"));

    gtk_tree_view_column_add_attribute(poste,c1,"text",0);
    gtk_tree_view_column_add_attribute(salaire,c2,"text",1);
    gtk_tree_view_column_add_attribute(type,c3,"text",2);
    gtk_tree_view_column_add_attribute(d1,c4,"text",3);
    gtk_tree_view_column_add_attribute(d2,c5,"text",4);
    gtk_tree_view_column_add_attribute(d3,c6,"text",5);
     gtk_tree_view_column_add_attribute(f1,c7,"text",6);
    gtk_tree_view_column_add_attribute(f2,c8,"text",7);
    gtk_tree_view_column_add_attribute(f3,c9,"text",8);

    GtkTreeIter iter;
    while(q!=NULL){
    if(strcmp(q->off->code,p->code)==0){
            printf("%s\n",q->off->code);
    gtk_tree_store_append(tree,&iter,NULL);
    gtk_tree_store_set(tree,&iter,0,q->off->poste,-1);
    //gtk_tree_store_set(tree,&iter,1,q->off->salaire,-1);
    gtk_tree_store_set(tree,&iter,2,q->off->typeContrat,-1);
    gtk_tree_store_set(tree,&iter,3,q->off->anneD,-1);
    gtk_tree_store_set(tree,&iter,4,q->off->moisD,-1);
    gtk_tree_store_set(tree,&iter,5,q->off->jourD,-1);
    gtk_tree_store_set(tree,&iter,6,q->off->anneF,-1);
    gtk_tree_store_set(tree,&iter,7,q->off->moisF,-1);
    gtk_tree_store_set(tree,&iter,8,q->off->jourF,-1);
    }
    q=q->suivant;
    }
             gtk_widget_show_all(window);

            ajouter=GTK_BUTTON(gtk_builder_get_object(builder,"ajouter"));
           g_signal_connect(GTK_BUTTON(ajouter), "clicked", G_CALLBACK(ajouterOffre),NULL);

            nouveau=GTK_BUTTON(gtk_builder_get_object(builder,"nouveau"));
    g_signal_connect(GTK_BUTTON(nouveau), "clicked", G_CALLBACK(nouveauOffre), NULL);

          GtkButton  *deconnecterB=GTK_BUTTON(gtk_builder_get_object(builder,"b"));
    g_signal_connect(GTK_BUTTON(deconnecterB), "clicked", G_CALLBACK(deconnecter), NULL);
     GtkButton  *retour=GTK_BUTTON(gtk_builder_get_object(builder,"tt"));
    g_signal_connect(GTK_BUTTON(retour), "clicked", G_CALLBACK(RetourPage1), NULL);

}
//connexion entreprise a son compte
void connexionEntreprise1(GtkWidget* widget,gpointer* data){

    GtkButton  *connectbtn;
    GtkWidget *dialog;
    GtkButton *profile;
    GtkComboBoxText *offre_choix;
    GtkButton *offre;


    email=GTK_ENTRY(gtk_builder_get_object(builder,"email"));
    password=GTK_ENTRY(gtk_builder_get_object(builder,"password"));
    emailText=(char*)gtk_entry_get_text(email);
    passwordText=(char*)gtk_entry_get_text(password);

   int x=se_connecterEn(emailText,passwordText);
   if(x==1){
    printf("connecte");
    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"vous etes connecte a votre compte avec succes");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

            if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window3"));
    GtkLabel *title=GTK_LABEL(gtk_builder_get_object(builder,"titl"));
    gchar *text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#BD2F2F\" size=\"xx-large\"><b>Bienvenue dans votre espace de travail </b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);
    gtk_widget_show_all(window);
    offre=GTK_BUTTON(gtk_builder_get_object(builder,"offre"));
    g_signal_connect(GTK_BUTTON(offre), "clicked", G_CALLBACK(gestionOffre), NULL);

    GtkButton *gestion=GTK_BUTTON(gtk_builder_get_object(builder,"gestion"));
    g_signal_connect(GTK_BUTTON(gestion), "clicked", G_CALLBACK(gestionCandidat), NULL);
   }else{
   printf("incorrect");
           dialog= gtk_message_dialog_new(GTK_WINDOW(data),GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"votre email ou votre mot de passe est incorrect");
            gtk_window_set_title(GTK_WINDOW(dialog), "Failed");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
   }

}
//inscription entreprise
void s_inscrireEntreprise(GtkWidget* btn,gpointer* data){
    GtkEntry *nom;
    GtkEntry *mail;
    GtkEntry *adresse;
    GtkEntry *password1;
    GtkEntry *password2;
    GtkEntry *code;
    GtkComboBox *specialite;

    char* textnom;
    char* textmail;
    char* textadresse;
    char* textpassword1;
    char* textpassword2;
    char* textspecialite;
    char* cin;
    int x;
    nom=GTK_ENTRY(gtk_builder_get_object(builder,"nom"));
    mail=GTK_ENTRY(gtk_builder_get_object(builder,"mail"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adresse"));
    password1=GTK_ENTRY(gtk_builder_get_object(builder,"password1"));
    password2=GTK_ENTRY(gtk_builder_get_object(builder,"password2"));
    specialite=GTK_COMBO_BOX(gtk_builder_get_object(builder,"specialit"));
    code=password2=GTK_ENTRY(gtk_builder_get_object(builder,"cod"));
    printf("hii\n");
    textnom=(char*)gtk_entry_get_text(nom);
    textmail=(char*)gtk_entry_get_text(mail);
    textadresse=(char*)gtk_entry_get_text(adresse);
    password1=(char*)gtk_entry_get_text(password1);
    password2=(char*)gtk_entry_get_text(password2);
    textspecialite=combo_box_active_get_text(specialite);
    cin=(char*)gtk_entry_get_text(code);
    printf("hii\n");
    printf("%s\n" ,textadresse);
    printf(" %s %s %s %s %s %s %s",cin,textnom,textmail,password1,textadresse,textspecialite,password2);

    if(strcmp(password1,password2)!=0){
            printf("hii\n");
            x=enregistrerEntreprise(cin,textnom,password1,textmail,textadresse,textspecialite);
            if(x==0){
               GtkWidget *dialog = dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"vous etes inscrit");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

             if(window!=NULL)
         gtk_widget_hide(window);

              builder = gtk_builder_new();
             gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
              window = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
             gtk_widget_show_all(window);

           GtkButton   *connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"se_connecter"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connexionEntreprise1), NULL);
}
    }
}
//inscription candidat
void s_inscrire(GtkWidget* btn,gpointer data){
    GtkEntry *nom;
    GtkEntry *prenom;
    GtkEntry *email1;
    GtkEntry *adresse;
    GtkEntry *mot_de_passe;
    GtkComboBox *specialite;
    GtkEntry *age;
    GtkEntry *nb_stage;
    GtkEntry *nb_projet;
    GtkEntry *nb_experience;
    //GtkDialog *dialog;

    char* textnom;
    char* textprenom;
    char* textemail1;
    char* textadresse;
    char* textmot_de_passe;
    char* textspecialite;
    int age1;
    int stage;
    int projet;
    int exp;
    int x;
    nom=GTK_ENTRY(gtk_builder_get_object(builder,"nom"));
    prenom=GTK_ENTRY(gtk_builder_get_object(builder,"prenom"));
    email1=GTK_ENTRY(gtk_builder_get_object(builder,"email"));
    mot_de_passe=GTK_ENTRY(gtk_builder_get_object(builder,"mot_passe"));
    adresse=GTK_ENTRY(gtk_builder_get_object(builder,"adresse"));
    specialite=GTK_COMBO_BOX(gtk_builder_get_object(builder,"specialite1"));
    age=GTK_ENTRY(gtk_builder_get_object(builder,"age"));
    nb_stage=GTK_ENTRY(gtk_builder_get_object(builder,"stage"));
    nb_projet=GTK_ENTRY(gtk_builder_get_object(builder,"projet"));
    nb_experience=GTK_ENTRY(gtk_builder_get_object(builder,"exp"));

    textnom=(char*)gtk_entry_get_text(nom);
    textprenom=(char*)gtk_entry_get_text(prenom);
    textemail1=(char*)gtk_entry_get_text(email1);
    textmot_de_passe=(char*)gtk_entry_get_text(mot_de_passe);
    textadresse=(char*)gtk_entry_get_text(adresse);
    textspecialite=combo_box_active_get_text(specialite);
    printf("%s\n",textspecialite);
    age1=atoi(gtk_entry_get_text(age));
    stage=atoi(gtk_entry_get_text(nb_stage));
    projet=atoi(gtk_entry_get_text(nb_projet));
    exp=atoi(gtk_entry_get_text(nb_experience));

    GtkButton *connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"s_inscrire"));
    printf("%s %s %s %s %s %s %d %d %d %d",textnom,textprenom,textemail1,textmot_de_passe,textadresse,textspecialite,age1,projet,exp,stage);

   // if(!textnom &&!textprenom && !textmot_de_passe && !textemail1 && !textadresse && !textspecialite){
        x=enregistrerCandidat(textnom,textprenom,textemail1,textmot_de_passe,textadresse,textspecialite,age1,stage,projet,exp);
            printf("%d",x);
            if(x==0){
               GtkWidget *dialog = dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"vous etes inscrit");
            gtk_window_set_title(GTK_WINDOW(dialog), "Successful");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

             if(window!=NULL)
         gtk_widget_hide(window);

              builder = gtk_builder_new();
             gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
              window = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
             gtk_widget_show_all(window);

           GtkButton   *connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"se_connecter"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connexion), NULL);

}
}
//affichage interface inscription candidat
void inscription(GtkWidget* btn,GtkWindow* parent){
     GtkLabel *title;
    gchar *text;
    GtkButton *inscrire;
    if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"inscription.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window3"));
    title=GTK_LABEL(gtk_builder_get_object(builder,"label11"));
    text=text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#8DC5A4\" size=\"xx-large\"><b>Créer votre compte</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

   gtk_widget_show_all(window);

   inscrire=GTK_LINK_BUTTON(gtk_builder_get_object(builder,"s_inscrire"));
    g_signal_connect(GTK_LINK_BUTTON(inscrire),"clicked",G_CALLBACK(s_inscrire),NULL);
     GtkButton *retour=GTK_BUTTON(gtk_builder_get_object(builder,"retour"));
    g_signal_connect(GTK_BUTTON(retour), "clicked", G_CALLBACK(retour1), NULL);

}

//affichage interface inscription entreprise
void inscriptionEntreprise(GtkWidget* btn,GtkWindow* parent){
    GtkLabel *title;
    gchar *text;
    GtkButton *inscrire;
    if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
   gtk_widget_show_all(window);
    title=GTK_LABEL(gtk_builder_get_object(builder,"title"));
    text=text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#8fb178\" size=\"xx-large\"><b>Créer votre compte</b></span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_text(title,text);
    gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);
        g_free(text);

   inscrire=GTK_LINK_BUTTON(gtk_builder_get_object(builder,"inscrireEn"));
    g_signal_connect(GTK_LINK_BUTTON(inscrire),"clicked",G_CALLBACK(s_inscrireEntreprise),NULL);

}
void retour1(GtkWidget* widget,gpointer* data){
 if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
   gtk_widget_show_all(window);

    GtkButton  * connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"se_connecter"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connexion), NULL);

    GtkButton  * insc=GTK_LINK_BUTTON(gtk_builder_get_object(builder,"linkInscription"));
    g_signal_connect(GTK_LINK_BUTTON(insc),"clicked",G_CALLBACK(inscription),NULL);

}
//affichage interface connxion candidat
void connect(GtkWidget* btn,GtkWindow* parent){

    GtkButton  *connectbtn;
     GtkLinkButton *insc;
     GtkButton *tt;

  if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
   gtk_widget_show_all(window);

    connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"se_connecter"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connexion), NULL);

    insc=GTK_LINK_BUTTON(gtk_builder_get_object(builder,"linkInscription"));
    g_signal_connect(GTK_LINK_BUTTON(insc),"clicked",G_CALLBACK(inscription),NULL);


}
//affichage interface connxion entreprise
void connexionEntreprise(GtkWidget* btn,GtkWindow* parent){

    GtkButton  *connectbtn;
     GtkLinkButton *insc;
     GtkButton *tt;

  if(window!=NULL)
         gtk_widget_hide(window);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder,"se_connecter.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
   gtk_widget_show_all(window);

    connectbtn=GTK_BUTTON(gtk_builder_get_object(builder,"se_connecter"));
    g_signal_connect(GTK_BUTTON(connectbtn), "clicked", G_CALLBACK(connexionEntreprise1), NULL);

    insc=GTK_LINK_BUTTON(gtk_builder_get_object(builder,"linkInscription"));
    g_signal_connect(GTK_LINK_BUTTON(insc),"clicked",G_CALLBACK(inscriptionEntreprise),NULL);


}



