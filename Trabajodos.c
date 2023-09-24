#include <stdio.h>
#include <string.h> // https://www.uco.es/grupos/eatco/informatica/metodologia/cadenasyarrays.pdf de aquí voy a sacar funciones como strlen(cadena) q me devuelve la cantidad de caracteres en la cadena , strcat q me concatena dos cadenas 

int itsNoDecimal(char *num)
{

    if(strcmp(num,"0")==0||strcmp(num,"1")==0|| strcmp(num,"2")==0 || strcmp(num,"3")==0 || strcmp(num,"4")==0 || strcmp(num,"5")==0 || strcmp(num,"6")==0||strcmp(num,"7")==0 ||strcmp(num,"8")==0||strcmp(num,"9")==0)
    {
        return 1 ; 
    } 
    return 0 ; 
}
int itsOctal(char *num)
{

    if(strcmp(num,"0")==0||strcmp(num,"1")==0|| strcmp(num,"2")==0 || strcmp(num,"3")==0 || strcmp(num,"4")==0 || strcmp(num,"5")==0 || strcmp(num,"6")==0||strcmp(num,"7")==0 ||strcmp(num,"8")==0||strcmp(num,"9")==0)
    {
        return 1 ; 
    } 
    return 0 ; 
}
int itsHexa(char *num)
{
    if(strcmp(num,"A")==0||strcmp(num,"B")==0|| strcmp(num,"C")==0 || strcmp(num,"D")==0 || strcmp(num,"F")==0 )
    {
        return 1; 
    }
    return 0 ; 
}
void revisarPalabra (char *palabra) 
{   
    int count = 0 ; 
    int hexa = 0 ; 
    for (int i = 0; i < (strlen(palabra)-1); i++)
    {

      if((strcmp(palabra[i],"0") ==0 && i==0)  )
      {
        count++;
      }  //Preguntamos si el primer elemento de la cadena no es un 0 
      if((strcmp(palabra[i],"-") ==0&& i!=0)) // elemtno que no sea el primero 
      // es un signo -(recordamos que solo el decimal admite - en el primero elemento)
      {
            count++ ; 
            hexa ++  ; 
      } else if(itsNoNum(palabra[i])==0)
      {
        if(itsHexa(palabra[i]==1))
        {

        }
      }
    }
    
}

int main()
{
   char cadena[100] ;  
   char  *groupFirst ="" ; 
   char  *groupSecond ="" ;
   char  *groupThird ="" ;
   char *cadenaUnida = ""; 
    printf("Ingrese una cadena: ");
    scanf( " %s",cadena) ; 
    for (int i = 0; i < (strlen(cadena)-1); i++) //strlen ´´´´me devuelve la cantidad de caracteres que tiene la cadena que me pasaron y le resto uno 1 ya que i =0
     {
      if(strcmp(cadena[i+1],"$") ==0 ) 
        {
       

        }

       strcat(cadenaUnida,cadena[i]);
       
     } 
     
    //strcat(cadena , algo) ; 
    


    return 0; 
}