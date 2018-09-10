# Arcade Table
My take of the classic arcade table (cabinet). Constructed completely by hand with 13mm MDF, glue and a lots of screws. Complete with 4:3 aspect ratio 19 Inch TFT Monitor, thumping 2x50 Watt Class-D Power Amplified and authentic controls.

# Warning
This design has not been compliance tested and will not be. Mains power is feed directly into the cabinet and can be DANGEROUS or LIFE THREATING. I take no personal responsibility liability should you injure or kill yourself should you decide to copy this design and build a cabinet yourself. I accept no responsibility for any damage to any equipment that results from the use of this design and its components. IT IS ENTIRELY AT YOUR OWN RISK!

# Overview
After seeing my designs of Raspberry Pi arcade tables or cabinets I was sold on the idea and wanted to build one myself. I found a blog of person who created one using an IKEA table and I though this was a great idea. I then built one and after many hours playing "Buggy Boy" on the C64 I realise the ergonomics of the IKEA table design was terrible!

I actually found some sellers on various auction sites selling designs and cut frames for all different prices, but I wanted the challenge to make one completely myself. So set with 4sqm of 13mm MDF (I only ended up needing 1sqm), a bunch of tools and an idea, I set to work on a table top design.

Simple angels are used ensuring the LCD remains in the optimal viewing position and the controls "lean" towards the player. I researched the layout of the buttons (yes there is actually an optimal layout as each finger on our hand has a different length relative to your knuckles) to also make sure these would be comfortable.

### Appearance
Nice basic frame:
![Basic Frame](/Images/BasicFrame.JPG)

### Components
Of course a Raspberry Pi is at the heart of this! As I am only interested in C64 and really early arcade classics (Double Dragon) I settled with a Raspberry Pi B+ which I had on hand. Overclocked to 800Mhz this was perfectly fine. Wired to the Raspberry Pi via HDMI is a 19 Inch TFT, USB dongle for a Keyboard + Mouse, USB Control Kit and a Bluetooth dongle.

Basic internals:
![Basic Internals](/Images/PSU+RaspberryPi+AMP+Speakers.JPG)

Sound is realised though a set of 7 Inch Car Speakers each rated at 100 Watts mounted on the sides of the cabinet. These are powered by a Class-D Digital Power Amplifier with both 3.5mm Jack and Bluetooth input source capabilities. I found that once the cabinet is sealed closed there is enough loading on the speakers to produce a great sound! I just love the intro music to Cybernoid II (https://en.wikipedia.org/wiki/Cybernoid_II:_The_Revenge) - one of the best SID tunes in my opinion.

Wired internals:
![Wired Internals](/Images/PSU+RaspberryPi+AMP+Speakers-Wired.JPG)

With the monitor fitted:
![Monitor Fitted](/Images/AssembledOnlyWithScreen.JPG)

Assembled with controls:
![Controls Fitted](/Images/AssembledWithControls.JPG)

... and finally with some power applied:
![All Powered Up](/Images/ItsAlive.JPG)

### Bling Bling
To go along with the awesome Cybernoid II intro music, I decided to add some flashing lights... Of course! Having used WS2812, but only having a few spare I opted to use a simple Blue LED strip. Simple but effective, especially with the glossy paint finish.

LED Strip:
![LED Strip](/Images/LEDStrip.JPG)

I didn't use the Raspberry Pi to control the LEDs as I had on hand a bunch of ATTiny85 USB Dev Boards and I wired an output to control a N-Channel FET. The control software is COMPLETE OVERKILL. I created a series of LED Flash Patterns handlers which in my later Arduino Projects were put into a class. Still huge OVERKILL, but pretty cool nevertheless!

The LEDs are flashed and faded randomly using a random selection primitive handles. The next flash pattern is only selected once the current is finished. Available amazing eye-catching primitives are;

1. Slow flashes
  - slowFlashSingle
  - slowFlashMultiple
  - slowFlashRandom

2. Fast flashes
  - fastFlashSingle
  - fastFlashMultiple
  - fastFlashRandom

3. Fading effects
  - fadeOnFadeOff
  - fadeOnFastOff
  - fastOnFadeOff

That's it! Back to Cybernoid II! :laughing:
