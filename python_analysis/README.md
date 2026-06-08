import pandas as pd

data = pd.read_csv("../dataset/sample_battery_dataset.csv")

print("Battery Dataset Summary")
print(data.describe())

print("\nAverage Voltage:", data["Voltage"].mean())
print("Average Temperature:", data["Temperature"].mean())
