# Script that plots the data from the csv files and saves them as png files
# Takes the first column as the x-axis and the rest as the y-axis
# The labels are inferred from the column names on the first row after comments
import sys
from os import path
import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# If no filename passed, exit
if len(sys.argv) < 2:
	print("Please pass the filename as an argument.")
	print("Only files in the output folder can be plotted.")
	exit()

# Find the path of CSV file
basepath = path.dirname(__file__)
filepath = path.abspath(path.join(basepath, "..", "output", sys.argv[1]))

# Read the CSV file using pandas
data = pd.read_csv(filepath, comment='#', index_col=0)

# Plot the data
sns.set_style("darkgrid")
sns.lineplot(data=data)
plt.show()