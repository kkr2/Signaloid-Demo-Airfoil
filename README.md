[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/kkr2/Signaloid-Demo-Airfoil#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.svg#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/kkr2/#gh-light-mode-only)

# Model of lift generation of an airfoil
This is a small demo that models the realtion between the `geometry` of an airfoil and external measurements like `temperature`, `air density`, `altitude` and `pressure`, with `lift force`. For the external measurements like `pressure`,  `altitude` and `temperature` we have an accompanying error percentage that represent the mesurement error that is calculated as normal distribution with ranges `value+-error%`. 
## Inputs
The default inputs  are:
-	`liftCoefficient`:      0.1
-	`airfoilArea`:          37 M2
-	`relativeHumidity`:     0.7 RH
-	`relativeHumidityError`:0.01 (1%)
-	`deltaPressure`:        1000 Pascal
-	`deltaPressureError`:   0.05 (5%)
-	`temperature`:          15 C
-	`temperatureError`:     0.01 (1%)
-	`altitude`:             1000 Meters
-	`altitudeError`:        0.01 (1%)

## Outputs

### Es Readings:
<img width="400" alt="Es" src="https://user-images.githubusercontent.com/43975216/214069548-3698c9ed-2247-4c08-9d8a-f8addc0081cf.png">

### Pv Readings:
<img width="400" alt="Pv" src="https://user-images.githubusercontent.com/43975216/214069710-6ad6766f-5f83-46e7-a0e1-efd66478a942.png">

### Actual presure Readings:
<img width="400" alt="AP" src="https://user-images.githubusercontent.com/43975216/214069898-3f5734b6-add0-4815-b019-c40fe40046e0.png">

### Rho Readings:
<img width="400" alt="Rho" src="https://user-images.githubusercontent.com/43975216/214070155-972378f6-48d3-4940-9aa1-296950a8335a.png">

### Velocity Readings:
<img width="400" alt="V" src="https://user-images.githubusercontent.com/43975216/214070302-9bf4b8e3-7308-475b-bae4-37927c2f9109.png">


### Lift force Readings:
<img width="400" alt="Lift" src="https://user-images.githubusercontent.com/43975216/214070408-bc5abbf1-cf03-4db1-9f79-b08866dddc15.png">


## Calculations

1) To calculate air density
- Air density (ref 2) calculates density based on `total pressure`,  `pressure of water vapor`, `temperature` and `gas constant` for dry air
- Tetens formula (ref 3) calculates saturation pressure of water vapor based on `temperature`
- Hypsometric Formula (ref 4) calculates absolute air pressure based on `altitude` and `temperature`

2) To calculate velocity
- Pitot tube (ref 5) calculations for velocity based on air `density` and `pressure` difference 

3) To calculate lift force
- Lift equation (ref 1) calculates lift force as a function of `lift coefficient`,`area` of airfoil, air `density` and `velocity`

## Repository Structure
```
.
├── README.md
└── src
    ├── config.mk
    └── main.c
```

## References:

1. [Nasa lift equation](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/lift-equation)
2. [Evaporation into the Atmosphere, Wilfried Brutsaert, p37](https://wahiduddin.net/calc/refs/brutsaert-37-38.pdf)
3. Tetens, O. 1930. Über einige meteorologische Begriffe. Z. Geophys 6: 297-309.
4. Wallace, J. M., and P. V. Hobbs, 1977: Atmospheric Science: An Introductory Survey. Academic Press, 55–57. 
5. [Nasa pitot tube (Bernoulli's equation)](https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/pitot.html)