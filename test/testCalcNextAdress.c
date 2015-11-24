///////////////////////////////////////////////////////////////////////////////////////////////////////////
//********************************************************************************************************
//********************************************* CODE DE TEST *********************************************
//*********************************  Test de la procédure calcNextAdress *********************************
//*********************************  Utilisationde la fonction ...  *********************************
//********************************************************************************************************
//******************************************* EN PHASE DE TEST *******************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

//******************************************-Procédures-******************************************
void calcNextAdress(int networkBinInt32[],int *firstAdress4); // TODO Rempli un tableau decPoint4 de la première adresse ip de la plage
//******************************************-Fonctions-******************************************

//******************************************-Main-******************************************
int main(){

    int i,j;
    int netBinInt32[32];
    int maskBinInt32[32];
    int nextNetworkBinInt32[32];
    int nextNetworkDecInt4[4];
    int nextNetworkBinInt8[8];

    for(i=0;i<32;i++){
        netBinInt32[i]=0;
        maskBinInt32[i]=1;
    }

    for(i=32;i>18;i--){
        maskBinInt32[i]=0;
    }

    for(i=0;i<32;i++){
        if(i==0||i==1||i==8||i==18||i==10||i==20||i==21||i==31){
            netBinInt32[i]=1;
        }
    }
    printAdress32(netBinInt32);
    printAdress32(maskBinInt32);



    calcNextNetwork(netBinInt32,maskBinInt32,nextNetworkBinInt32,nextNetworkDecInt4);


    printf("netBinInt32 : \n");
    printAdress32(netBinInt32);
    printf("maskBinInt32 : \n");
    printAdress32(maskBinInt32);
    printf("nextNetworkBinInt32 : \n");
    printAdress32(nextNetworkBinInt32);
    printf("nextNetworkDecInt4 : \n");
    printAdress4(nextNetworkDecInt4);
    return 0;

}
void calcNextAdress(int baseDecInt4[],int *nextAdress4) 
{
    int j;
    for( j=0 ; j<4 ; j++ )
    {
        nextAdress4[j] = baseDecInt4[j]; // On rentre l'adresse réseau dans nextAdress4
    }

    for ( j=3 ; j>=0 ; j-- ) // On ajoute 1 pour avoir la première adresse ip disponible
    {
        if ( nextAdress4[j] < 255)
        {
            nextAdress4[j] += 1;
            break;
        } else if ( nextAdress4[j] == 255)
        {
            nextAdress4[j] = 0;
        }
    }
}
