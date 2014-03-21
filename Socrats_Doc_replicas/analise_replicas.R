setwd("C:/Users/Vrios/Dropbox/Doutorado/codigo/socrats/Socrats_Doc_replicas")
library("matrixStats") 
##memoria individual
#tamanhos dos clusters
# list files with .txt extension
files  <- list.files(pattern = 'g_')
#read memory lengths from filenames
temp_length <- read.table(textConnection(files), sep = "_")
mem_lengths = unique(temp_length[17])
mem_lengths=sort(mem_lengths[,])
n_iter= as.character(temp_length[1,19])
n_iter= as.numeric(strtrim(n_iter, nchar(n_iter)-4))
n_iter # numero de iterações
#expressão regular g_tam.*tMem_2000.* -> retorna tudo que tiver g_tam e tMem_2000 em qualquer lugar da string
# reg=paste('g_tam.*',as.character(z),'.*', sep="")
# la=grep(pattern=reg,i_tam,value=TRUE)  
# la  

#read only files with  a given memory length
tamanhos.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(tamanhos.medios) = mem_lengths

#calculate average group size
for (i in 1:length(mem_lengths))
  {
  #create file list with selected memory lengths
    reg.exp=paste('g_tam.*',mem_lengths[i],'.*', sep="")
    temp=grep(pattern=reg.exp,files,value=TRUE)
    i_tam=list.files(pattern = reg.exp)
    #read files
    tablesitam <- lapply(i_tam, read.table, header = FALSE)
    #calculates average group size for given memory length
    tam=as.data.frame(tablesitam)#dados brutos
    tamanhos.medios[,i]= as.data.frame(rowMeans(tam))
  }

#calculate group size average standard deviation
sd.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(sd.medios) = mem_lengths
i=1
for (i in 1:length(mem_lengths))
{
  #create file list with selected memory lengths
  reg.exp=paste('g_var.*',mem_lengths[i],'.*', sep="")
  temp=grep(pattern=reg.exp,files,value=TRUE)
  i_sd=list.files(pattern = reg.exp)
  #i_sd=list.files(pattern = temp)
  
  #read files
  tablesisd <- lapply(i_sd, read.table, header = FALSE)
  #calculates average group size for given memory length
  sd=as.data.frame(tablesisd)#dados brutos
  sd.medios[,i]= as.data.frame(rowSds(sd))
}
#calculate group size average standard deviation
n.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(n.medios) = mem_lengths
i=3
for (i in 1:length(mem_lengths))
{
  #create file list with selected memory lengths
  reg.exp=paste('g_num.*',mem_lengths[i],'.*', sep="")
  temp=grep(pattern=reg.exp,files,value=TRUE)
  i_n=list.files(pattern = reg.exp)
  #i_n=list.files(pattern = temp)
  #read files
  tablesin <- lapply(i_n, read.table, header = FALSE)

  #calculates average group size for given memory length
  n=as.data.frame(tablesin)#dados brutos
  n.medios[,i]= as.data.frame(rowSds(n))
}

x11()
matplot(tamanhos.medios, type = "l")
x11()
matplot(sd.medios, type = "l")
x11()
matplot(n.medios, type = "l")


