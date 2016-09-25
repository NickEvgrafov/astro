//-----------------------------------------------------------------------------//
// Общие функции для работы с сетью

#ifndef __COMMON_NETWORK_H__
#define __COMMON_NETWORK_H__

#include <netinet/in.h>

/**
 * Создать tcp-сокет.
 * Если не удалось, то вывести сообщение и завершиться
 */
int create_tcp_socket();

/**
 * Сделать сокет переиспользуемым, чтобы не ждать 2 минуты после завершения.
 * Если не удалось, то завершиться
 */
void set_reuse_addr_opt(int sockfd);

/// Привязать серверный сокет к определенному порту
/**
 * Если ошибка, то выдать сообщение и завершить программу
 */
void bind_server_socket(int sockfd, uint16_t port);

/**
 * Сделать сокет прослушиваемым.
 * Если не удалось, то завершиться.
 */
void listen_tcp_socket(int sockfd);

/// Принять новое клиентское соединение. 
/**
 * Обрабатывает прерывание по сигналу.
 * Если произошла ошибка, то завершиться
 * @param masterSockFd - прослушиваемый tcp-сокет
 * @param clientInAddr != 0 - структура IPv4 адреса клиента
 */
int accept_client_connection(
    int masterSockFd,
    struct sockaddr_in* clientInAddr);

#endif
