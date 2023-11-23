# <p align="center">OvercookedController</p>

<p align="center">This repository contains the code for a custom controller designed for the game "Overcooked! 2". The controller is split into three distinct parts, each serving a specific function:</p>

<p align="center"><img src="https://github.com/eske4/OvercookedController/blob/main/images/AllComponents.jpg" width="800"></p>

## <p align="center">Parts:</p>

<p align="center">1. <strong>Knife with Buttons:</strong></p>
<p align="center">- Equipped with buttons for user interaction.</p>
<p align="center">- Enables unique actions triggered by doing a chopping motion with the knife.</p>
<p align="center"><img src="https://github.com/eske4/OvercookedController/blob/main/images/knife.gif" width="500"></p>

<p align="center">2. <strong>Plate Controller:</strong></p>
<p align="center">- Responsible for character movement and control within the game.</p>
<p align="center">- Utilizes an accelerometer to track the tilt of the plate, adding an immersive dimension to the gameplay.</p>
<p align="center"><img src="https://github.com/eske4/OvercookedController/blob/main/images/plate.gif" width="500"></p>

<p align="center">3. <strong>Receiver:</strong></p>
<p align="center">- Serves as a central hub that receives information from both the knife and plate controllers.</p>
<p align="center">- Enables Bluetooth communication between the controller components and the gaming system.</p>
<p align="center"><img src="https://github.com/eske4/OvercookedController/blob/main/images/Sugar.jpg" width="500"></p>

## <p align="center">Controllers showcase:</p>
<p align="center">Below the interaction with the controllers and their hardware can be seen</p>
<p align="center"><img src="https://github.com/eske4/OvercookedController/blob/main/images/Info.jpg" width="700"></p>

## <p align="center">Code Organization:</p>

### <p align="center">Receiver:</p>
<p align="center">- Code Location: [Receiver/](Receiver/)</p>
<p align="center">- Description: Code that takes input from the knife and plate controllers.</p>

### <p align="center">Plate Controller:</p>
<p align="center">- Code Location: [Wireless_Knife_Plate/Plate_Wireless](Wireless_Knife_Plate/Plate_Wireless)</p>
<p align="center">- Description: Sends thumb stick x-y coordinates through the accelerometer to the receiver. Triggers vibration if tilted too much, signaling that in-game items may be dropped.</p>

### <p align="center">Knife Controller:</p>
<p align="center">- Code Location: [Wireless_Knife_Plate/KnifeWireless](Wireless_Knife_Plate/KnifeWireless)</p>
<p align="center">- Description: Sends input from the knife controller to the receiver. Includes a pressure sensor for in-game grabbing, two buttons for interactions, and an accelerometer to detect shaking for specific interactions.</p>

## <p align="center">Components and libraries Utilized:</p>

<p align="center">- <strong>Vibration Module:</strong> Enhances user feedback by incorporating vibration effects into the gaming experience.</p>
<p align="center">- <strong>Bluetooth Module:</strong> Facilitates wireless communication between the controller components and the gaming system.</p>
<p align="center">- <strong>Accelerometer:</strong> Enables precise tracking of plate tilt, contributing to a more dynamic and engaging gameplay.</p>
<p align="center">- <strong>Buttons:</strong> Used for initiating various in-game actions.</p>
<p align="center">- <strong>Pressure sensor:</strong> Used for grab actions.</p>
<p align="center">- [xInput Library](https://github.com/dmadison/ArduinoXInput): Employed to emulate an Xbox controller, ensuring compatibility with the game "Overcooked! 2".</p>

<p align="center">Feel free to explore the codebase to gain insights into the intricacies of each component and their interactions.</p>
