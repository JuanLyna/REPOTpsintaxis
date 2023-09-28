#include <stdio.h>
#include <string.h> // https://www.uco.es/grupos/eatco/informatica/metodologia/cadenasyarrays.pdf de aquí voy a sacar la funcion  strcat q me concatena dos cadenas 
#include <ctype.h> // de acá salimos el isdigit

#define AUTOMATA_OCTAL 1
#define AUTOMATA_DECIMAL 2
#define AUTOMATA_HEXADECIMAL 3
int  cantPalabrasOctales = 0  ; 
int  cantPalabrasHexadecimales = 0  ;
int  cantPalabrasDecimales = 0  ;  
int erroresLexicos=0 ; 
#define ESTADO_ACEPTACION_OCTAL 2
#define ESTADO_ACEPTACION_DECIMAL 2
#define ESTADO_ACEPTACION_HEXADECIMAL 3

int verificarPalabraOctal(char *palabra) ; 
int verificarPalabraHexadecimal(char *palabra) ; 
int verificarPalabraDecimal(char *palabra) ; 
int valorNumerico (char c ) ; 
int transformarACol(char c) ;
int revisarHexa(char *cadena)
{
      erroresLexicos  = 0 ; 
    for(int i = 0 ; cadena[i] ; i++)
    {
        if(cadena[i] != 'A' && cadena[i] != 'B'  && cadena[i] != 'C' && cadena[i] != 'D' && cadena[i] != 'E' && cadena[i] != 'F'  &&  isdigit(cadena[i])==0 && cadena[i] != 'x') // si alguno da true es que es un hexa 
    {
       erroresLexicos ++ ;  
    }
    } 
   
	
   return erroresLexicos  ; 
}

int revisarOctal(char *cadena)
{
      erroresLexicos  = 0 ; 
    
   for (int i = 0; cadena[i]; i++)
   {
     if(cadena[i] != '0'&&cadena[i] != '1'&&cadena[i] != '2'&&cadena[i] != '3'&&cadena[i] != '4'&&cadena[i] != '5'&&cadena[i] != '6'&&cadena[i] != '7') // si alguno da true es que es un hexa 
    {
       erroresLexicos ++ ;  
    } 
   }
   
   return erroresLexicos ; 
}
int revisarDecimal(char *cadena) 
{   
  erroresLexicos = 0; 
  for (int i = 0;cadena[i]; i++)
  {
	
    if(isdigit(cadena[i])==0 && cadena[i] != '-'&&cadena[i] != '+')
    {
		
      erroresLexicos  ++ ; 
    }
  }
  
 
  return erroresLexicos  ;
}
int estadoLetraAPosicion(char estado) ; 



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
	
	
	return tipoAutomata;
}


int verificarPalabra(char* palabra)
{
	int palabraCorrecta = -1;
	
	 
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
	
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizOctal[estadoActual][transformarACol(caracterActual)]);
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
	{// [0] [1-9]  +   - 
		{'D','C','B','B',} , //A-
		{'C' ,'C','D','D'},  //B
		{'C','C','D','D'} ,  //C+
		{'D','D','D','D'} // D
	};

	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizDecimal[estadoActual][transformarACol(caracterActual)]);
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
		{'E','E','C'}, //B
		{'E','D','E'} ,  //C
		{'E','D','E'} , //D+
		{'E','E','E'} //E
	};
	 
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizHexadecimal[estadoActual][transformarACol(caracterActual)]);
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

int transformarACol(char c){
	int col = 0;
	int valorNum = valorNumerico(c);
	if(valorNum== 0){
		col = 0;
	}
	else if (valorNum > 0){
		col = 1;
	}
	else{
		col = 2;
	}
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
		
		 if(distinguirConstante(grupoPalabra)==AUTOMATA_OCTAL)
		 {
			revisarOctal(grupoPalabra) ; 
			printf("Los errores lexicos de Octal han sido %d \n" , erroresLexicos) ; 
			
		 } else if (distinguirConstante(grupoPalabra)==AUTOMATA_DECIMAL)
		 {
			revisarDecimal(grupoPalabra) ; 
			printf("Los errores lexicos de Decimal han sido %d \n" , erroresLexicos) ; 
		 } else if (distinguirConstante(grupoPalabra)==AUTOMATA_HEXADECIMAL) 
		 {
			 revisarHexa(grupoPalabra) ; 
			printf("Los errores lexicos de HexaDecimal han sido %d \n" , erroresLexicos) ; 
		 }
		 
		if(erroresLexicos==0)
			{
				verificarPalabra(grupoPalabra) ;

			}  else printf("no es posible analizar la cadena porque no pertenece al alfabeto \n") ; 

 	
		grupoPalabra = strtok(NULL , "$") ; 
		 
	}
	
	printf("Cantidad de palabras correctas Decimales %d \n" , cantPalabrasDecimales) ;
	printf("Cantidad de palabras correctas  Octales %d \n" , cantPalabrasOctales) ;

	printf("Cantidad de palabras correctas Hexadecimales %d \n" , cantPalabrasHexadecimales) ;

	
	
    
    


    return 0; 
}
