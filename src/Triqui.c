/*
 ============================================================================
 Name        : Triqui.c
 Author      : Andrew Florez
 Version     :
 Copyright   : Your copyright notice
 Description : Juego de Triqui en consola
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ESPACIO ' '

/* Representación de caracteres del tablero de triqui
 * Inicialmente vacío (espacios)
 */
char matriz [3][3] = {

   ESPACIO,ESPACIO,ESPACIO,
   ESPACIO,ESPACIO,ESPACIO,
   ESPACIO,ESPACIO,ESPACIO
};

/* Matriz de número actual de posibilidades de ganar el juego
 * desde la perspectiva de cada celda
 * Si la celda ya esta ocupada, es igual a cero
 */
unsigned short int matPos [3][3] = {
		3,2,3,
		2,4,2,
		3,2,3
};

/* Primera fila con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int H1cont [3] = {
		0,0,0
};

/* Segunda fila con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int H2cont [3] = {
		0,0,0
};

/* Tercera fila con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int H3cont [3] = {
		0,0,0
};

/* Primera columna con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int V1cont [3] = {
		0,0,0
};

/* Segunda columna con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int V2cont [3] = {
		0,0,0
};

/* Tercera columna con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int V3cont [3] = {
		0,0,0
};

/* Diagonal de pendiente positiva con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int D1cont [3] = {
		0,0,0
};

/* Diagonal de pendiente negativa con posiciones ocupadas por el contrincante
 * (ocupada=1)
 */
unsigned short int D2cont [3] = {
		0,0,0
};

/* Primera fila con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int H1 [3] = {
		0,0,0
};

/* Segunda fila con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int H2 [3] = {
		0,0,0
};

/* Tercera fila con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int H3 [3] = {
		0,0,0
};

/* Primera columna con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int V1 [3] = {
		0,0,0
};

/* Segunda columna con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int V2 [3] = {
		0,0,0
};

/* Tercera columna con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int V3 [3] = {
		0,0,0
};

/* Diagonal de pendiente positiva con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int D1 [3] = {
		0,0,0
};

/* Diagonal de pendiente negativa con posiciones ocupadas por el computador
 * (ocupada=1)
 */
unsigned short int D2 [3] = {
		0,0,0
};

void obt_mov_jugador(void), obt_mov_computadora(void);
void mostrar_matriz(void);
int comprobar(void);
void marcacion (int, int);
int lanzamientoDado();

int main()
{

   char hecho;
   int iniciaJug=0;

   printf("Este es un juego de triqui.\n");
   printf("Usted jugara contra la computadora.\n");
   printf("Los siguientes valores simulan el resultado del lanzamiento de un dado.\n");
   printf("El jugador con el mayor valor inicia el juego.\n");

   iniciaJug=lanzamientoDado();

   mostrar_matriz();

   hecho = ESPACIO;
   do {

      printf("\n");
      if (iniciaJug)
      {
    	  obt_mov_jugador();
      }
      else
      {
    	  obt_mov_computadora();

    	  mostrar_matriz();
      }
      hecho = comprobar();
      if(hecho!=ESPACIO) break;
      if (iniciaJug)
      {
    	  obt_mov_computadora();
      }
      else
      {
    	  obt_mov_jugador();
      }
      hecho = comprobar();
      if (iniciaJug)
      {
    	  mostrar_matriz();
      }


   }while(hecho==ESPACIO);
   if(hecho=='x')
   {
	   if (iniciaJug)
	   {
		   mostrar_matriz();
		   printf("\nUsted ha ganado!\n");
	   }
   }
   else printf("\nYo gano!!!!\n");


   return 0;
}

void obt_mov_jugador(void)
{
   int x, y, t;
   char *p;
   p = (char *) matriz;

   for(t=0; *p!=ESPACIO && t<9; ++t) p++;
        if(t==9) {
      	  printf("\nEmpate\n");
      	  //mostrar_matriz();
      	  exit(0);
        }

   printf("Introduzca las coordenadas de su X (<fila 1..3><enter><columna 1..3><enter>): ");
   scanf("%d%d", &x, &y);
   x--; y--;
   if(matriz[x][y]!=ESPACIO) {
      printf("Movimiento invalido, pruebe de nuevo.\n");
      obt_mov_jugador();
   }
   else
   {
	  matriz[x][y] = 'x';
	  marcacion(x,y);
   }

}

