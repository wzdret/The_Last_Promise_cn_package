/*
 * export_text.c
 *
 *  Created on: 2015��4��19��
 *      Author: yami
 */


/**
 * @file		export_text.c
 * @author		yami
 * @date		2015-04-19 01:16:49
 * @brief
 * ����ROM������ı�����
 * ����ʱ��		2015-04-26 15:14:26
 * �����Ϊ�˷��㷭�����޳�һЩ���Ʒ�
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef		unsigned char	u8;
typedef		unsigned short	u16;
typedef		unsigned int	u32;

typedef		signed char		s8;
typedef		signed short	s16;
typedef		signed int		s32;


typedef struct{
	char*	filename;
	int		size;
	u8*		mem;
	u32		mask_point;
	u32		mask_base;
	u32		texts_base;
}rom;



rom		TLP_rom	=	{
		"fe7tlp.gba",
		0,
		0,
		0x8B808A8,		//ͷ��Ϣ
		0x8B7D71C,		//huffman����
		0x8B808AC		//�ı�ָ��
};


/**
 *��ʼ���ṹ������
 * @param rom	rom�ṹ��
 * @return		�������0����������
 */
int		rom_init(rom*rom){
	if(!rom->mem)
	{
		if(rom->filename){
			FILE*	file;
			u8		*mem;
			file	=	fopen(rom->filename,"rb");
			if(!file){
				printf("���ļ�(%s)ʧ��\n",rom->filename);
				return 1;
			}
			fseek(file,0,SEEK_END);
			rom->size	=	ftell(file);
			if(rom->size<=0){
				printf("�����ļ�(%s)��Сʧ��\n",rom->filename);
				fclose(file);
				return 1;
			}

			//�����ڴ�
			rom->mem	=	(u8*)calloc(rom->size,1);

			if(!rom->mem){
				printf("�����ڴ�ʧ��\n");
				return 1;
			}

			//�ļ����¶�λ
			fseek(file,0,SEEK_SET);
			fread(rom->mem,rom->size,1,file);
			fclose(file);
		}
		else
		{
			return 1;
		}
	}
	return 0;
}


/**
 * �ͷ���rom������
 * @param rom	rom�ṹ��
 * @return		�������0�������ͷ�
 */
int		rom_free(rom*rom){
	if(rom->mem){
		free(rom->mem);
		rom->mem	=	0;
	}
	return 0;
}


/**
 * ���ROM���������,�������0,���ʾʧ��
 * @param r			rom�ṹ��
 * @param addr		rom��ַ
 * @return			���ص�ǰ��ַ
 */
u8*		rom_data(rom*r,u32 addr){
	if(addr>=0x08000000&&addr<=0x0A000000){
		addr-=0x08000000;
		return 	r->mem + addr;
	}
	return 0;
}




int		huffman_decode(rom*r,u32 src,u8*dst){
		//��ʼ����
	u8			*src_data;
	u32			bit;
	int			bit_index;
//	struct{
//		u16		low;
//		u16		High;
//	}tree;
	u16			*tree_data;
	u16			*tree_data_base;
	u32			*tree_base;
	u16			tree_;
	s32			data;
	if(!r->mask_base)
		return 1;
	if(!r->mask_point)
		return 1;
	//ǰ����ǽ���ʧ��,��Ϊ�ǿ�ָ��u




	tree_base	=	(u32*)rom_data(r,r->mask_base);

	tree_data_base	=	(u16*)rom_data(
			r,
			*(u32*)rom_data(r,r->mask_point)
			);

	src_data	=	rom_data(r,src);
	if(!src_data){
		printf("����������ָ�����\n");
		return 1;
	}
	tree_data	=	tree_data_base;
	do{
		//֪��ѭ����0����Ϊֹ
		bit		=	*src_data++;
		for(bit_index=7;bit_index>=0;bit_index--){
			tree_		=	tree_data[bit&1];
			tree_data	=	(u16*)(tree_base	+	tree_);
			bit	>>=	1;
			if((data = *((s32*)tree_data))>0){
				continue;
			}
			tree_data	=	tree_data_base;
			if(!(data&0xff00)){
				*dst	=	(u8)data;
				if(!(data&0xff))
				{
					return 0;
				}
				else{
					dst	++;
				}
			}
			else{
				//XXYY
				dst[0]	=	(u8)data;
				dst[1]	=	(u8)(((u32)(data))>>8);
				dst		+=	2;
			}
		}
	}while(1);

	return 0;
}

static	void	out_C_str_(FILE*file,u8*text,u32	index){
	u8		*src_text;
	u8		c;
	s32		len;
	s32		flag;
	u8		format[0x50];
	src_text	=	text;
	len			=	0;
	flag		=	0;
	if(file){
		sprintf(format,"%.15s","[0x%04X] = ");
		fprintf(file,format,index);
		fprintf(file,"\"");
		while((c = *src_text++)){

			if(len){
				//����
				//fprintf(file,"\\x%02X",c);
				len	--;
				continue;
			}

			if(c<=0x1F||c>=0x80){


				if(c==0x10){
					len	=	1;		//����1��������ȥ
				}

				if(!flag){
					//fprintf(file,"\"\n%12s","\"");		//����,����
					flag	=	1;						//�����������Ʒ�����һ��
					fprintf(file,"\"\n%12s","\"");
				}
				//fprintf(file,"\\x%02X",c);
				if(c==1){
					//����,�ַ������
					//fprintf(file,"\"\n%12s","\"");
					//fprintf(file,"\"\n%12s","\"");
				}
			}
			else if(c=='\"'){
				flag		=	0;
				fprintf(file,"\\%c",c);
			}
			else{
				flag		=	0;
				fprintf(file,"%c",c);
			}

		}
		fprintf(file,"\",");
	}
}


int		out_C_str(rom*r){
	u32*	texts;
	u32		text_addr;
	s32		index;
	u8		*text;
	FILE	*file;
	char	fname[0x50];


	texts	=	(u32*)rom_data(r,r->texts_base);
	if(!texts){
		printf("��Ϸ�ı��Ļ�ָ�����\n");
		return 1;
	}

	sprintf(fname,"%s.c",r->filename);
	file	=	fopen(fname,"w+");

	text	=	(u8*)malloc(1024*10);
	for(index=0;index<0x1350;index++){
		text_addr	=	texts[index];
		if(text_addr&0x80000000)
		{
			text_addr&=(~0x80000000);
			if(!strcpy((char*)text,(char*)rom_data(r,text_addr)))
			{
				continue;
			}
		}
		else
		{
			if(huffman_decode(r,text_addr,text))
			{
				continue;
			}
		}
		out_C_str_(file,text,index);
		fprintf(file,"\n");
	}

	fclose(file);
	free(text);
	return 0;
}




int		main(int c,char**v){
	if(c==1){
		//û���ļ�,Ĭ��ʹ��fe7tlp.gba
		rom_init(&TLP_rom);

		out_C_str(&TLP_rom);

		rom_free(&TLP_rom);
	}
	return 0;
}


