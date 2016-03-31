
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x2B, 0x7B };  
IPAddress ip(10,0,0, 20);                               

EthernetServer server(80);

char char_in = 0;                         
String HTTP_req;                          

const byte LED_pins[] = {2, 3};         
byte LED[sizeof(LED_pins)] = {0};         

void setup()
{
    Ethernet.begin(mac, ip);
    server.begin();
    
                                                                       
																	   for (byte index = 0; index < sizeof(LED_pins); index++) {
        pinMode(LED_pins[index], OUTPUT);
    }
}

void loop()
{
    EthernetClient client = server.available();

    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char_in = client.read();                                    
                HTTP_req += char_in;                                        

                                                                                         
                if (char_in == '\n') {
                                                                                
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println();
                    CheckLEDs();                                                
                    DisplayLEDs(&client);                                           
                    HTTP_req = "";                                                     
                    client.stop();
                } // end if (char_in == '\n')
            } // end if (client.available()
        } // end while (client.connected())
    } // end if (client)
}

// get the state of the LED checkboxes from the HTTP request
void CheckLEDs()
{
    for (byte led_num = 0; led_num < sizeof(LED_pins); led_num++) {
        if ((HTTP_req.charAt(9) == (LED_pins[led_num] + '0')) &&
                    (HTTP_req.charAt(16) == (LED_pins[led_num] + '0'))) {  
            LED[led_num] = 1;
        }
        else if (HTTP_req.charAt(9) == (LED_pins[led_num] + '0')) {        
		LED[led_num] = 0;
        }
    }
}

// write the HTML that includes the state of the LED checkboxes for displaying on the web browser
void DisplayLEDs(Client *client)
{
    // some CSS in the HTML to change colours and position of the box containing the LED checkboxes
    client->print("<div style=\"background:white; color:green; position: absolute; margin:20px; border: grey solid 2px; padding:0 10px 4px 10px;\">");
    client->print("<h1 style=\"font: normal 20px/150% Verdana, Arial, Sans-serif;\">LED Outputs</h1>");
    // send each LED checkbox in turn
    for (byte led_num = 0; led_num < sizeof(LED_pins); led_num++) {
        // use hidden checkbox so that unchecking a checkbox sends a value to the Arduino
        // if only a normal checkbox is used, nothing is sent when it is unchecked
        // both hidden and normal checkboxes are produced here for each LED
        client->print("<form> <input type=\"hidden\" name=\"LED");
        client->print(LED_pins[led_num], DEC);
        client->print("\" value=\"0\"> <input type=\"checkbox\" name=\"LED");
        client->print(LED_pins[led_num], DEC);
        client->print("\" value=\"");
        client->print(LED_pins[led_num], DEC);
        client->print("\"");
                                                                             
        if (LED[led_num]) {
            client->print(" checked ");                                    
            digitalWrite(LED_pins[led_num], HIGH);                        
        }
        else {
            digitalWrite(LED_pins[led_num], LOW);                       
        }
        client->print(" onclick=\"submit();\">LED");
        client->print(LED_pins[led_num], DEC);
        client->print(" </form>");                                     }
    client->print("</div>");                                        
}
