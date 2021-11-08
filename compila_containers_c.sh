#! /bin/bash
for (( i=1; i<=10; i++))
do
	sudo docker exec -i pso_$i gcc -o /home/pso_$i/main /home/pso_$i/main.c -lm
done
