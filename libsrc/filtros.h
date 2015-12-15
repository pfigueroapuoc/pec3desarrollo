/*! \mainpage Control de Versiones y Documentación
 * \section control Control de versiones
 *
 * \section intro_sec Introducción
 *
 * En la presente documentación encontrará información relacionada con las funciones filtro.c y filtro.h desarrolladas en c, para realizar esta documentación se usó Doxygen.
 *
 * Mientras que en la segunda encontrará las cabeceras de cada una de estas funciones.
 *
 * Por cada archivo (filtros.h y filtros.c) de la copia local del depósito se encuentran los comentarios de cabecera en el que, usando siempre etiquetas de Doxygen, se indica, de forma resumida y
 * también de forma detallada, qué se encuentra en el archivo, el autor y la fecha en la que se genera la documentación.
 *
 * La documentación se generó en formato html en un directorio llamdo doc.
 *
 * La idea de esta sección de la PEC es desarrollar habilidades en la documentación de un producto de desarrollo de software
 *
 * Finalmente toda esta información se encuentra almacenada en el repositorio local libsrc y adicionalmente en el repositorio remoto en github.
 */

/**
 *  @file filtros.h

 *	@brief Cabeceras de las filtros ofrecidos en filtros.c
	
 *	Se listas los filtros principales:
 
 *	fs_head, fs_wc, fs_nl y fs_cut 
 
 *  Cada filtro tiene como entrada un archivo representado por la variable (fd), y fs_cut tiene un parámetro adicional que es un entero el cual indica la columna a imprimir
 
 *	@author Paula Figueroa.

 *	@date 04/12/2015.
 */

void fs_head( int fd );
void fs_wc( int fd );
void fs_nl( int fd );
void fs_cut( int  fd, int col );

