#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#undef main

// swap(arr, idx1, idx2) swaps the values at the idexes in arr
// effect: mutates arr
void swap(int arr[], int idx1, int idx2){
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

// get_max(arr, len) finds the greatest number in arr
int get_max(int arr[], int len){
    assert(len > 0);
    int max = arr[0];
    for (int i = 0; i < len; i++){
        if (arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

// get_last(num, unit) gets the digit from the index unit where the tens are at unit 0
int get_last(int num, int unit){
    for (int i = 0; i < unit; i++){
        num /= 10;
    }
    return num%10;
}


// current_state(arr, len, renderer, green, yellow) draws the state of the sorting algorithm for every step it's going through
// effects: modifies renderer
void current_state(int arr[], int len, SDL_Renderer *renderer, int green, int yellow){
    for (int i = 0; i < len; i++){
        if (i == green){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else if (i == yellow){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i, 99, i, 99 - arr[i]);

    }
}

// clear_screen(renderer) clears the screen display to black
// effects: modifies renderer
void clear_screen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
// draw_screen(renderer) shows the screen
// effects: displays a screen showing a visual display of the sorting
void draw_screen(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
    SDL_Delay(0);
}

// random_number_generator(min, max) generates a random number between min and max and returns
int random_number_generator(int min, int max){
    return (rand() % (max - min + 1) + min);
}

// QUICKSORT
// ====================================================
// merge_sort_helper(arr, start, end) sort the elements greater and smaller than the pivot and splits the array into 2
// effects: modifies renderer
void current_state_quicksort(int arr[], int len, SDL_Renderer *renderer, int green, int yellow, int start){
    for (int i = 0; i < len; i++){
        if (i == green){
            SDL_SetRenderDrawColor(renderer, 201, 242, 155, 255);
        }
        else if(i == start){
            SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255);
        }
        else if (i == yellow){
            SDL_SetRenderDrawColor(renderer, 255, 252, 127, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i, 99, i, 99 - arr[i]);

    }
}

// quicksort_helper(arr, len, start, end, renderer) seperates all elements greater or smaller to the pivot
// and inserts the pivot in its sorted position
// effects: mutates arr
//          displays a screen
void quicksort_helper(int arr[], int len, int start, int end, SDL_Renderer *renderer){
    if (start >= end){
        return;
    }
    int to_swap = end;
    for (int i = end; i >= start; i--){
        if (arr[start] < arr[i]){
            swap(arr, to_swap, i);
            to_swap--;
        }
        clear_screen(renderer);
        current_state_quicksort(arr, len, renderer, to_swap, i, start);
        draw_screen(renderer);
    }
    current_state(arr, len, renderer, to_swap, start);
    draw_screen(renderer);
    swap(arr, to_swap, start);
    quicksort_helper(arr, len, start, to_swap - 1, renderer);
    current_state(arr, len, renderer, to_swap, start);
    draw_screen(renderer);
    quicksort_helper(arr, len, to_swap + 1, end, renderer);
    current_state(arr, len, renderer, to_swap, start);
    draw_screen(renderer);
}

// merge_sort(arr, len) sorts the array arr using the first index as the pivot
// effects: mutates arr
//          displays a screen
void quicksort(int arr[], int len, SDL_Renderer *renderer){
    quicksort_helper(arr, len, 0, len - 1, renderer);
}
// =====================================================

// INSERT SORT
// =====================================================
// insert_sort(int arr, int len) sorts arr
// effects: mutates arr
//          displays a screen
void insert_sort(int arr[], int len, SDL_Renderer *renderer){
    int to_swap;
    for (int i = 0; i < len; i++){
        to_swap = i;
        for (int j = i; j >= 0; j--){
            if (arr[to_swap] > arr[j]){
                break;
            }
            else if (j != to_swap){
                swap(arr, to_swap, j);
                to_swap--;
            }
            clear_screen(renderer);
            current_state(arr, len, renderer, i, j);
            draw_screen(renderer);
        }
    }
}
// =====================================================

// SELCTION SORT
// =====================================================
// selection_sort(arr, len) sorts the array arr
// effects: mutates arr
//          displays a screen
void selection_sort(int arr[], int org_arr[], int len, SDL_Renderer *renderer){
    int min;
    for (int i = 0; i < len; i++){
        min = i;
        for (int j = i; j < len; j++){
            if (arr[min] > arr[j]){
                min = j;
            }
            clear_screen(renderer);
            current_state(arr, len, renderer, i, j);
            draw_screen(renderer);
        }
        swap(arr, min, i);
    }
}
// =====================================================

// MERGE SORT
// =====================================================
// curreent_state_merge(arr, start, end, renderer, green, yellow) draws the current state the array is at
// coloring position green with the green color and position yellow with the yellow color
// effects: Modifies renderer
void current_state_merge(int arr[], int start, int end, SDL_Renderer *renderer, int green, int yellow){
    for (int i = start; i <= end; i++){
        if (i == green){
            SDL_SetRenderDrawColor(renderer, 201, 242, 155, 255);
        }
        else if (i == yellow){
            SDL_SetRenderDrawColor(renderer, 255, 252, 127, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i, 99, i, 99 - arr[i - start]);

    }
}

// clear_part_screen(arr, start, end, renderer) renders all area from x position start to x position end black
// effects: Modifies renderer
void clear_part_screen(int arr[], int start, int end, SDL_Renderer *renderer){
    for (int i = start; i <= end; i++){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, i, 99, i, 0);
    }
}

// merge(dest, src1, len1, src2, len2) merges back 2 sorted arrays, src1, src2, into dest
// effects: mutates dest
//          displays a screen
void merge(int dest[], int start, int end, const int src1[], int len1, const int src2[], int len2, SDL_Renderer *renderer){
    int pos1 = 0;
    int pos2 = 0;
    for (int i = 0; i < len1 + len2; i++){
        if (pos2 == len2 || (pos1 < len1 && src1[pos1] < src2[pos2])){
            pos1++;
        }
        else{
            pos2++;
        }
        clear_part_screen(dest, start, end, renderer);
        current_state_merge(dest, start, end, renderer, pos1 + start, pos2 + start + len1);
        draw_screen(renderer);
    }
    pos1 = 0;
    pos2 = 0;
    for (int i = 0; i < len1 + len2; i++){
        if (pos2 == len2 || (pos1 < len1 && src1[pos1] < src2[pos2])){
            dest[i] = src1[pos1];
            pos1++;
        }
        else{
            dest[i] = src2[pos2];
            pos2++;
        }
        clear_part_screen(dest, start, end, renderer);
        current_state_merge(dest, start, end, renderer, -1, -1);
        draw_screen(renderer);
    }
}
// merge_sort(arr, len) sorts the array arr
// effects: mutates arr
//          displays a screen
void merge_sort(int arr[], int len, int start, int end, SDL_Renderer *renderer){
    if (len > 1){
        int left_len = len / 2;
        int right_len = len - left_len;
        int *left_arr = malloc(sizeof(int) * left_len);
        int *right_arr = malloc(sizeof(int) * right_len);
        for (int i = 0; i < left_len; i++){
            left_arr[i] = arr[i];
        }
        for (int i = 0; i < right_len; i++){
            right_arr[i] = arr[i + left_len];
        }
        merge_sort(left_arr, left_len, start, start + left_len - 1, renderer);
        merge_sort(right_arr, right_len, start + left_len, end, renderer);
        for (int x = 0; x < left_len; x++){
            arr[x] = left_arr[x];
        }
        for (int i = 0; i < right_len; i++){
            arr[i + left_len] = right_arr[i];
        }
        merge(arr, start, end, left_arr, left_len, right_arr, right_len, renderer);
        free(left_arr);
        free(right_arr);
    }
}
// draw_merge_sort(arr, len, start, end, renderer) displays how the merge algorithm works on a window
// effects: displays a screen
//          mutates arr
void draw_merge_sort(int arr[], int len, int start, int end, SDL_Renderer *renderer){
    current_state(arr, len, renderer, -1, -1);
    draw_screen(renderer);
    merge_sort(arr, len, start, end, renderer);
}
// =====================================================

// COCKTAIL SORT
// =====================================================
// cocktail_sort(arr, len, renderer) sorts the array arr and displays the cocktail sorting algorithm
// effects: mutates arr
//          displays a screen
void cocktail_sort(int arr[], int len, SDL_Renderer *renderer){
    int comp = 1;
    int end = len - 1;
    int start = 0;
    while (comp == 1){
        comp = 0;
        for (int i = start; i < end; i++){
            if (arr[i] > arr[i + 1]){
                swap(arr, i, i+ 1);
                comp = 1;
            }
            clear_screen(renderer);
            current_state(arr, len, renderer, i, i - 1);
            draw_screen(renderer);
        }
        end--;
        for (int i = end; i > start; i--){
            if (arr[i] < arr[i - 1]){
                swap(arr, i, i - 1);
                comp = 1;
            }
            clear_screen(renderer);
            current_state(arr, len, renderer, i, i - 1);
            draw_screen(renderer);
        }
        start++;
    }
}
// =====================================================

// RADIX SORT
// =====================================================
// radixsort(arr, len, renderer) sorts the array arr based on units, tens, hundreds, etc.
// effects: mutates arr
//          displays a screen
void countingSort(int arr[], int len, int unit, SDL_Renderer *renderer) {
  int *output = malloc(sizeof(int) * (len + 1));
  int max = (arr[0] / unit) % 10;

  for (int i = 1; i < len; i++) {
    if (((arr[i] / unit) % 10) > max)
      max = arr[i];
  }
  int *count = malloc(sizeof(int) * (max + 1));
  for (int i = 0; i < max; ++i) {
    count[i] = 0;
  }
  for (int i = 0; i < len; i++) {
    count[(arr[i] / unit) % 10]++;
  }
  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }
  for (int i = len - 1; i >= 0; i--) {
    output[count[(arr[i] / unit) % 10] - 1] = arr[i];
    count[(arr[i] / unit) % 10]--;
    clear_screen(renderer);
    current_state(output, len, renderer, -1, count[(arr[i] / unit) % 10] - 1);
    draw_screen(renderer);
  }
  for (int i = 0; i < len; i++) {
    arr[i] = output[i];
  }
  free(output);
  free(count);
}

// radixsort(arr, len, renderer) sorts the array arr
// effects: mutates arr
//          displays a screen
void radix_sort(int arr[], int len, SDL_Renderer *renderer) {
  int max = get_max(arr, len);
  for (int i = 1; max / i > 0; i *= 10)
    countingSort(arr, len, i, renderer);
}
// =====================================================

int main(void){
    int random_numbers[400]; // Modify array sizde based on dimensions
    int numbers_len = 400;
    srand(time(NULL));
    for (int i = 0; i < numbers_len; i++){
        random_numbers[i] = random_number_generator(1, 99);
    }
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(
        200*10, 100*10, 0, &window, &renderer // Modify dimensions based on monitor size
    );
    SDL_RenderSetScale(renderer, 5, 10);
    quicksort(random_numbers, numbers_len, renderer); //Example of use
    return 0;
}
