
# setwd("C:/Users/Vitor/Desktop/abacus 3")
# file = "C:/Users/Vitor/Desktop/abacus 3/g_finalSocEdges_tam_79_ags_1000_raio_3_eps_3_mPts_4_nTurnos_1000_tMem_10_MemMod_0.500000_rep_7.txt"

calc.mean.degree= function(file = f){

  library(igraph)
  g=as.data.frame(read.table(file, as.is=T, header= T, sep=";"))
  #g=subset(g, g$Weight !=0)
  # dado que as ids do r sempre começam com 1, é necessário importar os dados e somar 1 ao id
  g[,1]=g[,1]+1#corrigindo valores de id
  g[,2]=g[,2]+1#corrigindo valores de id
  g[,1]=as.character(g[,1])
  g[,2]=as.character(g[,2])

  #mantendo apenas as arestas com relações positivas
  g.subset= subset(g,g[,3]>0)
  graph.subset=graph.edgelist(as.matrix(g.subset[,1:2]), directed = F)
  E(graph.subset)$Weight=as.numeric(g.subset[,3])#adiciona os pesos das arestas
  simplify(graph.subset, remove.multiple = T,remove.loops = T, edge.attr.comb = "sum") #remove loops e arestas duplas
  mean(degree(graph.subset))


  return (mean(degree(graph.subset)))
}