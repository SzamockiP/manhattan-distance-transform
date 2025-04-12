#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 64 * 8

void manhattan_distance_transform(const char *inArr, int *outArr, int arrSize) {
    int total = arrSize * arrSize;
    // Ustawiamy wartość nieskończoności – tutaj maksymalna odległość
    int INF = arrSize * arrSize;

    // Inicjalizacja tablicy wyjściowej – wyzerujemy, czyli wstawimy wartość INF do wszystkich pozycji.
    for (int i = 0; i < total; i++) {
        outArr[i] = INF;
    }

    // Forward pass: skanowanie od top-left do bottom-right
    for (int i = 0; i < arrSize; i++) {
        int rowOffset = i * arrSize;
        for (int j = 0; j < arrSize; j++) {
            int idx = rowOffset + j;

            // Jeżeli jesteśmy na krawędzi z góry lub z lewej, dla rozpoczęcia możemy
            // ewentualnie ustalić odległość 0, jeśli chcemy traktować takie pozycje jako "wewnętrzne"
            // ale w naszym przypadku warunek krawędzi definiujemy poprzez różnicę z sąsiadem.
            // Dlatego sprawdzamy sąsiadów i ustawiamy odległość = 1, gdy występuje różnica.

            // Sprawdzenie górnego sąsiada
            if (i > 0) {
                int topIdx = idx - arrSize;
                if (inArr[topIdx] != inArr[idx]) {
                    outArr[idx] = 1;
                } else {
                    // Propagacja wartości z góry
                    int candidate = outArr[topIdx] + 1;
                    if (candidate < outArr[idx])
                        outArr[idx] = candidate;
                }
            }

            // Sprawdzenie lewego sąsiada
            if (j > 0) {
                int leftIdx = idx - 1;
                if (inArr[leftIdx] != inArr[idx]) {
                    if (1 < outArr[idx])
                        outArr[idx] = 1;
                } else {
                    int candidate = outArr[leftIdx] + 1;
                    if (candidate < outArr[idx])
                        outArr[idx] = candidate;
                }
            }
        }
    }

    // Backward pass: skanowanie od bottom-right do top-left
    for (int i = arrSize - 1; i >= 0; i--) {
        int rowOffset = i * arrSize;
        for (int j = arrSize - 1; j >= 0; j--) {
            int idx = rowOffset + j;

            // Sprawdzenie dolnego sąsiada
            if (i < arrSize - 1) {
                int bottomIdx = idx + arrSize;
                if (inArr[bottomIdx] != inArr[idx]) {
                    if (1 < outArr[idx])
                        outArr[idx] = 1;
                } else {
                    int candidate = outArr[bottomIdx] + 1;
                    if (candidate < outArr[idx])
                        outArr[idx] = candidate;
                }
            }

            // Sprawdzenie prawego sąsiada
            if (j < arrSize - 1) {
                int rightIdx = idx + 1;
                if (inArr[rightIdx] != inArr[idx]) {
                    if (1 < outArr[idx])
                        outArr[idx] = 1;
                } else {
                    int candidate = outArr[rightIdx] + 1;
                    if (candidate < outArr[idx])
                        outArr[idx] = candidate;
                }
            }
        }
    }
}


#define INF 1000000
#define MAX_ITER 1000
void distance_transform_jacobi(const char *inArr, int *oldArr, int *newArr, int arrSize) {
    int changed = 1;
    int iter = 0;
    
    while(changed && iter < MAX_ITER) {
        changed = 0;
        // Paralelizujemy całą tablicę – każdy element aktualizowany jest na podstawie stanu z poprzedniej iteracji.
        // #pragma omp parallel for collapse(2)
        for (int i = 0; i < arrSize; i++) {
            for (int j = 0; j < arrSize; j++) {
                int idx = i * arrSize + j;
                int current = oldArr[idx];
                int candidate = current; // początkowo brak zmian
                // Sprawdzenie czterech sąsiadów:
                // Góra
                if (i > 0) {
                    int val = oldArr[(i-1)*arrSize + j] + 1;
                    if(val < candidate)
                        candidate = val;
                }
                // Lewo
                if (j > 0) {
                    int val = oldArr[i*arrSize + j - 1] + 1;
                    if(val < candidate)
                        candidate = val;
                }
                // Dół
                if (i < arrSize - 1) {
                    int val = oldArr[(i+1)*arrSize + j] + 1;
                    if(val < candidate)
                        candidate = val;
                }
                // Prawo
                if (j < arrSize - 1) {
                    int val = oldArr[i*arrSize + j + 1] + 1;
                    if(val < candidate)
                        candidate = val;
                }
                // Dodatkowo możemy wprowadzić warunki, jeśli chcemy brać pod uwagę różnicę w inArr
                if (inArr[idx] != '1') {  // przykładowy warunek – dowolna logika zależna od typu
                    candidate = 1;
                }
                newArr[idx] = candidate;
                if (candidate != current) {
                    // #pragma omp atomic write
                    changed = 1;
                }
            }
        }
        // Zamieniamy bufor
        int *temp = oldArr;
        oldArr = newArr;
        newArr = temp;
        iter++;
    }
}


