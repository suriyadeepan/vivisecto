#ViVi
#####

A light-weight visualizer for [Castalia](https://castalia.forge.nicta.com.au/index.php/en/). Based on MVC pattern, uses opencv's graphics capabilites for displaying events in a simulated sensor network environment. Events include node movement, radio transmission, reception and dynamic clustering. 

![alt tag](https://raw.githubusercontent.com/suriyadeepan/vivisecto/master/screenshots/screenshot.png)

##Installation
#####Run the install script

```bash
cd path/to/vivisecto/
./install
# Enter sudo password for commands that require admin rights
# Close terminal and open a new session for changes to take effect
```

##Running Vivi
```bash
# Enter the Castalia Simulation folder
cd /path/to/Castalia/Simulations/ScenarioName/
# Assuming that simulation is done and trace files
#  RadioCommunication.txt, Mobility.txt, Topology.txt 
#     are generated
vivi
```

##Contribution
#####To contribute please follow these steps

1. Fork the repo
2. Write clear [commit messages](https://github.com/erlang/otp/wiki/Writing-good-commit-messages)
3. Give Pull Request to master branch
4. Write clear description to the pull request
