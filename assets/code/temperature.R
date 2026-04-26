library(ggplot2)
library(MASS)
library(car)
library(DAAG)

"Lets Try ANCOVA"

temp.lm<-lm(temp~time+site,data = temp)

Anova(temp.lm)

ggplot(temp)+geom_smooth(aes(x=time,y=temp,fill=site),method="lm")+
  theme_classic()
