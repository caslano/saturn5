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
2NwBIM5S2618ehplQECWoQQZI7uNdfyH2m1See4mmfXKCgACOowmY0Iq9DpHprrPRMoPD6xLky+Ao1ZAEWmVzgPm5GIkxaWuue0t40FK3WAaCS2wUFidvN/IVVKxDKfFJCfHbxGF8+V9QokpgE6TSSAwH08iWWvWg5AeBBIdq+7jyHgJLuyEXbVtAEzCZox9BQeu0F8i1t1Q9g4LwRfIvNxsLo8XrwnBLD9FCo4p5NJgtVko+PYhr4rBrv1s4AZgFG6js0mz0fmJhJpcHYr60F17vf0U3cSYIdcSbLmDAfqxiQS+kx5heEqcxx1quHWV7rr0kq2gcGNVinuUKs8oM9PcqlIOxOtwREzz5Rpr4n3BWayy++uGGUajnn4DOrVTMKvKCZtMIklGJi3mAC2PVrv1eswG/a2bVkT3F7xkQgp2SZ95hUuWNZcdRoDPZ7L2qp7x2AeBxHg6gzH0XOlhaUUGFIxaNPBADQ0yCQpxq18Hnl+N1L/HvYon2E7FTa8XUExQU5TCFjKi6BCHkmoy7fDQxrh8S4GiTFkhw7Y5G69URto5naXK7hLEthp+kQj6x86qsnyVZeKoSj+h6PssVIDzr6fJdBeg01DKezV8MdfOYv4RnUaDwfTr9Qa8YZ0DdPHPLOCYLeAYm82c+Ml9GBhElwrpqUsvncr5dDrTIoZKWhOwVs2h3WQVymnncOMN1yJ178+0Z/slvmZxO80wQFHDrjc6ClIJooyGjpAAACaAaCeJkGwABZchkZy0lFOMmaLLTDY2d3F+nvLlJffQbQaFJoXGfbtP3O5rC43zet6p47nb02n1Yom0Kr5Wv7u6Q0CR/99QtTAcpwlQ2e6V2+22ZvRnBwLsHsgycZcO8WPTPiKvRJtu5bR9cELqtdJMJjP5YqmSAwXD8vKkxOp2e4ec39sZrNMbsDYpdZ1A4xM0EW0+tjhfpwRqqud8hxnOQa938Ya2VmcJoEBFhV28prehZiej2QC6GlMvkTRdl0Gvzz1vUynCzqgKKjaFOjBBYiCPG2yb/W53pi6dX0wj9subrkSyf1nWqKy6vDyrRIr/9US0FxxfjEYAAM5aYEGZdOjFFtGsEuFTmbQoAwIBHYWFvCgiBn/fB6rnceQOGArnuRSoqptbGKioqJ0MO9n5W+znNsSEkvYS4Ysrrthi+8n+s6O6dxXK6es4Kr4eSbqPAx4ZhhJ2OQKBChQKOsm/JrxpJ1yHsmDlW6efwyvmbZpym7EHAMghEr9shvP9bpF0Kvjhb0SIDzu4e7OZLNVIRvES6REVSDDS7lOi9+pbQWfoVQq/X37r499UVTAMQ+PoxkedCpxk8tLSyLPxYMc+xHzp+nOJHeYadAHL9GDwzemCfNMDF1c7wwaXV5cpef+nrO3vsbXjJnxtGvQcZnZTykoAw+5qfjaHf0cyMs0y/UTGvAGDqG/QCwxOyBfpCyeHgChDtWIoAgBxDwUb8QLTyB24vr/fH8jvkdb13CdKtJoGLEYFn8n6vRT+31diE5P0KQQMHHEEFKOx9P1xe227nl40fxkNH2LsBtDTgT+2ZttCWs6JyQKWoSIfA7F1GQ2ba3xdMrM8pC+3sAOFUS9SoXhCmJec7kNhsF8N0u8798oQeu1QBBWqfUOmcRhyAIJlwDh9ZBwS1SPR6PJqDgn/6AxRUVi+FjHyJ/NvNynKu//+jlv77hK+HxmTgh3DqOAsyGWoEkLDVcdTLEUHLTWdEeC9wewVdbXSqJvO0ia7QU2FuqhSKb4umU8m7flI0X0v8wdrrfRdC+4w4W8qm/UgUege8dzWDZM5V0Pyl8ah9yMlL9nzKhzf1mLQ6zrjIQI89tsxRTRhHLP7LBaKJhIIOElykBSZq82YQAxPfPcb/cfd/VrFNpkJMKGiWdozPbHiZwKg0VTHRa6tJwc9jFVElQGwUUxWr5EyvS0wzW6+B2jQxZ+ipU9GYGUfb6VvU/H3noua3dctd3ovSblA7bdi1gCMVLnDXeM16dya0j0JJHVlQJEx+5/qgUH2M0CFtsGCpk/L6zKoz6Q8y6gZNfiQ9GZ6qQJTX4qx9RPcdb/dN+qLZZ2io4rVujZSter/6ZDJYoKGEVrh84dqHBWKFJJZqJwYrNLXVSvZ/T6RcV4Neh9voL/BamQZbGeK4lFQUx9dMEIPQLE3Aa6whG/iqAVsP0SLNgkGcAtERK77anPY7/Lg5RmYrQ6SgOu9aALW2VanNtF3jqlgUcen/otCnVl12IwxOmiNV0zFAqUQXb/Jiqql6CpTqUaOk39dfp0UzfcT6XUeavpJItPaY9kQMPrmrCgqKgJ4SBa3MxbO0rJbOvJebwfZ38848hcMgLoupcrjdqeba4vNchstpiSdMXmu+31T9bwT/6XrgnPLlFq6r5YJCtonkBBb6adgMNPpnQ4HKSNRG7Hl+Cg1fQz/2yK660JJ8g4wRl7WHS0Mx+NCBH4X0iAPUreDTCapPgq0mPHncdYAAHKQESq0MxmQBKiufSzhjwajL6dhUWUKrRtwe4Lm/wj4fk+vk5BTxFQb8K1QjKPc+oCeMoWhSmaMu3yeJyDnVi4rXshkrmOxWo1fNJnKg/O8C79L1L7TyVf56XC1pdr5CvQGQwsnr3cHvEKxgNue4Ryv7Rtohuf8b80xoTyXWyCiNeZPeDqgMXCcFmB/v1Toe5wEdF8VdZ1spFvPaAQrJ6nktOYwNomYHRITTWMwtyryQrBQ0JkBqwBaHtI3N2pnJ+oT7XUegH4MsuOLpld1zXmZ6CpXSHaNIYORnNudBJufHv7EAkjmN2nD5MOxlgAAcrgg3lNMqxwbMYgtWFIepZBhGszP4d96yPK9N3ifGBSLzCg4ao8XPk3NULUj3/xzTaDopyphyQwdhQBfz1Z5hwQgF7/1bJ906XC7tZPCIhmwSRJnIMuMAGOFfx3595UPRAL8V0+aoTD+lAAEAtoF+AlzrTD32m9oVqXi9Q8zaQ6j3LrOX6vX8+cpSTdCyrE10qHBGq9/4Oak2MqCsh8XIpyOgp07i9XUrYPtxgJU4jYxfY30DzLiEUjW6l6WzLzNwYJDvv1sY2LNEivYEg5T4N7z2r9I4Q6Eo7EeggNyCidxgWlbFtPytbSr0+vkaU+DtK/LN/n44N3/R0OyS2WpzFiKXY0ClgxW/MiNoh9+8HSaNrkBY7xqkpIi5TNNhvjmr8VLPt+1mqf/fhK7WdjL5LDrLfKYsD0/0pbyuKLkCPppygO5ghAQolONX+B09mSXigakIYBzU4hhScUwE76zgf5rYY6fwv3PmXyYHe2Hyeb1I3DRIp1KkRX+hlvtYtlyhAnXWMC2utExykvdrFfnu8J/n7iZVnKlbQpbC4it+pjwEWk3/39lq/3U92DDOM//G7BdyP38u0BjoFaUjA5BWh5oVBChdeb4cU74o1jyPG6DAUOwnFfj0o6nSZI6AF0qI1uVeAwsBywPuEuxMdLT6Okgo49p1viJOzvtbJUe8I+QbyE8IXdroHeoOmY6EAm58i+Df4KgEP2MuKAG+ozAyh2pGCaolccKzJlCN5tLJHc9z/aNZsLBmnv1OASDfPTq7uJtkSTCIwcPxmjmZ+mG8dm4yGamZ1J0nTp/jkPOj0fYnsQ6j1KeYWRmLe08CpIhArrgCTCTz3cFgMev2WhmxEfbmdpBxPzRntfkkoHmwohZE+c73tmwHK03duAcUMTLxwY+ZHywotSDGuIvEGWApyb1Etpx1EfX9UvTDqho43P+X5U6T8HkSYfAJ6hMAY8IcNcUY0TOiHmQKfi1Wi1UN985rxCaAFQm71znJ9seYS1wfvx2Ka1Anznj1bWWqc70feJwyy8ScR21a0HWQGzockOGlnirSKKMn3YhCv0wu4BIO88R0p0ME0o0bd+uyd/X6qduuyXOl48IaEhjhVMjmbS7+JmvmTWC/5sC3Q0XPxjuGfZc6+rLi0O8FWjB5M46jxf+Eiu/cRQODvfslo191OpHuKzifKDjYOHTjm5gwehOD7az8f4tYnYf0o/GSI8JVHG2jE2lR4hwm3upNPEdDxY+gsw3AIJrVjxIv1DIY6dDjNt7+DLNdWdwOW8uD+W3yensjtMDdqmk4yWUokxo+Cyxlex0oCgkPJBhUeXyTic/l3f8dPDV22bbSh+FLIDxJ0JJMS8BDyup1OqPT9fN/5qBQTK/+VxI6copR/mqkE4XpzwWT8/qNAnle1RgEWUkD1yryNAmQc4VX0bLAQSZsK1JoZJkfNDzlBWI/l5DwU8izd1IZ8gn1UsgRttLd/No8Yz8bDv/pagFFFi7kjK5U8mrme/V82d2f3rHT+zA28YDgcsjFz5jqNrjQf0jOcBCQ43HnxynTYn3u/XztDV27YOKwoOW7zkgOuRmMPhr8xNFgkhh++9arMCYXyTNBtmPHjloiU7bfe8/0o9f3OxZA9hZiMmqcidy+ZpY46/nR9mBQN8wgUkhwB6V1906lleziW/6bm3XG2s5TogDzpoAExyPBJ6IurRNiGwnETkAlMwNyGyTUTC6sOE+OrwKQS9xKeBQ8rW7tGt6fyU/etvA4oSzsbmBFTrOsgA7Yi/ZcWCcHZpM3nodb4Bot3HDUd7CVeNjvfcBLi6f4v/EGLWDwKvjUR6+iDwoweXh3pdHAQFDJEqF1i6H6p2RjVanM5mV8QgaWtpxQCZmz8ob3AQjs2HhBa+EFHPoRgBx44wGE5nbZcqxwzndW/oIXeXZZ+uZOpHJpganAjsdUIFqBQUwGxS3ly6KtvdHh+zSLCFkVbcya9D1q5Ltdd5E+pBGgQ41fPZmTV+bCERnr9RJ9Ai2AK/FYaDi+rbbA4jPpjBBe6Fwsq3WompAtKFbsTpAeQSH5IDngo73xTkvlEHA75b6KS8AwplQcJbShw3GjlklyDDXP8QrrGS90wnYerTYM2p3FlMJl9b2S5raTTl4TRdTjDZ0V0we5yCz+Pcjyk7EZYY9B8LLUlBerU0d1ax3Ol2/BsrxBfe5laL6H7btAxjggkCscdSHckYxQXDuxRbSkjp/y86OR9asbtqHqropNa72C6cvVMS8AHDErFxaMZMJCAXe2ZNSAQPM5q1NP/4BMBIQEryH54LqhDCjv87PbJuEJp/gsnMwRUQG9hGLOqY1VjQAjxUdWnEdx+uH6bneFDtdN0oy+VpZHSnMFhR1rQRMiZ0Z9//uKMtxnmT/UJovs+/D8z4rKDn+ewbgOBXcGwvtP5lKlx/xad6IyFAhuR92HOtI36PtIEXVU48S93WClrQaliDjDQrcP7eyT7Ou1SB6gsc0BsiTWU88Li/rVb3E2iTW3PQukNTS4i7dbG+buPWVdQLgRqi82iTaJzBo7yFmhnbPNHmsv7mGCBDD0vBg+vHa7ls0rHU4T41bVdPkKde4/VrqSAwmIgq9Gxp88v8fFEqFgz/iLSn3v2J5lZ8QSE+dezPN5Ly9IMzAb/wphwltPFt/sZLEy4Wtvbq135tDGO4oov0DsLZLDmt5lnxCwrD9DejoSoc5tNtwYXRpvJh5DRuOE+NpBFpWi90oyOjLlWYyp2nYfVsi3KyCTbbqPdV7PgqrvXq02K2rUuLgJHyChxfVNDI1XkijErmIBKocTa7j104b91qxFz+nhwl96eyrU7B9GrTqup7NaNyUyTyRL4lI24NbEWLfe4jn0JKgLjylMAg1MBnlBHlLC3tTOXy+nxig4VlyWIWrV36/zddVIxfEoG6MCQ9JDF45MhYFgJybgJ2YwQYFs96i/zw4cvEU2AvOwynqF/MnKnRlGQInQPOdnRl2+KqAkhqVdv3J7KtQPS9afB/HlbdOPlq+EDDURwEJMtd1rWUCRt2m5nmxzQrqvWdc6bnxEGmI0CblG/SvqpfMJwyfkrOBiWDHozmeu53+fn9m2k/edanVqt+fKsrzPpu1VaW412ZaymEQwMxK/sXAL8E5qDgY1PYrJN8dVqiv4afwb/fO4nCN9pKtpFRc4LuvZ+TqO0GO4TCgoNyC8sTNIdq7Uqvd0Amcl2XdLkufxicTo8Wkl6XJeV5v4LabWoWr3Ngm3Nrs5oDCLkmgM+sRrvtMsCyDYPIXQpDPtkkzz6rMDmdQUtcp8PnPSHneu7m0KGVsDNuosXk021yt1rQUDIwpxFEEPKvWVtv7f20h8rcTURvBN3GgOtJc6x/bAPLrBOoLT5j0L8QOOdF/LP8obcVkx3k881AlacOVGTIiqGEvEWSYeaErF+OE57gsm2Aq2/FDkiroJPwTwbQks7yyAuXYWa4t67xoynIpnxzaHOrWTHU6hQzHmLep4aJYYY2NwFdK1YP54cQ2qxz7hRHKXXdh6bFI7u7P7VsB35JJa2QI2wx/QKMn5bW6EPG41absO+R+7e7xfmMryDMHoLD+L+Ft0RWuwveFy1IjA9dF5mEWOo9fnGq2XPIIkT/eB20DOtqg5Fw9UtNwxg+PhH4w2DbsTyTYcel9fCcZdDApSIRDOqVPFEMf7C6/sMpJi5N2qr49P+/nGLbqXNi7vjB9DKbPpVHX6xaZhPJm4BhFXb2RbQ+tXJEJd942U0yexZKgq+3+tsmMyQtVBICBx+07QJ8zTu2hVHJ/eJ92DT8eB6lLY8bT4Dcilrllv6BLI4I9PZgvd9bEBybYpbNmmjq2kC+5ZGD4O/jzXs0TGkSDtIK5fZF7S6mN/Zj5wy5p+7peTicEyR/AsdmOibQ9HJVLvh2jzaURx+WTvNV+6dz+GUcLCIGO5+jC0K3Li6NxvuOuSkcP7Yxa63A9rA5gUN2XIbvv8WMY0ZX4DDXU4FizvX4XkkhUsxyp0WgfkOXyanTsvlhyOoKXd+55sTyzHVdVVX1pT/okocHLC2oYr+QDHhBeBDA0IaF7HrMcS0tSuh2RByX4e8iXl3LmBkswC8ZqRRVYlmd72sLTwngooCwr9JpHwmREpNZYNtlZkEtGSta6AYEIFPKdxXw6Hg9NPr7881HR8zTll0iLp72Yz8QYNrYxsswwYXS8MyYKjUU/NzMH4uhWwvYJNPfzHacV49IMvp5UeWZgM1SLXhmDP7v9PWPreP7mdXJJ0qU9BTSdyeFyteKs9eWG+BopGKGayxXTSVVBjw55XuZZ94QALncjXgwOuZPmfxrE64B+A3ASG7ynJMphaiERgpA1WMbBgar3Q8G4rrRMl+nS8lH7WpYcedzCz6e947PNenZhlbZ3py6RBL/MSCJypCdM3X4qbk87ldu2WiH6cjh5ldsW/fsMw/L8CPVtvD0BboQ9+7odI1/LcElZdKJrKAwcxYf3fx91lX+dcBbMO07zYLvcP1AmEIWTJquTlEYIAul/JyF+KRFXYwCORPr+lV9oERrQEEBLEVdT4xhTJYPKvnWPck+bWLmQMy8ZK1cK+TDRVUr6d+hYs/cxKcnkrJX5vWavj1RNYSyFYc/c4JZUSbIgocwAiXe5mdV6rmCQf93No9lXKnjraxHdfRWjuXCXS54W+VIF9SrzSGe3XhP8w9Tur7k3wuwbNfx00CUvWnL3UCIOiryGVkHvPILMfUJaHddoMAz+xOPqAt0lv2FY3xGLfSVPDqASNV+ydYJOk2jv84shkYgmgSyFtNuRpyeZpPXASxm0xGL/PgKNgW1on7tmej1lkgmIcPtI6rALTTmIuR5SKR/AwESVgb5wnB6EUWDOzAyFlL5u+HplP4hYCBAuFe9kQ+5Ib2TYXWzlQVHgigES6Ta0/vK533U6dUbHP+jWIuMeTYDZu0HL1th9YjU1a/ax9ZMNix/2kNvZ0S21SwrvTfChoK9yh0wQ0x9tw3lzPpYaSlptJ/iUOOY+2Sn7YsYmUjpWQunmHYJeN8pPQvZkMIwRy0JBC9xFXunan22nfFRecbEoE77otaSmMUYBlTLF59Ku4zLL899zAoB6DxBITu8TxBonHU8ZlkrAYe38/c5MLYbWCGf9FVwECe8deCPyBl229y7KuME8yok0p4CDH0Wk+iDJQlZEjkqfr/l7oFYVJOCVEXkm2wTuR2977IYP52oa+mW4U5m2qiCvObTasOHFCu88exaQHRn7rZj40N0EvwaWjLVr9FWbU5VJ+q6Ux6dufrJ1+Kui4iwQzOvW08OcJlCTTNgybbmzQmAfMMvlYLFDZ/m/BBT/g6qXpy7v6PD8II7ncZq8KM/vldoDnQlBEiEO++Db5IQu6FdQpiab9rG8EdTsOSWo5X6yl8oNwExiD1barKeZVLBx3UlLh0mTq2Epn2BhhU+hoKpRmTzvUrG8WS0+1Z0aduF04McpP3OWYcJg1p44W2t2Knv4OaGt26Nk2P0/LIAYFjT7X+1OKe7NsWm8GL5EiplQgAcgZZwc+AHzfY94pFocGZ6PmntW388SF7OzqRYGQHU1kf4z8Y9IpldxN3FgxbiARgCWys7qaphoJ9sA2q0Elw6q+ilpDyoKyJRAp6EdLphgEmjcx666fNK3TnVpQdXKFrfPEaJSfuwdlgzAAxEp+14t73ixz+ibNBhBxGFuApFj/JRkWd1QcDsTFTW1J6xaGtK0bIoMkspXvcRzfxRukroWHKMNpuXgMPvcBImJGFVWCSg7gJpxeYArrBLxh7lPZ4Atns54tK59RqQt+kATAwQIFWholot7Zojfe06100+jDw35Vd5psySp00p5XJK1/2fMs5F6fe4rblhtWgVwdXQB9N8Xfx+ZdK+zz/Yh454UvNegBm80j+/9/gBaex+4nD8kNA46Qcy8sn055DAqMyA6hl3QpeYM92+vJpPMGtTDfh9AVekIKaWvfKli6YSJp8/MI6grFSRjNRN5RKy0kdVxWhd7Fsuzda/K4VG6C/gbu7E0KFhfIVR0g8Pc9PnIbwUS5hj81P3JSZFnauP7PJSKR/wEfKZGlzZLC96OF3QsX2DxKveR2sTzbxNcKurfZtzSK3xRVSiqm/1h/yKHoIml38goO7Y4GO+zRqrKWqtkqaZCTH5EWujzvno4CIRP8pgyMEQygKNnyOQDgRSYHBUlWSBGQ5YMjYzj2O3fj3H0Xo8QYXv56UzRuMvyJA3LAkGhB0OHLQ+4+3PmSHOv9PbyOp23o5evNTT48EdSprE7pnhoTMJGHC+buuvUaS4sh04dnJFh13HxDudjPaPTpGPyyfsJsuxPO4FiRdH0QPvRiq5KZxz/KvfUdOfao/8TNPn4RvouZBscAHo=
*/