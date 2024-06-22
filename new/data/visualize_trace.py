import pandas as pd
import matplotlib.pyplot as plt

trace = "retail.csv"
column_names = ["Timestamp", "Key", "Volume"]

df = pd.read_csv(trace, names=column_names, nrows = 100000)

df.groupby("Key").size().plot(kind="hist", bins=df["Key"].nunique(), color='skyblue', edgecolor='black')

plt.xlabel("Keys")
plt.ylabel("Key count")
plt.title("Distribution of " + trace)

plt.show()

df.groupby("Key")["Volume"].sum().plot(kind="hist", bins=df["Key"].nunique(), color='skyblue', edgecolor='black')

plt.xlabel("Keys")
plt.ylabel("Aggregate volume")
plt.title("Distribution of " + trace)

plt.show()

"""
aggregate_volumes = {}
max_key = 0

for i, row in df.iterrows():
    aggregate_volumes[row["Key"]] = aggregate_volumes.get(row["Key"], 0) + row["Volume"]
    max_key = max(max_key, row["Key"])


# Plotting a basic histogram
plt.hist([aggregate_volumes.get(i, 0) for i in range(max_key + 1)], bins=len(aggregate_volumes), color='skyblue', edgecolor='black')
 
# Adding labels and title
plt.xlabel('Key')
plt.ylabel('Aggregate volume')
plt.title('Kosarak Distribution')
 
# Display the plot
plt.show()
"""
