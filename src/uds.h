#define UDS_MESSAGE_START "s"
#define UDS_MESSAGE_END "e"
#define UDS_PATH "/tmp/latency_tester_socket"

extern int uds_fd;
extern int uds_running;
extern int render_start_flag;
extern struct sockaddr_un address;

void uds_init();
void uds_send_start();
void uds_send_end();
void uds_send_message(const char* message);
void uds_run();
void uds_close();
