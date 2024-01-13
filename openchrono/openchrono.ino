/**
 * OpenChrono Arduino Airsoft Chronograph
 * KnightsWhoSayNi0
 */

// pin mnemonics
const unsigned short SENS1 = 0,
                     SENS2 = 1,
                    LEDPIN = 13;
                    
float                  fps, // feet per second
                  bbWeight, // weight of bb's
                       mps, // meters per second
                    joules; // kinetic energy

void setup() 
{
  bbWeight = 0.20;
  
  pinMode(SENS1, INPUT);
  pinMode(SENS2, INPUT);
  pinMode(LEDPIN, OUTPUT);

  Serial.begin(9600);
  Serial.printf("%s\t%s\n", "fps", "joules");     // print headers
}

void loop() 
{
  if (digitalRead(SENS1))                         // execute on first sensor trip
  {                                               // get time difference
    unsigned long time1 = millis();
    
    while (!digitalRead(SENS2));

    unsigned long time2 = millis();
    unsigned long timediff = time2 - time1;

    // 166666.34 - 1 in
    fps = 83333.167 / timediff;                   // calc coeff for 2 in spacing
    if (fps>0 && fps<1000)                        // validation for correct math
    {
      mps = fps * 0.3048;                         // 1 fps = 0.3048 m/s
      joules = (0.5*bbWeight*(mps*mps))/1000;     // energy calculation 1/2mv^2
      Serial.printf("%.2f\t%.2f\n", fps, joules);
    } 
  }
}
