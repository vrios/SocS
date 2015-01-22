# dado que as ids do r sempre começam com 1, é necessário importar os dados e somar ao id
setwd("C:/Users/Vitor/Dropbox/Doutorado/codigo/socrats/build-Socrats_Doc_replicas-Desktop_Qt_5_3_MSVC2013_32bit-Debug/debug/")
library(igraph)


# list files with .txt extension
files  <- list.files(pattern = 'g_r')##type is irrelevante here, this block will only get the paramter from filenames
#read memory lengths from filenames
temp_length <- read.table(textConnection(files), sep = "_")
mem_lengths = unique(temp_length[16])##verificar numero da coluna no objeto tempo_length
mem_lengths=sort(mem_lengths[,])
#read number of iterations from filenames
n_iter= as.character(temp_length[1,18])
n_iter= as.numeric(strtrim(n_iter, nchar(n_iter)-4))#remove .txt from string

#read densities from filenames
sizes=(unique(temp_length[,6]))##verificar numero da coluna no objeto tempo_length
densities = 100/sizes^2 # individuals per square unit
#read number of replicates from filenames
n_rep = length(unique(temp_length[,4]))
#functions to calulate averages of averages through replicates

type="i"

size=sizes[2]

modularidade.med=function(type,size)#type = memory type, d= agent density
{
  #calculate average group size
  modularidade.por.mem=as.data.frame(data.frame(matrix(NA, nrow = n_iter,ncol = length(mem_lengths))))
  colnames(modularidade.por.mem) = mem_lengths
  #i=mem_lengths[3]
  for (i in 1:length(mem_lengths))
  {
    for (rep in 0:n_rep)
    {
      #create file list with selected memory lengths
      reg.exp=paste(
        paste(type,"_rede.*",sep="")#for a given memory type
        ,paste("rep_",n_rep,"_",sep="")
        ,paste("tam_", sizes[size], sep="") #only one density
        ,'.*'#everything in between
        ,paste("tMem_", mem_lengths[i],"_", sep="")#only one memory length
        ,sep="")
      
      i_rede=list.files(pattern = reg.exp)
      #read files from list
      
      mod.por.replica=0
      for (q in 1:length(i_rede))
      {
        message(i_rede[q])
        mod.por.replica[q]=calc_modularity(file=i_rede[q])
        
      }
      #calculates average group size for given memory length
    }
      modularidade.por.mem[,i]= as.data.frame(mod.por.replica)
      
    }
    return (modularidade.por.mem)
  }
  
  
  #create empty arrays to store data
  #arrays tridimensionais : numero de interações X comprimentos de memória X densidades
  i_results_tam=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))                    , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))
  
  
  g_results_tam=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))                    , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ",  round (densities, 3),sep="")))
  
  d=1
  #for each density, read the files, separating by memory length
  for (d in 1:length(densities))
  {
    type="i"
    # results_tam[,,d]=tam.med(type="i",d)
    i_results_tam[,,d]=as.matrix(as.data.frame(modularidade.med(type="i",d)))
    type="g"
    g_results_tam[,,d]=as.matrix(as.data.frame(modularidade.med(type="g",d)))
    
  }
  
  