/*
 * Actualiza cada posibilidad de triunfo del oponente (usuario), marca la posición de la jugada en la matriz de posibilidades
 * con un cero
 */
void marcacion(int x, int y)
{
	matPos[x][y] = 0;

	      if (x==0 && y==0)
	      {
	    	  H1cont[0]=1;
	      	  V1cont[0]=1;
	      	  D2cont[0]=1;
	      }
	      if (x==0 && y==1)
	      {
	    	  H1cont[1]=1;
	      	  V2cont[0]=1;
	      }
	      if (x==0 && y==2)
	      {
	    	  H1cont[2]=1;
	    	  V3cont[0]=1;
	    	  D1cont[2]=1;
	      }
	      if (x==1 && y==0)
	      {
	    	  H2cont[0]=1;
	    	  V1cont[1]=1;
	      }
	      if (x==1 && y==1)
	      {
	    	  H2cont[1]=1;
			  V2cont[1]=1;
			  D2cont[1]=1;
			  D1cont[1]=1;
	      }
		  if (x==1 && y==2)
		  {
			  H2cont[2]=1;
			  V3cont[1]=1;
		  }
		  if (x==2 && y==0)
		  {
			  H3cont[0]=1;
			  V1cont[2]=1;
			  D1cont[1]=1;
		  }
		  if (x==2 && y==1)
		  {
			  H3cont[1]=1;
			  V2cont[2]=1;
		  }
		  if (x==2 && y==2)
		  {
			  H3cont[2]=1;
			  V3cont[2]=1;
			  D2cont[2]=1;
		  }
}

/*
 * Actualiza cada posibilidad de triunfo del computador, marca la posición de la jugada en la matriz de posibilidades
 * con un cero
 */
void marcacionPC(int x, int y)
{
	matPos[x][y] = 0;

	      if (x==0 && y==0)
	      {
	    	  H1[0]=1;
	      	  V1[0]=1;
	      	  D2[0]=1;
	      }
	      if (x==0 && y==1)
	      {
	    	  H1[1]=1;
	      	  V2[0]=1;
	      }
	      if (x==0 && y==2)
	      {
	    	  H1[2]=1;
	    	  V3[0]=1;
	    	  D1[2]=1;
	      }
	      if (x==1 && y==0)
	      {
	    	  H2[0]=1;
	    	  V1[1]=1;
	      }
	      if (x==1 && y==1)
	      {
	    	  H2[1]=1;
			  V2[1]=1;
			  D2[1]=1;
			  D1[1]=1;
	      }
		  if (x==1 && y==2)
		  {
			  H2[2]=1;
			  V3[1]=1;
		  }
		  if (x==2 && y==0)
		  {
			  H3[0]=1;
			  V1[2]=1;
			  D1[1]=1;
		  }
		  if (x==2 && y==1)
		  {
			  H3[1]=1;
			  V2[2]=1;
		  }
		  if (x==2 && y==2)
		  {
			  H3[2]=1;
			  V3[2]=1;
			  D2[2]=1;
		  }
}

