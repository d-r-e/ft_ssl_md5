#!/bin/bash
FILES=$(find . -type f | head -n 100)
make

CHECKER=md5sum
if [ "`uname`" != "Linux" ]; then
    CHECKER=md5
fi
diff <(echo -n "" | ./ft_ssl md5) <(echo -n "" | $CHECKER)
diff <(echo -n 42 | ./ft_ssl md5) <(echo -n 42 | $CHECKER)
diff <(echo -n hola | ./ft_ssl md5) <(echo -n hola | $CHECKER)
diff <(cat -e test.sh | ./ft_ssl md5) <(cat -e test.sh | $CHECKER)
diff <(echo -n "117d5f2873a1dab7283f08fcc893d840117d5f2873a1dab7283f08fcc893d840" | ./ft_ssl md5) <(echo -n 117d5f2873a1dab7283f08fcc893d840117d5f2873a1dab7283f08fcc893d840 | $CHECKER)
diff <(echo -n "" | ./ft_ssl md5) <(echo -n "" | $CHECKER)
diff <(echo -n "" | ./ft_ssl md5) <(echo -n "" | $CHECKER)
for f in $FILES; do
    diff <(cat -e $f | $CHECKER) <(cat -e $f | ./ft_ssl md5) &>/dev/null
    cat -e $f | $CHECKER | grep `cat -e $f | ./ft_ssl md5` &>/dev/null
    if (($?)) ; then
        echo "KO" -  $f
    else
        echo "OK" -  $f
    fi
done