#include <iostream>
#include <unistd.h>
#include <string>
const int MAX = 1000;

// 第三步 1)设计联系人结构体
struct Person {
    // 姓名
    std::string m_Name;
    // 性别 1 男 2 女
    int m_Sex;// 设计巧妙点2: 防止用户输入其他的数据，将性别规定用整型1和2来分别限制男和女
    // 年龄
    int m_Age;
    // 电话
    std::string m_Phone;
    // 住址
    std::string m_Addr;
};

// 第三步 2)设计通讯录结构体
struct Addressbooks {
    // 通讯录中保存的联系人数组
    struct Person personArray[MAX];
    // 通讯录中当前记录的联系人个数
    int m_Size;
};

// 第一步 封装函数显示该界面 如 void showMenu()
// 第一步 菜单界面
void showMenu() {
    std::cout << "*************************" << std::endl;
    std::cout << "***** 1、添加联系人 *****" << std::endl;
    std::cout << "***** 2、显示联系人 *****" << std::endl;
    std::cout << "***** 3、删除联系人 *****" << std::endl;
    std::cout << "***** 4、查找联系人 *****" << std::endl;
    std::cout << "***** 5、修改联系人 *****" << std::endl;
    std::cout << "***** 6、清空联系人 *****" << std::endl;
    std::cout << "***** 0、退出通讯录 *****" << std::endl;
    std::cout << "*************************" << std::endl;
}

// 第三步 4)封装添加联系人函数
void addPerson(Addressbooks* abs) {

    // 判断通讯录是否已满 如果满了就不要再添加
    if(abs->m_Size == MAX) {
        std::cout << "通讯录已满，无法添加" << std::endl;
        return;
    } else {
        // 添加具体联系人

            // 姓名
            std::string name;
            std::cout << "请输入姓名: " << std::endl;
            std::cin >> name;
            abs->personArray[abs->m_Size].m_Name = name;// 将输入的姓名赋给真正通讯录结构体变量中联系人结构体中的联系人姓名
            // 并且对通讯录中的人员个数做增加操作

            // 性别
            std::cout << "请输入性别: " << std::endl;
            std::cout << "1 ----- 男" << std::endl;
            std::cout << "2 ----- 女" << std::endl;
            int sex = 0;

            while (true) {// 设计巧妙点4: 让用户无限输入数字，直到输入正确的1或者2对应的性别是男和女为止
                // 如果输入的是1或者2 可以退出循环，因为输入的是正确的值
                // 如果输入有误，重新输入
                std::cin >> sex;
                if (sex == 1 || sex == 2) {
                    abs->personArray[abs->m_Size].m_Sex = sex;// 输入1或者2 将输入的性别赋给真正通讯录结构体变量中联系人结构体中的联系人性别
                    // 并且对通讯录中的人员个数做增加操作
                    break;// 输入正确时可以退出循环
                }
                std::cout << "输入性别有误，请重新输入" << std::endl;
            }

            // 年龄
            std::cout << "请输入年龄: " << std::endl;
            int age = 0;
            while (true) {
                std::cin >> age;
                if (age > 0 && age < 150) {
                    abs->personArray[abs->m_Size].m_Age = age;// 输入0-150 将输入的年龄赋给真正通讯录结构体变量中联系人结构体中的联系人年龄
                    // 并且对通讯录中的人员个数做增加操作
                    break;
                }
                std::cout << "输入年龄有误，请重新输入" << std::endl;
            }

            // 电话
            std::cout << "请输入联系电话: " << std::endl;
            std::string phone;
            std::cin >> phone;
            abs->personArray[abs->m_Size].m_Phone = phone;// 输入电话号码 将输入的电话号码赋给真正通讯录结构体变量中联系人结构体中的联系人电话号码
                    // 并且对通讯录中的人员个数做增加操作
            
            // 住址
            std::cout << "请输入家庭住址: " << std::endl;
            std::string address;
            std::cin >> address;
            abs->personArray[abs->m_Size].m_Addr = address;// 输入家庭住址 将输入的家庭住址赋给真正通讯录结构体变量中联系人结构体中的联系人家庭住址
                    // 并且对通讯录中的人员个数做增加操作

            // 更新通讯录人数
            abs->m_Size++;

            std::cout << "添加成功" << std::endl;
    }
}

