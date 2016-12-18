 #include <ESP8266WiFi.h>
 #include <IRremoteESP8266.h>
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);           
decode_results results; 
int ledPin_p=16;
int ledPin_o=15;
int ledPin_i=13;
int ledPin_u=12;
int ledPin_y=5;
int ledPin_t=4;
int ledState_p= 0;
int ledState_o= 0;
int ledState_i= 0;
int ledState_u= 0;
int ledState_y= 0;
int ledState_t= 0;
int i=0;

String ResponseControl(void);

WiFiServer server(80);

int pinList[6] = { 16, 15, 13, 12, 5, 4};
String responseHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\nConnection: close\r\n\r\n";

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare
  for (int i=0;i<6;i++){
    pinMode(pinList[i], OUTPUT);
    digitalWrite(pinList[i], LOW);
  }
    irrecv.enableIRIn(); 
  pinMode(ledPin_p, OUTPUT);
  pinMode(ledPin_o, OUTPUT);
  pinMode(ledPin_i, OUTPUT);
  pinMode(ledPin_u, OUTPUT);
  pinMode(ledPin_y, OUTPUT);
  pinMode(ledPin_t, OUTPUT);

  digitalWrite(ledPin_p, LOW);
  digitalWrite(ledPin_o, LOW);
  digitalWrite(ledPin_i, LOW);
  digitalWrite(ledPin_u, LOW);
  digitalWrite(ledPin_y, LOW);
  digitalWrite(ledPin_t, LOW);
    
    
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ElangoMaja","123456789"); 
  // WiFi.softAP("ioESP", "123456789"); 
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    translateIR(); 
    irrecv.resume(); 
  } 
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(client.connected() && !client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/api") >= 0){ // Is API request
    for (int i=0;i<6;i++){
      if (req.indexOf("/api/gpio" + String(pinList[i])) >= 0){
        if (req.indexOf("/api/gpio" + String(pinList[i]) + "/1") >= 0){
          digitalWrite(pinList[i], HIGH);
          client.flush();
          client.print(responseHeader + "OK");
        }else if (req.indexOf("/api/gpio" + String(pinList[i]) + "/0") >= 0){
          digitalWrite(pinList[i], LOW);
          client.flush();
          client.print(responseHeader + "OK");
        }else if (req.indexOf("/api/gpio" + String(pinList[i]))){
          client.flush();
          client.print(responseHeader + "Status:" + (digitalRead(pinList[i]) ? "1" : "0")); // Send the response to the client
        }
        break;
      }
    }
  }else{
    // Match the request
    for (int i=0;i<6;i++){
      if (req.indexOf("/gpio" + String(pinList[i]) + "/1") >= 0)
        digitalWrite(pinList[i], HIGH);
      else if (req.indexOf("/gpio" + String(pinList[i]) + "/0") >= 0)
        digitalWrite(pinList[i], LOW);
    }

    client.flush();

    // Prepare the response
    String s = ResponseControl();

    // Send the response to the client
    client.print(s);
  }

  Serial.println("Client disonnected");
  delay(1);
  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

String ResponseControl(){
  String ControlHTML = responseHeader;
  ControlHTML += "<title>Z POWER</title>\r\n";
  ControlHTML += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=5\">\r\n";
 
  ControlHTML += "<h1 style=\"color:#50;center;\">Z POWER ELECTRONICS</h1>\r\n";
  ControlHTML += "<h3 style=\"color:#255;margin-top:5px;\">HOME AUTOMATION INNOVATION</h3>\r\n";
  ControlHTML += "<table width=\"200\" border=\"0\" cellpadding=\"10\" cellspacing=\"0\"\>\r\n";
  ControlHTML += "<body bgcolor = \"#bccad6\">";
  ControlHTML += "<font color=\"#0000ff\">";
   ControlHTML +="<body background=\"one.jpg\">";
  ControlHTML +="<meta http-equiv=\"refresh\" content=\"0\">";
  for (int i=0;i<6;i++){
  ControlHTML += "<tr>\r\n";
  ControlHTML += "<td width=\"100\">LAMP" + String(pinList[i]) + "</td>\r\n";
  ControlHTML += "<td width=\"60\" align=\"center\"><button {background-color: #4CAF50;} onClick=\"location='/gpio" + String(pinList[i]) + "/" + (digitalRead(pinList[i]) ? "0" : "1") + "'\">" + (digitalRead(pinList[i]) ? "OFF" : "ON") + "</button></td>\r\n";
  ControlHTML += "</tr>\r\n";
  }
  ControlHTML += "</table>\r\n";
  return ControlHTML;
}

