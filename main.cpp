#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void free_matrix(double **m, int size)
{
        for (int i = 0; i < size; i++)
                free(*(m + i));
        free(m);
}
double get_inv_matrix(double **m, int size, double **mm)
{
        if (size < 2)
                return 0;

        int i, j, k, l;
        double n, det = 1;// **m;

        //m = (double**) malloc(sizeof(double*) * size);
        for (i = 0; i < size; i++)
        {
                mm[i][i] = 1;
                /**(m + i) = (double*) malloc(sizeof(double) * size);
                for (j = 0; j < size; j++)
                        m[i][j] = r[i][j];*/
        }

        for (i = 0; i < size - 1; i++)
        {
                k = i;
                while (m[k++][i] == 0)
                        if (k == size)
                        {
                                //free_matrix(m, size);
                                return 0;
                        }

                if (--k > i)
                {
                        for (j = 0; j < size; j++)
                        {
                                n = m[k][j];
                                m[k][j] = -m[i][j];
                                m[i][j] = n;

                                n = mm[k][j];
                                mm[k][j] = -mm[i][j];
                                mm[i][j] = n;
                        }
                }
                for (j = k + 1; j < size; j++)
                {
                        if (m[j][i] == 0)
                                continue;

                        n = m[j][i] / m[i][i];
                        for (l = 0; l < size; l++)
                        {
                                m[j][l] -= m[i][l] * n;
                                mm[j][l] -= mm[i][l] * n;
                        }
                }
                det *= m[i][i];
        }
        if (det *= m[size - 1][size - 1] == 0.0)
        {
                //free_matrix(m, size);
                return 0;
        }
        for (i = size - 1; i > 0; i--)
        {
                for (j = i - 1; j >= 0; j--)
                {
                        if (m[j][i] == 0)
                                continue;

                        n = m[j][i] / m[i][i];
                        for (l = size - 1; l >= 0; l--)
                                mm[j][l] -= mm[i][l] * n;
                }
        }
        for (i = 0; i < size; i++)
        {
                for (j = 0; j < size; j++)
                        mm[i][j] /= m[i][i];
        }
        //free_matrix(m, size);
        return det;
}

double get_det(double **r, int size)
{
        if (size < 2)
                return 0;

        if (size == 2)
                return r[0][0] * r[1][1] - r[1][0] * r[0][1];

        int i, j, k, l;
        double n, det = 1, **m;
        m = (double**) malloc(sizeof(double*) * size);
        for (i = 0; i < size; i++)
        {
                *(m + i) = (double*) malloc(sizeof(double) * size);
                for (j = 0; j < size; j++)
                        m[i][j] = r[i][j];
        }

        for (i = 0; i < size - 1; i++)
        {
                k = i;
                while (m[k++][i] == 0)
                        if (k == size)
                        {
                                free_matrix(m, size);
                                return 0;
                        }

                if (--k > i)
                {
                        for (j = i; j < size; j++)
                        {
                                n = m[k][j];
                                m[k][j] = -m[i][j];
                                m[i][j] = n;
                        }
                }
                for (j = k + 1; j < size; j++)
                {
                        if (m[j][i] == 0)
                                continue;

                        n = m[j][i] / m[i][i];
                        for (l = i + 1; l < size; l++)
                                m[j][l] -= m[i][l] * n;
                }
                det *= m[i][i];
        }
        det *= m[size - 1][size - 1];
        free_matrix(m, size);
        if (det == 0)
                return 0;
        return det;
}
int main()
{
        int i, j, size = 4;
        double **m, **mm/*, **r*/;

        printf("Determinanto ir atvirkstines matricos skaiciavimas.\nDydis (n x n): ");
        scanf("%d", &size);
        printf("Iveskite dabar skaicius eilutemis.\n");

        m =  (double**) malloc(sizeof(double*) * size);
        mm = (double**) malloc(sizeof(double*) * size);
        //r = (double**) malloc(sizeof(double*) * size);
        for (i = 0; i < size; i++)
        {
                *(m + i) =      (double*) malloc(sizeof(double) * size);
                *(mm + i) =     (double*) calloc(size, sizeof(double));
                //*(r + i) =      (double*) calloc(size, sizeof(double));
        }

        for (i = 0; i < size; i++)
        {
                for (j = 0; j < size; j++)
                {
                        mm[i][j] = /*r[i][j] = */0;
                        scanf("%lf", *(m + i) + j);
                }
        }
        double det = get_det(m, size);
        if (det == 0)
        {
                printf("\nDeterminantas: %G\n\nAtvirkstines matricos nera.\n", get_det(m, size));
                return 0;
        }
        printf("\nDeterminantas: %G\n\nAtvirkstine matrica:\n", get_det(m, size));
        get_inv_matrix(m, size, mm);
        //get_inv_matrix(mm, size, r);
        for (i = 0; i < size; i++)
        {
                printf("\n");
                for (j = 0; j < size; j++)
                        printf("%12.6G ", mm[i][j]);
        }

        printf("\n");
        free_matrix(m, size);
        free_matrix(mm, size);
        return 0;
}
