/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_myevent.h"

#define DEFAULT_ERROR_DOCREF(level, message) php_error_docref(NULL TSRMLS_CC, level, message)

ZEND_DECLARE_MODULE_GLOBALS(myevent)

static void myevent_events_dtor(void *ht){
    zend_hash_destroy((HashTable *)ht);
}
static void php_myevent_globals_ctor(zend_myevent_globals *mg){

}

static zend_function* myevent_get_function(zval *call TSRMLS_DC) {
    
}

ZEND_BEGIN_ARG_INFO(my_add_event_arginfo, 0)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_ARRAY_INFO(0, clazz, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(my_add_event){
    char *name;
    int  name_len = 0;
    zval *clazz;
    int clazz_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &name, &name_len, &clazz) == FAILURE) {
        //php_error_docref(NULL TSRMLS_CC, E_WARNING, "");
        RETURN_FALSE;
    }

    if (!name || name_len == 0) {
        DEFAULT_ERROR_DOCREF(E_ERROR, "name is not allow empty!");
        RETURN_FALSE;
    }

    if (!clazz || Z_TYPE_P(clazz) != IS_ARRAY) {
        DEFAULT_ERROR_DOCREF(E_ERROR, "clazz is not allow empty!");
        RETURN_FALSE
    }

    clazz_len = zend_hash_num_elements(Z_ARRVAL_P(clazz));
    //if (clazz_len <= 0 || clazz_len > 2) {
    if (clazz_len != 2){
        DEFAULT_ERROR_DOCREF(E_ERROR, "clazz length is not valid!");
        RETURN_FALSE
    }


    RETURN_TRUE;
}


PHP_MINIT_FUNCTION(myevent){
    ZEND_INIT_MODULE_GLOBALS(myevent, php_myevent_globals_ctor, NULL);
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(myevent){
	return SUCCESS;
}



PHP_RINIT_FUNCTION(myevent){
    //初始化global变量
    zend_hash_init(&MYEVENT_G(events), 8, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_init(&MYEVENT_G(listeners), 8, NULL, ZVAL_PTR_DTOR, 0);
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(myevent){
    //释放global变量
    zend_hash_destroy(&MYEVENT_G(events));
    zend_hash_destroy(&MYEVENT_G(listeners));
	return SUCCESS;
}



PHP_MINFO_FUNCTION(myevent){
	php_info_print_table_start();
	php_info_print_table_header(2, "myevent support", "enabled");
	php_info_print_table_end();
}


/* {{{ myevent_functions[]
 *
 * Every user visible function must have an entry in myevent_functions[].
 */
const zend_function_entry myevent_functions[] = {
    PHP_FE(my_add_event,    my_add_event_arginfo)       /* For testing, remove later. */
    PHP_FE_END  /* Must be the last line in myevent_functions[] */
};
/* }}} */

/* {{{ myevent_module_entry
 */
zend_module_entry myevent_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "myevent",
    myevent_functions,
    PHP_MINIT(myevent),
    PHP_MSHUTDOWN(myevent),
    PHP_RINIT(myevent),     /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(myevent), /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(myevent),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MYEVENT_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYEVENT
ZEND_GET_MODULE(myevent)
#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
