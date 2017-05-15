# MD5 sum creator for OS X

## Introducion

This is a very simple C project to create and verify MD5 and SHA256 checksum of files.

The main thing is it uses same format as Linux md5sum/sha256sum utility, so you can
create and verify checksum files what created with that. 

## Installation

If you trying use this under another OS than Mac OSX, please make sure OpenSSL libs
and headers are installed. 

    git clone git://github.com/hron84/md5sum-osx.git
    cd md5sum-osx
    mkdir build
    cd build
    cmake ..
    make all
    make test install

## Known limitations

* The parser can handle only file names with length 990 byte (UTF-8 characters counted as **2** byte).


If you got any errors or have any suggestions, feel free to contact me over github or over GMail 
(just type hrgyster before GMail's domain).

Have a lot of fun!
