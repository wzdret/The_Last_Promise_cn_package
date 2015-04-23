/*
 * texts.c
 *
 *  Created on: 2015年4月19日
 *      Author: yami
 */


/**
 * @file		texts.c
 * @author		yami
 * @date		2015-04-19 01:13:21
 * @brief
 * 这些是文本修改
 * 注意
 * 1,必须要GBK保存文件
 * 2,最好是以
 * 		#ifdef 	(翻译者在text_version.h定义的信息)
 * 		#include "翻译文本""
 * 		#endif
 * 	 形式来下,下面有例子
 * 3,
 * 	翻译形式
 * 	[文本ID]	=	"翻译文本"
 */

#include "types.h"
#include "text_version.h"

#define		N		+ 0x80000000
#define		TXT		(u32)

u32			texts[] = {
#include		"textpoters.h"
#ifdef	TLP_CN_YAMI_ITEMNAME_
//有yami提供的翻译文本,如果不用的话,请在text_version.h注释掉TLP_CN_YAMI_ITEMNAME_,
		//或者删掉那一行
#include		"yami/item_text.h"
		[0x03F7]	= TXT"铁之大剑"N,
		TXT"钢之大剑"N,
		TXT"银之大剑"N,

		[ 0x03fa ] =	TXT"毒剑"N,
		[ 0x03fb ] =	TXT"突刺剑"N,
		[ 0x03fc ] =	TXT"玛尼☆卡缇\x1F"N,
		[ 0x03fd ] =	TXT"雷剑"N,

#endif
		 [0x046C]	=	TXT"伤药\x1F"N,
		 [0x0491]	=	TXT"游侠骑士"N,
		 [0x0826]	=
				 TXT"\x0B\x10\x16\x01\x01"
				 "所以啊, 你在逗我?"
				 "\x01"
				 "你个二货...\x03\x01"
				 "打死你"
				 "\x01"
				 "烧死你\x03"N,

				 [0x01B1]	=TXT
						 "对待敌人是特别冲动"
						 "\x01"
						 "of justice and dedication."
						 "\x01"
						 "He suffers from deep wounds..."N,
};

//u32		texts[] = {
////旧版的指针,为了方便一些未修改的玩意
//#include		"textpoters.h"
//
//
//
////这个是测试
////[0x01B1]	=	TXT"一个男人是一个二货\x01of justice and dedication.\x01He suffers from deep wounds..." N,
////[0x0B9B]	=	TXT"abc"N,
////[0x04DE]	=	TXT"二货"N,
////[0x03F3]	=	TXT"铁剑"N,
//};
