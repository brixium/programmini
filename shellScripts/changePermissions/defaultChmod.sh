DIRECTORY='.'
find $DIRECTORY -type d -exec chmod 755 {} \;
find $DIRECTORY -type f -exec chmod 644 {} \;

