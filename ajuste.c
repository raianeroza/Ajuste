#include <stdio.h>
#include <math.h>
#include <stdlib.h>

FILE *q;

//Métodos dos mínimos quadrados
double minQuad(double *X, double *Y, int N)
{
	double somax=0, somay=0, a0, a1, xy, x2, y2, r[N];
	int i, j;
	
	for(i=0; i<N; i++)
	{
		somax += X[i];		//somatorio de xi
		somay += Y[i];		//somatorio de yi
		xy += (X[i]*Y[i]);		//somatorio de xiyi
		x2 += pow(X[i],2);		//somatorio de xi²
		y2 += pow(Y[i],2); 		//somatorio de yi²
	}
	
	a0 = ((x2*somay) - (xy*somax)) / ((N*x2) - pow(somax,2));
	a1 = ((N*xy) - (somax*somay)) / ((N*x2) - pow(somax,2));
	
	printf("\n\t--X--\t--Y--\n");
	for(i=0; i<N; i++)
		printf("\t%.2lf\t%.2lf\n", X[i], Y[i]);
	printf("\n");
		
		
	printf("\n\t--------Coeficientes--------\n");
	printf("A0 = %lf\nA1 = %lf\n", a1, a0);
	
	q=fopen("dados1.dat", "w");
	for(i=0; i<N; i++)
	{
		r[i] = (a1*X[i] + a0);
		fprintf(q, "%.2lf\t%.2lf\t%.2lf\n ", X[i], Y[i], r[i]);
	}
	
	fclose(q);
}


double **fit(double *X, double *y, int N, int n)
{
	int i, j, m;
	double somax[2*n+1], xn, somay[n+1], **a;
	
	m=n+1;
	a=malloc(m*sizeof(double *));
	
	for(i=0; i<N; i++)
	{
		xn=1;
		for(j=0; j<2*n+1; j++)
		{
			somax[j] += xn;
			if(j<=n)
				somay[j] += xn+y[i];
			xn*=X[i];
		}
	}
	
	for(i=0; i<=n; i++)
	{
		a[i] = malloc((m+1)*sizeof(double));
		a[i][m] = somay[i];
		
		for(j=0; j<=n; j++)
			a[i][j] = somax[i+j];
	}
	
	return(a);
}

//imprimindo a matriz
void imprime(double **M, int dim)
{
	int i, j;
	
	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim; j++)
			printf("%.2lf\t", M[i][j]);
		printf("\n");
	}
}

main(int argc, char *argv[])
{
	
	double *X, *Y, **a, *r;
	int i=0, dim, N, n;
	
	//n=atoi(argv[2]);
	q=fopen(argv[1],"r");
	
	X = malloc(100*sizeof(double));
	Y = malloc(100*sizeof(double));
	
	//dim=n+1;
	//r = malloc(dim*sizeof(double));
	
	while(fscanf(q, "%lf\t%lf", &X[i], &Y[i]) != EOF)
		i++;

	N=i;
	//ajuste de curva com minimos quadrados
	minQuad(X, Y, N);
	
	/*//reallocando os vetores
	X = realloc(x, N*sizeof(*x));
	Y = realloc(y, N*sizeof(*y));
	a = fit(X,Y,N,n);
	
	imprime(a, dim);*/
	
	
	
}
