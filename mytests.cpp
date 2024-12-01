//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// mytests.cpp
// This file contains the tests cases for Hash classes and
// for the Set class
//========================================================
#include "customexceptions.hpp"
#include "HashMap.hpp"
#include "Hash.hpp"
#include "HashMapTree.hpp"
#include "Set.hpp"

#include <iostream>
using namespace std;

HashMap<int, int> createSampleHashMap();
HashMapTree<int, string> createSampleHashMapTree();
Set<int> createSampleSet();

// Pass or Fail Testing
void testHashMap();
void testHashMapTree();
void testSet();

// Testing functions for HashMap
bool testHashMapInsert();
bool testHashMapDel();
bool testHashMapOperator();
bool testHashMapSearch();
bool testEdgeCasesHashMap();

// Testing functions for HashMapTree
bool testHashMapTreeInsert();
bool testHashMapTreeRemove();
bool testHashMapTreeOperator();
bool testHashMapTreeSearch();
bool testEdgeCasesHashMapTree();

// Testing functions for Set
bool testSetInsert();
bool testSetRemove();
bool testSetSearch();
bool testEdgeCasesSet();

//==============================================================
// main
// Initiate testing by calling testing methods.
// PARAMETERS:
// - none
// RETURN VALUE:
// - 0
//==============================================================
int main()
{
    cout << "Testing HashMap:" << endl;
    testHashMap();

    cout << "\nTesting HashMapTree:" << endl;
    testHashMapTree();

    cout << "\nTesting Set:" << endl;
    testSet();

    return 0;
}

//==============================================================
// createSampleHashMap
// Creates and returns a sample HashMap with predefined key-value pairs.
// PARAMETERS:
// - none
// RETURN VALUE:
// - HashMap<int, int> with predefined key-value pairs
//==============================================================
HashMap<int, int> createSampleHashMap()
{
    HashMap<int, int> map;
    map.insert(10, 100);
    map.insert(20, 200);
    map.insert(30, 300);
    return map;
}

//==============================================================
// createSampleHashMapTree
// Creates and returns a sample HashMapTree with predefined key-value pairs.
// PARAMETERS:
// - none
// RETURN VALUE:
// - HashMapTree<int, string> with predefined key-value pairs
//==============================================================
HashMapTree<int, string> createSampleHashMapTree()
{
    HashMapTree<int, string> mapTree;
    mapTree.insert(1, "One");
    mapTree.insert(2, "Two");
    mapTree.insert(3, "Three");
    return mapTree;
}

//==============================================================
// createSampleSet
// Creates and returns a sample Set with predefined elements.
// PARAMETERS:
// - none
// RETURN VALUE:
// - Set<int> with predefined elements
//==============================================================
Set<int> createSampleSet()
{
    Set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    return set;
}

//******************************************
//*************HASH MAP TESTING*************
//******************************************

//==============================================================
// testHashMapInsert
// Tests the insertion functionality of the HashMap.
// Verifies that elements can be inserted and the map size is updated correctly.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapInsert()
{
    HashMap<int, int> map = createSampleHashMap();

    // Inserting a new key-value pair
    map.insert(40, 400);
    if (map.search(40) == nullptr || map.search(40)->second != 400)
    {
        cout << "Error: Insertion failed for key 40!" << endl;
        return false;
    }

    // Inserting an existing key with a different value (should update)
    map.insert(10, 500);
    if (map.search(10) == nullptr || map.search(10)->second != 500)
    {
        cout << "Error: Insertion failed or size incorrect for key 10!" << endl;
        return false;
    }

    cout << "testHashMapInsert passed!" << endl;
    return true;
}