void obt_mov_computadora(void)
   {

	  register int t;
      register int j;
      int max=0;
      char *p;
      p = (char *) matriz;

      int xmax;
      int ymax;

      for(t=0; *p!=ESPACIO && t<9; ++t) p++;
      if(t==9) {
    	  mostrar_matriz();
    	  printf("\nEmpate\n");
    	  exit(0);
      }
      else
      {
    	  p = (char *) matriz;

    	  /*
    	   * Falta verificar si el computador puede ganar (tiene 2 celdas en linea)
    	   * Por el momento solo verifica si el contrincante puede ganar para bloquearlo
    	   */
    	  if (H1[0]+H1[1]+H1[2]==2 && (matriz[0][0]==ESPACIO || matriz[0][1]==ESPACIO || matriz[0][2]==ESPACIO))
		  {
			  for(t=0; *p!=ESPACIO && t<3; ++t) p++;
			  *p = '0';
			  marcacionPC(0,t);
		  }
		  else if (H2[0]+H2[1]+H2[2]==2 && (matriz[1][0]==ESPACIO || matriz[1][1]==ESPACIO || matriz[1][2]==ESPACIO))
		  {

			  for(t=0, p+=3; *p!=ESPACIO && t<3; ++t) p++;
			  *p = '0';
			  marcacionPC(1,t);
		  }
		  else if (H3[0]+H3[1]+H3[2]==2 && (matriz[2][0]==ESPACIO || matriz[2][1]==ESPACIO || matriz[2][2]==ESPACIO))
		  {
			  for(t=0, p+=6; *p!=ESPACIO && t<3; ++t) p++;
			  *p = '0';
			  marcacionPC(2,t);
		  }
		  else if (V1[0]+V1[1]+V1[2]==2 && (matriz[0][0]==ESPACIO || matriz[1][0]==ESPACIO || matriz[2][0]==ESPACIO))
		  {
			  for(t=0; *p!=ESPACIO && t<3; ++t) p=p+3;
			  *p = '0';
			  marcacionPC(t,0);
		  }
		  else if (V2[0]+V2[1]+V2[2]==2 && (matriz[0][1]==ESPACIO || matriz[1][1]==ESPACIO || matriz[2][1]==ESPACIO))
		  {
			  for(t=0, p+=1; *p!=ESPACIO && t<3; ++t) p=p+3;
			  *p = '0';
			  marcacionPC(t,1);
		  }
		  else if (V3[0]+V3[1]+V3[2]==2 && (matriz[0][2]==ESPACIO || matriz[1][2]==ESPACIO || matriz[2][2]==ESPACIO))
		  {
			  for(t=0, p+=2; *p!=ESPACIO && t<9; ++t) p=p+3;
			  *p = '0';
			  marcacionPC(t,2);
		  }
		  else if (D1[0]+D1[1]+D1[2]==2 && (matriz[2][0]==ESPACIO || matriz[1][1]==ESPACIO || matriz[0][2]==ESPACIO))
		  {
			  for(t=0, p+=6; *p!=ESPACIO && t<3; ++t) p=p-2;
			  *p = '0';
			  marcacionPC(2-t,t);
		  }
		  else if (D2[0]+D2[1]+D2[2]==2 && (matriz[0][0]==ESPACIO || matriz[1][1]==ESPACIO || matriz[2][2]==ESPACIO) )
		  {
			  for(t=0; *p!=ESPACIO && t<3; ++t) p=p+4;
			  *p = '0';
			  marcacionPC(t,t);
		  }
		  else
		  {
			  if (H1cont[0]+H1cont[1]+H1cont[2]==2 && (matriz[0][0]==ESPACIO || matriz[0][1]==ESPACIO || matriz[0][2]==ESPACIO))
			  {
				  for(t=0; *p!=ESPACIO && t<3; ++t) p++;
				  *p = '0';
				  marcacionPC(0,t);
			  }
			  else if (H2cont[0]+H2cont[1]+H2cont[2]==2 && (matriz[1][0]==ESPACIO || matriz[1][1]==ESPACIO || matriz[1][2]==ESPACIO))
			  {

				  for(t=0, p+=3; *p!=ESPACIO && t<3; ++t) p++;
				  *p = '0';
				  marcacionPC(1,t);
			  }
			  else if (H3cont[0]+H3cont[1]+H3cont[2]==2 && (matriz[2][0]==ESPACIO || matriz[2][1]==ESPACIO || matriz[2][2]==ESPACIO))
			  {
				  for(t=0, p+=6; *p!=ESPACIO && t<3; ++t) p++;
				  *p = '0';
				  marcacionPC(2,t);
			  }
			  else if (V1cont[0]+V1cont[1]+V1cont[2]==2 && (matriz[0][0]==ESPACIO || matriz[1][0]==ESPACIO || matriz[2][0]==ESPACIO))
			  {
				  for(t=0; *p!=ESPACIO && t<3; ++t) p=p+3;
				  *p = '0';
				  marcacionPC(t,0);
			  }
			  else if (V2cont[0]+V2cont[1]+V2cont[2]==2 && (matriz[0][1]==ESPACIO || matriz[1][1]==ESPACIO || matriz[2][1]==ESPACIO))
			  {
				  for(t=0, p+=1; *p!=ESPACIO && t<3; ++t) p=p+3;
				  *p = '0';
				  marcacionPC(t,1);
			  }
			  else if (V3cont[0]+V3cont[1]+V3cont[2]==2 && (matriz[0][2]==ESPACIO || matriz[1][2]==ESPACIO || matriz[2][2]==ESPACIO))
			  {
				  for(t=0, p+=2; *p!=ESPACIO && t<9; ++t) p=p+3;
				  *p = '0';
				  marcacionPC(t,2);
			  }
			  else if (D1cont[0]+D1cont[1]+D1cont[2]==2 && (matriz[2][0]==ESPACIO || matriz[1][1]==ESPACIO || matriz[0][2]==ESPACIO))
			  {
				  for(t=0, p+=6; *p!=ESPACIO && t<3; ++t) p=p-2;
				  *p = '0';
				  marcacionPC(2-t,t);
			  }
			  else if (D2cont[0]+D2cont[1]+D2cont[2]==2 && (matriz[0][0]==ESPACIO || matriz[1][1]==ESPACIO || matriz[2][2]==ESPACIO) )
			  {
				  for(t=0; *p!=ESPACIO && t<3; ++t) p=p+4;
				  *p = '0';
				  marcacionPC(t,t);
			  }
			  else
			  {
				  if (matriz[0][0]=='x' && matriz[0][2]=='x')
				  {

				  }
				  for(t=0; t<3; ++t)
				  {
					  for (j=0; j<3; ++j)
					  {
						if (matPos[t][j]>max)
						{
							max=matPos[t][j];
							xmax=t;
							ymax=j;
						}
					  }
				  }
				  if(max==0)
				  {
					  printf("Tablas\n");
					  exit(0);
				  }
				  else
				  {

					  matriz[xmax][ymax] = '0';
					  marcacionPC(xmax,ymax);
				  }

			  }

		  }

      }
}


