
calc_modularity=function(file = f)
{
  library(igraph)
  g=as.data.frame(read.table(file, as.is=T, header= T, sep=";"))
    # dado que as ids do r sempre começam com 1, é necessário importar os dados e somar 1 ao id
  g[,1]=g[,1]+1#corrigindo valores de id
  g[,2]=g[,2]+1#corrigindo valores de id
  graph=graph.edgelist(as.matrix(g[,1:2]), directed = F) #cria o grafo
  E(graph)$Weight=g[,3]#adiciona os pesos das arestas
  
  g.modulos=multilevel.community(graph)# calcula modularidade de louvain
  return (max(g.modulos$modularity))

}
