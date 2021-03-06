#include <stdio.h>  // printf() scanf()
#include <stdlib.h> // free()

#include "message_queue/message_queue.h"
#include "my_ftoa/my_ftoa.h"
#include "print_real_time/print_real_time.h"

int main(void)
{
    double a, b, c;                                     // стороны треугольника

    printf("a = ");
    scanf("%lf", &a);                                   // ввод стороны треугольника A

    printf("b = ");
    scanf("%lf", &b);                                   // ввод стороны треугольника B

    printf("c = ");
    scanf("%lf", &c);                                   // ввод стороны треугольника С

    if (!(a + b > c))                                   // условие существование треугольника
    {
        printf("Not triangle\n");
        return 0;
    }

    char* string_a = my_ftoa(a);                        // double to char*
    char* string_b = my_ftoa(b);                        // double to char*
    char* string_c = my_ftoa(c);                        // double to char*

    print_real_time();
    mqd_t queue_send_a_b_c = get_opened_message_queue("/abc");  // открытие очереди /abc

    print_real_time();
    send_message_queue(string_a, queue_send_a_b_c);     // отправка сообщения в очередь /abc
    free(string_a);                                     // очистка памяти

    print_real_time();
    send_message_queue(string_b, queue_send_a_b_c);     // отправка сообщения в очередь /abc
    free(string_b);                                     // очистка памяти

    print_real_time();
    send_message_queue(string_c, queue_send_a_b_c);     // отправка сообщения в очередь /abc
    free(string_c);                                     // очистка памяти

    print_real_time();
    mqd_t queue_get_s = get_opened_message_queue("/s"); // открытие очереди /s

    print_real_time();
    reveiving_message_queue(queue_get_s);               // принятие сообщения из очереди /s

    print_real_time();
    delete_message_queue("/s");                         // удаление очереди /s

    return 0;
}