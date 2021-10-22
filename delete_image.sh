#! /bin/bash

for (( c=1; c<=10; c++ ))
do
	sudo docker stop pso_$c; 
	sudo docker rm pso_$c;
done
