//global vars
int programStatus = 0;


//config settings
void setup() {
  
  Serial.begin(9600);
  
  pinMode(3, INPUT); //pressostato
  pinMode(5, OUTPUT); //motor E
  pinMode(6, OUTPUT); //motor D
  pinMode(7, OUTPUT); //bomba flush
  pinMode(8, OUTPUT); //solenoide inundacao
  pinMode(11, OUTPUT); //speaker
  pinMode(12, OUTPUT); //led status - vermelho
  pinMode(13, OUTPUT); //led status - verde
  pinMode(A0, INPUT_PULLUP); //pullup do selector-key
 
  //zera todas saidas
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  
  delay(2000); //aguarda 3 segundos para inicio do programa, evitando repiques da chave seletora
}


//main loop
void loop() {
  
  if(programStatus == 0){
      
      int programSelectorValue = (analogRead(0) / 10); //leitura key-selector
      
      //MODO 1 - Super Molho
      if(programSelectorValue > 98 && programSelectorValue < 105){
          //sequencia 1
          Serial.println("MODO 1 :: SUPER MOLHO");
          //nunca usado
          Serial.println(programSelectorValue);
      }
      
      //MODO 2 - Lavagem Pesada
      else if(programSelectorValue > 90 && programSelectorValue < 98){
          Serial.println("MODO 2 :: LAVAGEM PESADA");
          Serial.println("### INICIANDO LAVAGEM ###");
          
          Serial.println(">> Inundando o tanque com agua ate o nivel selecionado...");
          tankFlood(); //inundando o tanque
          
          //bate a roupa durante 5 minutos, deixa de molho 5 minutos, e repete ate completar 1hr
          Serial.println(">> Batendo a roupa por 1hr com repouso de 5 min...");
          for(int i=0; i < 6; i++){
              
              wash(172, 500); //bate a roupa 172x
              
              //deixa a roupa de molho por 5 min
              for (int x=0; x < 300; x++){
                  digitalWrite(12, HIGH);
                  delay(500);
                  digitalWrite(12, LOW);
                  delay(500);
              }
          }
          
          Serial.println(">> Esvaziando o tanque ate o fim...");
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando durante 3 min...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> Inundando o tanque...");
          tankFlood(); //inundando o tanque
          
          Serial.println(">> Batendo a roupa por mais 5min...");
          wash(172, 500); //bate a roupa 172x
          
          Serial.println(">> Esvaziando o tanque ate o fim...");
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando por mais 3 minutos...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua da centrifugacao...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> LAVAGEM COMPLETA! =)");
      }
      
      //MODO 3 - Lavagem Normal
      else if(programSelectorValue > 80 && programSelectorValue < 90){
          Serial.println("MODO 3 :: LAVAGEM NORMAL");
          Serial.println("### INICIANDO LAVAGEM ###");
          
          Serial.println(">> Inundando o tanque com agua ate o nivel selecionado...");
          tankFlood(); //inundando o tanque
          
          //bate a roupa durante 5 minutos, deixa de molho 5 minutos, e repete ate completar 1hr
          Serial.println(">> Batendo a roupa por 30 minutos com repouso de 5 min...");
          for(int i=0; i < 3; i++){
              
              wash(172, 500); //bate a roupa 172x
              
              //deixa a roupa de molho por 5 min
              for (int x=0; x < 300; x++){
                  digitalWrite(12, HIGH);
                  delay(500);
                  digitalWrite(12, LOW);
                  delay(500);
              }
          }
          
          Serial.println(">> Esvaziando o tanque ate o fim...");
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando durante 3 min...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> Inundando o tanque...");
          tankFlood(); //inundando o tanque
          
          Serial.println(">> Batendo a roupa por mais 5min...");
          wash(172, 500); //bate a roupa 172x
          
          Serial.println(">> Esvaziando o tanque ate o fim...");
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando por mais 3 minutos...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua da centrifugacao...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> LAVAGEM COMPLETA! =)");
      }
      
      //MODO 4 - Lavagem Rapida
      else if(programSelectorValue > 68 && programSelectorValue < 80){
          Serial.println("MODO 4 :: LAVAGEM RAPIDA");
          //nunca usado
      }
      
      //MODO 5 - Lavagem Delicada
      else if(programSelectorValue > 51 && programSelectorValue < 68){
          Serial.println("MODO 5 :: LAVAGEM DELICADA");
          //nunca usado
      }
      
      //MODO 6 - ENXAGUE
      else if(programSelectorValue > 31 && programSelectorValue < 51){
          Serial.println("MODO 6 :: ENXAGUE");
          
          Serial.println(">> Esvaziando o tanque ate o fim...");
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando durante 3 min...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> Inundando o tanque...");
          tankFlood(); //inundando o tanque
          
          Serial.println(">> Batendo a roupa por mais 5min...");
          wash(172, 500); //bate a roupa 172x
          
          Serial.println(">> Esvaziando o tanque ate o fim...");
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando por mais 3 minutos...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua da centrifugacao...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> LAVAGEM COMPLETA! =)");
      }
      /*
      //MODO 7 - CENTRIFUGACAO
      else if(programSelectorValue > 9 && programSelectorValue < 51){
          Serial.println("MODO 7 :: CENTRIFUGACAO");
          Serial.println(">> Esvaziando o tanque ate o fim...");
          
          tankFlush(0); //esvazia o tanque
          
          Serial.println(">> Centrifugando durante 3 minutos...");
          tankCentrifuge(180); //centrifuga a parada
          
          Serial.println(">> Esvaziando o excesso de agua da centrifugacao (15s)...");
          tankFlush(15); //retira a agua restante da centrifugacao
          
          Serial.println(">> CENTRIFUGACAO COMPLETA! =)");
      }*/
      
      digitalWrite(13, HIGH); //acende o led status de verde pra indicar lavagem completa
      
      //endOfJobMusic(); //faz barulho
      
      programStatus = 1; //programa concluido!
  }
}


