#include <iostream>
#include <string>
#include <random>       // Librairie pour utiliser la génération aléatoire 
#include <ctime>        // Librairie pour utiliser le temps
#define NULL 0;
using namespace std;





/***************************************	Q.0	 *******************************************/

struct t_maillon {

  string chaine;
  t_maillon *suivant;
};

//----------------------------------------------------
//---------------------- 0.a -------------------------
/*
 * Rôle: Ajouter une chaine au début d'une liste.
 * Précondition: p_deb est déjà alloué, et sa fin marqué en nullptr.
 * @param string chaine
 * @param t_maillon *p_deb
 **/
void ajouterDebut(string chaine, t_maillon *&p_deb){
 
 if(p_deb->suivant == nullptr && p_deb->chaine == ""){ // le cas d'une liste vide.
  p_deb->chaine = chaine;

 }else{
  t_maillon *p_m = p_deb;
  p_deb = new t_maillon;
  p_deb->suivant = p_m;
  p_deb->chaine = chaine;
 }
}

//----------------------------------------------------
//---------------------- 0.b -------------------------
/*
 * Rôle: Ajouter une chaine à la fin d'une liste.
 * Précondition: p_deb est déjà alloué, et sa fin marqué en nullptr.
 * @param string chaine
 * @param t_maillon *p_deb
 **/
void ajouterFin(string chaine, t_maillon *&p_deb){
  
  t_maillon *p_m;
  p_m = p_deb;

  while(p_m->suivant != nullptr){

    p_m = p_m->suivant;
  }
  p_m->suivant = new t_maillon;
  p_m = p_m->suivant;
  p_m->chaine = chaine;
  p_m->suivant = nullptr;
}

//----------------------------------------------------
//---------------------- 0.c -------------------------
/*
 * Rôle: Supprimer une case au début d'une liste.
 * Précondition: p_deb est déjà alloué, et sa fin marqué en nullptr.
 * @param t_maillon *p_deb
 **/
void supprimerDebut(t_maillon *&p_deb){ 

  if(p_deb->suivant != nullptr){ // si la liste est plus d'une case.
    t_maillon *p_m;
    p_m = p_deb->suivant;
    delete p_deb;
    p_deb = p_m;

  }else{ // si la liste est une seule case.
    p_deb = new t_maillon;
    p_deb->suivant = nullptr;
  }
}

//----------------------------------------------------
//---------------------- 0.d -------------------------
/*
 * Rôle: Supprimer une case à la fin d'une liste.
 * Précondition: p_deb est déjà alloué, et sa fin marqué en nullptr.
 * @param t_maillon *p_deb
 **/
void supprimerFin(t_maillon *&p_deb){

  if(p_deb->suivant != nullptr){ // si la liste est plus d'une case.
    t_maillon *p_m;
    p_m = p_deb;

    while (p_m->suivant->suivant != nullptr){ // quitter à la case avant la dérnière.
      p_m = p_m->suivant;
    }
    delete p_m->suivant->suivant;
    p_m->suivant = nullptr;

  }else{ // si la liste est une seule case.
    p_deb = new t_maillon;
    p_deb->suivant = nullptr;
  }
}

/***************************************	Q.1	 *******************************************/


//----------------------------------------------------
//--- Fonction donne_pseudo():chaîne de caractères ---
//----------------------------------------------------

/* 
  Cette fonction retourne une chaine de caractères aléatoire composée de 4 lettres et deux chiffres
*/
string donne_pseudo(){
  string pseudo = "";
  char consonne[20] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};  //tableau de consonnes
  char voyelle[6] = {'a','e','i','o','u','y'};            //tableau de voyelles

  for (int i=0; i<2; i++){                    //boucle de génération de la chaine de lettres
    pseudo = pseudo + consonne[rand()%20];    //tire au hasard un chiffre entre 0 et 20 puis ajoute la lettre correspondante au pseudo  
    pseudo = pseudo + voyelle[rand()%6];      //tire au hasard un chiffre entre 0 et 6 puis ajoute la lettre correspondante au pseudo  
  }
  for (int i=0; i<2; i++){                    //boucle de génération des deux chiffres
    pseudo = pseudo + to_string(rand()%9);    //tire au hasard un chiffre entre 0 et 9 puis le convertit en chaine de caractères avant de l'ajouter au pseudo  
  }
  return pseudo;
}
/*
int main(){
  srand(time(0));//initialisation de random par time() Doit être appelé une seule et unique fois dans le main avant tout appel de la fonction donne_pseudo()
  cout << donne_pseudo() << endl;
}
*/

