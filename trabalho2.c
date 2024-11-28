#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    int dia, mes, ano;
};

struct marca{
    char nome[20];
    char pais[20];
};

struct refrigerante{
	char nome[20];
	int volume;
	char apresentacao[20];
    char tipo[20];
	struct data data;
    struct marca marca;
};

void le_refri( struct refrigerante *p );
void le_data( struct data *p );
void mostra_refri( struct refrigerante p );
void mostra_data( struct data d );

int main(int argc, char *argv[]) {
   	
	struct refrigerante *refri = NULL;
	int i, op, n = 0;
	
	FILE *recibo = fopen( "refrigerantes.txt", "rt" );
	if( recibo == NULL ){
		printf("Cadastro não encontrado!\n");
	}
	else{
		fscanf( recibo, "%d", &n);
		refri = malloc( sizeof( struct refrigerante ) * n );		
		for( i = 0 ; i < n ; i++ ){
			fscanf(recibo, " %[^\n]", &refri[i].nome);
			fscanf(recibo, "%d", refri[i].volume );
			fscanf(recibo, " %[^\n]", &refri[i].apresentacao);
            fscanf(recibo, " %[^\n]", &refri[i].tipo);
			fscanf(recibo, "%d %d %d", &refri[i].data.dia, &refri[i].data.mes, &refri[i].data.ano);
            fscanf(recibo, " %[^\n] %[^\n]", &refri[i].marca.nome, &refri[i].marca.pais);
		}
		fclose ( recibo );
		printf("%d registros carregados!\n", n );
	}
	
	do{
		printf("1-Inserir\n2-Remover\n3-Mostrar\n4-Sair\n");
		scanf("%d", &op);
		switch( op ){
			case 1:
				n++;
				refri = realloc( refri, sizeof( struct refrigerante ) * n );
				le_refri( &refri[n-1] );
				break;
			
            case 2:// não sei fazer isso aqui T-T
                n--;
                printf("Qual registro você deseja remover? ");
                break;

			case 3:
				printf("\nLista de produtos:\n");
				for( i = 0 ; i < n ; i++ ){
					printf("produto %d: ", i+1 );
					mostra_refri( *(refri+i) );
				}
				break;				
		}			
	}while( op != 4 );
	
	recibo = fopen( "refrigerantes.txt", "wt" );
	fprintf( recibo, "%d\n", n);
	for( i = 0 ; i < n ; i++ ){
		fprintf(recibo, "%s\n", &refri[i].nome);
		fprintf(recibo, "%d\n", refri[i].volume );
		fprintf(recibo, "%s\n", &refri[i].apresentacao);
        fprintf(recibo, "%s\n", &refri[i].tipo);
		fprintf(recibo, "%d/%d/%d", &refri[i].data.dia, &refri[i].data.mes, &refri[i].data.ano);
        fprintf(recibo, " %s\n%s", &refri[i].marca.nome, &refri[i].marca.pais);
	}
	
	fclose ( recibo );
	
	free( refri );
	
	return 0;
}

void le_refri( struct refrigerante *p ){
	printf("Digite o nome: ");
	scanf(" %[^\n]", p->nome);
	printf("Digite o volume: ");
	scanf("%d", &(*p).volume);
	printf("Digite a apresentação: ");
	scanf(" %[^\n]", p->apresentacao);
    printf("Digite a tipo: ");
	scanf(" %[^\n]", p->tipo);
    printf("Digite a data: ");
    le_data(&p->data);
}

void le_data( struct data *p ){
	scanf("%d", &p->dia);
	printf("Digite o mes: ");
	scanf("%d", &p->mes);
	printf("Digite o ano: ");
	scanf("%d", &p->ano);
}

void mostra_refri( struct refrigerante p ){//ta dando bug pq a apresentacao aparece o tipo tbm
	printf("{%s, %d, '%s', %s, ", p.nome, p.volume, p.apresentacao, p.tipo);
	mostra_data( p.data );
	printf("}\n\n");
}

void mostra_data( struct data d ){
	printf("%d/%d/%d", d.dia, d.mes, d.ano);
}