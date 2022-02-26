/*******************************************************************************/
/*     Réalisateur: MOHAMED M'MADI HASSANE                             */
/*    INGENIEUR EN CONCEPTION MECANIQUE ET INNOVATION */
/******************************************************************************/
Servo my_servo;
const int vert=13;
const int RECV_PIN = 7; // reception pin 8
IRrecv irrecv(RECV_PIN);
decode_results results;       
/********************************************************/ 
const int ldr = A3;
const int D0 = 5;

int seuil = 800;
void setup() {
     Serial.begin(9600); // initialisation liaison série
     irrecv.enableIRIn(); // initialisation reception Ir
    // irrecv.blink13(true); // la diode implémenté clignote a la reception
    lcd.init();
    lcd.backlight();
    lcd.setCursor(5,0);
    lcd.print("Welcome");
    lcd.setCursor(1,1);
    lcd.print("Smart Parking!");
    delay(3000);
    lcd.clear();
    pinMode(ldr, INPUT);
    pinMode(led_ouverture, OUTPUT);
    pinMode(led_fermeture, OUTPUT);
    pinMode(IR_IN, INPUT);
    pinMode(IR_Out,INPUT);
    digitalWrite(led_ouverture, LOW);
    digitalWrite(led_fermeture,LOW);
    my_servo.attach(2);
    my_servo.write(25);
    delay(1000);
    pinMode(vert,OUTPUT);
    digitalWrite(vert,LOW);
     my_servo.detach();
     /****************************************************************/
     
     } // fin de void setup
    
void loop() 
   {
    Rotary_parking();
    } //void loop 

 void Rotary_parking()
 {
  Portail_Systeme();
  Rotation_Systeme();
 allumage_auto();
 }

 void Portail_Systeme()
    {
        int val_in = analogRead(IR_IN);
        int val_out= analogRead(IR_Out);
        Serial.print("valeur entree = ");
        Serial.println(val_in);
        Serial.print("valeur sortie=  ");
        Serial.print(val_out);
               
//Entrée des Voitures 

  if(val_in >1016 && nbr_voiture <6 )
    {          
        my_servo.attach(2);
        digitalWrite(led_ouverture, HIGH);
        digitalWrite(led_fermeture,LOW);
        for( int pos=25;pos<130;pos++)
        {my_servo.write(pos);
        delay(40);
          }
          my_servo.detach();
        delay(5000);
        my_servo.attach(2);
        for (int pos=130;pos>25;pos--)
        {my_servo.write(pos);
        delay(40);  
        }
        nbr_voiture++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Place occupee");
        lcd.setCursor(0,1);
        lcd.print("est: ");
        lcd.print(nbr_voiture);
        val_in = analogRead(IR_IN);
        my_servo.detach();
    }                

 //Sortie des voitures
    
  else if (val_out >1015 && nbr_voiture>0)
   {    
         my_servo.attach(2);
        digitalWrite(led_ouverture, HIGH);
        digitalWrite(led_fermeture,LOW);
        for( int pos=25;pos<130;pos++)
        {my_servo.write(pos);
        delay(40);
          }
         my_servo.detach();
        delay(5000);
        my_servo.attach(2);
        for (int pos=130;pos>25;pos--)
        {my_servo.write(pos);
        delay(40);  
        }
        nbr_voiture--;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Place occupee");
        lcd.setCursor(0,1);
        lcd.print("est: ");
        lcd.print(nbr_voiture);
        val_out= analogRead(IR_Out);
        my_servo.detach();
   }
   else{// Ne fait rien du tout 
    }

    // Parking plein
   if(nbr_voiture==6)
     {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Le Parking est");
        lcd.setCursor(1,1);
        lcd.print("Plein");
        digitalWrite(led_fermeture,HIGH);
        digitalWrite(led_ouverture, LOW);
                    
     }
     // Parking vide     
     if(nbr_voiture==0)
     {

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Le Parking est");
      lcd.setCursor(1,1);
      lcd.print("Vide");      
      digitalWrite(led_fermeture,LOW);
      digitalWrite(led_ouverture, HIGH);
           
    }  
  } 
 void Rotation_Systeme()
    {
            int valeur=600;
          int etat_initial=0;
          int Angle_1=800, Angle_2=800, Angle_3=650, Angle_4=700, Angle_5=760, Angle_6=700;           
       if (irrecv.decode(&results)){   // si reception trame correcte
       // Serial.println(results.value);  // liaison pc
        irrecv.resume();               // resume Ir
        }


  switch (results.value) { // debut de la structure code sylver crest  kh 2311
  
    case 0xFF30CF:         // cas 1
    for(int pos=0; pos< Angle_1; pos++) 
    {
     int vitesse=map(valeur, 523, 1023, 5, 500);
    stepper.setSpeed(vitesse);
    stepper.step(1);
    }
    break;
    case 0xFF18E7:         // cas 2
    for(int pos=0;pos< Angle_2;pos++)
    {
    int  vitesse=map(valeur, 523, 1023, 5, 500);
    stepper.setSpeed(vitesse);
    stepper.step(1);
    }
    break;

    case 0xFF7A85:         // cas 3
   for(int pos=0;pos< Angle_3;pos++)
   {
    int vitesse=map(valeur, 523, 1023, 5, 500);
    stepper.setSpeed(vitesse);
    stepper.step(1);
   }
    break;
    case 0xFF10EF:         // cas 4
    for(int pos=0;pos< Angle_4;pos++)
    {
      int vitesse=map(valeur, 523, 1023, 5, 500);
      stepper.setSpeed(vitesse);
      stepper.step(1);
    }
    break;

    case 0xFF38C7:         // cas 5
    for(int pos=0;pos< Angle_5;pos++)
    {
      int vitesse=map(valeur, 523, 1023, 5, 500);
      stepper.setSpeed(vitesse);
      stepper.step(1);
    }
    break;

    case 0xFF5AA5:        // cas 6
    for(int pos=0;pos< Angle_6;pos++)
    {
      int vitesse=map(valeur, 523, 1023, 5, 500);
      stepper.setSpeed(vitesse);
      stepper.step(1);
    }
    break;

    case 0xFF42BD:       // cas 7
    digitalWrite(vert,HIGH);
    break;
    case 0xFF4AB5:       // cas 8
    digitalWrite(vert,LOW);
    break;
    case 0xFF52AD:       // cas 9
    my_servo.attach(2);
     for( int pos=25;pos<130;pos++)
     {
     my_servo.write(pos);
     delay(40);
     }
     my_servo.detach();
     delay(5000);
     my_servo.attach(2);
     for( int pos=130;pos>25;pos--)
     {
     my_servo.write(pos);
     delay(40);
     }
     my_servo.detach();
     break;
     case 0xFFFFFFFF: Serial.print(F(" "));
     break;  
     default: 
      Serial.print(F("   "));
      //lightRGB(0,0,0);
     
 }  // fin switch
   
   results.value= 0; // force l' arret du moteur en effaçant le code
   
      }

void allumage_auto()
{
  int etatldr = analogRead(ldr);
 Serial.println(etatldr);
  if (etatldr >= seuil)
  {
    my_servo.detach();
        digitalWrite(vert, HIGH);
        Serial.println( " led allumée ");
         
  }

  else
     {
        digitalWrite(vert, LOW);
        Serial.println( " led éteinte ");
     }
  
}
