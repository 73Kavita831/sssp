#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 9999

void dijkstra(int**,int,int);
int input_array[1000];
int length_of_input=0;
int read_ints (const char* file_name)
{
  FILE* file = fopen (file_name, "r");
  int i = 0;

  fscanf (file, "%d", &i);
  while (!feof (file))
    {
      input_array[length_of_input]=i;
      length_of_input++;
      fscanf (file, "%d", &i);
    }
   fclose (file);
}


int main(int argc, char *argv[])
{
if(argc < 3)
{
printf("compile : gcc sssp.c -o sssp\n");
printf("run : ./sssp <Path to file> <Node Name>\n");
return(1);
}
	read_ints(argv[1]);
  int Node = atoi(argv[2]);
  Node = Node-1; // Since vertex 2 would be stored as 1 in Adjacency Matrix

	int Vertices = input_array[0];
	int Edges = input_array[1];
  if (Node > Vertices)
  {
    printf("The Given Node must be one of the Vertices of the Graph \n");
    return(1);
  }

  int **Graph = (int **)malloc(Vertices * sizeof(int *));
	for (int i=0; i<Vertices; i++)
         	Graph[i] = (int *)malloc(Vertices * sizeof(int));

        for(int z=0;z<Vertices;z++)
        {
                for(int y=0;y<Vertices;y++)
                Graph[z][y] = 0;
        }

	for(int temp1 = 2;temp1 < 2+2*Vertices ;temp1 = temp1+2)
	{
	int source = input_array[temp1];
	int dest  = input_array[temp1];
	int cost = input_array[temp1+1];
	Graph[source-1][dest-1]=cost;

	}
	for(int temp2 = 2+2*Vertices;temp2 < length_of_input;temp2 = temp2+3)
	{
	int source=input_array[temp2];
	int dest=input_array[temp2+1];
	int cost=input_array[temp2+2];
	Graph[source-1][dest-1]=cost;
	}
	printf("Graph is : \n ");
	for(int z=0;z<Vertices;z++)
	{
		for(int y=0;y<Vertices;y++)
		{ printf("%d ",Graph[z][y]);
	}
	printf("\n");
	}
  dijkstra(Graph,Vertices,Node);
	return 0;
}

void dijkstra(int **G, int n, int startnode)
{
  	int cost[n][n], distance[n], pred[n];
  	int visited[n], count, mindistance, nextnode, i,j;
  	for(i=0;i < n;i++)
  		for(j=0;j < n;j++)
  			if(G[i][j]==0)
  				cost[i][j]=INFINITY;
  			else
  				cost[i][j]=G[i][j];

  	for(i=0;i< n;i++)
  	{
  		distance[i]=cost[startnode][i];
  		pred[i]=startnode;
  		visited[i]=0;
  	}
  	distance[startnode]=0;
  	visited[startnode]=1;
  	count=1;
  	while(count < n-1){
  		mindistance=INFINITY;
  		for(i=0;i < n;i++)
  			if(distance[i] < mindistance&&!visited[i])
  			{
  				mindistance=distance[i];
  				nextnode=i;
  			}
  		visited[nextnode]=1;
  		for(i=0;i < n;i++)
  			if(!visited[i])
  				if(mindistance+cost[nextnode][i] < distance[i])
  				{
  					distance[i]=mindistance+cost[nextnode][i];
  					pred[i]=nextnode;
  				}
  			count++;
  	}

  	for(i=0;i < n;i++)
  		if(i!=startnode)
  		{
  			printf("\nDistance of %d = %d", i, distance[i]);
  			printf("\nPath = %d", i);
  			j=i;
  			do
  			{
  				j=pred[j];
  				printf(" <-%d", j);
  			}
  			while(j!=startnode);
  		}
  }
