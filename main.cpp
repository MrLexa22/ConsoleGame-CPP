#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <SFML/Audio.hpp>

sf::Music music;
sf::Music music1;
//Hello1
using namespace std;

const unsigned int DIM1 = 10; //константы, определяющие размеры массивов
const unsigned int DIM2 = 7;
string mas[DIM1][DIM2] ={ //массив со всем возможными отрядами ///характеристики: атака, защита, здоровье, регенерация, цена, тип атаки
        {"Лучник","50","15","140","2","200","range"},
        {"Арбалетчик", "100", "30", "200", "5", "400", "range"},
        {"Лучник с длинным луком", "150", "7", "250", "4", "500", "range"},
        {"Немецкий Африканский Танковый Корпус", "500", "600", "3000", "0", "10000", "range"},
        {"Копейщик", "100", "70", "600", "0", "450", "melee"},
        {"Ландскнехт", "150", "5", "250", "10", "200", "melee"},
        {"Тевтонский рыцарь", "300", "150", "2500", "15", "400", "melee"},
        {"Синие Полоски", "400", "350", "1500", "20", "1000", "melee"},
        {"Рыцарь", "600", "400", "2500", "0", "5000", "melee"},
        {"Художник из Австрии", "10000", "5000", "20000", "0", "50000", "melee"}
};

string army[DIM1][DIM2];
string enemyarmy[DIM1][DIM2];

string spells[DIM1][DIM2] = { //название, урон, магическая сила, необходимая для использования заклинания
        {"ВОЛШЕБНЫЙ БАН", "1000", "500"},
        {"Shinra Tensei", "0", "2000"}, //киляет все армии, оставляя только 1 отряд в армии персонажа
        {"Сусаноо", "0", "1800"}, //увеличивает статы в 10 раз у выбранного отряда
        {"nico nico power", "0", "1000"}, // дает 2 хода подряд
};

int shet = 0;
//Характеристики персонажа
string name = "";
string klass = "";
string race = "";
double health = 100;
int level = 1;
int xp = 0;
double gold = 0;
bool shlem = false;
bool grudak = false;
bool shtany = false;
bool botinki = false;

bool mozhnoornet = true;
bool vich = false;

//Классовые характеристики
string rasa = "";
double zashita = 0;
double magsila = 0;
int max_health = 0;

//переменные для заклинаний
bool niconico = false;

class Unit // класс с характеристиками отрядов
{
public:
    string unitname = "";
    int attack;
    int defend;
    int health;
    int regen;
    int price;
    string attacktype = "";
};

bool intSigned(const std::string& s)
{
    size_t offset=0;
    if(s[offset]=='-')
        ++offset;
    return s.find_first_not_of("0123456789", offset) == std::string::npos;
}


int Random1(int a,int b)
{
    _sleep(500);
    srand(_time64(NULL));
    return a + (rand() % ((b - a) + 1));;
    /*srand(time(NULL));
    if (a >= 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);*/
}

int Random(int min, int max) //Генератор рандомных числе в диапазоне
{
    _sleep(500);
    srand(_time64(NULL));
    return min + (rand() % ((max - min) + 1));;
    /*std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(min, max);
    int x = distribution(generator);*/
    //return x;
}

int Random_army()
{
    int t = 0;
    bool boss = false;
    if (level == 1 || level == 3)
    {
        t = Random1(1,3);
    }
    else if (level == 4 || level == 5)
    {

        t = Random1(1,5);
    }
    else if (level == 6 || level == 7)
    {
        t = Random1(2,7);
    }
    else
    {
        boss = true;
        t = Random1(3,10);
    }
    int t2 = 0;
    int t1 = 0;
    const int arraySize = 10;
    int rand_kolvo = 0;
    int ma[arraySize] = { };
    int ma1[arraySize] = { };
    for (int i = 0; i < t; i++)
    {
        stt1: t1 = 0;
        //cout << i << "\n\n";
        if (t1 == 0)
        {
            hjrg1: t2 = Random1(0, 9);
            if (mas[t2][0] == "Немецкий Африканский Танковый Корпус" && boss == false)
                goto hjrg1;
            for (int i = 0; i < arraySize; i++)
            {
                if (ma[i] == t2)
                    goto hjrg1;
            }
            ma[i] = t2;
            if (level == 1 || level == 3)
            {
                rand_kolvo = Random1(1, 3);
            }
            else if (level == 4 || level == 5)
            {
                rand_kolvo = Random1(1, 5);
            }
            else if (level == 6 || level == 7)
            {
                rand_kolvo = Random1(2, 7);
            }
            else
            {
                rand_kolvo = Random1(3, 10);
            }


            enemyarmy[i][0] = mas[t2][0];
            enemyarmy[i][0] = mas[t2][0];
            enemyarmy[i][1] = to_string(atoi(mas[t2][1].c_str()) * rand_kolvo);
            enemyarmy[i][2] = to_string(atoi(mas[t2][2].c_str()) * rand_kolvo);
            enemyarmy[i][3] = to_string(atoi(mas[t2][3].c_str()) * rand_kolvo);
            enemyarmy[i][4] = to_string(atoi(mas[t2][4].c_str()) * rand_kolvo);
            enemyarmy[i][5] = mas[t2][6];
            enemyarmy[i][6] = to_string(rand_kolvo);
        }
    }
    return 1;
}

