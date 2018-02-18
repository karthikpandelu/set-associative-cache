#define SETS 2          //number of sets in the cache segment
#define LINES 1024      //number of lines in the cache memory
#define BLOCK_SIZE 128  //size of each block = 128 bytes 
#define TAG_BIT 13      //number of tag bits from the address
#define TAG 19
#define BLOCK 512       //to calculate hash function


#include <stdio.h>
#include <stdlib.h>

//declaration of functions
void cacheMemory(unsigned long int);
unsigned long int cacheTag(unsigned long int);
int hashValue(unsigned long int);
void assignValues(int, int, unsigned long int);

//declaration of the cache hit and cache miss counters
static int hit_count = 0;
static int miss_count = 0;

//structure of each cache line
typedef struct{
    int valid;
    unsigned long int tag;
    unsigned long int address;
}cache;

// declaration of cache memory 
cache cacheBlock[LINES];

int main(){
    int i;
    int n = 1728000;                                           //number of inputs
    unsigned long int address;                              //unsigned long integer to hold the value of address 
    for(i=0; i<n; i++){
        scanf("%lu", &address);
        cacheMemory(address);                               //calling cacheMemory function to chech cache memory
    }
    printf("CacheHit count = %d\n", hit_count);
    printf("CacheMiss count = %d\n", miss_count);   

    float hit_ratio = ((float)hit_count/(hit_count + miss_count))*100;

    printf("CacheHit ratio = %.4f %%\n", hit_ratio);

    printf("CacheMiss ratio = %.4f %%\n", (100-hit_ratio)); 
}

void cacheMemory(unsigned long int addrs){
    int hValue = hashValue(addrs);                          //hash function value for the input address
    unsigned long int tagTemp = cacheTag(addrs);                          //tag value for the input address

    
    if(cacheBlock[hValue].valid == 1){                      //if valid bit at cacheBlock[hValue] is 1, then enter the loop                      
        if(cacheBlock[hValue].tag == tagTemp){              //if tag matches => cache hit
        hit_count++;                                        //increament hit counter
        return;                                             //return to main
        }
        else if(cacheBlock[hValue+BLOCK].valid == 1){       //if tag not equal at cacheBlock[hValue] then check at cacheBlock[hValue+BLOCK]
            if(cacheBlock[hValue+BLOCK].tag == tagTemp){    
                hit_count++;                                //if tag at hValue+BLOCK macthes, increament hit counter
                return;
            }
            else{
                assignValues(hValue, tagTemp, addrs);       //if valid is 1 at both hValue and hValue+BLOCK and doesn't macth, then assign new value to cacheBlock[hValue]
                miss_count++;                               //increament hit miss counter
                return;
            }
        }

    //if valid bit at cacheBlock[hValue+BLOCK] is not equal to 1, then make a cache entry and increament hit miss counter
        assignValues(hValue+BLOCK, tagTemp, addrs);
        miss_count++;
        return;
    }

    //if cacheBlock[hValue] is not 1, then make new entry and increament hit miss counter
    assignValues(hValue, tagTemp, addrs);
    miss_count++;
    return;
}


//function to calculate tag of an address
unsigned long int cacheTag(unsigned long int addrs){
    // int tag;
    addrs = addrs >> TAG;                                   //right shift by TAG number of bits to get the tag value
    // tag = addrs;
    return addrs;                                             //return tag value
}

//function to calculate hash value
int hashValue(unsigned long int tag){
    int h = tag % BLOCK;
    return h;                                               //return hash value
}

//function to make new entry to the cache memory
void assignValues(int hValue, int tagValue, unsigned long int addrs){
    cacheBlock[hValue].valid = 1;                           //make valid bit = 1
    cacheBlock[hValue].tag = tagValue;                      //assign tag value
    cacheBlock[hValue].address = addrs;                     //assign the complete address
}