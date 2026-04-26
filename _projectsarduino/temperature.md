---
title: "Temperature and SD Card"
date: 2024-10-9
layout: single
classes: narrow
---

<!--more-->

## Overview
For this project, I was tasked to design a system that could read the temperature of different environments and save it to an SD card. For this I was given a SD card shield that I could just slot ontop of the Arduino Uno. I was to save an excel file onto the SD card with all the temperature information needed to then analyze using RStudio.

## Parts Used
- Arduino Uno
- Temperature & Humidity Sensor (DHT11)
- Seeed Studio SD Card Shield V4

## Design Layout

<img src="/images/temperature_design.png" style="width:600px; height:auto;">

## Code
### Arduino Code

<script src="https://gist.github.com/goldentoad12/2308896209afee882e753b1441840c8e.js"></script>

Download Arduino Code:
[Download Arduino Code]({{ "/assets/code/temperature.ino" | relative_url }})

### RStudio Code

<script src="https://gist.github.com/goldentoad12/02b5ccd1238093c2d91a204b14f95367.js"></script>

Download RStudio Code:
[Download RStudio Code]({{ "/assets/code/temperature.R" | relative_url }})

## Summary
Summary Goes Here

---

PLACE THIS INTO THE projectsarduino.md FILE

### [Temperature and SD Card]({{ "/projectsarduino/temperature/" | relative_url }})

Using an SD card to save temperature readings.

**Tools:** Arduino, SEEED Studio parts, RStudio

---
