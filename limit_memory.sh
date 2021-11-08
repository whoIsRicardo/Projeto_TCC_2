#!/bin/bash

for (( i=1; i<=10; i++))
do
	sudo docker update --memory="15M" pso_$i
done
