#include <stdio.h>
#include <math.h>

#define n 10

FILE *q;

main(int argc, char *argv[] )
{
	
	double X, Y, xi=0, yi=0, xi2=0, yi2=0, a0, a1, soma=0, x[n], y[n], r[n];
	int i=0;
	
	q=fopen(argv[1],"r");
	
	while(fscanf(q, "%lf\t%lf", &X, &Y) != EOF)
	{
		xi+=X; //somatorio de xi
		xi2+=pow(X,2); //somatorio de xi²
		
		soma+=(X*Y); //somatorio de xiyi
		
		yi+=Y; //somatorio de yi
		yi2+=pow(Y,2); //somatorio de yi²
				
		x[i]=X;  
		y[i]=Y;  
		i++;
		
	}
	
	//Calculando os coeficientes
	
	a0 = ((xi2*yi) - (soma*xi)) / ((n*xi2) - pow(xi,2));
	a1 = ((n*soma) - (xi*yi)) / ((n*xi2) - pow(xi,2));
	
	printf("\n\t--------Valores de X--------\n");
	for(i=0; i<n; i++)
		printf("%.2lf\t", x[i]);
	printf("\n");
		
	printf("\n\t--------Valores Y--------\n");
	for(i=0; i<n; i++)
		printf("%.2lf\t", y[i]);
	printf("\n");
	
	printf("\n\t--------Coeficientes--------\n");
	printf("A0 = %lf\nA1 = %lf\n", a1, a0);
	
	fclose(q);
	
	//
	q=fopen("dados1.dat", "w");
	
	for(i=0; i<n; i++)
	{
		r[i] = (a1*x[i] + a0);
		fprintf(q, "%.2lf\t%.2lf\t%.2lf\n ", x[i], y[i], r[i]);
	}
	
	
	
}
