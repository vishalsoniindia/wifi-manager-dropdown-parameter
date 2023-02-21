#include <WiFiManager.h>

WiFiManager wm;

const char *bufferStr = R"(
  
  <!-- INPUT SELECT -->
  <br/>
  <label for='hour_select'>Choose Hour</label>
  <select name="hour_select" id="hour_select" class="button">
  <option value="0">--choose an option--</option>
  <option value="1">  1 </option>
  <option value="2">  2 </option>
  <option value="3">  3 </option>
  <option value="4">  4 </option>
  <option value="5">  5 </option>
  <option value="6">  6 </option>
  <option value="7">  7 </option>
  <option value="8">  8 </option>
  <option value="9">  9 </option>
  <option value="10">10 </option>
  <option value="11">11 </option>
  <option value="12">12 </option>
  </select>

  <br/>
  <label for='minute_select'>Choose minute</label>
  <select name="minute_select" id="minute_select" class="button">
  <option value="0">--choose an option--</option>
  <option value="1">   1 </option>
  <option value="2">   2 </option>
  <option value="3">   3 </option>
  <option value="4">   4 </option>
  <option value="5">   5 </option>
  <option value="6">   6 </option>
  <option value="7">   7 </option>
  <option value="8">   8 </option>
  <option value="9">   9 </option>
  <option value="10"> 10 </option>
  <option value="11"> 11 </option>
  <option value="12"> 12 </option>
  <option value="13"> 13 </option>
  <option value="14"> 14 </option>
  <option value="15"> 15 </option>
  <option value="16"> 16 </option>
  <option value="17"> 17 </option>
  <option value="18"> 18 </option>
  <option value="19"> 19 </option>
  <option value="20"> 20 </option>
  <option value="21"> 21 </option>
  <option value="22"> 22 </option>
  <option value="23"> 23 </option>
  <option value="24"> 24 </option>
  <option value="25"> 25 </option>
  <option value="26"> 26 </option>
  <option value="27"> 27 </option>
  <option value="28"> 28 </option>
  <option value="29"> 29 </option>
  <option value="30"> 30 </option>
  <option value="31"> 31 </option>
  <option value="32"> 32 </option>
  <option value="33"> 33 </option>
  <option value="34"> 34 </option>
  <option value="35"> 35 </option>
  <option value="36"> 36 </option>
  <option value="37"> 37 </option>
  <option value="38"> 38 </option>
  <option value="39"> 39 </option>
  <option value="40"> 40 </option>
  <option value="41"> 41 </option>
  <option value="42"> 42 </option>
  <option value="43"> 43 </option>
  <option value="44"> 44 </option>
  <option value="45"> 45 </option>
  <option value="46"> 46 </option>
  <option value="47"> 47 </option>
  <option value="48"> 48 </option>
  <option value="49"> 49 </option>
  <option value="50"> 50 </option>
  <option value="51"> 51 </option>
  <option value="52"> 52 </option>
  <option value="53"> 53 </option>
  <option value="54"> 54 </option>
  <option value="55"> 55 </option>
  <option value="56"> 56 </option>
  <option value="57"> 57 </option>
  <option value="58"> 58 </option>
  <option value="59"> 59 </option>
  <option value="60"> 60 </option>
  </select>
  
  )";


WiFiManagerParameter custom_html_inputs(bufferStr);

int hour = 0;
int minute = 0;

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  wm.resetSettings();

  wm.addParameter(&custom_html_inputs);

  // callbacks
  wm.setSaveParamsCallback(saveParamCallback);
  
  //set title
  wm.setTitle("Set Time");

  // invert theme, dark
  wm.setDarkMode(true);

  std::vector<const char *> menu = {"param", "sep", "exit"};
  wm.setMenu(menu); // custom menu, pass vector

  if (wm.autoConnect("digiPclock")) {
    ; // get false on exit
    Serial.println("Pass");
  }
  else {
    Serial.println("Exit");
  }

  if(hour != 0){
  Serial.println(hour);
  }else{
    Serial.println("hour not set");
  }

  if(minute != 0){
  Serial.println(minute);
  }else{
    Serial.println("minute not set");
  }
}

void loop() {

}

void saveParamCallback() {
  hour    = getParam("hour_select").toInt();
  minute  = getParam("minute_select").toInt();
  wm.stopConfigPortal();
}

String getParam(String name) {
  //read parameter from server, for customhmtl input
  String value;
  if (wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}
