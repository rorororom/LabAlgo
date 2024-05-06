#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const int COUNT = 1000000;

    FILE *file = fopen("random_numbers.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < COUNT; i++) {
        fprintf(file, "%d\n", rand() % 1000);
    }

    fclose(file);

    return 0;
}