int LevelUp() //проверка и повышение уровня игрока и его характеристик
{
    if (xp >= 400)
    {
        level = 2;
        health = health + (level * 4); //увеличение здоровья в зависимости от уровня
        max_health = max_health + (level * 10);//увеличение максимального здоровья в зависимости от уровня
        zashita = zashita + (level * 4);//увеличение защиты в зависимости от уровня
        if (klass == "Маг")//увеличение магической силы в зависимости от уровня и класса персонажа
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 800)
    {
        level = 3;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 1600)
    {
        level = 4;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 2200)
    {
        level = 5;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 2600)
    {
        level = 6;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 3000)
    {
        level = 7;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
   else  if (xp >= 3500)
    {
        level = 8;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 4000)
    {
        level = 9;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    else if (xp >= 5000)
    {
        level = 10;
        health = health + (level * 4);
        max_health = max_health + (level * 10);
        zashita = zashita + (level * 4);
        if (klass == "Маг")
        {
            magsila = magsila + (level * 10);
        }
        else
        {
            magsila = magsila + (level * 4);
        }
    }
    return 1;
}

int Veshi()
{
    int a = 0;
    int ran = 0;
    a = Random(0, 25); //Получем число от 0 до 25
    if (a == 7) //Если выпало 7
    {
        if (shlem != true) //Проверяем, есть ли шлем у персонажа, елси нету
        {
            cout << "\nПоздравляем! Вам выпал шлем!\n";
            ran = Random(5, 30); //Прибавляем случайное значение защиты
            cout << "Защита +" << ran << "\n"; zashita += ran;
            ran = Random(5, 30); //Прибавляем случайное значение здоровья
            cout << "Здоровье +" << ran << "\n"; health += ran;
            shlem = true; //Ставим true, значит шлем у игрока есть
            Sleep(5000);
            return 1;
        }
        else
        {	//Шлем уже есть, поэтому за него дадаут 20 монет
            cout << "\nПоздравляем! Вам выпал шлем, но он у вас уже есть, поэтому вы его продали и получили 20 золота\n";
            gold += 20;
            Sleep(5000);
            return 1;
        }
    }
        //Грудак
    else if (a == 10)
    {
        if (grudak != true)
        {
            cout << "\nПоздравляем! Вам выпал грудак!\n";
            ran = Random(5, 30);
            cout << "Защита +" << ran << "\n"; zashita += ran;
            ran = Random(5, 30);
            cout << "Маг. сила +" << ran << "\n"; magsila += ran;
            grudak = true;
            Sleep(5000);
            return 1;
        }
        else
        {
            cout << "\nПоздравляем! Вам выпал грудак, но он у вас уже есть, поэтому вы его продали и получили 50 золота\n";
            gold += 50;
            Sleep(5000);
            return 1;
        }
    }
        //Штаны
    else if (a == 13)
    {
        if (shtany != true)
        {
            cout << "\nПоздравляем! Вам выпали штаны!\n";
            ran = Random(5, 30);
            cout << "Защита +" << ran << "\n"; zashita += ran;
            ran = Random(5, 30);
            cout << "Маг. сила +" << ran << "\n"; magsila += ran;
            shtany = true;
            Sleep(5000);
            return 1;
        }
        else
        {
            cout << "\nПоздравляем! Вам выпали штаны, но они у вас уже есть, поэтому вы его продали и получили 50 золота\n";
            gold += 50;
            Sleep(5000);
            return 1;
        }
    }
        //Ботинки
    else if (a == 19)
    {
        if (botinki != true)
        {
            cout << "\nПоздравляем! Вам выпали ботинки!\n";
            ran = Random(5, 30);
            cout << "Здоровье +" << ran << "\n"; health += ran;
            ran = Random(5, 30);
            cout << "Маг. сила +" << ran << "\n"; magsila += ran;
            botinki = true;
            Sleep(5000);
            return 1;
        }
        else
        {
            cout << "\nПоздравляем! Вам выпали ботинки, но они у вас уже есть, поэтому вы его продали и получили 25 золота\n";
            gold += 25;
            Sleep(5000);
            return 1;
        }
    }
    return 1;
}

int ChooseUnit() //Магазин
{
    start:
    cout << "\nДобро пожаловать в магазин войск!";
    cout << "\n1. Войска ближнего боя \n2. Войска дальнего боя \n3. Выход \nВыберите тип атаки юнита: ";
    int vib; //Выбираем тип атаки или выход
    cin >> vib;
    int j = 1; //Переменные необходимые для работы
    int checker3[16];
    int k[16];
    int hh = 1;
    int j2 = 0;
    string tip = ""; //Записываем в эту переменную тип, исходя из введённого числа
    if (vib == 1)
        tip = "melee";
    else if (vib == 2)
        tip = "range";
    else if (vib == 3)
        return 1;

    system("cls"); //Очищаем консоль
    for (int i = 0; i < 10; i++)//Сканируем массив и находим в нём войска нужного типа
    {
        if (mas[i][0] != "" && mas[i][6] == tip) {
            if (level < 7 && mas[i][0] == "Немецкий Африканский Танковый Корпус") //Если уровень меньше 7
            {                                                                //То корпуса купить нельзя
                continue;
            } else {
                cout << j << ". " << mas[i][0] << "\n"; //Выводим найденное совпадение
                k[hh] = i; //Записываем индекс массива
                hh++; //прибавляем hh
                checker3[j] = j; //Записываем число вывода
                j++; //Прибавляем j
            }
        }
    }

    string vib33 = "";
    st11:
    cout << "Выбор: ";
    cin >> vib33;
    bool jcheck = intSigned(vib33);
    if (!jcheck)
    {
        cout << "\nНЕ число! \n";
        goto st11;
    }
    j2 = atoi(vib33.c_str());
    bool flag1 = false;
    for (int i1 = 0; i1 < j; ++i1) //Проверяем, если пользователь ввёл
    {                            //Число выбора правильное
        if (checker3[i1] == j2 && checker3[i1] != 0) //То программа продолжается
        {
            flag1 = true;
        }
    }
    if (!flag1) //Если нет, то предлагаем повторить ввод
    {
        cout << "Error\n";
        Sleep(2000);
        goto st11;
    }
    else if (flag1)
    {
        cout << "\n";
        system("cls");
        int vob = 0;
        vob = k[j2]; //в vob записываем индекс необходимого выбранного массива
        cout << "Вы выбрали воина: " << mas[vob][0] << "\n"; //Выводим статистику армии
        cout << "Атака: " << mas[vob][1] << "\n";
        cout << "Защита: " << mas[vob][2] << "\n";
        cout << "Здоровье: " << mas[vob][3] << "\n";
        cout << "Регенерация: " << mas[vob][4] << "\n";
        cout << "Цена: " << mas[vob][5] << "\n";
        cout << "Тип атаки: " << mas[vob][6] << "\n";

        kik:
        cout << "\n1. Buy unit \n2. Exit \nYour choose: ";
        string v; //Предлагаем купить или выйти
        cin >> v;
        int h = 0;
        if (v == "1")
        {
            nach:
            cout << "Enter kolvo: "; //Вводим количество
            cin >> vib33;
            bool jcheck = intSigned(vib33);
            if (!jcheck)
            {
                cout << "\nНЕ число! \n";
                goto st11;
            }
            int kolvo;
            kolvo = atoi(vib33.c_str());

            if (gold < (atoi(mas[vob][5].c_str()) * kolvo)) //Если денег не хватает, то предлагаем повторить ввод
            {
                cout << "Мало денег \n";
                goto start;
            }
            bool iii = true;
            for (int i = 0; i < 10; i++) //Находим свободную ячейку
            {
                if (army[i][0] == mas[vob][0]) //Если уже есть такой тип войск
                {                            //То записываем её индекс
                    h = i;
                    iii = false;
                    break;
                }
            }
            if (iii)
            {
                for (int i = 0; i < 10; i++) //Находим свободную ячейку
                {
                    if (army[i][0] == "") //Если находим пустую, то записываем в пустую
                    {
                        h = i;
                        break;
                    }
                }
            }
            if (kolvo > 10 || kolvo <= 0) //Проверяем, чтобы ввёленное число кол-ва было нормальным
            {
                cout << "Максимальное кол-во юнитов в отряде 10\n\n";
                goto nach;
            }
            if ((kolvo + atoi(army[h][6].c_str())) > 10) //Проверяем сколько уже есть юнитов
            {
                cout << "В вашей армии находится " << atoi(army[h][6].c_str()) << " юнитов данного типа\n";
                cout << "Максимальное кол-во юнитов в отряде 10\n\n";
                ChooseUnit();
            }
            else
                {
                arm: //Записываем в армию игрока выбранный юнит
                army[h][0] = mas[vob][0];
                army[h][1] = to_string(atoi(mas[vob][1].c_str()) * kolvo + atoi(army[h][1].c_str()));
                army[h][2] = to_string(atoi(mas[vob][2].c_str()) * kolvo + atoi(army[h][2].c_str()));
                army[h][3] = to_string(atoi(mas[vob][3].c_str()) * kolvo + atoi(army[h][3].c_str()));
                army[h][4] = to_string(atoi(mas[vob][4].c_str()) * kolvo + atoi(army[h][4].c_str()));
                army[h][5] = mas[vob][6];
                army[h][6] = to_string(kolvo + atoi(army[h][6].c_str()));
                gold -= (atoi(mas[vob][5].c_str()) * kolvo);
                system("cls"); //Выводим характеристики армии
                cout << "\nВаша армия '" << army[h][0] << "':";
                cout << "\nАтака (итог): " << army[h][1];
                cout << "\nЗащита (итог): " << army[h][2];
                cout << "\nЗдоровье (итог): " << army[h][3];
                cout << "\nРегенерация (итог): " << army[h][4];
                cout << "\nЦена: " << army[h][5];
                cout << "\nИтоговая численнсть: " << army[h][6];
                char ch;
                int code;
                cout << "\n\nДля возврата в меню - нажмите Enter"; //предлагаем вернуться в меню
                while (1)
                {
                    ch = _getch();
                    code = static_cast<int>(ch);
                    if (ch == 13) // если клавиша Enter
                        return 1;
                }
            }
        }
        else if (v == "2") //Если выбрали 2, то возрат в гланвое меню
            return 1;
        else
            goto kik;
    }
    return 1;
}

int Battle()
{
    cout<<"Pleae Wait";
    if (!mozhnoornet) //Если пользователь участвовал в бою ранее,
    {							//то повторно участвовать нельзя, пока не сходить в бордель/кафе
        cout << "\n\nСначала отдохните, сходив в бордель или в кафе";
        Sleep(2000); //Пауза
        return 1; //Возврат в меню
    }
    bool mpt = true;
    system("cls");
    bool check = false; // проверка на наличие хотя бы 1 отряда в армии игрока
    for (int i = 0; i < 10; i++)
    {
        if (army[i][0] != "")
        {
            check = true;
            break;
        }
    }
    if (!check)
    {
        cout << "\nВаша армия пуста. Для начала пополните её!\n";
        Sleep(3000);
        return 1;
    }
    Random_army();
    int ran = 0;
    ran = Random(1, 20); //рандомное кол-во времени на поиск противника
    int i = 0;
    cout << "Идет поиск противника";
    while (i < ran)
    {
        Sleep(1000);
        i++;
    }
    system("cls");
    cout << "\nПротивник найден, приготовьтесь к бою!";
    Sleep(3000);
    system("cls");
    cout << "Ваша армия: \n\n"; //вывод нашей армии
    for (int h = 0; h < 10; h++)
        if (army[h][0] != "")
        {
            cout << "\nВаш отряд '" << army[h][0] << "':";
            cout << "\nАтака (итог): " << army[h][1];
            cout << "\nЗащита (итог): " << army[h][2];
            cout << "\nЗдоровье (итог): " << army[h][3];
            cout << "\nРегенерация (итог): " << army[h][4];
            cout << "\nТип атаки: " << army[h][5];
            cout << "\nИтоговая численнсть: " << army[h][6];
            cout << "\n";
        }
    cout << "Армия противника: \n\n"; //вывод армии противника
    for (int h = 0; h < 10; h++)
        if (enemyarmy[h][0] != "")
        {
            cout << "\nОтряд противника '" << enemyarmy[h][0] << "':";
            cout << "\nАтака (итог): " << enemyarmy[h][1];
            cout << "\nЗащита (итог): " << enemyarmy[h][2];
            cout << "\nЗдоровье (итог): " << enemyarmy[h][3];
            cout << "\nРегенерация (итог): " << enemyarmy[h][4];
            cout << "\nТип атаки: " << enemyarmy[h][5];
            cout << "\nИтоговая численнсть: " << enemyarmy[h][6];
            cout << "\n";
        }
    Sleep(3000);
    while (mpt) //цикл боя
    {
        start:
        system("cls");
        string vib;
        cout << "1. Использовать заклинание \n2. Провести атаку армией\nВыбор: "; //предоставление выбора для атаки : войсками или заклинаниями
        cin >> vib;
        int j = 1;
        if (vib == "1")
        { //Доделать проверки
            jik:
            for (int i = 0; i < 4; i++)
            {
                if (spells[i][0] != "")
                {
                    cout << j << ". " << spells[i][0] << "\n";
                    j++;
                }
            }
            string zak1 = "0";
            int zak = 0;
            cout << "\nВыберите заклинание: ";
            cin >> zak1;
            if (zak1 == "1") {
                zak = 1;
                if (magsila < atoi(spells[zak -
                                          1][2].c_str())) //проверяет, достаточно ли магической силы у персонажа для использования этого заклинания
                {
                    cout << "\nУ вас маленькая магическая сила!";
                    Sleep(2000);
                    goto start;
                } else {
                    cout << "\nВыбрано заклинание '" << spells[zak - 1][0] << "'"; //выводит выбранное заклинание
                    Sleep(1000);
                    int enu;
                    int j11 = 1;
                    string jkle1[16];
                    for (int i = 0; i < 10; i++) //вывели отряды противника для атак
                    {
                        if (enemyarmy[i][0] != "") {
                            cout << j11 << ". " << enemyarmy[i][0] << "\n";
                            jkle1[j11] = enemyarmy[i][0];
                            j11++;
                        }
                    }

                    jjj11:
                    string vib44 = "";
                    cout << "\nВыберите отряд противника, для атаки: "; //выбираем отряд для атаки
                    cin >> vib44;
                    bool jcheck1 = intSigned(vib44);
                    if (!jcheck1) {
                        cout << "\nНЕ число! \n";
                        goto jjj11;
                    }
                    bool juk1 = false;
                    enu = atoi(vib44.c_str());
                    if (enu < 0 || enu > 10) {
                        cout << "\nНекорректный выбор!\n";
                        goto jjj11;
                    }
                    for (int i = 0; i < 10; i++) {
                        if ((jkle1[enu] == enemyarmy[i][0]) && jkle1[enu] != "") {
                            enu = i;
                            juk1 = true;
                            break;
                        }
                    }
                    if (!juk1) {
                        cout << "\nНекорректный выбор!\n";
                        goto jjj11;
                    }
                    enu++;
                    enemyarmy[enu - 1][3] = to_string(
                            atoi(enemyarmy[enu - 1][3].c_str()) - atoi(spells[zak - 1][1].c_str()));
                }
                break;
            }
            else if (zak1 == "2")
            {
                zak = 2;
                if (magsila < atoi(spells[zak - 1][2].c_str())) {
                    cout << "\nУ вас маленькая магическая сила!";
                    Sleep(2000);
                    goto start;
                } else {
                    cout << "\nВыбрано заклинание '" << spells[zak - 1][0] << "'";
                    Sleep(1000);
                    for (int i = 1; i < 10; i++)
                    {
                        army[i][1] = "";
                        army[i][2] = "";
                        army[i][3] = "";
                        army[i][4] = "";
                        army[i][5] = "";
                        army[i][6] = "";
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        enemyarmy[i][0] = "";
                        enemyarmy[i][1] = "";
                        enemyarmy[i][2] = "";
                        enemyarmy[i][3] = "";
                        enemyarmy[i][4] = "";
                        enemyarmy[i][5] = "";
                        enemyarmy[i][6] = "";
                    }
                    Sleep(3000);
                    system("cls");
                    cout << "Вы победили";
                    int zarab = 200 * Random(1, 5);
                    int XP = 100 * Random(1, 5);
                    cout << "\nВы заработали: " << zarab << " золота" << "\nВы заработали: " << XP << " опыта";
                    Veshi();
                    xp += XP;
                    gold += zarab;
                    for (int i = 0; i < 10; i++)
                    {
                        enemyarmy[i][0] = "";
                        enemyarmy[i][1] = "";
                        enemyarmy[i][2] = "";
                        enemyarmy[i][3] = "";
                        enemyarmy[i][4] = "";
                        enemyarmy[i][5] = "";
                        enemyarmy[i][6] = "";
                    }
                    Sleep(2000);
                    mozhnoornet = false;
                    char ch;
                    int code;
                    cout << "\n\nДля возврата в меню - нажмите Enter";
                    while (1)
                    {
                        ch = _getch();
                        code = static_cast<int>(ch);
                        if (ch == 13) // если клавиша Enter
                            return 1;
                    }
                }
                break;
            }
            else if (zak1 == "3")
            {
                zak = 3;
                if (magsila < atoi(spells[zak - 1][2].c_str()))
                {
                    cout << "\nУ вас маленькая магическая сила!";
                    Sleep(2000);
                    goto start;
                }
                else
                    {
                    cout << "\nВыбрано заклинание '" << spells[zak - 1][0] << "'";
                    Sleep(1000);
                    int u;
                    int j = 1;
                    string jkle[16];
                    for (int i = 0; i < 10; i++) //вывели отряды противника для атак
                    {
                        if (army[i][0] != "")
                        {
                            cout << j << ". " << army[i][0] << "\n";
                            jkle[j] = army[i][0];
                            j++;
                        }
                    }
                    string vib33 = "";
                    jjj2:
                    cout << "\nВыберите отряд, для применения к нему сусаноо: "; //выбираем отряд для атаки
                    cin >> vib33;
                    bool jcheck = intSigned(vib33);
                    if (!jcheck)
                    {
                        cout << "\nНЕ число! \n";
                        goto jjj2;
                    }
                    bool juk = false;
                    u = atoi(vib33.c_str());
                    if (u < 0 || u > 10)
                    {
                        cout << "\nНекорректный выбор!\n";
                        goto jjj2;
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        if ((jkle[u] == army[i][0]) && jkle[u] != "")
                        {
                            u = i;
                            juk = true;
                            break;
                        }
                    }
                    if (!juk)
                    {
                        cout << "\nНекорректный выбор!\n";
                        goto jjj2;
                    }
                    u++;

                    army[u - 1][1] = to_string(atoi(army[u - 1][1].c_str()) * 10);
                    army[u - 1][2] = to_string(atoi(army[u - 1][2].c_str()) * 10);
                    army[u - 1][3] = to_string(atoi(army[u - 1][3].c_str()) * 10);
                    army[u - 1][4] = to_string(atoi(army[u - 1][4].c_str()) * 10);
                    Sleep(1000);
                    system("cls");
                }
                break;
            }
            else if (zak1 == "4")
            {
                zak = 4;
                if (magsila < atoi(spells[zak - 1][2].c_str()))
                {
                    cout << "\nУ вас маленькая магическая сила!";
                    Sleep(2000);
                    goto start;
                }
                else
                    {
                    cout << "\nВыбрано заклинание '" << spells[zak - 1][0] << "'";
                    Sleep(1000);
                    niconico = true;
                    system("cls");
                }
            }
            else
                goto jik;
        }

        j = 1;
        string jkle[11];
        for (int i = 0; i < 10; i++) //вывели свои отряды для атак
        {
            if (army[i][0] != "")
            {
                cout << j << ". " << army[i][0] << "\n";
                jkle[j] = army[i][0];
                j++;
            }
        }

        int u;
        jjj:
        string vib33 = "";
        cout << "\nВыберите отряд, для атаки: "; //выбираем отряд для атаки
        cin >> vib33;
        bool jcheck = intSigned(vib33);
        if (!jcheck)
        {
            cout << "\nНЕ число! \n";
            goto jjj;
        }
        bool juk = false;
        u = atoi(vib33.c_str());
        if (u < 0 || u > 10)
        {
            cout << "\nНекорректный выбор!\n";
            goto jjj;
        }
        for (int i = 0; i < 10; i++)
        {
            if ((jkle[u] == army[i][0]) && jkle[u] != "")
            {
                u = i;
                juk = true;
                break;
            }
        }
        if (!juk)
        {
            cout << "\nНекорректный выбор!\n";
            goto jjj;
        }
        u++;

        int att, def, healt, reg;
        string name1, atttp;
        name1 = army[u - 1][0];
        atttp = army[u - 1][5];
        att = atoi(army[u - 1][1].c_str());
        def = atoi(army[u - 1][2].c_str());
        healt = atoi(army[u - 1][3].c_str());
        reg = atoi(army[u - 1][4].c_str());
        ///////////////////////////////////////// взятие данных отряда

        cout << "\n\n";
        int enu;
        j = 1;
        string jkle1[11];
        for (int i = 0; i < 10; i++) //вывели отряды противника для атак
        {
            if (enemyarmy[i][0] != "")
            {
                cout << j << ". " << enemyarmy[i][0] << "\n";
                jkle1[j] = enemyarmy[i][0];
                j++;
            }
        }
        jjj1:
        string vib44 = "";
        cout << "\nВыберите отряд противника, для атаки: "; //выбираем отряд для атаки
        cin >> vib44;
        bool jcheck1 = intSigned(vib44);
        if (!jcheck1)
        {
            cout << "\nНЕ число! \n";
            goto jjj1;
        }
        bool juk1 = false;
        enu = atoi(vib44.c_str());
        if (enu < 0 || enu > 10)
        {
            cout << "\nНекорректный выбор!\n";
            goto jjj1;
        }
        for (int i = 0; i < 10; i++)
        {
            if ((jkle1[enu] == enemyarmy[i][0]) && jkle1[enu] != "")
            {
                enu = i;
                juk1 = true;
                break;
            }
        }
        if (!juk1)
        {
            cout << "\nНекорректный выбор!\n";
            goto jjj1;
        }
        enu++;

        int enatt, endef, enhealt, enreg;
        string enname, enatttp;
        enname = enemyarmy[enu - 1][0];
        enatttp = enemyarmy[enu - 1][5];
        enatt = atoi(enemyarmy[enu - 1][1].c_str());
        endef = atoi(enemyarmy[enu - 1][2].c_str());
        enhealt = atoi(enemyarmy[enu - 1][3].c_str());
        enreg = atoi(enemyarmy[enu - 1][4].c_str());
        /////////////////////////////////////////// взятие данных отряда

        int ataka = att - endef - enreg; //рассчет нанесенного урона
        int enataka = 0;
        if (ataka < 0) //проверка, чтобы не было отрицательного урона
        {
            ataka = 0;
        }
        enhealt -= ataka;
        string pname = enemyarmy[enu - 1][0], apname = army[u - 1][0]; //взятие имен отрядов игрока и противника для кореектного вывода в логе
        if (enhealt > 0)
        {
            enemyarmy[enu - 1][3] = to_string(enhealt);
        }
        else if (enhealt <= 0) //проверка на оставшееся здоровье отрда противнка, если оно меньеш или равно 0 то вся строка отряда очищается
        {
            pname = enemyarmy[enu - 1][0];
            enemyarmy[enu - 1][0] = "";
            enemyarmy[enu - 1][1] = "";
            enemyarmy[enu - 1][2] = "";
            enemyarmy[enu - 1][3] = "";
            enemyarmy[enu - 1][4] = "";
            enemyarmy[enu - 1][5] = "";
            enemyarmy[enu - 1][6] = "";
        }
        if (atttp == "melee") //если у нашего отряда тип атаки melee, они должны получить ответный урон
        {
            enataka = enatt - def - reg;//рассчет крона отряду
            if (enataka < 0)
            {
                enataka = 0;
            }
            healt -= enataka;
            if (healt > 0)
            {
                army[u - 1][3] = to_string(healt);
            }
            else if (healt <= 0)
            {
                apname = army[u - 1][0];
                army[u - 1][0] = "";
                army[u - 1][1] = "";
                army[u - 1][2] = "";
                army[u - 1][3] = "";
                army[u - 1][4] = "";
                army[u - 1][5] = "";
                army[u - 1][6] = "";
            }
        }
        //////////////////////////////////// бой

        system("cls");
        cout << "\nВаш отряд '" << apname << "' нанес " << ataka << " едениц урона отряду '" << pname << "' противника и получил " << enataka << " единиц урона в ответ";
        cout << "\nУ вашего отряда '" << apname << "' осталось " << healt << " единиц здоровья.";
        cout << "\nУ отряда '" << pname << "' противника осталось " << enhealt << " единиц здоровья.";
        Sleep(5000);
        ///////////////////////////// лог атаки


        if (niconico) //проверка на использование заклинания nico nico power
        {
            niconico = false;
            goto start;
        }
        int proverka = 0, enproverka = 0; //проверка наличия армий у игроков
        for (int i = 0; i < 10; i++)
        {
            if (army[i][0] != "")
            {
                proverka++;
            }
        }
        if (proverka <= 0) //если в армии нет войск, то игрок проигрывает
        {
            mpt = false;
            Sleep(3000);
            system("cls");
            cout << "Вы проиграли";
            int zarab = 20 * Random(1, 5);
            int XP = 10 * Random(1, 5);
            int damage = 0;
            for (int i = 0; i < 10; i++) //очистка армии противника
            {
                enemyarmy[i][0] = "";
                enemyarmy[i][1] = "";
                enemyarmy[i][2] = "";
                enemyarmy[i][3] = "";
                enemyarmy[i][4] = "";
                enemyarmy[i][5] = "";
                enemyarmy[i][6] = "";
            }

            for (int i = 0; i < 10; i++) //расчет урона персонажу
            {
                if (enemyarmy[i][0] != "")
                {
                    damage++;
                }
            }

            health -= damage * 10;
            cout << "\nВы заработали: " << zarab << " золота" << "\nВы заработали: " << XP << " опыта";
            Veshi();
            xp += XP;
            gold += zarab;
            Sleep(2000);
            mozhnoornet = false;
            char ch;
            int code;
            cout << "\n\nДля возврата в меню - нажмите Enter";
            while (1)
            {
                ch = _getch();
                code = static_cast<int>(ch);
                if (ch == 13) // если клавиша Enter
                    return 1;
            }
        }
        else if (proverka > 0) //если в армии игрока есть хотя бы 1 отряд проверяем армию противника
        {
            for (int i = 0; i < 10; i++)
            {
                if (enemyarmy[i][0] != "")
                {
                    enproverka++;
                }
            }
            if (enproverka <= 0) //если в армии противника нет отрядов то игрок выигрывает
            {
                mpt = false;
                Sleep(3000);
                system("cls");
                cout << "Вы победили";
                int zarab = 200 * Random(1, 5);
                int XP = 100 * Random(1, 5);
                cout << "\nВы заработали: " << zarab << " золота" << "\nВы заработали: " << XP << " опыта";
                Veshi();
                xp += XP;
                gold += zarab;
                for (int i = 0; i < 10; i++)
                {
                    enemyarmy[i][0] = "";
                    enemyarmy[i][1] = "";
                    enemyarmy[i][2] = "";
                    enemyarmy[i][3] = "";
                    enemyarmy[i][4] = "";
                    enemyarmy[i][5] = "";
                    enemyarmy[i][6] = "";
                }
                Sleep(2000);
                mozhnoornet = false;
                char ch;
                int code;
                cout << "\n\nДля возврата в меню - нажмите Enter";
                while (1)
                {
                    ch = _getch();
                    code = static_cast<int>(ch);
                    if (ch == 13) // если клавиша Enter
                        return 1;
                }
            }
            else if (enproverka > 0)//если в армии противника есть хотя-бы один отряд, начинается ход противника
            {
                int j1 = 1;
                int k1 = 0;
                int ind1[16];
                for (int i = 0; i < 10; i++) //вывели свои отряды для атак
                {
                    if (enemyarmy[i][0] != "")
                    {
                        ind1[k1] = i;
                        k1++;
                        j1++;
                    }
                }

                int rak = 0;
                att3:
                rak = Random1(0, 9);
                if (rak < 0)
                    goto att3;
                bool tik = true;
                for (int i = 0; i < 10; i++)
                {
                    if (rak == ind1[i])
                    {
                        enu = ind1[i];
                        enu++;
                        tik = false;
                        break;
                    }
                }
                if (tik || enemyarmy[enu - 1][0] == "")
                    goto att3;

                enname = enemyarmy[enu - 1][0];
                enatttp = enemyarmy[enu - 1][5];
                enatt = atoi(enemyarmy[enu - 1][1].c_str());
                endef = atoi(enemyarmy[enu - 1][2].c_str());
                enhealt = atoi(enemyarmy[enu - 1][3].c_str());
                enreg = atoi(enemyarmy[enu - 1][4].c_str());
                /////////////////// вы брали какой отряд противника будет атаковать


                j = 1;
                int k = 0;
                int ind[16];
                for (int i = 0; i < 10; i++) //вывели свои отряды для атак
                {
                    if (army[i][0] != "")
                    {
                        ind[k] = i;
                        k++;
                        j++;
                    }
                }

                att2:
                bool tik1 = true;
                int rak1 = 0;
                while (tik1)
                {
                    rak1 = 0;
                    rak1 = Random1(0, 9);
                    for (int i = 0; i < 10; i++)
                    {
                        if (rak1 == ind[i])
                        {
                            u = ind[i];
                            u++;
                            tik1 = false;
                            break;
                        }
                    }
                }
                if (tik1 || army[u - 1][0] == "")
                    break;

                name1 = army[u - 1][0];
                atttp = army[u - 1][5];
                att = atoi(army[u - 1][1].c_str());
                def = atoi(army[u - 1][2].c_str());
                healt = atoi(army[u - 1][3].c_str());
                reg = atoi(army[u - 1][4].c_str());
                ////////////////////////////выбрали какой из наших отрядов будет атакован

                enataka = enatt - def - reg;
                apname = army[u - 1][0], pname = enemyarmy[enu - 1][0];
                if (enataka < 0)
                {
                    enataka = 0;
                }
                healt -= enataka;
                if (healt > 0)
                {
                    army[u - 1][3] = to_string(healt);
                }
                else if (healt <= 0)
                {
                    apname = army[u - 1][0];
                    army[u - 1][0] = "";
                    army[u - 1][1] = "";
                    army[u - 1][2] = "";
                    army[u - 1][3] = "";
                    army[u - 1][4] = "";
                    army[u - 1][5] = "";
                    army[u - 1][6] = "";
                }
                if (enatttp == "melee")//если отряд противника имеет тип атаки melee, то он должен получить урон в ответ
                {
                    ataka = att - endef - enreg;
                    if (ataka < 0)
                    {
                        ataka = 0;
                    }
                    enhealt -= ataka;
                    if (enhealt > 0)
                    {
                        enemyarmy[u][3] = to_string(enhealt);
                    }
                    else if (enhealt <= 0)
                    {
                        pname = enemyarmy[enu - 1][0];
                        enemyarmy[enu - 1][0] = "";
                        enemyarmy[enu - 1][1] = "";
                        enemyarmy[enu - 1][2] = "";
                        enemyarmy[enu - 1][3] = "";
                        enemyarmy[enu - 1][4] = "";
                        enemyarmy[enu - 1][5] = "";
                        enemyarmy[enu - 1][6] = "";
                    }
                }
                ////////////////////бой

                system("cls");
                cout << "\nОтряд '" << pname << "' противника нанес " << enataka << " едениц урона вашему отряду '" << apname << "' и получил " << ataka << " единиц урона в ответ";
                cout << "\nУ вашего отряда '" << apname << "' осталось " << healt << " единиц здоровья.";
                cout << "\nУ отряда '" << pname << "' противника осталось " << enhealt << " единиц здоровья.";
                Sleep(3000);

                int enxproverka = 0, enxenproverka = 0;//точно такая же проверка как и до этого
                for (int i = 0; i < 10; i++)
                {
                    if (army[i][0] != "")
                    {
                        enxproverka++;
                    }
                }
                if (enxproverka <= 0)
                {
                    mpt = false;
                    Sleep(3000);
                    system("cls");
                    cout << "Вы проиграли";
                    int zarab = 20 * Random(1, 5);
                    int XP = 10 * Random(1, 5);
                    int damage = 0;
                    for (int i = 0; i < 10; i++) //очистка армии протичника
                    {
                        enemyarmy[i][0] = "";
                        enemyarmy[i][1] = "";
                        enemyarmy[i][2] = "";
                        enemyarmy[i][3] = "";
                        enemyarmy[i][4] = "";
                        enemyarmy[i][5] = "";
                        enemyarmy[i][6] = "";
                    }
                    for (int i = 0; i < 10; i++) //расчет урона персонажу
                    {
                        if (enemyarmy[i][0] != "")
                        {
                            damage++;
                        }
                    }

                    health -= damage * 10;
                    cout << "\nВы заработали: " << zarab << " золота" << "\nВы заработали: " << XP << " опыта";
                    Veshi();
                    xp += XP;
                    gold += zarab;
                    Sleep(2000);
                    mozhnoornet = false;
                    char ch;
                    int code;
                    cout << "\n\nДля возврата в меню - нажмите Enter";
                    while (1)
                    {
                        ch = _getch();
                        code = static_cast<int>(ch);
                        if (ch == 13) // если клавиша Enter
                            return 1;
                    }
                }
                else if (enxproverka > 0)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (enemyarmy[i][0] != "")
                        {
                            enxenproverka++;
                        }
                    }
                    if (enxenproverka <= 0)
                    {
                        mpt = false;
                        Sleep(3000);
                        system("cls");
                        cout << "Вы победили";
                        int zarab = 200 * Random(1, 5);
                        int XP = 100 * Random(1, 5);
                        cout << "\nВы заработали: " << zarab << " золота" << "\nВы заработали: " << XP << " опыта";
                        Veshi();
                        xp += XP;
                        gold += zarab;
                        for (int i = 0; i < 10; i++)
                        {
                            enemyarmy[i][0] = "";
                            enemyarmy[i][1] = "";
                            enemyarmy[i][2] = "";
                            enemyarmy[i][3] = "";
                            enemyarmy[i][4] = "";
                            enemyarmy[i][5] = "";
                            enemyarmy[i][6] = "";
                        }
                        Sleep(2000);
                        mozhnoornet = false;
                        char ch;
                        int code;
                        cout << "\n\nДля возврата в меню - нажмите Enter";
                        while (1)
                        {
                            ch = _getch();
                            code = static_cast<int>(ch);
                            if (ch == 13) // если клавиша Enter
                                return 1;
                        }
                    }
                }
                else if (enxenproverka > 0)//если в армии противника и в нашей армии есть хотя бы по 1 отряду, то цикл продолжается
                {

                }
            }
        }
    }
    return 1;
}

