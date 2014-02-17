setwd("C:/Users/Vrios/Dropbox/Doutorado/codigo/testes de clusters_b/Socrats_Doc_replicas")
# list files with .txt extension
filesg  <- list.files(pattern = 'g_')

# read files into a list of tables
tablesg <- lapply(filesg, read.table, header = FALSE)

D1=as.data.frame(tablesg)#dados brutos
max(D1)
min(D1)
D1.mean= as.data.frame(rowMeans(D1))#media dos tempos
D1.var=as.data.frame(apply(D1,MARGIN=1,var))
dm=data.frame(1:500,D1.mean)
dv=data.frame(1:500, D1.var)
x11()
plot(dm, type="p", 
     ylim=c(0,200),
     xlab="tempo /memoria grupal / n 150",ylab="media do tamanho médio do cluster")
#lines(dv,col="red")

filesi  <- list.files(pattern = 'i_')

# read files into a list of tables
tablesi <- lapply(filesi, read.table, header = FALSE)

D2=as.data.frame(tablesi)#dados brutos
max(D2)
min(D2)
D2.mean= as.data.frame(rowMeans(D2))#media dos tempos
D2.var=as.data.frame(apply(D2,MARGIN=1,var))
dm2=data.frame(1:500,D2.mean)
dv2=data.frame(1:500, D2.var)
x11()
plot(dm2, type="p", 
     ylim=c(0,200),
     xlab="tempo / individual / n 150",ylab="media do tamanho médio do cluster")
#lines(dv2,col="red")

