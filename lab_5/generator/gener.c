#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void generate_random_unsigned_int(int limit, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", rand() % (limit + 1));
    }
}

void generate_random_float(float limit, int size) {
    for (int i = 0; i < size; i++) {
        float random_number = ((float)rand() / (float)RAND_MAX) * (2 * limit) - limit;
        printf("%f\n", random_number);
    }
}


void generate_random_string(int size) {
    for (int i = 0; i < size; i++) {
        int length = rand() % 16 + 5;
        for (int j = 0; j < length; j++) {
            printf("%c", 'a' + rand() % 26);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    srand(42);
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <size> <limit> <type>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int limit = atoi(argv[2]);
    int type = atoi(argv[3]);

    if (size < 0 || limit < 0 || type < 0) {
        printf("Numbers should be positive!\n");
        return 1;
    }

    switch (type) {
        case 0:
            generate_random_unsigned_int(limit, size);
            break;
        case 1:
            generate_random_string(size);
            break;
        case 2:
            generate_random_float(limit, size);
            break;
        default:
            printf("Invalid type!\n");
            return 1;
    }
    return 0;
}
