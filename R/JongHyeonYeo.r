library("Deriv")
library(pracma)

# 1-(1)
f1 <- function(x){
   x * log(x)
}
df<-(Deriv(f1 ,"x"))
c <- (abs(df(seq(1, 100,  0.0001))
          -((f1(100)-f1(1))/(100 - 1)))
           < 10^-5)
length(c[c==TRUE])
#answer : 8


# 1-(2)
f2 <- function(x){
   x^2 * sin(1/x) 
}
df<-(Deriv(f2 ,"x"))
c <- (abs(df(seq(1, 100,  0.0001))
          -((f2(100)-f2(1))/(100 - 1)))
           < 10^-5)
length(c[c==TRUE])
# answer: 648

# 1-(3)
f3 <- function(x){
    (1 + x)^(1/x)
}
df<-(Deriv(f3 ,"x"))
c <- (abs(df(seq(1, 100,  0.0001))
          -((f3(100)-f3(1))/(100 - 1)))
           < 10^-5)
length(c[c==TRUE])
# answer: 192

# 2-(1) 
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


# 3-(1)
v <- exp(1-log(tan(1/exp(2))))
f1 <- function(x,v){
    ((gamma((v+1)/2) / gamma(v/2)) * (1/sqrt(v * pi))) *
    ((1 + x^2/v) ^ -(v+1)/2)
}

delta <- (sqrt(8)-(-sqrt(7)))/111
sum(pmin(
         (f1(seq(0,110) * delta, v) + f1(seq(1,111) * delta,v))/2,
          f1(((seq(0,110) + seq(1,111))/2)* delta, v) 
    )) * delta
#answer: 0.1734362

# 3-(2)
v1 <- exp(sqrt(pi))
v2 <- sqrt(exp((pi)))
f2 <- function(x,v1,v2){
    (gamma(((v1 + v2)/2) / (gamma(v1/2)) * gamma(v2/2))) *
    ((v1/v2) ^ (v1/2)) *
    ((x^(v1-2)/2) / (1 + (v1/v2) * x) ^ (v1+v2)/2)
}
delta <- (3-10^-5)/111
sum(pmin(
         (f2(seq(0,110) * delta, v1,v2) + f2(seq(1,111) * delta,v1,v2))/2,
          f2(((seq(0,110) + seq(1,111))/2)* delta, v1,v2) 
    )) * delta
#answer:0.0005035072
