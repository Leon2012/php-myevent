<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('myevent')) {
	dl('myevent.' . PHP_SHLIB_SUFFIX);
}

my_add_event("test", array("test"));

?>
