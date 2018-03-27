#3-(1)
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

#3-(2)
v1 <- exp(sqrt(pi))
v2 <- sqrt(exp((pi)))
f2 <- function(x,v1,v2){
    (gamma(((v1 + v2)/2) / (gamma(v1/2)) * gamma(v2/2))) *
    ((v1/v2) ^ v1/2) *
    ((x^(v1-2)/2) / (1 + (v1/v2) * x) ^ (v1+v2)/2)
}
delta <- (3-10^-5)/111
sum(pmin(
         (f2(seq(0,110) * delta, v1,v2) + f2(seq(1,111) * delta,v1,v2))/2,
          f2(((seq(0,110) + seq(1,111))/2)* delta, v1,v2) 
    )) * delta
#answer:0.0005035072
