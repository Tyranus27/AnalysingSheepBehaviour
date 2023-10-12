//
// Created by krawi on 28.11.2020.
//

#include "stdio.h"
#include "headers.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"


#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
//#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)


node_pointer create_data_node(double latitude, double longitude, int day, int month, int year, int hour, int min, int seconds) {
    node_pointer new_node_pointer;
    new_node_pointer = malloc(sizeof(data));
    struct tm time_pointer;

    if (new_node_pointer == NULL)
        return NULL;
    else {

        time_pointer.tm_mday = day;
        time_pointer.tm_mon = month;
        time_pointer.tm_year = year;

        time_pointer.tm_hour = hour;
        time_pointer.tm_min = min;
        time_pointer.tm_sec = seconds;

        time_pointer.tm_isdst = 1;

        new_node_pointer->latitude = latitude;
        new_node_pointer->longitude = longitude;
        new_node_pointer->date_time = time_pointer;
        new_node_pointer->next = NULL;
        return new_node_pointer;
    }

}

void insert_data_at_bottom(node_pointer *ptr_to_existing_head, node_pointer new_node_ptr) {
    node_pointer *temp_ptr;
    temp_ptr = ptr_to_existing_head;

    while (*temp_ptr != NULL) {
        temp_ptr = &((*temp_ptr)->next);
    }

    new_node_ptr->next = *temp_ptr;
    *temp_ptr = new_node_ptr;
}

// function for displaying linked list of data
//void display_list_of_data(node_pointer list_ptr)
/*{
   int i = 0;
   while (list_ptr != NULL) {
       i++;

       printf("Number: %d  Latitude: %lf, Longitude: %lf, Date: %d/%d/%d, Time: %d:%d:%d \n", i, list_ptr->latitude,
              list_ptr->longitude, list_ptr->date_time.tm_mday, list_ptr->date_time.tm_mon,
              list_ptr->date_time.tm_year, list_ptr->date_time.tm_hour, list_ptr->date_time.tm_min,
              list_ptr->date_time.tm_sec);
       list_ptr = list_ptr->next;
   }
}*/

