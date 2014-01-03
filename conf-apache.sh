#!/bin/sh

cd $1
cd httpd-2.2.23
./configure --prefix=$1 --with-mpm=$2;
echo "Installing Apache...";
make;
make install;
cd ..
rm -r -f httpd-2.2.23.tar.bz2;
rm -r -f httpd-2.2.23;
