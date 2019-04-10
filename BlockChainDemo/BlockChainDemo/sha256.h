#ifndef __SHA256_H__
#define __SHA256_H__
#pragma once 
#include <string>  

#define SHA_LONG unsigned int  
#define SHA_LBLOCK  16
//#define SHA_LAST_BLOCK  (SHA_CBLOCK-8) 
#define SHA256_CBLOCK   (SHA_LBLOCK*4)  /* SHA-256 treats input data as a
* contiguous array of 32 bit
* wide big-endian values. */
#define SHA256_DIGEST_LENGTH    32  
#define DATA_ORDER_IS_BIG_ENDIAN  

typedef struct SHA256state_st
{
	SHA_LONG h[8];
	SHA_LONG Nl, Nh;
	SHA_LONG data[SHA_LBLOCK];
	unsigned int num, md_len;
} SHA256_CTX;

//替换定义于通用算法里面的那些宏
#define HASH_LONG               SHA_LONG  
#define HASH_CTX                SHA256_CTX
#define HASH_CBLOCK             SHA256_CBLOCK  

#define MD32_REG_T long  
#define X(i)    XX##i  

#define HASH_MAKE_STRING(c,s)   do {    \
    unsigned long ll;       \
    unsigned int  nn;       \
    for (nn=0;nn<SHA256_DIGEST_LENGTH/4;nn++)   \
	        {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
    } while (0)  



//来源于md32_common.h的定义，用于大端对齐DATA_ORDER_IS_BIG_ENDIAN
#define HOST_c2l(c,l)   (l =(((unsigned long)(*((c)++)))<<24),        \
             l|=(((unsigned long)(*((c)++)))<<16),        \
             l|=(((unsigned long)(*((c)++)))<< 8),        \
             l|=(((unsigned long)(*((c)++)))       ),       \
             l)  
#define HOST_l2c(l,c)   (*((c)++)=(unsigned char)(((l)>>24)&0xff),    \
             *((c)++)=(unsigned char)(((l)>>16)&0xff),    \
             *((c)++)=(unsigned char)(((l)>> 8)&0xff),    \
             *((c)++)=(unsigned char)(((l)    )&0xff),  \
             l)  

class sha256
{
public:
	sha256(void);
	~sha256(void);
public:
	void sha(const std::string& src, std::string& out);
private:
	int init(SHA256_CTX *c);
	int update(SHA256_CTX *c, const void *data_, size_t len);
	int final(unsigned char *md, HASH_CTX *c);
	void sha256_block_data_order(SHA256_CTX *c, const void *p, size_t num);
};
#endif