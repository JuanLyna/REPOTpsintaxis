#include <stdio.h>
#include <string.h> // https://www.uco.es/grupos/eatco/informatica/metodologia/cadenasyarrays.pdf de aquí voy a sacar la funcion  strcat q me concatena dos cadenas 
#include <ctype.h> // de acá salimos el isdigit

#define AUTOMATA_OCTAL 1
#define AUTOMATA_DECIMAL 2
#define AUTOMATA_HEXADECIMAL 3
int  cantPalabrasOctales = 0  ; 
int  cantPalabrasHexadecimales = 0  ;
int  cantPalabrasDecimales = 0  ;  
#define ESTADO_ACEPTACION_OCTAL 2
#define ESTADO_ACEPTACION_DECIMAL 2
#define ESTADO_ACEPTACION_HEXADECIMAL 2

int verificarPalabraOctal(char *palabra) ; 
int verificarPalabraHexadecimal(char *palabra) ; 
int verificarPalabraDecimal(char *palabra) ; 

int revisarHexa(char *cadena)
{
      int count  = 0 ; 
    for(int i = 0 ; cadena[i] ; i++)
    {
        if(cadena[i] == 'A' && cadena[i] == 'B'  && cadena[i] == 'C' && cadena[i] == 'D' && cadena[i] == 'E' && cadena[i] == 'F'  &&  !(isdigit(cadena[i]))) // si alguno da true es que es un hexa 
    {
       count ++ ;  
    }
    }
    printf("%s" , "rh") ; 
   return count  ; 
}

int revisarOctal(char *cadena)
{
      int count  = 0 ; 
    
   for (int i = 0; cadena[i]; i++)
   {
     if(cadena[i] == '0'&&cadena[i] == '1'&&cadena[i] == '2'&&cadena[i] == '3'&&cadena[i] == '4'&&cadena[i] == '5'&&cadena[i] == '6'&&cadena[i] == '7') // si alguno da true es que es un hexa 
    {
       count ++ ;  
    }
   }
    printf("%s" , "ro") ; 
   return count ; 
}
int revisarDecimal(char *cadena) 
{   
  int count = 0; 
  for (int i = 0;cadena[i]; i++)
  {
    if((isdigit(cadena[i])) && cadena[i] == '-'&&cadena[i] == '+')
    {
      count  ++ ; 
    }
  }
   printf("%s" , "rd") ; 
  return count  ;
}
int estadoLetraAEstadoANum(char estado) ; 
int erroreslexicos  = 0 ; 


int distinguirConstante(char* palabra){
	int tipoAutomata = -1;
	if(palabra[0] == '0'){
		if(palabra[1] == 'x'){
			tipoAutomata = AUTOMATA_HEXADECIMAL;
		}
		else{
			tipoAutomata = AUTOMATA_OCTAL;
		}
	}
	else{
		tipoAutomata = AUTOMATA_DECIMAL;
	}
	 printf("%s" , "dc") ; 
	return tipoAutomata;
}


int verificarPalabra(char* palabra)
{
	int palabraCorrecta = -1;
	 printf("%s" , "vp") ; 
	switch (distinguirConstante(palabra))
	{
		case AUTOMATA_OCTAL:
			printf("Los errores lexicos en octal han sido %d" , revisarOctal(palabra));
			palabraCorrecta = verificarPalabraOctal(palabra);
			
			break;
		case AUTOMATA_DECIMAL:
			printf("Los errores lexicos en decimal han sido %d" , revisarDecimal(palabra));
			palabraCorrecta = verificarPalabraDecimal(palabra);
			break;
		case AUTOMATA_HEXADECIMAL:
			printf("Los errores lexicos en Hexadecimal han sido %d" , revisarHexa(palabra));
			palabraCorrecta = verificarPalabraHexadecimal(palabra);
			break;
		default:
			palabraCorrecta = -1;
	}
}

int verificarPalabraOctal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizOctal[4][2] = 
	{
		{1,3} , 
		{3,1 }, 
		{3,2} , 
		{3,3}
	};
	 printf("%s" , "vo") ; 
	for(int i=0; i<palabra[i]; i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAEstadoANum(matrizOctal[estadoActual][caracterActual]);
	}
	if(estadoActual == ESTADO_ACEPTACION_OCTAL){
		verificaPalabra = 1;
		cantPalabrasOctales++;
	}
	return verificaPalabra;
	
}

int verificarPalabraDecimal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizDecimal[4][4] = 
	{
		{2,1,1,3} , 
		{3 ,3,3,2}, 
		{3,3,3,2} , 
		{3,3,3,3}
	};
	 printf("%s" , "rd") ; 
	for(int i=0; i<palabra[i]; i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAEstadoANum(matrizDecimal[estadoActual][caracterActual]);
	}
	if(estadoActual == ESTADO_ACEPTACION_DECIMAL){
		verificaPalabra = 1;
		cantPalabrasDecimales++;
	} else 
	return verificaPalabra;
}

int verificarPalabraHexadecimal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizHexadecimal[5][3] = 
	{
		{1,4,4} , 
		{4,2,4}, 
		{4,4,3} , 
		{4,4,3} , 
		{4,4,4}
	};
	 printf("%s" , "vhex") ; 
	for(int i=0; i<palabra[i]; i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAEstadoANum(matrizHexadecimal[estadoActual][caracterActual]);
	}
	if(estadoActual == ESTADO_ACEPTACION_HEXADECIMAL){
		verificaPalabra = 1;
		cantPalabrasHexadecimales++;
	}
	return verificaPalabra;
}

int estadoLetraAEstadoANum(char estado){
	int numCol = -1;
	switch(estado){
		case 'A':
			numCol = 0;
			break;
		case 'B':
			numCol = 1;
			break;
		case 'C':
			numCol = 2;
			break;
		case 'D':
			numCol = 3;
			break;
		case 'E':
			numCol = 4;
			break;
		case 'F':
			numCol = 5;
			break;
		default:
			numCol = -1;
			break;
	}
	return numCol;
}



int main()
{
   char cadena[100] ;  
  
   char *cadenaUnida = ""; 
   int constante = 0 ;  
   int c = 0 ; 
   int erroresLexicos = 0 ; 
    printf("Ingrese una cadena: ");
	
    scanf( " %s",&cadena) ; 
	 printf("Ingrese una cadena: ");
    for (int i = 0; i < cadena[i]; i++) //cadena[i] se usa como condición ya que cuando apunte a un lugar de la cadena q esté vacía , este fallará 
     {
      
       printf("%d" , i) ; 
      if(cadena[i]=='$' ) 
        {
          verificarPalabra(cadenaUnida) ;          
        } else  {
			   char p[2] ; 
			   p[0] = cadena[i] ; 
			   p[1] = '\0' ;
			   strcat(cadenaUnida,p) ; 
 		}

        
          

       
       
     } 
     
    
    


    return 0; 
}