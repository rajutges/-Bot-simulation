#include <webots/DistanceSensor.hpp>
#include<webots/GPS.hpp>

#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#define TIME_STEP 64
using namespace webots;



#define LFM_FORWARD_SPEED 3
#define LFM_K_GS_SPEED 0.008

// int cx,cy = 0;
// int dx ,dy = 5;
// #include <iostream>
// #include <ctime>

using namespace std;

// void slep(float seconds){
    // clock_t startClock = clock();
    // float secondsAhead = seconds * CLOCKS_PER_SEC;
    // do nothing until the elapsed time has passed.
    // while(clock() < startClock+secondsAhead);
    // return;
// }





int main(int argc, char **argv) {

  Robot *robot = new Robot();
  DistanceSensor *ds[3];
  char dsNames[3][10] = {"ds_right", "ds_left","ds_front"};
  for (int i = 0; i < 3; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  DistanceSensor *Ir[5];
  char IrNames[5][10] = {"GS_RIGHT", "GS_LEFT","GS_CENTER","ir_left","ir_right"};
  for (int i = 0; i < 5; i++) {
    Ir[i] = robot->getDistanceSensor(IrNames[i]);
    Ir[i]->enable(TIME_STEP);
  }

      GPS *gp;
  gp=robot->getGPS("global");
  gp->enable(TIME_STEP);
  
  
  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
  }

  while (robot->step(TIME_STEP) != -1) {
  
    
    double leftSpeed;
    double rightSpeed;
   
    
    if(gp->getValues()[0]<-2.1 && gp->getValues()[0]>-2.2){
     
     if(gp->getValues()[2]<-1.48741){
     std::cout<<"##jvjcddjcvsdjvj###"<<std::endl;
    
     system("PAUSE");
     delete robot;
     exit(0);
    
    
     return 0;
  
    }}
     else{
    
      
      if((Ir[4]->getValue() > 350) || (Ir[3]->getValue() > 350 )){//detect intersection
         if(ds[2]->getValue()>100){  //noobstacles in front
            int DeltaS = Ir[0]->getValue() - Ir[1]->getValue();
            leftSpeed = LFM_FORWARD_SPEED - LFM_K_GS_SPEED * DeltaS;
            rightSpeed = LFM_FORWARD_SPEED + LFM_K_GS_SPEED * DeltaS;
               wheels[0]->setVelocity(leftSpeed);
               wheels[1]->setVelocity(rightSpeed);
               wheels[2]->setVelocity(leftSpeed);
               wheels[3]->setVelocity(rightSpeed);   
              }
              else if((ds[2]->getValue()<90) && ds[0]->getValue()<90){
               leftSpeed = 5;//turnright
               rightSpeed = 0;
               wheels[0]->setVelocity(leftSpeed);
               wheels[1]->setVelocity(rightSpeed);
               wheels[2]->setVelocity(leftSpeed);
               wheels[3]->setVelocity(rightSpeed);
              
              }
              else if((ds[2]->getValue()<90) && ds[1]->getValue()<90){
               leftSpeed = 0;//turnleft
               rightSpeed = 5;
               wheels[0]->setVelocity(leftSpeed);
               wheels[1]->setVelocity(rightSpeed);
               wheels[2]->setVelocity(leftSpeed);
               wheels[3]->setVelocity(rightSpeed);
              
              }
              else if((ds[2]->getValue()<50)){
               leftSpeed = 0;
               rightSpeed = 5;
               wheels[0]->setVelocity(leftSpeed);
               wheels[1]->setVelocity(rightSpeed);
               wheels[2]->setVelocity(leftSpeed);
               wheels[3]->setVelocity(rightSpeed);
              
              }
      
      }
      else if((Ir[4]->getValue() < 350) && (Ir[3]->getValue() < 350 ) && (Ir[0]->getValue() < 350) && (Ir[1]->getValue() < 350 ) &&(Ir[2]->getValue() < 350 )){
               leftSpeed = -5;//turnleft
               rightSpeed = 5;
               wheels[0]->setVelocity(leftSpeed);
               wheels[1]->setVelocity(rightSpeed);
               wheels[2]->setVelocity(leftSpeed);
               wheels[3]->setVelocity(rightSpeed);
      }
      
    
   
    else{
    int DeltaS = Ir[0]->getValue() - Ir[1]->getValue();
    leftSpeed = (LFM_FORWARD_SPEED - LFM_K_GS_SPEED * DeltaS);
    rightSpeed = (LFM_FORWARD_SPEED + LFM_K_GS_SPEED * DeltaS);
               wheels[0]->setVelocity(leftSpeed);
               wheels[1]->setVelocity(rightSpeed);
               wheels[2]->setVelocity(leftSpeed);
               wheels[3]->setVelocity(rightSpeed);
    }
    
    
    
    // if(Ir[2]->getValue() <400 && Ir[3]->getValue() <400){
  
    // leftSpeed = 1;
    // rightSpeed = -1;
    // }
    // 
      // if(Ir[3]->getValue() >400){
  
    // leftSpeed = 5;
    // rightSpeed = 5;
    // }
    
    
    // wheels[0]->setVelocity(leftSpeed);
    // wheels[1]->setVelocity(rightSpeed);
    // wheels[2]->setVelocity(leftSpeed);
    // wheels[3]->setVelocity(rightSpeed);
     
   
     // if(ps->getValue()>=2521){
  // leftSpeed =0;
    // rightSpeed = 0;
   // wheels[0]->setVelocity(leftSpeed);
   // wheels[1]->setVelocity(rightSpeed);
   // wheels[2]->setVelocity(leftSpeed);
   // wheels[3]->setVelocity(rightSpeed);}

  
 }}

  delete robot;
  return 0;  // EXIT_SUCCESS
}