setwd("C:/Users/Vitor/Desktop/sim abacus")
#setwd("C:/Users/Vrios/Dropbox/Doutorado/codigo/socrats/Socrats_Doc_replicas")
library("matrixStats") #rowSds() function <- now needs a matrix instead of a data.frame

# list files with .txt extension
files  <- list.files(pattern = 'g_clusterContent|i_clusterContent')
#read memory lengths from filenames
temp_length <- read.table(textConnection(files), sep = "_")
unique(temp_length[2])
mem_lengths = unique(temp_length[16])
mem_lengths=sort(mem_lengths[,])
mem_lengths
#read number of iterations from filenames
n_iter= as.numeric(temp_length[1,14])
n_iter # numero de iterações
#read densities from filenames
N_agents=unique(temp_length[,6])
sizes=(unique(temp_length[,4]))
densities = N_agents/sizes^2 # individuals per unit area
densities
#read number of replicates from filenames
replicate = as.character(unique(temp_length[,18]))
replicate=strtrim(replicate, nchar(replicate)-4)
replicate
#memory type
mem_types=c("g","i")

type="i"

#calculate average metric for all replicates of all mem_lengths of each density, for a given mem_type
replica.med=function(type,size,metric)#type = memory type, size= agent density
{
  if (metric != "meanClusterSize" | metric != "meanNumber" | metric !="StandardDev")
  {return ("error, wrong metric")}
  
#selects function
  outputType =NA
  if (metric == "meanClusterSize" ) {
    outputType = paste( type, "_clusterContent",sep="")
    func= rowMeans
  }
  if ( metric == "meanNumber" ){
    outputType = paste( type, "_numberOfClusters",sep="")
  func=rowMeans
  }
  if ( metric=="StandardDev"){
    outputType = paste( type, "_clusterContent",sep="")
  func=rowSds
  }
  #read files for a given metric
  # list files with .txt extension
  files  <- list.files(pattern = outputType)
  #read memory lengths from filenames
  temp_length <- read.table(textConnection(files), sep = "_")
  unique(temp_length[2])
  mem_lengths = unique(temp_length[16])
  mem_lengths=sort(mem_lengths[,])
  mem_lengths
  #read number of iterations from filenames
  n_iter= as.numeric(temp_length[1,14])
  n_iter # numero de iterações
  
  #read number of replicates from filenames
  replicate = as.character(unique(temp_length[,18]))
  replicate=strtrim(replicate, nchar(replicate)-4)
  replicate
  valores.medios.por.mem=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
  colnames(valores.medios.por.mem) = mem_lengths
  
  for (i in 1:length(mem_lengths))
  {
    files_for_mem=0
    bruteData=0
    #create file list with selected memory lengths
    reg.exp=paste(
      
      paste(type,outputType,sep="")
      #,mem_lengths[i]
      ,paste("tam_", size, sep="") #only one density
      ,'.*'
      ,paste("tMem_", mem_lengths[i],"_", sep="")#only one memory length
      #,'.*'
      ,sep="")
    #reg.exp2=grep(pattern=reg.exp,files,value=TRUE)
    files_for_mem=list.files(pattern = reg.exp)
    #i_sd=list.files(pattern = temp)
    
    #read files
    dataTable <- lapply(files_for_mem, read.table, header = FALSE)
    #calculates average group size for given memory length
    sd=as.data.frame(dataTable)#dados brutos
    #w=function(x){x[is.nan(x)] <- 0;return(x)}
    #   w=function(x){
    #     x[is.nan(x)] <- 0
    #     x[is.na<-(x)] <- 0
    #     return(x)}
    #sd=apply(tam.medio.por.replicas,FUN=w, MARGIN=c(2))
    #sd.medios[,i]= as.data.frame(rowSds(sd), na.rm=FALSE)
    valores.medios.por.mem[,i]= as.data.frame(func(as.matrix(bruteData)), na.rm=TRUE)
  }
  return (valores.medios.por.mem)
}