// 第四步 显示所有联系人
void showPerson(Addressbooks* abs) {
    //先判断通讯录中人数是否为0 如果为0 提示记录为空， 如果不为0，显示记录的联系人信息
    if (abs->m_Size == 0) {
        std::cout << "当前记录为空" << std::endl;
    } else {
        for (int i = 0; i < abs->m_Size; i++) {
            std::cout << "姓名: " << abs->personArray[i].m_Name << "\t";//设计巧妙6：采用水平制表符而不是换行操作，使得页面显示的好看一点
            std::cout << "性别: " << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";//巧妙设计7: 采用三目运算符而不是if/else判断，使得代码看起来很简洁
            std::cout << "年龄: " << abs->personArray[i].m_Age<< "\t";
            std::cout << "电话: " << abs->personArray[i].m_Phone << "\t";
            std::cout << "住址: " << abs->personArray[i].m_Addr << std::endl;
        }
    }
}

// 第五步 1)封装检测联系人是否存在 如果存在，返回联系人在通讯录中的位置，不存在返回-1
// 设计巧妙7：要先判断联系人是否存在才能做删除、修改、清空联系人操作
int isExist(Addressbooks* abs, std::string name) {// 传入的参数1是通讯录，参数2是对比的姓名
    for (int i = 0; i < abs->m_Size; i++) {
        // 找到用户输入的姓名
        if (abs->personArray[i].m_Name == name) {
            return i; // 找到了，返回这个人在数组中的下标编号
        }
    }
    return -1; // 如果遍历结束都没有找到 返回-1
}

// 第五步 2)封装删除联系人函数
void deletePerson(Addressbooks* abs) {
    std::cout << "请输入您要删除的联系人" << std::endl;
    std::string name;
    std::cin >> name;
    
    // ret == -1 未查到
    // ret != -1 查到了
    int ret = isExist(abs, name);

    if (ret != -1) {
        // 查到此人 进行删除操作
        // 设计巧妙8: 用到数据结构的知识: 数组的删除
        for (int i = ret; i < abs->m_Size; i++) {
            abs->personArray[i] = abs->personArray[i + 1];// 数据前移 后一数据赋值给前一数据
        }
        abs->m_Size--;// 更新通讯录中的人员数

        std::cout << "删除成功!" << std::endl;

    } else {
        std::cout << "查无此人!" << std::endl;
    }
}

// 第六步 查找指定联系人信息 
// 1)封装查找联系人函数
void findPerson(Addressbooks* abs) {
    std::cout << "请输入您要查找的联系人: " << std::endl;
    std::string name;
    std::cin >> name;

    //判断指定的联系人是否存在通讯录中
    int ret = isExist(abs, name);

    if (ret != -1) {// 找到联系人
        std::cout << "姓名: " << abs->personArray[ret].m_Name << "\t";
        std::cout << "性别: " << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
        std::cout << "年龄: " << abs->personArray[ret].m_Age << "\t";
        std::cout << "电话: " << abs->personArray[ret].m_Phone << "\t";
        std::cout << "住址: " << abs->personArray[ret].m_Addr << std::endl;
    } else {// 未找到联系人
        std::cout << "查无此人!" << std::endl;
    }
}

