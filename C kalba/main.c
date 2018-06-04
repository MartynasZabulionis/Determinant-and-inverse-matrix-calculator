#include <stdio.h>
#include <stdlib.h>

#define xor(a, b)               !a != !b

#define SetBit(a, b)            a |= (1<<b)
#define ResetBit(a, b)          a &= ~(1<<b)
#define InverseBit(a, b)        a ^= (1<<b)
#define GetBit(a, b)            (a & (1<<b))


double get_det(double **m, int size)
{
        if (size < 2)
                return 0;

        if (size == 2)
                return m[0][0] * m[1][1] - m[1][0] * m[0][1];

        int i, j, k, l;
        double n, det = 1;

        for (i = 0; i < size - 1; i++)
        {
                k = i;
                while (m[k++][i] == 0)
                {
                        if (k == size)
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
        return det * m[size - 1][size - 1];
}
int main()
{
        srand(time(NULL));
        int i, j, k, size = 4000;
        double **m;
        printf("Atvirkstines matricos skaiciavimas.\nDydis: ");
        scanf("%d", &size);
        printf("Iveskite dabar skaicius eilutemis.\n");

        m = malloc(sizeof(double*) * size);

        for (i = 0; i < size; i++)
        {
                *(m + i) = malloc(sizeof(double) * size);
                for (j = 0; j < size; j++)
                        scanf("%Lf", *(m + i) + j);
                        //m[i][j] = rand() % 2;
        }
        printf("Determinantas: %g", get_det(m, size));
}