node_pointer reading_from_file(FILE *fp) {
    // pointers to data structure
    node_pointer head = NULL;
    node_pointer temp_pointer;
    // variables to store values for comparing
    double latitude, longitude;
    double previous_longitude = 0, previous_latitude = 0;
    // variables for times and date
    int day, month, year, hour, minutes, seconds;
    // char arrays for reading from file
    char data_line[45], longitude_array[15], latitude_array[15], day_array[3], month_array[3], year_array[5], hour_array[3], minutes_array[3], seconds_array[3];
    // variables to store number of specific lines
    int previous_time_date[6], number_of_lines = 0, data_line_iteration, number_of_valid_records = 0, number_of_invalid_records = 0, number_of_records_in_linked_list = 0;
    // others
    int a = 0, i, repeat = 0;
    char *pointer;

    while ((fgets(data_line, 45, fp) != NULL)) {
        number_of_lines++;
        data_line_iteration = 0;
        i = 0;
        if (data_line[0] > 48 && data_line[0] < 58) {

            // latitude
            do {
                latitude_array[i] = data_line[data_line_iteration];
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration] != ',');
            latitude = strtod(latitude_array, &pointer);

            i = 0;
            // longitude
            do {
                longitude_array[i] = data_line[data_line_iteration + 2];
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 2] != ',');
            longitude = strtod(longitude_array, &pointer);

            i = 0;
            // day

            do {
                day_array[i] = data_line[data_line_iteration + 4];
                day_array[i + 1] = '\0';
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 4] != '/');
            i = 0;
            // month
            do {
                month_array[i] = data_line[data_line_iteration + 5];
                month_array[i + 1] = '\0';
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 5] != '/');

            i = 0;
            // year
            do {
                year_array[i] = data_line[data_line_iteration + 6];
                year_array[i + 1] = '\0';
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 6] != ',');

            i = 0;
            // hours
            do {
                hour_array[i] = data_line[data_line_iteration + 8];
                hour_array[i + 1] = '\0';
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 8] != ':');

            i = 0;
            // minutes

            do {
                minutes_array[i] = data_line[data_line_iteration + 9];
                minutes_array[i + 1] = '\0';
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 9] != ':');

            i = 0;
            // seconds

            do {
                seconds_array[i] = data_line[data_line_iteration + 10];
                seconds_array[i + 1] = '\0';
                i++;
                data_line_iteration++;
            } while (data_line[data_line_iteration + 10] != '\r');

            // assigning content of character arrays to variables with appropriate type
            day = atoi(day_array);
            month = atoi(month_array);
            year = atoi(year_array);
            hour = atoi(hour_array);
            minutes = atoi(minutes_array);
            seconds = atoi(seconds_array);

            // assigning value of latitude and longitude for comparing
            number_of_valid_records++;
            if (repeat > 0) {
                // conditional block to check if there was a duplicated coordinates in file
                if ((latitude != previous_latitude || longitude != previous_longitude)) {
                    if (a == 0) {
                        temp_pointer = create_data_node(previous_latitude, previous_longitude, previous_time_date[0],
                                                        previous_time_date[1], previous_time_date[2],
                                                        previous_time_date[3],
                                                        previous_time_date[4], previous_time_date[5]);
                        temp_pointer->next = head;
                        head = temp_pointer;

                        previous_latitude = latitude;
                        previous_longitude = longitude;
                        previous_time_date[0] = day;
                        previous_time_date[1] = month;
                        previous_time_date[2] = year;
                        previous_time_date[3] = hour;
                        previous_time_date[4] = minutes;
                        previous_time_date[5] = seconds;
                        a++;
                        number_of_records_in_linked_list++;
                        continue;

                    } else {
                        temp_pointer = create_data_node(previous_latitude, previous_longitude, previous_time_date[0],
                                                        previous_time_date[1], previous_time_date[2],
                                                        previous_time_date[3],
                                                        previous_time_date[4], previous_time_date[5]);
                        insert_data_at_bottom(&head, temp_pointer);

                        previous_latitude = latitude;
                        previous_longitude = longitude;
                        previous_time_date[0] = day;
                        previous_time_date[1] = month;
                        previous_time_date[2] = year;
                        previous_time_date[3] = hour;
                        previous_time_date[4] = minutes;
                        previous_time_date[5] = seconds;
                        number_of_records_in_linked_list++;
                        //continue;

                    }
                } else {
                    previous_latitude = latitude;
                    previous_longitude = longitude;
                    previous_time_date[0] = day;
                    previous_time_date[1] = month;
                    previous_time_date[2] = year;
                    previous_time_date[3] = hour;
                    previous_time_date[4] = minutes;
                    previous_time_date[5] = seconds;
                    continue;
                }
            } else {
                previous_latitude = latitude;
                previous_longitude = longitude;
                previous_time_date[0] = day;
                previous_time_date[1] = month;
                previous_time_date[2] = year;
                previous_time_date[3] = hour;
                previous_time_date[4] = minutes;
                previous_time_date[5] = seconds;
                repeat++;
                continue;
            }


        } else {
            number_of_invalid_records++;
            continue;
        }


    }
    temp_pointer = create_data_node(latitude, longitude, day, month, year, hour, minutes, seconds);
    insert_data_at_bottom(&head, temp_pointer);
    number_of_records_in_linked_list++;

    printf("\n");
    printf("Records analyse from provided file\n");
    printf("\n");
    printf("Number of lines in file in total: %d\n", number_of_lines);
    printf("Number of invalid records: %d\n", number_of_invalid_records);
    printf("Number of skipped records: %d\n", (number_of_valid_records - number_of_records_in_linked_list));
    printf("Number of valid and unique records: %d\n", number_of_records_in_linked_list);
    printf("\n");
    printf("\n");
    fclose(fp);
    return head;
}

