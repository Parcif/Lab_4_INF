#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void check_string(ifstream& file, string res)
{
    for (int i = 0; i < res.size(); i++)
    {
        if (isalpha(res[i]) == 0)
            throw runtime_error("\nАхтунг!!! Обнаружен символ - не буква!!!\n");
            
    }
}

void filefillarray(vector<string>& vec)
{
    string name; name = "words.txt";
    //cin >> name;

    ifstream file;
    file.open(name);
    
    if (file.is_open())  // Проверка отрылся файл или нет
        cout << "\nВсе хорошо! Файл открыт!" << endl;
    else
    {
        cout << "\nФайл не открыт!" << endl;
        throw runtime_error("\nЧто то пошло не так!\n");
    }

    for(int i = 0; !file.eof(); i++)
    {
        string inp;
        getline(file, inp);
        check_string(file, inp);
        vec.push_back(inp);
    }

    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << "\n";

}



int main()
{
    setlocale(LC_ALL, "ru");
    vector<string> vec;
    try 
    {
        filefillarray(vec);
    }
    catch (runtime_error& e)
    {
        cout << e.what();
    }

}
