#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Configurations/NetworkConfigs.h"

//A Struct to store all Details 
typedef struct {
    char method[20];
    char path[100];
    char headers[200];
    char body[500];
} HttpRequestBuilder;

void HttpRequestBuilder_init(HttpRequestBuilder *builder) {
    strcpy(builder->method, "GET");
    strcpy(builder->path, "/");
    strcpy(builder->headers, "");
    strcpy(builder->body, "");
}

void setMethod(HttpRequestBuilder *builder, const char *method) {
    strcpy(builder->method, method);
}

void setPath(HttpRequestBuilder *builder, const char *path) {
    strcpy(builder->path, path);
}

void addHeader(HttpRequestBuilder *builder, const char *headerKey,const char *headerValue) {
    strcat(builder->headers, headerKey);
    strcat(builder->headers, ": ");
    strcat(builder->headers, headerValue);
    strcat(builder->headers, "\r\n");
}

void setBody(HttpRequestBuilder *builder, const char *body) {
    strcpy(builder->body, body);
}

char* buildRequest(HttpRequestBuilder *builder) {
    char *request = (char *)malloc(MAX_REQUEST_SIZE);
    snprintf(request, MAX_REQUEST_SIZE,
            "%s %s %s\r\n"
            "%s"
            "\r\n"
            "%s",
            builder->method, builder->path,HTTP_VERSION, builder->headers, builder->body);
    return request;
}