//----------------------------------------------------
//---------------------- 1.a -------------------------
/*
 * Rôle: Construir une liste d'une capacité capa et la remplir en utilisant la fonction donne_pseudo().
 * Précondition: capa>=0.
 * @param int capa
 **/
t_maillon* construirListe(int capa){

  t_maillon *p_deb = new t_maillon;
  p_deb->suivant = nullptr;

  for (int i=0; i<capa; i++){
    ajouterDebut(donne_pseudo(), p_deb);
  }
  return p_deb;
}

//----------------------------------------------------
//---------------------- 1.b -------------------------
/*
 * Rôle: Suppression d'une liste de pseudonymes.
 * Précondition: vide.
 * @param t_maillon *p_deb
 **/
void  suppressionPseudonyme(t_maillon *&p_deb){

  t_maillon *p_m = p_deb;

  while (p_m->suivant != nullptr){

    p_m = p_deb->suivant;
    delete p_deb;
    p_deb = p_m; 
  }
  delete p_m;
  p_deb = new t_maillon;
  p_deb->suivant = nullptr;
}

//----------------------------------------------------
//---------------------- 1.c -------------------------
/*
 * Rôle: recharcher une liste de pseudonymes si sa taille est inférieur de la valeur seuil.
 * Précondition: 0 < seuil < capa, p_deb est déjà allué, et sa fin marqué en nullptr. 
 * @param t_maillon *p_deb
 * @param int seuil
 * @param int capa
 **/
void rechargerListe(t_maillon *&p_deb, int seuil, int capa){

  t_maillon *p_m = p_deb;
  int taille = 0;

  while(p_m != nullptr){
   taille++;
   p_m = p_m->suivant;
  }

  if(taille<seuil){
    for(int i=0; i<=capa-taille; i++){
      ajouterDebut(donne_pseudo(), p_deb);
    }
  } 
}

//----------------------------------------------------
//----------------------------------------------------
/*
 * Rôle: Affichage d'un liste de pseudonymes.
 * Précondition: p_deb est déjà allué, et sa fin marqué en nullptr.
 * @param t_maillon *p_deb
 **/
void afficherM(t_maillon *p_deb){

  t_maillon *p_m;
  p_m = p_deb;

  while(p_m->suivant != nullptr){
    cout << p_m->chaine << ", ";
    p_m = p_m->suivant;
  }
  cout << p_m->chaine << endl;
}


/***************************************	Q.2	 *******************************************/

struct t_date {

  int jour;
  int mois;
  int an;
};

//----------------------------------------------------
struct t_contact {

  string pseudo1; // l'utilisateur.
  string pseudo2; // la personne croisé.
  t_date date;
};

//----------------------------------------------------
struct t_maillon_contact { // liste de taille 20 max.

  t_contact contact;
  t_maillon_contact *suivant;
};

//----------------------------------------------------
//---------------------- 2.a -------------------------
/*
 * Rôle: intégration d'un contact dans une liste de contacts.
 * Précondition: p_deb est déjà alloué.
 * @param t_maillon_contact *p_deb
 * @param t_contact contact
 **/
void integrationContact(t_maillon_contact *&p_deb, t_contact contact){

  t_maillon_contact *p_courant = p_deb;
  int i = 0, j = 0;

  // chercher si la personne croisée est déjà dans la liste.
  while (p_courant != nullptr){ 
    j++;
    if(contact.pseudo2 != p_courant->contact.pseudo2){
    i++;
    }
    p_courant = p_courant->suivant;
  }

  if(i==j){ // si pseudo2 n'existe pas dans la liste, donc ajouter pseudo2 au début de la liste.

    p_courant = p_deb;
    p_deb = new t_maillon_contact;
    p_deb->suivant = p_courant;

    p_deb->contact.date = contact.date; // la date d'aujourd'hui.
    p_deb->contact.pseudo1 = contact.pseudo1; // le nom de l'utilisateur.
    p_deb->contact.pseudo2 = contact.pseudo2; // la personne croisée.
  }
}

//----------------------------------------------------
//----------------------------------------------------
// Créer les fonctions nécessaires pour vérifier le nombre de jours si >=14 ou pas.

/*
 * Rôle: vérifier si une année 'an' est bissextile ou non.
 * Précondition: an > 0.
 * @param int an
 **/
bool bissextile(int an){  return an%400==0 || an%4==0 && an%100!=0; } // fonction qui défini l'année bissextile.

/*
 * Rôle: vérifier si la différance entre les deux dates et moins ou égale à deux semaines (14 jours).
 * Précondition: Aujourdhui > d (d est une date plus ancienne d'Aujourdhui).
 * @param t_date d
 * @param t_date Aujourdhui
 **/
