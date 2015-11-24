///////////////////////////////////////////////////////////////////////////////////////////////////////////
//********************************************************************************************************
//********************************************* CODE DE TEST *********************************************
//*********************************  Test de la procédure Ad4To32 *********************************
//*********************************  Utilisation de la fonction ...  *********************************
//********************************************************************************************************
//******************************************* TEST OK *******************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

//******************************************-Procédures-******************************************
void Ad4To32(int decInt4[],int *binInt32); // Transforme une adresse en decimal pointe en adresse 32 bits
void printAdress32(int binInt32[]);
void printAdress4(int decInt4[]);
void base10ToBinaire(int n, int *binInt8); // Prend une valeur n compris entre 0 et 255 et la stock sous forme binaire dans un tableau de 8 cases

//******************************************-Fonctions-******************************************
//******************************************-Main-******************************************
int main(){

    int netBinInt32[32];
    int netDecInt4[4];

    netDecInt4[0]=192;
    netDecInt4[1]=168;
    netDecInt4[2]=10;
    netDecInt4[3]=1;

    printf("Ad4To32\n");

    Ad4To32(netDecInt4,netBinInt32);
    printf("netBinInt32 :\n");
    printAdress32(netBinInt32);

    return 0;

}
void Ad4To32(int decInt4[],int *binInt32) // Transforme une adresse en decimal pointe en adresse 32 bits
{
    // WORKS!
    int binInt8[8];
    int j,k,n;
    int temp[8]; // Permet d'isoler un octet et de transformer sa valeu en decimal grace a la fonction binaireToBase10
    base10ToBinaire(192,binInt8);
    for ( j = 0 ; j < 4 ; j++ )
    {
        n = decInt4[j] ;
        base10ToBinaire(n,binInt8);
        for ( k = 0 ; k < 8 ; k++ )
        {
            binInt32[j*8+k] = binInt8[k];
        }
        printf("\n");
    }
}
void printAdress32(int binInt32[])
{
    int j;
    for ( j=0 ; j<32 ; j++ )
    {
        printf("%d",binInt32[j] );
        if ( j==7 || j==15 || j==23 ) { printf("." ) ; }
    }
    printf("\n");
} 
void printAdress4(int decInt4[])
{
    printf("%d.%d.%d.%d\n", decInt4[0],decInt4[1],decInt4[2],decInt4[3]);
}
void base10ToBinaire(int n, int *binInt8) // Prend une valeur n compris entre 0 et 255 et la stock sous forme binaire dans un tableau de 8 cases
{
    int j;
    for ( j=7 ; j>=0 ; j-- )
    {
        binInt8[j] = n%2 ;
        n = n/2 ;
    }
}
