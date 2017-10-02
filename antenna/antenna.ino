  #include <Servo.h>
  #include <Stepper.h>
  
  
  const int stepsPerRevolution = 48;//set number of stepps per revolution
  const float resolution  = 7.5;//set the accuracy (360/48)
  Stepper myStepper(stepsPerRevolution, 9, 10, 11, 12); //digital pins for motor stepper
  Servo servo1; //instance of class Servo for use 
  
  int prev;
  int act;
  String command;
  int azimut;
  int elevation ;
  
  void setup()
  {
    Serial.begin(9600); //set serila baud rate
    servo1.attach(5); //pin for use servo
    //servo2.attach(4);
    myStepper.setSpeed(20); //number of rpm 

    myStepper.step(step_degree(0));
    servo1.write(0);
    delay(500);
    servo1.write(45);
    myStepper.step(step_degree(45));
    delay(500);
    servo1.write(90);
    myStepper.step(step_degree(90));
    delay(500);
    servo1.write(0); 
    myStepper.step(step_degree(0));
    delay(500);
    Serial.println("Init Serial comunitation");    
  }
  
  void loop()
  {


    if(Serial.available()) 
    {
      char c = Serial.read();
      
      if(c == '\n') //detect if a scape character 
      {
        //Serial.println("Incoming message: [" + command + "]");
        azimut = parseAzimut(command);
        elevation = parseElevation(command);
        act = azimut - prev;        
        moveElevation(elevation); //move the servo motor
        moveAzimut(act); //move the stepper motor
  
        Serial.print("AZ= " + String(azimut));
        Serial.print(" ");
        Serial.print("EL= " + String(elevation));
        Serial.print('\n');
        prev = azimut;
        command = "";
      }
      else
      {
        command += c;
      }      
    }

  }
    
  int parseElevation(String com)
  {    
    String elevation = "";
    int el = 0; 
    int spaceIndex = com.indexOf(' ');
    int secondSpaceIndex = com.indexOf(' ', spaceIndex + 1);
    elevation = com.substring(spaceIndex +3, secondSpaceIndex);
    el = elevation.toInt();
    return el;
  }
  
  int parseAzimut(String com)
  {
    String azimut = "";
    int az = 0;  
    int spaceIndex = com.indexOf(' ');
    int secondSpaceIndex = com.indexOf(' ', spaceIndex + 1);
    azimut = com.substring(3, spaceIndex);
    az = azimut.toInt();
    return az;
  }
  
  void moveElevation(int el)
  {
    servo1.write(el);
    delay(200);  
  }
  
  void moveAzimut(int az)
  {
    myStepper.step(step_degree(az));
  }
  
  int step_degree(float desired_degree)
  {
    return (desired_degree/resolution);
  }
    
  
  
