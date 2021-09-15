#! /bin/bash

FILES=$(find . -type f | head -n 100)
make

for f in $FILES; do
    diff <(cat -e $f | $CHECKER) <(cat -e $f | ./ft_ssl md5) &>/dev/null
    cat -e $f | $CHECKER | grep `cat -e $f | ./ft_ssl md5` &>/dev/null
    if (($?)) ; then
        echo "KO" -  $f
    else
        echo "OK" -  $f
    fi
    diff <(cat $f | md5) <(cat $f | ./ft_ssl md5)
    if (($?)) ; then
        echo "KO" -  $f
    else
        echo "OK" -  $f
    fi
done