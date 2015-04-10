# reg.exp=paste(paste("_rede.*",sep=""))#for a given memory type
# 
# i_rede=list.files(pattern = reg.exp)
# #read files from list
# 
# mod.por.replica=0
# for (q in 1:length(i_rede))
# {
#   message(i_rede[q])
#   mod.por.replica[q]=calc_modularity(file=i_rede[q])
#   
# }
# unique(mod.por.replica)
# 

#http://estebanmoro.org/2012/11/temporal-networks-with-igraph-and-r-with-20-lines-of-code/
setwd("C:/Users/Vitor/Desktop/sim")
library(igraph)
file="C:/Users/Vitor/Desktop/sim/g_finalSpaceEdges_tam_23_ags_100_raio_2_eps_3_mPts_4_nTurnos_2000_tMem_5_rep_0.txt"

data=as.data.frame(read.table(file, as.is=T, header= T, sep=";"))
# dado que as ids do r sempre começam com 1, é necessário importar os dados e somar 1 ao id

data[,1]=data[,1]+1#corrigindo valores de id
data[,2]=data[,2]+1#corrigindo valores de id

#data=subset.data.frame(x = data, subset = data[,3]==1)

g=graph.edgelist(as.matrix(data[,c(1,2)]), directed = F) #cria o grafo

E(g)$time_initial=data[,3]#adiciona os tempos das arestas
#E(g)$Weight=data[,3]
#E(g)$Weight=ifelse(E(g)$Weight==1,1,0)
#E(g)$time_final=data[,5]#adiciona os tempos das arestas
V(g)

  
  
  #g=simplify(g,remove.multiple = F)
  #generate a cool palette for the graph
  YlOrBr <- c("#FFFFD4", "#FED98E", "#FE9929", "#D95F0E", "#993404")
YlOrBr.Lab <- colorRampPalette(YlOrBr, space = "Lab")
#colors for the nodes are chosen from the very beginning
vcolor <- rev(YlOrBr.Lab(vcount(g)))
ti=0
E(g)$Weight <- ifelse(E(g)$time_initial == ti,1,0)

layout.old <- layout.fruchterman.reingold(g,params=list(weights=E(g)$Weight))
#png(file="example%03d.png", width=1600,height=900)
nsteps <- max(E(g)$time_initial)
total_time <- max(E(g)$time_initial)
#x11()
#Time loop starts
z=0
w=0
ti=1
for(ti in 0:total_time)
{
  #define weight for edges present up to time ti.
  E(g)$Weight <- ifelse( ti == E(g)$time_initial, 1,0)
  #   E(g)$weight <- ifelse( ti == E(g)$time_initial & E(g)$time_final == ti, 1,0)
  #Edges with non-zero weight are in gray. The rest are transparent
  #    E(g)$color <- ifelse(E(g)$Weight != 0,"black",rgb(0,0,0,0))
  #Nodes with at least a non-zero weighted edge are in color. The rest are transparent
  #    V(g)$color <- vcolor
  #given the new weights, we update the layout a little bit
  #      layout.new <- layout.fruchterman.reingold(g,params=list(niter=10,start=layout.old,weights=E(g)$Weight,maxdelta=1))
  g.modulos=multilevel.community(g,weights = E(g)$Weight)
  z[ti]=max(g.modulos$modularity)
  q=clusters(g)
  w[ti]=q$no
  #plot the new graph
  
  #   plot(g
  #        ,layout=layout.old
  #        #,vertex.label=""
  #        ,vertex.size=3#+2*log(graph.strength(g))
  #        ,vertex.frame.color=V(g)$color
  #        ,edge.width=1.5
  #        ,asp=9/16
  #        ,margin=-0.15
  #   )
  #use the new layout in the next round
  #   layout.old <- layout.new 
  #   ti=ti+1
}
plot(z, ylim=c(0,1))
max(z)
min(z)
plot (w)
#dev.off()