bool moins2Sem(t_date d, t_date Aujourdhui){ 

  int nbJ; // nb de jours dans un mois.
  
  if(d.mois == 4 || d.mois == 6 || d.mois == 9 || d.mois == 11 ){
      nbJ = 30;
  }else{
    if(d.mois != 2){
      nbJ = 31;
    }else{ // d.mois == 2;
      if(bissextile(d.an)){
          nbJ = 29;
      }else{
          nbJ = 28;
      }
    }
  }

  if(d.an == Aujourdhui.an){
    if(d.mois != Aujourdhui.mois){
      // vérifier si la différance entre les deux date est inférieur ou égale à deux semaines.
      return (nbJ + Aujourdhui.jour) - d.jour <= 14; 
    }else{
      return Aujourdhui.jour - d.jour <= 14;
    }
  }else{
    return false;
  }
}

//----------------------------------------------------
//----------------------------------------------------
/*
 * Rôle: Désallouer tous les contacts à partir du pointeur supp.
 * Précondition: supp est déjà alloué.
 * @param t_maillon_contact *supp
 **/
void desallocationContacts(t_maillon_contact *&supp){

  t_maillon_contact *supp1;

  while(supp != nullptr){ 
    supp1 = supp->suivant;
    delete supp;
    supp = supp1;
  }
}

//----------------------------------------------------
//---------------------- 2.b -------------------------
/*
 * Rôle: Supprimer les contacts qu'ils ont une date plus de deux semaines par rapport à Aujourdhui.
 * Précondition: p_deb est déjà allués, et p_deb ne contient pas des contacts avec des dates plus neuve d'Aujourdhui.
 * @param t_maillon_contact *p_deb
 * @param t_date Aujourdhui
 **/
void SuppPlus2Sem(t_maillon_contact *&p_deb, t_date Aujourdhui){

  t_maillon_contact *p_courant;
  t_maillon_contact *p_supp;
  p_courant = p_deb;

  while(p_courant->suivant != nullptr && moins2Sem(p_deb->contact.date, Aujourdhui)){
    p_courant = p_courant->suivant;
  }

  if(p_courant->suivant != nullptr){ // si'l reste des éléments dans la liste alors les désallouer.
    p_supp = p_courant->suivant->suivant;
    desallocationContacts(p_supp);
  }
  p_courant->suivant = nullptr;
}

//----------------------------------------------------
//----------------------------------------------------
/*
 * Rôle: Afficher les contacts pour un utilisateur dans une date.
 * Précondition: p_deb est déjà alloué.
 * @param t_maillon_contact *p_deb
 * @param t_date Aujourdhui
 **/
void afficherMC(t_maillon_contact *p_deb, t_date Aujourdhui){

  if(moins2Sem(p_deb->contact.date, Aujourdhui)){
    t_maillon_contact *p_m;
    p_m = p_deb;

    cout << "A la date de " << p_m->contact.date.jour << "/" << p_m->contact.date.mois << "/" << p_m->contact.date.an;
    cout << ", " << p_deb->contact.pseudo1 << " croise ";

    
    while(p_m->suivant->suivant != nullptr){
      cout << p_m->contact.pseudo2 << " et ";
      p_m = p_m->suivant;
    }
    cout << p_m->contact.pseudo2 << endl;
  }else{
    cout << "La liste est vide!" << endl;
  }
}

/***************************************	Q.3	 *******************************************/

//---------------------- 3.a -------------------------

struct t_utilisateur{ 

  string nom; // le nom de l'utilisateur.
  bool covid; // si l'utilisateur a le covid ou non.
};

//----------------------------------------------------
struct t_tous_contacts{ // liste de taille 14 max.

  t_utilisateur utilisateur; 
  t_maillon_contact *liste_contact; // liste de taille 20 max.
  t_tous_contacts *suivant;
};

//----------------------------------------------------
//---------------------- 3.b -------------------------
/*
 * Rôle: intégration d'une liste de tous les contacts pour un utilisateur.
 * Précondition: ltc et lc sont déjà alloués.
 * @param t_tous_contacts *ltc
 * @param t_utilisateur util
 * @param t_maillon_contact *lc
 **/
t_tous_contacts* IntegrationListeContact(t_tous_contacts *&ltc, t_utilisateur util, t_maillon_contact *lc){

  t_tous_contacts *pl_courant;
  pl_courant = ltc;
  ltc = new t_tous_contacts;
  ltc->suivant = pl_courant;
  ltc->utilisateur = util;

  ltc->liste_contact = lc;

  return ltc;
}

