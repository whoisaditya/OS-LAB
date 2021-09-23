echo "Welcome to Shell Programming"
var1=10
var2=20
echo "The value of var1 is $var1"
echo "The value of var2 is $var2"

echo "First Method"
var3=$(($var1 + $var2))
echo $var3

echo "Second Method"
var3=`expr $var1+$var2`
echo $var3
