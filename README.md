# OvercookedController

This repository contains the code for a custom controller designed for the game "Overcooked! 2". The controller is ingeniously split into three distinct parts, each serving a specific function:

<img src="https://github.com/eske4/OvercookedController/blob/main/images/AllComponents.jpg" width="300" height="200">

## Components:

1. **Knife with Buttons:**
   - Equipped with buttons for user interaction.
   - Enables unique actions triggered by doing a chopping motion with the knife.
     ![](https://github.com/eske4/OvercookedController/blob/main/images/knife.gif)

2. **Plate Controller:**
   - Responsible for character movement and control within the game.
   - Utilizes an accelerometer to track the tilt of the plate, adding an immersive dimension to the gameplay.
     ![](https://github.com/eske4/OvercookedController/blob/main/images/plate.gif)

3. **Receiver:**
   - Serves as a central hub that receives information from both the knife and plate controllers.
   - Enables Bluetooth communication between the controller components and the gaming system.
     ![](https://github.com/eske4/OvercookedController/blob/main/images/Sugar.jpg)

## Code Organization:

### Receiver:
   - Code Location: [Receiver/](Receiver/)
   - Description: Code that takes input from the knife and plate controllers.

### Plate Controller:
   - Code Location: [Wireless_Knife_Plate/Plate_Wireless](Wireless_Knife_Plate/Plate_Wireless)
   - Description: Sends thumbstick x-y coordinates through the accelerometer to the receiver. Triggers vibration if tilted too much, signaling that in-game items may be dropped.
### Knife Controller:
   - Code Location: [Wireless_Knife_Plate/KnifeWireless](Wireless_Knife_Plate/KnifeWireless)
   - Description: Sends input from the knife controller to the receiver. Includes a pressure sensor for in-game grabbing, two buttons for interactions, and an accelerometer to detect shaking for specific interactions.

## Components Utilized:

- **Vibration Module:** Enhances user feedback by incorporating vibration effects into the gaming experience.
- **Bluetooth Module:** Facilitates wireless communication between the controller components and the gaming system.
- **Accelerometer:** Enables precise tracking of plate tilt, contributing to a more dynamic and engaging gameplay.
- **Buttons:** Used for initiating various in-game actions.
- **Pressure sensor:** Used for grab actions.
- **xInput Library:** Employed to emulate an Xbox controller, ensuring compatibility with the game "Overcooked! 2".

Feel free to explore the codebase to gain insights into the intricacies of each component and their interactions.
