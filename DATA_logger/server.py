import requests
import time

ESP32_IP = "192.168.1.45"  # Replace with your ESP32 IP
filename = "sensor_data.csv"

while True:
    try:
        r = requests.get(f"http://{ESP32_IP}/data.csv")
        with open(filename, "w") as f:
            f.write(r.text)
        print("CSV updated on PC")
    except Exception as e:
        print("Error:", e)

    time.sleep(5)  # Fetch every 5 seconds
