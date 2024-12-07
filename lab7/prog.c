//3 номер

#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "Lorem ipsum dolaaaaaaaor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int mx_count = 0, count = 0;
    char wort_print[256],word[256];
    for (int i = 0, j = 0; i <= strlen(s); i++) {//иду по массиву
        if (s[i] == 'a' || s[i] == 'A') {
            count++;//считаю буквы а
        }
        if (s[i]!=' ' && s[i]!='\0'){
            word[j]=s[i];
            j++;
        } else {
            word[j] = '\0';//записываю каждое слово до пробела или конца строки
            if (mx_count<count){
                mx_count=count;
                strcpy(wort_print,word);//смотрю максимальное кол-во 'а' в слове, и если true пишу записываю его в массив для вывода 
            }
            j=0;
            count=0;//обнуляю счётчик символов, и счётчик длины слова
        }
    }
    printf("слово: %s; кол-во букв 'a': %d\n",wort_print,mx_count);
}
