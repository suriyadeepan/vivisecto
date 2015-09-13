import csv
from decimal import Decimal
import math

#########################
# Read from trace files #
#########################
mobile = list(csv.reader(open("path-to/Mobility.csv",'rb'),delimiter=' '))
radio = list(csv.reader(open("path-to/RadioCommunication.csv",'rb'),delimiter=' '))

nodes = list(csv.reader(open("path-to/Topology.csv",'rb'),delimiter=' '))
# write topology to monolith
ni = 0
ni_max = len(nodes)

while ni < ni_max:
	print "0", nodes[ni][0], "0", int(float(nodes[ni][1])), int(float(nodes[ni][2])), "-1"
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
		print Decimal(mobile[mi][0]), mobile[mi][1], "0", int(float(mobile[mi][2])), int(float(mobile[mi][3])), "-1"
		mi = mi + 1
	elif( Decimal(radio[ri][0]) < Decimal(mobile[mi][0]) ):
		sim_t = Decimal(radio[ri][0])
		if (radio[ri][1] == "TX"):
			print Decimal(radio[ri][0]), radio[ri][2], "1", "-1 -1", "-1"
		elif (radio[ri][4] != "-1"):
			print Decimal(radio[ri][0]), radio[ri][2], "2", "-1 -1", radio[ri][3]
		ri = ri + 1
	else:
		print radio[ri]
		print mobile[mi]
		ri = ri + 1
		mi = mi + 1