//==============================================================
// testHashMapDel
// Tests the deletion functionality of the HashMap.
// Verifies that elements can be deleted and the map size is updated correctly.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapDel()
{
    HashMap<int, int> map = createSampleHashMap(); // Use the helper function to create a HashMap
    // Delete a key
    map.del(20);

    // Check if the deleted key no longer exists in the map
    if (map.search(20) != nullptr)
    {
        cout << "Error: Deletion failed, key 20 still exists!" << endl;
        return false;
    }

    // Check other keys
    if (map.search(10) == nullptr || map.search(30) == nullptr)
    {
        cout << "Error: Other keys are missing after deletion!" << endl;
        return false;
    }

    // Attempt to access the deleted key and ensure it throws an exception
    try
    {
        map[20]; // Should throw an exception
        cout << "Error: Access to deleted key 20 did not throw an exception!" << endl;
        return false;
    }
    catch (const key_exception &e)
    {
        // Expected behavior, key 20 should not exist
    }

    cout << "testHashMapDel passed!" << endl;
    return true;
}

//==============================================================
// testHashMapOperator
// Tests the operator[] functionality of the HashMap.
// Verifies that values can be accessed and modified correctly using the operator[].
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapOperator()
{
    HashMap<int, int> map = createSampleHashMap(); // Use the helper function to create a HashMap

    // Check if the values are correct using the operator[]
    if (map[10] != 100)
    {
        cout << "Error: Incorrect value for key 10!" << endl;
        return false;
    }

    if (map[20] != 200)
    {
        cout << "Error: Incorrect value for key 20!" << endl;
        return false;
    }

    // Modify a value using the operator[]
    map[10] = 500;
    if (map[10] != 500)
    {
        cout << "Error: Incorrect modified value for key 10!" << endl;
        return false;
    }

    cout << "testHashMapOperator passed!" << endl;
    return true;
}

//==============================================================
// testHashMapSearch
// Tests the search functionality of the HashMap.
// Verifies that elements can be searched correctly, both existing and non-existing.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapSearch()
{
    HashMap<int, int> map = createSampleHashMap(); // Use the helper function to create a HashMap

    // Search for an existing key
    auto item = map.search(10);
    if (item == nullptr || item->second != 100)
    {
        cout << "Error: Search failed for key 10!" << endl;
        return false;
    }

    // Search for a non-existent key
    item = map.search(60);
    if (item != nullptr)
    {
        cout << "Error: Search should return nullptr for non-existent key!" << endl;
        return false;
    }

    cout << "testHashMapSearch passed!" << endl;
    return true;
}

//==============================================================
// testEdgeCasesHashMap
// Tests edge cases for the HashMap class.
// Verifies behavior for inserting, removing, and searching for elements in edge cases.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testEdgeCasesHashMap()
{
    bool allTestsPassed = true;

    // Test empty map search
    HashMap<int, int> emptyMap;
    if (emptyMap.search(10) != nullptr)
    {
        cout << "Error: Empty map should not contain any keys!" << endl;
        allTestsPassed = false;
    }

    // Test collision handling
    HashMap<int, int> mapWithCollision;
    mapWithCollision.insert(1, 100);
    mapWithCollision.insert(11, 200); // Assume 1 and 11 collide
    if (mapWithCollision.search(1) == nullptr || mapWithCollision.search(11) == nullptr ||
        mapWithCollision.search(1)->second != 100 || mapWithCollision.search(11)->second != 200)
    {
        cout << "Error: Collision handling failed!" << endl;
        allTestsPassed = false;
    }

    if (allTestsPassed)
        cout << "testEdgeCasesHashMap passed!" << endl;
    else
        cout << "testEdgeCasesHashMap failed!" << endl;

    return allTestsPassed;
}

//******************************************
//***********HASH MAP TREE TESTING**********
//******************************************

//==============================================================
// testHashMapTreeInsert
// Tests the insertion functionality of the HashMapTree.
// Verifies that new elements can be inserted correctly and the map size is updated.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeInsert()
{
    HashMapTree<int, string> mapTree = createSampleHashMapTree(); // Use the helper function

    // Test inserting a new element
    mapTree.insert(4, "Four");
    if (mapTree.search(4) != nullptr && mapTree.search(4)->second == "Four")
    {
        cout << "testHashMapTreeInsert passed for new insert" << endl;
    }
    else
    {
        cout << "testHashMapTreeInsert failed for new insert" << endl;
        return false;
    }

    cout << "testHashMapTreeInsert passed!" << endl;
    return true;
}

