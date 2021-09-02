FILES=$(find . -type f | head -n 100)
make
diff <(echo -n "" | ./ft_ssl md5) <(echo -n "" | md5)
diff <(echo -n 42 | ./ft_ssl md5) <(echo -n 42 | md5)
diff <(echo -n hola | ./ft_ssl md5) <(echo -n hola | md5)
diff <(cat -e test.sh | ./ft_ssl md5) <(cat -e test.sh | md5)
diff <(echo -n "117d5f2873a1dab7283f08fcc893d840117d5f2873a1dab7283f08fcc893d840" | ./ft_ssl md5) <(echo -n 117d5f2873a1dab7283f08fcc893d840117d5f2873a1dab7283f08fcc893d840 | md5)
diff <(echo -n "" | ./ft_ssl md5) <(echo -n "" | md5)
diff <(echo -n "" | ./ft_ssl md5) <(echo -n "" | md5)
for f in $FILES; do
    diff <(cat -e $f | md5) <(cat -e $f | ./ft_ssl md5)
    if (($?)) ; then
        echo "KO" -  $f
    else
        echo "OK" -  $f
    fi
done