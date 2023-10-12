//
// Created by krawi on 28.11.2020.
//

#ifndef ANALYSINGSHEEPBEHAVIOUR_HEADERS_H
#define ANALYSINGSHEEPBEHAVIOUR_HEADERS_H


#include <time.h>


typedef struct gps_data * node_pointer ;

// structure for storing data from Collar files
typedef struct gps_data {
    double latitude;
    double longitude;
    struct tm date_time;
    node_pointer next;
} data;

typedef struct default_config * config_pointer;
// structure for storing information from configuration file
typedef struct default_config{
    char data_name[20];
    double movement_first;
    double movement_second;
    double max_speed;
    int num_bars;
    double range_lon_first;
    double range_lon_second;
    double range_lat_first;
    double range_lat_second;
}config;

enum State {Stationary , Foraging , Moving , Implausible} ;

//functions for creating and inserting data to list
node_pointer create_data_node (double latitude, double longitude, int day, int month, int year, int hour, int min, int seconds);
void insert_data_at_bottom (node_pointer * ptr_to_existing_head, node_pointer new_node_ptr);
void display_list_of_data (node_pointer list_ptr);
// reading and handling data and creating movements
node_pointer reading_from_file(FILE * fp);
void generate_movement(node_pointer list_ptr, config_pointer config_str_ptr);
double distance(double first_lat, double second_lat, double first_lng, double seconds_lng);
char* getState(enum State state);
// functions handling config files
config_pointer reading_config(FILE * config_file);
config_pointer change_config(config_pointer config_str_ptr);
void save_new_configuration_file(config_pointer changed_config_file);

void createTestPlot(config_pointer ptr);
#endif //ANALYSINGSHEEPBEHAVIOUR_HEADERS_H