//lavacao
//shakes = batidas de roupa
//interval = intervalo entre batidas (ms)
void wash(int shakes, int interval){
  
  for (int i=0; i < shakes; i++){
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(13, HIGH); //ledstatus
      delay(500);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(13, LOW); //ledstatus
      delay(250); //repouso motor
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(13, HIGH); //ledstatus
      delay(500);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(13, LOW); //ledstatus
      delay(interval);
  }
  
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(13, LOW); //ledstatus
}

//centrifugar
//pin5 - gira motor direita
//*duration (segundos)
void tankCentrifuge(int duration){
  
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  
    int divider = (duration/10);
    
    for(int i=0; i < divider; i++){
      //liga por 6 seg
      digitalWrite(5, HIGH);
      
      for (int i=0; i < 6; i++){
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
      }
      
      //desliga 4s
      digitalWrite(5, LOW);
      
      for (int i=0; i < 4; i++){
        digitalWrite(12, HIGH);
        delay(500);
        digitalWrite(12, LOW);
        delay(500);
      }
    }
   
    digitalWrite(5, LOW);  //desliga motor
    digitalWrite(12, LOW); //desliga led status
}


//esvaziar o tanque
//pin7 - bomba de exaustao
//*duration (segundos)
void tankFlush(int duration){
    
    digitalWrite(7, HIGH);
    
    //se tem duration, usa ele como param
    if(duration > 0){
      for(int i=0; i < duration; i++){
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
      }
    }
    //se o pressostato esta travado, bombeia agua ate destravar
    else{
      //mantem ativo ate o pressostato gritar
      while(!digitalRead(3)){
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13, LOW);
          delay(500);
      }
      
      delay(3000); //da mais um dalayzinho basico pra esvaziar bem e nao deixar agua suja no fundo da maq
    }
   
    digitalWrite(7, LOW);
    digitalWrite(13, LOW);
}


//inundar o tanque
//pin8 - solenoide admissao
void tankFlood(){
  
  //mantem ativo ate o pressostato gritar
  while(digitalRead(3)){
      digitalWrite(8, HIGH); //flood valve
      digitalWrite(12, HIGH);//ledstatus
      delay(500);
      digitalWrite(12, LOW);
      delay(500);
  }
  
  digitalWrite(8, LOW); //flood valve
  digitalWrite(12, LOW); //ledstatus
}



//end of job music
void endOfJobMusic(){
  
  int speakerOut = 11;               
  byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
  int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
  byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";
  int count = 0;
  int count2 = 0;
  int count3 = 0;
  int MAX_COUNT = 24;
  int statePin = LOW;
  
  analogWrite(speakerOut, 0);     
  for (count = 0; count < MAX_COUNT; count++) {
    statePin = !statePin;
    
    for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) {
      for (count2=0;count2<8;count2++) {
        if (names[count2] == melody[count*2 + 1]) {       
          analogWrite(speakerOut,500);
          delayMicroseconds(tones[count2]);
          analogWrite(speakerOut, 0);
          delayMicroseconds(tones[count2]);
        } 
        if (melody[count*2 + 1] == 'p') {
          // make a pause of a certain size
          analogWrite(speakerOut, 0);
          delayMicroseconds(500);
        }
      }
    }
  }
}

