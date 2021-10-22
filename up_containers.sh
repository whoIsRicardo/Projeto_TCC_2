 #! /bin/bash 

 
for (( c=1; c<=10; c++ ))
do  
 sudo docker start pso_$c
done
