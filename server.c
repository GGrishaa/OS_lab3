// Лабораторная работа 1; Вариант 17; СЕРВЕР

/* Сервер: Создать очередь сообщений. Записать в качестве 1-го сообщения
идентификаторы всех процессов, принадлежащих данному пользователю, в качестве
2-го сообщения - приоритеты этих процессов, в качестве 3-го сообщения -
суммарное рабочее время, затраченное этими процессами, в качестве 4-го сообщения
- имена задействованных терминалов. */

#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

struct my_msg {
  long mtype;
  char mtext[4096];
};

int main() {
  int msgid = msgget(12345, IPC_CREAT | 0666);
  if (msgid == -1) {
    printf("Ошибка создания очереди\n");
    return 1;
  }
  printf("Очередь успешно создана; ID=%d\n", msgid);

  FILE* fp1 = popen("ps -u grigorijmironov -o pid= | head -100 | xargs", "r");
  if (fp1 == NULL) {
    printf("Ошибка popen 1\n");
    return 1;
  }

  struct my_msg msg1;
  msg1.mtype = 1;
  memset(msg1.mtext, '\0', sizeof(msg1.mtext));
  fgets(msg1.mtext, sizeof(msg1.mtext), fp1);
  pclose(fp1);

  if (msgsnd(msgid, &msg1, strlen(msg1.mtext) + 1, IPC_NOWAIT) == -1) {
    printf("Ошибка msgsnd 1\n");
    return 1;
  }
  printf("Сообщение 1 успешно отправлено\n");

  FILE* fp2 = popen("ps -u grigorijmironov -o nice= | head -100 | xargs", "r");
  if (fp2 == NULL) {
    printf("Ошибка popen 2\n");
    return 1;
  }

  struct my_msg msg2;
  msg2.mtype = 2;
  memset(msg2.mtext, '\0', sizeof(msg2.mtext));
  fgets(msg2.mtext, sizeof(msg2.mtext), fp2);
  pclose(fp2);

  if (msgsnd(msgid, &msg2, strlen(msg2.mtext) + 1, IPC_NOWAIT) == -1) {
    printf("Ошибка msgsnd 2\n");
    return 1;
  }
  printf("Сообщение 2 успешно отправлено\n");

  FILE* fp3 = popen(
      "ps -u grigorijmironov -o time= | head -100 | awk -F: '{print ($1 * 60) "
      "+ $2}' | awk '{sum += $1} END {print sum}'",
      "r");
  if (fp3 == NULL) {
    printf("Ошибка popen 3\n");
    return 1;
  }

  struct my_msg msg3;
  msg3.mtype = 3;
  memset(msg3.mtext, '\0', sizeof(msg3.mtext));
  fgets(msg3.mtext, sizeof(msg3.mtext), fp3);
  pclose(fp3);

  if (msgsnd(msgid, &msg3, strlen(msg3.mtext) + 1, IPC_NOWAIT) == -1) {
    printf("Ошибка msgsnd 3\n");
    return 1;
  }
  printf("Сообщение 3 успешно отправлено\n");

  FILE* fp4 = popen("ps -u grigorijmironov -o tty= | grep -v '?' | xargs", "r");
  if (fp4 == NULL) {
    printf("Ошибка popen 4\n");
    return 1;
  }

  struct my_msg msg4;
  msg4.mtype = 4;
  memset(msg4.mtext, '\0', sizeof(msg4.mtext));
  fgets(msg4.mtext, sizeof(msg4.mtext), fp4);
  pclose(fp4);

  if (msgsnd(msgid, &msg4, strlen(msg4.mtext) + 1, IPC_NOWAIT) == -1) {
    printf("Ошибка msgsnd 4\n");
    return 1;
  }
  printf("Сообщение 4 успешно отправлено\n");

  return 0;
}