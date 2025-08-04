#include <iostream>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <cstdlib> // 添加system函数所需的头文件

using namespace std;

const int MAX_ITEMS = 19;
const int DEFAULT_WORK_TIME = 1500;  // 测试用较短时间
const int DEFAULT_REST_TIME = 300;   // 测试用较短时间

int showMenu() {
    char choice;
    do {
        cout << "欢迎来到WaveTime软件！" << endl << endl;
        cout << "菜单" << endl;
        cout << "【1】开始" << endl;
        cout << "【2】帮助" << endl;
        cout << "【3】关于" << endl;
        cout << "请选择模式：";
        choice = getch();
        cout << choice << endl;
    } while (choice < '1' || choice > '3');

    return choice - '0';
}

void initializeForm(string formSurface[][3], int formBackend[][2]) {
    for (int i = 0; i < MAX_ITEMS; i += 2) {
        formSurface[i][0] = "否";
        formBackend[i][0] = 0;

        if (i > 0) {
            formSurface[i-1][0] = "否";
        }

        formSurface[i][1] = "空";
        if (i > 0) {
            formSurface[i-1][1] = "休息";
        }

        ostringstream oss;
        oss << DEFAULT_WORK_TIME << "s";
        formSurface[i][2] = oss.str();
        formBackend[i][1] = DEFAULT_WORK_TIME;

        if (i > 0) {
            ostringstream oss2;
            oss2 << DEFAULT_REST_TIME << "s";
            formSurface[i-1][2] = oss2.str();
            formBackend[i-1][1] = DEFAULT_REST_TIME;
        }
    }
}

void displayForm(const string& listName, const string formSurface[][3]) {
    cout << "\033c时间表名称：" << listName << endl;
    for (int i = 0; i < MAX_ITEMS; i++) {
        cout << "完成:" << formSurface[i][0]
             << "  项目:" << formSurface[i][1]
             << " 时间:" << formSurface[i][2] << endl;
    }
}

void editForm(string formSurface[][3]) {
    for (int i = 0; i < MAX_ITEMS; i += 2) {
        cout << "请输入第" << (i/2 + 1) << "项事件（结束请输入\"none\"）：";
        cin >> formSurface[i][1];

        if (formSurface[i][1] == "none") {
            formSurface[i][1] = "空";
            cout << "\033c";
            break;
        }
    }
}

void runTimer(const string& listName, string formSurface[][3], int formBackend[][2]) {
    for (int i = 0; i < MAX_ITEMS && formBackend[i][1] > 0; i++) {
        int remainingTime = formBackend[i][1];

        while (remainingTime > 0) {
            Sleep(1000);
            remainingTime--;

            ostringstream oss;
            oss << remainingTime << "s";
            formSurface[i][2] = oss.str();
            formBackend[i][1] = remainingTime;

            displayForm(listName, formSurface);
        }

        // 计时结束后启动alarm.exe
        system("alarm.exe");

        // 更新完成状态
        formSurface[i][0] = "是";
        displayForm(listName, formSurface);
    }
}

void createSchedule() {
    cout << "\033c时间表名称：";
    string listName;
    cin >> listName;

    string formSurface[MAX_ITEMS][3];
    int formBackend[MAX_ITEMS][2];

    initializeForm(formSurface, formBackend);

    char choice = 'n';
    while (choice != '2') {
        displayForm(listName, formSurface);
        cout << endl << "菜单" << endl;
        cout << "【1】编辑" << endl;
        cout << "【2】开始" << endl;

        choice = getch();
        cout << endl;

        if (choice == '1') {
            editForm(formSurface);
        }
    }

    runTimer(listName, formSurface, formBackend);
}

void showHelp() {
    // 这里添加打开帮助文档的代码
    // 例如：system("start WaveTimeHelp.docx");
    cout << "\033c帮助功能开发中..." << endl;
    cout << "按任意键返回主菜单...";
    getch();
}


void showAbout() {
    cout << "\033c";
    cout << "========================================" << endl;
    cout << "          WaveTime 时间管理工具         " << endl;
    cout << "              版本 1.0.0               " << endl;
    cout << "========================================" << endl << endl;

    cout << "◆ 功能特色：" << endl;
    cout << "  - 基于番茄工作法的时间管理" << endl;
    cout << "  - 支持自定义任务列表" << endl;
    cout << "  - 实时倒计时显示" << endl << endl;

    cout << "◆ 技术参数：" << endl;
    cout << "  - 默认工作时间: 25分钟" << endl;
    cout << "  - 默认休息时间: 5分钟" << endl;
    cout << "  - 最大任务数: 10个" << endl << endl;

    cout << "◆ 开发信息：" << endl;
    cout << "  作者: 蔚澜Waverly" << endl;
    cout << "  联系方式: Uild913@Outlook.com" << endl;
    cout << "  项目主页: https://github.com/weilanfurry/Wavetime" << endl << endl;

    cout << "◆ 版权声明：" << endl;
    cout << "  GPL2 License - 2025" << endl << endl;

    cout << "========================================" << endl;
    cout << "按任意键返回主菜单...";
    getch();
}

int main() {
    int selection = showMenu();
    switch (selection) {
        case 1: createSchedule(); break;
        case 2: showHelp(); break;
        case 3: showAbout(); break;
    }
    return 0;
}
