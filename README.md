# BU353S4 USB GPS Receiver

This REDHAWK Device has been developed against REDHAWK 2.0 and requires the following library as well as libusb-1.0, which is available in most operating systems.

http://downloads.sourceforge.net/project/nmea/NmeaLib/nmea-0.5.x/nmealib-0.5.3.zip

Installation of the NMEA parsing library is the typical make route:

    unzip nmealib-0.5.3.zip
    cd nmealib
    make
    sudo cp -r lib include /usr/local

## Installation

Compile the device in the usual way:

    cd cpp
    ./reconf
    ./configure
    make

Back at the top-level project directory where the SPD is located, you can then test the device in a Python shell.

    from ossie.utils import sb
    gps = sb.launch('BU353S4.spd.xml')
    gps.start()
    
    gps.ports[0].ref._get_gps_time_pos()
    gps.ports[0].ref._get_gps_info()

The output of these two commands should show the received time increasing and a valid position as long as there are more than 5 satellites visible.  The number of satellites visible can be seen in the GPS Info (second method call, above).

> Note, it may take a few moments for the dongle to reboot the first time.  This REDHAWK Device issues a cold start message to the dongle in an effort to ensure it does boot to a good state ready to output NMEA strings.

At this point once you've verified the device can read from your interface, issue `gps.stop()` and exit the python shell.  Then feel free to `make install` the Device to the Target SDR for integration in a node.

## Usage

The REDHAWK Device implements the Frontend GPS IDL and only has one controllable property, `serial_port`, for accessing the serial stream.  The default is `/dev/ttyUSB0`.  Ensure the user account that will be running the node executing this device has readwrite access to this location. 