//==============================================================
// testHashMapTreeRemove
// Tests the removal functionality of the HashMapTree.
// Verifies that elements can be removed and keys are inaccessible after removal.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeRemove()
{
    HashMapTree<int, string> mapTree = createSampleHashMapTree(); // Use the helper function

    // Test removing an existing element
    mapTree.remove(2);
    if (mapTree.search(2) == nullptr)
    {
        cout << "testHashMapTreeRemove passed for removing existing element" << endl;
    }
    else
    {
        cout << "testHashMapTreeRemove failed for removing existing element" << endl;
        return false;
    }

    try
    {
        mapTree.remove(5);
    }
    catch (const key_exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        cout << "testHashMapTreeRemove passed for removing non-existing element" << endl;
    }

    cout << "testHashMapTreeRemove passed!" << endl;
    return true;
}

//==============================================================
// testHashMapTreeOperator
// Tests the operator[] functionality of the HashMapTree.
// Verifies that values can be accessed and modified correctly using the operator[].
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeOperator()
{
    HashMapTree<int, string> mapTree = createSampleHashMapTree(); // Use the helper function

    // Test modifying value using operator[]
    mapTree[2] = "Updated Two";

    // Check if the value was updated correctly
    if (mapTree.search(2) != nullptr && mapTree.search(2)->second == "Updated Two")
    {
        cout << "testHashMapTreeOperator passed for updating value" << endl;
    }
    else
    {
        cout << "testHashMapTreeOperator failed for updating value" << endl;
        return false;
    }

    cout << "testHashMapTreeOperator passed!" << endl;
    return true;
}

//==============================================================
// testHashMapTreeSearch
// Tests the search functionality of the HashMapTree.
// Verifies that elements can be searched correctly, both existing and non-existing.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeSearch()
{
    HashMapTree<int, string> mapTree = createSampleHashMapTree(); // Use the helper function

    // Test searching for existing elements
    if (mapTree.search(1) != nullptr && mapTree.search(1)->second == "One" &&
        mapTree.search(2) != nullptr && mapTree.search(2)->second == "Two" &&
        mapTree.search(3) != nullptr && mapTree.search(3)->second == "Three")
    {
        cout << "testHashMapTreeSearch passed for existing elements" << endl;
    }
    else
    {
        cout << "testHashMapTreeSearch failed for existing elements" << endl;
        return false;
    }

    // Test searching for a non-existing element
    if (mapTree.search(5) == nullptr)
    {
        cout << "testHashMapTreeSearch passed for non-existing element" << endl;
    }
    else
    {
        cout << "testHashMapTreeSearch failed for non-existing element" << endl;
        return false;
    }

    cout << "testHashMapTreeSearch passed!" << endl;
    return true;
}

//==============================================================
// testEdgeCasesHashMapTree
// Tests edge cases for the HashMapTree class.
// Verifies behavior for inserting, removing, and searching for elements in edge cases.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testEdgeCasesHashMapTree()
{
    bool allTestsPassed = true;

    // Test sorted insertion
    HashMapTree<int, int> sortedTree;
    for (int i = 0; i < 10; i++)
        sortedTree.insert(i, i * 10);
    for (int i = 0; i < 10; i++)
    {
        if (sortedTree.search(i) == nullptr || sortedTree.search(i)->second != i * 10)
        {
            cout << "Error: Sorted insertion failed at key " << i << "!" << endl;
            allTestsPassed = false;
        }
    }

    // Test reverse order insertion
    HashMapTree<int, int> reverseTree;
    for (int i = 9; i >= 0; i--)
        reverseTree.insert(i, i * 10);
    for (int i = 0; i < 10; i++)
    {
        if (reverseTree.search(i) == nullptr || reverseTree.search(i)->second != i * 10)
        {
            cout << "Error: Reverse order insertion failed at key " << i << "!" << endl;
            allTestsPassed = false;
        }
    }

    // Test removal of root node
    HashMapTree<int, int> treeWithRootRemoval;
    treeWithRootRemoval.insert(50, 500);
    treeWithRootRemoval.insert(30, 300);
    treeWithRootRemoval.insert(70, 700);
    treeWithRootRemoval.remove(50);
    if (treeWithRootRemoval.search(50) != nullptr)
    {
        cout << "Error: Root removal failed!" << endl;
        allTestsPassed = false;
    }

    if (allTestsPassed)
        cout << "testEdgeCasesHashMapTree passed!" << endl;
    else
        cout << "testEdgeCasesHashMapTree failed!" << endl;

    return allTestsPassed;
}

