#include <ArduinoRobot.h>

boolean deplacement = false;
int relevePot = 0;

void setup() {
  Robot.begin();                              //init du robot beep-boop il est handicapé
  Robot.beginTFT();                           //init de l'afficheur
  Robot.beginSD();                            //init port SD robot
  Robot.drawBMP("albator2.bmp", 0, 0);        //affichage Albator pendant 5 secondes
  delay(5000);
  Robot.clearScreen();                        //effacement de l'écran
}

void loop() {
  if(deplacement == false){                   //phase préparation au déplacement
    Robot.motorsStop();                       //arrêt total du robot
    relevePot = map(Robot.knobRead(),0,1023,-255,255);
    Robot.stroke(0, 0, 0);
    Robot.text(relevePot, 0, 0);              //affichage du relevé du potar
    delay(32);
    Robot.stroke(255, 255, 255);              //réécriture du relevé dans la couleur opposée 
    Robot.text(relevePot, 0, 0);
    if(Robot.keyboardRead() == BUTTON_MIDDLE){
      deplacement = true;                     //sortie de la phase de préparation
      Robot.drawBMP("albator.bmp", 0, 0);
    }
  }else{                                      //phase de déplacement du robot handicapé
    Robot.motorsWrite(relevePot,relevePot);
    if(Robot.keyboardRead() == BUTTON_MIDDLE){
      delay(10);                              //p'tit delay au kazoo
      deplacement = false;                    //sortie de la phase de déplacement
      Robot.clearScreen();                    //effacement de l'écran
    }
  }
}
