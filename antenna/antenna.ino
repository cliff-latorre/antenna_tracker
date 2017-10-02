  #include <Servo.h>
  #include <Stepper.h>
  
  const int stepsPerRevolution = 48;
  const float resolution  = 7.5;
  Stepper myStepper(stepsPerRevolution, 9, 10, 11, 12);
  
  
  Servo servo1;
  Servo servo2;
  
  int prev;
  int act;
  
  void setup()
  {
    Serial.begin(9600);
    servo1.attach(5);
    servo2.attach(4);
    myStepper.setSpeed(20);
    

    myStepper.step(step_degree(360));
    servo1.write(0);
    servo2.write(0);
    delay(500);
    servo1.write(90);
    servo2.write(90);
    delay(500);
    servo1.write(0);
    servo2.write(0);
    delay(500);
    servo1.write(45); 
    servo2.write(45);
    delay(500);
    Serial.println("Hello");
    
  }
  
  String command;
  
  void loop()
  {
    int azimut;
    int elevation ;

    if(Serial.available())
    {
      char c = Serial.read();
      
      if(c == '\n')
      {
        //Serial.println(command);
        azimut = parseAzimut(command);
        elevation = parseElevation(command);
        act = azimut - prev;
        
        //(Serial.println("actual=" + String(act) + " azimut= " + String(azimut) + " previo= " + String(prev));
        
        moveElevation(elevation);
        moveAzimut(azimut);
        movestepper(act);
  
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
    servo2.write(az);
    delay(200);  
  }
  
  void movestepper(int degree)
  {
    myStepper.step(step_degree(degree));
  }
  
  int step_degree(float desired_degree)
  {
    return (desired_degree/resolution);
  }
    
  
  
