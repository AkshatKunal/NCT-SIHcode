import serial
import csv
import time

# Initialize serial communication
ser = serial.Serial('COM9', 9600, timeout=1)  # Update to your COM port
ser.flush()

# CSV file setup
csv_file = "pressure_data10.csv"
fields = ["pressure_mmHg", "sensVal", "waveAmplitude"]

# Create the CSV file and write the header
with open(csv_file, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(fields)

value_count = 0
max_values = 1000

try:
    print("Logging data... Press Ctrl+C to stop.")
    while value_count < max_values:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            print(line)  # Display data on the console
            data = line.split(',')
            if len(data) == 4:
                # Save data to CSV
                with open(csv_file, "a", newline="") as f:
                    writer = csv.writer(f)
                    writer.writerow(data)
                value_count += 1

    print(f"Reached {max_values} values. Data logging stopped. File saved as {csv_file}")
    ser.close()

except KeyboardInterrupt:
    print(f"Data logging interrupted. File saved as {csv_file}")
    ser.close()
