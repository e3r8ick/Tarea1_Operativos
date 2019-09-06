#ifndef SERVERPH_H
#define SERVERPH_H

#include <string.h>
#include <stdio.h>
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

enum ConnectionType
{
  GET = 0,
  POST = 1
};


/**
* Information we keep per connection.
*/
struct connection_info_struct
{
  enum ConnectionType connectiontype;

  /**
   * Handle to the POST processing state.
   */
  struct MHD_PostProcessor *postprocessor;

  /**
   * File handle where we write uploaded data.
   */
  FILE *fp;

  /**
   * HTTP response body we will return, NULL if not yet known.
   */
  const char *answerstring;

  /**
   * HTTP status code we will return, 0 for undecided.
   */
  unsigned int answercode;
};


int send_page (struct MHD_Connection *connection,
               const char *page,
               int status_code);

int iterate_post (void *coninfo_cls,
             enum MHD_ValueKind kind,
             const char *key,
             const char *filename,
             const char *content_type,
             const char *transfer_encoding,
             const char *data,
             uint64_t off,
             size_t size);

 void request_completed (void *cls,
                  struct MHD_Connection *connection,
                  void **con_cls,
                  enum MHD_RequestTerminationCode toe);

int answer_to_connection (void *cls,
                    struct MHD_Connection *connection,
                    const char *url,
                    const char *method,
                    const char *version,
                    const char *upload_data,
                    size_t *upload_data_size,
                    void **con_cls);

#endif