// 第七步 修改指定联系人信息
void modifyPerson(Addressbooks* abs) {
    std::cout << "请输入您要修改的联系人" << std::endl;
    std::string name;
    std::cin >> name;
    
    //判断要修改的联系人是否存在通讯录中
    int ret = isExist(abs, name);

    if (ret != -1) {// 找到指定要修改的联系人
        
        // 姓名
        std::string name;
        std::cout << "请输入姓名: " << std::endl;
        std::cin >> name;
        abs->personArray[ret].m_Name = name;
        
        // 性别
        std::cout << "请输入性别: " << std::endl;
        std::cout << "1---男 2---女" << std::endl;
        int sex = 0;

        while (true) {
            std::cin >> sex;
            if (sex == 1 || sex == 2) {
                //输入正确 退出循环输入
                abs->personArray[ret].m_Sex = sex;
                break;
            }
            std::cout << "输入有误，请重新输入" << std::endl;
        }
        
        // 年龄
        std::cout << "请输入年龄: " << std::endl;
        int age = 0;

        while (true) {
            std::cin >> age;
            if (age > 0 && age < 150) {
                //输入正确 退出循环输入
                abs->personArray[ret].m_Age = age;
                break;
            }
            std::cout << "输入有误，请重新输入" << std::endl;
        }

        // 电话
        std::cout << "请输入联系电话: " << std::endl;
        std::string phone;
        std::cin >> phone;
        abs->personArray[ret].m_Phone = phone;

        // 住址
        std::cout << "请输入家庭住址: " << std::endl;
        std::string address;
        std::cin >> address;
        abs->personArray[ret].m_Addr = address;

        std::cout << "修改成功" << std::endl;
    } else {// 未找到联系人
        std::cout << "查无此人!" << std::endl;
    }
}

// 第八步 清空联系人
void cleanPerson(Addressbooks* abs) {
    std::cout << "确定要清空吗？Y/N" << std::endl;
    char str;
    std::cin >> str;
    while (str == 'Y' || str == 'y') {
        abs->m_Size = 0; // 设计巧妙8：将当前记录联系人数量置为0 做逻辑清空操作
        std::cout << "通讯录已清空！" << std::endl;
        break;
    }
}

int main()
{
    // 第三步 3)main函数中创建通讯录结构体变量
    Addressbooks abs;
    // 初始化通讯录中当前人员个数
    abs.m_Size = 0;

    while (true) {// 设计巧妙点1：用一个while死循环使得用户除了输入0退出系统外，输入其他的数字都将继续显示菜单执行相应的功能
        // 第一步 在main函数中调用封装好的函数
        // 第一步 菜单调用
        showMenu();

        // 第二步 实现退出功能
        // 第二步 思路：根据用户不同的选择，进入不同的功能，可以选择switch分支结构，将整个架构进行搭建
        // 第二步 当用户选择0时，执行退出，选择其他先不做操作，也不会退出程序
        int select = 0;// 创建用户选择输入的变量
        std::cin >> select;// 输入选择
        switch (select)
        {
        case 1: // 1、添加联系人
            // 第三步 4)调用封装好的添加联系人函数并将通讯录结构体变量传递进去
            addPerson(&abs);// 设计巧妙点3: 用地址传递的方法将通讯录结构体变量传递给添加联系人函数才会真正的修改通讯录 修饰实参
            //如果用值传递不会修改它的值

            break;
        case 2: // 2、显示联系人
            showPerson(&abs);// 调用封装好的显示联系人函数
            break;
        case 3: // 3、删除联系人
        //{// 设计巧妙8: 当在switch中一个case下测试很长的某段代码时会编译报错，提示代码段过长，可以使用花括号把这段代码块括起来表示一个代码段
            //测试检测联系人是否存在代码
            // std::cout << "请输入删除联系人姓名: " << std::endl;
            // std::string name;
            // std::cin >> name;
            // if (isExist(&abs, name) == -1) {
            //     std::cout << "查无此人!" << std::endl;
            // } else {
            //     std::cout << "找到此人!" << std::endl;
            // }
        //}
            deletePerson(&abs);
            break;
        case 4: // 4、查找联系人
            findPerson(&abs);
            break;
        case 5: // 5、修改联系人
            modifyPerson(&abs);
            break;
        case 6: // 6、清空联系人
            cleanPerson(&abs);
            break;
        case 0: // 0、退出通讯录
            std::cout << "欢迎下次使用" << std::endl;
            return 0;
            break; 
        default:
            break;
        }
    }

    return 0;
}