int slychai()
{
    int ran = 0;
    string res = "1";
    ran = Random(1, 15); //Получаем рандомное число
    if (ran == 3) //Проверка игрока на честность
    {
        cout << "\nВы шли по улице и нашли кошелёк с деньгами.";
        st1: cout << "\nЖелаете отнести его в полицию или заберёте себе?\n1. Сдам в полицию\n2. Оставлю себе\nВаш выбор: ";
        cin >> res; //Игрок выбирает
        if (res == "1")
        {
            cout << "\nВас наградила судьба за вашу честность!\nВ полиции были шокированы вашим поступкои и дали Вам 50 монет в подарок\n";
            gold += 50;
            res = "1";
        }
        else if (res == "2")
        {
            cout << "\nУвы, но кошелёк был подставой.\nТак полиция искала честных и нечестных людей.\nЗа свою жадность вы не получаете монет\n";
            res = "0";
        }
        else
            goto st1;
    }
    else if (ran == 5) //Сделать правильный или неправильный выбор
    {
        cout << "\nВы идёте и видите, что бабушка не может перейти дорого";
        st2: cout << "\nПоможете ей?\n1. Да\n2. Нет\nВаш выбор: ";
        cin >> res;
        if (res == "1")
        {
            cout << "\nВы хороший человек, увы, но доброта никак не вознограждается\n";
            res = "0";
        }
        else if (res == "2")
        {
            cout << "\nПравильно сделали, ведь вы пойшли дальше и нашли лежащие на дороге 10 монет\n";
            gold += 10;
            res = "1";
        }
        else
            goto st2;
    }
        //Ловушка
    else if (ran == 9) //Ловушка
    {
        cout << "\nТебе предложили поучаствовать в олимпиаде, примешь ли ты участие?";
        st3: cout << "\n1. Да\n2. Нет\nВаш выбор: ";
        cin >> res;
        if (res == "1")
        {
            cout << "\nОлимпиада оказалась ловушкой и у вас украли 20 монет из вашего кармана, когда вы записывались\n";
            if (gold > 10)
                gold -= 10;
            res = "0";
        }
        else if (res == "2")
        {
            cout << "\nВы избежали ловушки\n";
            res = "1";
        }
        else
            goto st3;
    }
        //Помочь или нет?
    else if (ran == 11) //Помочь или нет?
    {
        cout << "\nК тебе подошёл полицейский и попросил помочь ему сопроводить преступника. Согласишься ли ты ему помочь?";
        st4: cout << "\n1. Да\n2. Нет\nВаш выбор: ";
        cin >> res;
        if (res == "1")
        {
            cout << "\nВы помолги полицейскому и получаете от него награду в 25 монет\n";
            gold += 25;
            res = "0";
        }
        else if (res == "2")
        {
            cout << "\nВы отказались помочь и продолжили свой путь.\n";
            res = "1";
        }
        else
            goto st4;
    }
    int res1 = 0;
    if (res == "1")
        res1=1;
    else if (res == "0")
        res1=0;
    return res1;
}

