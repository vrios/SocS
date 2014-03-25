setwd("C:/Users/Vrios/Dropbox/Doutorado/codigo/socrats/Socrats_Doc_replicas/debug/temp2")
#setwd("C:/Users/Vrios/Dropbox/Doutorado/codigo/socrats/Socrats_Doc_replicas")
library("matrixStats") 
##memoria grupal
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
  i_tam=0
  tam=0
  #create file list with selected memory lengths
    reg.exp=paste('g_tam.*',mem_lengths[i],'.*', sep="")
    #temp=grep(pattern=reg.exp,files,value=TRUE)
    i_tam=list.files(pattern = reg.exp)
    #read files
    tablesitam <- lapply(i_tam, read.table, header = FALSE)
    #calculates average group size for given memory length
    tam=as.data.frame(tablesitam)#dados brutos
  w=function(x){x[is.nan(x)] <- 0;return(x)}
  tam=apply(tam,FUN=w, MARGIN=c(2))
    tamanhos.medios[,i]= as.data.frame(rowMeans(tam))
  }

#calculate group size average standard deviation
sd.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(sd.medios) = mem_lengths

for (i in 1:length(mem_lengths))
{
  i_sd=0
  sd=0
  #create file list with selected memory lengths
  reg.exp=paste('g_var.*',mem_lengths[i],'.*', sep="")
  temp=grep(pattern=reg.exp,files,value=TRUE)
  i_sd=list.files(pattern = reg.exp)
  #i_sd=list.files(pattern = temp)
  
  #read files
  tablesisd <- lapply(i_sd, read.table, header = FALSE)
  #calculates average group size for given memory length
  sd=as.data.frame(tablesisd)#dados brutos
  w=function(x){x[is.nan(x)] <- 0;return(x)}
  sd=apply(tam,FUN=w, MARGIN=c(2))
  sd.medios[,i]= as.data.frame(rowSds(sd))
}
#calculate group size average standard deviation
n.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(n.medios) = mem_lengths

for (i in 1:length(mem_lengths))
{
  i_n=0
  n=0
  #create file list with selected memory lengths
  reg.exp=paste('g_num.*',mem_lengths[i],'.*', sep="")
  temp=grep(pattern=reg.exp,files,value=TRUE)
  i_n=list.files(pattern = reg.exp)
  #i_n=list.files(pattern = temp)
  #read files
  tablesin <- lapply(i_n, read.table, header = FALSE)

  #calculates average group size for given memory length
  n=as.data.frame(tablesin)#dados brutos
  w=function(x){x[is.nan(x)] <- 0;return(x)}
  n=apply(tam,FUN=w, MARGIN=c(2))
  n.medios[,i]= as.data.frame(rowSds(n))
}


#plotting 
#plotar tamanhos médios
ltam=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(ltam) = mem_lengths

for (z in 1:ncol(tamanhos.medios))
  {
  ltam[,z]=lowess(tamanhos.medios[,z])$y
  }
x11()
plot(ltam[,1], type='l',xlab="tamanho médio dos clusters / memoria grupal ", ylim=c(0,60))
for (k in 2:ncol(tamanhos.medios))
{
  lines(ltam[,k],col=k)
}

legend('topright', # places a legend at the appropriate place 
       names(tamanhos.medios), # puts text in the legend 
       
       lty=c(1,1), # gives the legend appropriate symbols (lines)
       
       #lwd=c(2.5,2.5),
       col=c(1:ncol(tamanhos.medios)) # gives the legend lines the correct color and width
)


#plotar SD médios
lsd=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(lsd) = mem_lengths

for (z in 1:ncol(sd.medios))
{
  lsd[,z]=lowess(sd.medios[,z])$y
}
x11()
plot(lsd[,1], type='l',xlab="sd médio dos tamanhos dos clusters  / memoria grupal ", ylim=c(0,60))
for (k in 2:ncol(sd.medios))
{
  lines(lsd[,k],col=k)
}

legend('topright', # places a legend at the appropriate place 
       names(sd.medios), # puts text in the legend 
       
       lty=c(1,1), # gives the legend appropriate symbols (lines)
       
       #lwd=c(2.5,2.5),
       col=c(1:ncol(sd.medios)) # gives the legend lines the correct color and width
)


#plotar número médio de clusters
ln=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(ln) = mem_lengths

for (z in 1:ncol(n.medios))
{
  ln[,z]=lowess(n.medios[,z])$y
}
x11()
plot(ln[,1], type='l',xlab="numero medio de clusters / memoria grupal ",ylim=c(0,60))
for (k in 2:ncol(n.medios))
{
  lines(ln[,k], col=k)
}

legend('topright', # places a legend at the appropriate place 
       names(n.medios), # puts text in the legend 
       
       lty=c(1,1), # gives the legend appropriate symbols (lines)
       
       #lwd=c(2.5,2.5),
       col=c(1:ncol(n.medios)) # gives the legend lines the correct color and width
)




