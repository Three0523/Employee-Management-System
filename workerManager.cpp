#include "workerManager.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
//构造函数
WorkerManager::WorkerManager() {
    // Ensure members are initialized to avoid using uninitialized values
	this->m_EmpNum = 0;
	this->m_EmpArray = nullptr;
	this->m_FileIsEmpty = true;
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //以输入的方式打开文件
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		//初始化职工人数和职工数组指针
		this->m_EmpNum = 0; //初始化职工人数
		this->m_EmpArray = nullptr; //初始化职工数组指针
		ifs.close(); //关闭文件
		return;
	}

	//2.文件存在但内容为空
	char ch;
	ifs >> ch; //尝试读取一个字符
	if (ifs.eof()) {
		//文件为空
		cout << "文件为空" << endl;
		this->m_EmpNum = 0; //初始化职工人数
		this->m_EmpArray = nullptr; //初始化职工数组指针
		ifs.close(); //关闭文件
		return;
	}
	//文件存在且内容不为空
	this->m_FileIsEmpty = false;
	//3.当文件存在且内容不为空时，统计文件中的职工人数，并将职工信息保存到职工数组中
	int num = this->get_EmpNum(); //统计文件中的职工人数
	cout << "文件中职工人数为: " << num << endl;
	this->m_EmpNum = num; //初始化职工人数

	this->m_EmpArray = new Worker * [this->m_EmpNum]; //开辟职工数组空间
	//将文件中的职工信息保存到职工数组中
	this->init_Emp(); //初始化职工信息
	
}
//析构函数
WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != nullptr) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			delete this->m_EmpArray[i]; //释放职工对象的内存
		}
	}
	delete[] this->m_EmpArray; //释放职工数组空间
	this->m_EmpArray = nullptr; //将职工数组指针置空
}
//保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //以输出的方式打开文件

	for (int i = 0; i < this->m_EmpNum; i++) {
	ofs <<	this->m_EmpArray[i]->m_Id << " " <<
		this->m_EmpArray[i]->m_Name << " " << 
		this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
//展示菜单
void WorkerManager::Show_Menu() {
   
    cout << "欢迎使用职工管理系统" << endl;
    cout << "0.退出管理程序" << endl;
    cout << "1.增加职工信息" << endl;
    cout << "2.显示职工信息" << endl;
    cout << "3.删除职工信息" << endl;
    cout << "4.修改职工信息" << endl;
    cout << "5.查找职工信息" << endl;
    cout << "6.按照编号排序" << endl;
    cout << "7.清空所有文档" << endl;
    cout << endl;
}
//退出程序
void WorkerManager::exitSystem() {
    cout << "退出系统成功 " << endl;
	exit(0); //退出程序
}
//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量" << endl;

	int addNum = 0; //保存用户输入的添加职工数量
	cin >> addNum; //获取用户输入的添加职工数量

    if (addNum > 0) {
        //添加
		//计算添加新空间的大小:新空间的人数 = 原来的人数 + 新添加的人数
		int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        Worker ** newspace = new Worker* [newSize];

		//将原来空间的数据拷贝到新空间
		if (this->m_EmpArray != nullptr) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                newspace[i] = this->m_EmpArray[i];
            }
        }
		//添加新数据
        for (int i = 0; i < addNum; i++) {
			int id;         //职工编号
			string name;    //职工姓名
			int dSelect;    //部门选择

			cout << "请输入第" << i + 1 << "个新职工的编号: ";
            cin >> id;

			cout << "请输入第" << i + 1 << "个新职工的姓名: ";
            cin >> name;

			cout << "请选择第" << i + 1 << "个新职工的部门: " << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			//创建一个worker指针，指向不同类型的职工对象
			Worker* worker = nullptr;
			switch (dSelect)
			{
				case 1:
					worker = new Employee(id, name, dSelect);
					break;
				case 2:
					worker = new Manager(id, name, dSelect);
					break;
				case 3:
					worker = new Boss(id, name, dSelect);
					break;
				default:
					break;
			}
			//将创建的职工对象指针保存到新空间中
			newspace[this->m_EmpNum + i] = worker;//存放指针的数组中，新增的指针
        }

		//释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间的指向
		this->m_EmpArray = newspace;
		//更新职工人数
		this->m_EmpNum = newSize;
		//更新文件是否为空的状态
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名职工" << endl;
		//成功添加后保存到文件中
		this->save();
		
    }

    else {
		cout << "输入有误" << endl;
    }

	//按任意键清屏
	system("pause");
	system("cls");
}
//显示职工
void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo(); //通过职工数组中的指针调用职工对象的showInfo函数，显示职工信息
		}
	}
	system("pause");
	system("cls");
}
//统计文件中的职工人数
int WorkerManager::get_EmpNum() {
    ifstream ifs(FILENAME, ios::in); //以输入的方式打开文件
    if (!ifs.is_open()) {
        return 0;
    }

    int id;
    string name;
    int dId;
    int count = 0; // 使用局部计数器，避免修改对象状态

    while (ifs >> id >> name >> dId) {    //可以读到数据则进行循环
        ++count;
    }
    ifs.close();
    return count;
}
//初始化职工信息
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //以输入的方式打开文件

	int id;
	string name;
	int dId;
	int index = 0; //职工数组的索引

	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = nullptr;

		if (dId == 1) {			//普通员工
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {	//经理
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3) {	//老板
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker; //将创建的职工对象指针保存到职工数组中
		index++;
	}
	
	ifs.close();

}
//判断职工是否存在，如果存在返回职工在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id) {
	int index = -1; //默认职工不存在
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i; //职工存在，记录职工在数组中的位置
			break;
		}
	}

	return index; //返回职工在数组中的位置，如果不存在返回-1
}
//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		int id; //保存用户输入的要删除的职工编号
		cout << "请输入要删除的职工编号: ";
		cin >> id;
		int index = this->IsExist(id); //判断职工是否存在，并获取职工在数组中的位置
		if (index != -1) { //职工存在
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1]; //将要删除的职工后面的职工指针前移
			}
			this->m_EmpNum--; //更新职工人数
			this->save(); //保存到文件中
			cout << "删除成功" << endl;

			if (this->m_EmpNum == 0) { //如果删除后职工人数为0，更新文件是否为空的状态
				this->m_FileIsEmpty = true;
			}
		}
		else {
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");

}
//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		int id; //保存用户输入的要修改的职工编号
		cout << "请输入要修改的职工编号: ";
		cin >> id;
		int index = this->IsExist(id); //判断职工是否存在，并获取职工在数组中的位置
		if (index != -1) { //职工存在
			delete this->m_EmpArray[index]; //删除原有职工对象，释放内存
			int newId;         //新的职工编号
			string newName;    //新的职工姓名
			int dSelect;       //新的部门选择
			cout << "请输入新的职工编号: ";
			cin >> newId;
			cout << "请输入新的职工姓名: ";
			cin >> newName;
			cout << "请选择新的部门: " << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker* worker = nullptr;
			switch (dSelect)
			{
				case 1:
					worker = new Employee(newId, newName, dSelect);
					break;
				case 2:
					worker = new Manager(newId, newName, dSelect);
					break;
				case 3:
					worker = new Boss(newId, newName, dSelect);
					break;
				default:
					break;
			}
			this->m_EmpArray[index] = worker; //将新的职工对象指针保存到职工数组中
			this->save(); //保存到文件中
			cout << "修改成功" << endl;
		}
		else {
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入查找的方式: " << endl;
		cout << "1.按照职工编号查找 " << endl;
		cout << "2.按照职工姓名查找 " << endl;

		int select = 0; //保存用户输入的查找方式
		cin >> select;

		if (select == 1) {
			int id; //保存用户输入的要查找的职工编号
			cout << "请输入要查找的职工编号: ";
			cin >> id;
			int index = this->IsExist(id); //判断职工是否存在，并获取职工在数组中的位置
				if (index != -1) { //职工存在
					cout << "查找成功，职工信息如下: " << endl;
					this->m_EmpArray[index]->showInfo(); //显示职工信息
				}
				else {
					cout << "查找失败，未找到该职工" << endl;
				}
		}
		else if (select == 2) {
			string name; //保存用户输入的要查找的职工姓名
			cout << "请输入要查找的职工姓名: ";
			cin >> name;
			//加入判断是否查找到的标准
			bool found = false; //默认未找到

			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) { //职工存在
					cout << "查找成功，职工信息如下: " << endl;
					bool found = true; //更新找到的状态
					this->m_EmpArray[i]->showInfo(); //显示职工信息
				}
			}
			if (found) { //如果未找到
				cout << "查找失败，未找到该职工" << endl;
			}
		}
		else {
			cout << "输入有误,请重新输入！" << endl;
		}
	}
	system("pause");
	system("cls");
}	
//排序职工
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");

	}
	else {
		cout << "请选择排序方式: " << endl;
		cout << "1.按照职工编号升序" << endl;
		cout << "2.按照职工编号降序" << endl;
		
		int select = 0; //保存用户输入的排序方式
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++) {
			int minOrMaxIndex = i; //记录当前轮次的最小或最大职工的索引
			if (select == 1) { //按照职工编号升序
				for (int j = i + 1; j < this->m_EmpNum; j++) {
					if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[minOrMaxIndex]->m_Id) {
						minOrMaxIndex = j; //更新最小职工的索引
					}
				}
			}
			else if (select == 2) { //按照职工编号降序
				for (int j = i + 1; j < this->m_EmpNum; j++) {
					if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[minOrMaxIndex]->m_Id) {
						minOrMaxIndex = j; //更新最大职工的索引
					}
				}
			}
			else {
				cout << "输入有误,请重新输入！" << endl;
				return;
			}
			//如果当前轮次的最小或最大职工的索引不是当前职工的索引，则交换职工指针
			if (minOrMaxIndex != i) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMaxIndex];
				this->m_EmpArray[minOrMaxIndex] = temp;

			}
		}
		this->save(); //保存到文件中
		cout << "排序成功" << endl;
		cout << "排序后的职工信息如下: " << endl;
		this->Show_Emp(); //显示排序后的职工信息
	}
	
}
//清空文件
void WorkerManager::Clean_File() {
	cout << "确认清空吗？" << endl;
	cout << "1.确认" << endl;
	cout << "2.取消" << endl;
	int select = 0; //保存用户输入的选择
	cin >> select;
	if (select == 1) {
		int select2 = 0; //保存用户输入的二次确认选择
		cout << "你确定要清空吗？" << endl;
		cout << "确认请按1，否则请按2" << endl;
		cin >> select2;
		if (select2 == 1) {
			int select3 = 0; //保存用户输入的三次确认选择
			cout << "你真的确定要清空吗？" << endl;
			cout << "一但清空，你将失去所有数据（很久很久）！" << endl;
			cout << "确认请按1，否则请按2" << endl;
			cin >> select3;
			if (select3 == 1) {
				ofstream ofs(FILENAME, ios::trunc); //以截断的方式打开文件，清空文件内容
				ofs.close();
				if (this->m_EmpArray != nullptr) {
					for (int i = 0; i < this->m_EmpNum; i++) {
						delete this->m_EmpArray[i]; //释放职工对象的内存
					}
					delete[] this->m_EmpArray; //释放职工数组空间
					this->m_EmpArray = nullptr; //将职工数组指针置空
					this->m_EmpNum = 0; //更新职工人数

				}
				this->m_FileIsEmpty = true; //更新文件是否为空的状态
				cout << "清空成功" << endl;
			}
			else if (select3 == 2) {
				cout << "已取消清空操作" << endl;
			}
			else {
				cout << "输入有误,请重新输入！" << endl;
			}
		}
		else if (select2 == 2) {
			cout << "已取消清空操作" << endl;
		}
		else {
			cout << "输入有误,请重新输入！" << endl;
		}
	}
	else if (select == 2) {
		cout << "已取消清空操作" << endl;
	}
	else {
		cout << "输入有误,请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}