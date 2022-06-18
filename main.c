#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HASH_SIZE 100

typedef struct Node {
  char *key;   
  char *data;
  struct Node *next;
} Node;

typedef struct HashTable {
  Node* list[MAX_HASH_SIZE];
} HashTable;

unsigned int hash(char *key) {
  unsigned int hash = 5381;
  unsigned int i = *key;
  while (i) {
    hash = hash * 33 + i;
    i = *key++;
  }

  return hash % MAX_HASH_SIZE;
}

Node *createNode(char *key, char *data) {
  Node *node = malloc(sizeof(Node));
  node->key = malloc(sizeof(char) * strlen(key) + 1);
  node->data = malloc(sizeof(char) * strlen(data) + 1);
  strcpy(node->key, key);
  strcpy(node->data, data);
  node->next = NULL;

  return node;
}

void insert(HashTable *hash_table, char *key, char *data) {
  int hash_index = hash(key);
  Node *new_node = createNode(key, data);
  Node *current_node = hash_table->list[hash_index];

  if (current_node == NULL) {
    hash_table->list[hash_index] = new_node;
    return;
  }

  if (strcmp(current_node->key, key) == 0) {
    strcpy(current_node->data, data);
    return;
  }

  while (current_node->next != NULL) {
    if (strcmp(current_node->next->key, key) == 0) {
      strcpy(current_node->next->data, data);
      return;
    }

    current_node = current_node->next;
  }

  current_node->next = new_node;
}

char *search(HashTable *hash_table, char *key) {
  int hash_index = hash(key);
  Node *current_node = hash_table->list[hash_index];

  while (current_node != NULL) {
    if (strcmp(current_node->key, key) == 0) {
      return current_node->data;
    }
    current_node = current_node->next;
  }

  return NULL;
}

void clearHashTable(HashTable* hash_table) {
  for (int i = 0; i < MAX_HASH_SIZE; i++) {
    Node *current_node = hash_table->list[i];
    while (current_node != NULL) {
      Node *next_node = current_node->next;
      free(current_node->key);
      free(current_node->data);
      free(current_node);
      current_node = next_node;
    }

    hash_table->list[i] = NULL;
  }

}

HashTable *createHashTable() {
  HashTable *hash_table = malloc(sizeof(HashTable));
  int i = 0;

  for (i = 0; i < MAX_HASH_SIZE; i++) {
    hash_table->list[i] = NULL;
  }

  return hash_table;
}

int main() {
  HashTable *hash_table = createHashTable();
  char hello_key[] = "hello";
  char name_key[] = "name";

  insert(hash_table, hello_key, "world");
  insert(hash_table, name_key, "Ozeias Ribeiro");

  char *hello_content = search(hash_table, hello_key);
  printf("Content in key \"%s\": \"%s\"\n", hello_key, hello_content);

  char *name_content = search(hash_table, name_key);
  printf("Content in key \"%s\": \"%s\"\n", name_key, name_content);

  clearHashTable(hash_table);
  return 0;
}