##memoria individual
#tamanhos dos clusters
# list files with .txt extension
files  <- list.files(pattern = 'i_')
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
i=1
for (i in 1:length(mem_lengths))
{
  i_tam.=0
  tam=0
  #create file list with selected memory lengths
  reg.exp=paste('i_tam.*',mem_lengths[i],'.*', sep="")
  #temp=grep(pattern=reg.exp,files,value=TRUE)
  i_tam=list.files(pattern = reg.exp)
  #read files
  tablesitam <- lapply(i_tam, read.table, header = FALSE)
  #calculates average group size for given memory length
  tam=as.data.frame(tablesitam)#dados brutos
  w=function(x){x[is.nan(x)] <- 0;return(x)}
  tam=apply(tam,FUN=w, MARGIN=c(2))
  tamanhos.medios[,i]= as.data.frame(rowMeans(tam))
}

#calculate group size average standard deviation
sd.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(sd.medios) = mem_lengths

for (i in 1:length(mem_lengths))
{
  i_sd=0
  sd=0
  #create file list with selected memory lengths
  reg.exp=paste('i_var.*',mem_lengths[i],'.*', sep="")
  #temp=grep(pattern=reg.exp,files,value=TRUE)
  i_sd=list.files(pattern = reg.exp)
  #i_sd=list.files(pattern = temp)
  
  #read files
  tablesisd <- lapply(i_sd, read.table, header = FALSE)
  #calculates average group size for given memory length
  
  sd=as.data.frame(tablesisd)#dados brutos
  w=function(x){x[is.nan(x)] <- 0;return(x)}
  sd=apply(tam,FUN=w, MARGIN=c(2))
  sd.medios[,i]= as.data.frame(rowSds(sd))
}
#calculate group size average standard deviation
n.medios=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(n.medios) = mem_lengths

for (i in 1:length(mem_lengths))
{
  i_n=0
  n=0
  #create file list with selected memory lengths
  reg.exp=paste('i_num.*',mem_lengths[i],'.*', sep="")
  #temp=grep(pattern=reg.exp,files,value=TRUE)
  i_n=list.files(pattern = reg.exp)
  #i_n=list.files(pattern = temp)
  #read files
  tablesin <- lapply(i_n, read.table, header = FALSE)
  
  #calculates average group size for given memory length
  n=as.data.frame(tablesin)#dados brutos
  w=function(x){x[is.nan(x)] <- 0;return(x)}
  n=apply(tam,FUN=w, MARGIN=c(2))
  n.medios[,i]= as.data.frame(rowSds(n))
}


#plotting 
#plotar tamanhos médios
ltam=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(ltam) = mem_lengths

for (z in 1:ncol(tamanhos.medios))
{
  ltam[,z]=lowess(tamanhos.medios[,z])$y
}
x11()
plot(ltam[,1], type='l',xlab="tamanho médio dos clusters / memoria individual ", ylim=c(0,60))
for (k in 2:ncol(tamanhos.medios))
{
  lines(ltam[,k],col=k)
}

legend('topright', # places a legend at the appropriate place 
       names(tamanhos.medios), # puts text in the legend 
       
       lty=c(1,1), # gives the legend appropriate symbols (lines)
       
       #lwd=c(2.5,2.5),
       col=c(1:ncol(tamanhos.medios)) # gives the legend lines the correct color and width
)


#plotar SD médios
lsd=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(lsd) = mem_lengths

for (z in 1:ncol(sd.medios))
{
  lsd[,z]=lowess(sd.medios[,z])$y
}
x11()
plot(lsd[,1], type='l',xlab="sd médio dos tamanhos dos clusters  / memoria individual ", ylim=c(0,60))
for (k in 2:ncol(sd.medios))
{
  lines(lsd[,k],col=k)
}

legend('topright', # places a legend at the appropriate place 
       names(sd.medios), # puts text in the legend 
       
       lty=c(1,1), # gives the legend appropriate symbols (lines)
       
       #lwd=c(2.5,2.5),
       col=c(1:ncol(sd.medios)) # gives the legend lines the correct color and width
)


#plotar número médio de clusters
ln=as.data.frame(data.frame(matrix(NA, nrow = n_iter, ncol = length(mem_lengths))))
colnames(ln) = mem_lengths

for (z in 1:ncol(n.medios))
{
  ln[,z]=lowess(n.medios[,z])$y
}
x11()
plot(ln[,1], type='l',xlab="numero medio de clusters / memoria individual ",ylim=c(0,60))
for (k in 2:ncol(n.medios))
{
  lines(ln[,k], col=k)
}

legend('topright', # places a legend at the appropriate place 
       names(n.medios), # puts text in the legend 
       
       lty=c(1,1), # gives the legend appropriate symbols (lines)
       
       #lwd=c(2.5,2.5),
       col=c(1:ncol(n.medios)) # gives the legend lines the correct color and width
)
