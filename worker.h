#pragma once
#include <iostream>
#include <string>
using namespace std;
/*职工分类：普通员工、经理，老板
  职工属性：编号、姓名、部门编号
  职工行为：岗位职责信息描述，获取岗位名称*/


//职工抽象类，故无法实例化对象
class Worker {
public:
	//显示个人信息
	virtual void showInfo() = 0;	//纯虚函数，子类必须重写该函数
	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_Id;			//职工编号
	string m_Name;		//职工姓名
	int m_DeptId;		//职工部门编号
};