void mostrar_matriz(void)
{
   int t;

   for(t=0; t<3; t++) {
      printf(" %c | %c | %c ", matriz [t][0],
	 matriz[t][1], matriz[t][2]);
      if(t!=2) printf("\n---|---|---\n");
   }
   printf("\n");
}


/*
 * Retorna espacio si nadie ha ganado
 * Retorna "x" si "x" ha ganado
 * Retorna "0" si "0" ha ganado
 */
int comprobar(void)
{
   int t;
   char *p;

   for(t=0; t<3; t++) {
      p = &matriz[t][0];
      /*
       * Recorrido de filas
       */
      if(*p==*(p+1) && *(p+1)==*(p+2)) return *p;
   }

   for(t=0; t<3; t++) {
      p = &matriz[0][t];
      /*
       * Recorrido de columnas
       */
      if(*p==*(p+3) && *(p+3)==*(p+6)) return *p;
   }


   if (matriz[0][0]==matriz[1][1] && matriz[1][1]==matriz[2][2])
      return matriz[0][0];

   if (matriz[0][2]==matriz[1][1] && matriz[1][1]==matriz[2][0])
      return matriz[0][2];

   return ESPACIO;
}

/*
 * El resultado define quien empieza el juego
 */
int lanzamientoDado()
{
	time_t t;
	int lanPC;
	int lanJug;

	/* Intializes random number generator */
	srand((unsigned) time(&t));
	lanPC=rand() % 6 + 1;
	lanJug=rand() % 6 + 1;
	printf("Lanzamiento computador: %d\n", lanPC);
	printf("Lanzamiento jugador: %d\n", lanJug);

	if (lanJug>lanPC)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

