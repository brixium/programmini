NMAKE install_static -f Makefile_windows
IF %ERRORLEVEL%  NEQ 0 (
	NMAKE install -f Makefile_windows
)
NMAKE clean -f Makefile_windows