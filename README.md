# AnalysingSheepBehaviour

Analysing Sheep Behaviour program is program for handling movement of sheeps using data from gps devices.

[main](https://github.com/Tyranus27/AnalysingSheepBehaviour/blob/ad5bf23d4fffb84d5e014e8c9ea378b2e0157706/main.c) file contain whole menu and allow user to use various of features
[functions](https://github.com/Tyranus27/AnalysingSheepBehaviour/blob/ad5bf23d4fffb84d5e014e8c9ea378b2e0157706/functions.c) file contains all functions used to run this project
[headers](https://github.com/Tyranus27/AnalysingSheepBehaviour/blob/ad5bf23d4fffb84d5e014e8c9ea378b2e0157706/headers.h) file contains function headers and data structures

To run this program correctly project directory must contain: some data file for example "Collar_12.txt", default_config_file.txt, and custom_config_file.txt

This program runs using data file with gps coordinates to create movements, also program need some configuration information from configuration file to refine .csv file to given boundries,
if we want to create plot for whole data, we have to create new configuration file with range big enough to cover every movement.

We can create new configuration file using program, all you need to do is to change current configuration file and then save to new file or overwrite custom_config_file.txt

After .csv file is created, program creates plot with given filename and create in project directory .svg file that can be open in browser 

If we want to run this program by command line, directory with main.c and functions.c must contain both configuration files and data file.
When running program in CLion cmake-build-debug directory must contain both configuration files and data file.

For creating plots the Gnuplot version 5.2 is used.
