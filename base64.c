//base64编码代码

#include <stdlib.h>

const char *base64_list = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789+/";
const char base64_last 	= '=';

char* base64_enc(const char* data, int len, char *dst)
{
	if(!data || len <= 0)	return NULL;

	int new_len = (len * 4) / 3 + 5;
	if(!dst)
		dst = (char*)calloc(new_len, 1);

	int index = 0;

	int i = 0;
	for(i = 0; i < len; i+=3)
	{
		char tmp[3] = { 0 };
		for(int j = 0; j < 3 && j < (len-i); j++)
		{
			tmp[j] = data[i+j]; 
		}
		dst[index++] = base64_list[tmp[0]>>2];
		dst[index++] = base64_list[((tmp[0]&3)<<4) + (tmp[1]>>4)];
		dst[index++] = base64_list[((tmp[1]&0xf)<<2) + (tmp[2]>>6)];
		dst[index++] = base64_list[tmp[2]&0x3f];
	}
	//注意这里是允许data不以\0结尾的

	if(i == len + 1)
		dst[index - 1] = '=';
	else if(i == len + 2)
		dst[index - 1] = dst[index - 2] = '=';

	return dst;	
}

char* base64_dec(const char *data, int len, char *dst)
{
	if(!data || len < 0)
		return NULL;
	int new_len = (len * 3) / 4 + 3;
	if(!dst)
		dst = (char*)calloc(new_len, 1);

	u_int8_t map[128] = { 0 };
	for(int i = 0; i < 64; i++)
	{
		map[base64_list[i]] = i;
	}

	if(data[len-1] == '=') len--;
	if(data[len-2] == '=') len--;

	int index = 0;
	for(int i = 0; i < len; i+=4)
	{
		u_int8_t tmp[4] = { 0 };
		for(int j = 0; j < 4 && j < (len - i); j++)
		{
				tmp[j] = map[data[i+j]];
		}

		dst[index++] = (tmp[0]<<2) + (tmp[1]>>4);
		if(len - i > 2)
			dst[index++] = (tmp[1]<<4) + (tmp[2]>>2);
		if(len - i > 3)
			dst[index++] = (tmp[2]<<6) + tmp[3];

	}

	return dst;
}

#ifdef TEST_BASE64
#include <string.h>
#include <stdio.h>
	int main()
	{
		char buffer[128];
		scanf("%s", &buffer);

		char *enc = base64_enc(buffer, strlen(buffer), NULL);
		printf("base encode: %s\n", enc);;

		char *dec = base64_dec(enc, strlen(enc), NULL);
		printf("base decode: %s\n", dec);

		return 1;
	}

#endif