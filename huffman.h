#ifndef HUFFMAN_H
#define HUFFMAN_H
struct letter {
	unsigned long count;
	int value;
	struct letter *next;
	struct letter *left, *right;
	int codes[256], size;
};
unsigned long charCount;
int arr[256], sympos[256];
void encodeFile(FILE* in, FILE* out, int printTable);
void decodeFile(FILE* in, FILE* out);
struct letter* createNode(int value, unsigned long count, struct letter* left,
 struct letter* right);
struct letter* pop(struct letter** headRef);
struct letter* createTree();
int exists(int c);
struct letter* insert(struct letter* head,struct letter* left, struct letter* right,
 int value, unsigned long count);
int qdone(struct letter* head);
int furright(struct letter* head);
void initcode(struct letter* node);
void buildCodes(struct letter* node, int code, int size);
struct letter* fill(struct letter* head,struct letter* left, struct letter* right,
 int value, unsigned long count);
struct letter* findNode(struct letter* root,int value);
unsigned short numl(struct letter* head);
void freeTree(struct letter* root);
#endif
