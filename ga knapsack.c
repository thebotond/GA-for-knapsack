#include <stdio.h>
#include <stdlib.h>

typedef struct Chrom
{
	short int bit[6];
	int fit;
	int weight;
}chrom;

typedef struct Item
{
	int itemIndex;
	int weight;
	int value;
}item;

//initialisation
void *evpop(chrom popcurrent[16]);
int x(chrom popcurrent);
int y(int x);
void *pickchroms(chrom popcurrent[16]);
void *crossover(chrom popnext[16]);
void *mutation(chrom popnext[16]);
void *generateItems(item goods[6]);

int sackCapacity = 25;
int latestFitness[25];

struct Item listOfItems[6];

int main()
{	
	int maxIterations;
	int i,j;
	int store;
	int itemID, randomWeight, randomValue;
	
	int randomWeightUpper = 10;
	int randomWeightLower = 4;
	int randomValueUpper = 25;
	int randomValueLower = 10;
	int flag = 0;
	srand(time(0));
	
	for(i = 0; i < 6; i++)
	{
		itemID = i + 1;
		randomWeight = (rand() % (randomWeightUpper - randomWeightLower + 1)) + randomWeightLower;
		randomValue = (rand() % (randomValueUpper - randomValueLower + 1)) + randomValueLower;
		listOfItems[i].itemIndex = itemID;
		listOfItems[i].weight = randomWeight;
		listOfItems[i].value = randomValue;
		//listOfItems[i] = item;
		printf("\nItems:%d 	Item weight:%d		Item value:%d", listOfItems[i].itemIndex, listOfItems[i].weight, listOfItems[i].value);
	}	
	
	printf("\nPlease enter the number of iterations: ");
	scanf("%d", &maxIterations);
	chrom popcurrent[16];
	chrom popnext[16];
	evpop(popcurrent);

	
	for(i = 0; i < maxIterations; i++)
	{
		printf("\ni = %d\n", i); //print iteration count
		for(j = 0; j< 16; j++)
		{
			popnext[j] = popcurrent[j]; //create offsprings
		}
		pickchroms(popnext); //perform selection on newly created generation
		crossover(popnext); //apply crossover
		mutation(popnext); //apply mutation
		
		for(j = 0; j < 16; j++) //create new generation
		{
			popcurrent[j] = popnext[j];
		}
		store = i % 25;
		latestFitness[store] = popcurrent[0].fit;
		
		for(j = 0; j < 25; j++)
		{
			if(latestFitness[0] == latestFitness[j])
			{
				flag++;
			}
		}
		
		if(flag == 25)
		{
			printf("\nSolution found before reaching iteration limit. Solution fitness: %d. Solution weight: %d.", popcurrent[0].fit, popcurrent[0].weight);
			printf("\nTake the following: ");
			if(popcurrent[0].bit[5] == 1)
			{
					printf("\nitem 6");
			}
			if(popcurrent[0].bit[4] == 1)
			{
					printf("\nitem 5");
			}
			if(popcurrent[0].bit[3] == 1)
			{
					printf("\nitem 4");
			}
			if(popcurrent[0].bit[2] == 1)
			{
					printf("\nitem 3");
			}
			if(popcurrent[0].bit[1] == 1)
			{
					printf("\nitem 2");
			}
			if(popcurrent[0].bit[0] == 1)
			{
					printf("\nitem 1");
			}
			printf("\nNumber of iterations: %d", i + 1);			
			
			return 0;
		}
		printf("\nNumber of iterations: %d", i + 1);
		printf("\nTake the following: ");
		if(popcurrent[0].bit[5] == 1)
		{
				printf("\nitem 6");
		}
		if(popcurrent[0].bit[4] == 1)
		{
				printf("\nitem 5");
		}
		if(popcurrent[0].bit[3] == 1)
		{
				printf("\nitem 4");
		}
		if(popcurrent[0].bit[2] == 1)
		{
				printf("\nitem 3");
		}
		if(popcurrent[0].bit[1] == 1)
		{
				printf("\nitem 2");
		}
		if(popcurrent[0].bit[0] == 1)
		{
				printf("\nitem 1");
		}
	}
	return 0;
}

//create population
void *evpop(chrom popcurrent[16])
{
	int i,j;
	int random;
	int tempFit;
	int tempWeight;
	for(j = 0; j < 16; j++) //16 individuals
	{
		tempFit = 0;
		tempWeight = 0;
		for(i = 0; i < 6; i++) //6-bit random solution
		{
			random = rand();
			random = (random%2);
			popcurrent[j].bit[i] = random; //add individual to population
			if(popcurrent[j].bit[i] == 1) //if binary at i for individual j is 1, add value, weight to solution
			{
				//printf("\nWeight and value of item: %d and %d", listOfItems[i].weight, listOfItems[i].value);
				tempFit = tempFit + listOfItems[i].value;
				tempWeight = tempWeight + listOfItems[i].weight;
			}
		}
		popcurrent[j].fit = tempFit;
		popcurrent[j].weight = tempWeight;
		
		//print chromosome j
		printf("\n popcurrent[%d]=%d%d%d%d%d%d	weight=%d	fitness=%d", 
			j,
			popcurrent[j].bit[5], 
			popcurrent[j].bit[4],
			popcurrent[j].bit[3],
			popcurrent[j].bit[2],
			popcurrent[j].bit[1],
			popcurrent[j].bit[0],
			popcurrent[j].weight,
			popcurrent[j].fit);
	}
	return(0);
}


