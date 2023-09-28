#include <stdio.h>


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




struct PilaNumerica {
    int top;
    float items[100];
};

struct PilaCaracter
{
  int top;
    char items[100];
};


void inicializarPila(struct PilaNumerica* pila) {
    pila->top = -1;
}
void inicializarPilaCaracteres(struct PilaCaracter* pila) {
    pila->top = -1;
}

int isEmpty(struct PilaNumerica* pila) {
    return pila->top == -1;
}
int isEmptyCaracteres(struct PilaCaracter* pila) {
    return pila->top == -1;
}

void push(struct PilaNumerica* pila, float item) {
    
   pila->top=pila->top+1 ; 
    pila->items[pila->top] = item;
}
void pushCaracteres(struct PilaCaracter* pila, float item) {
    pila->top=pila->top+1 ; 
    pila->items[pila->top] = item;
}


float pop(struct PilaNumerica* pila) {
    if (!isEmpty(pila)) {
         float num = pila->items[pila->top] ;
        pila->top = pila->top-1 ; 
        return num;
    }
    return -1;
}
char popCaracteres(struct PilaCaracter* pila) {
    if (!isEmptyCaracteres(pila)) {
        char car = pila->items[pila->top] ;
        pila->top = pila->top-1 ; 
        return car;
    }
    return -1; 
}

float realizarOperacion(float num1, char operador, float num2) {
    switch (operador) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0) {
                return num1 / num2;
            } 
        default:
            printf("Operador no válido: %c\n", operador);
           return -1  ; 
    }
}


float evaluarExpresion(char* expresion) {
    struct PilaNumerica pilaNum;
    struct PilaCaracter pilaOp;
    inicializarPila(&pilaNum);
    inicializarPilaCaracteres(&pilaOp);

    int i = 0;
    while (expresion[i] != '\0') {
         float numero = valorNumerico(expresion[i]) ;

        if (numero>= 0 && numero <=9 ) {
           
            
            push(&pilaNum, numero);
        } else if (expresion[i] == '+' || expresion[i] == '-') {
            if(!isEmptyCaracteres(&pilaOp) &&
                   (pilaOp.items[pilaOp.top] == '+' || pilaOp.items[pilaOp.top] == '-' ||
                    pilaOp.items[pilaOp.top] == '*' || pilaOp.items[pilaOp.top] == '/')) 
            {   
                float num2 = pop(&pilaNum);
                float num1 = pop(&pilaNum);
                char operador = popCaracteres(&pilaOp); 
                float resultado = realizarOperacion(num1, operador, num2);
                push(&pilaNum, resultado);
            }
            pushCaracteres(&pilaOp, expresion[i]);
        } else if (expresion[i] == '*' || expresion[i] == '/') {
           if(!isEmptyCaracteres(&pilaOp) &&
                   (pilaOp.items[pilaOp.top] == '*' || pilaOp.items[pilaOp.top] == '/')) {
                float num2 = pop(&pilaNum);
                float num1 = pop(&pilaNum);
                char operador = popCaracteres(&pilaOp);
                float resultado = realizarOperacion(num1, operador, num2);
                push(&pilaNum, resultado);
            }
            pushCaracteres(&pilaOp, expresion[i]);
        }
        i++;
    }

    //Realizar opereaciones restantes con resultados parciales que se fueron dando
    while (!isEmptyCaracteres(&pilaOp)) {
        float num2 = pop(&pilaNum);
        float num1 = pop(&pilaNum);
        char operador = popCaracteres(&pilaOp);
        float resultado = realizarOperacion(num1, operador, num2);
        push(&pilaNum, resultado);
    }

    return pilaNum.items[pilaNum.top];
}


int main() {
    char entrada[100];
    printf("Ingrese la operación matemática (sin paréntesis): ");
    fgets(entrada, sizeof(entrada), stdin);

    float resultado = evaluarExpresion(entrada);

    printf("Resultado: %.2f\n", resultado);

    return 0;
}