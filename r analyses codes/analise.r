setwd("C:/Users/Vrios/Dropbox/Doutorado/codigo/socrats/Socrats_Doc_replicas")
library("matrixStats") 
##memoria individual
#tamanhos dos clustes
# list files with .txt extension
i_tam  <- list.files(pattern = 'i_tam_')
# read files into a list of tables
tablesitam <- lapply(i_tam, read.table, header = FALSE)
tam=as.data.frame(tablesitam)#dados brutos
max(tam)
min(tam)
tam.mean= as.data.frame(rowMeans(tam))#media dos tempos
#média das SDiancias dos tamanhos
i_SD <- list.files(pattern = 'i_var_')
tablesiSD <- lapply(i_SD, read.table, header = FALSE)
SD=as.data.frame(tablesiSD)#dados brutos
max(SD)
min(SD)
SD.mean= as.data.frame(rowMeans(SD))#media dos tempos
# número de clusters
i_num <- list.files(pattern = 'i_num_')
tablesinum <- lapply(i_num, read.table, header = FALSE)
num=as.data.frame(tablesinum)#dados brutos
max(num)
min(num)
num.mean= as.data.frame(rowMeans(num))#media dos tempos
num.sd = as.data.frame(rowSds(num))#SD dos tempos

x11()
plot(tam.mean[,1], type= "p", col="black",
     ylim=c(0,50),
     xlab="tempo /tamanho dos clusters/individual/ mem = 100",# ylab="media do tamanho médio do cluster"
)

points(SD.mean[,1],col="red")

x11()
plot(num.mean[,1], type= "l", col="black",
     ylim=c(0,50),
     xlab="tempo /numero de clusters/individual/mem=100",# ylab="media do tamanho médio do cluster"
)
#lines(num.mean[,1],col="black", lwd=1)
lines(num.sd[,1],col="red", lwd=1)


## memoria grupal
g_tam  <- list.files(pattern = 'g_tam_')
# read files into a list of tables
tablesitam <- lapply(g_tam, read.table, header = FALSE)
tam=as.data.frame(tablesitam)#dados brutos
max(tam)
min(tam)
tam.mean= as.data.frame(rowMeans(tam))#media dos tempos
#média das SDiancias dos tamanhos
g_SD <- list.files(pattern = 'g_var_')
tablesiSD <- lapply(g_SD, read.table, header = FALSE)
SD=as.data.frame(tablesiSD)#dados brutos
max(SD)
min(SD)
SD.mean= as.data.frame(rowMeans(SD))#media dos tempos
# número de clusters
g_num <- list.files(pattern = 'g_num_')
tablesinum <- lapply(g_num, read.table, header = FALSE)
num=as.data.frame(tablesinum)#dados brutos
max(num)
min(num)
num.mean= as.data.frame(rowMeans(num))#media dos tempos
num.sd = as.data.frame(rowSds(num))#SD dos tempos

x11()
plot(tam.mean[,1], type= "p", col="black",
     ylim=c(0,50),
     xlab="tempo /tamanho dos clusters/grupal/ mem = 600",# ylab="media do tamanho médio do cluster"
)

points(SD.mean[,1],col="red")

x11()
plot(num.mean[,1], type= "l", col="black",
     ylim=c(0,50),
     xlab="tempo /numero de clusters/grupal/mem=600",# ylab="media do tamanho médio do cluster"
)
#lines(num.mean[,1],col="black", lwd=1)
lines(num.sd[,1],col="red", lwd=1)

