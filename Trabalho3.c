#include <stdio.h>
#include <stdlib.h>

int main()
{
        int i,j = 0,N,Pi[1000000],Q,k,avail,count = 0;
		int contq[1000], x = 0, y = 0;
		int page_faults[1000], z = 0;

        scanf("%d",&N);

        for(i = 1;i <= N;i++)
            scanf("%d",&Pi[i]);

        while(scanf("%d",&Q) != EOF){
			contq[x] = Q;
			x++;

        	int quadro[10000];

			for(k = 0; k < Q; k++)
				quadro[Q] = 0;

			for(i = 1; i <= N; i++){
				avail = 0;
				for(k = 0; k < Q; k++){
					if(quadro[k] == Pi[i]){
						avail = 1;
					}
				}

				if(avail == 0){
					quadro[j] = Pi[i];
					j = (j+1)%Q;
					count++;
				}
			}
			printf("%d\n", count);
			page_faults[z] = 0;
			page_faults[z] = count;
			printf("page_faults[%d] = %d\n", z, page_faults[z]);
			z++;
			count = 0;
		}
		for(y = 0; y < x; y++){
			printf("%d %d\n",contq[y], page_faults[y]);
		}
		z = 1;
		if(page_faults[z] > page_faults[z-1]){
			printf("Belady detectado\n");
		}else{
			printf("Sem anomalia\n");
		}
        return 0;
}
