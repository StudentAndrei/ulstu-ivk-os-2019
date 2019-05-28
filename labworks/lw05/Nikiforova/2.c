#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{

    printf("Nikiforova Alevtina\n");
    printf("ISTbd-21\n Lab 4.1\n");

    int *array; /*Указатель на разделяемую память*/
    int shmid; /*IPC дескриптор для области разделяемой памяти*/
    int new = 1; /*Флаг необходимости инициализации элементов массива*/
    char pathname[] = "/home/alya/Рабочий стол/labar/os4.1/key";
    key_t key; /*IPC ключ*/

    /*Генерируем IPC*/
    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Не удаётся сгенерировать ключ\n");
        exit(-1);
    }

    /*Создание разделяемой памяти*/
    if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
        /*Анализ ошибки создания*/
        if (errno != EEXIST)
        {
            /*прочие ошибки*/
            printf("Не удаётся создать разделяемую память \n");
            exit(-1);
        }
        else
        {
            /*Память уже существует*/
            if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0)
            {
                printf("Не удаётся создать разделяемую память \n");
                exit(-1);
            }
            new = 0;
        }
    }

    /*Отобржение разделяемой памяти в адресное пространство текущего
    процесса. Обратите внимание на то, что для правильного сравнения
    мы явно преобразовываем значение -1 к указателю на целое*/
    if ((array = (int*)shmat(shmid, NULL, 0)) == (int*)(-1))
    {
        printf("Не удаётся присоединить разделяемую память \n");
        exit(-1);
    }

    /*В зависимости от значения флага либо инициализируем массив,
    либо увеличиваем соответствующие счетчики*/
    if (new)
    {
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
    }
    else
    {
        array[1] += 1;
        array[2] += 1;
    }

    /*Печатаем новые значения счетчиков, удаляем разделяемую память из
    адресного пространства текущего процесса и завершаем работу*/
    printf("Программа 1 была создана %d раз(а), программа 2 - %d раз(а), всего - %d раз(а)\n",
    array[0], array[1], array[2]);

    if (shmdt(array) < 0)
    {
        printf("Не удаётся отсоединить разделяемую память \n");
        exit(-1);
    }
    return 0;
}
