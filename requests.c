#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

//Task1 : writing the name of the method, the path, the parameters and the type of the protocol we used( get or post)

char *compute_get_request(char *host, char *url, char *url_params, char *cookie, const char *token){

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (url_params != NULL){
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else{
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    sprintf(line, "HOST: %s", host);
    compute_message(message, line);



    if(cookie == NULL){
        sprintf(line, "Cookie: ");
    }else{
       sprintf(line, "Cookie:%s", cookie);
    }

    compute_message(message, line);



    if(token != NULL){
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }



    sprintf(line, "%s", "");
    compute_message(message, line);

    return message;
}

char *compute_post_request( char *host, char *url, char *form_data, const char *type, char *cookie, const char *token){

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);


    /*
       Task2 : Adding the host
    */
    sprintf(line, "HOST: %s", host);
    compute_message(message, line);

    sprintf(line, "Cookie: %s", cookie);
    compute_message(message, line);



    /*

        Task3: Adding the headers or the cookies, depeding on the protocol
    */
    if(type == NULL){
       sprintf(line, "Content-Type: application/x-www-form-urlencoded");
    } else {
        sprintf(line, "Content-Type: %s", type);
    }

    compute_message(message, line);

    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);

    if(token != NULL){
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }

    sprintf(line, "%s", "");
    compute_message(message, line);

    sprintf(line, "%s", form_data);
    compute_message(message, line);


    return message;

}
