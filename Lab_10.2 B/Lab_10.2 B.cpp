#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };  // KN - Комп'ютерні науки, INF - Інформатика, ME - Математика та економіка, FI - Фізика та інформатика, TN - Трудове навчання
string specialnistStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
    string prizv;
    unsigned kurs;
    Specialnist specialnist;
    int ocinkaFizyka;
    int ocinkaMatematika;

    union {
        int ocinkaProgramming;
        int ocinkaNumericalMethods;
        int ocinkaPedagogics;
    };

    double avg() const { // Функція для розрахунку середнього балу
        int thirdGrade = (specialnist == KN) ? ocinkaProgramming :
            (specialnist == INF) ? ocinkaNumericalMethods : ocinkaPedagogics;
        return (ocinkaFizyka + ocinkaMatematika + thirdGrade) / 3.0;
    }
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);
int FindStudentWithMinAverage(const Student* s, const int N);
void CountSatisfactoryGrades(const Student* s, const int N);
void PrintStudentWithMinAverage(const Student* s, const int N);
void SortPhysical(Student* s, const int N);
void PrintIndexSorted(const Student* s, const int* I, const int N);
int* IndexSort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string prizv, unsigned kurs, double avg);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Student* s = new Student[N];

    string prizv;
    unsigned kurs;
    int specialnist;
    
    int menuItem;
    int indexBin = -1;

    do {
        cout << "\nВиберіть дію:\n";
        cout << " [1] - введення даних\n";
        cout << " [2] - вивід даних\n";
        cout << " [3] - фізичне сортування\n";
        cout << " [4] - індексне сортування\n";
        cout << " [5] - бінарний пошук\n";
        cout << " [0] - завершення роботи\n";
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            SortPhysical(s, N);
            break;
        case 4:
            PrintIndexSorted(s, IndexSort(s, N), N);
            break;
        case 5:
            cout << "Введіть прізвище студента для пошуку: "; cin >> prizv;
            cout << "Введіть курс студента: "; cin >> kurs;
            cout << "Виберіть спеціальність (0 - РІ, 1 - ІК, 2 - СШІ): "; cin >> specialnist;

            indexBin = BinSearch(s, N, prizv, kurs, (Specialnist)specialnist);

            if (indexBin != -1) {
                cout << "Студент знайдений:" << endl;
                cout << "Прізвище: " << s[indexBin].prizv << endl;
                cout << "Курс: " << s[indexBin].kurs << endl;
                cout << "Спеціальність: " << specialnistStr[s[indexBin].specialnist] << endl;
                cout << "Середній бал: " << fixed << setprecision(2) << s[indexBin].avg() << endl;
            }
            else {
                cout << "Студента з таким прізвищем, курсом та спеціальністью не знайдено!" << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Помилкове значення!\n";
        }
    } while (menuItem != 0);

    PrintStudentWithMinAverage(s, N);
    CountSatisfactoryGrades(s, N);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        cin.get();
        cout << " прізвище: "; getline(cin, s[i].prizv);
        cout << " курс: "; cin >> s[i].kurs;
        cout << " спеціальність (0 - КН, 1 - ІНФ, 2 - МЕ, 3 - ФІ, 4 - ТН): ";
        cin >> specialnist;
        s[i].specialnist = (Specialnist)specialnist;
        cout << " оцінка з фізики: "; cin >> s[i].ocinkaFizyka;
        cout << " оцінка з математики: "; cin >> s[i].ocinkaMatematika;

        if (s[i].specialnist == KN) {
            cout << " оцінка з програмування: "; cin >> s[i].ocinkaProgramming;
        }
        else if (s[i].specialnist == INF) {
            cout << " оцінка з чисельних методів: "; cin >> s[i].ocinkaNumericalMethods;
        }
        else {
            cout << " оцінка з педагогіки: "; cin >> s[i].ocinkaPedagogics;
        }
        cout << endl;
    }
}

