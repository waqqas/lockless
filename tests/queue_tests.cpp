#include "lockless/lockless.hpp"

#include <catch2/catch.hpp>

SCENARIO("Lockless queue", "[lockless-queue]")
{
  GIVEN("An empty queue")
  {
    // Arrange
    using queue = lockless::queue<uint16_t>;

    std::size_t size = 32;
    queue       q(size, 1, 1);

    WHEN("initialized")
    {
      THEN("queue should have valid values")
      {
        // Assert
        REQUIRE(q.capacity() == size - 1);  // capacity is the nearest lowest power of 2 - 1
        REQUIRE(q.is_empty() == true);      // queue is initially empty
        REQUIRE(q.is_full() == false);      // queue is not full
      }
    }

    WHEN("1 item is added")
    {
      queue::value_type value_pushed = {1};

      REQUIRE(q.push(value_pushed) == true);

      THEN("1 item should be available for read")
      {
        queue::value_type value_popped = {0};
        REQUIRE(q.pop(value_popped) == true);
        REQUIRE(value_pushed == value_popped);
      }
    }

    WHEN("2 items are added")
    {
      q.push(1);
      q.push(2);

      THEN("2 items should be available for read")
      {
        queue::value_type value_popped = {0};
        std::size_t       popped_count = 0;
        while (q.pop(value_popped) == true)
        {
          popped_count++;
        }
        REQUIRE(popped_count == 2);
      }
    }

    WHEN("all items are added")
    {
      for (queue::value_type count = 0; count < q.capacity(); count++)
      {
        REQUIRE(q.is_full() == false);
        REQUIRE(q.push(count) == true);
      }

      THEN("queue should be full")
      {
        REQUIRE(q.is_full() == true);

        queue::value_type   value_popped = {0};
        queue::counter_type popped_count = 0;
        while (q.pop(value_popped) == true)
        {
          popped_count++;
        }
        REQUIRE(popped_count == q.capacity());
      }
    }

    WHEN("An item is pushed")
    {
      q.push(1);
      AND_WHEN("And an item is popped")
      {
        queue::value_type item = {0};
        REQUIRE(q.pop(item) == true);

        THEN("queue should be empty")
        {
          REQUIRE(q.is_empty() == true);
          REQUIRE(item == 1);
        }
      }
    }
  }
}
