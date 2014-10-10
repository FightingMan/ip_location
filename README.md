ip_location
===========

hhvm-ext/ip_location

hphpize

install:
cmake . && make

test:
hhvm -vDynamicExtensions.0=ip_location.so test.php
