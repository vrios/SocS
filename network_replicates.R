# dado que as ids do r sempre começam com 1, é necessário importar os dados e somar ao id
setwd("C:/Users/Vitor/Desktop/sim")
library(igraph)


# list files with .txt extension
files  <- list.files(pattern = 'finalSpaceEdges')##type is irrelevante here, this block will only get the paramter from filenames
#read memory lengths from filenames
temp_length <- read.table(textConnection(files), sep = "_")
mem_lengths = unique(temp_length[16])##verificar numero da coluna no objeto tempo_length
mem_lengths=sort(mem_lengths[,])
#read number of iterations from filenames
n_iter= as.numeric(temp_length[1,14])
#n_iter= as.numeric(strtrim(n_iter, nchar(n_iter)-4))#remove .txt from string

#read densities from filenames
sizes=as.numeric(unique(temp_length[,4]))##verificar numero da coluna no objeto tempo_length
densities = 100/sizes^2 # individuals per square unit
#read number of replicates from filenames
n_rep = as.character(unique(temp_length[,18]))
n_rep= as.numeric(strtrim(x = n_rep,width =  nchar(n_rep)-4))
#functions to calulate averages of averages through replicates

type="i"

# size=sizes[2]
# rep=1
# q=1
modularidade.med=function(type,size)#type = memory type, d= agent density
{
  #calculate average group size
  modularidade.por.mem=as.data.frame(data.frame(matrix(NA, nrow = n_iter,ncol = length(mem_lengths))))
  colnames(modularidade.por.mem) = mem_lengths
  #i=mem_lengths[3]
  for (i in mem_lengths)
  {
    for (rep in n_rep)
    {
      #create file list with selected memory lengths
      reg.exp=paste(
        paste(type,"_finalSpaceEdges.*",sep="")#for a given memory type
        ,paste("tam_", sizes[size],"_", sep="") #only one density
        
        
        ,'.*'#everything in between
        ,paste("tMem_", mem_lengths[i],"_",".*", sep="")#only one memory length
        ,paste("rep_",rep,".",sep="")
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
  i_results_finalSpaceEdges=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))                    , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))
  
  
  g_results_finalSpaceEdges=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))                    , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ",  round (densities, 3),sep="")))
  
  d=1
  #for each density, read the files, separating by memory length
  for (d in 1:length(densities))
  {
    type="i"
    # results_tam[,,d]=tam.med(type="i",d)
    i_results_finalSpaceEdges[,,d]=as.matrix(as.data.frame(modularidade.med(type="i",d)))
    type="g"
    g_results_finalSpaceEdges[,,d]=as.matrix(as.data.frame(modularidade.med(type="g",d)))
    
  }
  warnings()


#plotagem
nrow(i_results_finalSpaceEdges)
ncol(i_results_finalSpaceEdges)
d=densities[2]
z =i_results_finalSpaceEdges[d,d,]
z
for (d in densities)
{
  #x11()
  mems=as.data.frame(matrix(NA,nrow = n_iter, ncol = length(mem_lengths)))#armazena a série temporal de cada comprimento de meória
  colnames(mems)= paste("comprimento", mem_lengths, sep=" ")
  for (z in 1:i_results_finalSpaceEdges[,,d])
  {
    x11()
    # mems[,z]=lowess(i_results_tam[,z,d])$y
    mems[,z]=i_results_finalSpaceEdges[,z,d]
    m=paste("Memória Individual",
            dimnames(i_results_finalSpaceEdges)[[3]] [z],
            #dimnames(i_results_tam)[[2]] [z],
            sep=" , ")
    plot(mems[,1], type='l', xlab="tempo", ylab= "tamanho médio dos clusters", ylim=c(0,100), main=m)
    for (k in 2:ncol(mems))
    {
      lines(mems[,k],col=k)
    }
    legend('topright', # places a legend at the appropriate place 
           names(mems), # puts text in the legend 
           
           lty=c(1,1), # gives the legend appropriate symbols (lines)
           
           #lwd=c(2.5,2.5),
           col=c(1:ncol(mems)) # gives the legend lines the correct color and width
    )
  } 
}  

summary (g_results_finalSpaceEdges)
dim(g_results_finalSpaceEdges)
