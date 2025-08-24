// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());//check in the collection is empty
    ASSERT_EQ(collection->size(), 0);//if it is empty, size will be 0

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_FALSE(collection->empty()); //check if the collection is empty after adding one entry
    ASSERT_EQ(collection->size(), 1); //if the add_entries() method worked correctly, the size should now be 1
}

// Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    ASSERT_TRUE(collection->empty());//start by checking if collection is empty
    ASSERT_EQ(collection->size(), 0);//if so, collection size should be 0

    add_entries(5);

    ASSERT_FALSE(collection->empty());//collection should now not be empty
    ASSERT_EQ(collection->size(), 5);//checking that the collection size is now 5
}

// Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxGreaterOrEqualToVectorSize)
{
    //using ASSERT_GE, or assert greater than or equal too, for more clarity
    ASSERT_TRUE(collection->empty());//begin by checking if collection is empty
    ASSERT_EQ(collection->size(), 0);// if so, size should be zero
    ASSERT_GE(collection->max_size(), collection->size());//collection starts with 0 entries, so checking max size against current size

    add_entries(1);//add one entry
    ASSERT_GE(collection->max_size(), collection->size());//compare current size to max

    add_entries(5);//add five entries
    ASSERT_GE(collection->max_size(), collection->size());//compare current size to max

    add_entries(10);//add 10 entries
    ASSERT_GE(collection->max_size(), collection->size());//compare current size to max
    
}

//Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterOrEqualToVectorSize)
{
    ASSERT_TRUE(collection->empty());//check if collection is empty
    ASSERT_EQ(collection->size(), 0);//if so, size should be 0
    ASSERT_GE(collection->capacity(), collection->size());//compare initial empty collection to capacity

    add_entries(1);//add one entry
    ASSERT_GE(collection->capacity(), collection->size());//compare current size to capacity
                          
    add_entries(5);//add five entries
    ASSERT_GE(collection->capacity(), collection->size());//compare current size to capacity
                          
    add_entries(10);//add 10 entries    
    ASSERT_GE(collection->capacity(), collection->size());//compare current size to capacity
}

//Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollection)
{
    ASSERT_TRUE(collection->empty());//check if collection is empty
    ASSERT_EQ(collection->size(), 0);//if so, size should be 0

    collection->resize(1);//resize the collection using the value of the newColSize variable

    ASSERT_EQ(collection->size(), 1);//check that the collection size actually increased.
}

//Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollection)
{
    ASSERT_TRUE(collection->empty());//check if collection is empty
    ASSERT_EQ(collection->size(), 0);//if so, size should be 0

    collection->resize(1);//bring collection size up to 1

    ASSERT_EQ(collection->size(), 1);//check that the collection size increased

    collection->resize(0);//bring collection size down to zero

    ASSERT_EQ(collection->size(), 0);//check that the collection size actually decreased.
}

//Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreasesToZero)
{
    add_entries(10);//begin by adding entries to the collection
    ASSERT_EQ(collection->size(), 10);//check that the collection is the size that was added

    collection->resize(0);//resize the collection down to zero
    ASSERT_EQ(collection->size(), 0);//check that the collection now has a size of 0
    ASSERT_TRUE(collection->empty());//check that the collection is empty to be more clear
}

//Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(10);// add some entries to the collection
    ASSERT_EQ(collection->size(), 10);//confirm that the size of the collection after adding entries is equal to the added entries
    
    collection->clear();// call clear() on the collection
    ASSERT_TRUE(collection->empty());//confirm that the collection is now empty after calling clear()
}

//Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseErasesCollection) 
{
    add_entries(10);//add entries to the collection
    ASSERT_EQ(collection->size(), 10);//confirm the size of the collection equals the amount of entries

    collection->erase(collection->begin(), collection->end());//call erase() on the collection, using the beginning and the end of the collection as the paramaters
    ASSERT_TRUE(collection->empty());//confirm the collection is now empty after calling erase() method
}

//Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    //check that the size of the collection is currently 0
    ASSERT_EQ(collection->size(), 0);
    //call reserve() to inncrease the capacity of the collection to 10
    collection->reserve(10);
    //check that the capacity is greater than or equal to the amount given in reserve()
    ASSERT_GE(collection->capacity(), 10);
    //confirm that the size of the collection did not change.
    ASSERT_EQ(collection->size(), 0);
}

//Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AtCallThrowsOutOfRange)
{
    //first confirm that the collection is empty
    ASSERT_TRUE(collection->empty());
    //call at() with the index of 0, which should be out of range since the collection is currently empty. throws out of range exception
    ASSERT_THROW(collection->at(0), std::out_of_range);

}

//Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

//Positive Test
TEST_F(CollectionTest, InsertedValuePresentInCollection)
{
    //check that the initial collection is empty
    ASSERT_TRUE(collection->empty());
    // push a value to the collection
    collection->push_back(405);
    //confirm that the value pushed to the collection is present at the first index in the collection.
    ASSERT_EQ(collection->at(0), 405);
}

//Negative Test
TEST_F(CollectionTest, OutOfRangeWhenAtCalledOnHigherIndexThanSize)
{
    //check initial size of collection is 0
    ASSERT_EQ(collection->size(), 0);
    //resize the collection to size of 10
    collection->resize(10);
    //check that there is a value at the highest index of the new collection size
    ASSERT_EQ(collection->at(9), 0);
    //resize the collection down to size of 4
    collection->resize(4);
    // confirm that calling at() at the old collection index now throws an out of range exception
    ASSERT_THROW(collection->at(9), std::out_of_range);
}