void translateIR() 
{
 switch(results.value)
 {

  case 0xF16E011F:  if(ledState_p==0){ //if the LED is off, It will turn on
          Serial.println("Turns ON the LED Selected");
          digitalWrite(ledPin_p, HIGH);  //sets the LED on
          ledState_p=1;                  //updates the LED state
        }
        else{
          Serial.println("Turns OFF the LED Selected"); //else: the LED is on, It will turn off
          digitalWrite(ledPin_p, LOW);   //sets the LED off
          ledState_p=0;                  //updates the LED state
        }   ;break;
        case 0x4913289B:  if(ledState_o==0){ //if the LED is off, It will turn on
          Serial.println("Turns ON the LED Selected");
          digitalWrite(ledPin_o, HIGH);  //sets the LED on
          ledState_o=1;                  //updates the LED state
        }
        else{
          Serial.println("Turns OFF the LED Selected"); //else: the LED is on, It will turn off
          digitalWrite(ledPin_o, LOW);   //sets the LED off
          ledState_o=0;                  //updates the LED state
        }   ;break;
        case 0x835150FB:  if(ledState_i==0){ //if the LED is off, It will turn on
          Serial.println("Turns ON the LED Selected");
          digitalWrite(ledPin_i, HIGH);  //sets the LED on
          ledState_i=1;                  //updates the LED state
        }
        else{
          Serial.println("Turns OFF the LED Selected"); //else: the LED is on, It will turn off
          digitalWrite(ledPin_i, LOW);   //sets the LED off
          ledState_i=0;                  //updates the LED state
        }   ;break;
        case 0x8E45A9BF:  if(ledState_u==0){ //if the LED is off, It will turn on
          Serial.println("Turns ON the LED Selected");
          digitalWrite(ledPin_u, HIGH);  //sets the LED on
          ledState_u=1;                  //updates the LED state
        }
        else{
          Serial.println("Turns OFF the LED Selected"); //else: the LED is on, It will turn off
          digitalWrite(ledPin_u, LOW);   //sets the LED off
          ledState_u=0;                  //updates the LED state
        }   ;break;
        case 0x3C76279B:  if(ledState_y==0){ //if the LED is off, It will turn on
          Serial.println("Turns ON the LED Selected");
          digitalWrite(ledPin_y, HIGH);  //sets the LED on
          ledState_y=1;                  //updates the LED state
        }
        else{
          Serial.println("Turns OFF the LED Selected"); //else: the LED is on, It will turn off
          digitalWrite(ledPin_y, LOW);   //sets the LED off
          ledState_y=0;                  //updates the LED state
        }   ;break;
        case 0xA83875F:  if(ledState_t==0){ //if the LED is off, It will turn on
          Serial.println("Turns ON the LED Selected");
          digitalWrite(ledPin_t, HIGH);  //sets the LED on
          ledState_t=1;                  //updates the LED state
        }
        else{
          Serial.println("Turns OFF the LED Selected"); //else: the LED is on, It will turn off
          digitalWrite(ledPin_t, LOW);   //sets the LED off
          ledState_t=0;                  //updates the LED state
        }   ;break;
         
  default: 
  Serial.println(" other button   ");
  }

  delay(500); 

}
