#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "huffman.h"
char *fn;
node* new(char data, unsigned freq) {
    node* temp = (node*) malloc(sizeof(node) );
    temp->l = temp->r = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
heap* createMinHeap(unsigned capacity) {
    heap* heap_1 = (heap*) malloc(sizeof(heap_1));
    heap_1->size = 0;
    heap_1->capacity = capacity;
    heap_1->arr =(node**)malloc(heap_1->capacity * sizeof(node*) );
    return heap_1;
}
void swapMinHeapNode(struct node **a, struct node **b) {
    struct node* t = *a;
    *a = *b;
    *b = t;
}
void build(heap* heap_1, int idx) {
    int s = idx;
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    if (l < heap_1->size && heap_1->arr[l]->freq < heap_1->arr[s]->freq)
        s = l;
    if (r < heap_1->size && heap_1->arr[r]->freq < heap_1->arr[s]->freq)
        s = r;
    if (s != idx) {
        swapMinHeapNode(&heap_1->arr[s], &heap_1->arr[idx]);
        build(heap_1, s);
    }
}
node* extract(heap* heap_1) {
    node* temp = heap_1->arr[0];
    heap_1->arr[0] = heap_1->arr[heap_1->size - 1];
    --heap_1->size;
    build(heap_1, 0);
    return temp;
}
void insert(heap* heap_1, node* Node) {
    ++heap_1->size;
    int i = heap_1->size - 1;
    while (i && Node->freq < heap_1->arr[(i - 1)/2]->freq) {
        heap_1->arr[i] = heap_1->arr[(i - 1)/2];
        i = (i - 1)/2;
    }
    heap_1->arr[i] = Node;
}
void buildMinHeap(heap* heap_1) {
    int n = heap_1->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        build(heap_1, i);
}
void printArr(char arr[], int n, int size, char c) {  
    static int j = 0;
    char code[size][32]; 	
    int i = 0;
    sprintf( &code[j][0] ,"%c", c);
    for (i = 1; i < (n + 1) ; i++)
        sprintf( &code[j][i] ,"%c", arr[i - 1]);
    *(code[j] + i) ='\0';
   // printf("%s%c%d",code[j] ,*(code[j] + 0), j);
    j++;
    printf("\n");
    if(j == size) {
	FILE *cp; 
	FILE *fp;
	int _j, _i, x;
	char ch;
	unsigned int p = sizeof(int);
	unsigned static int bitbuffer ='\0';
	int bitsinbuffer = 0;
	//char *compressedfilename;
	//compressedfilename = strcat(fn, ".z");
	fp = fopen(fn, "r");
	//printf("%s",argv[1]);
	cp = fopen("comp.txt", "w+");
	if( cp == NULL) {
		printf("FILE COULD NOT OPEN!");
		return;
	}
	while(  ( x = fread(&ch , sizeof(ch), 1, fp ) ) != 0 ) {
		printf("%c\t",ch);
		/*for(_j = 0 ; ( _j < size ) ; _j++) {
			if(ch == code[_j][0]) {
				printf("%s\n",code[_j]);
				break;
			}
			printf("hi");
			
		}*/
		//printf("%c%c%c%c", *(code[0] + 0), *(code[1] + 0), *(code[2] + 0) ,*(code[3] + 0));
		while(code[_j][++_i] != '\0') { 
			bitbuffer = bitbuffer | ( (code[_j][_i] == '1') ? 1 : 0 );
			(bitbuffer << 1 ); 
			bitsinbuffer++;
			if(bitsinbuffer > ( p*8 - 1 ) ) {
				fwrite(&bitbuffer, sizeof(bitbuffer), 1, cp);
				bitsinbuffer = 0;
				bitbuffer = '\0';
			}
		}
	}
	while(bitsinbuffer > 0 && (x == 0) ) {
		bitbuffer = bitbuffer | ( 1 ? 0 : 1 );
		(bitbuffer << 1 ); 
		bitsinbuffer++;
		if(bitsinbuffer > ( p*8 - 1 ) ) {
			fwrite(&bitbuffer, sizeof(bitbuffer), 1, cp);
			break;
		}
	}
	fclose(cp);
        fclose(fp);
   }
}
heap* create(char data[], int freq[], int size) {
    heap* heap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        heap->arr[i] = new(data[i], freq[i]);
    heap->size = size;
    buildMinHeap(heap);
    return heap;
}
node* buildHuffmanTree(char data[], int freq[], int size) {
    node *l, *r, *top;
    heap* heap = create(data, freq, size);
    while (!(heap->size == 1) ) {
        l = extract(heap);
        r = extract(heap);
        top = new('$', l->freq + r->freq);
        top->l = l;
        top->r = r;
        insert(heap, top);
    }
    return extract(heap);
}
void print(node* root, char arr[], int top, int size) {
    if (root->l) {
        arr[top] = '0';
        print(root->l, arr, top + 1, size);
    }
    if (root->r) {
        arr[top] = '1';
        print(root->r, arr, top + 1, size);
    }
    if (!(root->l) && !(root->r) ) {
        printArr(arr, top, size, root->data);
    }
}
void HuffmanCodes(char data[], int freq[], int size) {
   node* root = buildHuffmanTree(data, freq, size);
   char arr[MAX], top = 0;
   print(root, arr, top, size);
}	
void findcharandfreq(char arr[], int freq[], FILE *fp) {
	int init, idxofarr = 0, flag = 1, j;
	char ch;
	while( (ch = getc(fp) ) != EOF ) {	
		if( idxofarr != 0) {
			for( init = 0 ; init < idxofarr; init++) {
				if( ch == arr[init] ) {
					freq[init]++;
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
			if(flag == 0)
				continue;
		}
		if(flag == 1) {
			arr[idxofarr] = ch;
			freq[idxofarr] = 1;
			idxofarr++;
			flag = 0;
		}
	}
	/*for(init = 0 ; init < idxofarr ; init++) {
		printf("%c ",arr[init]);
		printf("%d\n",freq[init]);
	}*/
	fclose(fp);
        int size = idxofarr/sizeof(arr[0]);
        HuffmanCodes(arr, freq, size);
}
int main(int argc ,char *argv[]){
	char arr[256];
	int freq[256];
	FILE *fp;
	fn = argv[1];
	if(argc < 2) {
		errno = EINVAL;
		perror("BAD ARGUMENTS!");
		return errno;
	}
	fp = fopen(argv[1] , "r");
	if( fp == NULL) {
		printf("FILE COULD NOT OPEN!");
		return errno;
	}
	findcharandfreq(arr, freq, fp);
return 0;
}
