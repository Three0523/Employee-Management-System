
//菜单
//增删查改
//与文件交互

#pragma once        //防止头文件重复包含
#include <iostream>     //包含输入输出流头文件
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>

#define FILENAME "empFile.txt" //定义文件名

using namespace std;    //使用标准命名空间

class WorkerManager {
public:
    //记录职工人数
    int m_EmpNum;
    //职工数组指针
    Worker** m_EmpArray;
    //判断文件是否为空
	bool m_FileIsEmpty;
	//统计文件中的职工人数
	int get_EmpNum();


    
    //初始化
	void init_Emp();
    //退出系统函数声明
    void exitSystem();
    //添加职工
    void Add_Emp();
	//显示职工
	void Show_Emp();
	//删除职工
	void Del_Emp();
	//判断职工是否存在，如果存在返回职工在数组中的位置，不存在返回-1
	int IsExist(int id);
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
    //排序职工
    void Sort_Emp();
	//清空文件
	void Clean_File();

    //展示菜单
    void Show_Menu();

    //构造函数
    WorkerManager();
    //析构函数
    ~WorkerManager();
    
    //保存文件
	void save();
	
};

