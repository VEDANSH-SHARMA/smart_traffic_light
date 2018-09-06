    /*
      Arduino Wireless Network - Multiple NRF24L01 Tutorial
              == Base/ Master Node 00==
      by Dejan, www.HowToMechatronics.com
      Libraries:
      nRF24/RF24, https://github.com/nRF24/RF24
      nRF24/RF24Network, https://github.com/nRF24/RF24Network
    */
    #include <RF24Network.h>
    #include <RF24.h>
    #include <SPI.h>
    
    RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
    RF24Network network(radio);      // Include the radio in the network
    
    const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
    const uint16_t node01 = 01;
    const uint16_t node02 = 02;
    const uint16_t node03 = 03;
    const uint16_t node04 = 04;

    int nodes=1;

    unsigned long last_sent;            // When did we last sendto nodes
    const unsigned long interval = 100;  //ms  // How often to send data to the nodes

    int led_red = 5, led_ylw = 6, led_grn = 7;
    
    void setup() {
      SPI.begin();
      Serial.begin(9600);
      radio.begin();
      network.begin(90, this_node);  //(channel, node address)
      radio.setDataRate(RF24_2MBPS);
      Serial.println("setup done00");

      pinMode(led_red,OUTPUT);
      pinMode(led_ylw,OUTPUT);
      pinMode(led_grn,OUTPUT);  
    }
    
    void loop() {
      Configuration();  // define no of nodes available
      Serial.print("nodes=");
      Serial.println(nodes);

      switch (nodes)    //calling function according to no of nodes
      {
        case 3:
          Three_Way();
          break;
        case 4:
           Four_Way();
           break;
        case 5:
           Five_Way();
           break;
        default:
           Serial.println("type of intersaction not found");
      }
    }


    void Configuration() 
    {
      nodes=1;
      int check_node[5]={0};     
      unsigned long current_time=millis();
      unsigned long start_time=millis();
      
      while(current_time-start_time < 10000)  // search nodes for 10 seconds
      {
        network.update();
        //===== Receiving =====//
        while( network.available() )      // Is there any incoming data?
        {
          RF24NetworkHeader header; 
          unsigned long incomingData;
          network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
          Serial.println(header.from_node);
          Serial.println(incomingData);
          Serial.println("");
  
          if(check_node[header.from_node]==0)   //to check node only counted once
          {
            nodes=nodes+1;
            check_node[header.from_node]=1; 
          }
        } 
          current_time=millis();     //updating current time
      }
    }


    void Three_Way()
    {
      char led[3];
      int k=0;
      while(true)
      {
          network.update();
         //===== Sending =====//
         unsigned long now = millis();
          if (now - last_sent >= interval)    // If it's time  to send a data, send it!
            {
              last_sent = now;
              
              
              if(k==0)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data

              led[0]='0';                       //for master node led
              led[1]='0';
              led[2]='1';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
               if(k==1)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data

              led[0]='0';                       //for master node led
              led[1]='1';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }   
               if(k==2)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data

              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }      
               if(k==3)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data

              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }      
              if(k==4)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data

              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }          
                  
                  
                  
            }
          
          
         k++;
         if(k==5)
         {
             k==0;
         }    
      }
    }

    void Four_Way()
    {
     char led[3];
      int k=0;
      while(true)
      {
          network.update();
         //===== Sending =====//
         unsigned long now = millis();
          if (now - last_sent >= interval)    // If it's time  to send a data, send it!
            {
              last_sent = now;
              
              
              if(k==0)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='0';                       //for master node led
              led[1]='0';
              led[2]='1';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
               if(k==1)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='0';                       //for master node led
              led[1]='1';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }          
               if(k==2)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }   
              if(k==3)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }    
              if(k==4)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               } 
              if(k==5)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               } 
              if(k==6)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               } 
            }
          
          
         k++;
         if(k==7)
         {
             k==0;
         }    
      } 
        
        
    }

    void Five_Way()
    {
      char led[3];
      int k=0;
      while(true)
      {
          network.update();
         //===== Sending =====//
         unsigned long now = millis();
          if (now - last_sent >= interval)    // If it's time  to send a data, send it!
            {
              last_sent = now;
              
              
              if(k==0)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='0';                       //for master node led
              led[1]='0';
              led[2]='1';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              
              if(k==1)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='0';                       //for master node led
              led[1]='1';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              
              if(k==2)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              
              if(k==3)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              
              
              if(k==4)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              
              if(k==5)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              if(k==6)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              if(k==7)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='0';
              led[1]='1';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              if(k==8)
               {
              RF24NetworkHeader header(node01);   // (Address where the data is going)
              led[0]='0';
              led[1]='0';
              led[2]='1';
              bool ok = network.write(header, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header1(node02);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok1 = network.write(header1, &led, sizeof(led)); // Send the data
              
              RF24NetworkHeader header(node03);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok2 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              RF24NetworkHeader header(node04);   // (Address where the data is going)
              led[0]='1';
              led[1]='0';
              led[2]='0';
              bool ok3 = network.write(header, &led, sizeof(led)); // Send the data //CHeck if bool ok2 is correct
              
              
              led[0]='1';                       //for master node led
              led[1]='0';
              led[2]='0';
              digitalWrite(led_red,led[0]);
              digitalWrite(led_ylw,led[1]);
              digitalWrite(led_grn,led[2]);
               }
              
              }
          
          
         k++;
         if(k==9)
         {
             k==0;
         }    
      } 
        
      
    }
