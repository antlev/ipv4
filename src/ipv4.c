/*
*   PPE : Programme de gestion d'adresses IPV4
*   Version : v2.1
*   Auteur :Antoine Levy SIO2
*
*   Notes : Pour compiler ce programme, il faut rajouter l'option -lm
*   exemple : gcc ipv4.c -o ipv4 -lm
*
*   TODO : Revoir suppresion réseau dans un fichier
*/ 
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

struct Reseau{
    int numRes;
    int sIpDecInt4[4];
    int sMaskDecInt4[4];
};
//******************************************-Procédures-******************************************
void sayHello(); //  Dis Bonjour
void sayGoodBye(); // Dis Au-revoir
void error(int code); // Affiche les messages d'erreur du programme
void memAdress(char char100[], int *decInt4,int *binInt32, int ipOrMasque); // Enregistre l'adresse saisie dans char100 dans decInt4 et binInt32 en mémoire
void memNetworkAdresse(int ipBinInt32[],int ipDecInt4[],int masqueBinInt32[],int masqueDecInt4[], int *networkBinInt32, int *networkDecInt4); // Enregistre l'adresse réseau dans decInt et BinInt
void printAdress4(int decInt4[]); // Affiche une adresse en decimal pointé
void printAdress32(int binInt32[]); // Affiche une adresse en binaire
void base10ToBinaire(int n, int *binInt8); // Prend une valeur n compris entre 0 et 255 et la stock sous forme binaire dans un tableau de 8 cases
void calcNextAdress(int baseDecInt4[],int *nextDecInt4); // Prend en entrée une adresse en décimal pointée et rempli nextDecInt4 de l'adresse suivante 
void calcPreviousAdress(int baseDecInt4[],int *previousDecInt4); // Prend en entrée une adresse en décimal pointée et rempli previousDecInt4 de l'adresse précédente
void calcNextNetwork(int networkBinInt32[],int masqueBinInt32[],int *nextNetworkBinInt32,int *nextNetworkDecInt4); // Prend en entrée l'adresse réseau et le masque en binaire et rempli les tableaux nextNetworkDecInt4 et nextNetworkBinInt32
void Ad32To4(int binInt32[],int *decInt4); // Transforme une adresse 32 bits en décimal pointe
void Ad4To32(int decInt4[],int *binInt32); // Transforme une adresse  en décimal pointe en 32 bits
void saveAdress(int IpDecInt4[],int masqueDecInt4[]); //  Enregistre l'adresse ip et le masque en cours dans un fichier
void returnSaveAdress(int numRes,int *ipDecInt4,int *ipBinInt32,int *masqueDecInt4,int *masqueBinInt32);
void printSaveAdress(); // Affiche les réseaux stockés dans un fichier
void printOneSaveAdress(int adressToPrint); // Affiche le reseau voulu stocké dans un fichier
void delSaveAdress(int numRes); // Supprime un réseau donné dans le fichier
//******************************************-Fonctions-******************************************
int checkAdress(char char100[],int ipOrMasque); // Vérifie la validité de l'adresse
int checkIfAdressExist(int *decInt4, int ipOrMasque); // Vérifie si une adresse (ip ou masque) existe en mémoire
int binaireToBase10(int binInt[],int bit); // Prend en entrée une chaine de caractère binaire, allant jusqu'à 32bit et renvoi la valeur décimale
int calcRange(int masqueBinInt32[]); // Calcul le nombre d'ip disponible en fonction du masque
int valOctet(int binInt8[]); // Prend en entrée un tableau de 8 bits (un octet) et renvoi sa valeur en décimal
//******************************************-Main-******************************************
main(){
    FILE *PtrFich;
    int resASupp,resAAff;
    int i,j,k,n,numberInt,masquecidr,choice,valToConv,choixres;
    int ipDecInt4[4],masqueDecInt4[4],networkDecInt4[4],firstAdress4[4],lastAdress4[4],nextNetworkDecInt4[4],broadDecInt4[4],masqueDec4[4] ; // Permet de stocker des adresses ip en décimal pointées
    int tabBinInt8[8];
    int ipBinInt32[32],masqueBinInt32[32],networkBinInt32[32],nextNetworkBinInt32[32],nbAdressSousRes[100],masqueBin32[32],binToDec32[32]; // Permet de stocker des adresses ip en binaire
    int sousResNetworkDecInt4[4],sousResFirstDecInt4[4],sousResLastDecInt4[4],sousResBroadDecInt4[4],sousResNextNetworkDecInt4[4]; // Permet de stocker des adresses ip de sous-réseaux en décimal pointées
    int sousResNetworkBinInt32[32],sousResFirstBinInt32[32],sousReslastBinInt32[32],sousResBroadBinInt32[32],sousResNextNetworkBinInt32[32]; // Permet de stocker des adresses ip en binaire
    char ipChar100[100],masqueChar100[100]; // Permet de stocker les saisies utilisateurs avant la vérification de la validité
    char point=0; // Permet de verifier la structure de l'adresse ip donnée
    for( j=0 ; j<4 ; j++ ){ // Initialisation des tableaux ip et masque à 0;
        ipDecInt4[j] = masqueDecInt4[j] = 0;
    }
    for ( j=0 ; j<32 ; j++){
        ipBinInt32[j] = masqueBinInt32[j] = 0 ;
    }
    sayHello();
    while (choice != 9){
        printf("\n");
        printf("********************** MENU PRINCIPAL **********************\n");
        printf("Entrez une valeur correspondant a votre choix :\n");
        printf("1) Saisir une adresse ip en mémoire\n");
        printf("2) Saisir un masque de sous réseau en mémoire\n");
        printf("-------------------------------------------------------------\n");
        printf("3) Sauvegarder les paramètres en mémoire dans un fichier (ipm)\n");
        printf("4) Afficher les réseaux stockés dans un fichier \n");
        printf("5) Rentrer en mémoire un réseau stocké dans un fichier\n");
        printf("6) Supprimer un réseau stocké dans un fichier\n");
        printf("-------------------------------------------------------------\n");
        printf("7) Info réseau actuellement en mémoire (ipm)\n");
        printf("8) Conversion\n");
        printf("9) Sous-réseau (ipm)\n");
        printf("-------------------------------------------------------------\n");
        printf("10) Quitter\n");
        printf("************************************************************\n");
        if ( checkIfAdressExist(ipDecInt4,0) == 1 ){
            printf("ip actuellement en mémoire :     ");
            printAdress4(ipDecInt4);
        } else printf("Aucune adresse ip n'est actuellement en mémoire\n");
        if ( checkIfAdressExist(masqueDecInt4,1) == 1 ){
            printf("Masque actuellement en mémoire : ");
            printAdress4(masqueDecInt4) ;
        } else printf("Aucun masque n'est actuellement en mémoire\n");
        if ( checkIfAdressExist(ipDecInt4,0) == 1 && checkIfAdressExist(masqueDecInt4,1) == 1 ){
            memNetworkAdresse(ipBinInt32,ipDecInt4,masqueBinInt32,masqueDecInt4,networkBinInt32,networkDecInt4);
            printf("Adresse réseau calculée :        ");
            printAdress4(networkDecInt4);
        }
        printf("************************************************************\n");
        printf("->");
        scanf("%d",&choice);
        switch (choice){
        case 1 :
        printf("****************** Saisie de l'adresse IP ******************\n");
        if ( checkIfAdressExist(ipDecInt4,0) == 1 ) {
            printf("Adresse ip actuellement en mémoire\n");
            printAdress4(ipDecInt4);
        } else { printf("Aucune adresse ip n'est rentrée en mémoire\n");}
        do{
            printf("Veuillez saisir une adresse IP\n");
            printf("->");
            scanf("%s",ipChar100); // On demande une ip que l'on stock dans char100
            n = checkAdress(ipChar100,0) ; // On vérifie la validité de l'ip
            if ( n == 1 ){
                memAdress(ipChar100,ipDecInt4,ipBinInt32,0); // Si l'ip est valide on sauvegarde l'ip donné dans le tableau ipDecInt4
            }
        } while ( n  != 1);  // tant que l'ip n'est pas valide : reprompt
        break;    
        case 2 :
        printf("Entrez 1 pour saisir un masque en format adresse\n(xxx.xxx.xxx.xxx)\n");
        printf("Entrez 2 pour saisir un masque en format cidr (/xx)\n");
        printf("->");
        scanf("%d",&choice);
        switch (choice){
            case 1 :
            printf("************* Saisie du masque : Format Adresse *************\n");
            if ( checkIfAdressExist(masqueDecInt4,1) == 1 ){
                printf("Masque actuellement en mémoire :\n");
                printAdress4(masqueDecInt4) ;
            } else { printf("Aucun masque n'est actuellement rentré en mémoire\n") ; }
            printf("Veuillez saisir un masque de sous réseau dans \nun format xxx.xxx.xxx.xxx\n");
            do{
                printf("->");
                scanf("%s",masqueChar100); // On demande un masque que l'on stock dans masqueChar100
                n = checkAdress(masqueChar100,1) ; // On vérifie la validité du masque
                if ( n == 1 ){
                    memAdress(masqueChar100,masqueDecInt4,masqueBinInt32,1); // Si l'ip est valide on sauvegarde l'ip donné dans le tableau ipDecInt4
                }
            } while ( n  != 1);  // tant que l'ip n'est pas valide : reprompt
            break;
            case 2 :     
            printf("************** Saisie du masque : Format CIDR **************\n");
            if ( checkIfAdressExist(masqueDecInt4,1) == 1 ){
                printf("Masque actuellement en mémoire :\n");
                printAdress4(masqueDecInt4) ;
            }
            else { printf("Aucun masque n'est actuellement rentré en mémoire\n") ; }
            printf("Veuillez entrer un masque en format CIDR\nC'est-à-dire un entier compris entre 0 et 32\n");
            printf("->");
            scanf("%d",&masquecidr);
            if ( masquecidr <= 0 || masquecidr > 31 ) printf("La valeur cidr du masque doit être comprise entre 0 et 32\n");

            while ( masquecidr < 1 || masquecidr > 31 ){
                printf("Veuillez resaisir un masque en format cidr\n");
                printf("->");
                scanf("%d",&masquecidr);
                if ( masquecidr <= 0 || masquecidr > 31 ) printf("La valeur cidr du masque doit être comprise entre 0 et 32\n");
            }
            if ( masquecidr == 31 ) printf("Note : Vous vous appretez à rentrer un masque ayant qu'un seul bit à 0\nLe réseau correspondant ne pourra comporter qu'une seul adresse ip\n");
            i = 0;
            while ( masquecidr != 0 ){                      // masquecidr représente le nombre de 1 dans le masque                                           
               if (masquecidr >= 8 ){                        // Tant que l'on a plus de 8 bit à 1 dans le masque                                            
                       masqueDecInt4[i] = 255;         // => on remplis un octet de 1 soit 255 en décimal
                       for( k=i*8 ; k<i*8+8 ; k++ ){
                            masqueBinInt32[k] = 1 ;
                       }
                       masquecidr -= 8;                     // On retire les 8 bits à 1
                       i++;                                 // On avance d'un octet
               } else {                                     // Si il reste mois de 8 bits à 1
                       for ( j=0 ; j<masquecidr ; j++ ){    // on rentre 2⁷ pour le premier bit puis 2⁶ puis 2⁵ etc...
                           masqueDecInt4[i] += pow(2,(7-j));
                           masqueBinInt32[i*8+j] = 1 ;
                       }
                       masquecidr = 0 ;
                   }
            } // Message indiquant la sauvegarde en mémoire du masque
            printf("Sauvegarde du masque %d.%d.%d.%d en mémoire\n", masqueDecInt4[0],masqueDecInt4[1],masqueDecInt4[2],masqueDecInt4[3] );
            break;
            default :
            break;
        }
        break; 
        case 3 :
        if ( checkIfAdressExist(ipDecInt4,0) == 1 && checkIfAdressExist(masqueDecInt4,1) == 1 ){
            printf("**** Sauvegarde des paramètres actuellement en mémoire **** \n");
            saveAdress(ipDecInt4,masqueDecInt4);
        } else printf("Vous devez avoir une adresse ip et un masque valide rentré en mémoire pour les sauvegarder\n");
        break;
        case 4 :
            printf("Quelle réseau voulez vous afficher ?\n");
            printf("Entrer 0 pour afficher tous les réseaux\n");
            printf("->");
            scanf("%d",&resAAff);
            if ( resAAff == 0 ){
                printSaveAdress();
            } else {
                printOneSaveAdress(resAAff);
            }
        break;
        case 5 :
            printf("*** Rentrer en mémoire un réseau stocké dans un fichier ***\n");
            printf("Pour afficher les réseaux actuellement stocké dans un fichier rentrer 0\n");
            do {
                printf("Quel réseau voulez vous rentrer en mémoire ? \n");
                printf("Entrer le numéro de réseau correspondant\n");
                printf("->");
                scanf("%d",&choixres);
                if ( choixres == 0 ) { printSaveAdress() ; }

            } while ( choixres == 0 );  
                returnSaveAdress(choixres,ipDecInt4,ipBinInt32,masqueDecInt4,masqueBinInt32); // On récupère le réseau voulu
        break;
        case 6 :
            printf("Supprimer un réseau stocké dans un fichier\n");
            printf("Quel réseau voulez vous supprimer ?");
            printf("->");
            scanf("%d",&resASupp);
            delSaveAdress(resASupp);
        break;
        case 7 :
            if( checkIfAdressExist(ipDecInt4,0) == 1 && checkIfAdressExist(masqueDecInt4,1) == 1){  // On vérifie que l'on dispose d'une ip et d'un masque valide en mémoire
                printf("------------------------ Info réseau ------------------------\n");
                // CALCUL DES ADRESSES
                calcNextNetwork(networkBinInt32,masqueBinInt32,nextNetworkBinInt32,nextNetworkDecInt4); // PROCHAIN RESEAU EN BINAIRE
                Ad32To4(nextNetworkBinInt32,nextNetworkDecInt4); // CONVERSION PROCHAIN RESEAU EN DECIMAL POINTE
                calcNextAdress(networkDecInt4,firstAdress4); // CALCUL DE LA PREMIERE ADRESSE IP DISPONIBLE
                calcPreviousAdress(nextNetworkDecInt4,broadDecInt4); // CALCUL DE L ADRESSE DE BROADCAST
                calcPreviousAdress(broadDecInt4,lastAdress4); // CALCUL DE LA DERNIERE ADRESSE IP DISPONIBLE

                // AFFICHAGE DES ADRESSES
                printf("************************ En binaire ************************\n");
                printf("Adresse ip : ");
                printAdress32(ipBinInt32);
                printf("Masque     : ");
                printAdress32(masqueBinInt32);
                printf("Reseau     : ");
                printAdress32(networkBinInt32);
                printf("\n************************ En décimal ************************\n");
                printf("Adresse ip     : ");
                printAdress4(ipDecInt4);
                printf("Masque         : ");
                printAdress4(masqueDecInt4);
                printf("Adresse réseau : ");
                printAdress4(networkDecInt4);
                printf("\n1ère adresse ip disponible       : ");
                printAdress4(firstAdress4);
                printf("Nombres d'adresses ip disponible : %d\n",calcRange(masqueBinInt32));            
                printf("Dernière adresse ip disponible   : ");
                printAdress4(lastAdress4);
                printf("Adresse de broadcast             : "); 
                printAdress4(broadDecInt4);
                printf("Prochain réseau                  : ");  
                printAdress4(nextNetworkDecInt4);
                printf("--------------------------------------------------------------\n");
            } else {
                printf("Il faut une adresse ip et un masque valide pour afficher les infos du réseau\n");
                printf("Veuillez vérifier ces paramètres svp\n");
            }
        break;
        case 8 :                    
        choice = 0;
        while ( choice != 7 ){
        printf("************************ Conversion ************************\n");
        printf("1) Conversion d'un nombre décimal en binaire\n");
        printf("2) Conversion d'un nombre décimal en héxadécimal\n");
        printf("3) Conversion d'un nombre binaire en décimal\n");
        printf("4) Conversion d'un nombre binaire en héxadécimal\n");
        printf("5) Conversion d'un nombre héxadécimal en décimal\n");
        printf("6) Conversion d'un nombre héxadécimal en binaire\n");
        printf("7) Quitter Conversion\n");
        printf("->");
        scanf("%d",&choice);
            switch (choice){
                case 1 :
                    printf("Quel est le nombre décimal à convertir en binaire?\n");
                    printf("->");
                    scanf("%d",&valToConv);
                    while ( valToConv > 255 || valToConv < 0 ){
                        printf("Veuillez rentrer une valeur comprise entre 0 et 255\n");
                        printf("->");
                        scanf("%d",&valToConv);
                    }
                    printf("Votre valeur décimale : %d\n", valToConv);
                    printf("Conversion : " );
                    base10ToBinaire(valToConv,tabBinInt8);
                    for ( j=0 ; j<8 ; j++ ){
                        printf("%d",tabBinInt8[j]);
                    }
                    printf("\n");
                break;
               case 2 :
                    printf("Quel est le nombre décimal à convertir en héxadécimal?\n");
                    printf("->");
                    scanf("%d",&valToConv);
                    printf("%d vaut %X en héxadécimal\n",valToConv,valToConv);
                break;
                    // REVOIR CES 2 POINTS
                case 3 :
                    printf("Quel est le nombre binaire à convertir en décimal?\n");
                    j=valToConv=0;
                    printf("->");
                    scanf("%d",&valToConv);
                    while ( valToConv > 0 ){
                        binToDec32[j] = valToConv % 10 ;
                        j++;
                        valToConv = valToConv / 10 ;
                    }
                    printf("\nVotre valeur en décimal : %d\n",binaireToBase10(binToDec32,j));
                break;
                case 4 :
                    printf("Quel est le nombre binaire à convertir en héxadécimal?\n");
                    j=valToConv=0;
                    printf("->");
                    scanf("%d",&valToConv);
                    while ( valToConv > 0 ){
                        binToDec32[j] = valToConv % 10 ;
                        printf("%d",binToDec32[j] );
                        j++;
                        valToConv = valToConv / 10 ;
                    }
                    printf("\nVotre valeur en héxadécimal : %X\n",binaireToBase10(binToDec32,j));
                break; 
                case 5 :
                    printf("Quel est le nombre hexadécimal à convertir en décimal?\n");
                    printf("->");
                    scanf("%X",&valToConv);
                    printf("%X vaut %d en décimal\n",valToConv,valToConv );
                break;
                case 6 :
                    printf("Quel est le nombre hexadécimal à convertir en binaire?\n");
                    printf("->");
                    scanf("%X",&valToConv);
                    while ( valToConv > 255 || valToConv < 0 ){
                        printf("Veuillez rentrer une valeur comprise entre 0 et 255\n");
                        printf("->");
                        scanf("%X",&valToConv);
                    }
                    base10ToBinaire(valToConv,tabBinInt8);
                    for ( j=0 ; j<8 ; j++ ){
                        printf("%d",tabBinInt8[j]);
                    }
                    printf("\n");
                    break;
                case 7 :
                printf("Quitter Conversion\n");
                break;
                default :
                break;
            }
        }     
        break;
        case 9 :
        {
            int nbSousRes,nbAdresses,temp2,masquecidr;
 
            int nbAdressesTot;
            double nbAdressesPossible ;
            nbAdressesTot = 0 ;
            if( checkIfAdressExist(ipDecInt4,0) == 1 && checkIfAdressExist(masqueDecInt4,1) == 1){

                printf("************************* SOUS-RESEAU ************************\n");
                //Calcul du nombre d'adresses possible
                temp2 = 0 ;
                for( j = 31 ; j >= 0 ; j-- ){   
                    if ( masqueBinInt32[j] == 0 ){
                        temp2++ ;
                    } else break ;
                }
                nbAdressesPossible = pow(2,temp2);
                printf("RAPPEL : Votre plage vous permet de disposer de %f \n",nbAdressesPossible );
                printf("Combien de sous-réseaux souhaitez vous créer ?\n");
                printf("->");
                scanf("%d",&nbSousRes);
                printf("Veuillez rentrer les sous réseau souhaité du PLUS GRAND au PLUS PETIT\n");
                for( j = 0 ; j < nbSousRes ; j++ ){
                    printf("Combien d'adresses doit contenir le sous-réseau n° %d ?\n",j+1 );
                    printf("->");
                    scanf("%d",&nbAdresses);
                    nbAdresses += 2 ; // On ajoute l'adresse de broadcast et réseau à prendre en compte
                    if ( j > 0 ){
                        if( nbAdresses > nbAdressSousRes[j-1] ){
                            printf("Vous venez de saisir un sous-réseau plus grand que le précédent :o\n");
                            printf("Il est impératif de saisir les sous-réseaux du plus grand au plus petit\n");
                            j = -1 ;
                        }
                    }
                    temp2 = 2 ;
                    while ( nbAdresses > 1 ){
                        temp2 *= 2 ;
                        nbAdresses = nbAdresses/2 ;
                    }
                    nbAdressSousRes[j] = temp2;
                    nbAdressesTot += temp2 ;
                }
                if ( nbAdressesPossible < nbAdressesTot ){ // Comparaison du nombre d'adresses possible avec le nombre d'adresses total
                    printf("Vous ne pouvez pas rentrer autant d'adresses étant donnée votre plage\n");
                    printf("Votre plage vous permet de disposer de %f \n",nbAdressesPossible );
                    printf("Rappel : chaque sous-réseau nécessite de deux adresses supplémentaire (réseau et broadcast)\n");
                } else { 
                    for ( j = 0 ; j < 4 ; j++ ){
                        sousResNetworkDecInt4[j] = networkDecInt4[j] ;
                    }

                    printf("************************* SOUS-RESEAUX ************************\n");
                    printf("---------------------------------------------------------------\n");
                    printf("***************************************************************\n");
                    for ( j = 0 ; j < nbSousRes ; j++ ){   
                        masquecidr = 32;
                        for ( k = 0 ; k < 32 ; k++ ){
                            masqueBin32[k] = 1 ;
                        }
                        k=31;
                        while ( nbAdressSousRes[j] > 1 ){
                                masqueBin32[k]=0 ;
                                k--;
                                masquecidr--;
                                nbAdressSousRes[j] /= 2 ;
                        }

                        //Calcul de la plage à reserver pour le sous réseau
                        printf("----------------------- Sous-réseau n°%d -----------------------\n",j+1 );
                        printf("Adresse Réseau : ");
                        printAdress4(sousResNetworkDecInt4);

                    
                        calcNextAdress(sousResNetworkDecInt4,sousResFirstDecInt4);

                        printf("1ere adresse Ip disponible : ");                          
                        printAdress4(sousResFirstDecInt4);
                        
                        Ad4To32(sousResNetworkDecInt4,sousResNetworkBinInt32); // On a besoin de l'adresse reseau en binaire pour calculer le prochain réseau
                        calcNextNetwork(sousResNetworkBinInt32,masqueBin32,sousResNextNetworkBinInt32,sousResNextNetworkDecInt4);
                        calcPreviousAdress(sousResNextNetworkDecInt4,sousResBroadDecInt4);

                        printf("Dernière adresse Ip disponible : ");
                        printAdress4(sousResBroadDecInt4);
                        calcPreviousAdress(sousResBroadDecInt4,sousResLastDecInt4);
                        printf("Adresse de Broadcast : ");
                        printAdress4(sousResLastDecInt4);
                        printf("Masquecidr = %d\n",masquecidr );
                        printf("Masque en binaire : ");
                        printAdress32(masqueBin32);
                        printf("Masque en décimal pointé : " );
                        printAdress4(masqueDec4);

                        // On rentre les valeurs trouvées dans notre structure
//                        SousRes.masquecidr = masquecidr ;
//                        for(k=0;k<4;k++){
//                            SousRes.netDecInt4[k] = sousResNetworkDecInt4[k];
//                            SousRes.broadDecInt4[k] = sousResBroadDecInt4[k];
//                        }
                        // On initialise l'adresse reseau contenu dans sousResNetworkDecInt4 avec sousResNextNetworkDecInt4 pour le prochain sous réseau
                        for(k=0;k<4;k++){
                            sousResNetworkDecInt4[k] = sousResNextNetworkDecInt4[k];
                        }
                        printf("***************************************************************\n");
                    }
                    printf("---------------------------------------------------------------\n");
                    printf("\n");

                }

            } else { printf("Il faut avoir en mémoire une adresse ip et un masque valide pour avoir cette option\nVeuillez vérifier ces paramètres svp\n"); }
        }
        break;
        case 10 :
            printf("************************** SORTIE **************************\n");
            printf("Voulez vous vraiment quitter mon programme?? ;(\n");       
            printf("( 10 ) pour confirmer ;(\n");
            printf("************************************************************\n");
            printf("->");
            scanf("%d",&choice);
            if(choice==10){
                sayGoodBye();
            } else break;
        return;
    
        default :
        break;
        }
    }
}
//******************************************-Procédures-******************************************
void sayHello(){
    printf("\n");
    printf("*************************************************************\n");
    printf("Bonjour et bienvenue sur mon programme\n");
    printf("*************************************************************\n");
}
void sayGoodBye(){
    printf("\n");
    printf("**************************************************\n");
    printf("Au revoir et à bientôt :)\n");
    printf("**************************************************\n");
}
void error(int code){
    switch(code){
        //************************** ip et Masque **************************//
        case 1 :
            printf("ERREUR 1 : Format non respecté \n")    ; // Message d'error si la forme xxx.xxx.xxx.xxx n'est pas respectée
            printf("RAPPEL : L'adresse saisie doit respecter le format : xxx.xxx.xxx.xxx\n");
            printf("Les valeurs 'xxx' doivent être comprises entre 0 et 255\n\n");
        break;
        case 2 :
            printf("ERREUR 2 : Valeur hors-limite \n")    ; // Message d'error si une valeur xxx est hors limite
            printf("RAPPEL : L'adresse saisie doit respecter le format : xxx.xxx.xxx.xxx\n");
            printf("Les valeurs 'xxx' doivent être comprises entre 0 et 255\n\n");
        break;
        //************************** Masque **************************//
        case 3 :
            printf("ERREUR 3 : Masque saisie invalide ! : Bits à 1 non contigus\n");
            printf("RAPPEL : L'adresse saisie doit respecter le format : xxx.xxx.xxx.xxx\n");
            printf("Les bits à 1 doivent être contigus\n");
        break;
    }
}
void memAdress(char char100[], int *decInt4,int *binInt32, int ipOrMasque){ // Enregistre l'adresse saisie dans char100 dans decInt4 et binInt32 en mémoire
    int j,k,a=0,numberInt ;
    int binInt8[8];
    char temp[3];
    char point=0; // Permet de verifier la structure de l'adresse ip donnée
    for( j=0 ; j <= strlen(char100) ; j++ ){ // On parcourt le tableau...
            if( char100[j] != '.' && char100[j] != '\0' ){ // ... si on ne trouve pas de point ni la fin du tableau
                temp[a] = char100[j]    ;    // on stock la valeur de l'char100 de j dans une vaariable temp
            }
            else if ( ( char100[j] == '.' || char100[j] == '\0' ) && point < 4 ){ // ... si on trouve un point ou la fin du tableau
                numberInt = atoi(temp)    ; // on ressort la valeur numérique contenue dans temp
                temp[0]=0;
                a=-1; // On réinitialise temp et son compteur
                temp[1]=temp[2]='\0';
                if ( numberInt >= 0 && numberInt < 256){ // On vérifie que la valeur contenue maintenant dans
                    decInt4[point] = numberInt;          // numberInt ne dépasse pas les limites
                    base10ToBinaire(numberInt,binInt8);
                    for ( k=0 ; k<8 ; k++ ){
                        binInt32[point*8+k] = binInt8[k];
                    }
                    point++;
                }
            }
            a++; // a permet d'avoir un compteur pour le tableau temp   
    }
    if ( ipOrMasque == 0 ){
        printf("Sauvegarde de l'adresse ip %d.%d.%d.%d en mémoire \n",decInt4[0],decInt4[1],decInt4[2],decInt4[3]);
    }
    if ( ipOrMasque == 1 ){
        printf("Sauvegarde du masque %d.%d.%d.%d en mémoire \n",decInt4[0],decInt4[1],decInt4[2],decInt4[3]);
    }
}
void memNetworkAdresse(int ipBinInt32[],int ipDecInt4[],int masqueBinInt32[],int masqueDecInt4[], int *networkBinInt32, int *networkDecInt4){
    int j;
    for ( j=0 ; j<32 ; j++ )
    {
        networkBinInt32[j] = ipBinInt32[j] & masqueBinInt32[j] ; // Et Logique entre l'adresse ip et le masque =  adresse reseau ( en bit )
    }
    for ( j=0 ; j<4 ; j++ )
    {
       networkDecInt4[j] = ipDecInt4[j] & masqueDecInt4[j] ;  // Et Logique entre l'adresse ip et le masque =  adresse reseau ( en décimal pointé )
    }
}
void printAdress4(int decInt4[]){ // Affiche une adresse en decimal pointé
    printf("%d.%d.%d.%d\n", decInt4[0],decInt4[1],decInt4[2],decInt4[3]);       
}
void printAdress32(int binInt32[]){ // Affiche une adresse en binaire
    int j;
    for ( j=0 ; j<32 ; j++ )
    {
        printf("%d",binInt32[j] );
        if ( j==7 || j==15 || j==23 ) { printf("." ) ; }
    }
    printf("\n");
} 
void base10ToBinaire(int n, int *binInt8){ // Prend une valeur n compris entre 0 et 255 et la stock sous forme binaire dans un tableau de 8 cases
    int j;
    for ( j=7 ; j>=0 ; j-- ){
        binInt8[j] = n%2 ;
        n = n/2 ;
    }
}
void calcNextAdress(int baseDecInt4[],int *nextDecInt4){ // Rempli un tableau decPoint4 de la première adresse ip de la plage
    int j;
    for( j=0 ; j<4 ; j++ ){
        nextDecInt4[j] = baseDecInt4[j]; // On rentre l'adresse réseau dans nextDecInt4
    }

    for ( j=3 ; j>=0 ; j-- ){ // On ajoute 1 pour avoir la première adresse ip disponible
        if ( nextDecInt4[j] < 255){
            nextDecInt4[j] += 1;
            break;
        } else if ( nextDecInt4[j] == 255){
            nextDecInt4[j] = 0;
        }
    }
}
void calcPreviousAdress(int baseDecInt4[],int *previousDecInt4){ //  Rempli un tableau decPoint4 de la dernière adresse ip de la plage
    int j;
    for( j=0 ; j<4 ; j++ ){
        previousDecInt4[j] = baseDecInt4[j]; // On rentre l'adresse réseau dans previousDecInt4
    }

    for ( j=3 ; j>=0 ; j-- ){ // On ajoute 1 pour avoir la première adresse ip disponible
        if ( previousDecInt4[j] > 0){
            previousDecInt4[j] -= 1;
            break;
        } else if ( previousDecInt4[j] == 0){
            previousDecInt4[j] = 255;
        }
    }  
}
void calcNextNetwork(int networkBinInt32[],int masqueBinInt32[],int *nextNetworkBinInt32,int *nextNetworkDecInt4){ // Prend en entrée l'adresse reseau et le masque et rempli les tableaux nextNetworkDecInt4 et nextNetworkBinInt32
    // Prend en entrée l'adresse reseau et le masque 
    // Rempli les tableaux nextNetworkDecInt4 et nextNetworkBinInt32

    int temp=0,j,octet,pas,i;
    int nextNetworkBinInt8[8];
    for( j=0 ; j<32 ; j++ ){
        nextNetworkBinInt32[j] = networkBinInt32[j] && masqueBinInt32[j];
    } 
    temp = -1 ; 
    for( j=0 ; j<32 ; j++ ){
        if(masqueBinInt32[j] == 1){
            temp++;
        } else { break; }
    }
    while(1){
        if(nextNetworkBinInt32[temp] == 0){
            nextNetworkBinInt32[temp]=1;
            break;
        }else {
            nextNetworkBinInt32[temp] = 0;
            temp--;
            if (temp < 0 ){
                printf("error\n");
                break;
            }
        }
    }
    for(i=0;i<4;i++){
        for (j = 0; j < 8 ; j++){
            nextNetworkBinInt8[j]  = nextNetworkBinInt32[i*8+j]  ;
            //nextNetworkDecInt4[i] = binaireToBase10(nextNetworkBinInt8,8)     ; 
        }
        nextNetworkDecInt4[i] = valOctet(nextNetworkBinInt8);
    }
}
void Ad32To4(int binInt32[],int *decInt4){ // Transforme une adresse 32 bits en decimal pointe
    int j,k;
    int temp[8]; // Permet d'isoler un octet et de transformer sa valeu en decimal grace a la fonction binaireToBase10
    for ( j = 0 ; j < 4 ; j++ ){
        for ( k = 0 ; k < 8 ; k++ ){
            temp[k] = binInt32[j*8+k];
        }
        decInt4[j] = valOctet(temp);
    }
}
void Ad4To32(int decInt4[],int *binInt32){ // Transforme une adresse en décimal pointe en adresse 32 bits
    int binInt8[8];
    int j,k,n;
    int temp[8]; // Permet d'isoler un octet et de transformer sa valeur en décimal grace a la fonction binaireToBase10
    base10ToBinaire(192,binInt8);
    for ( j = 0 ; j < 4 ; j++ ){
        n = decInt4[j] ;
        base10ToBinaire(n,binInt8);
        for ( k = 0 ; k < 8 ; k++ ){
            binInt32[j*8+k] = binInt8[k];
        }
    }
}
void saveAdress(int IpDecInt4[],int masqueDecInt4[]) { //  Enregistre l'adresse ip et le masque en cours dans un fichier
    FILE *PtrFich;
    int pos,j,k;
    struct Reseau Res ; // Instanciation d'une structure Reseau  

    PtrFich = fopen("../output/reseau.dta","r"); // On tente d'ouvrir le fichier "reseau.dta" en lecture 
    if ( PtrFich == NULL ){ // Si le fichier n'existe pas
        PtrFich = fopen("../output/reseau.dta","w "); // On l'ouvre avec l'option w, ce qui permet de le créer
        Res.numRes = 1 ;
    } else {
        PtrFich = fopen("../output/reseau.dta","a"); // Sinon on l'ouvre avec l'option a (écriture en fin de fichier)
        pos = ftell(PtrFich); // On stock la position du curseur (donc de la fin du fichier) dans pos
        j = (int)(pos / (long) sizeof(Res));  // on calcul j+1 qui est égal au nombre de reseau stocké dans le fichier
        Res.numRes = j+1 ;                         // j = position du curseur / taille d'un Reseau
    }                                            // On cast le sizeof en long et le tout en int 
    for (k=0;k<4;k++){
        Res.sIpDecInt4[k] = IpDecInt4[k];
        Res.sMaskDecInt4[k] = masqueDecInt4[k] ;
    }                                          

    if ( fwrite(&Res,sizeof(struct Reseau),1,PtrFich ) == -1 ){
        printf("Problème d'écriture dans le fichier\n");
    } else {
        printf("\nLe réseau n°%d \nAdresse ip : %d.%d.%d.%d \nMasque : %d.%d.%d.%d \na bien été sauvegardé dans un fichier \n",Res.numRes,Res.sIpDecInt4[0],Res.sIpDecInt4[1],Res.sIpDecInt4[2],Res.sIpDecInt4[3],Res.sMaskDecInt4[0],Res.sMaskDecInt4[1],Res.sMaskDecInt4[2],Res.sMaskDecInt4[3] );
    }
    fclose(PtrFich); // On ferme le fichier
}