//----------------------------------------------------
//----------------------------------------------------
/*
 * Rôle: Désallouer tous les listes de contacts à partir du pointeur supp.
 * Précondition: supp est déjà alloué.
 * @param t_tous_contacts *supp
 **/
void desallocationTC(t_tous_contacts *&supp){

  t_tous_contacts *supp1;

  while(supp != nullptr){ 
    supp1 = supp->suivant;
    desallocationContacts(supp->liste_contact);
    delete supp;
    supp = supp1;
  }
}

//----------------------------------------------------
//---------------------- 3.c -------------------------
/*
 * Rôle: Suppression des listes de contacts d'une liste de tous les contacts pour un utilisateur avec une date plus de deux semaines.
 * Précondition: ltc est déjà alloué, et ltc ne contient pas des listes de contacts avec des dates plus neuve d'Aujourdhui.
 * @param t_tous_contacts *ltc
 * @param t_date Aujourdhui
 **/
void SuppListePlus2Sem(t_tous_contacts *&ltc, t_date Aujourdhui){

  t_tous_contacts *l_courant;
  t_tous_contacts *l_tmp;
  t_tous_contacts *supp;

  l_courant = ltc;

  while (l_courant->suivant != nullptr && moins2Sem(l_courant->liste_contact->contact.date, Aujourdhui)){
    l_courant = ltc->suivant;
  }

  if(l_courant->suivant != nullptr){
    supp = l_courant->suivant->suivant;
    desallocationTC(supp);
  }
  l_courant->suivant = nullptr;
}

//----------------------------------------------------
//----------------------------------------------------
/*
 * Rôle: Afficher des listes de contacts d'une liste de tous les contacts.
 * Précondition: ltc est déjà alloué.
 * @param t_tous_contacts *ltc
 **/
void afficherLTC(t_tous_contacts *ltc){

  t_tous_contacts *t_courant = ltc;

  while(t_courant->suivant != nullptr){

    afficherMC(t_courant->liste_contact, t_courant->liste_contact->contact.date);

    if(t_courant->utilisateur.covid == true){ // afficher ce message lorsqu'un utilisateur a le covid.
      cout << "ATTENTION: " << ltc->utilisateur.nom << " a le covid! " << endl;
    }
    t_courant = t_courant->suivant;
  }
}


