#include <stdio.h>
#include <string.h> // https://www.uco.es/grupos/eatco/informatica/metodologia/cadenasyarrays.pdf de aquí voy a sacar funciones como strlen(cadena) q me devuelve la cantidad de caracteres en la cadena , strcat q me concatena dos cadenas

#define AUTOMATA_OCTAL 1
#define AUTOMATA_DECIMAL 2
#define AUTOMATA_HEXADECIMAL 3
int  cantPalabrasOctales = 0  ; 
int  cantPalabrasHexadecimales = 0  ;
int  cantPalabrasDecimales = 0  ;  

#define ESTADO_ACEPTACION_OCTAL 2
#define ESTADO_ACEPTACION_DECIMAL 2
#define ESTADO_ACEPTACION_HEXADECIMAL 2

int estadoLetraAEstadoANum(char estado) ; 
int erroreslexicos  = 0 ; 
int main(){

}

int matrizOctal() 
{
	 
}

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


int verificarPalabra(char* palabra){
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
	{
		{1,3} , 
		{3,1 }, 
		{3,2} , 
		{3,3}
	};
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

/*
if(cadena.size %2 != 0 )
{
	return -1 ; 
	} 

for ( int  i = 0; cadena[i]; i++)
{
	
	
	c = cadena[0] ; 
	if( i%2 == 0  )
	{
		revisarCaracter(decimal) ;
		
	} else revisar caracterOperador(cadena[i]) 
}


switch (operador )
{
case  '+':
	resultado =  cadena1 + cadena2 ;
	break;
case '-' : 
	resultado =  cadena1 -cadena2 ;
case '*' :
	resultado = cadena1 * cadena2 ; 
case '/' :
	resultado = cadena1 / cadena2 ;
default:
	break;
}
return resultado  ; */
/*

	[0-9]	+	-
A-	  C		B	B
B	  C		D	D
C+    C		D	D
D     D		D	D


[A][0]->[C][0]->[C][0]
[A][1]->[B][2]->[D][0]
[A][1]->[B][0]->[C][0]




*/


/*
 '/0'
casos : 1+2*3/5*6-7
casos : 2*3/5*6

casos: cadena original = 1-2*3+1/5*6-7*8
	 cadenaOrd = 2*3/5*6 + 1
a=b=c=d 
a  = 2 d =1 
if(num[i+2]!= + && num[i+2]!= - &&num[i+2]!= '\0')
{
	int result = resolverOperador(num[i] , num[i+1] , num[i+2]) ; 
	i = i+5
}

*/