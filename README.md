🇬🇧 [English version](#suntracker-en)

---
# SunTracker [PL]



## Dwuosiowy układ śledzenia źródła światła (Solar tracker)

Projekt dwuosiowego układu śledzenia źródła światła. Urządzenie wykorzystuje cztery fotorezystory do szukania najjaśniejszego punktu i ustawia głowicę w jego stronę za pomocą dwóch serwomechanizmów. Głowica i podstawka zostały własnoręcznie zaprojektowane w programie Autodesk Inventor, a następnie wydrukowane na drukarce 3D.



## Sprzęt

* **Mikrokontroler:** Arduino Uno

* **Zasilanie:** Pakiet 4x bateria AA (łącznie 6V)

* **Elementy wykonawcze:** 2x serwomechanizm SG90 Micro (zakres ruchu 180°)

* **Czujniki:** 4x fotorezystor (rezystancja 5-10 kΩ)



## Konstrukcja

Urządzenie składa się z dwóch zaprojektowanych przeze mnie i wydrukowanych na drukarce 3D części: podstawki oraz głowicy. Korzysta również z [gotowego układu pan/tilt](https://botland.com.pl/chwytaki-uchwyty-gimbale/1948-uchwyt-do-serw-micro-pan-tilt-sparkfun-rob-10335-5904422308308.html). Podstawka została zaprojektowana tak, aby serwomechanizm bezpośrednio się w nią wsuwał. Głowica z druku 3D jest natomiast przykręcana do uchwytu pan/tilt przy pomocy 4 śrub.



## Elektronika

Fotorezystory pracują w klasycznym układzie dzielnika napięcia, z którego sygnał odczytywany jest przez wejścia analogowe Arduino. Serwomechanizmy sterowane są sygnałami PWM z mikrokontrolera, ale korzystają z całkowicie niezależnego źródła zasilania (pakiet baterii 6V) ze wspólną masą. Na obecnym etapie prototypowania wszystkie połączenia zrealizowano za pomocą przewodów na stykowej płytce montażowej (breadboard).



## Algorytm i kod

Algorytmy zostały napisane całkowicie w języku C++. Cała logika sterowania została zamknięta w autorskiej klasie `SunTracker`. Klasa ta przechowuje konfigurację sprzętową pinów, zbiera odczyty analogowe z czterech fotorezystorów i bezpośrednio wysterowuje serwomechanizmy. Zawiera również wbudowane zabezpieczenia przed przekroczeniem fizycznych limitów konstrukcji oraz metody diagnostyczne ułatwiające rozwiązywanie problemów przez port szeregowy.



Główne tryby pracy opierają się na dwóch metodach:

* **Śledzenie horyzontalne (`trackHorizontal`):** Podstawowy algorytm odpowiadający za orientację układu w jednej osi (lewo-prawo). Oblicza różnicę naświetlenia między lewą a prawą stroną, a gdy uchyb przekroczy wyznaczony próg tolerancji (`threshold`), koryguje pozycję dolnego serwa o jeden stopień. Algorytm posiada blokady zapobiegające zejściu wartości sterującej poniżej 0 i przekroczeniu 180.

* **Śledzenie dwuosiowe (`trackDualAxis`):** Główny algorytm korygujący położenie w obu płaszczyznach jednocześnie. Analizuje odczyty ze wszystkich czterech czujników, niezależnie obliczając błąd dla osi poziomej i pionowej. Ruch serwa wertykalnego jest dodatkowo objęty sztywnymi limitami (`MAX_TILT_DOWN` ustawione na 90 stopni i `MAX_TILT_UP` na 140 stopni), co zapobiega uszkodzeniu lub zablokowaniu się głowicy o podstawkę konstrukcji.



## Plany rozwoju

* **Praca długoterminowa i usypianie:** Napisanie energooszczędnego algorytmu, w którym układ dostaje zasilanie tylko na chwilę, ustala pozycję i idzie spać na wyznaczony czas. Głowica opadnie wtedy pod swoim ciężarem, ale w trybie uśpienia nie ma to znaczenia.

* **Elektronika:** 

  * Dodanie kondensatorów w obwód zasilania serwomechanizmów, aby zagwarantować stabilność zasilania.

  * Zaprojektowanie i wykonanie docelowej płytki drukowanej (PCB) pod cały układ.
---


# SunTracker [EN]



## Dual-axis light source tracking system (Solar tracker)

A dual-axis light source tracking system project. The device uses four photoresistors to find the brightest point and points the head towards it using two servomechanisms. The head and base were custom-designed in Autodesk Inventor and then 3D printed.



## Hardware

* **Microcontroller:** Arduino Uno

* **Power supply:** 4x AA battery pack (6V total)

* **Actuators:** 2x SG90 Micro servomechanism (180° range of motion)

* **Sensors:** 4x photoresistor (5-10 kΩ resistance)



## Construction

The device consists of two 3D-printed parts designed by me: the base and the head. It also utilizes a [ready-made pan/tilt bracket](https://botland.com.pl/chwytaki-uchwyty-gimbale/1948-uchwyt-do-serw-micro-pan-tilt-sparkfun-rob-10335-5904422308308.html). The base was designed so that the servomechanism slides directly into it. The 3D-printed head is screwed to the pan/tilt bracket using 4 screws.



## Electronics

The photoresistors operate in a classic voltage divider circuit, from which the signal is read by the Arduino's analog inputs. The servomechanisms are controlled by PWM signals from the microcontroller but use a completely independent power source (6V battery pack) with a common ground. At the current prototyping stage, all connections are made using jumper wires on a breadboard.



## Algorithm and code

The algorithms were written entirely in C++. The entire control logic is encapsulated in a custom `SunTracker` class. This class stores the hardware pin configuration, collects analog readings from the four photoresistors, and directly controls the servomechanisms. It also includes built-in safeguards against exceeding the physical limits of the structure and diagnostic methods to facilitate troubleshooting via the serial port.



The main operating modes are based on two methods:

* **Horizontal tracking (`trackHorizontal`):** The basic algorithm responsible for the system's orientation in one axis (left-right). It calculates the illumination difference between the left and right sides, and when the error exceeds a designated tolerance threshold (`threshold`), it corrects the lower servo's position by one degree. The algorithm has safeguards to prevent the control value from dropping below 0 and exceeding 180.

* **Dual-axis tracking (`trackDualAxis`):** The main algorithm correcting the position in both planes simultaneously. It analyzes readings from all four sensors, independently calculating the error for the horizontal and vertical axes. The vertical servo's movement is additionally constrained by hard limits (`MAX_TILT_DOWN` set to 90 degrees and `MAX_TILT_UP` to 140 degrees), which prevents the head from damaging or jamming against the base structure.



## Future development

* **Long-term operation and sleep mode:** Writing an energy-efficient algorithm where the system receives power only for a moment, determines its position, and goes to sleep for a set time. The head will then drop under its own weight, but in sleep mode, this does not matter.

* **Electronics:** 

  * Adding capacitors to the servomechanism power circuit to ensure power stability.

  * Designing and manufacturing a custom printed circuit board (PCB) for the entire system.
