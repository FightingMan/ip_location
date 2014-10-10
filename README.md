ip_location
===========

hhvm-ext/ip_location

compile:
```
  hphpize
  cmake . && make
```
test:
```
  hhvm -vDynamicExtensions.0=ip_location.so test.php
```
