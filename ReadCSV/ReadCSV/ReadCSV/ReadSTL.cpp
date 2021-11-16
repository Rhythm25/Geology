#include "ReadSTL.h"
void ReadSTL::ReadSTLFile(const char* filename) {
	Head head;
	FILE* fp;
	
	fp = fopen(filename, "rb");

	if (fp != NULL)
	{
		fread(head.partName, 80, 1, fp);//获取部件名
		fread(&head.faceNum, 4, 1, fp);//获取三角面片的数目
	}

	Face* faces = (Face*)malloc(head.faceNum * sizeof(Face));//根据三角面片的数目，创建一个Face类型的数组

	//循环读取三角面片数据
	for (int i = 0; i < head.faceNum; i++)
	{
		fread(&faces[i].normal, 12, 1, fp);//读取法线数据
		fread(&faces[i].p1, 12, 1, fp);//读取顶点1的数据
		fread(&faces[i].p2, 12, 1, fp);//读取顶点2的数据
		fread(&faces[i].p3, 12, 1, fp);//读取顶点3的数据
		fread(&faces[i].info, 2, 1, fp);//读取保留项数据，这一项一般没什么用，这里选择读取是为了移动文件指针
	}

	fclose(fp);

	printf("STL文件解析如下：\n");
	printf("三角形数目：");
	printf("%d\n", head.faceNum);
	printf("各面的顶点和法线数据如下：\n");

	//在控制台上输出STL文件的数据
	for (int i = 0; i < head.faceNum; i++)
	{
		printf("面%d\n", i + 1);
		printf("法线：\n");
		printf("%f  %f  %f\n", faces[i].normal.i, faces[i].normal.j, faces[i].normal.k);
		printf("顶点数据：\n");
		printf("%f  %f  %f\n", faces[i].p1.x, faces[i].p1.y, faces[i].p1.z);
		printf("%f  %f  %f\n", faces[i].p2.x, faces[i].p2.y, faces[i].p2.z);
		printf("%f  %f  %f\n", faces[i].p2.x, faces[i].p2.y, faces[i].p2.z);
	}


}