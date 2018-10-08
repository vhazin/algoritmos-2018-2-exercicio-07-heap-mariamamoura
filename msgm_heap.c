#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct conjunto{
	char esq[10];
	int ponteiro;
}rotuloPrioridade[50000];

int tree[1<<18];
int f(struct conjunto x,struct conjunto y){
	return (strcmp(x.esq,y.esq)<0?0:1);
}

void iniciar(int node,int esq,int dir){
	if(esq==dir){
        tree[node]= esq;
        return;
    }
	iniciar(node<<1,esq,(esq+dir)/2);
	iniciar((node<<1)+1,((esq+dir)/2)+1,dir);
	if(rotuloPrioridade[tree[node<<1]].ponteiro >= rotuloPrioridade[tree[(node<<1)+1]].ponteiro)
        tree[node]=tree[node<<1];
	else tree[node]=tree[(node<<1)+1];
}

int query(int node,int n_esq,int n_dir,int q_esq,int q_dir){
	if(n_esq > q_dir || n_dir < q_esq)
        return -1;
	else if(n_esq>=q_esq && n_dir<=q_dir)
        return tree[node];
	int x = query(node<<1,n_esq,(n_esq+n_dir)/2,q_esq,q_dir);
	int y = query((node<<1)+1,((n_esq+n_dir)/2)+1,n_dir,q_esq,q_dir);
	if(x == -1)
        return y;
	else if(y == -1)
        return x;
	else if(rotuloPrioridade[x].ponteiro >= rotuloPrioridade[y].ponteiro)
        return x;
	else
        return y;
}
int testes;
void imprimir(int esq,int dir){
	int k;
	if(esq > dir)
        return;
	printf("(");
	k = query(1, 0, testes-1, esq, dir);
	work(esq, k-1);
	printf("%s/%d", rotuloPrioridade[k].esq, rotuloPrioridade[k].ponteiro);
	imprimir(k+1,dir);
	printf(")");
}

int main(){
	int i,j,l;
	char string[10];
	scanf("%i", &testes);
	while(testes){
		for(i=0; i<testes; i++){
			scanf(" %s", string);
			l = strlen(string);
			for(j=0; j<l; j++){
				if(string[j] == '/')
                    break;
				rotuloPrioridade[i].esq[j] = string[j];
			}
			rotuloPrioridade[i].esq[j] = 0;
			j++;
			rotuloPrioridade[i].ponteiro = 0;
			for(; j<l; j++)
				rotuloPrioridade[i].ponteiro = rotuloPrioridade[i].ponteiro*10+(string[j]-'0');
		}
		qsort(rotuloPrioridade, testes, sizeof(rotuloPrioridade[0]),(void *)f);
		iniciar(1,0,testes-1);
		work(0,testes-1);
		printf("\n");
		scanf("%d",&testes);
	}
	return 0;
}
