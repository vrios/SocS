#setwd("C:/Users/Vitor/Dropbox/Doutorado/codigo/build-Socrats_Doc_replicas-Desktop_Qt_5_4_0_MinGW_32bit-Release/release")
#setwd("C:/Users/Vitor/Dropbox/Doutorado/codigo/build-Socrats_Doc_replicas-Desktop_Qt_5_4_0_MinGW_32bit-Debug/")
setwd("C:/Users/Vitor/Desktop/novas sim plos/high_dens")
#setwd("C:/Users/Vitor/Desktop/abacus 3")

library("matrixStats") #rowSds() function <- now needs a matrix instead of a data.frame
library("extrafont") #for using different fonts in graphs
loadfonts(quiet = TRUE) ## allows use of arial

files  <- list.files(pattern = "Edges")#reads files only to find parameters
#read memory lengths from filenames
temp_length <- read.table(textConnection(files), sep = "_", as.is=TRUE, colClasses = "character")
unique(temp_length[2])
mem_lengths = unique(temp_length[16])
mem_lengths=sort(mem_lengths[,])
mem_lengths
#memory type
mem_types=unique(temp_length[1])
mem_types=sort(mem_types[,])
mem_types
#read number of iterations from filenames
n_iter= as.numeric(temp_length[1,14])
n_iter # numero de iterações
#read densities from filenames
N_agents=as.numeric(unique(temp_length[,6]))
world_sizes=as.numeric(unique(temp_length[,4]))
densities = N_agents/world_sizes^2 # individuals per unit area
densities
# read radii from filenames
radii = as.numeric(unique(temp_length[,8]))
radii
mem_mods = as.character(unique(temp_length[,18]))
mem_mods

#read number of replicates from filenames
replicate = as.character(unique(temp_length[,20]))
replicate=strtrim(replicate, nchar(replicate)-4)
replicate
###bug na analise, objetos abaixo eram criados no for...

valores.medios.por.mem = data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths)))
valores.sd.medio.por.mem = data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths)))

