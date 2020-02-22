# MQTT Client Module

Scilab MQTT Client Module with PAHO Library

## Getting Started


### Prerequisites

1. Scilab 6.0.x or Scilab 6.1.x

### Installing

The module could be easily install from the Scilab atoms portal by using command:

--> atomsInstall('bytecode_mqtt'); // Coming soon

or the offline version by replacing the input argument to the zip file name.

If you prefer to build then module, download the source and unzip it, just type in scilab:

```
--> exec("bytecode_mqtt_Path/builder.sce")
```

If the module is place in the "contrib" folder, it could be loaded from the "Toolboxes" menu. Otherwise, just type in scilab:

``` 
--> exec("bytecode_mqtt_path/loader.sce"); 
```

bytecode_mqtt_Path is where this file is.

### EXAMPLES and DEMOS
 To see some examples type in scilab:

--> help 

## Features
* mqtt_pub
* mqtt_sub

## Revisions

### REVISION NOTES 1.0
* Update for release 
* Change module name

### REVISION NOTES 0.1
* Initial Version with Synchonize publish and subscribe 
* Only Support Public MQTT

## To-Do

## Version

This is the Revision 1.0 of bytecode_mqtt toolbox for Scilab 6.0.x

## Authors

Tan Chin Luh (ByteCode Malaysia)

## License

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