char *getState(enum State state) {
    switch (state) {


        case Stationary:
            return "Stationary";
        case Foraging:
            return "Foraging";
        case Moving:
            return "Moving";
        case Implausible:
            return "Implausible";
        default:
            return "Nothing";
    }
}

void generate_movement(node_pointer list_ptr, config_pointer config_str_ptr) {
    FILE *csv_file;
    csv_file = fopen("Movement data.csv", "w");
    if (csv_file == NULL) {
        printf("File doesn't exist\n");
    }
    csv_file = freopen("Movement data.csv", "a", csv_file);
    time_t time1, time2;
    char *state;
    int movement = 0;
    double speed, meters, first_lat, first_lng, second_lat, second_lng;
    int time, stationary_time = 0, foraging_time = 0, moving_time = 0, implausible_time = 0;
    node_pointer movement_start = list_ptr;
    node_pointer movement_end = list_ptr->next;
    node_pointer test = list_ptr;
    while (1) {

        test = test->next;
        if (test == NULL) {
            break;
        }
        // assigning data from linked list to local variables
        // creating time from tm structure for every movement
        first_lat = movement_start->latitude;
        first_lng = movement_start->longitude;
        time1 = mktime(&movement_start->date_time);

        second_lat = movement_end->latitude;
        second_lng = movement_end->longitude;
        time2 = mktime(&movement_end->date_time);
        //calculating distance between two coordinates using distance() function
        meters = distance(first_lat, second_lat, first_lng, second_lng);
        time = difftime(time2, time1);
        speed = meters / time;
        if (speed > 50) {
            movement_start = movement_end;
            movement_end = movement_end->next;
            continue;
        } else {
            movement++;
            // condition block for refining .csv file to meet demands of configuration file
            if ((movement_start->longitude > config_str_ptr->range_lon_first &&
                 movement_end->longitude < config_str_ptr->range_lon_second) &&
                (movement_start->latitude > config_str_ptr->range_lat_first &&
                 movement_end->latitude < config_str_ptr->range_lat_second) &&
                (time > config_str_ptr->movement_first && time < config_str_ptr->movement_second) &&
                (speed < config_str_ptr->max_speed)) {
                // condition block using enumerated structure for finding state of a sheep
                if (speed < 0.02 && speed > 0) {
                    state = getState(Stationary);
                    stationary_time += time;
                } else if (speed > 0.02 && speed < 0.33) {
                    state = getState(Foraging);
                    foraging_time += time;
                } else if (speed > 0.33 && speed < 12.00) {
                    state = getState(Moving);
                    moving_time += time;
                } else if (speed > 12) {
                    state = getState(Implausible);
                    implausible_time += time;
                }

                // input refined data to file
                fprintf(csv_file, "Movement: %d, %d/%d/%d, %d:%d:%d, %lf, %lf, %lf, %lf, %lfm, %ds, %0.2lfm/s, %s \n",
                        movement,
                        movement_start->date_time.tm_mday, movement_start->date_time.tm_mon,
                        movement_start->date_time.tm_year, movement_start->date_time.tm_hour,
                        movement_start->date_time.tm_min,
                        movement_start->date_time.tm_sec, first_lat, first_lng, second_lat, second_lng, meters, time,
                        speed,
                        state);
            } else movement--;
            movement_start = movement_end;
            movement_end = movement_end->next;
        }
    }
    fclose(csv_file);

    printf("Total times for each category: \n");
    printf("\n");
    printf("Stationary : %ds\n", stationary_time);
    printf("Foraging : %ds\n", foraging_time);
    printf("Moving : %ds\n", moving_time);
    printf("Implausible : %ds\n", implausible_time);
    printf("\n");

}

double distance(double first_lat, double second_lat, double first_lng, double seconds_lng) {

    double lon1, lon2, lat1, lat2;


    lon1 = degToRad(first_lng);
    lat1 = degToRad(first_lat);

    lon2 = degToRad(seconds_lng);
    lat2 = degToRad(second_lat);


    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2)
               + cos(lat1) * cos(lat2)
                 * pow(sin(dlon / 2), 2);

    double c = 2 * asin(sqrt(a));

    // Radius of earth in kilometers. Use 3956
    // for miles
    double r = 6371;

    // calculate the result (in m)
    return ((c * r) * 1000);


}

