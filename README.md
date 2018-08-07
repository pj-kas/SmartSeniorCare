# SmartSeniorCare

## An Ambient Assisted Living (AAL) Safety System for Senior Citizens.

#### Employs a network of wireless sensor nodes (motion and vibration), connected to ESP8266 microcontrollers sending data to Raspberry Pi using MQTT. Published data is then uploaded to AWS IoT and stored in DynamoDb. AWS Lambda parses data and sends emergency SMS alerts to subscribed phone numbers when no motion has been detected for 12 hours or if a fall has been detected by a vibration sensor. Live Camera feed is also available via static external IP address for concerned family members to be able to check in on their loved ones.

#### More detailed documentation is available in DOCUMENTATION.pdf

#### Arduino folder contains Arduino code used for programming ESP8266. AWS folder contains Lambda code and AWS IoT Rules. Python folder contains Python code to be run on Raspberry Pi base stations.

#### Link to demo video https://drive.google.com/file/d/1t5RpT7yu19N2V-xy0Dn5PcDaqNZWd0j5/view?usp=sharing
