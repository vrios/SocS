n=500
tam=100
pts=cria.pontos2(n,tam)
# x11()
# plot(pts)
dists=toroidal.distance(object=pts,tam)
dists.sort=matrix(NA, nrow=n,ncol=n)
  for (i in 1:length(dists[1,]))
  {
    dists.sort[,i]=sort(dists[i,])
  }
dists.sort
dists.sort[4,]
k.dist=sort(dists.sort[4,],decreasing=TRUE)
#k.dist
x11()
plot(k.dist, type='p'
     #,pch=24
     )
#dev.capabilities(what='locator')
identify(k.dist)
locator(k.dist, y=)