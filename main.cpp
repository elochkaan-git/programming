#include <iostream>

void switcher(int* armor, int pos) {
    *(armor + pos - 1) = !(*(armor + pos - 1));
}

bool is_active(int* armor, int pos) {
    return *(armor + pos - 1);
}

char activities_counter(int* armor) {
    char temp = 0;
    for(char i = 0; i < 5; i++) {
        if(*(armor + i)) {
            temp++;
        }
    }
    return temp;
}

std::string attention(int* armor) {
    if(!(*(armor)) && !(*(armor+3)) {
        return "YOU HAVE BEEN NOTICED 👁";
    }
    if(!(*(armor+1)) && !(*(armor+2))) {
        return "YOU HAVE BEEN NOTICED 👁";
    }
    return "Did I hear that?";
}

int main() {

    /* ВЫ ДОПУСТИЛИ ПОТЕРЮ ДОРОГОСТОЯЩЕГО ОБМУНДИРОВАНИЯ
    0 - Невидимость
    1 - Беззвучие
    2 - Подавление волн инфракрасного спектра
    3 - Подавление радиоволн
    4 - Энергосберегательный режим
    */

    int armor[5]{true, true, true, true, true};

    /* Проверяйте работоспособность в дебагере! */
    switcher(armor, 1);
    bool response_1 = is_active(armor, 2);
    char response_2 = activities_counter(armor);
    std::string response_3 = attention(armor);
    switcher(armor, 2);
    switcher(armor, 3);
    switcher(armor, 4);
    switcher(armor, 5);
    std::string response_4 = attention(armor);
    return 0;
}