void Print(const Student* s, const int N) {
    cout << "==================================================================================================================================" << endl;
    cout << "| № | Прізвище           | Курс | Спеціальність             | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " | " << setw(18) << left << s[i].prizv
            << " | " << setw(4) << s[i].kurs
            << " | " << setw(25) << left << specialnistStr[s[i].specialnist]
            << " | " << setw(6) << s[i].ocinkaFizyka
            << " | " << setw(10) << s[i].ocinkaMatematika;

        if (s[i].specialnist == KN) {
            cout << " | " << setw(13) << s[i].ocinkaProgramming << " | " << setw(15) << "-" << " | " << setw(10) << "-" << " |\n";
        }
        else if (s[i].specialnist == INF) {
            cout << " | " << setw(13) << "-" << " | " << setw(15) << s[i].ocinkaNumericalMethods << " | " << setw(10) << "-" << " |\n";
        }
        else {
            cout << " | " << setw(13) << "-" << " | " << setw(15) << "-" << " | " << setw(10) << s[i].ocinkaPedagogics << " |\n";
        }
    }
    cout << "==================================================================================================================================\n";
}

int FindStudentWithMinAverage(const Student* s, const int N) {
    int minIndex = 0;
    double minAvg = s[0].avg();

    for (int i = 1; i < N; i++) {
        if (s[i].avg() < minAvg) {
            minAvg = s[i].avg();
            minIndex = i;
        }
    }
    return minIndex;
}

void PrintStudentWithMinAverage(const Student* s, const int N) {
    int minIndex = FindStudentWithMinAverage(s, N);
    cout << "Студент з найменшим середнім балом: " << s[minIndex].prizv << endl;
}

void CountSatisfactoryGrades(const Student* s, const int N) {
    int satisfactoryPhysics = 0, satisfactoryMath = 0, satisfactorySpecial = 0;
    const int SATISFACTORY_GRADE = 3;

    for (int i = 0; i < N; i++) {
        if (s[i].ocinkaFizyka == 3) satisfactoryPhysics++;
        if (s[i].ocinkaMatematika == 3) satisfactoryMath++;

        if (s[i].specialnist == KN && s[i].ocinkaProgramming == SATISFACTORY_GRADE) satisfactorySpecial++;
        else if (s[i].specialnist == INF && s[i].ocinkaNumericalMethods == SATISFACTORY_GRADE) satisfactorySpecial++;
        else if (s[i].specialnist != KN && s[i].specialnist != INF && s[i].ocinkaPedagogics == SATISFACTORY_GRADE) satisfactorySpecial++;
    }

    cout << "Кількість задовільних оцінок з фізики: " << satisfactoryPhysics << endl;
    cout << "Кількість задовільних оцінок з математики: " << satisfactoryMath << endl;
    cout << "Кількість задовільних оцінок за спеціальністю: " << satisfactorySpecial << endl;
}

void SortPhysical(Student* s, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) { // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            // Якщо середній бал поточного студента більше, ніж у наступного
            if (s[i1].avg() < s[i1 + 1].avg() ||
                (s[i1].avg() == s[i1 + 1].avg() && s[i1].prizv < s[i1 + 1].prizv) ||
                (s[i1].avg() == s[i1 + 1].avg() && s[i1].prizv == s[i1 + 1].prizv && s[i1].kurs > s[i1 + 1].kurs)) {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
        }
    }
}

int* IndexSort(Student* s, const int N) 
{
    int* I = new int[N]; // створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i; // заповнили його початковими даними

    int i, j, value; // починаємо сортувати масив індексів
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((s[I[j]].avg() > s[I[j + 1]].avg() || (s[I[j]].avg() == s[I[j + 1]].avg() && s[I[j]].prizv > s[I[j + 1]].prizv) ||
                (s[I[j]].avg() == s[I[j + 1]].avg() && s[I[j]].prizv == s[I[j + 1]].prizv && s[I[j]].kurs > s[I[j + 1]].kurs)));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

int BinSearch(Student* s, const int N, const string& prizv, unsigned kurs, double avg) 
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (s[m].prizv == prizv && s[m].kurs == kurs && s[m].avg() == avg)
            return m;
        if (s[m].prizv < prizv
            || (s[m].prizv == prizv && s[m].kurs < kurs)
            ||
            (s[m].prizv == prizv && s[m].kurs == kurs && s[m].avg() < avg))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}


void PrintIndexSorted(const Student* s, const int* I, const int N) {
    cout << "Список студентів, відсортованих за середнім балом:" << endl;
    cout << "==================================================" << endl;
    cout << "| № | Прізвище       | Курс | Середній бал       |" << endl;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << i + 1
            << " | " << setw(14) << s[I[i]].prizv
            << " | " << setw(4) << s[I[i]].kurs
            << " | " << setw(18) << fixed << setprecision(2) << s[I[i]].avg() << " |" << endl;
    }
    cout << "==================================================" << endl;
}