output = c("_MeanSizeOfClusters", "_numberOfClusters")
for (o in 1:length(output))
{
  #outType=output[1]
  output[o]
  for (r in 1:length(radii))
  {
    #radius =radii[1]
    radius =radii[r]
    for (t in 1:length(mem_types))
    {
      #type=mem_types[1]
      type=mem_types[t]
      for (s in 1:length(world_sizes))
      {
        #world_size=world_sizes[1]
        world_size = world_sizes[s]
        outputType = paste( type, output[o] ,sep="")
        metrica=ifelse(test = output[o]=="_MeanSizeOfClusters", yes = "Mean Cluster Size", no = "Mean Number of Clusters")

        for (m in 1:(length(mem_lengths)))
        {
          #mem_length=mem_lengths[1]
          mem_length = mem_lengths[m]
          #           mem_length = mem_lengths[m]
          #           valores.medios.por.mem = data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths)))
          #           valores.sd.medio.por.mem = data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths)))
          for (mod in 1:length(mem_mods))
          {
            #  modifier=mem_mods[1]
            modifier = mem_mods[mod]
            #           old_par =  par(mfrow=c(3, 3))
            #           png(paste (type, modifier,".png", sep=""),width = 900,height = 900)

            temp_valores_replicas = as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(replicate))))
            colnames(valores.medios.por.mem) = mem_lengths
            colnames(temp_valores_replicas) = replicate
            reg.exp=paste(
              paste(outputType,sep="")
              ,paste("_tam_", world_size, sep="") #only one density
              ,'.*'
              ,paste("_raio_", radius, sep="") #only one radius
              ,'.*'
              ,paste("tMem_", mem_length,"_", sep="")#only one memory length
              ,'.*'
              ,paste("MemMod_", modifier,"_", sep="")#only one memory modifier
              ,'.*'
              ,sep="")
            files_to_read=list.files(pattern = reg.exp)
            files_to_read
            if (length(files_to_read)!=0)
            {
              #temp_valores_replicas=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(replicate))))
              for (r in 1:(length(files_to_read)))
              {
                #  message(paste(type, mem_length, files_to_read[r], sep = " "))
                temp_valores_replicas[,r] <- read.table(files_to_read[r],  header = FALSE)
              }

              #creating plot names
              graphtype=NA
              if(type=="g"){graphtype=" with general recognition "}
              if (type=="i") {graphtype=" with Individual Recognition "}
              if (type=="nr") {graphtype=" with No Recognition "}

              plotname =paste(
                #"forPaper "
                #, outputType
                #,
                metrica
                ,graphtype
                #, ", Agentes = ", N_agents
                #, ", raio = ", radius
                , ", mundo = ", world_size
                , ", mem length = ", as.numeric(mem_length)
                #, ", mem type = ", type
                , ", mem modifier = ", as.numeric (modifier)
                ,".tiff"
                , sep = "")
              if("plots"%in%dir()==FALSE) dir.create("plots")
              filename = file.path("C:", "Users", "Vitor","Desktop", "novas sim plos","high_dens","plots" ,plotname)
              #filename = file.path("C:", "Users", "Vitor","Desktop", "abacus 3","plots" ,plotname)

              #               png(filename
              #                   ,width = 7.5 ,height = 5,
              #                   units = "in"
              #                   ,res=300
              #                   )
              tiff(filename
                   ,width = 7.5 ,height = 5,
                   units = "in"
                   ,res=300, compression = "lzw",type="cairo",
                   antialias = "default"

              )
              # pdf(filename, height = 6, width = 6.83,family = "Arial", paper = "special", onefile = FALSE)

              #y=ifelse(test= output[o]=="_MeanSizeOfClusters",yes=500,no=500)
              y=max(temp_valores_replicas,na.rm = TRUE)+1
              #y=1001
              par(
                mar=c(4,5,1,2)+0.1
              )
              plot(
                temp_valores_replicas[,1]
                , ylim=c(-1,y)
                , xlab = "Time steps"
                , ylab = metrica
                #  ,main = paste(metrica,graphtype, sep = " ")
                , type="l"
                ,bty="l"
                ,family="Arial"
                #,pch=19
                # ,cex=2
                #,cex.axis=1,5
                ,cex.lab=1.5
                #,cex.main =2
                #,cex.sub=2

              )
              for (p in 2:ncol(temp_valores_replicas))
              {lines(temp_valores_replicas[p],col=p)}


              # par(op)#restores parameter settings

              dev.off()
              #
              #               #plotando médias
              #               valores.medios.por.mem[m]=rowMeans(temp_valores_replicas)
              #               valores.sd.medio.por.mem[m]=rowSds(as.matrix(temp_valores_replicas))
              #
              #               #creating plot names
              # #               graphtype=NA
              # #               if(type=="g"){graphtype=" with general recognition "}
              # #               if (type=="i") {graphtype=" with Individual Recognition "}
              # #               if (type=="nr") {graphtype=" with No Recognition "}
              # #
              #               plotnameMedias =paste(
              #                 "averages,", metrica,
              #                 paste(
              #                   #" mem type = "
              #                       #,
              #                       #outputType
              #                      #,
              #                      graphtype
              #                       #, ", média, NAgentes = ", N_agents
              #                      # , " raio = ", radius,
              #                      # ", mundo = ", world_size
              #                       , ", mem length = ", as.numeric(mem_length)
              #                 #, ", mem type = ", type
              #                 , ", mem modifier = ", as.numeric (modifier)
              #                     #  , ", comprimento de memoria = ", as.numeric(mem_length)
              #                     #  ,  "modificador de memória = ", as.numeric (modifier)
              #                       ,".png"
              #                       , sep = "")
              #                 , sep = "")
              #               if("plots"%in%dir()==FALSE) dir.create("plots")
              #               filename = file.path("C:", "Users", "Vitor","Desktop", "novas sim plos","plots",plotnameMedias)
              #               #pdf(filename, height = 6, width = 6.83,family = "Arial", paper = "special", onefile = FALSE)
              #               # op <- par(mar = c(5, 4, 0.05, 0.05) + 0.1)
              #                 #postscript(filename, height = 6, width = 6.83, family = "Arial", paper = "special", onefile = FALSE, horizontal = FALSE)
              #               png(filename,width = 1000,height = 1000)
              #               #title=paste(metrica)
              #               y=ifelse(test= output[o]=="_MeanSizeOfClusters",yes=1000,no=1000)
              #               plot(valores.medios.por.mem[,m]
              #                    , ylim=c(-1,y)
              #                    , xlab = "Time steps"
              #                    , ylab = metrica
              #                    ,main = plotnameMedias
              #                    , type="l"
              #                    ,bty="l"
              #                    #,family="Arial"
              #                    ,pch=19
              #                        ,cex=2
              #                        #,cex.axis=1,5
              #                        ,cex.lab=2
              #                        #,cex.main =2
              #                        #,cex.sub=2
              #                        ,mar=c(7,7,7,7)
              #                        ,oma=c(2,2,2,2)
              #               )
              #
              #               dev.off()

            }
          }
          #dev.off()

          #           #plotando médias
          #           plotname2=paste(outputType, ", N agente = ", N_agents, " raio = ",radius,", mundo = ", world_size,", media de todos os comprimentos de memoria ", type,", modificador de memoria = ", as.numeric (modifier), sep = "")
          #
          #           png(paste (plotname2,".png", sep=""),width = 900,height = 900)
          #           #tail(temp_valores_replicas)
          #           title=paste(metrica, ", N agente = ", N_agents, " raio = ",radius,", media de todos os comprimentos de memória", " \n","tamanho do mundo =", world_size,",tipo de memoria =", type,", modificador de memoria = ",  as.numeric (modifier), sep = "")
          #           y=ifelse(test= output[o]=="_MeanSizeOfClusters",yes=1000,no=1000)
          #           #y=1001
          #           plot(valores.medios.por.mem[1], ylim=c(-1,y), xlab = "Tempo", ylab = metrica,main = title, type="l")
          # #           for (p in 2:ncol(valores.medios.por.mem))
          # #           {lines(valores.medios.por.mem[p],col="red")}
          #           dev.off()
          #           #plotando sds
          #           plotname3=paste(outputType, ", N agente = ", N_agents, " raio = ",radius,", mundo =", world_size,", variancia de todos os comprimentos de memoria", type, ", modificador de memoria = ", as.numeric (modifier), sep = "")
          #
          #           png(paste (plotname3,".png", sep=" "),width = 900,height = 900)
          #           #tail(temp_valores_replicas)
          #            title=paste(metrica, ", N agente = ", N_agents, " raio = ",radius,", variancia de todos os comprimentos de memória", " \n","tamanho do mundo =", world_size,",tipo de memoria =", type, ", modificador de memoria = ", as.numeric (modifier), sep = "")
          #           y=ifelse(test= output[o]=="_MeanSizeOfClusters",yes=1000,no=1000)
          #           #y=1001
          #           plot(valores.medios.por.mem[1], ylim=c(-1,y), xlab = "Tempo", ylab = metrica,main = title, type="l")
          # #           for (p in 2:ncol(valores.medios.por.mem))
          # #           {lines(valores.sd.medio.por.mem[p],col=p)}
          #           dev.off()
        }
      }
    }
  }
}


