#-*- coding: utf-8 -*-  
#coding=utf-8
import sys

def BINWrite(File,data,addr,len):
	File.seek(addr,0);
	File.write(data);

#�����в���   binwrite.py dstBin srcBin addr [size]



# f = open("test.bin","rb+");
# s = "abcdef";
# BINWrite(f,s,0,len(s));
# f.close();
argc    =   len(sys.argv);
if (argc<4):
	print("�������,��ʽ��,binwrite.py ROM�ļ� �޸��ļ� ʮ�����Ƶ�ַ");
	exit();

dstFile	=	open(sys.argv[1],"rb+");
srcFile	=	open(sys.argv[2],"rb");
address	=	int (sys.argv[3],16);
srcData	=	srcFile.read();
srcFile.close();
BINWrite(dstFile,srcData,address,len(srcData));
dstFile.close();
