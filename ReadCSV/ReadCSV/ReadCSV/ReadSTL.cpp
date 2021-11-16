#include "ReadSTL.h"
void ReadSTL::ReadSTLFile(const char* filename) {
	Head head;
	FILE* fp;
	
	fp = fopen(filename, "rb");

	if (fp != NULL)
	{
		fread(head.partName, 80, 1, fp);//��ȡ������
		fread(&head.faceNum, 4, 1, fp);//��ȡ������Ƭ����Ŀ
	}

	Face* faces = (Face*)malloc(head.faceNum * sizeof(Face));//����������Ƭ����Ŀ������һ��Face���͵�����

	//ѭ����ȡ������Ƭ����
	for (int i = 0; i < head.faceNum; i++)
	{
		fread(&faces[i].normal, 12, 1, fp);//��ȡ��������
		fread(&faces[i].p1, 12, 1, fp);//��ȡ����1������
		fread(&faces[i].p2, 12, 1, fp);//��ȡ����2������
		fread(&faces[i].p3, 12, 1, fp);//��ȡ����3������
		fread(&faces[i].info, 2, 1, fp);//��ȡ���������ݣ���һ��һ��ûʲô�ã�����ѡ���ȡ��Ϊ���ƶ��ļ�ָ��
	}

	fclose(fp);

	printf("STL�ļ��������£�\n");
	printf("��������Ŀ��");
	printf("%d\n", head.faceNum);
	printf("����Ķ���ͷ����������£�\n");

	//�ڿ���̨�����STL�ļ�������
	for (int i = 0; i < head.faceNum; i++)
	{
		printf("��%d\n", i + 1);
		printf("���ߣ�\n");
		printf("%f  %f  %f\n", faces[i].normal.i, faces[i].normal.j, faces[i].normal.k);
		printf("�������ݣ�\n");
		printf("%f  %f  %f\n", faces[i].p1.x, faces[i].p1.y, faces[i].p1.z);
		printf("%f  %f  %f\n", faces[i].p2.x, faces[i].p2.y, faces[i].p2.z);
		printf("%f  %f  %f\n", faces[i].p2.x, faces[i].p2.y, faces[i].p2.z);
	}


}