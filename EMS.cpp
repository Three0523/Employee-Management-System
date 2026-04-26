/*Employee Management System*/

//职工类型：普通员工、经理，老板

         /*系统功能*/

//      0.退出管理程序
//      1.增加员工信息
//      2.显示职工信息
//      3.删除员工信息
//      4.修改员工信息
//      4.修改员工信息
//      5.查找员工信息
//      6.按照编号排序                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//      7.清空所有文档

#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;
int main() {

	////测试代码
	//Worker* worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker; //释放内存

	//worker = new Manager(2, "李四", 2);
	//worker->showInfo();
	//delete worker; //释放内存

	//worker = new Boss(3, "王五", 3);
	//worker->showInfo();
	//delete worker; //释放内存
    
    //实例化管理者对象
    WorkerManager wm;

	int choice = 0; //用户输入的选择
    while (true) {
        //调用展示菜单成员函数
        //展示菜单:
        wm.Show_Menu();

		cout << "请输入您的选择: ";
		cin >> choice;  //获取用户输入的选择`

        switch (choice) {
            case 0:
                //cout << "退出管理程序" << endl;
                return 0; //退出程序
            case 1:
                cout << "正在增加员工信息……" << endl;
				wm.Add_Emp();
                //调用增加员工信息的函数
                break;
            case 2:
                cout << "以下为职工信息：" << endl;
				wm.Show_Emp();
                //调用显示职工信息的函数
                break;
            case 3:
                //cout << "删除员工信息" << endl;
                //调用删除员工信息的函数
				wm.Del_Emp();
                break;
            case 4:
                //cout << "修改员工信息" << endl;
                //调用修改员工信息的函数
				wm.Mod_Emp();
                break;
            case 5:
                //cout << "查找员工信息" << endl;
                //调用查找员工信息的函数
				wm.Find_Emp();
                break;
            case 6:
                //cout << "按照编号排序" << endl;
                //调用按照编号排序的函数
				wm.Sort_Emp();
                break;
            case 7:
                cout << "清空所有文档" << endl;
                //调用清空所有文档的函数
				wm.Clean_File();
                break;
            default:
                cout << "无效的选择，请重新输入。" << endl;
				system("pause"); //暂停系统，等待用户按键
				system("cls"); //清屏
                
		}
    }

    

    return 0;
}

