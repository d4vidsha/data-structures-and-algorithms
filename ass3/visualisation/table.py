import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# config =======================================================================

WITH_DEADENDS = True
X_NAME = "Grid Size"
Y_NAME = "Number of Generated Nodes"

# end of config ================================================================

if WITH_DEADENDS:
    grid_size = [6, 8, 9, 9, 10, 10, 11, 5, 6, 7, 8, 9, 5]
    num_generated = [74, 5932, 126993, 34888, 965527, 10651, 872191, 17, 128, 213, 2219, 7285, 103]
else:
    grid_size = [6, 10, 5, 6, 7, 8, 9, 5]
    num_generated = [202, 317532, 18, 283, 3317, 409726, 549827, 1689]

# Create a dataframe
data_plot = pd.DataFrame({
        X_NAME: grid_size,
        Y_NAME: num_generated
    })

# Plot the data
sns.lineplot(x=X_NAME, y=Y_NAME, data=data_plot)
plt.show()