#include <stdio.h>
#include <stdlib.h>

int arrayProcessIds[] = {1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2};
int arrayPriorities[] = {5, 4, 3, 5, 4, 7, 2, 1, 2, 5 ,3, 5, 4, 2, 3, 1, 4, 4, 2, 3, 2, 2};
static int counter = 0;
typedef struct Process{
	int processId;
	int priority;
	struct Process *next;
}Process;

typedef struct Memory{
	int processId;
	int priority;
	struct Memory *prev;
	struct Memory *next;
}Memory;

void swap(Memory *x, Memory *y){
	int tempPriority = x -> priority;
	int tempProcessId = x -> processId;
	x -> priority = y -> priority;
	x -> processId = y -> processId;
	y -> priority = tempPriority;
	y -> processId = tempProcessId;
	counter++;
}

void Sort(Memory *head){
	
	Memory *iter = head;
	
	if(iter -> prev != NULL){
		if(iter -> priority > iter -> prev -> priority){
			swap(iter, iter -> prev);
			if(iter -> prev != NULL)
				Sort(iter -> prev);
			else
				Sort(iter -> next);
		}
		else{
			if(iter -> next != NULL)
				Sort(iter -> next);
			else{
				return;
			}
				
		}
	}
	
	else{
		if(iter -> next != NULL)
			Sort(iter -> next);
		else
			return;
	}
	
}

void transferProcess(Process **process){
	
	for(int i = 1; i < sizeof(arrayProcessIds) / sizeof(int); i++){
		
		Process *current = malloc(sizeof(Process));
		current -> processId = arrayProcessIds[i];
		current -> priority = arrayPriorities[i];
		current -> next = NULL;
		
		if(*process == NULL){
			*process = current;
		}
		else{
			Process *iter = *process;
			while(iter -> next != NULL){
				iter = iter -> next;
			}
			iter -> next = current;
		}
		
	}		
	
}

void listProcess(Process *process, int index){
	Process *iter = process;
	for(int i = 0; i < index; i++){
		iter = iter -> next;
		printf(" ");	
	} 
	while(iter != NULL){
		printf("%d ", iter -> processId);
		iter = iter -> next;
	}
	printf("\n\n");
}

void listMemory(Memory *memory, int count){
	Memory *iter = memory;
	while((iter != NULL) && count != 0){
		printf("Process: %d\t Priority: %d\n", 
		iter -> processId, iter -> priority);
		iter = iter -> next;
		count--;
	}
	printf("\n\n\n");
}

void main(void){
	Process *process = NULL;
	transferProcess(&process);
	listProcess(process, 0);
	int memorySize, index = 0;
	
	printf("What is memory length: ");
	scanf("%d", &memorySize);
	printf("\n\n");
	
	Process *current = process;
	Memory *memory = NULL;
	while(current != NULL){
		Memory *iter = memory;
		int	flag = 1;
		
		while(iter != NULL){
			if(current -> processId == iter -> processId){
				iter -> priority += current -> priority;
				Sort(iter);
				flag = 0;
			}
			iter = iter -> next;
		}	
		
		if(flag){ 
			Memory *newMemory = malloc(sizeof(Memory));
			newMemory -> processId = current -> processId;
			newMemory -> priority = current -> priority;
			newMemory -> next = NULL;
			newMemory -> prev = NULL;
			
			if(memory == NULL){
				memory = newMemory;
				counter++;
			}
			else{
				Memory *memoryIter = memory;
				while(memoryIter -> next != NULL){
					memoryIter = memoryIter -> next;
				}
				if(counter < memorySize)
					counter++;
				memoryIter -> next = newMemory;
				newMemory -> prev = memoryIter;
			}
			Sort(memory);
		}
		index++;
		listProcess(process, index);
		listMemory(memory, memorySize);
		current = current -> next;
	}	
	
	printf("\n\nWrong Page:%d", counter);
	
}


