
#########
# HashMap
#########

import pandas as pd
import matplotlib.pyplot as plt

# Load the data
hashmap_data = pd.read_csv("hashmap_operations.csv")
hashmaptree_data = pd.read_csv("hashmaptree_operations.csv")

# Set up the figure and subplots
fig, axs = plt.subplots(3, 1, figsize=(10, 15), sharex=True)

# Define x-axis ticks and labels
x_ticks = [100, 1000, 10000, 100000, 1000000]
x_labels = [f"{int(x):,}" for x in x_ticks]  # Format labels with commas

# Insertion Performance
axs[0].plot(hashmap_data["Array Size"], hashmap_data["Insert Time (seconds)"],
            marker='o', color='blue', label="HashMap Insertion")
axs[0].plot(hashmaptree_data["Array Size"], hashmaptree_data["Insert Time (seconds)"],
            marker='o', color='orange', label="HashMapTree Insertion")
axs[0].set_title("Insertion Performance")
axs[0].set_ylabel("Time (seconds)")
axs[0].grid()
axs[0].legend()

# Deletion Performance
axs[1].plot(hashmap_data["Array Size"], hashmap_data["Delete Time (seconds)"],
            marker='s', color='red', label="HashMap Deletion")
axs[1].plot(hashmaptree_data["Array Size"], hashmaptree_data["Delete Time (seconds)"],
            marker='s', color='purple', label="HashMapTree Deletion")
axs[1].set_title("Deletion Performance")
axs[1].set_ylabel("Time (seconds)")
axs[1].grid()
axs[1].legend()

# Search Performance
axs[2].plot(hashmap_data["Array Size"], hashmap_data["Search Time (seconds)"],
            marker='^', color='green', label="HashMap Search")
axs[2].plot(hashmaptree_data["Array Size"], hashmaptree_data["Search Time (seconds)"],
            marker='^', color='brown', label="HashMapTree Search")
axs[2].set_title("Search Performance")
axs[2].set_xlabel("Array Size (log scale)")
axs[2].set_ylabel("Time (seconds)")
axs[2].grid()
axs[2].legend()

# Set x-axis ticks and scale
for ax in axs:
    ax.set_xscale("log")  # Use logarithmic scale for even spacing
    ax.set_xticks(x_ticks)
    ax.set_xticklabels(x_labels)  # Add formatted labels

# Adjust layout and save the figure
plt.tight_layout()
plt.savefig("combined_hashmap_hashmaptree_performance_log.png", dpi=300, bbox_inches='tight')
print("Graph saved as combined_hashmap_hashmaptree_performance_log.png")
plt.show()


#############
# HashMap Slots
#############
data = pd.read_csv("slot_distribution_multiple_sizes.csv")

# Array sizes to process
array_sizes = data["Array Size"].unique()

for size in array_sizes:
    subset = data[data["Array Size"] == size]

    # Plot histogram
    plt.figure(figsize=(12, 6))
    plt.bar(subset["Slot"], subset["Count"], color="skyblue", edgecolor="black")
    plt.title(f"HashMap Slot Distribution for Array Size {size}")
    plt.xlabel("Slot Index")
    plt.ylabel("Number of Elements")
    plt.grid(axis="y")

    # Save each histogram as a separate image
    output_image = f"slot_distribution_size_{size}.png"
    plt.savefig(output_image, dpi=300, bbox_inches="tight")
    print(f"Histogram for size {size} saved as {output_image}")

    plt.show()
    
    
#############
# HashMapTree Slots
#############
# Load the data
data = pd.read_csv("hashmaptree_slot_distribution.csv")

# Array sizes to process
array_sizes = data["Array Size"].unique()

for size in array_sizes:
    subset = data[data["Array Size"] == size]

    # Plot histogram
    plt.figure(figsize=(12, 6))
    plt.bar(subset["Slot"], subset["Count"], color="skyblue", edgecolor="black")
    plt.title(f"HashMapTree Slot Distribution for Array Size {size}")
    plt.xlabel("Slot Index")
    plt.ylabel("Number of Elements")
    plt.grid(axis="y")

    # Save each histogram as a separate image
    output_image = f"slot_distribution_tree_size_{size}.png"
    plt.savefig(output_image, dpi=300, bbox_inches="tight")
    print(f"Histogram for size {size} saved as {output_image}")

    plt.show()