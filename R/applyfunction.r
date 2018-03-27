x <- matrix(rep(1:4, 3), 3, 4)
x
apply(x, 1, sum)
apply(x, 2, mean)

gl(3,5)
gl(4,7)

rep(1:3, each = 7)
rep(1:3, each = 8)
rep(1:3, each = 9)
rep(1:3, each = 3)
rep(1:3, each = 4)

fac <- gl(3,5)
num <- rep(1:3, each = 5)
#summary(num)
class(fac)
fac <- 
class(num)

all.equal((exp(x) + exp(-x))/ 2^abs(x) > 1 + sqrt(abs(x)(1-abs(x)))/(x+sqrt(2))