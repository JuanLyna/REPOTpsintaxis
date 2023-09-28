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
#define ESTADO_ACEPTACION_HEXADECIMAL 3

int verificarPalabraOctal(char *palabra) ; 
int verificarPalabraHexadecimal(char *palabra) ; 
int verificarPalabraDecimal(char *palabra) ; 
int valorNumerico (char c ) ; 
int transformarAColOctal (char c) ; 
int revisarHexa(char *cadena)
{
      int count  = 0 ; 
    for(int i = 0 ; cadena[i] ; i++)
    {
        if(cadena[i] != 'A' && cadena[i] != 'B'  && cadena[i] != 'C' && cadena[i] != 'D' && cadena[i] != 'E' && cadena[i] != 'F'  &&  isdigit(cadena[i])==0 && cadena[i] != 'x') // si alguno da true es que es un hexa 
    {
       count ++ ;  
    }else cantPalabrasHexadecimales++ ; 
    } 
    printf("%s" , "rh") ; 
	fflush(stdout);
   return count  ; 
}

int revisarOctal(char *cadena)
{
      int count  = 0 ; 
    
   for (int i = 0; cadena[i]; i++)
   {
     if(cadena[i] != '0'&&cadena[i] != '1'&&cadena[i] != '2'&&cadena[i] != '3'&&cadena[i] != '4'&&cadena[i] != '5'&&cadena[i] != '6'&&cadena[i] != '7') // si alguno da true es que es un hexa 
    {
       count ++ ;  
    } else cantPalabrasOctales++ ; 
   }
    printf("%s" , "ro") ; 
	fflush(stdout);
   return count ; 
}
int revisarDecimal(char *cadena) 
{   
  int count = 0; 
  for (int i = 0;cadena[i]; i++)
  {
	 printf("caracter actual %c \n" ,cadena[i]) ; 
    if(isdigit(cadena[i])==0 && cadena[i] != '-'&&cadena[i] != '+')
    {
		printf("entre \n" ) ; 
      count  ++ ; 
    }else cantPalabrasDecimales++ ; 
  }
   printf("%s" , "rd") ; 
   fflush(stdout);
  return count  ;
}
int estadoLetraAPosicion(char estado) ; 
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
	 printf("primera letra es  %c \n" , palabra[0]) ; 
	  printf("segunda letra es %c \n" , palabra[1]) ;
	   printf("tipo automata es %d \n " , tipoAutomata) ;
	 fflush(stdout);
	return tipoAutomata;
}


int verificarPalabra(char* palabra)
{
	int palabraCorrecta = -1;
	
	 fflush(stdout);
	switch (distinguirConstante(palabra))
	{
		case AUTOMATA_OCTAL:
			
			palabraCorrecta = verificarPalabraOctal(palabra);
			
			break;
		case AUTOMATA_DECIMAL:
			
			palabraCorrecta = verificarPalabraDecimal(palabra);
			break;
		case AUTOMATA_HEXADECIMAL:
			
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
	{  // 0   0-7
		{'B','D'} , //A-
		{'C','C' }, //B
		{'C','C'} , //C+
		{'D','D'}  //D
	};
	 printf("verificar palabra octal llega la palabra%s \n" ,palabra) ; 
	 fflush(stdout);
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizOctal[estadoActual][transformarAColOctal(caracterActual)]);
		printf("lueg de ejecturar caracter %c el  estado es %d \n",caracterActual , estadoActual) ; 
	}
	
	if(estadoActual == ESTADO_ACEPTACION_OCTAL){
		verificaPalabra = 1;
		cantPalabrasOctales++;
	}
	printf("estado actual es %d \n" , estadoActual) ; 
	return verificaPalabra;
	
}

int verificarPalabraDecimal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizDecimal[4][4] = 
	{// [0] [1-9]  +   - 
		{'C','B','B','D',} , //A-
		{'C' ,'D','D','C'},  //B
		{'C','D','D','C'} ,  //C+
		{'D','D','D','D'} // D
	};
	 printf("%s \n" , "rd") ; 
	 fflush(stdout);
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizDecimal[estadoActual][transformarAColDecimal(caracterActual)]);
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
	{//   0  1-F  X
		{'B','E','E'} , //A-
		{'E','C','E'}, //B
		{'E','E','D'} ,  //C
		{'E','E','D'} , //D+
		{'E','E','E'} //E
	};
	 printf("%s \n" , "vhex") ; 
	 fflush(stdout);
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizHexadecimal[estadoActual][transformarAColHexa(caracterActual)]);
	}
	if(estadoActual == ESTADO_ACEPTACION_HEXADECIMAL){
		verificaPalabra = 1;
		cantPalabrasHexadecimales++;
	}
	return verificaPalabra;
}

int estadoLetraAPosicion(char estado){
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
int transformarAColOctal(char c){
	int col = 0;
	int valorNum = valorNumerico(c);
	printf("valor numerico a devolver es %d y caracter es %c \n" , valorNum , c) ; 
	if(valorNum!=-1 && valorNum < 8){
		if(valorNum== 0){
			col = 0;
		}
		else{
			col = 1;
		}
	}
	else{
		col = 2;
	}
	printf("la columna a devolver es %d \n" , col) ; 
	return col;
}


int valorNumerico(char caracter)
{
	 int numero = -1;
	switch (caracter)
{
		 case '0':
			numero = 0;
			 break;
		 case '1':
		 numero = 1;
		 break;
		 case '2':
		numero = 2;
		break;
		 case '3':
		 numero = 3;
		break;
		case '4':
		 numero = 4;
		break;
		case '5':
			numero = 5;
		 break;
		 case '6':
			 numero = 6;
			 break;
		 case '7':
			numero = 7;
			break;
		 case '8':
			 numero = 8;
		 break;
		 case '9':
		numero = 9;
			 break;
		 case 'A':
		numero = 10;
		 break;
		case 'B':
		numero = 11;
		 break;
	 	 case 'C':
 		 numero = 12;
		 break;
		 case 'D':
		 numero = 13;
		break;
		 case 'E':
		 numero = 14;
		break;
		 case 'F':
		numero = 15;
	 break;
		 }
	return numero;
}


int main()
{
   /**/char cadena[100] ;  
  

    printf("Ingrese una cadena: ");
	fflush(stdout);
    scanf( " %s",&cadena) ; 
	char *grupoPalabra =   strtok(cadena,"$") ; 
	
    
	while (grupoPalabra!=NULL)
	{	
		printf("%s \n", grupoPalabra);
		 printf("verificar palabra ");
		verificarPalabra(grupoPalabra) ; 
 	
		grupoPalabra = strtok(NULL , "$") ; 
		 
	}
	
	
	printf("verificarPalabraOctal es %d \n", verificarPalabraOctal("012")) ;
	
    
    


    return 0; 
}