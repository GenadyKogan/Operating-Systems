#ifndef FUNCTION_H
#define FUNCTION_H
void writeFunc(int key, char* data){
	memory* temp = temp1;
	int flag = 0;
	do{
		if(temp->key == key){
			strcat(temp->data,data);
			flag =1;
			if(status == 1){
				lruSwapFunc(temp);
			}
			break;
		}
		temp=temp->next;
	}while(temp!=NULL);
	// copy from secondary to main memory.
	if(flag == 0){
		dequeueFunc(temp1->key);
		enqueueFunc(key,secondaryMemory[key]);
		temp  = temp1;
		while(temp!=NULL){
			if(temp->key == key){
				strcat(temp->data,data);
				break;
			}
			temp=temp->next;
		}

	}
	
}


void auxillaryFunc(memory* temp2){
	if (temp1 == temp2) 
        	temp1 = temp2->next; 
   	if (temp2->next != NULL) 
       		temp2->next->prev = temp2->prev; 
   	if (temp2->prev != NULL) 
       		temp2->prev->next = temp2->next;
}

void lruSwapFunc(memory* temp){
	memory* temp2 = temp1;
	memory *swap;
	memory *last;
	do{
		if(temp2->key == temp->key){
			swap = temp2;
			if (temp1 == temp2) 
        			temp1 = temp2->next; 
   			if (temp2->next != NULL) 
       				temp2->next->prev = temp2->prev; 
   			if (temp2->prev != NULL) 
       				temp2->prev->next = temp2->next;
		}

		temp2 = temp2 ->next;
	}while(temp2!=NULL);
	enqueueFunc(swap->key,swap->data);

}


char *readFunc(int key){
	memory *temp  = temp1;
	do{
		if(temp->key == key){
			if(status == 1){
				lruSwapFunc(temp);
			}
			return temp->data;
		}
		temp = temp->next;
	}while(temp!=NULL);
	// copy from secondary to main memory.
	dequeueFunc(temp1->key);
	enqueueFunc(key,secondaryMemory[key]);
	temp  = temp1;
	while(temp!=NULL){
		if(temp->key == key){
			return temp->data;
		}
		temp = temp->next;
	}
	return "";
}


void dequeueFunc(int key){
	memory* temp2 = temp1;
	char * swap;
	do{
		if(temp2->key == key){
			swap = (char*)malloc(strlen(temp2->data)+1);
			strcpy(swap,temp2->data);
			if (temp1 == temp2) 
        			temp1 = temp2->next; 
   			if (temp2->next != NULL) 
       				temp2->next->prev = temp2->prev; 
   			if (temp2->prev != NULL) 
       				temp2->prev->next = temp2->next;
		}
		temp2 = temp2 ->next;
	}while(temp2!=NULL);
	
	strcpy(secondaryMemory[key],swap);
}
void enqueueFunc(int key,char* data){
	
	memory* table = (memory*)malloc(sizeof(memory));
	if(currentNode == NULL){
		currentNode = (memory*)malloc(sizeof(memory));
		temp1  = (memory*)malloc(sizeof(memory));
		temp1 = table;
		table->prev = NULL;

	}
	else{ 
		table->prev = currentNode; 
		currentNode->next = table;
	}
	table->data = (char*)malloc(1000);
	table->key = key;
	strcpy(table->data,data);
	table->next = NULL;
	currentNode = table;
}
#endif