//******************************************
//****************SET TESTING***************
//******************************************

//==============================================================
// testSetInsert
// Tests the insertion functionality of the Set.
// Verifies that elements can be inserted into the set and that duplicates are not allowed.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testSetInsert()
{
    Set<int> set = createSampleSet(); // Use the helper function

    // Test inserting a new element
    set.insert(4);
    if (set.search(4))
    {
        cout << "testSetInsert passed for new insert" << endl;
    }
    else
    {
        cout << "testSetInsert failed for new insert" << endl;
        return false;
    }

    // Test inserting a duplicate element (should not insert it again)
    set.insert(3); // Duplicate
    if (set.search(3))
    {
        cout << "testSetInsert passed for duplicate insert (no insertion)" << endl;
    }
    else
    {
        cout << "testSetInsert failed for duplicate insert (should not insert again)" << endl;
        return false;
    }

    cout << "testSetInsert passed!" << endl;
    return true;
}

//==============================================================
// testSetRemove
// Tests the removal functionality of the Set.
// Verifies that elements can be removed and the set size is updated correctly.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testSetRemove()
{
    Set<int> set = createSampleSet(); // Use the helper function

    // Test removing an existing element
    set.remove(1);
    if (!set.search(1))
    {
        cout << "testSetRemove passed for removing existing element" << endl;
    }
    else
    {
        cout << "testSetRemove failed for removing existing element" << endl;
        return false;
    }

    // Test removing a non-existing element
    try
    {
        set.remove(5); // Key 5 does not exist
        cout << "testSetRemove passed for removing non-existing element" << endl;
    }
    catch (const key_exception &e)
    {
    }

    cout << "testSetRemove passed!" << endl;
    return true;
}

//==============================================================
// testSetSearch
// Tests the search functionality of the Set.
// Verifies that elements can be searched correctly, both existing and non-existing.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testSetSearch()
{
    Set<int> set = createSampleSet(); // Use the helper function

    // Test searching for existing elements
    if (set.search(1) && set.search(2) && set.search(3))
    {
        cout << "testSetSearch passed for existing elements" << endl;
    }
    else
    {
        cout << "testSetSearch failed for existing elements" << endl;
        return false;
    }

    // Test searching for a non-existing element
    if (!set.search(5))
    {
        cout << "testSetSearch passed for non-existing element" << endl;
    }
    else
    {
        cout << "testSetSearch failed for non-existing element" << endl;
        return false;
    }

    cout << "testSetSearch passed!" << endl;
    return true;
}

//==============================================================
// testEdgeCasesSet
// Tests edge cases for the Set class.
// Verifies behavior for inserting, removing, and searching for elements in edge cases.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testEdgeCasesSet()
{
    bool allTestsPassed = true;

    // Test duplicate insertion
    Set<int> duplicateSet;
    duplicateSet.insert(10);
    duplicateSet.insert(10); // Duplicate insertion

    // Attempt to remove the element twice
    duplicateSet.remove(10); // First removal
    try
    {
        duplicateSet.remove(10); // Second removal should fail
        cout << "Error: Duplicate element was removed twice!" << endl;
        allTestsPassed = false;
    }
    catch (...)
    {
        // Expected behavior: no exception should be thrown
        cout << "Duplicate removal test passed!" << endl;
    }

    // Test edge values
    Set<int> edgeValueSet;
    edgeValueSet.insert(INT_MIN);
    edgeValueSet.insert(INT_MAX);

    // Remove the edge values to verify they were stored correctly
    try
    {
        edgeValueSet.remove(INT_MIN);
        edgeValueSet.remove(INT_MAX);
    }
    catch (...)
    {
        cout << "Error: Edge value insertion or removal failed!" << endl;
        allTestsPassed = false;
    }

    if (allTestsPassed)
        cout << "testEdgeCasesSet passed!" << endl;
    else
        cout << "testEdgeCasesSet failed!" << endl;

    return allTestsPassed;
}

