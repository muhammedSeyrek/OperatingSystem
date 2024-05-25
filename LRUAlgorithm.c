#include <stdio.h>
#include <stdlib.h>

static int counter = 0;

int exists(int elements, int *memory, int memorySize){
	for(int i = 0; i < memorySize; i++)
		if(memory[i] == elements)
			return 1;
	return 0;
}

int checkFreq(int *freq, int size){
	int flag = 1;
	for(int i = 0; i < size; i++)
		if(freq[i] == 0) flag = 0;
		
	if(flag) return 1;
	else return 0;
}

int minFreq(int *freq, int size){
	int min = 0;
	for(int i = 0; i < size; i++)
		if(freq[min] > freq[i])
			min = i;
	return min;
}

void fullMemory(int *array, int *memory, int memorySize, int index) {
	
	int firstProcess, freqCounter = 0, forFreq = -1;
	
	if(exists(array[index], memory, memorySize))
		return;
	
	int *freq = malloc(sizeof(memorySize) * sizeof(int));
	
	memcpy(freq, memory, sizeof(memorySize) * sizeof(int));
	
	for(int i = 0; i < memorySize; i++) freq[i] = 0;
	
    for (int i = index - 1; i >= 0; i--) {
    	if(checkFreq(freq, memorySize)) break; //icinin dolu oldugu durum.
		for (int j = 0; j < memorySize; j++) {
	        if (array[i] == memory[j]) {
	            freq[j] = forFreq--;
	            break;
	        }
		}	
    }
        		
    memory[minFreq(freq, memorySize)] = array[index];
    counter++;
    free(freq);
    return;
}

void listMemory(int *memory, int memorySize) {
    for (int i = 0; i < memorySize; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

void main(void) {
    int array[] = {1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2};
    int memorySize;
    char words;
    printf("Enter memory size: ");
    scanf("%d", &memorySize);

    int *memory = malloc(memorySize * sizeof(int));
    
    for (int i = 0; i < memorySize; i++) 
        memory[i] = 0;
    

    int index = 0, flag = 0;
	int indexFirst = 0;
    do {
        printf("Please press any button -> ");
        scanf(" %c", &words); 

        if (flag) {
            fullMemory(array, memory, memorySize, index);
        } 
		else {
            if(indexFirst == memorySize){
            	flag = 1;
            	fullMemory(array, memory, memorySize, index);
			}
            	
            else{
            	if(!exists(array[index], memory, memorySize)){
            		memory[indexFirst++] = array[index];
            		counter++;	
				}
			}
        }
        index++;
        listMemory(memory, memorySize);
    } while (index < (sizeof(array) / sizeof(int)));
    printf("\n\nWrong page count: %d", counter);
    free(memory);
}

