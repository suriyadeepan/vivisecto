#sed -i.bak 1d path-to/Mobility.txt && sed -i.bak 's/  */ /g' path-to/Mobility.txt
#sed -i.bak 1d path-to/RadioCommunication.txt && sed -i.bak 's/  */ /g' path-to/RadioCommunication.txt
#sed -i.bak 1d path-to/Topology.txt && sed -i.bak 's/  */ /g' path-to/Topology.txt

mv path-to/Mobility.txt path-to/Mobility.csv
mv path-to/RadioCommunication.txt path-to/RadioCommunication.csv
mv path-to/Topology.txt path-to/Topology.csv

#sed -i.bak 1d path-to/*.csv && sed -i.bak 's/  */ /g' path-to/*.csv
sed -i.bak 's/  */ /g' path-to/*.csv && sed -i.bak 1d path-to/*.csv 
rm path-to/*.csv.bak
