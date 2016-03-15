/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

 #ifndef NGX_HTTP_PHP_CORE_H
 #define NGX_HTTP_PHP_CORE_H

#include <ngx_http.h>
#include <php_embed.h>
#include "php/php_ngx.h"

extern ngx_http_request_t *ngx_php_request;

typedef enum code_type_t {
	NGX_HTTP_PHP_CODE_TYPE_FILE,
	NGX_HTTP_PHP_CODE_TYPE_STRING
} code_type_t;

typedef struct ngx_http_php_code_t {
	union code {
		char *file;
		char *string;
	} code;
	code_type_t code_type;
} ngx_http_php_code_t;

typedef struct ngx_http_php_rputs_chain_list_t {
	ngx_chain_t **last;
	ngx_chain_t *out;
} ngx_http_php_rputs_chain_list_t;

typedef struct ngx_http_php_ctx_t {
	ngx_http_php_rputs_chain_list_t *rputs_chain;
} ngx_http_php_ctx_t;


ngx_http_php_code_t *ngx_http_php_code_from_file(ngx_pool_t *pool, ngx_str_t *code_file_path);
ngx_http_php_code_t *ngx_http_php_code_from_string(ngx_pool_t *pool, ngx_str_t *code_str);

// php_ngx
ngx_int_t ngx_php_embed_run(ngx_http_request_t *r, ngx_http_php_code_t *code);
ngx_int_t ngx_php_ngx_run(ngx_http_request_t *r, ngx_http_php_code_t *code);

int ngx_http_php_code_ub_write(const char *str, unsigned int str_length TSRMLS_DC);
void ngx_http_php_code_flush(void *server_context);
void ngx_http_php_code_log_message(char *message);

#endif