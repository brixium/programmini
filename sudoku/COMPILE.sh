make install_static
if [ $? -eq 1 ] ; then
	make install
fi
make clean
