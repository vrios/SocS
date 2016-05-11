# calc_modularity=function(file = f)
#{
library(igraph)
setwd("C:/Users/Vitor/Desktop/abacus 3")

file  <- "C:/Users/Vitor/Desktop/abacus 3/g_finalSocEdges_tam_79_ags_1000_raio_3_eps_3_mPts_4_nTurnos_1000_tMem_30_MemMod_0.100000_rep_3.txt"

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


# Plot the graph -- details in the "Drawing graphs" section of the igraph manual
colors = rainbow(length(graph.subset.modulos))
#x11()
set.seed(4)
#pdf("SocialNetworkExample.pdf", height = 6, width = 6.83,family = "Arial", paper = "special", onefile = FALSE)
#op <- par(mar = c(5, 4, 0.05, 0.05) + 0.1)
png("SocialNetworkExample.png",width = 900,height = 900)
plot(graph.subset,
     #layout = layout.auto(graph.subset),
     layout= layout_nicely(graph=graph.subset),
     #layout =layout_with_lgl(graph=graph.subset),
     #layout =layout_with_drl(graph=graph.subset),
     #layout =layout_on_sphere(graph=graph.subset) ,
     #layout =layout.fruchterman.reingold(graph=graph.subset,weights=E(graph.subset)$Weight, niter=1000),
     #main = "Social Network",
     vertex.label=NA,
     vertex.color=colors[membership(graph.subset.modulos)],
     vertex.size = 5,
     #edge.width= E(graph.subset)$Weight,
     #edge.curved=FALSE,
     #edge.color=c("black","lightgray")[crossing(graph.subset.modulos, graph.subset)+1]
     #family = "Arial"
     # edge.color=membership(graph.subset.modulos)
    # edge.color=colors
)
#par(op)
dev.off()

#   return (max(graph.subset.modulos$modularity))
#
#}
# layouts <- grep("^layout\\.", ls("package:igraph"), value=TRUE)
# # Remove layouts that do not apply to our graph.
# layouts <- layouts[!grepl("bipartite|merge|norm|sugiyama|harel", layouts)]
# x11()
# par(mfrow=c(5,4))
#
# for (layout in layouts) {
# #
#   print(layout)
#   l <- do.call(layout, list(graph.subset))
#   plot(
#     graph.subset, edge.arrow.mode=0, layout=l, main=layout,
#     vertex.label=NA,
#      vertex.color=colors[membership(graph.subset.modulos)],
#      vertex.size = 5,
#      edge.width= E(graph.subset)$Weight/10,
#      edge.curved=FALSE,
#      edge.color="lightgray"
#     ) }
#
# dev.off()
