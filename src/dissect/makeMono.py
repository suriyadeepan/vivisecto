import csv
from decimal import Decimal
import math

#########################
# Read from trace files #
#########################
mobile = list(csv.reader(open("./Mobility.csv",'rb'),delimiter=' '))
radio = list(csv.reader(open("./RadioCommunication.csv",'rb'),delimiter=' '))

nodes = list(csv.reader(open("./Topology.csv",'rb'),delimiter=' '))

# open "events.mono"
fhandle = open("../events.mono",'w');

# write topology to monolith
ni = 0
ni_max = len(nodes)

while ni < ni_max:
	fhandle.write("0 " + nodes[ni][0] + " 0 " + str( int(float(nodes[ni][1])) ) + " " + str( int(float(nodes[ni][2])) ) + " -1" + "\n") 
	ni = ni + 1

# End of Simulation time
sim_te = math.ceil(float((radio[len(radio)-1][0])))

sim_t = 0.0
mi = 0
ri = 0
ri_max = len(radio)

while Decimal(sim_t) < Decimal(sim_te) and ri < ri_max:
	if( Decimal(radio[ri][0]) > Decimal(mobile[mi][0]) ):
		sim_t = Decimal(mobile[mi][0])
		fhandle.write( str(Decimal(mobile[mi][0])) + " " + mobile[mi][1]+ " 0 " + str(int(float(mobile[mi][2]))) + " " + str( int(float(mobile[mi][3])))+ " -1" + "\n")
		mi = mi + 1
	elif( Decimal(radio[ri][0]) < Decimal(mobile[mi][0]) ):
		sim_t = Decimal(radio[ri][0])
		if (radio[ri][1] == "TX"):
			fhandle.write( str(Decimal(radio[ri][0]))+ " " + radio[ri][2]+ " 1"+ " -1 -1 "+ "-1" + "\n")
		elif (radio[ri][4] != "-1"):
			fhandle.write( str(Decimal(radio[ri][0]))+ " " + radio[ri][2]+ " 2"+ " -1 -1 "+ radio[ri][3] + "\n")
		ri = ri + 1
	else:
		fhandle.write( radio[ri] + "\n")
		fhandle.write( mobile[mi] + "\n")
		ri = ri + 1
		mi = mi + 1
