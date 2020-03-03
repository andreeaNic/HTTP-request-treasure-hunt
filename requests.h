#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_get_request(char *host, char *url, char *url_params, char *cookie, const char *token);

char *compute_post_request(char *host, char *url, char *form_data, const char *type, char *cookie,const char *token);

#endif
