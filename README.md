# Poulailler

My **chicken coop** automation.

Automatisation de mon poulailler.
*Ce projet est majoritairement en anglais, non pas pour faire le mec qui s'y croit, mais simplement pour pouvoir partager sur les forums internationaux.*

## Goals

* Automatic open/close door as per sun light and/or consign
* Autonomous but ...
* ... connected to my home dashboard : wakeup consign, display critical figures on my dashboard and raise alarm in case of trouble.

## ESP8266 GPIO

* **ADC** : power supply monitoring (*internal*)
* **GPIO0** : enable water warming (*low*)
* **GPIO2** : 1-wire
* **GPIO4** : water low (*low*)

## Door control

- MX1508 H-Bridge
