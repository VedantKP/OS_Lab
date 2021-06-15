ans=0
while [ $ans -ne 7 ]
do
echo -n
echo "----------------------------"
echo "|	***MENU***          |"
echo "----------------------------"
echo "|1.Create Database          |"
echo "|2.Display Database         |"
echo "|3.Search Record            |"
echo "|4.Insert Record            |"
echo "|5.Delete Record            |"
echo "|6.Modify Record            |"
echo "|7.Exit                     |"
echo "----------------------------"
echo "Enter your choice => "
read ans
case $ans in
	1)
		>database.txt
		echo -n
		echo "Enter number of records => "
		read total
		#cat > database.txt
		i=0
		uid=33150
		while [ $i -ne $total ]
		do
			echo "Enter name of student $(( i + 1 )) => "
			read name
			echo -n
			echo "Enter age of $name => "
			read age
			echo -n
			echo "Enter phone number of $name => "
			read phone
			echo -n
			echo "Enter pointer of $name => "
			read pointer
			uid=$(( $uid + 1 )) 
			echo "$uid|$name|$age|$phone|$pointer|">>database.txt
			i=$(( $i + 1 ))
		done			
		echo "Database created!"
	;;	
	2)
		echo -n
		echo "***DATABASE***"
		echo -n 
		echo "No|	Name|		Age| 	Phone|		Pointer|"
		value=$(<database.txt)
		echo "$value"
	;;
	3)	#without looping
		#echo -n
		#echo "Enter UID of student =>  "
		#read regid
		#echo "No|	Name|		Age| 	Phone|		Pointer|"
		#grep -w $regid database.txt
		echo "Enter UID of person to search => "
		read searchID
		for j in `cat database.txt`
		 do
		 IDVal=$(echo "$j" | cut -d "|" -f 1)
		 nameVal=$(echo "$j" | cut -d "|" -f 2)
		 ageVal=$(echo "$j" | cut -d "|" -f 3)
		 phoneVal=$(echo "$j" | cut -d "|" -f 4)
		 pointerVal=$(echo "$j" | cut -d "|" -f 5)
		 if [ "$searchID" == "$IDVal" ]
		 then
		 echo "Record found!"
		 echo "$IDVal|	$nameVal|		$ageVal|	$phoneVal|		$pointerVal|"
		 fi		 
		 done
	;;
	4)
		total=$(( $total + 1 ))
		uid=$(( $uid + 1 )) 
		echo "Enter name of student $(( i + 1 )) => "
		read name
		echo "Enter age of $name => "
		read age
		echo "Enter mobile number of $name => "
		read phone
		echo "Enter pointer of $name => "
		read pointer	
		echo "$uid|$name|$age|$phone|$pointer|">>database.txt
		i=$(( $i + 1 ))
		echo -n
		echo "Record inserted!"
	;;
	5) #without looping
		#echo "Enter UID of person to delete record => "
		#read searchVal
		#>temp.txt
		#grep -v $searchVal database.txt >> temp.txt
		#rm database.txt
		#mv temp.txt database.txt
		>temp.txt
		flag=0
		echo "Enter UID of person to delete record => "
		read searchID
		for j in `cat database.txt`
		 do
		 IDVal=$(echo "$j" | cut -d "|" -f 1)
		 nameVal=$(echo "$j" | cut -d "|" -f 2)
		 ageVal=$(echo "$j" | cut -d "|" -f 3)
		 phoneVal=$(echo "$j" | cut -d "|" -f 4)
		 pointerVal=$(echo "$j" | cut -d "|" -f 5)
		if [ "$searchID" != "$IDVal" ]
		then
		echo "$IDVal|$nameVal|$ageVal|$phoneVal|$pointerVal|">>temp.txt	 
		else
		flag=1
		fi
		done
		if [ $flag == 1 ] 
		then
		echo "Record deleted successfully!"
		rm database.txt
		mv temp.txt database.txt
		else
		echo "Record not found!"
		rm temp.txt
		fi
	;;
	6)
		>temp.txt
		flag=0
		echo "Enter UID of person to delete record => "
		read searchID
		for j in `cat database.txt`
		 do
		 IDVal=$(echo "$j" | cut -d "|" -f 1)
		 nameVal=$(echo "$j" | cut -d "|" -f 2)
		 ageVal=$(echo "$j" | cut -d "|" -f 3)
		 phoneVal=$(echo "$j" | cut -d "|" -f 4)
		 pointerVal=$(echo "$j" | cut -d "|" -f 5)
		if [ "$searchID" != "$IDVal" ]
		then
		echo "$IDVal|$nameVal|$ageVal|$phoneVal|$pointerVal|">>temp.txt	 
		else
		flag=1
		echo "Enter new name of $nameVal => "
		read nameVal
		echo "Enter new age of $nameVal => "
		read ageVal
		echo "Enter new phone number of $nameVal => "
		read phoneVal
		echo "Enter new pointer of $nameVal => "
		read pointerVal
		echo "$IDVal|$nameVal|$ageVal|$phoneVal|$pointerVal|">>temp.txt
		fi
		done
		if [ $flag == 1 ] 
		then
		echo "Record modified successfully!"
		rm database.txt
		mv temp.txt database.txt
		else
		echo "Record not found!"
		rm temp.txt
		fi		
	;;	
	7)
		echo "Bye"
	;;	
	*)
		echo "Invalid choice"
	;;		
esac	
done
