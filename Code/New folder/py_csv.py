import serial
import csv
import time

# Set up the serial connection
serial_port = 'COM4'  # Change this to your Arduino port
baud_rate = 9600
output_file = 'ultrasound_data.csv'

try:
    # Open the serial port
    with serial.Serial(serial_port, baud_rate, timeout=2) as ser:
        print(f"Connected to {serial_port} at {baud_rate} baud")

        # Open CSV file for writing
        with open(output_file, mode='w', newline='') as file:
            writer = csv.writer(file)
            # Write CSV header
            writer.writerow(["Time (s)", "Pressure (mmHg)", "Amplitude Ratio", "IOP"])
            
            start_time = time.time()

            # Continuously read from serial and save data
            while True:
                try:
                    # Read a line from the serial port
                    line = ser.readline().decode('utf-8').strip()
                    print(f"Received: {line}")
                    
                    # Split data into relevant variables
                    data = line.split(',')
                    if len(data) == 3:
                        pressure_mmhg = float(data[0])
                        amplitude_ratio = float(data[1])
                        iop = float(data[2])

                        # Calculate elapsed time
                        elapsed_time = time.time() - start_time

                        # Write data to CSV
                        writer.writerow([elapsed_time, pressure_mmhg, amplitude_ratio, iop])
                        print(f"Saved: {elapsed_time:.2f}s, {pressure_mmhg} mmHg, {amplitude_ratio}, {iop}")
                    else:
                        print("Invalid data format, skipping...")

                except KeyboardInterrupt:
                    print("Data logging stopped by user.")
                    break
                except Exception as e:
                    print(f"Error: {e}")

except serial.SerialException:
    print(f"Could not open serial port {serial_port}. Check the connection.")
