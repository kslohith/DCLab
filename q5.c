#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

double** points;
int cluster_count[4];
int cluster[4][2] = { {0,0} , {25,25} , {50,50} , {75,75} };

void populate_points(int size)
{
    points = (double*) malloc(size * sizeof(double));
    for(int i = 0; i < size; i++ )
    {
        points[i] = (double*) malloc(2 * sizeof(double));
    }

    for(int i = 0; i < size; i++ )
    {
        points[i][0] = rand()%100;
        points[i][1] = rand()%100;
    }
    printf("Generated points are\n");
    for(int j = 0; j < size; j++ )
    {
        printf("%f %f\n",points[j][0],points[j][1]);
    }
    for(int k = 0; k < 4; k++ )
    {
        cluster_count[k] = 0;
    }
}

double getdistance(double x1 , double y1 , double x2 , double y2 )
{
    double dx = (x2-x1);
    double dy = (y2-y1);

    return (double) sqrt(dx*dx + dy*dy);
}

void classify_points(int size)
{

    #pragma omp parallel for num_threads(8)
    for(int i = 0; i < size; i++)
    {
        double cur_dis = 0.0;
        double min_dis = 999.0;
        int cluster_index = 0;
        for(int j = 0; j < 4; j++ )
        {
            cur_dis = getdistance(points[i][0],points[i][1],cluster[j][0],cluster[j][1]);
            if( cur_dis < min_dis )
            {
                min_dis = cur_dis;
                cluster_index = j;
            }
        }
        printf("Point (%f,%f) belongs to cluster %d\n",points[i][0],points[i][1],cluster_index);
    }
}

void classify_points_noparallel(int size)
{


    for(int i = 0; i < size; i++)
    {
        double cur_dis = 0.0;
        double min_dis = 999.0;
        int cluster_index = 0;
        for(int j = 0; j < 4; j++ )
        {
            cur_dis = getdistance(points[i][0],points[i][1],cluster[j][0],cluster[j][1]);
            if( cur_dis < min_dis )
            {
                min_dis = cur_dis;
                cluster_index = j;
            }
        }
        printf("Point (%f,%f) belongs to cluster %d\n",points[i][0],points[i][1],cluster_index);
    }
}


void main()
{
    int n = 0;
    printf("Enter the number for points for classification\n");
    scanf("%d",&n);
    populate_points(n);
    double t1 = omp_get_wtime();
    classify_points(n);
    double t2 = omp_get_wtime();
    printf("Total time taken for parallel classification is %f",(t2-t1));
    double t11 = omp_get_wtime();
    classify_points_noparallel(n);
    double t22 = omp_get_wtime();
    printf("Total time taken for sequential classification is %f",(t22-t11));
}
