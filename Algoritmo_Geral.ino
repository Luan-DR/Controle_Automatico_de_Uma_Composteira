//Algoritmo base, permitindo alterações nos valores de acordo com a preferencia do usuario
#include <OneWire.h>
#include <DallasTemperature.h>
const int oneWireBus = 32;     //Entrada dos dados de temperatura 
OneWire oneWire(oneWireBus);   //Confugurações da biblioteca
DallasTemperature sensors(&oneWire);  //Configurações da biblioteca

const int sensor = 33;  //Definindo a contante "sensor" como 33
const int posicao=34;   //Definindo a constante "posicao" como 34
int pos=0;  //Definindo uma vairiavel de nome "pos" com o valor inical 0
const int stepPin = 3; //Definindo a contante "stepPin" como 3

int temperatura(){ 
  sensors.requestTemperatures(); //Leitura do sensor de temperatura
  float temperatureC = sensors.getTempCByIndex(0);  //Intepretação dos dados 
  delay(500);
  return(temperatureC); //Retorno do  Valor temperatura
}

int umidade(){
  int umid=0; //Zerando o valor da variavel 
  int valor = analogRead(sensor); //Leitura de dados analógicos 
  map(valor,1600,4000,0,100); //Interpretação dos dados. Esta função pode ser calibrada
  delay(500);
  return(valor); //Retorno do Valor de umidade
}


void correcao_posicao(){
  while(pos != 1){  //Equanto os sensores não estiverem posicionados corretamente a composteira rotaciona
    digitalWrite(stepPin,HIGH); //Comando de pulso nivel alto
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW);  //Comando de pulso nivel baixo
    delayMicroseconds(500);
    pos=digitalRead(posicao);   //Leitura da posição dos sensores
  }
}

void rotacao(){
  for(int x = 0; x < 5000; x++) {  //Cada sequencia de pulso alto e pulso baixo, o motor realiza um passo 
    digitalWrite(stepPin,HIGH);   //Sequencia de pulso alto
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);    //Sequencia de pulso baixo
    delayMicroseconds(500);
    }
  delay(1000);
}

void setup() {
  pinMode(sensor, INPUT);   //Definindo o pino como entrada de dados do sensor de umidade
  sensors.begin();          //Proticolo do sensor de temperatura
  pinMode(posicao, INPUT);  //Defininddo o pino como entrada de dados do sensor de estado
  pinMode (stepPin, OUTPUT);//Definindo o pino como saída de dados para o driver do motor de passo
}

void loop() {
  pos=digitalRead(posicao); //Leitura do sensor de estado
  if(pos==0){
    correcao_posicao();   //Correção da posição caso os sensores não estejam no angulo correto
  }
  if(temperatura()>40 || umidade()>60){   //Leitura dos valores de umidade e temperatura
    rotacao();  //Rotação caso a umidade ou temperatura exceda o valor definido 
  }
}
