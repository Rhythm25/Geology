#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static class ReadSTL
{
public:
	struct Head
	{
		char partName[80];//�������
		int  faceNum;//�����Ŀ
	};

	//�㣬����float���͵ģ���СΪ12�ֽ�
	struct Point
	{
		float x;
		float y;
		float z;
	};

	//����
	struct Normal
	{
		float i;
		float j;
		float k;
	};

	//�����棬��һ�����ߣ������㣬��һ�����ֽڵı����һ��50�ֽ�
	struct Face
	{
		Normal normal;
		Point  p1;
		Point  p2;
		Point  p3;
		char  info[2];//�������ݣ����Բ��ù�
	};

	static void ReadSTLFile(const char* filename);
};