int menu_igroka()
{
    system("cls"); //Очистка консоли
    cout << "Меню: \n\n"; //Вывод всех характеристик персонажа
    cout << "\nИмя персонажа: " << name;
    cout << "\nКласс персонажа: " << klass;
    cout << "\nРаса персонажа: " << race;
    cout << "\nУровень: " << level;
    cout << "\nXP: " << xp;
    cout << "\nЗолото: " << gold;
    cout << "\nЗдоровье: " << health;
    cout << "\nЗащита: " << zashita;
    cout << "\nМагическая сила: " << magsila;
    cout << "\nШлем: "; //Проверка, есть ли вещь у игрока
    if (shlem == true)
        cout << "есть";
    else
        cout << "нет";
    cout << "\nНагрудник: ";
    if (grudak == true)
        cout << "есть";
    else
        cout << "нет";
    cout << "\nШтаны: ";
    if (shtany == true)
        cout << "есть";
    else
        cout << "нет";
    cout << "\nБотинки: ";
    if (botinki == true)
        cout << "есть";
    else
        cout << "нет";
    char ch;
    int code;
    cout << "\n\nДля возврата в меню - нажмите Enter"; //Возврат в меню по Enter
    while (1)
    {
        ch = _getch();
        code = static_cast<int>(ch);
        if (ch == 13) // если клавиша Enter
            return 1;
    }
}