/*************************************** 	Main  *****************************************/
/*************************************** 	Q.4	  *****************************************/
int main(){

  //initialisation de random par time() Doit être appelé une seule et unique fois dans le main avant tout appel de la fonction donne_pseudo()
  srand(time(0));

  // Créer les utilisateurs.
  t_utilisateur charles, alice;
  charles.nom = "Charles";
  charles.covid = true;
  alice.nom = "Alice";
  alice.covid = false;

  // Créer leurs listes de contactes.
  t_maillon_contact *mCharles = new t_maillon_contact;
  mCharles->suivant = nullptr;
  t_maillon_contact *mAlice = new t_maillon_contact;
  mAlice->suivant = nullptr;

  // Créer la date de croisement.
  t_date date;
  date.an = 2020;
  date.mois = 12;
  date.jour = 20;

  // Créer le contact pour Charles d'après les informations précedantes.
  t_contact contact;
  contact.date = date;
  contact.pseudo1 = charles.nom;
  contact.pseudo2 = alice.nom;

  // Intégration le contact de Charles dans sa liste de contact. 
  integrationContact(mCharles, contact);

  // changement le contact pour que l'utilisateur soit Alice.
  contact.pseudo1 = alice.nom;
  contact.pseudo2 = charles.nom;

  // Intégration le contact d'Alice dans sa liste de contact. 
  integrationContact(mAlice, contact);

  // Créer une liste de tous les contactes. 
  t_tous_contacts *ltc = new t_tous_contacts;
  ltc->suivant = nullptr;

  // Intégration les listes de contactes de Charles et Alices dans la liste de tous les contactes.
  IntegrationListeContact(ltc, charles, mCharles);
  IntegrationListeContact(ltc, alice, mAlice);

  // Afficher la liste de tous les contactes.
  afficherLTC(ltc);



 





/*************************************** 	Jeux de tests	  *****************************************/
/*

  // Jeux de tests pour Q0:
  cout << "---------------- Q0 -------------------" << endl;
  t_maillon *Q0 = new t_maillon;
  Q0->suivant = nullptr;

  cout << "---------------  integration  --------------------" << endl;
  
  ajouterDebut("2", Q0);
  ajouterDebut("1", Q0);
  ajouterFin("3", Q0);
  ajouterFin("4", Q0);
  
  afficherM(Q0);

  cout << "---------------  suppression  --------------------" << endl;

  supprimerDebut(Q0);
  supprimerFin(Q0);

  afficherM(Q0);

//------------------------------------------------------------------------------------------------------------------

  // Jeux de tests pour Q1:
  cout << "---------------  Q1  --------------------" << endl;

  t_maillon* Q1;

  Q1 = construirListe(5);
  afficherM(Q1);

  cout << "---------------  suppression  --------------------" << endl;
  suppressionPseudonyme(Q1);
  afficherM(Q1);

  cout << "---------------  recharger  --------------------" << endl;
  rechargerListe(Q1, 3, 5);
  afficherM(Q1);

  cout << "---------------  suppression début puis recharger ----------------" << endl;
  // après la suppression d'un seul élément la procédure rechargerListe ne fonctionne pas car le nombre d'éléments reste supérieur du seuil.
  supprimerDebut(Q1);
  rechargerListe(Q1, 3, 5);
  afficherM(Q1);

//------------------------------------------------------------------------------------------------------------------------

  // Jeux de tests pour Q2:
  cout << "---------------  Q2  --------------------" << endl;
  t_date date;
  date.an = 2020;
  date.mois = 10;
  date.jour = 20;

  string util = "Utilisateur";

  t_contact contact1, contact2;
  contact1.date = date;
  contact1.pseudo1 = util; // l'utilisateur.
  contact1.pseudo2 = donne_pseudo();

  contact2.date = date;
  contact2.pseudo1 = util; // l'utilisateur.
  contact2.pseudo2 = donne_pseudo();

  t_maillon_contact *Q2 = new t_maillon_contact;
  Q2->suivant = nullptr;

  cout << "---------------  Integration  --------------------" << endl;

  integrationContact(Q2, contact1);
  integrationContact(Q2, contact2);
  afficherMC(Q2, date);

  t_date Aujourdhui;
  Aujourdhui.an = 2020;
  Aujourdhui.mois = 11;
  Aujourdhui.jour = 25;

  cout << "---------------  suppression  --------------------" << endl;

  SuppPlus2Sem(Q2, Aujourdhui);
  afficherMC(Q2, Aujourdhui);

// -------------------------------------------------------------------------------------------------------

  // Jeux de tests pour Q3:
  cout << "---------------  Q3  --------------------" << endl;
  // créer des dates.
  t_date date1;
  date1.an = 2020;
  date1.mois = 10;
  date1.jour = 20;

  t_date date2;
  date2.an = 2020;
  date2.mois = 11;
  date2.jour = 12;

  t_date Aujourdhui;
  Aujourdhui.an = 2020;
  Aujourdhui.mois = 11;
  Aujourdhui.jour = 20;

  // Créer un utilisateur.
  t_utilisateur util;
  util.nom = "utilisateur";
  util.covid = false;

  // créer des listes de contactes.
  t_maillon_contact *MC1 = new t_maillon_contact;
  MC1->suivant = nullptr;

  t_maillon_contact *MC2 = new t_maillon_contact;
  MC2->suivant = nullptr;


  // créer des contactes, et les intégrer dans leurs listes.
  t_contact contact1, contact2;
  contact1.date = date1;
  contact1.pseudo1 = util.nom; // l'utilisateur.
  contact1.pseudo2 = donne_pseudo();

  contact2.date = date1;
  contact2.pseudo1 = util.nom; // l'utilisateur.
  contact2.pseudo2 = donne_pseudo();

  integrationContact(MC1, contact1);
  integrationContact(MC1, contact2);

  contact1.date = date2;
  contact1.pseudo1 = util.nom; // l'utilisateur.
  contact1.pseudo2 = donne_pseudo();

  contact2.date = date2;
  contact2.pseudo1 = util.nom; // l'utilisateur.
  contact2.pseudo2 = donne_pseudo();

  integrationContact(MC2, contact1);
  integrationContact(MC2, contact2);


  // Créer une liste de tous les contactes.
  t_tous_contacts *Q3 = new t_tous_contacts;
  Q3->suivant = nullptr;

  cout << "---------------  integration --------------------" << endl;

  IntegrationListeContact(Q3, util, MC1);
  IntegrationListeContact(Q3, util, MC2);
  afficherLTC(Q3);

  cout << "---------------  suppression plus 2 semaines  ----------------" << endl;

  SuppListePlus2Sem(Q3, Aujourdhui);
  afficherLTC(Q3);

*/


	return 0;
}