void printSaveAdress(){ // Affiche les réseaux stockés dans un fichier
    FILE *PtrFich;
    int pos,j;
    struct Reseau Res ; // Instanciation d'une structure Reseau  
    PtrFich = fopen("../output/reseau.dta","r"); // On tente d'ouvrir le fichier "reseau.dta" en lecture 
    if ( PtrFich == NULL ) // Si le fichier n'existe pas
    {
        printf("Le Fichier est vide ou n'existe pas");
    } else 
    {   
        printf("******************** Adresses Stockées dans le fichier ********************\n");
        while ( fread(&Res,sizeof(struct Reseau),1,PtrFich ) == 1 )  // Tant que l'on peut lire encore 1 Res de taile struct Reseau dans PtrFich
        {   //On affiche les informations contenu dans le fichier
            if ( Res.numRes != -1){
                printf("\nReseau n° %d\nAdresse IP : %d.%d.%d.%d\nMasque : %d.%d.%d.%d\n",Res.numRes,Res.sIpDecInt4[0],Res.sIpDecInt4[1],Res.sIpDecInt4[2],Res.sIpDecInt4[3],Res.sMaskDecInt4[0],Res.sMaskDecInt4[1],Res.sMaskDecInt4[2],Res.sMaskDecInt4[3] );
            }
        }
        fclose(PtrFich); // On ferme le fichier
    }
}
void printOneSaveAdress(int adressToPrint){ // Affiche le reseau voulu stocké dans un fichier
    FILE *PtrFich;
    int pos,j;
    struct Reseau Res ; // Instanciation d'une structure Reseau  
    PtrFich = fopen("../output/reseau.dta","r"); // On tente d'ouvrir le fichier "reseau.dta" en lecture 
    if ( PtrFich == NULL ) // Si le fichier n'existe pas
    {
        printf("Le Fichier est vide ou n'existe pas");
    } else {   
        if ( fseek(PtrFich,(adressToPrint-1) * sizeof(struct Reseau),SEEK_SET ) == 0 ){ // On se positionne devant le réseau à afficher à l'écran
            fread(&Res,sizeof(struct Reseau),1,PtrFich ); // On lit un réseau
            printf("\nReseau n° %d\nAdresse IP : %d.%d.%d.%d\nMasque : %d.%d.%d.%d\n",Res.numRes,Res.sIpDecInt4[0],Res.sIpDecInt4[1],Res.sIpDecInt4[2],Res.sIpDecInt4[3],Res.sMaskDecInt4[0],Res.sMaskDecInt4[1],Res.sMaskDecInt4[2],Res.sMaskDecInt4[3] );
        } else {
            printf("Le réseau n°%d n'a pas pu être trouvé dans le fichier\n",adressToPrint );
        }
    }
    fclose(PtrFich); // On ferme le fichier
}
void returnSaveAdress(int numRes,int *ipDecInt4,int *ipBinInt32,int *masqueDecInt4,int *masqueBinInt32){
    FILE *PtrFich;
    int pos,j,i;
    struct Reseau Res ; // Instanciation d'une structure Reseau  
    PtrFich = fopen("../output/reseau.dta","r"); // On tente d'ouvrir le fichier "reseau.dta" en lecture 
    if ( PtrFich == NULL ) // Si le fichier n'existe pas
    {
        printf("Le Fichier est vide ou n'existe pas");
    } else {   
        if ( fseek(PtrFich,(numRes-1) * sizeof(struct Reseau),SEEK_SET ) == 0 ){ // On se positionne devant le réseau à afficher à l'écran
            fread(&Res,sizeof(struct Reseau),1,PtrFich );
            for(i=0;i<4;i++){
                ipDecInt4[i] = Res.sIpDecInt4[i]; // On écrit le réseau lu dans les tableaux passés en paramètres de la procédure
                masqueDecInt4[i] = Res.sMaskDecInt4[i];
            }
        } else {
            printf("Le réseau n°%d n'a pas pu être trouvé dans le fichier\n",numRes );
        }   
    }
    Ad4To32(ipDecInt4,ipBinInt32);
    Ad4To32(masqueDecInt4,masqueBinInt32);
    fclose(PtrFich); // On ferme le fichier
}
void delSaveAdress(int numRes){ // Supprime un réseau donné dans le fichier
// DOING SUPPRESSION LOGIQUE NON TESTE TODO COMPACTAGE -> SUPPRESSION PHYSIQUE
    FILE *PtrFich;
    int compteur,compteur2;
    struct Reseau Res ; // Instanciation d'une structure Reseau  
    printf("Suppression Logique\n");
    PtrFich = fopen("../output/reseau.dta","r+"); // On ouvre le fichier PtrFich avec l'option r+ (ecriture/lecture en début de fichier)
    if ( PtrFich == NULL ){ // Si le fichier est vide (ou n'existe pas)                      
        printf("Aucun fichier 'reseau.dta' éxiste\n"); // On affiche un message d'erreur
    } else {
        compteur = 0 ;
        while ( fread(&Res,sizeof(struct Reseau),1,PtrFich ) == 1 ){ // Tant que l'on peut lire encore 1 Res de taile struct Res dans PtrFich   
            compteur++; 
        } 
        // On positionne le curseur au début + numRes * taille Reseau 
        //-> le curseur sera postionné devant le reseau à supprimer (note: on commence à numéroter les Reseau à partir de 1)
        fseek(PtrFich,(numRes-1)*sizeof( struct Reseau),SEEK_SET);
        if ( fread(&Res,sizeof(struct Reseau),1,PtrFich ) != 1 )  // Si on arrive pas à lire le réseau à supprimer
        {   // Message d'erreur 
            printf("Erreur de lecture : Lecture du réseau n° %d a échoué\n", numRes); // On affiche un message d'erreur
        } else {
            fseek(PtrFich,-1*sizeof( struct Reseau ),SEEK_CUR); // On redéplace le curseur devant le réseau à modifier
            Res.numRes = - 1 ; // Sinon on modifie le numéro du réseau à -1 (Supression Logique) 
            // On essai d'écrire les informations contenu dans Res, de taille struct Reseau, on écrit 1 Res, dans le fichier PtrFich
            if ( fwrite(&Res,sizeof(struct Reseau),1,PtrFich ) == -1 ){ // On réécris le réseau avec le numéro -1
                printf("Problème d'écriture dans le fichier\nLe Fichier n'a pas été modifié");  // Si fwrite  renvoi -1 on met un message d'erreur car 
            } else {
                printf("Compacter le fichier \n");
       
                compteur = 0 ; // On initialise les numéros à redonner aux réseaux
                while ( fread(&Res,sizeof(struct Reseau),1,PtrFich ) == 1 ){ // Tant que l'on peut lire encore 1 Res de taile struct Reseau dans PtrFich   
                    if ( Res.numRes != -1 ){
                        compteur++;  // On incrémente que si le réseau n'existe pas 
                    } else {
                        compteur2++;  // Sinon on incrémente un deuxième compteur pour avoir le trop plein de réseaux à supprimer
                    }
                    Res.numRes = compteur ; 
                    // On essai d'écrire les informations contenu dans Res, de taille struct Reseau, on écrit 1 Res, dans le fichier PtrFich
                    if ( fwrite(&Res,sizeof(struct Reseau),1,PtrFich ) == -1 ){ // On réécris l'employé avec le matricule -1
                        printf("Erreur d'écriture : oups! il y a eu un problème lors du compactage du fichier\n");  // Si fwrite  renvoi -1 on met un message d'erreur car 
                    }   
                } 
            }
            printf("Fin du compactage du fichier\n");
            }                                                                                   
        }                                                   
        fclose(PtrFich); // On ferme le fichier ouvert 
    }

