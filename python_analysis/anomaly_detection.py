import pandas as pd

data = pd.read_csv("../dataset/sample_battery_dataset.csv")

threshold = 40

anomalies = data[data["Temperature"] > threshold]

print("Potential Anomalies:")
print(anomalies)
