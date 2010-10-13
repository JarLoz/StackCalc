

struct doubleStack{
	double value;
	struct doubleStack *next;
};

typedef struct doubleStack doubleStack;


doubleStack* createStackNode(double);
doubleStack* push(double, doubleStack*);
double pop(doubleStack**, int*);
void printStackContent(doubleStack*);
void* destructStack(doubleStack*);
