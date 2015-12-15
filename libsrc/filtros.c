/**
 *  @file filtros.c

 *	@brief A continuación se presentan varias funciones que permite preparar archivos dependiendo del filtro seleccionado.
	
 *	Se tienen cuatro funciones principales:
 
 *	fs_head, fs_wc, fs_nl y fs_cut 
 
 *	Cada filtro de estos aplicado a un archivo de texto permite obtener diferentes salidas a partir del mismo

 *	@author Paula Figueroa.

 *	@date 04/12/2015.
 */
 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filtres.h"

/**
   @brief printstr: Es una función auxiliar que permite imprimir los contadores de caracteres, palabras, lineas de los filtros fs_wc y fs_nl
 
   Descripción: Ingresa un entero que se va recorriendo con un ciclo for controlado por una variable i, a medida que se recorre el número se incrementa aux
   El puntero nstr reserva espacios de memoria con la función malloc y la cantidad va dada por el incremento de aux + 2
   Luego se imprime, según el tamaño o el puntero nstr que fue dado la instrucción malloc, en formato entero (%d) y lo que se imprime es lo que ingresa en el num
   Y se escribe con la función write en el nstr y por último se libera la memoria con free. 
 
   @param num: es un número para controlar el tamaño del puntero controlado por el ciclo 

*/

void printstr(int num)
{
		int aux, i; /*! aux, i: son variables tipo entero que representan contadores i es para ir recorriendo cada num ingresado mientras que aux controla la memoria asignada al apuntador, ambas inicializan en 1.*/
		char *nstr; /*! nstr: puntero tipo char  */

        aux = 1;
        for( i = 1; i < num; i*=10 ) aux++; 
        nstr = (char *)malloc( aux + 2 ); 
        sprintf(nstr, "%d ", num);
        write( 1, nstr, strlen( nstr ) );
		free( nstr ); 
}

/**
	@brief fs_head: Este filtro mostrará las tres primeras líneas leídas. Las líneas están separadas por el carácter salto de línea '\ n'
	
	Descripción: Este filtro esta compuesto por un contador llamado count inicializado en cero y un caracter c. Con un ciclo while
	se recorre el archivo caracter a caracter usando la función read, cuando encuentra un salto de línea incrementa count hasta que este sea 3 o mayor e imprime.
	
	Ejemplo:
	\verbatim
	El archivo de texto de entrada es:
		Besa el aura que gime blandamente
		Las leves ondas que jugando riza;
		El sol besa a la nube en occidente
		Y de purpura y oro la matiza;
		La llama en derredor del tronco ardiente
		Por besar a otra llama se desliza,
		Y hasta el sauce, inclinandose a su peso,
		Al rio, que le besa, vuelve un beso.
		
	La salida es:
		Besa el aura que gime blandamente
		Las leves ondas que jugando riza;
		El sol besa a la nube en occidente
   \endverbatim
	
	@returns Devuelve las tres primeras líneas del archivo de texto
	
	@param fd: variable de entrada la cual es un archivo de texto seleccionado por el usuario

*/

void fs_head( int fd )
{
	int count = 0; /*!&lt; count: variable que se declara dentro de la función, tipo entero, es un contador que permite determinar la cantidad de lineas que se tienen en un texto,
	cada vez que dentro del while se encuentra un salto de línea se incrementa el contador, una vez llega a 3 se sale del ciclo.*/
	char c; /*!&lt; c: es una variable que se declara dentro de la función, tipo caracter en el cual se irá almacenando el caracter que se lee en el ciclo while */

	while( read( fd, &c, 1 ) && (count < 3) ){ /*!&lt; read: requiere del archivo que se va leer (fd), se le asigna la dirección de memoria de c (&c) para que aquí almacene cada caracteres leido y el 1 le indica que es de 1 a 1. Mientras el contador sea menor a 3 se escribe cada caracter con el comando */
		write( 1, &c, 1 ); /*!&lt; write: si se encuentra un salto de línea se incrementa el contador, de esta manera se controla que se escriban las tres primeras líneas. */
		if ( c == '\n' ) count++; /*!&lt; El if permite ir incrementando el count cuando c sea un salto de linea */
	}
}

/**
	@brief fs_wc: Este filtro contará el número de caracteres, palabras y líneas de la entrada y lo mostrará por pantalla 
	
	Descripción: Este filtro cuenta los caracteres, palabras y líneas, dados por los separadores. Los separadores de palabras son los caracteres salto de línea '\ n', tabulador '\ t' y espacio en blanco '', 
	y como separador de líneas sólo el salto de línea '\ n'. Dos palabras pueden estar separadas por 1 o más caracteres separadores
	
	@returns Devuelve la cantidad de caracteres, palabras y líneas que tiene un archivo de texto.
	
	Ejemplo:
	\verbatim
	El archivo de texto de entrada es:
		Besa el aura que gime blandamente
		Las leves ondas que jugando riza;
		El sol besa a la nube en occidente
		Y de purpura y oro la matiza;
		La llama en derredor del tronco ardiente
		Por besar a otra llama se desliza,
		Y hasta el sauce, inclinandose a su peso,
		Al rio, que le besa, vuelve un beso.
		
	La salida es:
		281 58 8
   \endverbatim
	
	@param fd: variable de entrada la cual es un archivo de texto seleccionado por el usuario
	
*/