#functions to calulate averages of averages through replicates
tam.med=function(type,d)#type = memory type, d= agent density
{
  #calculate average group size
  tamanhos.medios.por.mem=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
  colnames(tamanhos.medios.por.mem) = mem_lengths
  #i=mem_lengths[2]
  for (i in 1:length(mem_lengths))
  {
    i_tam=0
    tam.medio.por.replicas=0
    #create file list with selected memory lengths
    
    reg.exp=paste(
      #'i_tam.*' #only group memory
      paste(type,"_tam.*",sep="")
      #,mem_lengths[i]
      ,paste("tam_", d, sep="") #only one density
      ,'.*'
      ,paste("tMem_", mem_lengths[i],"_", sep="")#only one memory length
      #,'.*'
      ,sep="")
    
    i_tam=list.files(pattern = reg.exp)
    
    #read files from list
    tablesitam <- lapply(i_tam, read.table, header = FALSE)
    
    #calculates average group size for given memory length
    tam.medio.por.replicas=as.data.frame(tablesitam)#dados brutos
    #   w=function(x){
    #     x[is.nan(x)] <- 0
    #     x[is.na<-(x)] <- 0
    #     return(x)}
    #   tam.medio.por.replicas=apply(tam.medio.por.replicas,FUN=w, MARGIN=c(2))
    tamanhos.medios.por.mem[,i]= as.data.frame(rowMeans(tam.medio.por.replicas, na.rm=TRUE))
    # tamanhos.medios.por.mem[,i]= as.data.frame(rowMeans(tam.medio.por.replicas, na.rm=FALSE))
  }
  return (tamanhos.medios.por.mem)
}

#calculate average group size  standard deviation
sd.med=function(type,d)#type = memory type, d= agent density
{
  valores.medios.pormem=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
  colnames(valores.medios.pormem) = mem_lengths
  
  for (i in 1:length(mem_lengths))
  {
    i_sd=0
    sd=0
    #create file list with selected memory lengths
    reg.exp=paste(
      #'i_var.*' #only group memory
      paste(type,"sd*",sep="")
      #,mem_lengths[i]
      ,paste("tam_", d, sep="") #only one density
      ,'.*'
      ,paste("tMem_", mem_lengths[i],"_", sep="")#only one memory length
      #,'.*'
      ,sep="")
    #reg.exp2=grep(pattern=reg.exp,files,value=TRUE)
    i_sd=list.files(pattern = reg.exp)
    #i_sd=list.files(pattern = temp)
    
    #read files
    tablesisd <- lapply(i_sd, read.table, header = FALSE)
    #calculates average group size for given memory length
    sd=as.data.frame(tablesisd)#dados brutos
    #w=function(x){x[is.nan(x)] <- 0;return(x)}
    #   w=function(x){
    #     x[is.nan(x)] <- 0
    #     x[is.na<-(x)] <- 0
    #     return(x)}
    #sd=apply(tam.medio.por.replicas,FUN=w, MARGIN=c(2))
    #sd.medios[,i]= as.data.frame(rowSds(sd), na.rm=FALSE)
    valores.medios.pormem[,i]= as.data.frame(rowSds(as.matrix(sd)), na.rm=TRUE)
  }
  return (valores.medios.pormem)
}

#calculate average group size  standard deviation
sd.med=function(type,d)#type = memory type, d= agent density
{
  valores.medios.pormem=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
  colnames(valores.medios.pormem) = mem_lengths
  
  for (i in 1:length(mem_lengths))
  {
    i_sd=0
    sd=0
    #create file list with selected memory lengths
    reg.exp=paste(
      #'i_var.*' #only group memory
      paste(type,"sd*",sep="")
      #,mem_lengths[i]
      ,paste("tam_", d, sep="") #only one density
      ,'.*'
      ,paste("tMem_", mem_lengths[i],"_", sep="")#only one memory length
      #,'.*'
      ,sep="")
    #reg.exp2=grep(pattern=reg.exp,files,value=TRUE)
    i_sd=list.files(pattern = reg.exp)
    #i_sd=list.files(pattern = temp)
    
    #read files
    tablesisd <- lapply(i_sd, read.table, header = FALSE)
    #calculates average group size for given memory length
    sd=as.data.frame(tablesisd)#dados brutos
    #w=function(x){x[is.nan(x)] <- 0;return(x)}
    #   w=function(x){
    #     x[is.nan(x)] <- 0
    #     x[is.na<-(x)] <- 0
    #     return(x)}
    #sd=apply(tam.medio.por.replicas,FUN=w, MARGIN=c(2))
    #sd.medios[,i]= as.data.frame(rowSds(sd), na.rm=FALSE)
    valores.medios.pormem[,i]= as.data.frame(rowSds(as.matrix(sd)), na.rm=TRUE)
  }
  return (valores.medios.pormem)
}