int DangeEvents()
{
    int ran = 0;
    string res = "1";
    ran = Random(1, 15);//рандомное событие
    if (ran == 3)
    {
        cout << "\nВы нашли сундук.";
        st1: cout << "\nОткрыть?\n1. Да\n2. Нет\nВаш выбор: ";
        cin >> res;
        if (res == "1")
        {
            int res1 = Random(1, 3);//рандомный результат события
            switch (res1)
            {
                case 1:
                {
                    cout << "\nВ сундуке ничего не оказалось. Вы пошли, расстроились, но пошли дальше.\n";
                    res = "1";
                }
                case 2:
                {
                    cout << "\nВ сундуке лежало немного монет. Мало, но что-то\n";
                    gold += 50 * Random(2, 4);
                    res = "1";
                }
                case 3:
                {
                    cout << "\nВ сундуке оказался клад!\nВы нашли мешок монет и предмет экипировки!\n";
                    gold += 50 * 1000;
                    Veshi();
                    res = "1";
                }
            }
        }
        else if (res == "2")
        {
            cout << "\nВы решили оставить сундук и пойти дальше.\n";
            res = "0";
        }
        else
            goto st1;
    }
    else if (ran == 6)
    {
        cout << "\nВы идёте и видите, плачущую девочку.";
        st2: cout << "\nПодойти?\n1. Да\n2. Нет\nВаш выбор: ";
        cin >> res;
        if (res == "1")
        {
            int res1 = Random(1, 3);//рандомный результат события
            switch (res1)
            {
                case 1:
                {
                    cout << "\nВы подошли к девочке, но оказалась всего - лишь иллюзией\n";
                    res = "1";
                }
                case 2:
                {
                    cout << "\nДевочка оказалась монстром, к бою!\n";
                    Sleep(2000);
                    Battle();
                }
                case 3:
                {
                    st22: cout << "\nДевочка провалилась сюда, когда убегала от монстра.\nПомочь ей выбраться? \n1. Да \n 2. Нет";
                    string pom;
                    cin >> pom;
                    if (pom == "1")
                    {
                        cout << "\nВы подобрали девочку и двинулись назад.";
                        Sleep(4000);
                        st222: cout << "\nВы вывели девочку на поверхность, рядом оказалась ее деревня. \n1. Отвести девочку \n2. Пусть сама идет";
                        cin >> pom;
                        if (pom == "1")
                        {
                            cout << "\nВы повели девочку в деревню.";
                            Sleep(4000);
                            st2222: cout << "\nВы нашли ее родителей и вернули девочку. \nОни предлагают Вам вознаграждение \n1. Взять деньги \n2. Не брать вознаграждение";
                            cin >> pom;
                            if (pom == "1")
                            {
                                cout << "\n Вы взяли вознаграждение и двинулись в путь";
                                gold += 20 * Random(2, 4);
                                res = "1";
                            }
                            else if (pom == "2")
                            {
                                cout << "\n Вы не стали вознаграждение и двинулись в путь";
                                res = "1";
                            }
                            else
                            {
                                goto st2222;
                            }
                        }
                        else if (pom == "2")
                        {
                            cout << "\n Вы сказали девочке идти самой в деревню и двинулись в путь";
                            res = "1";
                        }
                        else
                            goto st222;
                    }
                    else if (pom == "2")
                    {
                        st23: cout << "\nВы оставили девочку и пошли дальше в подземелье. \nЧерез несколько минут Вы услышали детский крик \n1. Вернуться к девочке \n2. Пойти дальше \nВаш выбор: ";
                        cin >> pom;
                        if (pom == "1")
                        {
                            cout << "\nВы развернули свои отряды и поспешили к девочке";
                            int sob = Random(1, 2);//рандомный результат события
                            switch (sob)
                            {
                                case 1:
                                {
                                    cout << "\nВы опоздали. Девочка была разорвана пополам, а ее внутренности были разбросаны вокруг";
                                    string a;
                                    st233: cout << "\n1. Идти дальше \nВаш выбор: ";
                                    cin >> a;
                                    if (a == "1")
                                    {
                                        res = "1";
                                    }
                                    else
                                        goto st233;
                                }
                                case 2:
                                {
                                    cout << "\nВы успели во время, монстр хочет убить девочку. К бою!";
                                    Sleep(2000);
                                    Battle();
                                }
                            }
                        }
                        else if (pom == "2")
                        {
                            cout << "\nВы двинулись дальше. Через несолько минут крики стихли.";
                            Sleep(2000);
                            res = "1";
                        }
                        else
                            goto st23;
                    }
                    else
                    {
                        goto st22;
                    }
                }
            }
        }
        else if (res == "2")
        {
            cout << "\nВы нашли 10 монет\n";
            gold += 10;
            res = "1";
        }
        else
            goto st2;
    }
    else if (ran == 9)
    {
        cout << "\nВы наткнулись на армию противника. К бою!";
        Sleep(2000);
        Battle();//бой с противником
    }
    else if (ran == 11)
    {
        cout << "\nВы шли во главе войска и попались в ловушку!";
        int ur = 100 * Random(2, 6);//рандомное кол-во нанесенного урона персонажу
        cout << "\nВы получили " << ur << " единиц урона";
        health -= ur;
        if (health <= 0)
        {
            cout << "\nВы умерли"; //очищение армии, при смерти игрока
            for (int i = 0; i < 10; i++)
            {
                army[i][0] = "";
                army[i][1] = "";
                army[i][2] = "";
                army[i][3] = "";
                army[i][4] = "";
                army[i][5] = "";
                army[i][6] = "";
            }
            Sleep(2000);
            res = "1";
        }
    }
    int res1 = 0;
    if (res == "1")
        res1 = 1;
    else if (res == "0")
        res1 = 0;
    return res1;
}