int x(chrom popcurrent)
{
	int z;
	z = (popcurrent.bit[0]*1) +
		(popcurrent.bit[1]*2) +
		(popcurrent.bit[2]*4) +
		(popcurrent.bit[3]*8) +
		(popcurrent.bit[4]*16);
		if(popcurrent.bit[5] == 1)
		{
			z = z * (-1);
		}
		return(z);
}

int y(int x)
{
	int y;
	y =- (x*x) + 5;
	return(y);
}

//selection
void *pickchroms(chrom popcurrent[16])
{
	int i, j;
	chrom temp; //temporary variable
	
	for(i = 0; i < 15; i++)
	{
		for(j = 0; j < 15; j++)
		{
			if((popcurrent[j + 1].fit > popcurrent[j].fit && (popcurrent[j + 1].weight <= sackCapacity)) || ((popcurrent[j].weight > sackCapacity && popcurrent[j + 1].weight <= sackCapacity)))
			{
				temp = popcurrent[j + 1];
				popcurrent[j + 1] = popcurrent[j];
				popcurrent[j] = temp;
			}
		}
		for(i = 0; i < 16; i++)
		{
			printf("\nSorting: popnext[%d] fitness=%d weight=%d \n", i, popcurrent[i].fit, popcurrent[i].weight);
		}
	}
	return(0);
}

//crossover
void *crossover(chrom popnext[16])
{
	printf("\nAttempting crossover");
	int i, j, k;
	int random;
	int tempFit, tempWeight;
	
	j = 0;
	k = 1;
	while(j > 16 && k > 15)
	{
		random = rand();
		random = ((random%5) + 1); //randomly select a crossing point
		
		//single point crossover - first half
		for(i = 0; i < random; i++)
		{
			//printf("\nAttempting first set");
			{
				popnext[j].bit[i] = popnext[k].bit[i];
			}

		}
		//single point crossover - second half
		for(i = random; i < 6; i++)
		{
			//printf("\nAttempting second set");
			{
				popnext[j].bit[i] = popnext[k].bit[i];
			}
		}
		j += 2;
		k += 2;
	}
	//printf("\n%d", j);
	printf("\nNew population is generated");
	
	//evaluate new population
	for(i = 0; i < 16; i++)
	{
		tempFit = 0;
		tempWeight = 0;
		for(j = 0; j < 6; j++)
		{
			if(popnext[i].bit[j] == 1)
			{
				tempFit = tempFit + listOfItems[j].value;
				tempWeight = tempWeight + listOfItems[j].weight;
			}
		}
		popnext[i].fit = tempFit;
		popnext[i].weight = tempWeight;
	}		
	
	//print result of crossover
	for(i = 0; i < 16; i++)
	{
		printf("\nCrossover popnext[%d]=%d%d%d%d%d%d 	fitness=%d	weight=%d",
			i,
			popnext[i].bit[5],
			popnext[i].bit[4],
			popnext[i].bit[3],
			popnext[i].bit[2],
			popnext[i].bit[1],
			popnext[i].bit[0],
			popnext[i].fit,
			popnext[i].weight);
	}
	return(0);
}

//mutation
void *mutation(chrom popnext[16])
{
	int i,j;
	int random;
	int row, col;
	random = rand()%50;
	
	//
	if(random == 25)
	{
		col = rand()%6;
		row = rand()%16;
		//flip the 0 or 1 at a given index in the sequence
		if(popnext[row].bit[col] == 0)
		{
			popnext[row].bit[col] = 1;
			popnext[row].fit = listOfItems[row].value + popnext[row].fit;
			popnext[row].weight = popnext[row].weight + listOfItems[row].weight;
		}
		else if(popnext[row].bit[col] == 1)
		{
			popnext[row].bit[col] = 0;
			popnext[row].fit = popnext[row].fit - listOfItems[row].value;
			popnext[row].weight = popnext[row].weight - listOfItems[row].weight;
		}
		printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    fitness=%d weight=%d",
			row,
			col,
			popnext[row].bit[5],
			popnext[row].bit[4],
			popnext[row].bit[3],
			popnext[row].bit[2],
			popnext[row].bit[1],
			popnext[row].bit[0],
			popnext[row].fit,
			popnext[row].weight);
	}
	return(0);
}