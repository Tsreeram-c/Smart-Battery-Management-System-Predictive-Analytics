import pandas as pd

data = pd.read_csv("../dataset/sample_battery_dataset.csv")

max_temp = data["Temperature"].max()
min_voltage = data["Voltage"].min()

print("Battery Health Report")
print("---------------------")
print("Maximum Temperature:", max_temp)
print("Minimum Voltage:", min_voltage)

if max_temp > 60:
    print("Warning: Thermal stress detected")

if min_voltage < 23:
    print("Warning: Deep discharge condition detected")
