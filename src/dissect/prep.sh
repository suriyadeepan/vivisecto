#sed -i.bak 1d ./Mobility.txt && sed -i.bak 's/  */ /g' ./Mobility.txt
#sed -i.bak 1d ./RadioCommunication.txt && sed -i.bak 's/  */ /g' ./RadioCommunication.txt
#sed -i.bak 1d ./Topology.txt && sed -i.bak 's/  */ /g' ./Topology.txt

mv ./Mobility.txt ./Mobility.csv
mv ./RadioCommunication.txt ./RadioCommunication.csv
mv ./Topology.txt ./Topology.csv

#sed -i.bak 1d ./*.csv && sed -i.bak 's/  */ /g' ./*.csv
sed -i.bak 's/  */ /g' ./*.csv && sed -i.bak 1d ./*.csv 
rm ./*.csv.bak
