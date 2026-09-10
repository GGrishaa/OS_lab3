// Лабораторная работа 1; Вариант 17; КЛИЕНТ 1

/* Клиент 1: Определить общее число байтов во всех сообщениях очереди. */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int msgid = msgget(12345, 0);
  if (msgid == -1) {
    printf("Очередь с ключом 12345 не найдена, ожидаем 60 секунд\n");
    sleep(60);
    msgid = msgget(12345, 0);
    if (msgid == -1) {
      printf("Очередь с ключом 12345 не найдена\n");
      return 1;
    }
  }

  struct msqid_ds stat;
  if (msgctl(msgid, IPC_STAT, &stat) == -1) {
    printf("Ошибка получения статистики очереди\n");
    return 1;
  }

  printf("Общее число байт в очереди на данный момент: %lu\n", stat.msg_cbytes);

  return 0;
}