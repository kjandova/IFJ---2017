//zasobnik

#define E_FILE 1
#define MAXSTACK 30

typedef struct iStack{
  tabItem * data;
  int type;
} tStack_item;
 
typedef struct tStacke {
    tStack_item * item;
    int top;
    int size;
} *tStack;

void SPrint(tStack *S);
int SInit(tStack *S);
void SDispose(tStack *S);
void SPush(tStack *S, int ptr, tabItem *addr);
void SPush_term(tStack *S, int ptr, int addr);
void SPop(tStack *S);
tStack_item STop(tStack *S);
int SFind_Term(tStack * S);
tStack_item STop_Term(tStack *S);

