# dado que as ids do r sempre começam com 1, é necessário importar os dados e somar ao id
#setwd("C:/Users/Vitor/Dropbox/Doutorado/codigo/build-Socrats_Doc_replicas-Desktop_Qt_5_4_0_MinGW_32bit-Debug/preferencia afiliativa")
#setwd("C:/Users/Vitor/Desktop/abacus 3")
setwd("C:/Users/Vitor/Desktop/novas sim plos")

library(igraph)
library("extrafont")#for using different fonts in graphs
loadfonts(quiet = TRUE) ## allows use of arial
source(
  "C:/Users/Vitor/Dropbox/Doutorado/codigo/socrats/r analyses codes/calc_modularity.R"
)
source(
  "C:/Users/Vitor/Dropbox/Doutorado/codigo/socrats/r analyses codes/calc.mean.degree.R"
)

# calc_modularity=function(file = f)
# {
#   library(igraph)
#   g=as.data.frame(read.table(file, as.is=T, header= T, sep=";"))
#   # dado que as ids do r sempre começam com 1, é necessário importar os dados e somar 1 ao id
#   g[,1]=g[,1]+1#corrigindo valores de id
#   g[,2]=g[,2]+1#corrigindo valores de id
#   graph=graph.edgelist(as.matrix(g[,1:2]), directed = F) #cria o grafo
#   E(graph)$Weight=g[,3]#adiciona os pesos das arestas
#
#   g.modulos=multilevel.community(graph)# calcula modularidade de louvain
#   return (max(g.modulos$modularity))
#
# }

files  <-
  list.files(pattern = "Edges")#reads files only to find parameters
#read memory lengths from filenames
temp_length <-
  read.table(
    textConnection(files), sep = "_", as.is = TRUE, colClasses = "character"
  )
#unique(temp_length[2])
mem_lengths = unique(temp_length[16])
mem_lengths = sort(mem_lengths[,])
#mem_lengths
#memory type
mem_types = unique(temp_length[1])
mem_types = sort(mem_types[,])

#read number of iterations from filenames
n_iter = as.numeric(temp_length[1,14])
n_iter # numero de iterações
#read densities from filenames
N_agents = as.numeric(unique(temp_length[,6]))
world_sizes = sort(as.numeric(unique(temp_length[,4])))
densities = N_agents / world_sizes ^ 2 # individuals per unit area
#densities
# read radii from filenames
radii = as.numeric(unique(temp_length[,8]))
mem_mods = as.character(unique(temp_length[,18]))
mem_mods = sort(mem_mods)
#read number of replicates from filenames
replicate = as.character(unique(temp_length[,20]))
replicate = strtrim(replicate, nchar(replicate) - 4)
#replicate

reg.exp = paste("finalSocEdges"
                ,"_tam_",sep = "*")

files  <- list.files(pattern = reg.exp)

# output = "_finalSocEdges"
# for (o in 1:length(output))
# {
#   #outType=output[1]
#   output[o]
valores.medios.por.mem.mod = data.frame(matrix(NA, nrow = length(mem_mods), ncol = 2))
temp_modularidade_replicas = as.data.frame(data.frame(matrix(
  NA, nrow = length(replicate), ncol = length(mem_mods))))
