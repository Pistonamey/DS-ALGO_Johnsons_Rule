/* Name - Amey Shinde
   Student ID - 1001844387
   Command for Compilation - "gcc lab2.c"
   Command for output using the file given by Proffessor - "a.out lab2.a.dat"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct washing washer;

struct washing{
    int wTime;
    int dTime;
    int arrayToSort;
};

washer *basket;

int printOutput(int n, int jBasketWt[], int jBasketDt[], int index[]) //prints output
{
    int washSTime = 0;
    int DrySTime = jBasketWt[0];
    int Dend = DrySTime + jBasketDt[0];
    int makespan;
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d %d %d %d %d\n", index[i], jBasketWt[i], jBasketDt[i], washSTime, DrySTime);
        washSTime = washSTime + jBasketWt[i];
        if ((washSTime + jBasketWt[i + 1]) < (DrySTime + jBasketDt[i]))
            DrySTime = DrySTime + jBasketDt[i];
        else
            DrySTime = washSTime + jBasketWt[i + 1];
        if (Dend < DrySTime && i < (n - 1))
        {
            printf("Gap time from %d to %d\n", Dend, DrySTime);
        }
        if (i < (n - 1))
            Dend = DrySTime + jBasketDt[i + 1];
    }

    printf("Makespan is : %d\n", Dend);

    return 0;
}

int johnsonRule(int n, int washtime[], int drytime[])
{
    int p = n - 1, o = 0, k = 0;
    int jBasketWt[n];
    int jBasketDt[n];
    int index[n];
    int i;
    int j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (basket[i].arrayToSort == washtime[j])
            {

                jBasketWt[o] = washtime[j];
                jBasketDt[o] = drytime[j];
                index[o] = j;
                o++;
                k++;
            }
            if (basket[i].arrayToSort == drytime[j])
            {

                jBasketWt[p] = washtime[j];
                jBasketDt[p] = drytime[j];
                index[p] = j;
                p--;
                k++;
            }
        }
    }

    printOutput(n, jBasketWt, jBasketDt, index);
    return 0;
}

int numCompare(x, y)
    washer *x,
    *y;
{
    return x->arrayToSort - y->arrayToSort;
}

int theQSort(int n, int washtime[], int drytime[]) // function performs qsort
{
    int sortedBaskets[n];
    int k = 0;
    int nwashtime[n];
    int ndrytime[n];
    int i;
    int j;
    qsort((void *)basket, n, sizeof(washer), numCompare);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (basket[i].arrayToSort == washtime[j] || basket[i].arrayToSort == drytime[j])
            {
                nwashtime[k] = washtime[j];
                ndrytime[k] = drytime[j];
                k++;
            }
        }
    }

    johnsonRule(n, washtime, drytime);
    return 0;
}

int arrayOfSort(int n, int washtime[], int drytime[]) // finds minimum of two times and stores in array
{
    //int arrayToSort[n];
    int i;
    int x = n;
    for (i = 0; i < n; i++)
    {
        if (basket[i].wTime < basket[i].dTime)
        {
            basket[i].arrayToSort = basket[i].wTime;
        }
        else
        {
            basket[i].arrayToSort = basket[i].dTime;
        }
    }

    theQSort(n, washtime, drytime);
    return 0;
}

int acceptTimes(int nBaskets, FILE *fp) // accept the times
{
    int n = nBaskets;
    int washtime[n];
    int drytime[n];
    int i;
    basket = (washer *)malloc(n * sizeof(washer));
    if (!basket)
    {
        printf("malloc fail\n");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &basket[i].wTime);
        washtime[i] = basket[i].wTime;
        fscanf(fp, "%d", &basket[i].dTime);
        drytime[i] = basket[i].dTime;
    }

    arrayOfSort(n, washtime, drytime);
    return 0;
}

int noOfBaskets(FILE *fp) //find the number of baskets
{
    int nBaskets;
    fscanf(fp, "%d", &nBaskets);

    acceptTimes(nBaskets, fp);

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    noOfBaskets(fp);

    fclose(fp);

    return 0;
}
