withIR=read.csv(file = "C:/Users/Vitor/Desktop/novas sim plos/plots/ReplicatesModularity value with Individual Recognition , mem length = 20, mem modifier = 0.5.tiff.csv")
withIR=withIR[,2:4]
colnames(withIR)=c("IR0.05","IR0.10","IR0.5")
withoutIR=read.csv(file = "C:/Users/Vitor/Desktop/novas sim plos/plots/ReplicatesModularity value with Individual Recognition , mem length = 0, mem modifier = 0.5.tiff.csv")
withoutIR=withoutIR[,2:4]
colnames(withoutIR)=c("N0.05","N0.10","N0.5")

dados=matrix(NA, nrow = 6*length(withIR[,1]), ncol = 2)
ir1=withIR[,1]
ir2=withIR[,2]
ir3=withIR[,3]

no1=withoutIR[,1]
no2=withoutIR[,2]
no3=withoutIR[,3]

dados = data.frame(
  c(rep(x = "IR0.05",times=length(withIR[,1])),
    rep(x = "IR0.10",times=length(withIR[,1])),
    rep(x = "IR0.5",times=length(withIR[,1])),
    rep(x = "N0.05",times=length(withIR[,1])),
    rep(x = "N0.10",times=length(withIR[,1])),
    rep(x = "N0.5",times=length(withIR[,1]))
  ),
  c(ir1,ir2,ir3,no1,no2,no3)
)
colnames(dados)= c("x","y")

teste=aov(formula = dados$y~dados$x)
 par(mfrow=c(1,2))          # set graphics window to plot side-by-side
 plot(teste, 1)           # graphical test of homogeneity
 plot(teste, 2)
summary(teste)
TukeyHSD(teste)

teste2= kruskal.test(dados$y~dados$x)
teste2$p.value


library(FSA)
dunnTest(dados$y~dados$x)

