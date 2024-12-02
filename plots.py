import pandas as pd
import matplotlib.pyplot as plt

# #########
# # HashMap
# #########
# # Load the data
# data = pd.read_csv("hashmap_operations.csv")

# # Plot insertion time
# plt.figure(figsize=(8, 5))
# plt.plot(data["Array Size"], data["Insert Time (seconds)"], marker='o', color='blue', label="Insertion Time")
# plt.title("HashMap Insertion Performance")
# plt.xlabel("Array Size")
# plt.ylabel("Time (seconds)")
# plt.grid()
# plt.legend()
# plt.savefig("hashmap_insertion_plot.png", dpi=300, bbox_inches='tight')
# print("Graph saved as hashmap_insertion_plot.png")
# plt.show()

# # Plot deletion time
# plt.figure(figsize=(8, 5))
# plt.plot(data["Array Size"], data["Delete Time (seconds)"], marker='s', color='red', label="Deletion Time")
# plt.title("HashMap Deletion Performance")
# plt.xlabel("Array Size")
# plt.ylabel("Time (seconds)")
# plt.grid()
# plt.legend()
# plt.savefig("hashmap_deletion_plot.png", dpi=300, bbox_inches='tight')
# print("Graph saved as hashmap_deletion_plot.png")
# plt.show()

# # Plot search time
# plt.figure(figsize=(8, 5))
# plt.plot(data["Array Size"], data["Search Time (seconds)"], marker='^', color='green', label="Search Time")
# plt.title("HashMap Search Performance")
# plt.xlabel("Array Size")
# plt.ylabel("Time (seconds)")
# plt.grid()
# plt.legend()
# plt.savefig("hashmap_search_plot.png", dpi=300, bbox_inches='tight')
# print("Graph saved as hashmap_search_plot.png")
# plt.show()

# #############
# # HashMapTree
# #############
# # Load the data
# data = pd.read_csv("hashmaptree_operations.csv")

# # Plot insertion time
# plt.figure(figsize=(8, 5))
# plt.plot(data["Array Size"], data["Insert Time (seconds)"], marker='o', color='blue', label="Insertion Time")
# plt.title("HashMapTree Insertion Performance")
# plt.xlabel("Array Size")
# plt.ylabel("Time (seconds)")
# plt.grid()
# plt.legend()
# plt.savefig("hashmaptree_insertion_plot.png", dpi=300, bbox_inches='tight')
# print("Graph saved as hashmaptree_insertion_plot.png")
# plt.show()

# # Plot deletion time
# plt.figure(figsize=(8, 5))
# plt.plot(data["Array Size"], data["Delete Time (seconds)"], marker='s', color='red', label="Deletion Time")
# plt.title("HashMapTree Deletion Performance")
# plt.xlabel("Array Size")
# plt.ylabel("Time (seconds)")
# plt.grid()
# plt.legend()
# plt.savefig("hashmaptree_deletion_plot.png", dpi=300, bbox_inches='tight')
# print("Graph saved as hashmaptree_deletion_plot.png")
# plt.show()

# # Plot search time
# plt.figure(figsize=(8, 5))
# plt.plot(data["Array Size"], data["Search Time (seconds)"], marker='^', color='green', label="Search Time")
# plt.title("HashMapTree Search Performance")
# plt.xlabel("Array Size")
# plt.ylabel("Time (seconds)")
# plt.grid()
# plt.legend()
# plt.savefig("hashmaptree_search_plot.png", dpi=300, bbox_inches='tight')
# print("Graph saved as hashmaptree_search_plot.png")
# plt.show()


import pandas as pd
import matplotlib.pyplot as plt

# Load the data
hashmap_data = pd.read_csv("hashmap_operations.csv")
hashmaptree_data = pd.read_csv("hashmaptree_operations.csv")

# Set up the figure and subplots
fig, axs = plt.subplots(3, 1, figsize=(10, 15), sharex=True)

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
axs[2].set_xlabel("Array Size")
axs[2].set_ylabel("Time (seconds)")
axs[2].grid()
axs[2].legend()

# Adjust layout and save the figure
plt.tight_layout()
plt.savefig("combined_hashmap_hashmaptree_performance.png", dpi=300, bbox_inches='tight')
print("Graph saved as combined_hashmap_hashmaptree_performance.png")
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