int Dange() //выбор данжа
{
    pjkl:
    system("cls");
    cout << "1. Бронзовый\n";
    cout << "2. Серебряный\n";
    cout << "3. Золотой\n";

    cout << "\nВыберите уровень данжа: ";
    string vib = "";
    cin >> vib;
    if (vib == "1") {
        if (level <= 5) //проверка на уровень
        {
            cout << "\nВаш уровень слишком мал. Неоюходим 5 уровень";
            Sleep(2000);
            return 1;
        }
        system("cls");
        slychai();//рандомный случай (описан в отчете напарника)
        cout << "Вы спускаетесь в подземелье...";
        Sleep(1000);
        DangeEvents(); //рандомное событие в данже
        cout << "\nВы нашли сундук с золотом";
        gold += 20 * Random(1, 5);
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        DangeEvents();//рандомное событие в данже
        cout << "\nВы успешно прошли подземелье";
        Sleep(2000);
        return 1;
    } else if (vib == "2") {
        if (level <= 7) {
            cout << "\nВаш уровень слишком мал. Неоюходим 7 уровень";
            Sleep(2000);
            return 1;
        }
        system("cls");
        slychai();//рандомный случай (описан в отчете напарника)
        cout << "Вы спускаетесь в подземелье...";
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        cout << "\nВы нашли сундук с вещами";
        Veshi();//получение вещей (описанов отчете напарника)
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        DangeEvents();//рандомное событие в данже
        cout << "\nВпереди армия противника. Обнажить мечи! В атаку!";
        Sleep(1000);
        Battle();//бой с противником
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        int ran1 = Random(1, 10);
        if (ran1 == 1 || ran1 == 4 || ran1 == 10 || ran1 == 7 || ran1 == 2) {
            cout << "\nВ переди босс. К оружию!";
            Sleep(1000);
            Battle();//бой с противником
        } else if (ran1 == 3 || ran1 == 5 || ran1 == 6 || ran1 == 8 || ran1 == 8) {
            cout << "\nВы успешно прошли подземелье";
            Sleep(2000);
            return 1;
        }
    }
    if (vib == "3") {
        if (level <= 10) {
            cout << "\nВаш уровень слишком мал. Неоюходим 10 уровень";
            Sleep(2000);
            return 1;
        }
        system("cls");
        slychai();//рандомный случай (описан в отчете напарника)
        cout << "Вы спускаетесь в подземелье...";
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        cout << "\nВы нашли сундук с вещами";
        Veshi();//получение вещей (описанов отчете напарника)
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        DangeEvents();//рандомное событие в данже
        cout << "\nВпереди армия противника. Обнажить мечи! В атаку!";
        Sleep(1000);
        Battle();//бой с противником
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        cout << "\nВы нашли сундук с золотом";
        gold += 200 * Random(5, 15);
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        cout << "\nВы спускаетесь еще ниже....";
        Sleep(1000);
        DangeEvents();//рандомное событие в данже
        cout << "\nВпереди армия противника. Обнажить мечи! В атаку!";
        Sleep(1000);
        Battle();//бой с противником
        Sleep(1000);
        cout << "\nВы нашли сундук с золотом";
        gold += 200 * Random(5, 15);
        int ran1 = Random(1, 10);
        if (ran1 == 1 || ran1 == 4 || ran1 == 10 || ran1 == 7 || ran1 == 2) {
            cout << "\nВ переди босс. К оружию!";
            Sleep(1000);
            Battle();//бой с противником
        } else if (ran1 == 3 || ran1 == 5 || ran1 == 6 || ran1 == 8 || ran1 == 8) {
            cout << "\nВы успешно прошли подземелье";
            Sleep(2000);
            return 1;
        }
    }
    else
        goto pjkl;
    return 1;
}

int traktir_pool() //Один из 3 методов на случайное событие на работе
{
    int ran = 0;
    int res = 1;
    ran = Random(1, 12); //Генерируем число от 1 до 12
    if (ran == 3) //В зависимости от выпавшего
    {
        cout << "Ой, вы уронили стакан! Денег вы не получите!\n"; //Выводим сообщение, что денег не будет
        res = 0;
    }
    else if (ran == 5)
    {
        cout << "Вас нагло обманули и кинули на бабки\n";
        res = 0;
    }
    else if (ran == 8)
    {
        cout << "Вас заставили драить полы, но вы отказались и лишились зарплаты\n";
        res = 0;
    }
    else if (ran == 11)
    {
        cout << "Трактир обонкротился и поэтому денег за работу вы не получите";
        res = 0;
    }
    return res; //Возвращаем 1 или 0 (если 0, то денег не будет выплачено игроку)
}

int bordel_pool()
{
    int ran = 0;
    int res = 1;
    ran = Random(1, 12);
    if (ran == 3 || ran == 5 || ran == 8 || ran == 11)
    {
        cout << "Вас кинули на бабки и ничего не заплатили\n";
        res = 0;
    }
    return res;
}

int popr_pool()
{
    int ran = 0;
    int res = 1;
    ran = Random(1, 12);
    if (ran == 3 || ran == 5 || ran == 8 || ran == 11)
    {
        cout << "Увы, но все ваши деньги забрала полиция\n";
        res = 0;
    }
    return res;
}

