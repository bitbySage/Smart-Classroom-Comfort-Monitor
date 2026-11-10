#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILENAME "temperature_log.csv"

// Function to simulate turning the LED ON/OFF
void set_led_status(bool is_warning) {
    if (is_warning) {
        printf(" [LED: ON - WARNING]\n");
    } else {
        printf(" [LED: OFF - NORMAL]\n");
    }
}

int main() {
    // Default acceptable range per project requirements
    float min_temp = 68.0;
    float max_temp = 76.0;
    
    float temp_input;
    float sum_temps = 0.0;
    int count = 0;
    char choice;

    // Open file for appending temperature logs
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Error opening log file");
        return 1;
    }

    printf("=== Smart Classroom Comfort Monitor ===\n");
    printf("Default Acceptable Range: %.1f°F - %.1f°F\n\n", min_temp, max_temp);

    // Main data-entry loop
    while (true) {
        printf("Enter classroom temperature in °F (or enter 999 to quit): ");
        if (scanf("%f", &temp_input) != 1) {
            printf("Invalid input. Please enter a numerical value.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        // Exit condition
        if (temp_input == 999.0) {
            break;
        }

        sum_temps += temp_input;
        count++;

        // Determine status (NORMAL or WARNING)
        bool is_warning = (temp_input < min_temp || temp_input > max_temp);

        printf("Temperature: %.1f°F -> Status: ", temp_input);
        if (is_warning) {
            printf("WARNING");
        } else {
            printf("NORMAL");
        }
        
        // Trigger LED
        set_led_status(is_warning);

        // Save reading and status to file
        fprintf(file, "Temperature: %.1f°F - Status: %s\n", temp_input, is_warning ? "WARNING" : "NORMAL");
        fflush(file); 
    }

    // Calculate and display average if readings were entered
    if (count > 0) {
        float average = sum_temps / count;
        printf("\n--- Summary ---\n");
        printf("Total readings recorded: %d\n", count);
        printf("Average temperature: %.2f°F\n", average);
        
        fprintf(file, "\nSummary: Total Readings = %d, Average Temperature = %.2f°F\n", count, average);
    } else {
        printf("\nNo temperature readings were recorded.\n");
    }

    // Close the file
    fclose(file);
    printf("Data successfully saved to %s. Program exited.\n", FILENAME);

    return 0;
}