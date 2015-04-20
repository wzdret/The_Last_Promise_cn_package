/*
 * export_item_txt_number.c
 *
 *  Created on: 2015��4��20��
 *      Author: yami
 */


/**
 * @file		export_item_txt_number.c
 * @author		yami
 * @date		2015-04-20 11:11:13
 * @brief
 * �йص��ߵ��ı��������
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
}rom;


rom		TLP_rom	=	{
		"fe7tlp.gba",0,0
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



typedef struct{
	u16		name_number;
	u16		desc;
	u8		u4_[32];
}item;



int		TLP_item_txt_export(rom*r,u32 addr){
	item*		item_ptr;
	item*		item_base_ptr;
	int			i;

	item_base_ptr	=	(item*)rom_data(r,addr);
	item_ptr		=	item_base_ptr;
	if(!item_ptr){
		printf("��ַ(0x%8X)����,������gba rom�ĵ�ַ��Χ\n",addr);
		return 1;
	}

	item_ptr		=	item_base_ptr;
	printf("//%s\n","������");
	for(i=0;i<0x100;i++){
		printf("\t[0x%04X]\t=\t\t//%02X\n",item_ptr->name_number,i);
		item_ptr	++;
	}

	item_ptr		=	item_base_ptr;
	printf("//%s\n","��������");
	for(i=0;i<0x100;i++){
		printf("\t[0x%04X]\t=\t\t//%02X\n",item_ptr->desc,i);
		item_ptr	++;
	}


	return 0;
}



int		main(int c,char**vv){
	if(c==1){
		//memset(&TLP_rom,0,sizeof(TLP_rom));
		if(rom_init(&TLP_rom)){
			return 1;
		}

		//˵�����
		TLP_item_txt_export(&TLP_rom,0x9250000);

		rom_free(&TLP_rom);
	}
	return 0;
}