int EarnMoney() {
    slychai(); //рандомное событие (описано в отчете напарника)
    start:

    cout << "1. Работать в трактире\n"; //выбор способов заработка
    cout << "2. Работать в борделе\n";
    cout << "З. Попрошайничать\n";
    cout << "4. Выйти в меню\n";

    cout << "\nВыберите способ заработка: ";
    string vib = "";
    cin >> vib;
    if (vib == "1")
    {
        if (level < 6)//проверка на уровень
        {
            cout << "Работа дотсупна с 6 уровня!\n\n";
            goto start;
        } else {
            system("cls");
            int i = 0;
            while (i < 100) {
                Sleep(800);    //задержка в 1000 миллисекунд (1 секунда)
                std::cout << "Работаю (" << i << "%)" << std::endl;
                i++;
            }
            int test = 1;
            test = traktir_pool();//рандомное событие, которое может выпасть во время работы (описано в отчете напарника)
            if (test == 1) {
                system("cls");
                int rand = 1000 * Random(2, 5);
                gold += rand;
                int rand1 = 100 * Random(1, 4);
                xp += rand1;
                cout << "Вы заработали " << rand << " золота\n";
                cout << "Вы заработали " << rand1 << " XP\n";
            }
            cout << "\n\n";
            goto start;
        }
    }
    else if (vib == "2")
    {
        if (level < 4) //проверка на уровень
        {
            cout << "Работа дотсупна с 4 уровня!\n\n";
            goto start;
        } else {
            system("cls");
            int i = 0;
            while (i < 100) {
                Sleep(600);    //задержка в 1000 миллисекунд (1 секунда)
                std::cout << "Работаю (" << i << "%)" << std::endl;
                i++;
            }
            int test = 1;
            test = bordel_pool();//рандомное событие, которое может выпасть во время работы (описано в отчете напарника)
            if (test == 1) {
                system("cls");
                int rand = 500 * Random(2, 5);
                gold += rand;
                int rand1 = 60 * Random(1, 6);
                xp += rand1;
                cout << "Вы заработали " << rand << " золота\n";
                cout << "Вы заработали " << rand1 << " XP\n";
            }
            cout << "\n\n";
            goto start;
        }
    }
    else if (vib == "3")
    {
        system("cls");
        int i = 0;
        while (i < 50) {
            Sleep(1000);    //задержка в 1000 миллисекунд (1 секунда)
            std::cout << "Работаю (" << i * 2 << "%)" << std::endl;
            i++;
        }
        int test = 1;
        test = popr_pool();//рандомное событие, которое может выпасть во время работы (описано в отчете напарника)
        if (test == 1) {
            system("cls");
            int rand = 100 * Random(1, 3);
            gold += rand;
            int rand1 = 40 * Random(1, 4);
            cout << "Вы заработали " << rand << " золота\n";
            cout << "Вы заработали " << rand1 << " XP\n";
        }
        cout << "\n\n";
        goto start;
    } else if (vib == "4")
        return 1;
    else
        goto start;
}

int kafe()
{
    system("cls"); //Очистка консоли
    slychai(); //Переходим в метод, в котором может произойти случайное событие
    int i = 0;
    string a = "";
    st1: cout << "\nВы желаете поесть за 150 монет?\n1. Да\n2. Нет\nВыбор: "; //Выбираем
    cin >> a;
    if (a == "1" && gold >= 150) //Если выбрано 1 и достаточно золота
    {
        gold -= 150;
        mozhnoornet = true;
    }
    else if (a == "2") //Если 2, то возврат в меню
        return 2;
    else if (gold < 150) //Если 1, но золота меньше 150
    {
        cout << "\nНедостаточно монет, чтобы поесть!";
        Sleep(1000);
        return 2;
    }
    else
        goto st1;
    music.pause(); //Фоновая музыка на паузе
    if (!music1.openFromFile("Eat.ogg"))
    {

    }
    music1.setVolume(50);//Звук хаванья еды
    music1.setLoop(true);
    music1.play(); //Воспроизведение звука хаванья еды
    while (i < 100) //Пока не будет 100%
    {
        std::cout << "Кушаю (" << i << "%)" << std::endl;
        Sleep(400);
        i++;
    }
    cout << "\nВы успешно поели\n";
    Sleep(2000);
    music1.stop(); //Остановка звука хаванья
    music.play(); //Воспроизведение фоновой
    return 1; //Возврат в меню
}

int bordel()
{
    system("cls"); //Очищаем консоль
    slychai(); //Переходим в метод, в котором может произойти случайное событие
    int i = 0;
    string a = "";
    if (level < 2) //Проверка на уровень
    {
        cout << "Бордель доступен с 2 уровня!";
        Sleep(3000);
    }
    else
    {
        if (gold < 200) //Проверка на наличие денег
        {
            cout << "Недостаточно денег для посещения борделя. Требуется 200 золота!";
            Sleep(3000);
            return 1;
        }
        gold -= 200; //Списывается 200 золота
        cout << "Добро пожаловать в бордель!\n";
        cout << "За вход списано 200 золота\n";
        stt1: cout << "\nВыберите свою принадлежность: \n1. Gay-party\n2. Натурал\nВыбор: ";
        cin >> a;
        int g = 0;
        if (a == "1") //Если выбрана "гей" принадлежность
        {
            music.pause(); //Фоновая музыка ставиться на паузу
            if (!music1.openFromFile("gachi.ogg")) //Включается другая музыка
            {

            }
            music1.setVolume(50); //Громкость другой музыки
            music1.setLoop(true); //Повторность другой музыкт
            music1.play(); //Воспроизвести другую музыку
            while (i < 100) //Пока i<100
            {
                Sleep(500);    //задержка
                std::cout << "Процесс гей-вечеринки (" << i << "%)" << std::endl;
                i++;
            }
            cout << "Вы завершили...\n";
            mozhnoornet = true; //Можно снова участвовать в боях
            g = Random(1, 15); //Рандомное число от 1 до 15
            if (g == 7) //Если рандомное число равно 7
            {        //То игрок заражется ВИЧ
                cout << "Вы заразились ВИЧ-инфекцией...\n";
                cout << "На лекарства каждый бой вы будете тратить по 100 золота\n";
                vich = true;
            }
            Sleep(5000);
            music1.stop(); //Остановка гачи музыки
            music.play(); //Воспроизведение фоновой музыки
            return 1;
        }
            //То же самое, как и в "гей"
        else if (a == "2")
        {
            while (i < 100)
            {
                Sleep(500);    //задержка
                std::cout << "Процесс ... (" << i << "%)" << std::endl;
                i++;
            }
            cout << "Вы завершили...\n";
            mozhnoornet = true;
            Sleep(3000);
            g = Random(1, 15);
            if (g == 7)
            {
                cout << "Вы заразились ВИЧ-инфекцией...\n";
                cout << "На лекарства каждый бой вы будете тратить по 100 золота\n";
                vich = true;
            }
        }
        else
            goto stt1;
        Sleep(3000);
        return 1; //Возврат в меню
    }
    return 1;
}

int menu_army()
{
    for (int h = 0; h < 10; h++)
    {//Сканируем весь массив армии
        if (army[h][0] != "") //Если нулевая ячейка не равна нулю, то выводим данные об армии
        {
            cout << "\nВаша армия '" << army[h][0] << "':";
            cout << "\nАтака (итог): " << army[h][1];
            cout << "\nЗащита (итог): " << army[h][2];
            cout << "\nЗдоровье (итог): " << army[h][3];
            cout << "\nРегенерация (итог): " << army[h][3];
            cout << "\nТип атаки: " << army[h][5];
            cout << "\nИтоговая численнсть: " << army[h][6];
            cout << "\n\n";
        }
    }
    char ch;
    int code;
    cout << "\n\nДля возврата в меню - нажмите Enter"; //Возвращаемся в меню
    while (1)
    {
        ch = _getch();
        code = static_cast<int>(ch);
        if (ch == 13) // если клавиша Enter
            return 1;
    }
    return 1;
}

