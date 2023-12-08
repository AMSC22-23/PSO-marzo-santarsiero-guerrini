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

# Compose the title from the comments
title = ""
description = "("
with open(filepath, 'r') as f:
	title = f.readline()[1:].strip().replace('_', ' ').capitalize()
	for line in f:
		if line[0] == '#':
			description += line[1:].strip() + ", "
	description = description[:-2] + ")"
# Plot the data
sns.set_style("darkgrid")
ax = sns.lineplot(data=data)
ax.set_yscale('symlog', linthresh=1e-200)	# Needed for having a log scale showing 0
# Set description below title
ax.text(x=0.5, y=1.1, s=title, fontsize=16, weight='bold', ha='center', va='bottom', transform=ax.transAxes)
ax.text(x=0.5, y=1.05, s=description, fontsize=8, alpha=0.75, ha='center', va='bottom', transform=ax.transAxes)

plt.show()