# group9-hw-ID-CAPR
Group 9 repository for the ID homework of CMLS 2022
# The BELAtore
## Computer Music - Languages and Systems AY 2021/2022, Homework 3.
### By CAPR Group: Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

<br />
<div align="center">
<img src="https://user-images.githubusercontent.com/51057211/169388464-58b6c300-094e-49a4-bde6-31e8fce45283.png" width="200" height="200">
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
      <li><a href="#the-belatore">The BELAtore</a></li>
      <li><a href="#built-with">Built With</a></li>
    <li>
      <a href="#folder-structure">Folder Structure</a>
    <li>
      <a href="#usage">Usage</a>
    </li>
    <li>
      <a href="#the-bela-board">The BELA board</a>
    </li>
    <li>
      <a href="#the-belabirinto">The BELAbirinto</a>
    </li>
    <li>
      <a href="#the-belatore-plugin">The BELAtore plugin</a>
    </li>
    <li>
      <a href="#contact">Contact</a></li>
  </ol>
</details>

## The BELAtore
The Belatore is an effect plugin that permits to use, manage, and mix two audio effects in a funny and interactive way using a joystick and a touch sensor connected to a BELA board. 
The Belatore can be used either as a standalone application or as a VST in a DAW, such as Ableton, Pro Tools etc. and it consists in two main parts:
* The BELAtore: The audio plugin.
* The BELAbirinto: An interactive GUI that communicate with the Belatore using OSC messages.

### Built With

These are the major tools used to bootstrap the Belatore project. Please, make sure to have all these components installed in your device in order to make the application work properly.

* [Processing](https://processing.org/)
* [BELA](https://bela.io/)
* [JUCE 6](https://juce.com/)
* [Visual Studio](https://visualstudio.microsoft.com/)

## Folder structure
Cloning the repository there will be available two main folders, **TheBELAtore** and **TheBELAbirinto**.
The **TheBELAtore** folder contains a JUCE project whose structure is the same as a standard JUCE plugin application. Opening the ***.jucer*** file with the cross-platform **Projucer**, the JUCE project can then be built with every other IDE such as Visual Studio and XCode.
The **BELAbirinto** folder contains the maze game. This section has been implemented using Processing. In the folder is present the ***Labirinto.pde*** file, that can be opened and run with the Processing IDE.

TODO: how to import the BELA script and to make it work

## How to run the BELAtore

The application can be used in two modalities: as a classic VST application or connecting it with the BELAbirinto maze. This is possible only with a BELA board connected to the computer and a Joystick and touch sensor. In particular, the devices that have been used for our development are ***DFROBOT Touch Sensor V2*** and ***DFROBOT Joystick V2*** (available here: https://www.dfrobot.com/connected) to a solderless breadboard. 
<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

### The BELA Board
Connect the sensors with Bela throught a breadboard.
In particular the X and Y potentiometers of the Joystick has to be connected to analog inputs (https://learn.bela.io/tutorials/pure-data/connecting/analog-input/) while the Z potentiometer and the Touch Sensor has to go into the digital input (https://learn.bela.io/tutorials/pure-data/connecting/digital-input/#:~:text=The%20%5Br%20bela_digitalIn18%5D%20receives%20the%20value%20read%20of,3.3V%20which%20is%20represented%20as%201%20on%20Bela.).

Now you can send OSC messages which can be read by the other programmes (https://learn.bela.io/tutorials/pure-data/communication/open-sound-control/).

### The BELAbirinto
![TheBELAbirinto](https://user-images.githubusercontent.com/51057211/171942269-32ad74a8-9f45-4892-8b09-0882195f8f1e.png)
|:--:|
| <b>The BELAbirinto maze game</b>|

The user can play with the **Capr Logo** and move it through the maze with the Joystick. The goal is to perceive the sound effects changes by moving horizontally and vertically. In the labyrinth the goat can run into other animals. The user can displace them by using the Touch Sensor (for real animals) or the Z Joystick's potentiometer (for scary faces). But, take care if you touch them: you return to the start middle position!

### The BELAtore plugin
<img src="https://user-images.githubusercontent.com/51057211/171940299-39ebd688-16c5-4c65-ba38-d2e86a85b005.png" alt="TheBelatoreGUI" width="700"/>
<b>The BELAtore GUI</b>

The GUI has three main modules: **The Master Controls** and two **Effects modules** in series.
The effects can be chosen selecting them on the combo box and bypassed toggling button on the right of each module.
The available effects are:
* **Distortion**, in which is present a cabinet selector with some of the most famous guitar amp cabinets of all time.
* **Filter:** A two-band filter with gain controls for each band. 
* **Phaser.** 
* **Chorus.**
* **Delay:** A linear interpolated delay with a maximum delay length of 2 seconds.
* **Reverb.**
* **Pan.**

### Interaction between The BELAtore and the BELAbirinto
The CAPR's position in the BELAbirinto maze game controls via OSC messages some audio parameters in the BELAtore audio application.
In particular, here is a list of the controlled parameters:

* **Distortion:** Mix control.
* **Filter:** Cutoff frequency. 
* **Phaser:** Mix control.
* **Chorus:** Mix control.
* **Delay:** Mix control.
* **Reverb:** Mix control.
* **Pan:** Panning control.

Choosing one effect in the first module, its OSC-controlled parameter will be affected by the ***x*** position of CAPR in the maze, while the ***y*** position will affect the parameter of the second module's effect.

Moreover, the maze is haunted of animals and scary faces! If CAPR touches them, a white noise component occurs and he will go back to the center of the BELAbirinto maze. In order to remove the noise component, CAPR has to go near to a character an press the touch sensor or the ***z*** button of the joystick, depending if it is respectively a face or an animal. 

## Contact

Claudio Eutizi - claudio.eutizi@mail.polimi.it
Andres Bertazzi - andres.bertazzi@mail.polimi.it
Pierluigi Tartabini - pierluigi.tartabni@mail.polimi.it
Riccardo Martinelli - riccardo1.martinelli@mail.polimi.it

Project Link: [Belatore-CAPR](https://github.com/polimi-cmls-22/group9-hw-ID-CAPR/)

<p align="right">(<a href="#top">back to top</a>)</p>

