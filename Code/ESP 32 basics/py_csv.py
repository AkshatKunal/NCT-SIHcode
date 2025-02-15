import serial
import csv
i = 0

# Configure the serial port (Update 'COM4' to match your port)
ser = serial.Serial('COM5', 115200, timeout=1)

# File to store the data
output_file = 'arduino_data3.csv'

# Open the file in append mode
with open(output_file, 'a', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)

    # Write the header row only once if the file is empty
    if csvfile.tell() == 0:
        csvwriter.writerow(['Raw Value', 'Voltage (V)', 'Current (mA)', 
                            'Receiver Ultrasound', 'Pressure (mmHg)'])

    print("Listening to Arduino. Press Ctrl+C to stop.")

    try:
        # Continuously read data from Arduino
        while True:
            raw_data = ser.readline()  # Read the raw data
            try:
                # Decode safely and strip any extra spaces or newlines
                data = raw_data.decode('utf-8', errors='ignore').strip()
                
                if data:  # If data is valid
                    print(data, end = ": Number: ")  # Display the data
                    print(i)
                    i= i+1
                    
                    # Split the data by the ": " separator
                    parts = data.split(": ")
                    
                    if len(parts) == 5:  # Ensure all parts exist
                        # Convert values to appropriate types for writing
                        raw_value = int(parts[0].strip())
                        voltage = float(parts[1].strip())
                        current = float(parts[2].strip())
                        ultrasound = float(parts[3].strip())
                        pressure = float(parts[4].strip())
                        
                        # Append the data to the CSV file
                        csvwriter.writerow([raw_value, voltage, current, ultrasound, pressure])
                        csvfile.flush()  # Ensure data is written to the file
            except Exception as e:
                print(f"Error processing data: {e}")
    except KeyboardInterrupt:
        print("\nTerminated by user.")

print(f"Data stored in {output_file}")
ser.close()