void skurwialy_distance_transform(const char *inArr, int *outArr, int arrSize){
    int i, j, idx;

    // Iteracja 1: inicjalizacja – oznaczanie granic
    // Granica: komórka ma przynajmniej jednego sąsiada (góra, dół, lewo, prawo) o innej wartości
    for(i = 0; i < arrSize; i++) {
        for(j = 0; j < arrSize; j++) {
            idx = i * arrSize + j;
            int boundary = 0;
            // Sprawdzenie góry
            if(i > 0 && inArr[idx - arrSize] != inArr[idx])
                boundary = 1;
            // Sprawdzenie dołu
            if(i < arrSize - 1 && inArr[idx + arrSize] != inArr[idx])
                boundary = 1;
            // Sprawdzenie lewej
            if(j > 0 && inArr[idx - 1] != inArr[idx])
                boundary = 1;
            // Sprawdzenie prawej
            if(j < arrSize - 1 && inArr[idx + 1] != inArr[idx])
                boundary = 1;

            outArr[idx] = boundary ? 1 : INF;
        }
    }

    // Iteracja 2: skanowanie od góry do dołu
    for(i = 1; i < arrSize; i++) {
        for(j = 0; j < arrSize; j++) {
            idx = i * arrSize + j;
            int topIdx = (i - 1) * arrSize + j;
            if(outArr[topIdx] + 1 < outArr[idx])
                outArr[idx] = outArr[topIdx] + 1;
        }
    }

    // Iteracja 3: skanowanie od lewej do prawej
    for(i = 0; i < arrSize; i++) {
        for(j = 1; j < arrSize; j++) {
            idx = i * arrSize + j;
            int leftIdx = i * arrSize + (j - 1);
            if(outArr[leftIdx] + 1 < outArr[idx])
                outArr[idx] = outArr[leftIdx] + 1;
        }
    }

    // Iteracja 4: skanowanie od dołu do góry
    for(i = arrSize - 2; i >= 0; i--) {
        for(j = 0; j < arrSize; j++) {
            idx = i * arrSize + j;
            int bottomIdx = (i + 1) * arrSize + j;
            if(outArr[bottomIdx] + 1 < outArr[idx])
                outArr[idx] = outArr[bottomIdx] + 1;
        }
    }

    // Iteracja 5: skanowanie od prawej do lewej
    for(i = 0; i < arrSize; i++) {
        for(j = arrSize - 2; j >= 0; j--) {
            idx = i * arrSize + j;
            int rightIdx = i * arrSize + (j + 1);
            if(outArr[rightIdx] + 1 < outArr[idx])
                outArr[idx] = outArr[rightIdx] + 1;
        }
    }
}

int main(void){
    // ======================== JACOBI ====================================
    // const int arrSize = 5;
    // const int total = arrSize * arrSize;
    // char inArr[25] = {
    //     '1','1','1','1','1',
    //     '1','1','1','1','0',
    //     '1','1','1','0','0',
    //     '1','1','0','0','0',
    //     '1','0','0','0','0'
    // };
    // // Inicjalizacja buforów – początkowo ustawiamy INF, a krawędzie (gdzie np. sąsiedź różny) wartością 1
    // int *oldArr = (int*) malloc(total * sizeof(int));
    // int *newArr = (int*) malloc(total * sizeof(int));
    // for (int i = 0; i < total; i++) {
    //     oldArr[i] = INF;
    //     newArr[i] = INF;
    // }
    // // Możesz zainicjalizować krawędzie zgodnie z Twoją logiką – tutaj uproszczony przykład:
    // // Na przykład: jeśli sąsiad różni się, ustawiamy INF na 1
    // // (możesz to zrobić też w osobnej pętli przed iteracjami)

    // // Uruchamiamy transformację
    // distance_transform_jacobi(inArr, oldArr, newArr, arrSize);

    // // Wyświetlamy wynik (pamiętaj, że końcowy wynik może być w oldArr lub newArr zależnie od iteracji)
    // for (int i = 0; i < arrSize; i++) {
    //     for (int j = 0; j < arrSize; j++) {
    //         printf("%d ", oldArr[i * arrSize + j]);
    //     }
    //     printf("\n");
    // }
    
    // free(oldArr);
    // free(newArr);
    // return 0;
    // ======================== JACOBI ====================================

    // ======================== CHAT ====================================
    
    double sum_mannhattan = 0;
    double sum_skurwialy = 0;
    
    for(int i = 0; i < 10; i++){
        char *arr2d = malloc(ARRAY_SIZE * ARRAY_SIZE * sizeof(char));
        int *out2d = malloc(ARRAY_SIZE * ARRAY_SIZE * sizeof(int));
        // int *out2d = calloc(ARRAY_SIZE * ARRAY_SIZE,sizeof(int));

        for(int i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++){
            arr2d[i] = 'a';
            out2d[i] = 0;
        }
        arr2d[12] = 'A';

        clock_t begin = clock();
        skurwialy_distance_transform(arr2d, out2d, ARRAY_SIZE);
        clock_t end = clock();
        sum_skurwialy += (double)(end - begin) / CLOCKS_PER_SEC;

        free(arr2d);
        free(out2d);
    }

    for(int i = 0; i < 10; i++){
        char *arr2d = malloc(ARRAY_SIZE * ARRAY_SIZE * sizeof(char));
        int *out2d = malloc(ARRAY_SIZE * ARRAY_SIZE * sizeof(int));
        // int *out2d = calloc(ARRAY_SIZE * ARRAY_SIZE,sizeof(int));

        for(int i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++){
            arr2d[i] = 'a';
            out2d[i] = 0;
        }
        arr2d[12] = 'A';

        clock_t begin = clock();
        manhattan_distance_transform(arr2d, out2d, ARRAY_SIZE);
        clock_t end = clock();
        sum_mannhattan += (double)(end - begin) / CLOCKS_PER_SEC;

        free(arr2d);
        free(out2d);
    }

    printf("Skurwialy: %f\nManhattan: %f\n", sum_skurwialy/10, sum_mannhattan/10);
    

    return 0;
}