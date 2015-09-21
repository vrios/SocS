# dado que as ids do r sempre começam com 1, é necessário importar os dados e somar ao id
setwd("C:/Users/Vitor/Dropbox/Doutorado/codigo/build-Socrats_Doc_replicas-Desktop_Qt_5_4_0_MinGW_32bit-Debug/preferencia afiliativa")
library(igraph)


calc_modularity=function(file = f)
{
  library(igraph)
  g=as.data.frame(read.table(file, as.is=T, header= T, sep=";"))
  # dado que as ids do r sempre começam com 1, é necessário importar os dados e somar 1 ao id
  g[,1]=g[,1]+1#corrigindo valores de id
  g[,2]=g[,2]+1#corrigindo valores de id
  graph=graph.edgelist(as.matrix(g[,1:2]), directed = F) #cria o grafo
  E(graph)$Weight=g[,3]#adiciona os pesos das arestas

  g.modulos=multilevel.community(graph)# calcula modularidade de louvain
  return (max(g.modulos$modularity))

}

files  <- list.files(pattern = "Edges")#reads files only to find parameters
#read memory lengths from filenames
temp_length <- read.table(textConnection(files), sep = "_", as.is=TRUE, colClasses = "character")
unique(temp_length[2])
mem_lengths = unique(temp_length[16])
mem_lengths=sort(mem_lengths[,])
mem_lengths
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
mem_mods = as.character(unique(temp_length[,18]))

#memory type
mem_types=c("g","i")
# mem_types=c("g")
# mem_types=c("i")
#read number of replicates from filenames
replicate = as.character(unique(temp_length[,20]))
replicate=strtrim(replicate, nchar(replicate)-4)
replicate

reg.exp=paste(
  "finalSocEdges"
  ,"_tam_",sep="*")

files  <- list.files(pattern = reg.exp)

output = "_finalSocEdges"
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
        for (m in 1:(length(mem_lengths)))
        {
          #mem_length=mem_lengths[1]
          mem_length = mem_lengths[m]
          valores.medios.por.mem = data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths)))
          valores.sd.medio.por.mem = data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths)))
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
              temp_valores_replicas=as.data.frame(data.frame(matrix(NA, nrow = 1, ncol = length(replicate))))
              for (r in 1:(length(files_to_read)))
              {
                #  message(paste(type, mem_length, files_to_read[r], sep = " "))
                mod=calc_modularity(file=files_to_read[r])
                temp_valores_replicas[,r] <- calc_modularity(file=files_to_read[r])

              }

              metrica="Modularidade"
              plotname=paste(metrica, ", N agente = ", N_agents, " raio = ",radius,",mundo =", world_size,", comprimento de memoria = ",  mem_length, ",tipo de memoria =", type, ", modificador de memoria = ", modifier)
              png(paste (plotname,".png", sep=""),width = 900,height = 900)
              #tail(temp_valores_replicas)
              title=paste(metrica, ", N agente = ", N_agents, " raio = ",radius,", comprimento de memoria = ",  mem_length, " \n","tamanho do mundo =", world_size,",tipo de memoria =", type, ", modificador de memoria = ", modifier)
              plot(temp_valores_replicas[,1], ylim=c(-1,1.5), xlab = "Tempo", ylab = metrica,main = title)
              for (p in 1:ncol(temp_valores_replicas))
              {points(temp_valores_replicas[p],col=p)}
              dev.off()

            }
          }

        }
      }
    }

  }
}