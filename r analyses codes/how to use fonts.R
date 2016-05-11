#http://www.fromthebottomoftheheap.net/2013/09/09/preparing-figures-for-plos-one-with-r/

install.packages("extrafont")

library("extrafont")
font_import()
fonts()


loadfonts() ## for pdf()
## or
loadfonts(device = "postscript") ## for postscript()
pdf("myfig.pdf", height = 6, width = 6.83,
           family = "Arial", paper = "special", onefile = FALSE)
op <- par(mar = c(5, 4, 0.05, 0.05) + 0.1)
plot(dens, main = "", xlab = "Duration between eruptions (minutes)")
par(op)
dev.off()