//******************************************
//***********FAIL OR PASS TESTING***********
//******************************************

//==============================================================
// testHashMap
// Testing functions and respective outputs for HashMap class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
void testHashMap()
{
    struct TestResult
    {
        int passed;
        int failed;
    };

    TestResult hashMap_result = {0, 0};

    if (testHashMapInsert())
    {
        cout << "testHashMapInsert passed!" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapInsert failed!" << endl;
        hashMap_result.failed++;
    }

    if (testHashMapDel())
    {
        cout << "testHashMapDel passed!" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapDel failed!" << endl;
        hashMap_result.failed++;
    }

    if (testHashMapOperator())
    {
        cout << "testHashMapOperator passed!" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapOperator failed!" << endl;
        hashMap_result.failed++;
    }

    if (testHashMapSearch())
    {
        cout << "testHashMapSearch passed!" << endl;
        hashMap_result.passed++;
    }
    if (testEdgeCasesHashMap())
    {
        cout << "testEdgeCasesHashMap passed!" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapSearch failed!" << endl;
        hashMap_result.failed++;
    }

    cout << "\n\n";
    cout << "HashMap Tests Passed: " << hashMap_result.passed << endl;
    cout << "HashMap Tests Failed: " << hashMap_result.failed << endl;
    cout << "\n\n";
}

//==============================================================
// testHashMapTree
// Testing functions and respective outputs for HashMapTree class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
void testHashMapTree()
{
    struct TestResult
    {
        int passed;
        int failed;
    };
    TestResult mapTree_result = {0, 0};

    if (testHashMapTreeInsert())
    {
        cout << "testHashMapTreeInsert passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        mapTree_result.failed++;
    }

    if (testHashMapTreeRemove())
    {
        cout << "testHashMapTreeRemove passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        mapTree_result.failed++;
    }

    if (testHashMapTreeOperator())
    {
        cout << "testHashMapTreeOperator passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        mapTree_result.failed++;
    }

    if (testHashMapTreeSearch())
    {
        cout << "testHashMapTreeSearch passed" << endl;
        mapTree_result.passed++;
    }
    if (testEdgeCasesHashMapTree())
    {
        cout << "testEdgeCasesHashMapTree passed!" << endl;
        mapTree_result.passed++;
    }
    else
    {
        mapTree_result.failed++;
    }

    cout << "\n\n";
    cout << "HashMapTree Tests Passed: " << mapTree_result.passed << endl;
    cout << "HashMapTree Tests Failed: " << mapTree_result.failed << endl;
    cout << "\n\n";
}

//==============================================================
// testSet
// Testing functions and respective outputs for Set class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
void testSet()
{
    struct TestResult
    {
        int passed;
        int failed;
    };
    TestResult set_result = {0, 0};

    if (testSetInsert())
    {
        cout << "testSetInsert passed" << endl;
        set_result.passed++;
    }
    else
    {
        set_result.failed++;
    }

    if (testSetRemove())
    {
        cout << "testSetRemove passed" << endl;
        set_result.passed++;
    }
    else
    {
        set_result.failed++;
    }

    if (testSetSearch())
    {
        cout << "testSetSearch passed" << endl;
        set_result.passed++;
    }
    if (testEdgeCasesSet())
    {
        cout << "testEdgeCasesSet passed!" << endl;
        set_result.passed++;
    }
    else
    {
        set_result.failed++;
    }

    cout << "\n\n";
    cout << "Set Tests Passed: " << set_result.passed << endl;
    cout << "Set Tests Failed: " << set_result.failed << endl;
    cout << "\n\n";
}

;
