#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[], char *envp[])//Аргумент argv представляет собой массив из указателей на аргументы командной строки
{
printf ("Лабораторная работа №3 Рыбаков А.С. ИСТбд-21\n");
	if (fork()==0)//если идентификатор текущего процесса равен 0 ( то есть если создание прошло успешно)
		execle("/bin/cat", "/bin/cat", "main.c", envp); //то, заменяется пользовательский контекст текущего процесса содержимым
//исполняемого файла и устанавливаются начальные значения регистров процессора
	else {
        char** env;
        for (env = envp; *env != 0; env++)
        {
            char* thisEnv = *env;
            printf("%s\n", thisEnv);
        }
	}
return 0;
}
