#include <stdlib.h>

int main(void)
{

    int id;
    id = fork();
    if (id == 0)
    {
        printf("Soy el hijo de %d\n", getppid());
    }
    else
    {
        printf("Soy el padre de %d\n", id);
    }

    printf("hola\n");
    exit(EXIT_SUCCESS);
}