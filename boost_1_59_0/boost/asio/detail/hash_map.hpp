//
// detail/hash_map.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HASH_MAP_HPP
#define BOOST_ASIO_DETAIL_HASH_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <list>
#include <utility>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# include <boost/asio/detail/socket_types.hpp>
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

inline std::size_t calculate_hash_value(int i)
{
  return static_cast<std::size_t>(i);
}

inline std::size_t calculate_hash_value(void* p)
{
  return reinterpret_cast<std::size_t>(p)
    + (reinterpret_cast<std::size_t>(p) >> 3);
}

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
inline std::size_t calculate_hash_value(SOCKET s)
{
  return static_cast<std::size_t>(s);
}
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

// Note: assumes K and V are POD types.
template <typename K, typename V>
class hash_map
  : private noncopyable
{
public:
  // The type of a value in the map.
  typedef std::pair<K, V> value_type;

  // The type of a non-const iterator over the hash map.
  typedef typename std::list<value_type>::iterator iterator;

  // The type of a const iterator over the hash map.
  typedef typename std::list<value_type>::const_iterator const_iterator;

  // Constructor.
  hash_map()
    : size_(0),
      buckets_(0),
      num_buckets_(0)
  {
  }

  // Destructor.
  ~hash_map()
  {
    delete[] buckets_;
  }

  // Get an iterator for the beginning of the map.
  iterator begin()
  {
    return values_.begin();
  }

  // Get an iterator for the beginning of the map.
  const_iterator begin() const
  {
    return values_.begin();
  }

  // Get an iterator for the end of the map.
  iterator end()
  {
    return values_.end();
  }

  // Get an iterator for the end of the map.
  const_iterator end() const
  {
    return values_.end();
  }

  // Check whether the map is empty.
  bool empty() const
  {
    return values_.empty();
  }

  // Find an entry in the map.
  iterator find(const K& k)
  {
    if (num_buckets_)
    {
      size_t bucket = calculate_hash_value(k) % num_buckets_;
      iterator it = buckets_[bucket].first;
      if (it == values_.end())
        return values_.end();
      iterator end_it = buckets_[bucket].last;
      ++end_it;
      while (it != end_it)
      {
        if (it->first == k)
          return it;
        ++it;
      }
    }
    return values_.end();
  }

  // Find an entry in the map.
  const_iterator find(const K& k) const
  {
    if (num_buckets_)
    {
      size_t bucket = calculate_hash_value(k) % num_buckets_;
      const_iterator it = buckets_[bucket].first;
      if (it == values_.end())
        return it;
      const_iterator end_it = buckets_[bucket].last;
      ++end_it;
      while (it != end_it)
      {
        if (it->first == k)
          return it;
        ++it;
      }
    }
    return values_.end();
  }

  // Insert a new entry into the map.
  std::pair<iterator, bool> insert(const value_type& v)
  {
    if (size_ + 1 >= num_buckets_)
      rehash(hash_size(size_ + 1));
    size_t bucket = calculate_hash_value(v.first) % num_buckets_;
    iterator it = buckets_[bucket].first;
    if (it == values_.end())
    {
      buckets_[bucket].first = buckets_[bucket].last =
        values_insert(values_.end(), v);
      ++size_;
      return std::pair<iterator, bool>(buckets_[bucket].last, true);
    }
    iterator end_it = buckets_[bucket].last;
    ++end_it;
    while (it != end_it)
    {
      if (it->first == v.first)
        return std::pair<iterator, bool>(it, false);
      ++it;
    }
    buckets_[bucket].last = values_insert(end_it, v);
    ++size_;
    return std::pair<iterator, bool>(buckets_[bucket].last, true);
  }

  // Erase an entry from the map.
  void erase(iterator it)
  {
    BOOST_ASIO_ASSERT(it != values_.end());
    BOOST_ASIO_ASSERT(num_buckets_ != 0);

    size_t bucket = calculate_hash_value(it->first) % num_buckets_;
    bool is_first = (it == buckets_[bucket].first);
    bool is_last = (it == buckets_[bucket].last);
    if (is_first && is_last)
      buckets_[bucket].first = buckets_[bucket].last = values_.end();
    else if (is_first)
      ++buckets_[bucket].first;
    else if (is_last)
      --buckets_[bucket].last;

    values_erase(it);
    --size_;
  }

  // Erase a key from the map.
  void erase(const K& k)
  {
    iterator it = find(k);
    if (it != values_.end())
      erase(it);
  }

  // Remove all entries from the map.
  void clear()
  {
    // Clear the values.
    values_.clear();
    size_ = 0;

    // Initialise all buckets to empty.
    iterator end_it = values_.end();
    for (size_t i = 0; i < num_buckets_; ++i)
      buckets_[i].first = buckets_[i].last = end_it;
  }

private:
  // Calculate the hash size for the specified number of elements.
  static std::size_t hash_size(std::size_t num_elems)
  {
    static std::size_t sizes[] =
    {
#if defined(BOOST_ASIO_HASH_MAP_BUCKETS)
      BOOST_ASIO_HASH_MAP_BUCKETS
#else // BOOST_ASIO_HASH_MAP_BUCKETS
      3, 13, 23, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
      49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
      12582917, 25165843
#endif // BOOST_ASIO_HASH_MAP_BUCKETS
    };
    const std::size_t nth_size = sizeof(sizes) / sizeof(std::size_t) - 1;
    for (std::size_t i = 0; i < nth_size; ++i)
      if (num_elems < sizes[i])
        return sizes[i];
    return sizes[nth_size];
  }

  // Re-initialise the hash from the values already contained in the list.
  void rehash(std::size_t num_buckets)
  {
    if (num_buckets == num_buckets_)
      return;
    BOOST_ASIO_ASSERT(num_buckets != 0);

    iterator end_iter = values_.end();

    // Update number of buckets and initialise all buckets to empty.
    bucket_type* tmp = new bucket_type[num_buckets];
    delete[] buckets_;
    buckets_ = tmp;
    num_buckets_ = num_buckets;
    for (std::size_t i = 0; i < num_buckets_; ++i)
      buckets_[i].first = buckets_[i].last = end_iter;

    // Put all values back into the hash.
    iterator iter = values_.begin();
    while (iter != end_iter)
    {
      std::size_t bucket = calculate_hash_value(iter->first) % num_buckets_;
      if (buckets_[bucket].last == end_iter)
      {
        buckets_[bucket].first = buckets_[bucket].last = iter++;
      }
      else if (++buckets_[bucket].last == iter)
      {
        ++iter;
      }
      else
      {
        values_.splice(buckets_[bucket].last, values_, iter++);
        --buckets_[bucket].last;
      }
    }
  }

  // Insert an element into the values list by splicing from the spares list,
  // if a spare is available, and otherwise by inserting a new element.
  iterator values_insert(iterator it, const value_type& v)
  {
    if (spares_.empty())
    {
      return values_.insert(it, v);
    }
    else
    {
      spares_.front() = v;
      values_.splice(it, spares_, spares_.begin());
      return --it;
    }
  }

  // Erase an element from the values list by splicing it to the spares list.
  void values_erase(iterator it)
  {
    *it = value_type();
    spares_.splice(spares_.begin(), values_, it);
  }

  // The number of elements in the hash.
  std::size_t size_;

  // The list of all values in the hash map.
  std::list<value_type> values_;

  // The list of spare nodes waiting to be recycled. Assumes that POD types only
  // are stored in the hash map.
  std::list<value_type> spares_;

  // The type for a bucket in the hash table.
  struct bucket_type
  {
    iterator first;
    iterator last;
  };

  // The buckets in the hash.
  bucket_type* buckets_;

  // The number of buckets in the hash.
  std::size_t num_buckets_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HASH_MAP_HPP

/* hash_map.hpp
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
*/