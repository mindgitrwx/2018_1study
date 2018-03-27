#Todo - constants to variables
# 2-(1) 
library(pracma)
seq(5,0)
f <- function(x){
    log(exp(x)^-1)
}
g <- log(1+sin(exp(1)^2))

coefficients <- taylor(f, x0 = sqrt(5), n = 5)
R5 <- f(g) - sum(coefficients * g^(seq(5,0)))
R5
# answer : 6.640322e-06

# 2-(2)  
coefficients <- taylor(f, x0 = sqrt(5), n = 3)
(abs(f(2) - sum(coefficients * 2^(seq(3,0)))) < 10^-6)

coefficients <- taylor(f, x0 = sqrt(5), n = 4)
(abs(f(2) - sum(coefficients * 2^(seq(4,0)))) < 10^-6)
# answer : 4

