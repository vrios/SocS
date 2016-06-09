#Readme
This code is licensed as License: GPL (>= 2). You may use and redistribute this code with proper credit. This software is provided as is.

Source files for SocS program, version 0.5, according to the PLOS ONE submitted manuscript. To compile, use Qt version 5.4 and Qt Creator 3.3, using C++11. The code should compile without problem in Windows 7 and newer and Linux, Mac OS X has not been tested.

To compile with graphical interface, use Socrats_Doc_Gui__codigo_base/main.cpp. This version does not allow replicates, does not generate output files and is used primarily for debugging.
To compile the full command line version, use Socrats_Doc_replicas/main.cpp.

Commande line parameters are:  "size, number of agents, action radius, random seed, number of replicates, simulation length, Epsilon value, MinPoints, memory type, memory length, memory modifier." Epsilon and MinPoints are DBSCAN parameters, according to {Ester, M., Kriegel, H.-P., Sander, J., Xu, X., 1996. A density-based algorithm for discovering clusters in large spatial databases with noise} See the ODD desciption on the manuscript for definitions of the parameters. Memory type is deprecated, and should be equal to zero. The program will automatically run simulations with individual recognition and without recognition, using the same parameters. Warning: simulations with over 500 agents require a lot of computer memory, and the output files can be very large .

For instance, run ./Socrats_Doc_replicas 79 1000 3 1 10 1000 3 4 0 20 0.05 

Each replicate run outputs a set of 6 separate text files for each memeory type, which then can be analised: 

*clusterContent*, this contains a list of all clusters [excluding noise] found by DBscan and their contents,per timestep, to be analyzed by MONIC for group stability (MONIC can be found at http://infolab.cs.unipi.gr/people/ntoutsi/monic.html)

*MeanSizeOfClusters*, this contais average cluster size for each timestep

*numberOfClusters*, this contains the amount of clusters found for each timestep

*StandardDevOfClustSize* this contains the santarde deviation of the average cluster size found for each timestep

*finalSocEdges*, this is a pairwise list of agents, with the sum of interactions between the pair presented as edge wheights

*finalSpaceEdges*  this is a pairwise list of agents, edge weights represent the number of times agents were in the same cluster
  