rownames(temp_modularidade_replicas) = replicate
colnames(temp_modularidade_replicas) = mem_mods
for (r in 1:length(radii))
{
  #radius =radii[1]
  radius = radii[r]
  for (t in 1:length(mem_types))
  {
    #type=mem_types[1]
    type = mem_types[t]
    for (s in 1:length(world_sizes))
    {
      #world_size=world_sizes[1]
      world_size = world_sizes[s]
      outputType = paste(type, "_finalSocEdges" ,sep = "")
      for (m in 1:(length(mem_lengths)))
      {
        #mem_length=mem_lengths[1]
        mem_length = mem_lengths[m]

        valores.medios.por.mem.mod[,1] = mem_mods
        for (mod in 1:length(mem_mods))
        {
          modifier = mem_mods[mod]

          #colnames(valores.medios.por.mem.mod) = mem_mods

          reg.exp = paste(
            paste(outputType,sep = "")
            ,paste("_tam_", world_size, sep = "") #only one density
            ,'.*'
            ,paste("_raio_", radius, sep = "") #only one radius
            ,'.*'
            ,paste("tMem_", mem_length,"_", sep = "")#only one memory length
            ,'.*'
            ,paste("MemMod_", modifier,"_", sep = "")#only one memory modifier
            ,'.*'
            ,sep = ""
          )
          files_to_read = list.files(pattern = reg.exp)
          if (length(files_to_read) != 0)
          {
            for (r in 1:(length(files_to_read)))
            {
              temp_modularidade_replicas[r,mod] <-
                calc_modularity(file = files_to_read[r])
            }
            valores.medios.por.mem.mod[mod,2] = mean(as.numeric(temp_modularidade_replicas[mod,]))
          }
        }


        metrica = "Modularity value"
        graphtype = NA
        if (type == "g") {
          graphtype = " with general recognition "
        }
        if (type == "i") {
          graphtype = " with Individual Recognition "
        }
        if (type == "nr") {
          graphtype = " with No Recognition "
        }

        #         plotname =paste(
        #           # "forPaper ", metrica
        #           #, ", NAgentes = ", N_agents
        #           # , ", raio = ", radius
        #           # , ", mundo = ", world_size
        #           "Average",metrica
        #           ,graphtype
        #           #, ", comprimento de memoria = ", as.numeric(mem_length)
        #           , ", mem length = ", as.numeric(mem_length)
        #           # , ", tipo de memória = ", type
        #           #, ", modificador de memória = ", as.numeric (modifier)
        #           , ", mem modifier = ", as.numeric (modifier)
        #           ,".tiff"
        #           , sep = "")
        #         if("plots"%in%dir()==FALSE) dir.create("plots")
        #         filename = file.path("C:", "Users", "Vitor","Desktop", "novas sim plos","plots" ,plotname)
        #         #   filename = file.path("C:", "Users", "Vitor","Desktop", "abacus 3","plots for paper",plotname)
        #         #par(cex=2)
        #         tiff(filename
        #              ,width = 7.5 ,height = 5,
        #              units = "in"
        #              ,res=300, compression = "lzw",type="cairo",
        #              antialias = "default"
        #         )
        #         #  png(filename,width = 900,height = 900)
        #         par(
        #           mar=c(4,5,1,2)+0.1
        #         )
        #         plot(
        #           #x=temp_modularidade_replicas[,1]
        #           x=valores.medios.por.mem.mod[,1]
        #           , y=valores.medios.por.mem.mod[,2]
        #           , ylim=c(0,0.6)
        #           , xlim= c(0,0.55)
        #
        #           , xaxt = "n"
        #           #, xlab = "Memory modifier (%)"
        #           , ylab = metrica
        #           #,main = title
        #           ,bty="l"
        #           ,pch=19
        #           #,cex=2
        #           #,cex.axis=1,5
        #           ,cex.lab=2
        #           #,cex.main =2
        #           #,cex.sub=2
        #           # ,mar=c(7,7,7,7)
        #           # ,oma=c(2,2,2,2)
        #         )
        #         #for (p in 2:ncol(temp_modularidade_replicas))
        #         #{points(temp_modularidade_replicas[p],col=p)}
        #         #                   for (p in 1:ncol(valores.medios.por.mem.mod))
        #         #                   {points(valores.medios.por.mem.mod[p],col=p)}
        #         axis(side=1, at =mem_mods,labels=as.numeric(mem_mods))
        #         dev.off()

        ###############
        plotname2 = paste(
          # "forPaper ", metrica
          #, ", NAgentes = ", N_agents
          # , ", raio = ", radius
          # , ", mundo = ", world_size
          "Replicates",metrica
          ,graphtype
          #, ", comprimento de memoria = ", as.numeric(mem_length)
          , ", mem length = ", as.numeric(mem_length)
          # , ", tipo de memória = ", type
          #, ", modificador de memória = ", as.numeric (modifier)
          , ", mem modifier = ", as.numeric (modifier)
          ,".tiff"
          , sep = ""
        )

        if ("plots" %in% dir() == FALSE)
        {
          dir.create("plots")
        }

        filename = file.path("C:", "Users", "Vitor","Desktop", "novas sim plos","plots" ,plotname2)

        tiff(
          filename
          ,width = 7.5 ,height = 5,
          units = "in"
          ,res = 300, compression = "lzw",type = "cairo",
          antialias = "default"
        )

        par(mar = c(4,5,1,2) + 0.1)

        plot(
          y = temp_modularidade_replicas[1,1]
          ,
          x = valores.medios.por.mem.mod[1,1]
          #x=valores.medios.por.mem.mod[,1]
          #, y=valores.medios.por.mem.mod[,2]
          , ylim = c(0,0.6)
          , xlim = c(0,0.55)
          , xaxt = "n"
          , xlab = "Memory modifier (%)"
          , ylab = metrica
          #,main = title
          ,bty = "l"
          ,pch = 1
          #,cex=2
          #,cex.axis=1,5
          ,cex.lab = 2
        )
        for(xvalues in 1:length(mem_mods))
        {
          for (yvalues in 1:nrow(temp_modularidade_replicas))
          {
            points(x=valores.medios.por.mem.mod[xvalues,1]
                   ,y=temp_modularidade_replicas[yvalues,xvalues]
                   #,col = xvalues
            )
          }
        }

        axis(side = 1, at = mem_mods,labels = as.numeric(mem_mods))
        dev.off()
        ######## saving modularities to .csv to save time in analysis
        write.csv(x = temp_modularidade_replicas, file = paste(filename,".csv",sep=""))

      }
    }
  }
}