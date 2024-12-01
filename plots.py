import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv("hashmap_operations.csv")

# Plot insertion time
plt.figure(figsize=(8, 5))
plt.plot(data["Array Size"], data["Insert Time (seconds)"], marker='o', color='blue', label="Insertion Time")
plt.title("HashMap Insertion Performance")
plt.xlabel("Array Size")
plt.ylabel("Time (seconds)")
plt.grid()
plt.legend()
plt.savefig("hashmap_insertion_plot.png", dpi=300, bbox_inches='tight')
print("Graph saved as hashmap_insertion_plot.png")
plt.show()

# Plot deletion time
plt.figure(figsize=(8, 5))
plt.plot(data["Array Size"], data["Delete Time (seconds)"], marker='s', color='red', label="Deletion Time")
plt.title("HashMap Deletion Performance")
plt.xlabel("Array Size")
plt.ylabel("Time (seconds)")
plt.grid()
plt.legend()
plt.savefig("hashmap_deletion_plot.png", dpi=300, bbox_inches='tight')
print("Graph saved as hashmap_deletion_plot.png")
plt.show()

# Plot search time
plt.figure(figsize=(8, 5))
plt.plot(data["Array Size"], data["Search Time (seconds)"], marker='^', color='green', label="Search Time")
plt.title("HashMap Search Performance")
plt.xlabel("Array Size")
plt.ylabel("Time (seconds)")
plt.grid()
plt.legend()
plt.savefig("hashmap_search_plot.png", dpi=300, bbox_inches='tight')
print("Graph saved as hashmap_search_plot.png")
plt.show()


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