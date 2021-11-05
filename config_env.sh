#! /bin/bash
for (( i=1; i<=10; i++))
do
	sudo mkdir volumes/volume_$i
	sudo docker run -d -v $(pwd)/volumes/volume_$i:/home/ --name pso_$i -t -i --memory="1g" ubuntu:20.04
	sudo docker exec -i pso_$i apt-get update 
	sudo docker exec -i pso_$i apt-get install vim -y
	sudo docker exec -i pso_$i apt-get install gcc -y 
	sudo docker exec -i pso_$i apg-get install g++ -y
	sudo docker cp pso_$i/ pso_$i:/home/
	sudo docker cp matrix_inversion_$i/ matrix_inversion_$i:/home/
done

