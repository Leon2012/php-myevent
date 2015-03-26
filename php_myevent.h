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

#ifndef PHP_MYEVENT_H
#define PHP_MYEVENT_H

extern zend_module_entry myevent_module_entry;
#define phpext_myevent_ptr &myevent_module_entry

#define PHP_MYEVENT_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_MYEVENT_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MYEVENT_API __attribute__ ((visibility("default")))
#else
#	define PHP_MYEVENT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(myevent);
PHP_MSHUTDOWN_FUNCTION(myevent);
PHP_RINIT_FUNCTION(myevent);
PHP_RSHUTDOWN_FUNCTION(myevent);
PHP_MINFO_FUNCTION(myevent);

PHP_FUNCTION(my_add_event);
PHP_FUNCTION(my_add_listener);


ZEND_BEGIN_MODULE_GLOBALS(myevent)
	HashTable  events;    //注册事件
	HashTable  listeners; //注册事件监听
ZEND_END_MODULE_GLOBALS(myevent)


#ifdef ZTS
#define MYEVENT_G(v) TSRMG(myevent_globals_id, zend_myevent_globals *, v)
#else
#define MYEVENT_G(v) (myevent_globals.v)
#endif

#endif	/* PHP_MYEVENT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
