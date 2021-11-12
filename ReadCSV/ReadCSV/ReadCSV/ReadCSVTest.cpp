﻿// ReadCSV.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ReadCSV.h"
#include "IDWCoef.h"

void ExpDataWrite(const vector<vector<vec3>> &xyz, string filename)
{
    /*const char* filename1 = "1.txt";
    FILE* fp1 = fopen(filename1, "w");
    if (fp1 == NULL) 
    {
        puts("Fail to open file!");
        exit(1);
    }

    fprintf(fp1, "v 0.000000 0.000000 0.000000\n");
    fprintf(fp1, "v 1.000000 0.000000 0.000000\n");
    fprintf(fp1, "v 0.000000 1.000000 0.000000\n");
    fprintf(fp1, "v 1.000000 1.000000 0.000000\n");
    

    fprintf(fp1, "f 1 2 3\n");
    fprintf(fp1, "f 2 4 3\n");
    
    fclose(fp1);
    printf("Data saved.\n");*/
    
    FILE* fp = fopen((filename+".txt").c_str(), "w");
    if (fp == NULL)
    {
        puts("Fail to open file!");
        exit(1);
    }
    for (int i = 0; i < xyz.size(); i++) {
        for (int j = 0; j < xyz[i].size(); j++) {
            fprintf(fp, "v %lf %lf %lf\n",xyz[i][j][0], xyz[i][j][1], xyz[i][j][2]);
        }
    }

    int frontNum = 0;
    for (int i = 0; i < xyz.size()-1; i++) {
        for (int j = 0; j < xyz[i].size()-1; j++) {
            fprintf(fp, "f %d %d %d\n", frontNum+j+1, frontNum + j + 2, frontNum+ xyz[i].size()+j+1);
            fprintf(fp, "f %d %d %d\n", frontNum + j + 2, frontNum + xyz[i].size() + j + 2, frontNum + xyz[i].size() + j + 1);
            
        }
        frontNum += xyz[i].size();
    }
    fclose(fp);
    printf("Data saved.\n");

    char szcmd[256] = "cmd /c rename ";
    strcat(szcmd, (filename+".txt").c_str());
    strcat(szcmd, " ");
    strcat(szcmd, (filename + ".obj").c_str());
    system(szcmd);
}


int main()
{
   /* string fileName = "hole_dhd_collar.csv";//stores all information about xy positions
    vector<vector<string>> allStringPos=ReadCSV::ReadFile(fileName);
    fileName = "hole_dhd_geology.csv";
    vector<vector<string>> allStringGeo = ReadCSV::ReadFile(fileName);
    fileName = "hole_dhd_survey.csv";
    vector<vector<string>> allStringAngle = ReadCSV::ReadFile(fileName);

    vector<double> x, y, z;
    ReadCSV::FindXYZForSeam(allStringGeo, allStringPos, allStringAngle, 6, x, y, z);*/
    string filename = "2";
    vector<vector<vec3>> xyz;
    xyz.resize(10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            vec3 xyzOne(j, i, i+j);
            xyz[i].push_back(xyzOne);
        }
    }


    ExpDataWrite(xyz,filename);

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
