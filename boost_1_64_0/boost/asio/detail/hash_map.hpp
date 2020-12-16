//
// detail/hash_map.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
8qib3OM3XYsHzPMb4niZz77V77NOt7mnqj+HdP729jT4Dt9InMv7/d27HeP5Bgw1T3iXO/3m615jnC7xNZikwxvd5XvQ4W9hhg4PxhwdHooFushb3+3bievy7Zis67zZPc7V3XwgmrGHfDzW6RJfiKG6wjdghK7yIgzTdV6FUbrJ7fP9DussH4Z6rJ9/c6/x3zKe/4t1jpfv8/6gqas8/n7vuTEV/s4Cv7G6zP/9h99S3ai1p2X/9O3r3EP+/EUt5uQlD7sXnV3Yng5H0iW+Af10jZeh4VoN/hirdXqkPW2O5TrHh2PIAOfyF1jn3O5F7ek4NHSZ78LyuC5v9qj1xxg+A6tj/fwRCubJLra3mKiL3PmYP5t0ns9ERld4EfrrBu/5uN8EXeAK6rr8hPmWmD/G81pUdfeT/v7wlH3QJb4T83Wd9/2X9y+uy89iuU517x4GDOzqdQmDdHiXpz1HHT4Q43X4YJR0Dz/wjL3V2X+3p/sxXzf52P94x3SNy8s8D13lRZgV6+FVmKub3P6s71Bn+dsY3mVP+Cfo1iV+DBN0g7++3PeyRVevj8Y0HT4Zs3WFH0Uh1xX2r5t8Ozr8LZR0ns/FncaH38ViHd70ec9XF/giTDe+h5dhneNN3vkFzyPm4dOjrS28BD06/C/M1+GtV3h2OnwEVuvwZKzX4Sr6mT/8MIbq7hfd30vuN+6d57/sucQauF/D+TGGf4qM9YRXor8O/xfDdPcrxmCWDq/EXB3+LxbGmFf9PQRjzFniOibEtXjGa34ndY3fRGbLrl4ftNJvqw4fjiE6PB55XeFLXzePrvOsVeaJ5h3e8P7oAs/HSt3gc1f7zdVV3vJNv6U6z5dhShzn1Ziu01vt6SlUdPZtfz/BHB2+CvN0+E4sjPl58Bpri3eMz8RYXeEb0MyZnxehoeu8Cut0k9vfcW2d5cHIObebD0RWF/h4DNElvhD9Y36+AeviW+BFyDhe51VIusnt77quMVkejKbu5gOxWhf4Uax3L02+5T1/z9mqq9f9PvD96vDOyOvuDz07jNXhjzFRh/dZ693S4bGYrcMzP/Yu6vCjqOvqf33Xn1iDrvOqT113a/N/Zm1YG8+RT8cCx8v8ILoHOXd9e2r53F7pHP8cZR3+PSo6vBJzdXiPLzwvHV7wpd8rXUod6SM0dfhfG3Sk1m26ev0KBuj8hh1pTmtH6o5u60jzsNB6wvd0dKTlOnx0Z0dap0sbdaQFGG98eI+vdKTJOjwGM3SFW/t0pLG6m+f17Ug9OrtxRyqhv/VU+ORNXNucVf5etiMNdzxc/6pzdfgtTNLlTTvSQV+zhm00r8F8HT6mX0darMO/QkPX+FPkBlvzZtbbvyNN17lvdKTHUdLpmx3pOMzTZX4dtTj+rY501AD3o2v81YEdaYju5sWYqJs8bAtr1hXePNeRsjrP39jSfuoCH4+51lPiC1HVFb4BM+PeeRFm6zqvwjTd5Pat7K3O8mDM0N18IKbqAh+PobrEF2KArvANGBHz8yIMi/l5FQbF/Ny+dUcaFfPzYEyI+flAjI/5+XiM0SW+EJNifr4BY2N+PmeQHqJ5g22M0eFTME2HL8BsXeMP0LOdfR7ckW5GfVu/M/zDbTvSal3ic4Z41jGeP9iuI40zPr99R9pqh440RRf5XWR1eIsd7YMO74VRusoH7NSR8uYp8UqsN3941507Uj/Hw6MxVJd5xC4daYWu8iW72ivj69w1zDy6zMsxXocf2t16dHgFKjq8GnN0uM8evhld4usxK9bGH+3tfXCtwkj7gCW6zl372M/t3S//DCuMD3+KtTp8777Wb0x4GYbq8HrkdSnvOphrfPhJVHX4P1ism7w=
*/