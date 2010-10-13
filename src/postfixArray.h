/*postfixArray.h*/

#define MAX_TOKENS 80
struct postfixArray{
	char** array;
	int size;
};
typedef struct postfixArray postfixArray;

postfixArray* createPostfixArray(char*);
void printPostfixArrayContents(postfixArray*);
void destructPostfixArray(postfixArray*);
