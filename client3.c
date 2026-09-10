// Лабораторная работа 1; Вариант 17; КЛИЕНТ 3

/* Клиент 3: Прочитать 3-е сообщение из очереди и вывести его на печать. Удалить
 * очередь сообщений. */

#include <errno.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>

struct my_msg {
  long mtype;
  char mtext[256];
};

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

  struct my_msg msg3;
  if (msgrcv(msgid, &msg3, sizeof(msg3.mtext), 3, IPC_NOWAIT) == -1) {
    if (errno == ENOMSG)
      printf("Ошибка прочтения третьего сообщения из очереди\n");
    else
      printf("Ошибка получения третьего сообщения\n");
  } else
    printf("Содержимое третьего сообщения: %s\n", msg3.mtext);

  if (msgctl(msgid, IPC_RMID, NULL) == -1) {
    printf("Ошибка удаления очереди сообщений\n");
    return 1;
  }

  printf("Очередь сообщений успешно удалена!\n");

  return 0;
}