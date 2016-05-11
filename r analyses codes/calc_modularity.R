
#setwd("C:/Users/Vitor/Desktop/abacus 3")
#file = "C:/Users/Vitor/Desktop/abacus 3/g_finalSocEdges_tam_79_ags_1000_raio_3_eps_3_mPts_4_nTurnos_1000_tMem_10_MemMod_0.500000_rep_7.txt"
calc_modularity=function(file = f)
{
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
  simplify(graph.subset, remove.multiple = T,remove.loops = T, edge.attr.comb = "sum")
  graph.subset.modulos=cluster_louvain(graph.subset,weights = E(graph.subset)$Weight)
  q.subset=max(graph.subset.modulos$modularity)
  z.subset=length(graph.subset.modulos)
  p=sizes(graph.subset.modulos)
  sum(p)
  #    x11()
  #   # Plot the graph -- details in the "Drawing graphs" section of the igraph manual
  # plot(graph.subset, layout = layout.fruchterman.reingold,
  #      main = "subset",
  #      vertex.label=NA,
  #      vertex.color=membership(graph.subset.modulos),
  #      vertex.size = 1,
  #      edge.width=E(graph.subset)$Weight,
  #      edge.color=membership(graph.subset.modulos)
  #      )



  return (max(graph.subset.modulos$modularity))

}

#
#   #reescalonar pesos pra ficar entre 0 e 100
#   library (scales)
#   g.scaled=rescale(g[,3], to=c(0,10))
#   unique(g.scaled)
#
#   graph.scaled=graph.edgelist(as.matrix(g[,1:2]), directed = F)
#   E(graph.scaled)$Weight=as.numeric(g.scaled)#adiciona os pesos das arestas
#   simplify(graph.scaled, remove.multiple = T,remove.loops = T, edge.attr.comb = "sum")
#   graph.scaled.modulos=cluster_louvain(graph.scaled,weights = E(graph.scaled)$Weight)
#   q.scaled=max(graph.scaled.modulos$modularity)
#   z.scaled=length(graph.scaled.modulos)


#   #retirando arestas zero e reescalonando
#   g.remove=subset(g,g[,3]!=0)
#   rescale=rescale(g.remove[,3], to=c(0,10))
#   graph.remove.rescale= graph.edgelist(as.matrix(g.remove[,1:2]),directed=F)
#   E(graph.remove.rescale)$Weight=as.numeric(rescale)
#   simplify(graph.remove.rescale, remove.multiple = T,remove.loops = T, edge.attr.comb = "sum")
#   graph.remove.rescale.modulos=cluster_louvain(graph.remove.rescale,weights = E(graph.remove.rescale)$Weigth)
#     q.remove.rescale=max(graph.remove.rescale.modulos$modularity)
#     z.remove.rescale=length(graph.remove.rescale.modulos)
#   x11()
#   # Plot the graph -- details in the "Drawing graphs" section of the igraph manual
# plot(graph.remove.rescale, layout = layout.fruchterman.reingold,
#      main = "remove.rescale",
#      vertex.label="",
#      vertex.color="grey",
#      vertex.size = 1,
#      edge.width=E(graph.remove.rescale)$Weight,
#      edge.color=membership(graph.remove.rescale.modulos)
#      )


#     #cria o grafo
#     graph=graph.edgelist(as.matrix(g[,1:2]), directed = F)
#   E(graph)$Weight=as.numeric(g[,3])#adiciona os pesos das arestas
#   simplify(graph, remove.multiple = T,remove.loops = T, edge.attr.comb = "sum")
#
#
#   #g.modulos=multilevel.community(graph)# calcula modularidade de louvain
#   graph2=simplify(graph)
#   g.modulos=cluster_louvain(graph,weights = E(graph)$Weight)
#   q=max(g.modulos$modularity)
#   z=length(g.modulos)