void fs_wc( int fd )
{
	int nl = 0, np = 0, nc = 0, sep = 0; /*!&lt; nl: contador de líneas 
												 np: contador de palabras
												 nc: contador de caracteres
												 sep es una bandera para controlar la cantidad de delimitadores que puedan separar una palabra*/
	char c; /*!&lt; c: donde se almancerá cada caracter leido del archivo */
	
	while( read( fd, &c, 1 ) ){
		nc++; /*!&lt; nc++: cada vez que se lea un caracter en el archivo se incrementa el contador */
		switch( c ){
			case '\n': nl++; /*!&lt; Si el valor almacenado en c al recorrer el archivo es un salto de línea se incrementa nl */
			case '\t': /*!&lt; Si es un espacio o un tabulador se pasa al siguiente case donde se evalua */
			case ' ': if( !sep ) np++; /*!&lt; Si sep es diferente de 0 se incrementa la palabra y se hace sep = 1 */
					  sep = 1; /*!&lt; Si sep es 1 es porque encontró un delimitador de palabra ya sea tabulador o espacio */
				  break;
			default: sep = 0; /*!&lt; En cualquier caso que no encuentre ningún delimitador sep siempre será 0 */
		}
	 }
	printstr( nc ); /** @see void printstr(int num) */
	printstr( np );
	printstr( nl );
	c = 10;
	write( 1, &c, 1 );
}

/**
	@brief fs_nl: Este filtro numera les líneas de la entrada.
	
	Descripción: Este filtro permite enumerar cada línea en el archivo de texto. Por ejemplo
	\verbatim
		El archivo de texto de entrada es:
		Besa el aura que gime blandamente
		Las leves ondas que jugando riza;
		El sol besa a la nube en occidente
		Y de purpura y oro la matiza;
		La llama en derredor del tronco ardiente
		Por besar a otra llama se desliza,
		Y hasta el sauce, inclinandose a su peso,
		Al rio, que le besa, vuelve un beso.
		
	La salida es:
		1 Besa el aura que gime blandamente
		2 Las leves ondas que jugando riza;
		3 El sol besa a la nube en occidente
		4 Y de purpura y oro la matiza;
		5 La llama en derredor del tronco ardiente
		6 Por besar a otra llama se desliza,
		7 Y hasta el sauce, inclinandose a su peso,
		8 Al rio, que le besa, vuelve un beso.
   \endverbatim
	
	@returns Devuelve cada línea numerada
	
	@param fd: variable de entrada la cual es un archivo de texto seleccionado por el usuario
	
*/

void fs_nl( int fd )
{
	int nl = 1, new = 1, aux, i; /*!&lt; new es una bandera para controlar las lineas, cada vez que encuentra un salto de línea coloca el número que va acumulando en la variable nl*/
	char c, *nlstr;

	while( read( fd, &c, 1) ){
		if( new ){
			printstr( nl ); /*!&lt; Usa printstr para imprimir los números al inicio de cada línea de texto */ /** @see void printstr(int num) */
			nl++;
			new = 0;
		}
		if ( c == '\n' ) new = 1;
		write( 1, &c, 1 );		
	}
}

/**
	@brief fs_cut: Este filtro muestra la palabra en la posición col de cada línea
	
	Descripción: El filtro recibe el archivo y la columna por la cual se quiere cortar el archivo, la primera palabra de cada línea estará en la posición 1, por lo que si se ingresa 1 se mostrará la primera palabra de cada línea que encuentra en el archivo.
	
	@returns Devuelve el archivo partido según la columna seleccionada
	
	@param fd: variable de entrada la cual es un archivo de texto seleccionado por el usuario
	
	@param col: entero que indica la posición de la columna se desea imprimir en el archivo.
	
	Ejemplo:
	\verbatim
		El archivo de texto de entrada es:
		Besa el aura que gime blandamente
		Las leves ondas que jugando riza;
		El sol besa a la nube en occidente
		Y de purpura y oro la matiza;
		La llama en derredor del tronco ardiente
		Por besar a otra llama se desliza,
		Y hasta el sauce, inclinandose a su peso,
		Al rio, que le besa, vuelve un beso.
		
	La salida es:
		el
		leves
		sol
		de
		llama
		besar
		hasta
		rio
   \endverbatim
	
*/

void fs_cut( int fd, int col )
{
	char c;
	int pal = 1, nc = 0;

	while( read( fd, &c, 1 ) ){
		if ( c == '\n' ){ /*!&lt; Se debe tener en cuenta el salto de línea */
			if((pal >= col)&& (nc>=0)) write( 1, &c, 1 ); /*!&lt; e ir contando la cantidad de palabras si estas son mayores o iguales al número ingresado en col se debe imprimir en pantalla. Para controlar que no se imprima saltos de linea en caso que la primera línea se encuentre vacía
			                                                      se debe ingresar en la condición que nc es mayor o igual a cero.*/
			pal = 1;
			nc = 0;
		} 
		else if ( pal == col ){ nc++; write( 1, &c, 1 );}
		if (( c == '\t' ) || ( c == ' ' )) pal++; /*!&lt; Si el caracter en c es una tabulación '\t' o un espacio ' ' incrementa el contador pal ya que es una palabra
	}
}

