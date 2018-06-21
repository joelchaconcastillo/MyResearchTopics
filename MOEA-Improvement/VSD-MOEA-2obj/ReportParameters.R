pdf(file= c("Parameters.pdf"))
D25 = read.table("D25")
names(D25) = c("Generacion", "Penalizados", "D teorico")
pairs(D25, main=c("D Inicial 0.25"))

D50 = read.table("D50")
names(D50) = c("Generacion", "Penalizados", "D teorico")
pairs(D50, main= c("D Inicial 0.50"))


D75 = read.table("D75")
names(D75) = c("Generacion", "Penalizados", "D teorico")
pairs(D75, main= c("D Inicial 0.75"))

D100 = read.table("D100")
names(D100) = c("Generacion", "Penalizados", "D teorico")
pairs(D100, main= c("D Inicial 1"))

dev.off()
