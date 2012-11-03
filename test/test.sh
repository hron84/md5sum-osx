#!/bin/sh
[ -d test ] && cd test
../md5sum -c test1.md5 || exit 1
../md5sum -c test\ with\ spaces.md5 || exit 1
../sha256sum -c test1.sha256 || exit 1
../sha256sum -c test\ with\ spaces.sha256 || exit 1
