#ifndef LOCKLESS_HPP
#define LOCKLESS_HPP

#include <atomic>
#include <cmath>
#include <cstddef>
#include <limits>
#include <vector>

namespace lockless {

template <typename T, typename C = size_t>
class queue
{
public:
  typedef T value_type;
  typedef C counter_type;

  queue(counter_type size, counter_type read_index = std::numeric_limits<counter_type>::min(),
        counter_type write_index = std::numeric_limits<counter_type>::min())
    : read_index_(read_index)
    , write_index_(write_index)
    , mask_((1 << (static_cast<counter_type>(floor(log2(size))))) - 1)
    , data_(size)
  {}

  inline const counter_type get_read_offset()
  {
    return (read_index_.load(std::memory_order_relaxed) & mask_);
  }

  inline const counter_type get_write_offset()
  {
    return (write_index_.load(std::memory_order_relaxed) & mask_);
  }

  inline const counter_type get_read_index()
  {
    return read_index_.load(std::memory_order_acquire);
  }

  inline const counter_type get_write_index()
  {
    return write_index_.load(std::memory_order_acquire);
  }

  inline void add_read_index(counter_type read_index)
  {
    read_index_.fetch_add(read_index, std::memory_order_release);
  }

  inline void add_write_index(counter_type write_index)
  {
    write_index_.fetch_add(write_index, std::memory_order_release);
  }

  inline void increment_read_index()
  {
    add_read_index(1);
  }

  inline void increment_write_index()
  {
    add_write_index(1);
  }

  inline bool is_empty()
  {
    counter_type local_write_index = write_index_.load(std::memory_order_acquire);
    return read_index_ == local_write_index;
  }

  inline bool is_full()
  {
    // return ( 1 == ((read_index_.fetch_sub(write_index_, std::memory_order_acquire)) &
    // mask_)) ;

    counter_type local_read_index = read_index_.load(std::memory_order_acquire);

    return (1 == ((local_read_index - write_index_) & mask_));
  }

  inline value_type *get_data_pointer(counter_type index)
  {
    return &data_[index];
  }

  inline value_type *get_read_pointer()
  {
    return &data_[get_read_offset()];
  }

  inline value_type *get_write_pointer()
  {
    return &data_[get_write_offset()];
  }

  inline counter_type capacity(void)
  {
    return mask_;
  }

  bool push(value_type const &to_add)
  {
    if (!is_full())
    {
      data_[get_write_offset()] = to_add;
      increment_write_index();
      return true;
    }
    return false;
  }

  bool pop(value_type &to_pop)
  {
    if (!is_empty())
    {
      to_pop = data_[get_read_offset()];
      increment_read_index();
      return true;
    }
    return false;
  }

private:
  std::atomic<counter_type> read_index_;   // points to the index this is available for read
  std::atomic<counter_type> write_index_;  // points to the index that is available for write
  counter_type              mask_;

  std::vector<value_type> data_;
};
}  // namespace lockless

#endif