int cheat(string kod)
{
    if (kod == "more__gold") //Чит-код на деньги
    {
        cout << "\n\nЧит-код активирован";
        cout << "\n>>> +5000 монет";
        gold += 5000;
        Sleep(3000);
    }
    else if (kod == "more__xp") //Чит-код на xp
    {
        cout << "\n\nЧит-код активирован";
        cout << "\n>>> +1000 опыта";
        xp += 1000;
        Sleep(3000);
    }
    else if (kod == "+HEAL+") //Чит-код на + к здоровью
    {
        cout << "\n\nЧит-код активирован";
        cout << "\n>>> ВИЧ излечён";
        vich = false;
        Sleep(3000);
    }
    else if (kod == "Kopss_mpt666" || kod == "Land_aezakmi" || kod == "ricar_cheat")
    { //Чит-коды на получение в армию по N бойцов определённого типа (до 10 максимум)
        int j = 0;
        if (kod == "Kopss_mpt666")
            j = 4; //Индекс в массиве
        else if (kod == "Land_aezakmi")
            j = 5;
        else if (kod == "ricar_cheat")
            j = 6;
        int h = 0;
        bool iii = true;
        for (int i = 0; i < 10; i++) //Находим свободную ячейку
        {
            if (army[i][0] == mas[j][0]) //Если уже есть такой тип войск
            {							//То записываем её индекс
                h = i;
                iii = false;
                break;
            }
        }
        if (iii)
        {
            for (int i = 0; i < 10; i++) //Находим свободную ячейку
            {
                if (army[i][0] == "") //Если находим пустую, то записываем в пустую
                {
                    h = i;
                    break;
                }
            }
        }
        int kolvo = 5;
        while (atoi(army[h][6].c_str()) + kolvo > 10) //Если в армии при добавлении
        {					//5 войск выходит больше 5, то прибавляем только наименьшее до 10
            kolvo--;
        }

        if (kolvo == 0) //Если и так уже 10
        {
            cout << "В вашей армии находится " << atoi(army[h][6].c_str()) << " юнитов данного типа\n";
            cout << "Максимальное кол-во юнитов в отряде 10\n\n";
            Sleep(3000);
        }
        else
        { //Записываем в армию
            army[h][0] = mas[j][0];
            army[h][1] = to_string(atoi(mas[j][1].c_str()) * kolvo + atoi(army[h][1].c_str()));
            army[h][2] = to_string(atoi(mas[j][2].c_str()) * kolvo + atoi(army[h][2].c_str()));
            army[h][3] = to_string(atoi(mas[j][3].c_str()) * kolvo + atoi(army[h][3].c_str()));
            army[h][4] = to_string(atoi(mas[j][4].c_str()) * kolvo + atoi(army[h][4].c_str()));
            army[h][5] = mas[j][6];
            army[h][6] = to_string(kolvo + atoi(army[h][6].c_str()));
            system("cls"); //Выводим информацию об армии
            cout << "\nЧит-код активирован";
            cout << "\n>>> В армию прибавлено " << kolvo << " войск";
            cout << "\nВаша армия '" << army[h][0] << "':";
            cout << "\nАтака (итог): " << army[h][1];
            cout << "\nЗащита (итог): " << army[h][2];
            cout << "\nЗдоровье (итог): " << army[h][3];
            cout << "\nРегенерация (итог): " << army[h][4];
            cout << "\nТип атаки: " << army[h][5];
            cout << "\nИтоговая численнсть: " << army[h][6];
        }
        char ch;
        int code;
        cout << "\n\nДля возврата в меню - нажмите Enter"; //Возвращаемся в меню
        while (1)
        {
            ch = _getch();
            code = static_cast<int>(ch);
            if (ch == 13) // если клавиша Enter
            {
                return 1;
            }
        }
    }
        //то же самое, что и выше, только другие коды
    else if (kod == "Luchnik_SZCMAWO" || kod == "Arbalet_AFPHULTL" || kod == "LuchnikTwo_HESOYAM" || kod == "TANK_AEDUWNV")
    {
        int j = 0;
        if (kod == "Luchnik_SZCMAWO")
            j = 0;
        else if (kod == "Arbalet_AFPHULTL")
            j = 1;
        else if (kod == "LuchnikTwo_HESOYAM")
            j = 2;
        else if (kod == "TANK_AEDUWNV")
            j = 3;
        int h = 0;
        bool iii = true;
        for (int i = 0; i < 10; i++) //Находим свободную ячейку
        {
            if (army[i][0] == mas[j][0]) //Если уже есть такой тип войск
            {							//То записываем её индекс
                h = i;
                iii = false;
                break;
            }
        }
        iii = true;
        if (iii)
        {
            for (int i = 0; i < 10; i++) //Находим свободную ячейку
            {
                if (army[i][0] == "") //Если находим пустую, то записываем в пустую
                {
                    h = i;
                    break;
                }
            }
        }
        int kolvo = 5;
        while (atoi(army[h][6].c_str()) + kolvo > 10)
        {
            kolvo--;
        }

        if (kolvo == 0)
        {
            cout << "В вашей армии находится " << atoi(army[h][6].c_str()) << " юнитов данного типа\n";
            cout << "Максимальное кол-во юнитов в отряде 10\n\n";
            Sleep(3000);
        }
        else
        {
            army[h][0] = mas[j][0];
            army[h][1] = to_string(atoi(mas[j][1].c_str()) * kolvo + atoi(army[h][1].c_str()));
            army[h][2] = to_string(atoi(mas[j][2].c_str()) * kolvo + atoi(army[h][2].c_str()));
            army[h][3] = to_string(atoi(mas[j][3].c_str()) * kolvo + atoi(army[h][3].c_str()));
            army[h][4] = to_string(atoi(mas[j][4].c_str()) * kolvo + atoi(army[h][4].c_str()));
            army[h][5] = mas[j][6];
            army[h][6] = to_string(kolvo + atoi(army[h][6].c_str()));
            system("cls");
            cout << "\nЧит-код активирован";
            cout << "\n>>> В армию прибавлено " << kolvo << " войск";
            cout << "\nВаша армия '" << army[h][0] << "':";
            cout << "\nАтака (итог): " << army[h][1];
            cout << "\nЗащита (итог): " << army[h][2];
            cout << "\nЗдоровье (итог): " << army[h][3];
            cout << "\nРегенерация (итог): " << army[h][4];
            cout << "\nТип атаки: " << army[h][5];
            cout << "\nИтоговая численнсть: " << army[h][6];
        }
        char ch;
        int code;
        cout << "\n\nДля возврата в меню - нажмите Enter";
        while (1)
        {
            ch = _getch();
            code = static_cast<int>(ch);
            if (ch == 13) // если клавиша Enter
            {
                return 1;
            }
        }
    }
    return 1;
}

void MainMenu()
{
    system("cls"); //Очистка
    LevelUp(); //Проверка уровня по количеству XP (Делал Павел Кононенков)
    cout << "1. Бой\n";
    cout << "2. Данж\n";
    cout << "З. Заработать деньги\n";
    cout << "4. Магазин армии\n";
    cout << "5. Кафе\n";
    cout << "6. Бордель\n";
    cout << "7. Меню игрока\n";
    cout << "8. Армия персонажа\n";

    cout << "\nВыберите, куда пойти: "; //Выбираем пункт меню
    string vib;
    cin >> vib;
    if (vib == "1") {
        system("cls");
        Battle(); //Перенос в метод боя (Делал Павел Кононенков)
        MainMenu(); //После битвы возврат в галвное меню
    }
    else if (vib == "2")
    {
        system("cls"); //Очистка консоли
        Dange(); //Перенос в нужный метод
        MainMenu(); //Возврат в меню после действия
    }
    else if (vib == "3")
    {
        system("cls");
        EarnMoney();
        MainMenu();
    }
    else if (vib == "4")
    {
        system("cls");
        ChooseUnit();
        MainMenu();
    }
    else if (vib == "5")
    {
        kafe();
        MainMenu();
    }
    else if (vib == "6")
    {
        bordel();
        MainMenu();
    }
    else if (vib == "7")
    {
        menu_igroka();
        MainMenu();
    }
    else if (vib == "8")
    {
        menu_army();
        MainMenu();
    }
    else //если не 1-8
    {
        cheat(vib); //Перенос в метод читов, куда передаём строку ввода выбора
        MainMenu(); //Возврат в меню
    }
}

void Luchnik()
{
    health = 100; //Здоровье
    max_health = health; //Максимальное здоровье
    gold = 1500; //Золото
    zashita = 50; //Защита
    magsila = 75; //Магическая сила
}

void Voin()
{
    health = 150;
    max_health = health;
    gold = 1500;
    zashita = 70;
    magsila = 55;
}

void Mag()
{
    health = 70;
    max_health = health;
    gold = 1500;
    zashita = 40;
    magsila = 100;
}

int Races()
{
    string races[5] = {
            "Люди",
            "Эльфы",
            "Темные эльфы",
            "Орки",
            "Дворфы"
    };
    int number = 1;
    cout << "\n\n\n\n";
    for (int i = 0; i < 5; i++)
    {
        cout << number << ". " << races[i] << "\n";
        number++;
    }
    stttt1:
    cout << "\n";
    cout << "\nВыберите расу персонажа: ";
    string r1 = "";
    cin >> r1;
    int r = 0;
    if (r1 == "1")
    {
        r = atoi(r1.c_str());
        race = races[r - 1];
    }
    else if (r1 == "2")
    {
        r = atoi(r1.c_str());
        race = races[r - 1];
        health -= 30;
        max_health -= 30;
        magsila += 100;
    }
    else if (r1 == "3")
    {
        r = atoi(r1.c_str());
        race = races[r - 1];
        health -= 10;
        max_health -= 30;
        magsila += 70;
    }
    else if (r1 == "4")
    {
        r = atoi(r1.c_str());
        race = races[r - 1];
        health += 50;
        max_health += 100;
        magsila -= 50;
    }
    else if (r1 == "5")
    {
        r = atoi(r1.c_str());
        race = races[r - 1];
        health += 30;
        max_health += 30;
        magsila -= 20;
    }
    else
        goto stttt1;
    return 1;
}

int t1()
{
    st2: cout << "\nВведите имя персонажа: "; //Вводим имя персонажа
    getline(cin, name);
    if (name == "") //Если строка пустая, то ошибка
        goto st2;
    st1: cout << "\n\n\n\n\n"; //Отступ
    cout << "1. Лучник\n";
    cout << "2. Воин\n";
    cout << "3. Маг\n";
    cout << "Выберите класс персонажа: "; //Выбор класса
    cin >> klass;						//В завимости от выбора будут
    if (klass == "1")					//определённые характеристики
    {
        klass = "Лучник"; //Присваиваем низвание класса
        Luchnik(); //Получаем характеристики класса
    }
    else if (klass == "2")
    {
        klass = "Воин";
        Voin();
    }
    else if (klass == "3")
    {
        klass = "Маг";
        Mag();
    }
    else
        goto st1;
    Races();
    MainMenu(); //Переходим в метод главного меню
    return 1;
}

int main()
{
    /*SetConsoleCP(1251);//Языковые параметры вывода в консоль
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");*/
    system("chcp 65001");
    if (!music.openFromFile("astronomia.ogg")) //Включение фоновой музыки
    { }
    music.setVolume(50); //Установка громкости фоновой музыка
    music.setLoop(true); //Повторение фоновой музыки
    music.play(); //Воспроизведением фоновой музыки
    t1(); //Перенос в метод выбора класса и ввода имени персонажа
}
