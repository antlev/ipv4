///////////////////////////////////////////////////////////////////////////////////////////////////////////
//********************************************************************************************************
//********************************************* CODE DE TEST *********************************************
//*************************************  Test de la procédure Ad32To4 ************************************
//*********************************  Utilisation de la fonction valOctet *********************************
//********************************************************************************************************
//************************************************ TEST OK ***********************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

//******************************************-Procédures-******************************************
void Ad32To4(int binInt32[],int *decInt4); // Transforme une adresse 32 bits en decimal pointe
void printAdress32(int binInt32[]);
void printAdress4(int decInt4[]);
//******************************************-Fonctions-******************************************
int valOctet(int binInt8[]); // Transforme une adresse 32 bits en decimal pointe
//******************************************-Main-******************************************
int main(){

    int i,j;
    int netBinInt32[32];
    int netDecInt4[4];


    netBinInt32[0]=1;
    netBinInt32[1]=1;
    netBinInt32[2]=0;
    netBinInt32[3]=0;
    netBinInt32[4]=0;
    netBinInt32[5]=0;
    netBinInt32[6]=0;
    netBinInt32[7]=0;
    netBinInt32[8]=1;
    netBinInt32[9]=0;
    netBinInt32[10]=1;
    netBinInt32[11]=0;
    netBinInt32[12]=1;
    netBinInt32[13]=0;
    netBinInt32[14]=0;
    netBinInt32[15]=0 ;
    netBinInt32[16]=1;
    netBinInt32[17]=1;
    netBinInt32[18]=0;
    netBinInt32[19]=0;
    netBinInt32[20]=0;
    netBinInt32[21]=0;
    netBinInt32[22]=0;
    netBinInt32[23]=0;
    netBinInt32[24]=1;
    netBinInt32[25]=0;
    netBinInt32[26]=1;
    netBinInt32[27]=0;
    netBinInt32[28]=1;
    netBinInt32[29]=0;
    netBinInt32[30]=0;
    netBinInt32[31]=0 ;

    printf("netBinInt32 :\n");
    printAdress32(netBinInt32);
    printf("Ad32To4\n");
    Ad32To4(netBinInt32,netDecInt4);
    printf("netDecInt4\n");
    printAdress4(netDecInt4);
  
    

    for(i=32;i>18;i--){
        maskBinInt32[i]=0;
    }
    return 0;

}
void Ad32To4(int binInt32[],int *decInt4) // Transforme une adresse 32 bits en decimal pointe
{
    // WORKS!
    int j,k;
    int temp[8]; // Permet d'isoler un octet et de transformer sa valeu en decimal grace a la fonction binaireToBase10
    for ( j = 0 ; j < 4 ; j++ )
    {
        for ( k = 0 ; k < 8 ; k++ )
        {
            temp[k] = binInt32[j*8+k];
        }
        decInt4[j] = valOctet(temp);
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
int valOctet(int binInt8[]) // Transforme une adresse 32 bits en decimal pointe
{
    int j, res=0, n= 0;
    for(j=7; j>=0; j--)
    {
       if ( binInt8[j] == 1 )
        {
            res = res + (int) pow(2,n);
        }
        n++;
    }
    return res;
}
