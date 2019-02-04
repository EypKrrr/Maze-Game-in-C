//Eyup KORURER 06.12.2017
//GNU GCC compiler ile derlenmiþtir.



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matris[45][45];
int boyut=0;

struct solucion
{
    int row;
    int column;
    struct solucion *next;
};
int control(int row, int column, int size)
{
    if(matris[row-1][column-1])
    {
    if(row==1 || row==size)
        if(column>0 && column<=size)
            return 1;
        else return 0;
    else if(column==1 || column==size)
        if(row>0 && row<=size)
            return 1;
        else return 0;
    else return 0;
    }else
    return 0;
}

struct solucion* push(struct solucion *iter,int a,int b)
{
    struct solucion *temp;
    temp=malloc(sizeof(struct solucion));
    iter->next=temp;
    temp->row=a;
    temp->column=b;
    temp->next=NULL;
    matris[a][b]=2;
    boyut++;
    return temp;
}

struct solucion* pop(struct solucion *iter)
{
    if(boyut>1)
    {
        if(boyut>2)
        {
            while(iter->next->next!=NULL)
            {
                iter=iter->next;
            }
        }
        matris[iter->next->row][iter->next->column]=0;
        iter->next=NULL;
        free(iter->next);
        boyut--;
    }
    return iter;
}

struct solucion* solvent(int s_row,int s_column,int f_row,int f_column,int size)
{
    struct solucion *root;
    struct solucion *iter;
    struct solucion *back;
    root=malloc(sizeof(struct solucion));
    iter=root;
    iter->row=s_row;
    iter->column=s_column;
    matris[s_row][s_column]=2;
    iter->next=NULL;
    boyut++;   //E?er kuyruktaysa 2 atanabilir.
    while(1)
    {
        back=root;
        if(boyut==1)
        {
            back=NULL;
        }
        else if(boyut==3)
        {
            back=root->next;
        }
        else if(boyut >3)
        {
            do
            {
                back=back->next;
            }
            while(back->next->next==NULL);
        }

        if(iter->row==f_row && iter->column==f_column)
        {
            break;
        }
        else if(iter->column!=size-1 && matris[iter->row][iter->column+1]==1 )
        {
            if(back==NULL)
            {
                iter=push(iter,iter->row,iter->column+1);
            }
            else if(iter->row!=back->row || iter->column+1!=back->column)
            {
                iter=push(iter,iter->row,iter->column+1);
            }
        }
        else if(iter->row!=size-1 && matris[iter->row+1][iter->column]==1 )
        {
            if(back==NULL)
            {
                iter=push(iter,iter->row+1,iter->column);
            }
            else if(iter->row+1!=back->row || iter->column!=back->column)
            {
                iter=push(iter,iter->row+1,iter->column);
            }
        }
        else if(iter->column!=0 && matris[iter->row][iter->column-1]==1 )
        {
            if(back==NULL)
            {
                iter=push(iter,iter->row,iter->column-1);
            }
            else if(iter->row!=back->row || iter->column-1!=back->column)
            {
                iter=push(iter,iter->row,iter->column-1);
            }
        }
        else if(iter->row!=0 && matris[iter->row-1][iter->column]==1 )
        {
            if(back==NULL)
            {
                iter=push(iter,iter->row-1,iter->column);
            }
            else if(iter->row-1!=back->row || iter->column!=back->column)
            {
                iter=push(iter,iter->row-1,iter->column);
            }
        }
        else if(iter->row==s_row && iter->column==s_column)
        {
            return NULL;
        }
        else
        {
            iter=pop(root);
        }
    }
    return root;
}

void print (int size)
{
    int i,j;
    printf("    ");
    for(i=1;i<=size;i++)
    {
        printf("%-3d ",i);
    }
    printf("\n");
    for(i=0; i<size; i++)
    {
        printf(" %-3d",i+1);
        for(j=0; j<size; j++)
        {
            if(matris[i][j]==0)
            {
                printf("%c%c%c%c",178,178,178,178);
            }
            if(matris[i][j]==1)
            {
                printf("%c%c%c%c",176,176,176,176);
            }
            if(matris[i][j]==2)
            {
                printf("%c%c%c%c",177,177,177,177);
            }
        }
        printf("\n    ");
        for(j=0; j<size; j++)
        {
            if(matris[i][j]==0)
            {
                printf("%c%c%c%c",178,178,178,178);
            }
            if(matris[i][j]==1)
            {
                printf("%c%c%c%c",176,176,176,176);
            }
            if(matris[i][j]==2)
            {
                printf("%c%c%c%c",177,177,177,177);
            }
        }
        printf(" %d\n",i+1);
    }
    printf("    ");
    for(i=1;i<=size;i++)
    {
        printf("%-3d ",i);
    }
}

int main()
{
    int size,i,j;
    int s_row, s_column, f_row, f_column;
    do
    {
        printf("Please, enter the maze size:"); //kullanycydan labirent boyutu alma
        scanf("%d",&size);
    }
    while(size<=0 || size>45);
    int M[size][size];
    printf("\n");
    srand(time(NULL));
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            M[i][j]=rand()%2;
            matris[i][j]=M[i][j];
        }
    }
    print(size);
    do
    {
        printf("\n\nPlease, enter the start row and  start column:");
        scanf("%d%d",&s_row,&s_column);
    }
    while(control(s_row, s_column, size)==0);
    do
    {
        printf("Please, enter the finish row and finish column:");
        scanf("%d%d",&f_row,&f_column);
    }
    while(control(f_row, f_column, size)==0);
    s_row--;
    s_column--;
    f_row--;
    f_column--;
    struct solucion *root;
    printf("\n\n");
    root=solvent(s_row,s_column,f_row,f_column,size);
    if(root==NULL)
    {
        printf("\aCozum yoktur!!!\n");
    }
    else
    {
        while(root->next==NULL)
        {
            matris[root->row][root->column]=2;
            root=root->next;
        }
           print(size);
    }

    return 0;
}
