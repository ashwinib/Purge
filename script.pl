#!/usr/bin/perl
for ($count = 10; $count < 1000; $count = $count + 10) {
	system("./dpurge fs/sample-".$count." out >> dpurgeres");
	system("./mpurge fs/sample-".$count." out1 >> mpurgeres");
}
