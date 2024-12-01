#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include "HashMap.hpp"

// Function to generate a random array of integers
int* rand_arr(long length, int min_val, int max_val) {
    int* arr = new int[length];

    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distri(min_val, max_val);

    // Populate the array with random numbers
    for (long i = 0; i < length; i++) {
        arr[i] = distri(gen);
    }

    return arr;
}

// Function to measure HashMap performance with insertions, deletions (using remove), and searches
void measure_hashmap_operations(const std::vector<long>& lengths, int min_val, int max_val, const std::string& output_file) {
    std::vector<std::tuple<long, double, double, double>> results; // {array size, insert time, delete time, search time}

    for (long len : lengths) {
        // Generate random array
        int* arr = rand_arr(len, min_val, max_val);

        // Create a hash map
        HashMap<int, int> hashMap;

        // Measure insertion time
        auto start_insert = std::chrono::high_resolution_clock::now();
        for (long i = 0; i < len; ++i) {
            hashMap.insert(arr[i], i);
        }
        auto end_insert = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_insert = end_insert - start_insert;

        // Perform deletions (using remove)
        long num_deletions = len / 10;
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<> prob_dist(0.0, 1.0);
        std::uniform_int_distribution<> index_dist(0, len - 1);

        auto start_delete = std::chrono::high_resolution_clock::now();
        for (long i = 0; i < len && num_deletions > 0; ++i) {
            if (prob_dist(gen) < 0.5) {
                int key_to_remove = arr[index_dist(gen)];
                auto node_to_remove = hashMap.search_node(key_to_remove);
                if (node_to_remove != nullptr) {
                    hashMap.remove(node_to_remove);
                    --num_deletions;
                }
            }
        }
        auto end_delete = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_delete = end_delete - start_delete;

        // Perform searches
        auto start_search = std::chrono::high_resolution_clock::now();
        for (long i = 0; i < len; ++i) {
            hashMap.search(arr[index_dist(gen)]);
        }
        auto end_search = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_search = end_search - start_search;

        // Record result
        results.emplace_back(len, elapsed_insert.count(), elapsed_delete.count(), elapsed_search.count());

        // Clean up dynamically allocated array
        delete[] arr;
    }

    // Save results to a CSV file
    std::ofstream file(output_file);
    file << "Array Size,Insert Time (seconds),Delete Time (seconds),Search Time (seconds)\n";
    for (const auto& [size, insert_time, delete_time, search_time] : results) {
        file << size << "," << insert_time << "," << delete_time << "," << search_time << "\n";
    }
    file.close();

    std::cout << "Operation results saved to " << output_file << std::endl;
}

int main() {
    // Array sizes to test
    std::vector<long> lengths = {100, 1000, 10000, 100000, 1000000};

    // Random number range
    int min_val = 1, max_val = 1000000;

    // Output file for operation results
    std::string output_file = "hashmap_operations.csv";

    // Measure performance for insertions, deletions, and searches
    measure_hashmap_operations(lengths, min_val, max_val, output_file);
    const std::vector<long> array_sizes = {100, 1000, 10000, 100000, 1000000};

    // Output file
    std::ofstream file("slot_distribution_multiple_sizes.csv");
    file << "Array Size,Slot,Count\n";

    for (long array_size : array_sizes) {
        std::cout << "Processing array size: " << array_size << std::endl;

        // Generate random array
        int* arr = rand_arr(array_size, min_val, max_val);

        // Create HashMap
        HashMap<int, int> hashMap;

        // Insert elements into the hash map
        for (long i = 0; i < array_size; ++i) {
            hashMap.insert(arr[i], i);
        }

        // Get slot distribution
        vector<int> slot_counts = hashMap.count_elements_per_slot();

        // Write to output file
        for (size_t i = 0; i < slot_counts.size(); ++i) {
            file << array_size << "," << i << "," << slot_counts[i] << "\n";
        }

        // Clean up
        delete[] arr;
    }

    file.close();
    std::cout << "Slot distributions saved to slot_distribution_multiple_sizes.csv\n";

    return 0;
}