#calculate group size average standard deviation
n.med=function(type,d)#type = memory type, d= agent density
{
  n.medios.por.mem=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
  colnames(n.medios.por.mem) = mem_lengths
  #i=2
  for (i in 1:length(mem_lengths))
  {
    i_n=0
    n=0
    #create file list with selected memory lengths
    reg.exp=paste(      #'i_num.*'
      paste(type,"_num.*",sep="")
      #,mem_lengths[i]
      ,paste("tam_", d, sep="") #only one density
      ,'.*'
      ,paste("tMem_", mem_lengths[i],"_", sep="")#only one memory length
      #,'.*'
      ,sep="")
    # temp=grep(pattern=reg.exp3,files,value=TRUE)
    i_n=list.files(pattern = reg.exp)
    #i_n=list.files(pattern = temp)
    #read files
    tablesin <- lapply(i_n, read.table, header = FALSE)
    
    #calculates average group size for given memory length
    n=as.data.frame(tablesin)#dados brutos
    #w=function(x){x[is.nan(x)] <- 0;return(x)}
    #w=function(x){x[is.nan(x)] <- 0;return(x)}
    #   w=function(x){
    #     x[is.nan(x)] <- 0
    #     x[is.na<-(x)] <- 0
    #     return(x)}
    # n=apply(tam.medio.por.replicas,FUN=w, MARGIN=c(2))
    n.medios.por.mem[,i]= as.data.frame(rowMeans(n), na.rm=TRUE)
    #n.medios.por.mem[,i]= as.data.frame(rowMeans(n), na.rm=FALSE)
  }
  return(n.medios.por.mem)
}

#create empty arrays to store data
#arrays tridimensionais : numero de interações X comprimentos de memória X densidades
i_results_tam=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))
                    , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))
i_results_sd=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))
                   , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))
i_results_n=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))
                  , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))


g_results_tam=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))
                    , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ",  round (densities, 3),sep="")))
g_results_sd=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))
                   , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))
g_results_n=array(data=0, dim=c(n_iter,length(mem_lengths),length(densities))
                  , dimnames=list(paste("t",(1:n_iter),sep=""), paste("Comprimento Memória",mem_lengths,sep=" "),paste("Densidade ", round (densities, 3),sep="")))

#for each density, read the files, separating by memory length
for (d in 1:length(densities))
{
  type="i"
  # results_tam[,,d]=tam.med(type="i",d)
  i_results_tam[,,d]=as.matrix(as.data.frame(replica.med(type="i",d,"meanClusterSize")))
#   i_results_sd[,,d]=as.matrix(as.data.frame(sd.med(type="i",d)))
#   i_results_n[,,d]=as.matrix(as.data.frame(n.med(type="i",d)))
#   #   results_sd[,,d]=sd.med(type="i",d)
#   #   results_n[,,d]=n.med(type="i",d)
#   type="g"
#   g_results_tam[,,d]=as.matrix(as.data.frame(tam.med(type="g",d)))
#   g_results_sd[,,d]=as.matrix(as.data.frame(sd.med(type="g",d)))
#   g_results_n[,,d]=as.matrix(as.data.frame(n.med(type="g",d)))
#   
}

i_results_tam[1:10,,]
g_results_tam[1:10,,]

######## plotagem
#one plot for each density

for (d in 1:length(densities))
{
  #x11()
  mems=as.data.frame(matrix(NA,nrow = n_iter, ncol = length(mem_lengths)))#armazena a série temporal de cada comprimento de meória
  colnames(mems)= paste("comprimento", mem_lengths, sep=" ")
  for (z in 1:ncol(i_results_tam[,,d]))
  {
    x11()
    # mems[,z]=lowess(i_results_tam[,z,d])$y
    mems[,z]=i_results_tam[,z,d]
    m=paste("Memória Individual",
            dimnames(i_results_tam)[[3]] [z],
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
for (d in 1:length(densities))
{
  #x11()
  mems=as.data.frame(matrix(NA,nrow = n_iter, ncol = length(mem_lengths)))#armazena a série temporal de cada comprimento de meória
  colnames(mems)= paste("comprimento", mem_lengths, sep=" ")
  for (z in 1:ncol(g_results_tam[,,d]))
  {
    x11()
    # mems[,z]=lowess(i_results_tam[,z,d])$y
    mems[,z]=g_results_tam[,z,d]
    m=paste("Memória grupal",
            dimnames(g_results_tam)[[3]] [z], 
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