//******************************************-Fonctions-******************************************
int valOctet(int binInt8[]){ // Prend en entrée un tableau de 8 bits (un octet) et renvoi sa valeur en décimal
    int j, res=0, n= 0;
    for(j=7; j>=0; j--){
       if ( binInt8[j] == 1 ){
            res = res + (int) pow(2,n);
        }
        n++;
    }
    return res;
}
int checkIfAdressExist(int *decInt4,int ipOrMasque){ // Check si une adresse (ip ou masque) existe en mémoire
    int j;
    for ( j=0 ; j<4 ; j++ ){ // On regarde si une adresse existe en mémoire
        if ( decInt4[j] != 0 ) { return 1 ; } // Si oui on renvoie 1
        else if ( j == 3 ) { return 0 ; }        
    }
}
int checkAdress(char char100[], int ipOrMasque){ // Vérifie la validité de l'adresse
    int j,a=0,numberInt,compteur,octetOk,coupure=0 ;           // est valide : renvoie 1 si valide, 0 sinon
    char temp[3];
    char point=0; // Permet de verifier la structure de l'adresse ip donnée
    int longueur = strlen(char100);
    for( j=0 ; j <= longueur ; j++ ){ // On parcourt le tableau...
            if( char100[j] != '.' && char100[j] != '\0' ){ // ... si on ne trouve pas de point ni la fin du tableau
                temp[a] = char100[j]    ;    // on stock la valeur de l'char100 de j dans une vaariable temp
            }
            else if ( ( char100[j] == '.' || char100[j] == '\0' ) && point < 4 ) // ... si on trouve un point ou la fin du tableau
            {

                if( char100[j] == '.' && char100[j+1] == '.'){ // Empêche la saisie de deux points d'affilée
                    error(1);
                    return 0;
                }
                if( char100[j] == '.' && char100[j+1] == '\0'){ // Empêche la saisie d'un point en dernier caractère
                    error(1);
                    return 0;
                }
                numberInt = atoi(temp)    ; // on ressort la valeur numérique contenue dans temp
                if ( coupure == 1 && numberInt != 0 ){
                    error(3);
                    printf("Veuillez resaisir un masque valide svp\n");
                    return 0 ;
                }
                if ( ipOrMasque == 1 ){
                    if ( numberInt == 255 ) { compteur++; } else { coupure = 1 ; } // Marque la coupure entre les 1 et les 0
                    if ( compteur == 4 )  // Permet de refuser l'adresse 255.255.255.255
                    {
                        printf("Vous ne pouvez pas rentrer cette adresse : 255.255.255.255\n");
                        printf("Veuillez saisir un masque valide svp\n");
                        return 0;
                    }
                    int var = 128 ;
                    while ( var != 0 ){
                        if (numberInt == 0) { var=0;} // Dans le cas ou l'octet vaut 0
                        if (numberInt == 255) { var=0; numberInt = 0;} // Dans le cas ou l'octet vaut 255
                        numberInt = numberInt - var ;
                        var = var / 2 ;
                        if(var == numberInt){
                            numberInt = 0 ;
                            var = 0 ;
                            octetOk++; // Valide un octet
                            if(octetOk == 4){ // Si les 4 Octets sont valides
                                return 1;
                            }
                        }
                        if(numberInt<0){
                            error(3); // error 3 bits non contigus
                            return 0;
                        }
                    }
                    if ( numberInt != 0 ){
                        error(3); // error 3 bits non contigus
                        return 0;
                    }
                }
                temp[0]=0;
                a=-1; // On réinitialise temp et son compteur
                temp[1]=temp[2]='\0';
               if ( numberInt >= 0 && numberInt < 256){  // On vérifie que la valeur contenue maintenant dans    
                    point++;                            // numberInt ne dépasse pas les limites
                }
                else {
                    error(2);
                    return 0;
                }
            }
            else {
                    error(1);
                    return 0;
            }
            a++; // a permet d'avoir un compteur pour le tableau temp   
    }
    if(point != 4){
        error(1);
        return 0;
    }
    return 1;
}
int binaireToBase10(int binInt[],int bit){
// Fonctionne, prend en entré un tableau d'entiers contenant des 1 ou des 0 
// et un entier (bit) donnant la taille du tableau
    int j, res=0, n= 0;
    for(j=0; j<bit; j++){
        if ( binInt[j] == 1 ){
            res = res + (int) pow(2,n);
        } else if ( binInt[j] != 0 ) { return 0 ;} // Retourne 0 si binInt[j]!=0 && binInt[j]!=1
        n++;
    }
    return res;
}
int calcRange(int masqueBinInt32[]){ // Calcul le nombre d'ip disponible en fonction du masque
    int j,bit=32,range; // On initialise bit à 32
    for (  j=0 ; j < 32 ; j++ ){ // on parcourt masqueBinInt32
        if ( masqueBinInt32[j] == 1 ){ // Si on tombe sur un 1 
                bit--; // on décrémente bit
        } else if ( masqueBinInt32[j] != 0 ) { return 0 ;} // Retourne 0 si masqueBinInt32[j]!=0 && masqueBinInt32[j]!=1
    }
    range = pow(2,bit)-2; // le nombre d'ip disponible correspond à (2^bit)-2 (-2 car il y a l'adresse réseau et de broadcast)
    return range;
}