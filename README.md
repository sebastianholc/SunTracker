# SunTracker

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
