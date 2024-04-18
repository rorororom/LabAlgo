#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

struct node {
    int value;
    int flag_zero;
};

struct arrHash2 {
    int A;
    int B;
    int P;
    struct node* arr;
    int size;
};

bool areCoprime(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a == 1;
}

void find(int** table, int value);


int generatePrime(int min, int max) {
    for (;;) {
        int num = rand() % (max - min + 1) + min;
        bool isPrime = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            return num;
        }
    }
}

int nearestLowerPowerOfTwo(int N) {
    int power = 1;
    while (power <= N) {
        power *= 2;
    }
    return power;
}

int generateA(int size) {
    int A;
    do {
        A = rand();
        A += (A % 2 == 0) ? 1 :  0;

    } while (!areCoprime(A, size));
    return A;
}


int main() {
    srand(time(NULL));

    int N = 0;
    scanf("%d", &N);
    bool nul = false;
    int* arr = (int*)calloc(N, sizeof(int));
    for (size_t i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        if(arr[i] == 0)
        {
            nul = true;
        }
    }

    int size = nearestLowerPowerOfTwo(N);

    int A, B, P;
    A = rand() % size;
    A = 2 * A + 1;
    B = rand() % size;
    P = rand() % size + size;
    P = 2 * P + 1;

    // printf("Obtained parameters: A = %d, B = %d, P = %d\n", A, B, P);

    struct arrHash2* hashTable = (struct arrHash2*)malloc(size * sizeof(struct arrHash2));
    assert(hashTable);

    int* collizion = (int*)calloc(size, sizeof(int));

    while (true) {
        for (int i = 0; i < N; i++) {
        int key = arr[i];
        if (key == 0)
            continue;
        int hashValue = ((A * key + B) % P + P) % P % size;
        collizion[hashValue]++;
        // printf("Hash value for key %d: %d\n", key, hashValue);
    }

        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += collizion[i] * collizion[i];
        }

//         for (int i = 0; i < size; i++) {
//             printf("%d %d\n",i,  collizion[i]);
//         }
//         printf("\n");
//
//         printf("!! %d - %d\n", sum, 4 * N);
        if (sum < 4 * N) {
            break;
        }

        for (int i = 0; i < size; i++) {
            collizion[i] = 0;
        }

        A = rand() % size;
        A = 2 * A + 1;
        B = rand() % size;
        P = rand() % size + size;
        P = 2 * P + 1;

        // printf("Obtained parameters: A = %d, B = %d, P = %d\n", A, B, P);
    }

    struct arrHash2* AAA = (struct arrHash2*)malloc(size * sizeof(struct arrHash2));
    for (int i = 0; i < size; i++) {
        AAA[i].arr = (struct node*)calloc(collizion[i], sizeof(struct node));
        AAA[i].size = 0;
    }

    for (int i = 0; i < N; i++) {
        int key = arr[i];
        if (key == 0)
            continue;
        int hashValue = ((A * key + B) % P + P) % P % size;
        AAA[hashValue].arr[AAA[hashValue].size++].value = key;
        // printf("Hash value for key %d: %d\n", key, hashValue);
    }

    // for (int i = 0; i < size; i++) {
    //     printf("%d ", i);
    //     for (int j = 0; j < AAA[i].size; j++) {
    //         printf("%d ", AAA[i].arr[j].value);
    //     }
    //     printf("\n");
    // }

    // printf(":1\n");
    for (int i = 0; i < size; i++) {
        hashTable[i].size = collizion[i] * collizion[i];
        if (hashTable[i].size == 0) {
            continue;
        }
        hashTable[i].arr = (struct node*)calloc(hashTable[i].size, sizeof(struct node));

        // do {
        //     hashTable[i].A = rand() % hashTable[i].size;
        //     hashTable[i].B = rand() % hashTable[i].size;
        //     hashTable[i].P = generatePrime(hashTable[i].size + 1, 2 * hashTable[i].size);
        // } while (!areCoprime(hashTable[i].P, hashTable[i].size) || !areCoprime(hashTable[i].A, hashTable[i].size));
        assert(hashTable[i].arr);
    }
    // printf(":2\n");

    // bool exitLoop = false;
    for (int i = 0; i < size; i++) {
        struct node* temp_arr = (struct node*)calloc(hashTable[i].size, sizeof(struct node));

        // printf("%d ", i);
        if (hashTable[i].size > 0) {
                // hashTable[i].A = rand() % hashTable[i].size;
                // hashTable[i].A += (hashTable[i].A % 2 == 0) ? 1 : 0;
                // hashTable[i].B = rand() % hashTable[i].size;
                // hashTable[i].P = generatePrime(hashTable[i].size + 1, 2 * hashTable[i].size);

                hashTable[i].A = rand() %  hashTable[i].size;
                hashTable[i].A = 2 * hashTable[i].A + 1;
                hashTable[i].B = rand() %  hashTable[i].size;
                hashTable[i].P = rand() %  hashTable[i].size +  hashTable[i].size;
                hashTable[i].P = 2 * hashTable[i].A + 1;
        }
        int A2 = hashTable[i].A, B2 = hashTable[i].B, P2 = hashTable[i].P;


        for (int qw = 0; qw < AAA[i].size; qw++) {
            // printf("qw = %d\n", qw);
            int key = AAA[i].arr[qw].value;
            if (key == 0)
                continue;

            int hashValue2 = ((A2 * key + B2) % P2 + P2) % P2 % hashTable[i].size;

            if (temp_arr[hashValue2].value != 0) {
                // do {
                    // A2 = rand() % hashTable[i].size;
                    // A2 += (A2 % 2 == 0) ? 1 : 0;
                    // B2 = rand() % hashTable[i].size;
                    // P2 = generatePrime(hashTable[i].size + 1, 2 * hashTable[i].size);

                    A2 = rand() % hashTable[i].size;
                    A2  = 2 * A2 + 1;
                    B2 = rand() % hashTable[i].size;
                    P2 = rand() % hashTable[i].size + hashTable[i].size;
                    P2 = 2 * P2 + 1;

                for (int as = 0; as < hashTable[i].size; as++) {
                    temp_arr[as].value = 0;
                    temp_arr[as].flag_zero = 0;
                }
                qw = -1;
            } else {
                temp_arr[hashValue2].value = key;
            }
        }

        hashTable[i].A = A2; hashTable[i].B = B2; hashTable[i].P = P2;
        for (int j = 0; j < hashTable[i].size; j++) {
            hashTable[i].arr[j].value = temp_arr[j].value;
            hashTable[i].arr[j].flag_zero = temp_arr[j].flag_zero;
        }

        free(temp_arr);
    }

    // for (int i = 0; i < size; i++) {
    //     printf("%d ", i);
    //     for (int j = 0; j < hashTable[i].size; j++) {
    //         printf("%d ", hashTable[i].arr[j].value);
    //     }
    //     printf("\n");
    // }

    // printf(":5\n");

    char command[10];
    scanf("%s", command);
    while (command[0] != '.') {
        int value = atoi(command);
        if(value == 0)
        {
            if(nul) printf("YES\n");
            else    printf("NO\n");
                scanf("%s", command);
            continue;
        }


        int hash1  = ((A * value + B) % P + P) % P % size;
        if (hashTable[hash1].arr == NULL) {
            printf("NO\n");
            scanf("%s", command);
            continue;
        }

        int A2 = hashTable[hash1].A, B2 = hashTable[hash1].B, P2= hashTable[hash1].P;
        int hash2 = ((A2 * value + B2) % P2 + P2) % P2 % hashTable[hash1].size;

        if (hashTable[hash1].arr[hash2].value == value )
            printf("YES\n");
        else
            printf("NO\n");

        scanf("%s", command);
    }

    return 0;
}

