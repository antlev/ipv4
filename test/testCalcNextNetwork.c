///////////////////////////////////////////////////////////////////////////////////////////////////////////
//********************************************************************************************************
//********************************************* CODE DE TEST *********************************************
//********************************  Test de la procédure calcNextNetwork  ********************************
//*********************************  Utilisationde la fonction valOctet  *********************************
//********************************************************************************************************
//*********************************************** TEST OK ***********************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

//******************************************-Procédures-******************************************
void printAdress32(int binInt32[]); // Formate et imprime une adresse en binaire dans un tableau de 32 cases
void calcNextNetwork(int networkBinInt32[],int maskBinInt32[],int *nextNetworkBinInt32,int *nextNetworkDecInt4); // Prend en entrée l'adresse reseau et le masque et rempli les tableaux nextNetworkDecInt4 et nextNetworkBinInt32
void printAdress4(int decInt4[]); // Formate et imprime une adresse en décimal pointé dans un tableau de 4 cases
//******************************************-Fonctions-******************************************
int binaireToBase10(int binInt[],int bit);

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


void calcNextNetwork(int networkBinInt32[],int maskBinInt32[],int *nextNetworkBinInt32,int *nextNetworkDecInt4) // Prend en entrée l'adresse reseau et le masque et rempli les tableaux nextNetworkDecInt4 et nextNetworkBinInt32
{   // Prend en entrée l'adresse reseau et le masque 
    // Rempli les tableaux nextNetworkDecInt4 et nextNetworkBinInt32

    int temp=0,j,octet,pas,i;
    int nextNetworkBinInt8[8];
    for( j=0 ; j<32 ; j++ )
    {
        nextNetworkBinInt32[j] = networkBinInt32[j] && maskBinInt32[j];
    } 
    temp = -1 ; 
    for( j=0 ; j<32 ; j++ )
    {
        if(maskBinInt32[j] == 1)
        {
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
        decInt4[j] = binaireToBase10(temp,8);
    }
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

void printAdress4(int decInt4[])
{
    printf("%d.%d.%d.%d\n", decInt4[0],decInt4[1],decInt4[2],decInt4[3]);
        
}

int binaireToBase10(int binInt[],int bit)
// Fonctionne, prend en entré un tableau d'entiers contenant des 1 ou des 0 
// et un entier (bit) donnant la taille du tableau
{
    int j, res=0, n= 0;
    for(j=0; j<bit; j++)
    {
       if ( binInt[j] == 1 )
        {
            res = res + (int) pow(2,n);
        }
        n++;
    }
    return res;
}