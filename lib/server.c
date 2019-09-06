/*tomado de https://www.gnu.org/software/libmicrohttpd/tutorial.html#largepost_002ec*/

/* Feel free to use this example code in any way
   you see fit (Public Domain) */
#include <server.h>

#ifdef _MSC_VER
#ifndef strcasecmp
#define strcasecmp(a,b) _stricmp((a),(b))
#endif /* !strcasecmp */
#endif /* _MSC_VER */

#if defined(_MSC_VER) && _MSC_VER+0 <= 1800
/* Substitution is OK while return value is not used */
#define snprintf _snprintf
#endif

#define POSTBUFFERSIZE  512
#define MAXCLIENTS      2

static unsigned int nr_of_uploading_clients = 0;

const char *askpage = "<html><body>\n\
                     Upload a file, please!<br>\n\
                     <form action=\"/filepost\" method=\"post\" enctype=\"multipart/form-data\">\n\
                     <input name=\"file\" type=\"file\">\n\
                     <input name=\"client\" type=\"hidden\" value=\"0\">\n\
                     <input name=\"op\" placeholder=\"Operacion\" type=\"text\">\n\
                     <input type=\"submit\" value=\" Send \"></form>\n\
                     </body></html>";
const char *busypage =
"<html><body>This server is busy, please try again later.</body></html>";
const char *completepage =
"<html><body>The upload has been completed.</body></html>";
const char *errorpage =
"<html><body>This doesn't seem to be right.</body></html>";
const char *servererrorpage =
"<html><body>Invalid request.</body></html>";
const char *fileexistspage =
"<html><body>This file already exists.</body></html>";
const char *fileioerror =
"<html><body>IO error writing to disk.</body></html>";
const char* const postprocerror =
"<html><head><title>Error</title></head><body>Error processing POST data</body></html>";


int send_page (struct MHD_Connection *connection,
         const char *page,
         int status_code)
{
int ret;
struct MHD_Response *response;

response =
  MHD_create_response_from_buffer (strlen (page),
                                   (void *) page,
           MHD_RESPMEM_MUST_COPY);
if (!response)
  return MHD_NO;
MHD_add_response_header (response,
                         MHD_HTTP_HEADER_CONTENT_TYPE,
                         "text/html");
ret = MHD_queue_response (connection,
                          status_code,
                          response);
MHD_destroy_response (response);

return ret;
}


int iterate_post (void *coninfo_cls,
            enum MHD_ValueKind kind,
            const char *key,
            const char *filename,
            const char *content_type,
            const char *transfer_encoding,
            const char *data,
            uint64_t off,
            size_t size)
{
struct connection_info_struct *con_info = coninfo_cls;
FILE *fp;
(void)kind;               /* Unused. Silent compiler warning. */
(void)content_type;       /* Unused. Silent compiler warning. */
(void)transfer_encoding;  /* Unused. Silent compiler warning. */
(void)off;                /* Unused. Silent compiler warning. */

if (! con_info->fp)
  {
    if (0 != con_info->answercode) /* something went wrong */
      return MHD_YES;
    if (NULL != (fp = fopen (filename, "rb")))
      {
        fclose (fp);
        con_info->answerstring = fileexistspage;
        con_info->answercode = MHD_HTTP_FORBIDDEN;
        return MHD_YES;
      }
    /* NOTE: This is technically a race with the 'fopen()' above,
       but there is no easy fix, short of moving to open(O_EXCL)
       instead of using fopen(). For the example, we do not care. */
    con_info->fp = fopen (filename, "ab");
    if (!con_info->fp)
      {
        con_info->answerstring = fileioerror;
        con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;
        return MHD_YES;
      }
  }

if (size > 0)
  {
    if (! fwrite (data, sizeof (char), size, con_info->fp))
      {
        con_info->answerstring = fileioerror;
        con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;
        return MHD_YES;
      }
  }

  if (0 == strcmp (data, "0"))
  {
    FILE * fp;

    fp = fopen ("log/log.txt", "a+");
    fprintf(fp, "%s", "#######################################################\n");
    fprintf(fp, "%s", "Cliente Web\n");

    fclose(fp);
  }
  if (0 == strcmp (data, "1"))
  {
    FILE * fp;

    fp = fopen ("log/log.txt", "a+");
    fprintf(fp, "%s", "#######################################################\n");
    fprintf(fp, "%s", "Cliente App\n");

    fclose(fp);
  }
  if (0 == strcmp (data, "hist"))
  {

    //ejecutar el Histograma
    //hist();

    FILE * fp;

    fp = fopen ("log/log.txt", "a+");
    fprintf(fp, "%s", "Operacion de Histograma\n");

    fclose(fp);
  }
  if (0 == strcmp (data, "racist"))
  {
    FILE * fp;

    fp = fopen ("log/log.txt", "a+");
    fprintf(fp, "%s", "Operacion de Clasificacion por color\n");

    fclose(fp);
  }

  // constantes del configuracion
  configParams* params = getConfigVariables();

  //mover archivos de ubicación
  char array_char[800];
  strcpy(array_char,"images/");
  if(filename != NULL){
    printf("filename: %s\n", filename);
    strcat(array_char,filename);
    printf("path %s\n", array_char);
  }

  //const char *newname = "images/a.png";
  rename (filename, array_char);

  return MHD_YES;
}


