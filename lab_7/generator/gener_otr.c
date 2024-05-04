#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int start;
    int end;
} Segment;

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

Segment generateSegment(int min, int max) {
    Segment segment;
    segment.start = randomInRange(min, max - 1);
    segment.end = randomInRange(segment.start + 1, max);
    return segment;
}

int main() {
    srand(time(NULL));

    const int MAX_SEGMENTS = 1000000;
    const int ARRAY_SIZE = 1000000;

    printf("Сгенерированные невырожденные отрезки:\n");
    for (int i = 0; i < MAX_SEGMENTS; i++) {
        Segment segment = generateSegment(0, ARRAY_SIZE);
        printf("%d %d\n", segment.start, segment.end);
    }

    return 0;
}