config_pointer reading_config(FILE *config_file) {
    config_pointer config_str_ptr;
    config_str_ptr = malloc(sizeof(config));

    int c = 0;
    char buff[20];

    do {
        fscanf(config_file, "%s", buff);
        getc(config_file);
        getc(config_file);
        getc(config_file);
        if (c == 0) {
            getc(config_file);
            fscanf(config_file, "%13[^\"]", config_str_ptr->data_name);
            getc(config_file);
            c++;
        } else if (c == 1) {
            getc(config_file);
            fscanf(config_file, "%lf", &config_str_ptr->movement_first);
            getc(config_file);
            fscanf(config_file, "%lf", &config_str_ptr->movement_second);
            getc(config_file);
            c++;
        } else if (c == 2) {
            fscanf(config_file, "%lf", &config_str_ptr->max_speed);
            c++;
        } else if (c == 3) {
            fscanf(config_file, "%d", &config_str_ptr->num_bars);
            c++;
        } else if (c == 4) {
            getc(config_file);
            fscanf(config_file, "%lf", &config_str_ptr->range_lon_first);
            getc(config_file);
            fscanf(config_file, "%lf", &config_str_ptr->range_lon_second);
            getc(config_file);
            c++;
        } else if (c == 5) {
            getc(config_file);
            fscanf(config_file, "%lf", &config_str_ptr->range_lat_first);
            getc(config_file);
            fscanf(config_file, "%lf", &config_str_ptr->range_lat_second);
            getc(config_file);
            c++;
        }


    } while (c != 6);

    return config_str_ptr;

}

config_pointer change_config(config_pointer config_str_ptr) {
    char option;
    int exit = 0;

    do {
        printf("*************************************************************************************************\n");
        printf("This is configuration file\n");
        printf("data_file_name = \"%s\"\nmovement_duration = <%lf:%lf>\nmaximum_speed = %lf\nnum_bars = %d\nrange_lon = <%lf:%lf>\nrange_lat = <%lf:%lf>\n",
               config_str_ptr->data_name,
               config_str_ptr->movement_first, config_str_ptr->movement_second, config_str_ptr->max_speed,
               config_str_ptr->num_bars, config_str_ptr->range_lon_first, config_str_ptr->range_lon_second,
               config_str_ptr->range_lat_first, config_str_ptr->range_lat_second);

        printf("What would you like to change?\n");
        printf("\n");
        printf("1. Change file name\n");
        printf("2. Change movement duration\n");
        printf("3. Change maximum speed\n");
        printf("4. Change number of bars\n");
        printf("5. Change range of longitude\n");
        printf("6. Change range of latitude\n");
        printf("7. Exit\n");
        printf("\n");


        scanf(" %c", &option);

        switch (option) {
            case '1':
                printf("Insert new data file name: \n");
                scanf("%s", config_str_ptr->data_name);
                break;
            case '2':
                printf("Insert new range for movement duration: \n");
                printf("First: ");
                scanf("%lf", &config_str_ptr->movement_first);
                printf("Second: ");
                scanf("%lf", &config_str_ptr->movement_second);
                break;
            case '3':
                printf("Insert new maximum speed value: \n");
                scanf(" %lf", &config_str_ptr->max_speed);
                break;
            case '4':
                printf("Insert number of bars: ");
                scanf("%d", &config_str_ptr->num_bars);
                break;
            case '5':
                printf("Insert new range for longitude: \n");
                printf("First value: ");
                scanf("%lf", &config_str_ptr->range_lon_first);
                printf("Second value: ");
                scanf("%lf", &config_str_ptr->range_lon_second);
                break;

            case '6':
                printf("Insert new range for latitude: \n");
                printf("First value: ");
                scanf("%lf", &config_str_ptr->range_lat_first);
                printf("Second value: ");
                scanf("%lf", &config_str_ptr->range_lat_second);
                break;
            case '7':
                exit = 1;
            default:
                break;
        }
    } while (exit != 1);
    return config_str_ptr;
}

