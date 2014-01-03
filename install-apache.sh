#!/bin/sh

cd $1
echo "Downloading Apache-2.2.23.tar.bz2...";
#wget http://archive.apache.org/dist/httpd/httpd-2.2.23.tar.bz2;
echo "Extrating Apache-2.2.23.tar.bz2...";
tar -xvf httpd-2.2.23.tar.bz2;
echo "Changing Directory to httpd-2.2.23...";
cd httpd-2.2.23
echo "Configuring...";
./configure --prefix=$1 --with-mpm=$2;
echo "Installing Apache...";
make;
make install;
cd ..
rm -r httpd-2.2.23.tar.bz2;
rm -r httpd-2.2.23;
