echo "Basic Arithmetic Operations"
#var1=10
#var2=20
echo "Value of var1 is "
read var1
echo "Value of var2 is "
read var2

echo "Sum"
sum=`expr $var1 + $var2`
echo $sum

echo "Subtraction"
diff=`expr $var1 - $var2`
echo $diff

echo "Multiplication"
prod=`expr $var1 \* $var2`
echo $prod
