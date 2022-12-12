echo "Enter your String: "
read vstr
for i in $(seq 0 ${#vstr})
do
	rvstr=${vstr:$i:1}${rvstr}
done

echo "Input string was :" $vstr
echo "After reversng string is :" $rvstr

if [ "$vstr" = "$rvstr" ]
then
	echo "String is palindrome."
else
	echo "String is not plaindrome."
fi
