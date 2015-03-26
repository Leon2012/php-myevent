 PHP_ARG_WITH(myevent, for myevent support,
  [  --with-myevent             Include myevent support])


 PHP_ARG_ENABLE(myevent, whether to enable myevent support,
  [  --enable-myevent           Enable myevent support])

if test "$PHP_MYEVENT" != "no"; then
  PHP_NEW_EXTENSION(myevent, myevent.c, $ext_shared)
fi
