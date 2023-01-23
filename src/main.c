#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <uncertain.h>


/**
 *	@brief Recives value and returns normal distribution of values in ranges [val-x%:val+x%]
 *         
 *	@param value           : Exact value
 *	@param percentage      : Percentage in error 
 *	@return distribution   : Normal distribution of the given value +-x%
 */
static double uniformDistWithPercentage(double value , double percentage) {
    double errorval = value*percentage;
    double val = libUncertainDoubleUniformDist((value-errorval), (value+errorval));
    return val;
}


/**
 *	@brief Hypsometric Formula (relevant for <11km).
 *         Calculates actual pressure based on temperature and altitude.
 *
 *	@param temp         : Temperature in Celcius.
 *	@param altitude     : Altitude in meters at the time of measurement
 *	@return Ptotal      : Total pressure in Pascal
 */
static double calculateActualPressure(double temp , double altitude) {
    double Ptotal = 101325 * pow((1-((0.0065*altitude)/(temp+273.15+(0.0065*altitude)))),5.257);
	printf("Actual Pressure\t= %.3E \tPascal\n", Ptotal);
    return Ptotal;
}


/**
 *	@brief Calculates fluid density based on temperature, humidity and altitude.
 *
 *	@param temp         : Temperature in Celcius.
 *	@param RH           : Relative humidity (expressed as a decimal value)
 *	@param altitude     : Altitude in meters at the time of measurement
 *	@return rho         : Fluid density in kg/m3
 */
static double calculateRho(double temp ,double RH,double altitude) {
    // Tetens' Formula
    double c0 = 6.1078 , c1 = 7.5 , c2 = 237.3;
    //Es = saturation vapor pressure (Pascal)
    double Es =  (c0 * pow(10,(c1*temp)/(c2+temp))) *100.0;
	printf("Es\t\t= %.4E \tPascal\n", Es);

    //Pv = pressure of water vapor (partial pressure) 
    double Pv = RH * Es;
	printf("Pv\t\t= %.3E \tPascal\n", Pv);

    // Calculate total pressure based on altitude relevant <11km (Hypsometric Formula)
    double Ptotal = calculateActualPressure(temp,altitude);

    // Gas constant for dry air, J/(kg*degK) = 287.05 = R/Md
    double Rd = 287.05;

    double rho = (Ptotal/((temp+273.15)* Rd)) * (1-((0.378*Pv)/Ptotal));
    printf("Rho\t\t= %.4E \tkg/m3\n", rho);
    return rho;
}

/**
 *	@brief Uses pitot tube values to calculate velocity of fluid.
 *         v = sqrt(2 * ( DeltaPressure / Rho ) )        
 *	@param Pd           : Delta pressure in Pascal
 *  @param Rho          : Fluid density in kg/m3
 *	@return velocity    : Velocity of fluid in m/s
 */
static double calculateVelocity(double Pd, double Rho) {
    double velocity = sqrt(2 * Pd/Rho); 
    printf("Velocity\t= %.4E \tm/s\n", velocity);
    return velocity; 
}

/**
 *	@brief Calculates and prints Lift force based on density velocity and lift coeff.
 *         Uses modern lift equation: L = .5 * Cl * r * V^2 * A
 *	@param CI           : Lift coefficient
 *	@param rho          : Fluid density in kg/m3
 *	@param velocity     : Fluid velocity
 *	@param area         : Wing area in m2
 *	@return liftForce   : Lift force in N
 */
static double calculateLiftForce(double CI ,double rho , double velocity, double area) {
    double liftForce = CI * rho * pow(velocity,2) *0.5 * area; 
    return liftForce;
}




struct Inputs{
    float deltaPressure;
    float deltaPressureError;
    float temperature;
    float temperatureError;
    float altitude;
    float altitudeError;
    float airfoilArea;
    float liftCoefficient;
    float relativeHumidity;
    float relativeHumidityError;
};


static struct Inputs* GetInputs(){
    struct Inputs *in = malloc(sizeof(struct Inputs));
	// Default values
    in->altitude = 1000; 
    in->altitudeError = 0.01;
    in->temperature = 15;
    in->temperatureError = 0.01;
    in->deltaPressure = 1000;
    in->deltaPressureError = 0.05;
    in->airfoilArea = 37;
    in->liftCoefficient = 0.1;
    in->relativeHumidity = 0.7;
    in->relativeHumidityError = 0.01;

    return in;
}

int main(int argc, char *argv[]){

	double CI,Area,Altitude,RH,Temp,DeltaPressure,Rho,Velocity,LiftForce;
    struct Inputs* in =  GetInputs();

    Altitude = uniformDistWithPercentage(in->altitude,in->altitudeError);
    RH = uniformDistWithPercentage(in->relativeHumidity,in->relativeHumidityError);
    Temp = uniformDistWithPercentage(in->temperature,in->temperatureError);
    DeltaPressure = uniformDistWithPercentage(in->deltaPressure,in->deltaPressureError);
    CI= in->liftCoefficient;
    Area = in->airfoilArea;

    Rho = calculateRho(Temp,RH,Altitude);
    Velocity = calculateVelocity(DeltaPressure,Rho);
    LiftForce = calculateLiftForce(CI,Rho,Velocity,Area);

    printf("Lift Force\t= %.4E \tN\n", LiftForce);
	return 0;
    
}