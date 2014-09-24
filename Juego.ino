//Rock, paper, sccisors, lizard, spock

#include "EEPROM.h"

const char* selection[] = {"piedra","papel","tijera","largartija","Spock"};

class pc
{
	public:
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
 Serial.print("Tu contricante seleccionó: ");
 Serial.println(selection[EntradaPC]);
 return EntradaPC;
}


pc AI= pc();

uint8_t Npartidas()
{
	uint8_t intpartidas=0;
	Serial.print("Ingrese el numero de partidas a jugar (1, 3 o 5)");
	while(intpartidas=0)
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
	    		intpartidas =5;
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

void setup()
{
	Serial.begin (115200);  //por que no 9600???
	EEPROM.write(10,0);
	EEPROM.write(11,0);
	//AI.victorias = EEPROM.read(10);
	//AI.perdidas = EEPROM.read(11);
}

void loop ()
{   
	uint8_t partidasjugadas = 0;
	uint8_t numpartidas = 0;
	uint8_t pperdidas=0;
	uint8_t pvictorias=0;
	bool playing = false;

		while (numpartidas==0)
	{
	numpartidas=Npartidas();
	playing = true;	
	}


	while (playing == true)
	{
		int result= resultado();
			if(result==1)
			{
				AI.victorias++;
				partidasjugadas++;
				pvictorias++;
				EEPROM.write(10, AI.victorias);
			}
			else if (result==-1)
			{
				AI.perdidas++;
				partidasjugadas++;
				pperdidas++;
		 		EEPROM.write(11, AI.perdidas);
			}
		if (partidasjugadas==numpartidas)
		{
			if (pvictorias>=pperdidas)
			{
				Serial.println("FELICITACIONES!!! Has ganado la partida");
				playing=false;
			}
			else{
				Serial.println("Lo siento, has perdido la partida");
				playing=false;
			}
			
		}
	}
}


int resultado()
{
	String usuario = preguntartipo();
		uint8_t pjugadas=EEPROM.read(10)+EEPROM.read(11);

	if (usuario!="piedra" && usuario!="papel" && usuario!="tijera" && usuario!="lagartija" && usuario!="spock" && usuario!="estado")
	 {
	 	Serial.println("Entrada inválida");
	 	usuario = preguntartipo(); //el return que tenia hacia que se quedara en preguntartipo
	 }

	if(usuario=="estado")
	{
	Serial.println("sus resultados son:");  
	Serial.print("El numero total de partidas jugadas es: ");
	Serial.println(pjugadas);
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
	}
}