void save_new_configuration_file(config_pointer changed_config_file) {

    FILE *new_config_file, *custom;
    char new_filename[30];
    char overwrite_filename[] = "custom_config_file.txt";
    char default_config[] = "default_config_file.txt";
    int option;
    printf("1. If you want to overwrite custom config file\n");
    printf("2. If you want create new file\n");
    scanf("%d", &option);

    if (option == 1) {
        custom = fopen(overwrite_filename, "w");
        fprintf(custom,
                "data_file_name = \"%s\"\nmovement_duration = <%lf:%lf>\nmaximum_speed = %lf\nnum_bars = %d\nrange_lon = <%lf:%lf>\nrange_lat = <%lf:%lf>",
                changed_config_file->data_name, changed_config_file->movement_first,
                changed_config_file->movement_second, changed_config_file->max_speed, changed_config_file->num_bars,
                changed_config_file->range_lon_first, changed_config_file->range_lon_second,
                changed_config_file->range_lat_first, changed_config_file->range_lat_second);
        fclose(custom);

    } else if (option == 2) {
        printf("Provide file name to save new config file: \n");
        scanf("%s", new_filename);
        new_config_file = fopen(new_filename, "w+r");
        if (new_config_file == NULL || strcmp(new_filename, default_config)==0) {
            printf("File cannot be created\n");
            printf("\n");
        } else {
        new_config_file = freopen(new_filename,"w",new_config_file);
            fprintf(new_config_file,
                    "data_file_name = \"%s\"\nmovement_duration = <%lf:%lf>\nmaximum_speed = %lf\nnum_bars = %d\nrange_lon = <%lf:%lf>\nrange_lat = <%lf:%lf>",
                    changed_config_file->data_name, changed_config_file->movement_first,
                    changed_config_file->movement_second, changed_config_file->max_speed, changed_config_file->num_bars,
                    changed_config_file->range_lon_first, changed_config_file->range_lon_second,
                    changed_config_file->range_lat_first, changed_config_file->range_lat_second);

        }
        fclose(new_config_file);
    }
}

void createTestPlot(config_pointer ptr) {

    char filename[25];
    int sizex = 1024;
    int sizey = 768;

    char xlabel[] = "\"Longitude\"";
    char ylabel[] = "\"Latitude\"";
    char cblabel[] = "\"Speed\"";
    char data[] = "\"Movement data.csv\"";
    char command[30];
    char gnu[30];
    char gnu_format[] = ".gnuplot";
    FILE *datafile;


    printf("Provide name of plot file: \n");

    scanf("%s", filename);
    strcat(filename, gnu_format);


    strcpy(gnu, filename);
    strcpy(command, "gnuplot ");
    strcat(command, gnu);


    if ((datafile = fopen(filename, "w")) == NULL) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    fprintf(datafile, "set terminal svg noenhanced linewidth 0.75 size %i,%i\n", sizex, sizey);

    fprintf(datafile, "set output \"%s.svg\"\n", filename);

    fprintf(datafile, "set title \"This is plot using configuration file\"\n");

    fprintf(datafile, "set autoscale\n");

    fprintf(datafile, "set xlabel %s\nshow xlabel\n", xlabel);
    fprintf(datafile, "set ylabel %s\nshow ylabel\n", ylabel);

    fprintf(datafile, "set cblabel %s\n", cblabel);

    fprintf(datafile, "set palette defined (0 \"black\", 0.02 \"blue\", 0.33 \"red\", 12.1 \"yellow\")\n");

    fprintf(datafile, "set datafile separator ','\n");
    fprintf(datafile,
            "plot %s using 5:4:10 with lines lc palette z title \"%s\", %s using 7:6:10  with lines lc palette z title \"%s\"\n",
            data, ptr->data_name, data, ptr->data_name);

    fflush(datafile);
    fclose(datafile);

    system(command);


}