void request_completed (void *cls,
                 struct MHD_Connection *connection,
                 void **con_cls,
                 enum MHD_RequestTerminationCode toe)
{
struct connection_info_struct *con_info = *con_cls;
(void)cls;         /* Unused. Silent compiler warning. */
(void)connection;  /* Unused. Silent compiler warning. */
(void)toe;         /* Unused. Silent compiler warning. */

if (NULL == con_info)
  return;

if (con_info->connectiontype == POST)
  {
    if (NULL != con_info->postprocessor)
      {
        MHD_destroy_post_processor (con_info->postprocessor);
        nr_of_uploading_clients--;
      }

    if (con_info->fp)
      fclose (con_info->fp);
  }

free (con_info);
*con_cls = NULL;
}


int answer_to_connection (void *cls,
                    struct MHD_Connection *connection,
                    const char *url,
                    const char *method,
                    const char *version,
                    const char *upload_data,
                    size_t *upload_data_size,
                    void **con_cls)
{
(void)cls;               /* Unused. Silent compiler warning. */
(void)url;               /* Unused. Silent compiler warning. */
(void)version;           /* Unused. Silent compiler warning. */

if (NULL == *con_cls)
  {
    /* First call, setup data structures */
    struct connection_info_struct *con_info;

    if (nr_of_uploading_clients >= MAXCLIENTS)
      return send_page (connection,
                        busypage,
                        MHD_HTTP_SERVICE_UNAVAILABLE);

    con_info = malloc (sizeof (struct connection_info_struct));
    if (NULL == con_info)
      return MHD_NO;
    con_info->answercode = 0; /* none yet */
    con_info->fp = NULL;

    if (0 == strcasecmp (method, MHD_HTTP_METHOD_POST))
      {
        con_info->postprocessor =
          MHD_create_post_processor (connection,
                                     POSTBUFFERSIZE,
                                     &iterate_post,
                                     (void *) con_info);

        if (NULL == con_info->postprocessor)
          {
            free (con_info);
            return MHD_NO;
          }

        nr_of_uploading_clients++;

        con_info->connectiontype = POST;
      }
    else
      {
        con_info->connectiontype = GET;
      }

    *con_cls = (void *) con_info;

    return MHD_YES;
  }

if (0 == strcasecmp (method, MHD_HTTP_METHOD_GET))
  {
    /* We just return the standard form for uploads on all GET requests */
    char buffer[1024];

    snprintf (buffer,
              sizeof (buffer),
              askpage,
              nr_of_uploading_clients);
    return send_page (connection,
                      buffer,
                      MHD_HTTP_OK);
  }

if (0 == strcasecmp (method, MHD_HTTP_METHOD_POST))
  {
    struct connection_info_struct *con_info = *con_cls;

    if (0 != *upload_data_size)
      {
        /* Upload not yet done */
        if (0 != con_info->answercode)
          {
            /* we already know the answer, skip rest of upload */
            *upload_data_size = 0;
            return MHD_YES;
          }
        if (MHD_YES !=
            MHD_post_process (con_info->postprocessor,
                              upload_data,
                              *upload_data_size))
          {
            con_info->answerstring = postprocerror;
            con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;
          }
        *upload_data_size = 0;

        return MHD_YES;
      }
    /* Upload finished */
    if (NULL != con_info->fp)
      {
        fclose (con_info->fp);
        con_info->fp = NULL;
      }
    if (0 == con_info->answercode)
      {
        /* No errors encountered, declare success */
        con_info->answerstring = completepage;
        con_info->answercode = MHD_HTTP_OK;
      }
    return send_page (connection,
                      con_info->answerstring,
                      con_info->answercode);
  }

/* Note a GET or a POST, generate error */
return send_page (connection,
                  errorpage,
                  MHD_HTTP_BAD_REQUEST);
}
