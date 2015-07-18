n=200
tam=10

cria.pontos = function (n,tam)
{
  coords=matrix(c(1:n,tam*runif(n),tam*runif(n)), nrow=n,ncol=3)
  coords
  return(coords)
}
cria.pontos2 = function (n,tam)
{
  coords=matrix(c(tam*runif(n),tam*runif(n)), nrow=n,ncol=2)
  coords
  return(coords)
}
w=cria.pontos(n,tam)
X=cria.pontos2(n,tam)
plot(X)
