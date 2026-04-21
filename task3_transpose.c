#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;
    printf("Enter N and M: ");
    scanf("%d %d", &n, &m);

    int *mat = (int *)malloc(n * m * sizeof(int));
    if (!mat) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    printf("Enter %d values (row by row): ", n * m);
    for (int i = 0; i < n * m; i++)
        scanf("%d", &mat[i]);

    int *trans = (int *)malloc(m * n * sizeof(int));
    if (!trans) {
        fprintf(stderr, "malloc failed\n");
        free(mat);
        return 1;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            trans[j * n + i] = mat[i * m + j];

    printf("Transposed matrix (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", trans[i * n + j]);
        printf("\n");
    }

    free(mat);
    free(trans);
    return 0;
}
