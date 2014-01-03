#!/bin/sh

cd $1
echo "Downloading Apache-2.2.23.tar.bz2...";
#wget http://archive.apache.org/dist/httpd/httpd-2.2.23.tar.bz2;
echo "Extrating Apache-2.2.23.tar.bz2...";
tar -xvf httpd-2.2.23.tar.bz2;
