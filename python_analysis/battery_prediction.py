import pandas as pd
from sklearn.linear_model import LinearRegression

data = pd.read_csv("../dataset/sample_battery_dataset.csv")

X = data[["Time"]]
y = data["Temperature"]

model = LinearRegression()
model.fit(X, y)

future_time = [[20]]

predicted_temp = model.predict(future_time)

print("Predicted Temperature at Time 20:")
print(predicted_temp[0])
