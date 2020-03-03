#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"



int main(int argc, char *argv[])
{
 //the parameters for the http request

    char *message;
    char *response;
    int  sockfd;
	char *host = "185.118.200.35";
    int port = 8081;

//Helping functions for getting the cookies and to find the beginning of the json document
    char  *CookieGetter(char *text) {
        char *cookie = malloc(400); char delims[] = "\" \n";

        strcpy(cookie, "");

        char *cookie_helper= strtok(text, delims);

        while (cookie_helper!= NULL) {

            if(strcmp(cookie_helper, "Set-Cookie:") == 0) {

                cookie_helper = strtok(NULL, delims);
                strcat(cookie, cookie_helper);

            }

            cookie_helper = strtok(NULL, delims);
        }

        strcat(cookie, "");

    	return cookie;
	}


	char *Json_beginning_text(char *response){
        int i = 0;

        while(response[i] != '{'){
            i++;
        }

        return &response[i];
	}

//Task 1
    printf("Etapa1 ------");

    sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request(host, "/task1/start", NULL, NULL, NULL);

    printf("\n Sending Message:%s\n", message);

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    printf("\n Received Message%s\n", response);

    close_connection(sockfd);

//Task 2
    printf("Etapa2 ---------------------");

//the extraction and the handling of the parameters from the json doc
    JSON_Value *value_init;
    JSON_Object *value_aft;

    char *cred_user = malloc(100);
    char *response_aft = malloc(100);
    char *cookie = malloc(291);


    response_aft = Json_beginning_text(response);


    value_init = json_parse_string(response_aft);
    value_aft = json_value_get_object(value_init);

    const char *url = json_object_get_string(value_aft, "url");
    const char *method = json_object_get_string(value_aft, "method");
    const char *type = json_object_get_string(value_aft, "type");
    char* username = json_object_dotget_string(value_aft, "data.username");
    char* password= json_object_dotget_string(value_aft, "data.password");

//creating the credentials
    strcpy(cred_user, "username=");
    strcat(cred_user, username);
    strcat(cred_user, "&password=");
    strcat(cred_user, password);

//cookies
    cookie = CookieGetter(response);

//opening the connection and sending the request
    sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);

    if( strcmp(method, "GET") == 0){
        message = compute_get_request(host, url, NULL, cookie, NULL);

    }else if(strcmp(method, "POST") == 0){
        message = compute_post_request(host, url, cred_user, type, cookie, NULL);
    }

    printf("\n {Sending Message}:%s\n", message);

    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("\n {Received Message}:%s\n", response);


    close_connection(sockfd);

//Etapa 3

    printf("Etapa3------------------------------");

//the extraction and the handling of the parameters from the json doc
    char *url_params = malloc(100);

    response_aft = Json_beginning_text(response);

    value_init = json_parse_string(response_aft);
    value_aft = json_value_get_object(value_init);

    url = json_object_get_string(value_aft, "url");
    method = json_object_get_string(value_aft, "method");
    char *token = json_object_dotget_string(value_aft, "data.token");
    char *id = json_object_dotget_string(value_aft, "data.queryParams.id");

    strcpy(url_params, "raspuns1=omul&raspuns2=numele&id=");
    strcat(url_params, id);
//cookies
	cookie = CookieGetter(response);
//opening the connection and sending the request
    sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);

    if( strcmp(method, "GET") == 0){
        message = compute_get_request(host, url, url_params, cookie, token);

    }else if(strcmp(method, "POST") == 0){
        message = compute_post_request(host, url, NULL, NULL, cookie, NULL);
    }

    printf("\n {Sending Message}:%s\n", message);

    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("\n {Received Message}:%s\n", response);

    close_connection(sockfd);

    printf("Etapa4----------------------------------------------------------");
//the extraction and the handling of the parameters from the json doc
    response_aft = Json_beginning_text(response);


	value_init = json_parse_string(response_aft);
    value_aft = json_value_get_object(value_init);

    url = json_object_get_string(value_aft, "url");
    method = json_object_get_string(value_aft, "method");
//cokies
    cookie = CookieGetter(response);
//opening the connection and sending the request   
    sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);

    if( strcmp(method, "GET") == 0){
        message = compute_get_request(host, url, NULL, cookie, token);

    }else if(strcmp(method, "POST") == 0){
        message = compute_post_request(host, url, NULL, NULL, cookie, token);
    }

    printf("\n {Sending Message}:%s\n", message);

    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("\n {Received Message}:%s\n", response);

    close_connection(sockfd);

    printf("Etapa5--------------------------------------------------------------" );
//extragerea si prelucrarea parametiilor pentru cerere
    response_aft = Json_beginning_text(response);

    value_init = json_parse_string(response_aft);
    value_aft = json_value_get_object(value_init);

    url = json_object_get_string(value_aft, "url");
    method = json_object_get_string(value_aft, "method");
    type = json_object_get_string(value_aft, "type");
    char *data_url = json_object_dotget_string(value_aft, "data.url");
    char *location = json_object_dotget_string(value_aft, "data.queryParams.q");
    char *APPID = json_object_dotget_string(value_aft, "data.queryParams.APPID");
    char *data_method = json_object_dotget_string(value_aft, "data.method");

    cookie = CookieGetter(response);

    strcpy(url_params, "q=");
    strcat(url_params, location);
    strcat(url_params, "&APPID=");
    strcat(url_params, APPID);
//getting the new hostname si Path
    char hostName[100];
    char *hostIP;
    char hostPath[100];

    int i, j;

    for(i = 0; data_url[i] != '/'; i++){
    	hostName[i] = data_url[i];
    }

    hostName[i] = '\0';

    for(i, j = 0; data_url[i] != NULL; i++ , j++){
    	hostPath[j] = data_url[i];
    }

    hostPath[j] = '\0';
//getting the new IP
  	hostIP = inet_ntoa(*((struct in_addr*)
    (gethostbyname(hostName)->h_addr_list[0])));

//opening the connection and sending the request
    sockfd = open_connection(hostIP, 80, AF_INET, SOCK_STREAM, 0);

    if( strcmp(data_method, "GET") == 0){
        message = compute_get_request(hostIP, hostPath, url_params, NULL, token);

    }else if(strcmp(data_method, "POST") == 0){
        message = compute_post_request(hostIP, hostPath, NULL, NULL, NULL, token);
    }

    printf("\n {Sending Message}:%s\n", message);
	send_to_server(sockfd, message);

    response = receive_from_server(sockfd);
    printf("\n {Received Message}:%s\n", response);

    close_connection(sockfd);
//handling the json response
    response_aft = Json_beginning_text(response);

    sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);
    message = compute_post_request(host, url, response_aft, type, cookie, token);

    printf("\n {Sending Message}:%s\n", message);
	send_to_server(sockfd, message);

    response = receive_from_server(sockfd);
    printf("\n {Received Message}:%s\n", response);

    close_connection(sockfd);

}
