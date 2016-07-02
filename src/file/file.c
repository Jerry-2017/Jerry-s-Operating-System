#include "include/common/common.h"
#include "include/device/io.h"
#define rootfile 10
#define startblock 2
#define BLOCK_SIZE 1024*1024
#define BLOCKSZ 512
#define MAX_BLK 16
#define START_BLOCK 2
#define FNAMEMAX 64
#define MAX_CHILD 16
#define MAX_LINK 16
typedef struct FILENODE{
    char name[FNAMEMAX];
	int node;
	int direct[MAX_LINK];//1024KB block
	int nchild;
	int child[MAX_CHILD];
} fnode;


struct {
    fnode rtnd[rootfile];
    int free[MAX_BLK];
} root;

int strcmp(const char* A,const char *B)
{
    int i;
    for (i=0;;i++)
    {
        if (A[i]=='\0' || B[i]=='\0')
            break;
        if (A[i]!=B[i])
            return false;
    }
    return true;
}

int strcpy(const char*src, char *dst)
{
   int i;
   for (i=0;;i++)
   {
      dst[i]=src[i];
      if (src[i]=='\0')
         break;
   }
   return 0;
}

int finit()
{
    int i;
    for (i=0;i<rootfile;i++)
    {
        root.rtnd[i].nchild=0;
        root.free[i]=0;
        strcpy(root.rtnd[i].name,"");
    }
    root.rtnd[0].nchild=1;
    root.rtnd[0].child[0]=0; 
    strcpy(root.rtnd[0].name,"Prog.o");
    root.free[0]=1;
    //fsave();
    return 0;
}

int fsave()
{
    int i;
    for (i=0;i<sizeof(root)/BLOCKSZ;i++)
    {
	writesects((void*)(&root)+BLOCKSZ*i,startblock+i,1);
    }
    return 0;
}

int fload()
{
   int i;
   for (i=0;i<sizeof(root)/BLOCKSZ;i++)
   {
       readsects((void*)(&root)+BLOCKSZ*i,startblock+i,i);
   }
   return 0;
}


int fread(const char* fname,uint32_t addr)
{
   for (int i=0;i<rootfile;i++) {
       if (strcmp(fname,root.rtnd[i].name))
       {
           readsects((void*)(addr+BLOCK_SIZE*i),startblock+BLOCK_SIZE/BLOCKSZ*i,BLOCK_SIZE/BLOCKSZ);
       }
   }
   return 0;
}

int fwrite(const char*fname,uint32_t addr)
{
   for (int i=0;i<rootfile;i++) {
       if (strcmp(fname,root.rtnd[i].name))
       {
           writesects((void*)(addr+BLOCK_SIZE*i),startblock+BLOCK_SIZE/BLOCKSZ*i,BLOCK_SIZE/BLOCKSZ);
       }
   }
   return 0;
}
