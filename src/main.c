 #include <server.h>
 #include <sys/types.h>
 #ifndef _WIN32
 #include <sys/select.h>
 #include <sys/socket.h>
 #else
 #include <winsock2.h>
 #endif
 #include <microhttpd.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 #if defined(_MSC_VER) && _MSC_VER+0 <= 1800
 /* Substitution is OK while return value is not used */
 #define snprintf _snprintf
 #endif

 #define PORT            8888
 #define POSTBUFFERSIZE  512
 #define MAXNAMESIZE     2000
 #define MAXANSWERSIZE   512

 #define GET             0
 #define POST            1

int main()
{
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon (MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                             &answer_to_connection, NULL,
                             MHD_OPTION_NOTIFY_COMPLETED, request_completed,
                             NULL, MHD_OPTION_END);
  if (NULL == daemon)
    return 1;

  (void) getchar ();

  MHD_stop_daemon (daemon);

  return 0;
}
