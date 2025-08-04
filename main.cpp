#include <iostream>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <cstdlib> // ���system���������ͷ�ļ�

using namespace std;

const int MAX_ITEMS = 19;
const int DEFAULT_WORK_TIME = 1500;  // �����ý϶�ʱ��
const int DEFAULT_REST_TIME = 300;   // �����ý϶�ʱ��

int showMenu() {
    char choice;
    do {
        cout << "��ӭ����WaveTime�����" << endl << endl;
        cout << "�˵�" << endl;
        cout << "��1����ʼ" << endl;
        cout << "��2������" << endl;
        cout << "��3������" << endl;
        cout << "��ѡ��ģʽ��";
        choice = getch();
        cout << choice << endl;
    } while (choice < '1' || choice > '3');

    return choice - '0';
}

void initializeForm(string formSurface[][3], int formBackend[][2]) {
    for (int i = 0; i < MAX_ITEMS; i += 2) {
        formSurface[i][0] = "��";
        formBackend[i][0] = 0;

        if (i > 0) {
            formSurface[i-1][0] = "��";
        }

        formSurface[i][1] = "��";
        if (i > 0) {
            formSurface[i-1][1] = "��Ϣ";
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
    cout << "\033cʱ������ƣ�" << listName << endl;
    for (int i = 0; i < MAX_ITEMS; i++) {
        cout << "���:" << formSurface[i][0]
             << "  ��Ŀ:" << formSurface[i][1]
             << " ʱ��:" << formSurface[i][2] << endl;
    }
}

void editForm(string formSurface[][3]) {
    for (int i = 0; i < MAX_ITEMS; i += 2) {
        cout << "�������" << (i/2 + 1) << "���¼�������������\"none\"����";
        cin >> formSurface[i][1];

        if (formSurface[i][1] == "none") {
            formSurface[i][1] = "��";
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

        // ��ʱ����������alarm.exe
        system("alarm.exe");

        // �������״̬
        formSurface[i][0] = "��";
        displayForm(listName, formSurface);
    }
}

void createSchedule() {
    cout << "\033cʱ������ƣ�";
    string listName;
    cin >> listName;

    string formSurface[MAX_ITEMS][3];
    int formBackend[MAX_ITEMS][2];

    initializeForm(formSurface, formBackend);

    char choice = 'n';
    while (choice != '2') {
        displayForm(listName, formSurface);
        cout << endl << "�˵�" << endl;
        cout << "��1���༭" << endl;
        cout << "��2����ʼ" << endl;

        choice = getch();
        cout << endl;

        if (choice == '1') {
            editForm(formSurface);
        }
    }

    runTimer(listName, formSurface, formBackend);
}

void showHelp() {
    // ������Ӵ򿪰����ĵ��Ĵ���
    // ���磺system("start WaveTimeHelp.docx");
    cout << "\033c�������ܿ�����..." << endl;
    cout << "��������������˵�...";
    getch();
}


void showAbout() {
    cout << "\033c";
    cout << "========================================" << endl;
    cout << "          WaveTime ʱ�������         " << endl;
    cout << "              �汾 1.0.0               " << endl;
    cout << "========================================" << endl << endl;

    cout << "�� ������ɫ��" << endl;
    cout << "  - ���ڷ��ѹ�������ʱ�����" << endl;
    cout << "  - ֧���Զ��������б�" << endl;
    cout << "  - ʵʱ����ʱ��ʾ" << endl << endl;

    cout << "�� ����������" << endl;
    cout << "  - Ĭ�Ϲ���ʱ��: 25����" << endl;
    cout << "  - Ĭ����Ϣʱ��: 5����" << endl;
    cout << "  - ���������: 10��" << endl << endl;

    cout << "�� ������Ϣ��" << endl;
    cout << "  ����: ε��Waverly" << endl;
    cout << "  ��ϵ��ʽ: Uild913@Outlook.com" << endl;
    cout << "  ��Ŀ��ҳ: https://github.com/weilanfurry/Wavetime" << endl << endl;

    cout << "�� ��Ȩ������" << endl;
    cout << "  GPL2 License - 2025" << endl << endl;

    cout << "========================================" << endl;
    cout << "��������������˵�...";
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
