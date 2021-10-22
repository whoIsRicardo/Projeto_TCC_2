#! /bin/bash


for ((c=1; c<=10; c++))
do
	sudo gcc volumes/volume_$c/pso_$c/main.c -o main -lm
	sudo docker exec -i pso_$c ./home/pso_$c/main > volumes/volume_$c/pso_$c.txt &
done


