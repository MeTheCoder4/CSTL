#ifndef CSTL_LIST_H
#define CSTL_LIST_H

#ifndef STDDEF_H
#define STDDEF_H

#include <stddef.h>

#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif 

#define CSTL_LIST(T) \
struct node { \
	int key; \
	T data; \
	struct node* next; \
	struct node* prev; \
}; \
\
struct list { \
	struct node* head; \
	struct node* tail; \
}; \
\
void initialize_list(struct list* instance) { \
	instance->head = NULL; \
	instance->tail = NULL; \
} \
\
struct node* allocate_node(int key, T data, struct node* prev, \
	struct node* next) { \
	struct node* temp \
		= (struct node*) malloc(sizeof(struct node)); \
	\
	if(temp == NULL) \
		return NULL; \
	\
	temp->next = next; \
	temp->prev = prev; \
	temp->key = key; \
	temp->data = data; \
	return temp; \
}\
\
int insert(struct list* instance, int key, T data) { \
	if(instance->head == NULL) { \
		instance->head  \
			= allocate_node(key, data, NULL, NULL); \
		\
		if(instance->head == NULL) \
			return 1; \
		\
		instance->tail = instance->head; \
	} \
	else { \
		struct node* temp = NULL; \
		\
		if(key < instance->head->key) { \
				temp = allocate_node(key, data, \
				NULL, instance->head); \
			\
			if(temp == NULL) \
				return 1; \
			\
			instance->head->prev = temp; \
			instance->head = temp; \
			return 0; \
		} \
		else if(key > instance->tail->key) { \
			temp = allocate_node(key, data, \
				instance->tail, NULL); \
			\
			if(temp == NULL) \
				return 1; \
			\
			instance->tail->next = temp; \
			instance->tail = temp; \
			return 0; \
		}	\
		temp = instance->head; \
		\
		while(temp->next != NULL && \
			key > temp->next->key) \
			temp = temp->next; \
		\
		struct node* temp2 \
			= allocate_node(key, data, temp, temp->next); \
		\
		if(temp2 == NULL) \
			return 1; \
		\
		temp2->prev->next = temp2; \
		\
		if(temp2->next == NULL) \
			instance->tail = temp2; \
		else \
			temp2->next->prev = temp2; \
	} \
	\
	return 0; \
} \
\
struct node* find(struct list* instance, int key) { \
	struct node* temp = instance->head; \
	\
	if(instance->tail->key == key) \
		return instance->tail; \
	\
	while(temp != instance->tail && temp->key <= key) { \
		if(temp->key == key) \
			return temp; \
		\
		temp = temp->next; \
	} \
	\
	return NULL; \
} \
\
int remove_node(struct list* instance, int key) { \
	struct node* temp = NULL; \
	\
	if((temp = find(instance, key)) != NULL) { \
		if(instance->head->key == temp->key) { \
			instance->head = temp->next; \
			free(temp); \
			instance->head->prev = NULL; \
		} \
		else if(instance->tail->key == temp->key) { \
			instance->tail = temp->prev; \
			free(temp); \
			instance->tail->next = NULL; \
		} \
		else { \
			temp->prev->next = temp->next; \
			temp->next->prev = temp->prev; \
			free(temp); \
		} \
		\
		return 0; \
	} \
	\
	return 1; \
} \
\
int remove_list(struct list* instance) { \
	struct node* temp = instance->head; \
	\
	temp = temp->next; \
	while(temp != NULL) { \
		free(temp->prev); \
		temp = temp->next; \
	} \
	\
	free(instance->tail); \
	return 0; \
} \

#endif
