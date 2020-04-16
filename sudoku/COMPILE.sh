make install
if [ $? -eq 1 ] ; then
	make install_static
fi
make clean
