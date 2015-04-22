/*
 * texts.c
 *
 *  Created on: 2015��4��19��
 *      Author: yami
 */


/**
 * @file		texts.c
 * @author		yami
 * @date		2015-04-19 01:13:21
 * @brief
 * ��Щ���ı��޸�
 * ע��
 * 1,����ҪGBK�����ļ�
 * 2,�������
 * 		#ifdef 	(��������text_version.h�������Ϣ)
 * 		#include "�����ı�""
 * 		#endif
 * 	 ��ʽ����,����������
 * 3,
 * 	������ʽ
 * 	[�ı�ID]	=	"�����ı�"
 */

#include "types.h"
#include "text_version.h"

#define		N		+ 0x80000000
#define		TXT		(u32)

u32			texts[] = {
#include		"textpoters.h"
#ifdef	TLP_CN_YAMI_ITEMNAME_
//��yami�ṩ�ķ����ı�,������õĻ�,����text_version.hע�͵�TLP_CN_YAMI_ITEMNAME_,
		//����ɾ����һ��
#include		"yami/item_text.h"
		[0x03F7]	= TXT"��֮��"N,
		TXT"��֮��"N,
		TXT"��֮��"N,

		[ 0x03fa ] =	TXT"����"N,
		[ 0x03fb ] =	TXT"ͻ�̽�"N,
		[ 0x03fc ] =	TXT"�����\x1F"N,
		[ 0x03fd ] =	TXT"�׽�"N,

#endif
		 [0x046C]	=	TXT"��ҩ\x1F"N

};

//u32		texts[] = {
////�ɰ��ָ��,Ϊ�˷���һЩδ�޸ĵ�����
//#include		"textpoters.h"
//
//
//
////����ǲ���
////[0x01B1]	=	TXT"һ��������һ������\x01of justice and dedication.\x01He suffers from deep wounds..." N,
////[0x0B9B]	=	TXT"abc"N,
////[0x04DE]	=	TXT"����"N,
////[0x03F3]	=	TXT"����"N,
//};
