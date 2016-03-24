/********************************************************************
* Description: tcpmem.hh
*
*   Derived from a work by Fred Proctor & Will Shackleford
*
* Author:
* License: GPL Version 2
* System: Linux
*    
* Copyright (c) 2004 All rights reserved.
*
* Last change: 
********************************************************************/

#ifndef TCPMEM_HH
#define TCPMEM_HH

#include "cms.hh"		/* class CMS */
#include "rem_msg.hh"		// REMOTE_CMS_REQUEST_TYPE

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
class TCPMEM:public CMS {
  public:
    TCPMEM(const char *bufline, const char *procline);
    virtual ~ TCPMEM() override;

    /* Overloaded CMS functions. */
    CMS_STATUS clear() override;
    int check_if_read() override;
    int get_msg_count() override;
    int get_queue_length() override;
    int get_space_available() override;
    CMS_STATUS read() override;
    CMS_STATUS blocking_read(double) override;
    CMS_STATUS peek() override;
    CMS_STATUS write(void *data, int *serial_number_out) override;
    CMS_STATUS write_if_read(void *data, int *serial_number_out) override;
//    int login(const char *, const char *) override;
    void reconnect() override;
    void disconnect() override;
    CMS_DIAGNOSTICS_INFO *get_diagnostics_info() override;

  protected:
      CMS_STATUS handle_old_replies();
    void send_diag_info();
    char diag_info_buf[0x400];
    int recvd_bytes;
    long serial_number;
    long returned_serial_number;
    int subscription_type;
    int poll_interval_millis;
    struct hostent *server_host_entry;
    struct sockaddr_in server_socket_address;
    int socket_fd;
    char temp_buffer[0x2000];
    REMOTE_CMS_REQUEST_TYPE timedout_request;
    long bytes_to_throw_away;
    int polling;
    int write_socket_fd;
    int read_socket_fd;
    long write_serial_number;
    long read_serial_number;
    void set_socket_fds(int new_fd);
    CMS_STATUS timedout_request_status;
    unsigned long timedout_request_writeid;
    int max_consecutive_timeouts;
    int waiting_for_message;
    unsigned long waiting_message_size;
    unsigned long waiting_message_id;
    int autoreconnect;
    int reconnect_needed;
    int sigpipe_count;
    void (*old_handler) (int);
    void disable_sigpipe();
    void reenable_sigpipe();
    void verify_bufname();
    int subscription_count;
};

#endif
