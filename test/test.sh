#!/bin/sh
[ -d test ] && cd test
../build/md5sum -c test1.md5 || exit 1
../build/md5sum -c test\ with\ spaces.md5 || exit 1

../build/sha256sum -c test1.sha256 || exit 1
../build/sha256sum -c test\ with\ spaces.sha256 || exit 1

../build/sha512sum -c test1.sha512 || exit 1
../build/sha512sum -c test\ with\ spaces.sha512 || exit 1
