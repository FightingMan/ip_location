<?php
/**
 * Description
 *
 * @file test.php
 * @date 2014-10-10 00:06:59
 * @author FightingMan <gianjason@gmail.com>
 * @copyright (c) 2014 FightingMan.
 */
$s = microtime(true);
$a = ip_location("61.135.169.80");
var_dump($a);
$s1 = microtime(true);
echo number_format($s1 - $s, 6) . "\n";

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
