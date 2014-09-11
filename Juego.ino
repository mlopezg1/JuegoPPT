//Rock, paper, sccisors, lizard, spock

#include "EEPROM.h"

const char* selection[] = {"piedra","papel","tijera","largartija","Spock"};

class pc
{
	public
	pc();  //debe llamarse igual que la clase
	uint8_t victorias;
	uint8_t perdidas;
	uint8_t jugar();
	String estado();
	float razon();
};

pc::pc(){
	victorias=0;
	perdidas=0;
}

uint8_t pc::jugar()
{  
 uint8_t EntradaPC= (random(0, 4.99));
 Serial.println("Tu contricante seleccionó: "+selection[EntradaPC]);
 return EntradaPC;
}


pc AI= pc();

uint8_t Npartidas()
{
	uint8_t intpartidas=0;
	Serial.print("Ingrese el numero de partidas a jugar (1, 3 o 5)");
	while(Serial.available())
	{
		String partidas = readString();
	  		if(partidas == "1")
	  		{
	     		intpartidas = 1;   
	    	}  
	    	if(partidas == "3")
	    	{
	     		intpartidas = 3;   
	    	}
	    	if (partidas == "5")
	    	{
	    		intpartidas ==5;
	    	}
	}
	return intpartidas;
}

String preguntartipo(){

	Serial.println("Insertar tipo o estado (piedra, papel, tijera, lagartija, spock o estado): ");
	String tipo = "";
	while(tipo == "")
	{
		tipo = readString();
	}
	return tipo;
}


String readString(){
	String output="";
	while(Serial.available())
	{
	  	output.concat(char(Serial.read()));
	  	delay(10);
	}
	return output;
}

void setup(){
	Serial.begin (115200);  //por que no 9600???
	AI.victorias = EEPROM.read(10);
	AI.perdidas = EEPROM.read(11);
}

void loop ()
{   
	uint8_t partidasjugadas = 0;
	uint8_t numpartidas = Npartidas();
	bool playing = true;

	while (playing == true)
	{
		int result= resultado();
			if(result==1)
			{
				AI.victorias++;
				partidasjugadas++;
				EEPROM.write(10, AI.victorias);
			}
			else if (result==-1)
			{
				AI.perdidas++;
				partidasjugadas++;
		 		EEPROM.write(11, AI.perdidas);
			}
		if (partidasjugadas==numpartidas)
		{
			playing=false;
		}
	}
}


int resultado()
{
	String usuario = preguntartipo();

	if(usuario=="estado")
	{
	Serial.println("sus resultados son:");  
	Serial.println("El numero total de partidas jugadas es:  totalpartidas");
	Serial.println("el numero de victorias es: " + String(EEPROM.read(10)));
	Serial.println("el numero de perdidas es: " + String(EEPROM.read(11)));
	Serial.print("\n");
	}
	else
	{
		uint8_t compu= AI.jugar();

	 if (usuario=="piedra")
	 {
	 	if ((compu==2)||(compu==3))
	 	{
	 		Serial.println ("Ganaste");
	 		return 1;
	 	}
	 	if (compu==0)
	 	{
	 		Serial.println ("Empate");
	 		return 0;
	 	}
	 	else
	 	{
	 		Serial.println ("Perdiste");
	 		return -1;
	 	}
	 }
	  else if (usuario=="papel")
	 {
	 	if ((compu==0)||(compu==4))
	 	{
	 		Serial.println ("Ganaste");
	 		return 1;
	 	}
	 	if (compu==1)
	 	{
	 		Serial.println ("Empate");
	 		return 0;
	 	}
	 	else
	 	{
	 		Serial.println ("Perdiste");
	 		return -1;
	 	}
	 }
	   else if (usuario=="tijera")
	 {
	 	if ((compu==1)||(compu==3))
	 	{
	 		Serial.println ("Ganaste");
	 		return 1;
	 	}
	 	if (compu==2)
	 	{
	 		Serial.println ("Empate");
	 		return 0;
	 	}
	 	else
	 	{
	 		Serial.println ("Perdiste");
	 		return -1;
	 	}
	 }
	   else if (usuario=="lagartija")
	 {
	 	if ((compu==1)||(compu==4))
	 	{
	 		Serial.println ("Ganaste");
	 		return 1;
	 	}
	 	if (compu==3)
	 	{
	 		Serial.println ("Empate");
	 		return 0;
	 	}
	 	else
	 	{
	 		Serial.println ("Perdiste");
	 		return -1;
	 	}
	 }
	    else if (usuario=="spock")
	 {
	 	if ((compu==0)||(compu==2))
	 	{
	 		Serial.println ("Ganaste");
	 		return 1;
	 	}
	 	if (compu==4)
	 	{
	 		Serial.println ("Empate");
	 		return 0;
	 	}
	 	else
	 	{
	 		Serial.println ("Perdiste");
	 		return -1;
	 	}
	 }
	 else
	 {
	 	Serial.println("Entrada inválida");
	 }
	}

}

