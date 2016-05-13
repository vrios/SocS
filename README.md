#Readme
This code is licensed as License: GPL (>= 2). You may use and redistribute this code with proper credit.

Source files for SocS program, according to the PLOS ONE submitted manuscript. To Compile, use Qt version 5.4 and Qt Creator 3.3, using C++11. The code should compile without problem in Windows 7 and newer and Linux, Mac OS X has not been tested.

To compile with graphical interface, use Socrats_Doc_Gui__codigo_base/main.cpp. This version does not allow replicates, does not generate output files and is used primarily for debugging.
To compile the full command line version, use Socrats_Doc_replicas/main.cpp.

Commande line parameters are:  "size, number of agents, action radius, random seed, number of replicates, simulation length, epsilon value, min_points, memory type, memory length, memory modifier." Memory type is deprecated, and should be equal to zero. The program will automatically run simulations with individual recognition and without recognition, using the same parameters. Warning: simulations with over 500 agents require a lot of computer memory, and the output files can be very large.

For instance, run ./Socrats_Doc_replicas 79 1000 3 1 10 1000 3 4 0 20 0.05 

Each replicateoutputs a set of 6 separate text files for each memeory type, which then can be analised: 

*clusterContent*, this contains a list of all clusters [excluding noise] found by DBscan and their contents,per timestep, to be analyzed by MONIC for group stability

*MeanSizeOfClusters*, this contais average cluster size for each timestep

*numberOfClusters*, this contains the amount of clusters found for each timestep

*StandardDevOfClustSize* this contains the santarde deviation of the average cluster size found for each timestep

*finalSocEdges*, this is a pairwise list of agents, with the sum of interactions between the pair presented as edge wheights

*finalSpaceEdges*  this is a pairwise list of agents, edge weights represent the number of times agents were in the same cluster
  
