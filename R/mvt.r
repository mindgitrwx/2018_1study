library("Deriv")

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

