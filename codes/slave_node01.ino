    /*
      Arduino Wireless Network - Multiple NRF24L01 Tutorial
            == Node 02 (Child of Master node 00) ==    
    */
    #include <RF24Network.h>
    #include <RF24.h>
    #include <SPI.h>
    
    RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
    RF24Network network(radio);      // Include the radio in the network
    
    const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
    const uint16_t node00 = 00;    // Address of the other node in Octal format
    
    const unsigned long interval = 200;  //ms  // How often to send data to the other unit
    unsigned long last_sent;            // When did we last send?
    char led[3]={0};

    int led_red = 5, led_ylw = 6, led_grn = 7;
   
    void setup() {
      SPI.begin();
      Serial.begin(9600);
      radio.begin();
      network.begin(90, this_node);  //(channel, node address)
      radio.setDataRate(RF24_2MBPS);
      Serial.println("setup done01");

      pinMode(led_red,OUTPUT);
      pinMode(led_ylw,OUTPUT);
      pinMode(led_grn,OUTPUT);
    }
    
    void loop() {
      Configuration();
      mains();
    }


    void Configuration() 
      {
        int led=0;
        do
        {
         network.update();
         //===== Sending =====//
         unsigned long now = millis();
          if (now - last_sent >= interval)    // If it's time to send a data, send it!
            {
              last_sent = now;
              led=!led;
              RF24NetworkHeader header(node00);   // (Address where the data is going)
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              Serial.println(led);
              Serial.println("");
            }
        }while(!network.available());  // Is there any incoming data?
      }


     void mains()
    {
      while(true)
      {
        network.update();
        //===== Receiving =====//
        while ( network.available() )      // Is there any incoming data?
        {
          RF24NetworkHeader header; 
          char incomingData[3];
          network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
          Serial.println(header.from_node);
          Serial.println(incomingData);
          Serial.println("");

          digitalWrite(led_red,incomingData[0]);
          digitalWrite(led_ylw,incomingData[1]);
          digitalWrite(led_grn,incomingData[2]);
        }
      }
    }
