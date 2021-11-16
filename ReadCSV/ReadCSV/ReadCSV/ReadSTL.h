#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static class ReadSTL
{
public:
	struct Head
	{
		char partName[80];//零件名称
		int  faceNum;//面的数目
	};

	//点，三个float类型的，大小为12字节
	struct Point
	{
		float x;
		float y;
		float z;
	};

	//法线
	struct Normal
	{
		float i;
		float j;
		float k;
	};

	//三角面，由一个法线，三个点，和一个两字节的保留项，一共50字节
	struct Face
	{
		Normal normal;
		Point  p1;
		Point  p2;
		Point  p3;
		char  info[2];//保留数据，可以不用管
	};

	static void ReadSTLFile(const char* filename);
};

